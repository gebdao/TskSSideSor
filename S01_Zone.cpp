#include "MainApp.h"

SERVER_INFO mSERVER_INFO;

BOOL WINAPI QuitOnExit(DWORD fdwCtrlType)
{
	switch (fdwCtrlType)
	{
	case CTRL_CLOSE_EVENT:
		SendMessageA(mSERVER_INFO.mWindow, WM_DESTROY, 0, 0);
		return TRUE;
	}
}

LRESULT GameLogic()
{
	mSERVER_INFO.mBaseTickCountForLogic = GetTickCount();
	if ((mSERVER_INFO.mBaseTickCountForLogic - mSERVER_INFO.mPostTickCountForLogic) > 500)
	{
		mSERVER_INFO.mPostTickCountForLogic = mSERVER_INFO.mBaseTickCountForLogic;
		mGAME.Logic(0.5f);
	}
	return 0;
}

LRESULT SocketFree()
{
	int index01;
	DWORD tPresentTime;

	tPresentTime = GetTickCount();
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].mCheckConnectState)
		{
			continue;
		}
		if ((tPresentTime - mUSER[index01].mConnectTime) > 2000)
		{
			if (strcmp(mUSER[index01].uID, "") == 0)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
				continue;
			}
		}
	}
	return 0;
}

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_NETWORK_MESSAGE_1:
		mSERVER.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return 0;
	case WM_NETWORK_MESSAGE_2:
		mCENTER_COM.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return 0;
	case WM_NETWORK_MESSAGE_3:
		mRELAY_COM.PROCESS_FOR_NETWORK(hWnd, wParam, lParam);
		return 0;
	case WM_TIMER:
		GameLogic(); 
		SocketFree();
		return 0;
	case WM_DESTROY:
		mSERVER.Free();
		return 0;
	}
	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

int main(int argc, char* argv[])
{
	system("color B");
	SetUnhandledExceptionFilter(unhandledExceptionHandler);
	SetConsoleCtrlHandler(QuitOnExit, TRUE);

	// Configs
	mSERVER_INFO.mServerNumber = atoi(argv[1]);
	mSERVER_INFO.mServerPort = 13000 + atoi(argv[1]);
	mSERVER_INFO.mServerMaxUserNum = MAX_SERVER_USER_NUM;
	mSERVER_INFO.mMaxSendBufferSize = ZONE_MAX_SEND_BUFFER_SIZE;
	mSERVER_INFO.mMaxRecvBufferSize = ZONE_MAX_RECV_BUFFER_SIZE;
	if ( !mSERVER_INFO.ReadServerRate() )
	{
		__LogMgr()->Log("Error::[Read server Rate]");
		Sleep(2000);
		return 0;
	}
	mSERVER_INFO.wCls = { sizeof(WNDCLASSEX), 0, WindowProc, 0, 0, NULL, 0, 0, 0, 0, mSERVER_INFO.mServerName, 0 };
	RegisterClassEx(&mSERVER_INFO.wCls);
	mSERVER_INFO.mWindow = CreateWindowEx(0, mSERVER_INFO.mServerName, mSERVER_INFO.mServerName, WS_DISABLED, 0, 0, 0, 0, HWND_DESKTOP, NULL, NULL, NULL);
	mSERVER.ConsoleTitle();
	if (mSERVER_INFO.mWindow == NULL)
	{
		__LogMgr()->Log("Error::[CreateWindowEx()]");
		Sleep(2000);
		return 0;
	}
	if (!mSERVER.Init(&mSERVER_INFO.tResult))
	{
		__LogMgr()->Log("[Error::mSERVER.Init()]-(%d), ZoneNumber[%d]", mSERVER_INFO.tResult, mSERVER_INFO.mServerNumber);
		Sleep(2000);
		return 0;
	}
	__LogMgr()->Log("[MyServer::Init] --> Zone Running! Map #%d", mSERVER_INFO.mServerNumber);

	// Logic Init
	mSERVER_INFO.mBaseTickCountForLogic = GetTickCount();
	mSERVER_INFO.mPostTickCountForLogic = mSERVER_INFO.mBaseTickCountForLogic;
	if (!SetTimer(mSERVER_INFO.mWindow, 1, (UINT)1, NULL))
	{
		__LogMgr()->Log("Error::[SetTimer()]", mSERVER_INFO.tResult, mSERVER_INFO.mServerNumber);
		Sleep(2000);
		return 0;
	}
	while (::GetMessage(&mSERVER_INFO.msg, NULL, 0, 0))
	{
		TranslateMessage(&mSERVER_INFO.msg);
		DispatchMessage(&mSERVER_INFO.msg);
	}
}

