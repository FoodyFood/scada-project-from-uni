//This section written by D O'Connor

#include "BaseComponent.h"
#include "CCTVCamera.h"
#include "CornerPipe.h"
#include "CrossJunction.h"
#include "HydraulicValve.h"
#include "IronPipe.h"
#include "PneumaticPump.h"
#include "SanitizationDrain.h"
#include "StorageTank.h"
#include "SuspendedConcreteGroundFloor.h"
#include "T_Junction.h"
#include "ThreeWayJunction.h"
#include "TwoWayJunction.h"
#include "WaterSource.h"

class Node	// Stores a component
{
public:
	Node(){Prior=NULL;Next=NULL;};				// constructor
	~Node(){};									// destructor

	Node* Prior;								// pointer to prior Node
	Node* Next;									// pointer to next Node
	class BaseComponent* component;				// component that the node stores
};

class List	// A list of all components
{
public:
	//Constructor and destructor
	List();
	~List();

	//Grid size variable
	UINT GRID_SIZE;

	//File access
	void SelectFile(HWND hWnd, bool openFile);			// selection of file into szFileName
	void ReadChosenFile(HWND hWnd);						// reads from file in szFileName
	void SaveChosenFile(HWND hWnd);						// saves to the file in szFileName
	void EmptyList(HWND hWnd, bool promptToSave, bool alsoClearFile);	// clears list

	//Modification of list contents
	void Add(char* iComp);								// add component from file string
	void AddComp(BaseComponent *iComp, HWND hWnd);		// add already defined component
	int  DeleteSelectedComponent();						// Deletes Component, count from 0, returns component ID

	//Modification of Components and Drawing functions
	void DrawComponents(HDC hdc);						// Draws all components to chosen DC
	void AnimateComponents(HDC hdc, WORD toAnimate);	// Animate the components
	int  SelectComponent(int ComponentNumber);			// Returns ComponentNumber if one already selected
	void UnSelectComponents(void);						// Unselects any selected components
	BaseComponent* GetSelectedComponent(void);			// Returns the selected component

	//Connect or Disconnect Sensor From Component
	int  IsPointOnComponent(POINT MousePosition, HWND hWnd);// Returns ComponentNumber at point, -1 if none
	void ConnectSensorToComponent(BaseComponent* comp, int sensor);

private:
	Node* Nodes;										// points to a node
	OPENFILENAME CurrentFile;							// the file for this list
	wchar_t szFileName[MAX_PATH];						// buffer for current file directory
};

List::List()
{
	GRID_SIZE=8;
	ZeroMemory(&CurrentFile, sizeof(CurrentFile));
	ZeroMemory(&szFileName, sizeof(szFileName));
	Nodes = NULL;			// initial node for list = NULL
}							// because nothing in list yet
List::~List()				// destructor method
{
	if(Nodes)
	{
		while( Nodes->Next != NULL ) // move pointer to first of list
			Nodes = Nodes->Next;
		while( Nodes->Prior != NULL ) //delete all nodes
		{
			Nodes = Nodes->Prior;
			delete Nodes->Next;
		}
		delete Nodes;
	}
}

