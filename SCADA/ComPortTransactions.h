//This section written by D O'Connor

#include "ComClass.h"

class ComTransact
{
public:
	ComTransact();
	~ComTransact();

	void ChoosePort(HWND hWnd, LPCWSTR Port);
	void UpdateData(HWND hWnd);
	WORD GetData();


private:
	ComPort myComPort;
	WORD data;
};

ComTransact::ComTransact()
{
	data = NULL;
}
ComTransact::~ComTransact()
{
	myComPort.Disconnect();
}

void ComTransact::ChoosePort(HWND hWnd, LPCWSTR Port)
{
	if(myComPort.IsConnected())
		myComPort.Disconnect();

	myComPort.Connect(hWnd, Port);
}
WORD ComTransact::GetData()
{
	return data;	//returns the current data, not updated
}
void ComTransact::UpdateData(HWND hWnd)
{
	//Check if there is a connection
	if(!myComPort.IsConnected())		// if not
	{									// report the error
		KillTimer(hWnd, IDT_EXTANIMATE);// kill the animation timers
		KillTimer(hWnd, IDT_EXTUPDATE);
		MessageBox(hWnd, L"No COM port selected", L"COM Error", MB_OK|MB_ICONERROR);
		return;							// return
	}

	//Send request for data
	unsigned char dataRequest = 'H';
	if(!myComPort.WriteData(&dataRequest, 1))
		return;
	Sleep(35);	//Loxking function, bad code, but small enough that it shouldnt be an inconvenience

	//Retrieve data
	unsigned char buffer[4];
	if(myComPort.ReadData(buffer, 4))
	{
		if(buffer[0]==10 && buffer[3]==10) //data assumed correct
		{
			//Combine the 2 buffer bytes into a word
			data=buffer[2];				//second buffer byte is high byte
			data<<=8;					//move to the high position
			data |= buffer[1];	//put in the low byte
		}
		else									//data assumed bad
		{
			data=NULL;
		}
	}
}