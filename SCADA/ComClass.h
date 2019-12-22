//This section written by D O'Connor

#ifndef COMCLASS
#define COMCLASS

class ComPort
{
private:
	HANDLE hCom;
	bool connected;

public:
	ComPort();
	~ComPort();

	BOOL Connect(HWND hWnd, LPCWSTR Port);			// Connect to passed port
	void Disconnect();								// Disconnect port
	BOOL IsConnected();								// Check if serial is connected

	DWORD ReadData(unsigned char *buffer, UINT nbChars);	// Read nb bytes
	DWORD WriteData(unsigned char *buffer, UINT nbChars);	// Write nb bytes
};

ComPort::ComPort()
{
	connected = false;
	hCom=NULL;
}
ComPort::~ComPort()
{
	if(connected)	// If connected, disconnect
	{
		CloseHandle(hCom);
		connected = false;
	}
}

BOOL ComPort::Connect(HWND hWnd, LPCWSTR Port)
{
	//Try to connect to the given port throuh CreateFile
	hCom = CreateFile(Port, GENERIC_READ | GENERIC_WRITE, 0,
		NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	//Check if the connection was successfull
	if(hCom==INVALID_HANDLE_VALUE)
		MessageBox(hWnd,L"Could not connect to selected COM port",
			L"Com Error",MB_OK|MB_ICONERROR);
	else
	{
		DCB comParams = {0};

		//Get the current configuration
		if (GetCommState(hCom, &comParams))
		{
			//Change serial connection parameters for the arduino board
			comParams.BaudRate=57600;
			comParams.ByteSize=8;
			comParams.StopBits=0;
			comParams.Parity=0;

			//Set the parameters
			if(SetCommState(hCom, &comParams)) // If everything worked we're connected
			{
				connected = true;
				return true;
			}
			else								// Else we aren't, warn and exit
			{
				MessageBox(hWnd,L"Could not connect to selected COM port",
					L"Com Error",MB_OK|MB_ICONERROR);
			}
		}
		CloseHandle(hCom);
	}
	return false;
}
void ComPort::Disconnect()
{
	if(connected)	// If connected, disconnect
	{
		CloseHandle(hCom);
		connected = false;
	}
}
BOOL ComPort::IsConnected()
{
	return connected;
}

DWORD ComPort::ReadData(unsigned char *buffer, UINT nbChars)
{
	if(!connected)
		return 0;

	DWORD bytesRead;
	DWORD errors;
	COMSTAT status;

	ClearCommError(hCom, &errors, &status);

	//if there are not enough characters, return 0
	if(status.cbInQue<nbChars)
		return 0;

	//if there are more than 1 packets, dump all untill the latest
	while(status.cbInQue>= 2*nbChars)
#pragma warning(suppress: 6031)
		ReadFile(hCom, buffer, nbChars, &bytesRead, NULL);

	//read the latest packet and return the number read to confirm
	if(ReadFile(hCom, buffer, nbChars, &bytesRead, NULL) && bytesRead != 0)
		return bytesRead;//number read

	//If nothing has been read, or that an error was detected return 0
	return 0;
}
DWORD ComPort::WriteData(unsigned char *buffer, UINT nbChars)
{
	if(!connected)
		return 0;

	DWORD bytesSent;
	DWORD errors;

	if(!WriteFile(hCom, (void *)buffer, nbChars, &bytesSent, 0))
		ClearCommError(hCom, &errors, NULL);	// If it fails, clear com errors
	else return bytesSent;						// Return the number of bytes sent
	return 0;									// Or return 0 on failure
}

#endif