void List::SelectFile(HWND hWnd, bool openFile)		// set true to open, false to save
{
	ZeroMemory(&CurrentFile, sizeof(CurrentFile));
	ZeroMemory(&szFileName, sizeof(szFileName));

	CurrentFile.lStructSize = sizeof(CurrentFile);
	CurrentFile.hwndOwner = hWnd;
	CurrentFile.lpstrFilter = L"SCADA Files (*.scd)\0*.scd\0All Files (*.*)\0*.*\0";
	CurrentFile.lpstrFile = szFileName;
	CurrentFile.nMaxFile = MAX_PATH;
	CurrentFile.Flags = OFN_EXPLORER | OFN_OVERWRITEPROMPT | OFN_ENABLESIZING | OFN_HIDEREADONLY;
	CurrentFile.lpstrDefExt = L"scd";

	if(openFile)
	{
		if(GetOpenFileName(&CurrentFile))
		{
			EmptyList(hWnd, false, false);
			ReadChosenFile(hWnd);
		}
	}
	else
	{
		if(GetSaveFileName(&CurrentFile))
			SaveChosenFile(hWnd);
	}
}
void List::ReadChosenFile(HWND hWnd)
{
	SendMessage(hWnd, WM_COMMAND, ID_RUN_STOPWORKSHEET, NULL);	//stops animation before loading new file

	HANDLE hFile = CreateFile(szFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	DWORD numberOfBytesRead=1;
	char iComp[ReadPerComponent*CharPerValue+1];	// should be size of important attributes only

	if(hFile == INVALID_HANDLE_VALUE)
	{
		MessageBoxW(hWnd, L"Error opening file.", L"File Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}
	else 
	{
		while (numberOfBytesRead)
		{
			ReadFile(hFile, iComp, (DWORD) ReadPerComponent*CharPerValue, &numberOfBytesRead, NULL);

			if (numberOfBytesRead == ReadPerComponent*CharPerValue)
				Add(iComp);
			else break;
		}
		CloseHandle(hFile);
	}

	UnSelectComponents();
	DrawComponents(GetDC(hWnd));
}
void List::SaveChosenFile(HWND hWnd)
{
	if(Nodes)
	{
		if(!szFileName[0])				// if a file is open this parameter has a value
			SelectFile(hWnd, false);	// save the file to a selected location instead

		//else,, save to current location
		HANDLE hFile = CreateFile(szFileName, GENERIC_WRITE, FILE_SHARE_READ, NULL, 
			CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

		if(hFile != INVALID_HANDLE_VALUE)
		{
			while( Nodes->Prior != NULL ) Nodes = Nodes->Prior; // move to first component
			Node* temp = Nodes;
			while( temp != NULL )
			{
				char buffer[ReadPerComponent][IntToSTR], buffer1[IntToSTR];
				DWORD written=0;

				_itoa_s(temp->component->getId(),   buffer[0], 10);
				_itoa_s(temp->component->getX(),    buffer[1], 10);
				_itoa_s(temp->component->getY(),    buffer[2], 10);
				_itoa_s(temp->component->getOrientation(), buffer[3], 10);
				_itoa_s(temp->component->getFuture0(), buffer[4], 10);
				_itoa_s(temp->component->getFuture1(), buffer[5], 10);
				_itoa_s(temp->component->getFuture2(), buffer[6], 10);

				for(int round=0;round<ReadPerComponent;round++)
				{
					int r=0;
					while(buffer[round][r++]);
					r=IntToSTR-r;
					int y=0;
					while(y+r<IntToSTR)
					{
						buffer1[y+r]=buffer[round][y];
						y++;
					}
					y=0;
					while(y<r)
					{
						buffer1[y]='0';
						y++;
					}

					WriteFile(hFile,buffer1,IntToSTR-1,&written,NULL);
				}
				temp = temp->Next;
			}
			CloseHandle(hFile);
		}
		else
		{
			MessageBox(hWnd, 
				L"Could not save to the chosen file\nBe sure the file is not write protected",
				L"Save File", MB_OK|MB_ICONEXCLAMATION);
		}
	}
}
void List::EmptyList(HWND hWnd, bool promptToSave, bool alsoClearFile)
{
	if(Nodes)
	{
		SendMessage(hWnd, WM_COMMAND, ID_RUN_STOPWORKSHEET, NULL);	//stops animation before emptying

		if(promptToSave)
		{
			DWORD choice = MessageBox(hWnd, L"Would you like to save your work first?", 
				L"New Document", MB_YESNOCANCEL|MB_ICONQUESTION);

			if(choice == IDYES)
				SaveChosenFile(hWnd);
			else if(choice == IDCANCEL)
				return;
		}

		while( Nodes->Next) // move pointer to first of list
			Nodes = Nodes->Next;
		while( Nodes->Prior) //delete all nodes
		{
			Nodes = Nodes->Prior;
			delete Nodes->Next;
		}
		delete Nodes;
		Nodes = NULL;
	}

	if(alsoClearFile)
	{
		ZeroMemory(&CurrentFile, sizeof(CurrentFile));				//clears file names
		ZeroMemory(&szFileName, sizeof(szFileName));
	}

	RECT client;
	GetClientRect(hWnd, &client);
	InvalidateRect(hWnd, &client, true);
}

// Function for adding components into the list  - Darragh O'Neill 
void List::Add(char* iComp)
{
	//deselect anything previously selected
	UnSelectComponents();

	// N is pointer to a new node
	Node *N = new Node;							
	N->Prior = NULL;
	N->Next = NULL;

	//Assign values here from iComp string
	int vals[ReadPerComponent];					//1 part is ID then values
	for(int i=0;i<ReadPerComponent;i++)
	{
		char section[CharPerValue+1];
		for(int t=0;t<CharPerValue;t++)
			section[t]=iComp[t+i*CharPerValue];
		section[CharPerValue]=NULL;
		vals[i]=atoi(section);
	}

	//Create new components of correct type and put into N->component
	if(vals[0]==1)	    //where 1 is a CCTVCamera ID
		N->component=new CCTVCamera(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==2)	//where 2 is an CornerPipe ID
		N->component=new CornerPipe(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==3)	//where 3 is an CrossJunction ID
		N->component=new CrossJunction(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==4)	//where 4 is an HydraulicValve ID
		N->component=new HydraulicValve(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==5)	//where 5 is an IronPipe ID
		N->component=new IronPipe(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==6)	//where 6 is an PneumaticPump ID
		N->component=new PneumaticPump(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==7)	//where 7 is an SanitizationDrain ID
		N->component=new SanitizationDrain(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==8)	//where 8 is an StorageTank ID
		N->component=new StorageTank(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==9)	//where 9 is an SuspendedConcreteGroundFloor ID
		N->component=new SuspendedConcreteGroundFloor(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==10)//where 10 is an T_Junction ID
		N->component=new T_Junction(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==11)//where 11 is an ThreeWayJunction ID
		N->component=new ThreeWayJunction(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==12)//where 12 is an TwoWayJunction ID
		N->component=new TwoWayJunction(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else if(vals[0]==13)//where 13 is an WaterSource ID
		N->component=new WaterSource(vals[0],vals[1],vals[2],vals[3],vals[4],vals[5],vals[6]);
	else
	{
		delete N;
		return;
	}

	//Continue the adding process
	if( Nodes == NULL )							// if this is the first time around
	{
		Nodes = N;								// make new node current node
		return;
	}

	while( Nodes->Next != NULL )				// else move current to end of list
		Nodes = Nodes->Next;

	N->Prior = Nodes;							// point new entry prior to current
	Nodes->Next = N;							// and current next to the new node
	Nodes = N;									// point current to new end of list
	return;
}
void List::AddComp(BaseComponent *iComp, HWND hWnd)
{
	//deselect anything previously selected
	UnSelectComponents();

	Node *N = new Node;							// N is pointer to a new node
	N->Next=NULL;
	N->Prior=NULL;
	N->component=iComp;

	if(Nodes)
	{
		while( Nodes->Next ) Nodes = Nodes->Next; // move to last component
		N->Prior = Nodes;
		Nodes->Next=N;
	}
	else Nodes=N;
}

void List::DrawComponents(HDC hdc)
{
	if(Nodes)
	{
		while( Nodes->Prior ) Nodes = Nodes->Prior; // move to first component
		Node* temp = Nodes;
		while( temp )
		{
			temp->component->draw(hdc, GRID_SIZE);
			temp = temp->Next;
		}
	}
}
void List::AnimateComponents(HDC hdc, WORD toAnimate)
{
	if(Nodes)
	{
		int inputSel=0;
		while(inputSel<10)
		{
			WORD mask=0x1;
			mask<<=inputSel;
			if(mask & toAnimate)
			{
				Node* tNode= Nodes;									// temp node for modification
				while(tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list

				while(tNode)
				{
					if(tNode->component->getFuture2() == inputSel+1)
						tNode->component->animate(hdc, GRID_SIZE);
					tNode=tNode->Next;
				}
			}
			inputSel++;
		}
	}
}

int List::DeleteSelectedComponent()
{
	int ComponentNumber=0;
	int ComponentID=0;

	if(Nodes)
	{
		Node* tNode= Nodes;									// temp node for modification
		while(tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list

		while(!(tNode->component->isComponentActive()))		// while this isnt the node
		{
			tNode=tNode->Next;							// move to next node
			if(tNode==NULL)								// if theres no more and wasnt found, return
				return 0;
			ComponentNumber++;							// increase component count
		}

		while(Nodes->Prior) Nodes = Nodes->Prior;			// move pointer to first of list

		if(ComponentNumber == 0 && Nodes->Next)
		{
			Nodes = Nodes->Next;
			ComponentID=Nodes->Prior->component->getId();
			delete Nodes->Prior;
			Nodes->Prior=NULL;
			return ComponentID;
		}
		else if(ComponentNumber == 0)
		{
			ComponentID=Nodes->component->getId();
			delete Nodes;
			Nodes=NULL;
			return ComponentID;
		}
		for(ComponentNumber;ComponentNumber>1;ComponentNumber--)
		{
			if(Nodes->Next == NULL) return -1;
			Nodes=Nodes->Next;
		}

		Node* temp;
		temp=Nodes->Next;

		if(temp->Next)
		{
			Nodes->Next=temp->Next;
			Nodes->Next->Prior=Nodes;
		}
		else
			Nodes->Next=NULL;

		ComponentID=temp->component->getId();
		delete temp;
		return ComponentID;
	}
	return -1;
}
int List::SelectComponent(int ComponentNumber)
{
	if(Nodes && ComponentNumber >= 0)						// if there are nodes and ComponentNumber is valid
	{
		//Check if any nodes are already active
		Node* tNode= Nodes;									// temp node for modification
		int tComponentNumber=0;								// component counter
		while(tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list
		while(tNode)										// while there is a node
		{
			if(tNode->component->isComponentActive())		// check if the node is active
				return tComponentNumber;					// if yes, return the active node number
			tNode=tNode->Next;								// if no, move to next node
			tComponentNumber++;								// increase component count
		}

		//If there are no active nodes, proceed to select the chosen node
		tComponentNumber=ComponentNumber;					// reset the component counter
		tNode=Nodes;										// reset temporary node pointer

		while( tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list
		while(tComponentNumber && tNode)					// while we are not at the chosen node yet
		{
			--tComponentNumber;								// decrease the temp counter
			tNode=tNode->Next;								// and move to the next node
		}

		if(tNode == NULL)									// if not enough components
			return -1;										// returns -1

		tNode->component->setSelected(true);				// when at correct node, set to active
	}
	return ComponentNumber;									// return the selected node number for error check
}
void List::UnSelectComponents()
{
	if(Nodes)
	{
		while(Nodes->Prior) Nodes=Nodes->Prior;
		Node* tNodes=Nodes;
		while(tNodes)
		{
			tNodes->component->setSelected(false);
			tNodes=tNodes->Next;
		}
	}
}
BaseComponent* List::GetSelectedComponent()
{
	int ComponentNumber=0;									// component counter
	if(Nodes)
	{
		Node* tNode= Nodes;									// temp node for modification
		while(tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list
		while(tNode)										// while there is a node
		{
			if(tNode->component->isComponentActive())		// check if the node is active
				return tNode->component;					// if yes, return the active node number
			tNode=tNode->Next;								// if no, move to next node
		}
	}
	return NULL;
}

int List::IsPointOnComponent(POINT MousePosition, HWND hWnd)
{
	if(Nodes)
	{
		Node* tNode=Nodes;
		RECT compRECT;
		int componentNumber=0;

		while( tNode->Prior) tNode = tNode->Prior;			// move pointer to first of list

		ScreenToClient(hWnd, &MousePosition);

		while(tNode)										// while there are more to check
		{
			tNode->component->getComponentRECT(compRECT);	// get component bound
			if(MousePosition.x > compRECT.left && MousePosition.x < compRECT.right)		// check x
				if(MousePosition.y > compRECT.top && MousePosition.y < compRECT.bottom) // check y
					return componentNumber;					// if both x & y, returns component number

			tNode=tNode->Next;		// move to next node
			componentNumber++;		// increment conter to next node
		}							// exits if not on any component
	}								// exits if there are no nodes
	return -1;						// return -1 on either condition above
}
void List::ConnectSensorToComponent(BaseComponent* comp, int sensor)
{
	if(comp)						// if comp is real
		comp->setFuture2(sensor);		// set the sensor
}
