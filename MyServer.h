#pragma once

class MyServer
{

private:
	WSADATA mWsaData;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;

public:
	int mMAX_USER_NUM;

	MyServer(void);
	int GetUser(WPARAM wPrm);
	int SetUser(WPARAM wPrm);
	BOOL Init(int* tResult);
	LRESULT Free(void);
	int PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm);
	void ConsoleTitle();
	void HexDump(char* buf, int len, int addr);
};
extern MyServer mSERVER;