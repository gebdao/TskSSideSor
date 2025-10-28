
#include "MainApp.h"

MyServer mSERVER;

MyServer::MyServer(void)
{
}

BOOL MyServer::Init(int* tResult)
{
	int index01 = 0;
	mMAX_USER_NUM = mSERVER_INFO.mServerMaxUserNum;
	srand((unsigned int)time(NULL));
	ZeroMemory(&mWsaData, sizeof(WSADATA));
	if (WSAStartup(MAKEWORD(2, 2), &mWsaData) != 0)
	{
		*tResult = 3;
		return FALSE;
	}
	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		*tResult = 4;
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = htonl(INADDR_ANY);
	mAddress.sin_port = htons(mSERVER_INFO.mServerPort);
	if (::bind(mSocket, (LPSOCKADDR)&mAddress, sizeof(mAddress)) == SOCKET_ERROR)
	{
		*tResult = 5;
		return FALSE;
	}
	if (listen(mSocket, SOMAXCONN) == SOCKET_ERROR)
	{
		*tResult = 6;
		return FALSE;
	}
	if (!SetNonBlock(mSocket))
	{
		*tResult = 43;
		return FALSE;
	}
	if (WSAAsyncSelect(mSocket, mSERVER_INFO.mWindow, WM_NETWORK_MESSAGE_1, FD_ACCEPT) == SOCKET_ERROR)
	{
		*tResult = 7;
		return FALSE;
	}

	mUSER = (MyUser*)GlobalAlloc(GMEM_FIXED, (mMAX_USER_NUM * sizeof(MyUser)));
	if (mUSER == NULL)
	{
		*tResult = 13;
		return FALSE;
	}
	for (index01 = 0; index01 < mMAX_USER_NUM; index01++)
	{
		mUSER[index01].mBUFFER_FOR_SEND = NULL;
		mUSER[index01].mBUFFER_FOR_RECV = NULL;
	}

	for (index01 = 0; index01 < mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].Init(index01, ZONE_MAX_SEND_BUFFER_SIZE, ZONE_MAX_RECV_BUFFER_SIZE))
		{
			*tResult = 14;
			return FALSE;
		}
	}

	if (!mPLAYUSER_COM.Init(mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_1_IP, mSERVER_INFO.mUpperServer_1_Port))
	{
		*tResult = 77;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Player server start", __FUNCTION__);

	if (!mCENTER_COM.Init(mSERVER_INFO.mServerNumber, mSERVER_INFO.mServerPort, mSERVER_INFO.mUpperServer_2_IP, mSERVER_INFO.mUpperServer_2_Port))
	{
		*tResult = 88;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Center server start", __FUNCTION__);

	if (!mRELAY_COM.Init(mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_4_IP, mSERVER_INFO.mUpperServer_4_Port))
	{
		*tResult = 999;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : RELAY server start", __FUNCTION__);
	if (!mEXTRA_COM.Init(mSERVER_INFO.mServerNumber, mSERVER_INFO.mUpperServer_3_IP, mSERVER_INFO.mUpperServer_3_Port))
	{
		*tResult = 999;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : EXTRA server start", __FUNCTION__);
	if (!mGAMELOG.Init(mSERVER_INFO.mUpperServer_5_IP, mSERVER_INFO.mUpperServer_5_Port))
	{
		*tResult = 11;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : GAMELOG server start", __FUNCTION__);
	if (!mCHATLOG.Init(mSERVER_INFO.mUpperServer_5_IP, mSERVER_INFO.mUpperServer_5_Port))
	{
		*tResult = 12;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : ChatLog server start", __FUNCTION__);

	if (!mWORK.Init())
	{
		*tResult = 15;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Work start", __FUNCTION__);
	if (!mTRANSFER.Init())
	{
		*tResult = 16;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Transfer start", __FUNCTION__);
	if (!mGAME.Init())
	{
		*tResult = 17;
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Game start\n", __FUNCTION__);

	mGAME.mCheckActiveBattleLogic = TRUE;

	return TRUE;
}

int MyServer::GetUser(WPARAM wPrm)
{
	int index01;
	for (index01 = 0; index01 < mMAX_USER_NUM; index01++)
	{
		if (mUSER[index01].mCheckConnectState && mUSER[index01].mSocket == (WPARAM)wPrm)
		{
			return index01;
		}
	}
	return -1;
}

int MyServer::SetUser(WPARAM wPrm)
{
	int index01;
	for (index01 = 0; index01 < mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].mCheckConnectState)
		{
			return index01;
		}
	}
	return -1;
}


int MyServer::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int index01;
	SOCKET tSocket;
	BYTE tProtocol;
	int tRandomNumber;
	int tempUserIndex;
	int tAddressLength;
	SOCKADDR_IN	tAddress;
	int tRecvSizeFromUser;
	char tPacketEncryptionValue;
	tSocket = (SOCKET)wPrm;

	switch (WSAGETSELECTEVENT(lPrm))
	{
	case FD_READ:
		tempUserIndex = GetUser(wPrm);
		if (tempUserIndex == -1)
		{
			return -1;
		}
		while (1)
		{
			tRecvSizeFromUser = recv(tSocket, &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mUSER[tempUserIndex].mTotalRecvSize], (ZONE_MAX_RECV_BUFFER_SIZE - mUSER[tempUserIndex].mTotalRecvSize), 0);
			if (tRecvSizeFromUser == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEWOULDBLOCK)
				{
					return 0;
				}
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			}
			for (index01 = mUSER[tempUserIndex].mTotalRecvSize; index01 < (mUSER[tempUserIndex].mTotalRecvSize + tRecvSizeFromUser); index01++)
			{
				mUSER[tempUserIndex].mBUFFER_FOR_RECV[index01] ^= mUSER[tempUserIndex].mPacketEncryptionValue[0];
			}
			mUSER[tempUserIndex].mTotalRecvSize += tRecvSizeFromUser;
			break;
		}
		while (TRUE)
		{
			if (mUSER[tempUserIndex].mTotalRecvSize < 9)
			{
				return -1;
			}
			tProtocol = (BYTE)mUSER[tempUserIndex].mBUFFER_FOR_RECV[8];
			if (W_FUNCTION[tProtocol].PROC == NULL)
			{
				//__LogMgr()->Log("tProtocol[%d], Size[%d], Zone[%d]", tProtocol, tRecvSizeFromUser, mSERVER_INFO.mServerNumber);
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			}
			if (mUSER[tempUserIndex].mTotalRecvSize < mWORK.mWorkerPacketSize[tProtocol])
			{
				//mLog("Size Incorrect --> tProtocol[%d]", tProtocol);
				return -1;
			}

			tPacketEncryptionValue = mUSER[tempUserIndex].mBUFFER_FOR_RECV[7];
			if (tPacketEncryptionValue != mUSER[tempUserIndex].mPacketEncryptionValue[1])
			{
				if (mUSER[tempUserIndex].mCheckValidState)
				{
				}
				mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return 0;
			}
			mUSER[tempUserIndex].mPacketEncryptionValue[1]++;

			W_FUNCTION[tProtocol].PROC(tempUserIndex);
			if (mUSER[tempUserIndex].mCheckConnectState)
			{
				MoveMemory(&mUSER[tempUserIndex].mBUFFER_FOR_RECV[0], &mUSER[tempUserIndex].mBUFFER_FOR_RECV[mWORK.mWorkerPacketSize[tProtocol]], (mUSER[tempUserIndex].mTotalRecvSize - mWORK.mWorkerPacketSize[tProtocol]));
				mUSER[tempUserIndex].mTotalRecvSize -= mWORK.mWorkerPacketSize[tProtocol];
			}
			if (mUSER[tempUserIndex].mTotalRecvSize == 0)
			{
				break;
			}
		}
		return tRecvSizeFromUser;

	case FD_ACCEPT:
		tAddressLength = sizeof(tAddress);
		tSocket = accept(mSocket, (LPSOCKADDR)&tAddress, &tAddressLength);
		if (tSocket == INVALID_SOCKET)
		{
			return 0;
		}
		tempUserIndex = SetUser(wPrm);
		if (tempUserIndex == -1)
		{
			closesocket(tSocket);
			return 0;
		}
		/*if (!SetNoDelay(tSocket))
		{
			closesocket(tSocket);
			return 0;
		}
		if (!SetNonBlock(tSocket))
		{
			closesocket(tSocket);
			return 0;
		}*/
		if (!SetSocketSendBuffer(tSocket, 100000000))
		{
			closesocket(tSocket);
			return 0;
		}
		if (WSAAsyncSelect(tSocket, hWnd, WM_NETWORK_MESSAGE_1, (FD_READ | FD_WRITE | FD_CLOSE)) == SOCKET_ERROR)
		{
			closesocket(tSocket);
			return 0;
		}
		mUSER[tempUserIndex].mCheckConnectState = TRUE;
		mUSER[tempUserIndex].mCheckValidState = FALSE;
		mUSER[tempUserIndex].mConnectTime = GetTickCount64();
		mUSER[tempUserIndex].mSocket = tSocket;
		sprintf(mUSER[tempUserIndex].mIP, "%d.%d.%d.%d", tAddress.sin_addr.S_un.S_un_b.s_b1, tAddress.sin_addr.S_un.S_un_b.s_b2, tAddress.sin_addr.S_un.S_un_b.s_b3, tAddress.sin_addr.S_un.S_un_b.s_b4);
		tRandomNumber = (rand() % 1001) * (rand() % 1001);
		CopyMemory(&mUSER[tempUserIndex].mPacketEncryptionValue[0], &tRandomNumber, 1);
		CopyMemory(&mUSER[tempUserIndex].mPacketEncryptionValue[1], &tRandomNumber, 1);
		mUSER[tempUserIndex].mPacketEncryptionValue[1] += 127;
		mUSER[tempUserIndex].mTotalSendSize = 0;
		mUSER[tempUserIndex].mTotalRecvSize = 0;
		mUSER[tempUserIndex].mUniqueNumber = 0;
		mUSER[tempUserIndex].mCheckTempRegister = FALSE;
		memset(&mUSER[tempUserIndex].mAvatarInfo, 0x00, sizeof(AVATAR_INFO));
		memset(&mAVATAR_OBJECT[tempUserIndex].mDATA, 0x00, sizeof(OBJECT_FOR_AVATAR));
		mUSER[tempUserIndex].mIsValidCashItemInfo = false;
		mTRANSFER.B_CONNECT_OK(tRandomNumber);
		mUSER[tempUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return 0;
	case FD_CLOSE:
		tempUserIndex = GetUser(wPrm);
		if (tempUserIndex == -1)
		{
			return 0;
		}
		mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return 0;
	}
}

LRESULT MyServer::Free()
{
	int tempUserIndex;
	for (tempUserIndex = 0; tempUserIndex < mSERVER.mMAX_USER_NUM; tempUserIndex++)
	{
		if (mUSER[tempUserIndex].mCheckValidState)
		{
			mUSER[tempUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
	}
	GlobalFree(mUSER);
	closesocket(mSocket);
	WSACleanup();
	PostQuitMessage(0);
	return 0;
}

void MyServer::ConsoleTitle()
{
	char buffer[1024];
	int zone = mSERVER_INFO.mServerNumber;

	sprintf(buffer, "Zone #%d running on Port: %d", zone, mSERVER_INFO.mServerPort);
	SetConsoleTitleA(buffer);
}



void MyServer::HexDump(char* buf, int len, int addr)
{
	int i, j, k;
	char binstr[80];

	for (i = 0; i < len; i++) {
		if (0 == (i % 16)) {
			sprintf(binstr, "%08x -", i + addr);
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
		}
		else if (15 == (i % 16)) {
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
			sprintf(binstr, "%s  ", binstr);
			for (j = i - 15; j <= i; j++) {
				sprintf(binstr, "%s%c", binstr, ('!' < buf[j] && buf[j] <= '~') ? buf[j] : '.');
			}
			printf("%s\n", binstr);
		}
		else {
			sprintf(binstr, "%s %02x", binstr, (unsigned char)buf[i]);
		}
	}
	if (0 != (i % 16)) {
		k = 16 - (i % 16);
		for (j = 0; j < k; j++) {
			sprintf(binstr, "%s   ", binstr);
		}
		sprintf(binstr, "%s  ", binstr);
		k = 16 - k;
		for (j = i - k; j < i; j++) {
			sprintf(binstr, "%s%c", binstr, ('!' < buf[j] && buf[j] <= '~') ? buf[j] : '.');
		}
		printf("%s\n", binstr);
	}
}