//This section written by D O'Connor

// SCADA.cpp : Defines the entry point for the application.


#include "stdafx.h"
#include "SCADA.h"

List myCompList;
ComTransact myArduino;

// Global Variables:
HINSTANCE hInst;								// current instance
#define MAX_LOADSTRING 100
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);
BOOL CALLBACK		EditAttb(HWND, UINT, WPARAM, LPARAM);

#pragma warning(suppress: 28251)
int APIENTRY _tWinMain(HINSTANCE hInstance,HINSTANCE hPrevInstance,LPTSTR lpCmdLine,int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	MSG msg;
	HACCEL hAccelTable;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_SCADA, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
		return FALSE;

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SCADA));

	//initialise common controls for toolbar & status bar
	INITCOMMONCONTROLSEX icex;
	icex.dwSize=sizeof(INITCOMMONCONTROLSEX);
	icex.dwICC=ICC_BAR_CLASSES;
	InitCommonControlsEx(&icex);

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SCADA));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_SCADA);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	HWND hWnd;

	hInst = hInstance; // Store instance handle in our global variable

	hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, 880, 554, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	//Declare variables used
	static BaseComponent *lastComp;			// the last component placed
	static BOOL runAnimation = false;		// whether to animate or not
	int wmId, wmEvent;						// message break down
	RECT wArea, rcStatus;					// working area RECT, Status bar RECT

	//Draw only to area not in status & tool bar area				// only works after WM_CREATE complete
	GetClientRect(hWnd,&wArea);										// get ClientArea
	GetWindowRect(GetDlgItem(hWnd, IDC_MAIN_STATUS), &rcStatus);	// get status bar area
	wArea.top+=HeightOfToolbar;										// ignore toolbar
	wArea.bottom-=(rcStatus.bottom-rcStatus.top);					// ignore status bar

	//Begin message handling
	switch (message)
	{
	case WM_COMMAND:
		{
			wmId    = LOWORD(wParam);
			wmEvent = HIWORD(wParam);

			switch (wmId)
			{
				//Common commands
			case IDM_ABOUT:
				DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
				break;
			case IDM_EXIT:
				DestroyWindow(hWnd);
				break;
			case ID_FILE_NEW:
				myCompList.EmptyList(hWnd, true, true);
				break;
			case ID_FILE_OPEN:
				myCompList.SelectFile(hWnd, true);
				break;
			case ID_FILE_SAVE:
				myCompList.SaveChosenFile(hWnd);
				break;
			case ID_FILE_SAVEAS:
				myCompList.SelectFile(hWnd, false);
				break;
			case ID_FILE_PRINT:
				{
					//Variables
					int iPagX, iPagY;

					//Printing structures & initialisation
					PRINTDLG pd = {0};
					DOCINFO di = {sizeof(DOCINFO),L"SCADA Print"};

					//Set up printer struct
					pd.lStructSize = sizeof(pd);
					pd.hwndOwner = hWnd;
					pd.Flags = PD_RETURNDC;
					PrintDlg(&pd);

					//Get printer DC dimentions to set up the page
					iPagX = GetDeviceCaps(pd.hDC,HORZRES);
					iPagY = GetDeviceCaps(pd.hDC,VERTRES);

					//Set up printer
					StartDoc( pd.hDC, &di );
					StartPage( pd.hDC );
					SetMapMode( pd.hDC, MM_ISOTROPIC );
					SetWindowExtEx( pd.hDC, iPagX, iPagY, NULL );
					SetViewportExtEx( pd.hDC, iPagX, iPagY, NULL );
					SetViewportOrgEx( pd.hDC, 0, 0, NULL );

					//Organise for the screen to be copied to the printer
					RECT cRect;
					GetClientRect(hWnd, &cRect);
					iPagY=(int)floor((iPagX/(float)cRect.right)*(cRect.bottom-HeightOfToolbar));

					//Copy to printer DC
					StretchBlt( pd.hDC, 10, 10, iPagX-10, iPagY-10, GetDC(hWnd), 0, 
						HeightOfToolbar, cRect.right, cRect.bottom-HeightOfToolbar, SRCCOPY);

					//Send to print
					EndPage( pd.hDC );
					EndDoc( pd.hDC );
				}
				break;

				//Animation & Redraw Commands
			case ID_RUN_STARTWORKSHEET:
				runAnimation=true;					//set animation
				SetTimer(hWnd, IDT_EXTANIMATE, AnimationSpeed, (TIMERPROC) NULL);
				SetTimer(hWnd, IDT_EXTUPDATE, DataUpdateSpeed, (TIMERPROC) NULL);
				break;
			case ID_RUN_STOPWORKSHEET:
				runAnimation=false;					//unset animation
				KillTimer(hWnd, IDT_EXTANIMATE);
				KillTimer(hWnd, IDT_EXTUPDATE);
				break;
			case ID_VIEW_REFRESH:
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PORT_COM1:
				myArduino.ChoosePort(hWnd, L"COM1");
				break;
			case ID_PORT_COM2:
				myArduino.ChoosePort(hWnd, L"COM2");
				break;
			case ID_PORT_COM3:
				myArduino.ChoosePort(hWnd, L"COM3");
				break;
			case ID_SENSOR_NONE:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),0);
				break;
			case ID_SENSOR_1:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),1);
				break;
			case ID_SENSOR_2:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),2);
				break;
			case ID_SENSOR_3:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),3);
				break;
			case ID_SENSOR_4:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),4);
				break;
			case ID_SENSOR_5:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),5);
				break;
			case ID_SENSOR_6:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),6);
				break;
			case ID_SENSOR_7:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),7);
				break;
			case ID_SENSOR_8:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),8);
				break;
			case ID_SENSOR_9:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),9);
				break;
			case ID_SENSOR_10:
				myCompList.ConnectSensorToComponent(myCompList.GetSelectedComponent(),10);
				break;

				//Zoom Commands
			case ID_ZOOM_50:
				myCompList.GRID_SIZE=4;
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_ZOOM_100:
				myCompList.GRID_SIZE=8;
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_ZOOM_150:
				myCompList.GRID_SIZE=12;
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_ZOOM_200:
				myCompList.GRID_SIZE=16;
				InvalidateRect(hWnd,&wArea,true);
				break;

				//Context Commands
			case ID_CONTEXT_PIPEUP: 
				myCompList.GetSelectedComponent()->setFuture0
					(myCompList.GetSelectedComponent()->getFuture0() + 1);
				InvalidateRect(hWnd, &wArea, true);
				break;
			case ID_CONTEXT_PIPEDOWN:
				if(myCompList.GetSelectedComponent()->getFuture0() > 1)
					myCompList.GetSelectedComponent()->setFuture0
					(myCompList.GetSelectedComponent()->getFuture0() - 1);
				InvalidateRect(hWnd, &wArea, true);
				break;
			case ID_CONTEXT_ROTATE:
				lastComp=myCompList.GetSelectedComponent();
				if(lastComp->getOrientation()>=3) lastComp->setOrientation(0);
				else lastComp->setOrientation(lastComp->getOrientation()+1);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_CONTEXT_DELETE:
				myCompList.DeleteSelectedComponent();
				InvalidateRect(hWnd,&wArea,true);
				break;

				//Component Creation Commands
			case ID_PLACE_CCTVCAMERA:
				myCompList.AddComp(new CCTVCamera(1,20,7,orientation2::left,12,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_CORNERPIPE:
				myCompList.AddComp(new CornerPipe(2,25,6,orientation2::top,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_CROSSJUNCTION:
				myCompList.AddComp(new CrossJunction(3,30,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_HYDRAULICVALVE:
				myCompList.AddComp(new HydraulicValve(4,35,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_IRONPIPE:
				myCompList.AddComp(new IronPipe(5,40,7,orientation2::left,7,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_PNEUMATICPUMP:
				myCompList.AddComp(new PneumaticPump(6,45,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_SANITIZATIONDRAIN:
				myCompList.AddComp(new SanitizationDrain(7,50,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_STORAGETANK:
				myCompList.AddComp(new StorageTank(8,55,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_SUSPENDEDCONCRETEGROUNDFLOOR:
				myCompList.AddComp(new SuspendedConcreteGroundFloor(9,60,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_TJUNCTION:
				myCompList.AddComp(new T_Junction(10,65,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_THREEWAYJUNCTION:
				myCompList.AddComp(new ThreeWayJunction(11,70,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_TWOWAYJUNCTION:
				myCompList.AddComp(new TwoWayJunction(12,75,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
			case ID_PLACE_WATERSOURCE:
				myCompList.AddComp(new WaterSource(13,80,7,orientation2::left,0,0,0), hWnd);
				InvalidateRect(hWnd,&wArea,true);
				break;
				//Message Not Processed
			default:
				return DefWindowProc(hWnd, message, wParam, lParam);
			}
		}
		break;

		//Drawing in the window
	case WM_PAINT:
		{
			//Get DC
			PAINTSTRUCT ps;						// paint struct for the DC
			HDC hdc = BeginPaint(hWnd, &ps);	// device context

			//Bitmap storage
			HDC hdcMem;
			HBITMAP hbmMem;
			RECT tempScr;

			GetClientRect(hWnd, &tempScr);
			hdcMem = CreateCompatibleDC(hdc);
			hbmMem = CreateCompatibleBitmap(hdc, tempScr.right, tempScr.bottom);
			SelectObject(hdcMem, hbmMem);

			//Fill the bitmap with white
			HBRUSH hbrBkGnd = CreateSolidBrush(GetSysColor(COLOR_WINDOW));
			FillRect(hdcMem, &tempScr, hbrBkGnd);
			DeleteObject(hbrBkGnd);

			//Calculate working area
			wArea.top+=myCompList.GRID_SIZE-1;
			wArea.bottom=(wArea.bottom-(wArea.bottom%myCompList.GRID_SIZE)-myCompList.GRID_SIZE-1);
			wArea.left=myCompList.GRID_SIZE-1;
			wArea.right=(wArea.right-(wArea.right%myCompList.GRID_SIZE)-myCompList.GRID_SIZE-1);

			//Draw working area
			Rectangle(hdcMem,wArea.left,wArea.top,wArea.right,wArea.bottom);

			//Fill working area with grid
			for(UINT x=1;x<(wArea.right-wArea.left)/myCompList.GRID_SIZE;x++)
				for(UINT y=1;y<(wArea.bottom-wArea.top)/myCompList.GRID_SIZE;y++)		// pixels are grey
					SetPixel(hdcMem,x*myCompList.GRID_SIZE+wArea.left,y*myCompList.GRID_SIZE+wArea.top,0x00959595);

			//Draw all components in list
			myCompList.DrawComponents(hdcMem);

			//assign animation data to parts if animation is active
			if(runAnimation)
				myCompList.AnimateComponents(hdcMem, myArduino.GetData());
			//WORD temp = 2047;
			//myCompList.AnimateComponents(hdcMem, temp);

			//Finish Drawing
			BitBlt(hdc,0,HeightOfToolbar,tempScr.right,tempScr.bottom,hdcMem,0,HeightOfToolbar,SRCCOPY);

			DeleteObject(hbmMem);
			DeleteDC(hdcMem);
			EndPaint(hWnd, &ps);
		}
		break;

		//Creating the context menu
	case WM_CONTEXTMENU:
		{
			HMENU hMenu = CreatePopupMenu(), hAttachMenu;				// context menu handle
			if(hMenu != INVALID_HANDLE_VALUE)
			{
				POINT test;
				GetCursorPos(&test);
				int onComponent = myCompList.IsPointOnComponent(test, hWnd);

				if(onComponent >= 0) // mouse was over item
				{
					//Special menu for pipes
					myCompList.SelectComponent(onComponent);			// select the item
					if(myCompList.GetSelectedComponent()->getId() == 5)	// where 5 id the ID of a pipe
					{
						AppendMenu(hMenu, MF_STRING, ID_CONTEXT_PIPEUP, TEXT("&Extend Pipe"));
						AppendMenu(hMenu, MF_STRING, ID_CONTEXT_PIPEDOWN, TEXT("&Shorten Pipe"));
						AppendMenu(hMenu, MF_SEPARATOR, NULL, NULL);
					}

					//Create a sub menu
					hAttachMenu=CreatePopupMenu();
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_NONE, TEXT("&Disconnect"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_1, TEXT("&Input 1"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_2, TEXT("&Input 2"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_3, TEXT("&Input 3"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_4, TEXT("&Input 4"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_5, TEXT("&Input 5"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_6, TEXT("&Input 6"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_7, TEXT("&Input 7"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_8, TEXT("&Input 8"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_9, TEXT("&Input 9"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_10, TEXT("&Input 10"));
					AppendMenu(hAttachMenu, MF_STRING, ID_SENSOR_11, TEXT("&Input 11"));

					//Attach the popup to the menu
					AppendMenu(hMenu, MF_STRING|MF_POPUP, (UINT) hAttachMenu, TEXT("&Attach Sensor"));
					AppendMenu(hMenu, MF_STRING, ID_CONTEXT_ROTATE, TEXT("&Rotate"));
					AppendMenu(hMenu, MF_STRING, ID_CONTEXT_DELETE, TEXT("&Delete"));
				}
				else // mouse wasnt over item
				{
					myCompList.UnSelectComponents();					// unselect any items
					hAttachMenu=CreatePopupMenu();
					AppendMenu(hMenu, MF_GRAYED|MF_POPUP, (UINT) hAttachMenu, TEXT("&Attach Sensor"));
					AppendMenu(hMenu, MF_GRAYED, ID_CONTEXT_ROTATE, TEXT("&Rotate"));
					AppendMenu(hMenu, MF_GRAYED, ID_CONTEXT_DELETE, TEXT("&Delete"));
				}
				TrackPopupMenu(hMenu, TPM_RIGHTBUTTON, LOWORD(lParam), HIWORD(lParam), 0, hWnd, NULL);
				DestroyMenu(hMenu);
			}
		}
		break;

		//Create the status and toolbar
	case WM_CREATE:
		{
			//Create the status bar
			HWND hStatus = CreateWindowEx(0, STATUSCLASSNAME, NULL,
				WS_CHILD | WS_VISIBLE | SBARS_SIZEGRIP, 0, 0, 0, 0,
				hWnd, (HMENU)IDC_MAIN_STATUS, GetModuleHandle(NULL), NULL);
#pragma warning(suppress: 6246)
			RECT rcStatus;
			GetWindowRect(GetDlgItem(hWnd, IDC_MAIN_STATUS), &rcStatus);
			int widths[4]={rcStatus.right-200,-1};
			SendMessage(hStatus, SB_SETPARTS, 2, (LPARAM)widths);
			SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)L"SCADA");

			//Create the tool bar
			TBBUTTON toolbarButtons[4];
			TBADDBITMAP tbab;
			HWND hTool = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
				hWnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);

			SendMessage(hTool, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);

			tbab.hInst = HINST_COMMCTRL;
			tbab.nID = IDB_STD_SMALL_COLOR;
			SendMessage(hTool, TB_ADDBITMAP, 0, (LPARAM)&tbab);

			ZeroMemory(toolbarButtons, sizeof(toolbarButtons));
			toolbarButtons[0].iBitmap   = STD_FILENEW;
			toolbarButtons[0].fsState   = TBSTATE_ENABLED;
			toolbarButtons[0].fsStyle   = TBSTYLE_BUTTON;
			toolbarButtons[0].idCommand = ID_FILE_NEW;
			toolbarButtons[1].iBitmap   = STD_FILEOPEN;
			toolbarButtons[1].fsState   = TBSTATE_ENABLED;
			toolbarButtons[1].fsStyle   = TBSTYLE_BUTTON;
			toolbarButtons[1].idCommand = ID_FILE_OPEN;
			toolbarButtons[2].iBitmap   = STD_FILESAVE;
			toolbarButtons[2].fsState   = TBSTATE_ENABLED;
			toolbarButtons[2].fsStyle   = TBSTYLE_BUTTON;
			toolbarButtons[2].idCommand = ID_FILE_SAVE;
			toolbarButtons[3].iBitmap   = STD_PRINT;
			toolbarButtons[3].fsState   = TBSTATE_ENABLED;
			toolbarButtons[3].fsStyle   = TBSTYLE_BUTTON;
			toolbarButtons[3].idCommand = ID_FILE_PRINT;

			SendMessage(hTool, TB_ADDBUTTONS, 4, (LPARAM)&toolbarButtons);
		}
		break;

		//Window resizing
	case WM_SIZE:
		{
			SendMessage(GetDlgItem(hWnd, IDC_MAIN_STATUS), WM_SIZE, 0, 0);
			SendMessage(GetDlgItem(hWnd, IDC_MAIN_TOOL), TB_AUTOSIZE, 0, 0);
		}
		break;
	case WM_ERASEBKGND:				// stop background erase when resizing
		{							// causes window to blank before WM_PAINT
			return (LRESULT)1;		// by stopping this, there is no flicker between paints
		}
		break;

		//Animation timer handling
	case WM_TIMER:
		{
			switch (wParam)
			{ 
			case IDT_EXTANIMATE: 
				//Force a WM_PAINT message to be sent
				InvalidateRect(hWnd, &wArea, true);
				break;
			case IDT_EXTUPDATE:
				//Update the stored data
				myArduino.UpdateData(hWnd);
				break;
			}
		}
		break;

		//Handling the Mouse
	case WM_LBUTTONDOWN:
		{
			POINT test;
			int comp;

			GetCursorPos(&test);
			myCompList.UnSelectComponents();
			comp = myCompList.IsPointOnComponent(test, hWnd);

			if(comp+1 >= 0)							// if there was a component
				myCompList.SelectComponent(comp);	// select the component
		}
		break;
	case WM_MOUSEMOVE: 
		if (wParam & MK_LBUTTON)
		{
			POINT curPos;
			curPos.x = LOWORD(lParam);
			curPos.y = HIWORD(lParam);

			if(lastComp=myCompList.GetSelectedComponent())
			{
				lastComp->setX(curPos.x/myCompList.GRID_SIZE-1);
				lastComp->setY((curPos.y-HeightOfToolbar)/myCompList.GRID_SIZE-1);
				InvalidateRect(hWnd, &wArea, true);
			}
		}
		break;
	case WM_LBUTTONUP:
		{
			POINT test;
			int comp;

			GetCursorPos(&test);
			myCompList.UnSelectComponents();
			comp = myCompList.IsPointOnComponent(test, hWnd);

			if(comp+1 >= 0)							// if there was a component
				myCompList.SelectComponent(comp);	// select the component
			else myCompList.UnSelectComponents();	// no component, unselect any selected

			InvalidateRect(hWnd, &wArea, true);		// force a redraw
		}
		break;

		//Destroy the window
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDCLOSE || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}