BOOL SERVER_INFO::ReadServerRate(void)
{
	char TempString[100];

	//Server Name
	GetPrivateProfileStringA("SERVERINFO", "ServerName", "", mSERVER_INFO.mServerName, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mServerName, "") == 0)
	{
		__LogMgr()->Log("Server Name Error");
		return FALSE;
	}

	// World Number
	GetPrivateProfileStringA("SERVERINFO", "WorldNumber", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mWorldNumber = atoi(TempString);
	if (mSERVER_INFO.mWorldNumber < 0 || mSERVER_INFO.mWorldNumber > 999)
	{
		__LogMgr()->Log("World Number Error");
		return FALSE;
	}

	// mUpperServer_1_IP
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_1_IP", "", mSERVER_INFO.mUpperServer_1_IP, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mUpperServer_1_IP, "") == 0)
	{
		__LogMgr()->Log("mUpperServer_1_IP Error");
		return FALSE;
	}

	// mUpperServer_1_Port
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_1_Port", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mUpperServer_1_Port = atoi(TempString);
	if (mSERVER_INFO.mUpperServer_1_Port < 1 || mSERVER_INFO.mUpperServer_1_Port > 65535)
	{
		__LogMgr()->Log("mUpperServer_1_Port Error");
		return FALSE;
	}

	// mUpperServer_2_IP
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_2_IP", "", mSERVER_INFO.mUpperServer_2_IP, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mUpperServer_2_IP, "") == 0)
	{
		__LogMgr()->Log("mUpperServer_2_IP Error");
		return FALSE;
	}

	// mUpperServer_2_Port
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_2_Port", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mUpperServer_2_Port = atoi(TempString);
	if (mSERVER_INFO.mUpperServer_2_Port < 1 || mSERVER_INFO.mUpperServer_2_Port > 65535)
	{
		__LogMgr()->Log("mUpperServer_2_Port Error");
		return FALSE;
	}

	// mUpperServer_3_IP
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_3_IP", "", mSERVER_INFO.mUpperServer_3_IP, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mUpperServer_3_IP, "") == 0)
	{
		__LogMgr()->Log("mUpperServer_3_IP Error");
		return FALSE;
	}

	// mUpperServer_3_Port
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_3_Port", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mUpperServer_3_Port = atoi(TempString);
	if (mSERVER_INFO.mUpperServer_3_Port < 1 || mSERVER_INFO.mUpperServer_3_Port > 65535)
	{
		__LogMgr()->Log("mUpperServer_3_Port Error");
		return FALSE;
	}

	// mUpperServer_4_IP
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_4_IP", "", mSERVER_INFO.mUpperServer_4_IP, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mUpperServer_4_IP, "") == 0)
	{
		__LogMgr()->Log("mUpperServer_4_IP Error");
		return FALSE;
	}

	// mUpperServer_4_Port
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_4_Port", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mUpperServer_4_Port = atoi(TempString);
	if (mSERVER_INFO.mUpperServer_4_Port < 1 || mSERVER_INFO.mUpperServer_4_Port > 65535)
	{
		__LogMgr()->Log("mUpperServer_4_Port Error");
		return FALSE;
	}

	// mUpperServer_4_IP
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_5_IP", "", mSERVER_INFO.mUpperServer_5_IP, 100, "CONFIG\\ServerInfo.ini");
	if (strcmp(mSERVER_INFO.mUpperServer_5_IP, "") == 0)
	{
		__LogMgr()->Log("mUpperServer_5_IP Error");
		return FALSE;
	}

	// mUpperServer_4_Port
	GetPrivateProfileStringA("SERVERINFO", "mUpperServer_5_Port", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.mUpperServer_5_Port = atoi(TempString);
	if (mSERVER_INFO.mUpperServer_5_Port < 1 || mSERVER_INFO.mUpperServer_5_Port > 65535)
	{
		__LogMgr()->Log("mUpperServer_5_Port Error");
		return FALSE;
	}

	// Exp Rate
	GetPrivateProfileStringA("SERVERINFO", "ServerExp", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.WORLD_EXP = atof(TempString);
	if (mSERVER_INFO.WORLD_EXP == 0)
	{
		__LogMgr()->Log("ServerExp is 0 Error");
		return FALSE;
	}

	// Drop Rate
	GetPrivateProfileStringA("SERVERINFO", "ServerDropRate", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.WORLD_ITEM_DROP = atof(TempString);
	if (mSERVER_INFO.WORLD_ITEM_DROP == 0)
	{
		__LogMgr()->Log("Drop Rate is 0 Error");
		return FALSE;
	}

	// Pet Exp
	GetPrivateProfileStringA("SERVERINFO", "ServerPetExp", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.WORLD_PATEXP = atof(TempString);
	if (mSERVER_INFO.WORLD_PATEXP == 0)
	{
		__LogMgr()->Log("Pet Exp is 0 Error");
		return FALSE;
	}

	// Kill Other Tribe Add Value / CP +x
	GetPrivateProfileStringA("SERVERINFO", "CP", "", TempString, 100, "CONFIG\\ServerInfo.ini");
	mSERVER_INFO.WORLD_KTAV = atoi(TempString);
	if (mSERVER_INFO.WORLD_KTAV < 0)
	{
		__LogMgr()->Log("CP Multiplier Non Real Number Error");
		return FALSE;
	}
}