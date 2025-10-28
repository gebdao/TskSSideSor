#pragma once

#include <iostream>
#include <string>
#include <stdio.h>
#include <Winsock2.h>
#include <fstream>
#include <sstream>
#include <tchar.h>
#include <time.h>
#include <map>
#include <set>
#include <random>
#include <thread>
#include <future>
#include "WS2tcpip.h"
#include "WinInet.h"

#pragma comment(lib,"WS2_32")

#include "Macros.h"
#include "..\include\TimeLog.h"
#include "..\include\struct.h"
#include "MyServer.h"
#include "MyUser.h"
#include "MyWork.h"
#include "MyTransfer.h"
#include "MyGame.h"
#include "MyUpperCom.h"
#include "MySummonSystem.h"
#include "MyGameSystem.h"
#include "MyWorld.h"


// Server Definitions
//#define WM_USER_NEW                                                 10
//#define WM_NETWORK_MESSAGE_1										WM_USER_NEW + 1
//#define WM_NETWORK_MESSAGE_2										WM_USER_NEW + 2
//#define WM_NETWORK_MESSAGE_3										WM_USER_NEW + 3
//#define WM_TIMER_NEW                                                WM_USER_NEW + 10
//#define ID_TIMER                                                    0

#define WM_NETWORK_MESSAGE_1										WM_USER + 1
#define WM_NETWORK_MESSAGE_2										WM_USER + 2
#define WM_NETWORK_MESSAGE_3										WM_USER + 3


extern BOOL mCheckLogicFlag;

class SERVER_INFO
{
public:
	DWORD mBaseTickCountForLogic;
	DWORD mPostTickCountForLogic;
	DWORD mMaxSendBufferSize;
	DWORD mMaxRecvBufferSize;
	HWND mWindow;
	WNDCLASSEX wCls;
	int tResult;
	MSG msg;


	char mServerName[100];
	int mServerPort;
	int mServerMaxUserNum;
	int mServerNumber;
	int mWorldNumber;
	char mUpperServer_1_IP[16];
	int mUpperServer_1_Port;
	char mUpperServer_2_IP[16];
	int mUpperServer_2_Port;
	char mUpperServer_3_IP[16];
	int mUpperServer_3_Port;
	char mUpperServer_4_IP[16];
	int mUpperServer_4_Port;
	char mUpperServer_5_IP[16];
	int mUpperServer_5_Port;

	float WORLD_EXP;
	float WORLD_ITEM_DROP;
	int  WORLD_KTAV;
	float WORLD_PATEXP;



	BOOL ReadServerRate();
};
extern SERVER_INFO mSERVER_INFO;

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
