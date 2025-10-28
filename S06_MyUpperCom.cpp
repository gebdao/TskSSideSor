#include "MainApp.h"

MyPlayUserCom mPLAYUSER_COM;

MyPlayUserCom::MyPlayUserCom(void)
{

}
//CONNECT
BOOL MyPlayUserCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		Sleep(1);
		return FALSE;
	}
	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	tSendData[0] = P_ZONE_FOR_PLAYUSER_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_PLAYUSER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			closesocket(mSocket);
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tOKRecvCheck = recv(mSocket, &tOKDataCheck, 1, 0);
	if (tOKRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	mCheckConnectState = TRUE;

	return TRUE;
}

//SEND
BOOL MyPlayUserCom::Send(void)
{
	int nResult = 0;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;

	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}

	return TRUE;
}

//RECV
BOOL MyPlayUserCom::Recv(void)
{
	int nCount = 0;
	int nResult = 0;
	int ret_val = 0;
	int tRecvValue01;
	int tRecvValue02;
	int chk_flag = 0;
	int chk_result = 0;

	if (mRecvDataSize > 0)
	{
		tRecvValue01 = 0;
		while (TRUE)
		{
			tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
			if (tRecvValue02 == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEINTR)
				{
					continue;
				}
				Close();
				return FALSE;
			}
			tRecvValue01 += tRecvValue02;
			if (tRecvValue01 == mRecvDataSize)
			{
				break;
			}
		}
	}

	return TRUE;
}

//CLOSE
void MyPlayUserCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

//INIT
BOOL MyPlayUserCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;
	InitializeCriticalSection(&m_lock);

	if (!Connect())
	{
		return FALSE;
	}

	return TRUE;
}
//FREE
void MyPlayUserCom::Free(void)
{
	Close();
	DeleteCriticalSection(&m_lock);
}

//PROCESS_FOR_NETWORK
BOOL MyPlayUserCom::ProcessForNetwork(void)
{
	if (!Connect())
	{
		return FALSE;
	}
	if (!Send())
	{
		return FALSE;
	}
	if (!Recv())
	{
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_PLAYUSER_SEND
void MyPlayUserCom::U_ZONE_OK_FOR_PLAYUSER_SEND(void)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_ZONE_OK_FOR_PLAYUSER_SEND;
		mSendDataSize = S_ZONE_OK_FOR_PLAYUSER_SEND;
		mRecvDataSize = 0;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_0_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_0_SEND(char tID[MAX_USER_ID_LENGTH])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_0_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_0_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_0_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_PlayUserIndex, &mRecvData[5], 4);
	LeaveCriticalSection(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_1_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_1_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_1_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tLogoutInfo[0], 24);
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_1_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_1_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_UserSort, &mRecvData[5], 4);
	CopyMemory(&mRecv_AvatarInfo, &mRecvData[34], sizeof(AVATAR_INFO));
	CopyMemory(mRecv_EffectValue, &mRecvData[(34 + sizeof(AVATAR_INFO))], (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	CopyMemory(&mRecv_CheckFirstZone, &mRecvData[(34 + sizeof(AVATAR_INFO) + MAX_AVATAR_EFFECT_SORT_NUM * 8)], 4);
	CopyMemory(&mRecv_AuthInfo, &mRecvData[(38 + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], sizeof(AUTH_INFO));
	LeaveCriticalSection(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_2_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_2_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO* tAuthInfo)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_2_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, sizeof(AVATAR_INFO));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_2_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_2_RECV;
		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}

//U_REGISTER_USER_FOR_ZONE_3_SEND
void MyPlayUserCom::U_REGISTER_USER_FOR_ZONE_3_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO* tAuthInfo)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_USER_FOR_ZONE_3_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, sizeof(AVATAR_INFO));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO) + (MAX_AVATAR_EFFECT_SORT_NUM * 8))], tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_REGISTER_USER_FOR_ZONE_3_SEND;
		mRecvDataSize = S_REGISTER_USER_FOR_ZONE_3_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}

//U_UNREGISTER_USER_FOR_ZONE_SEND
void MyPlayUserCom::U_UNREGISTER_USER_FOR_ZONE_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_UNREGISTER_USER_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], tAvatarInfo, sizeof(AVATAR_INFO));
		CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH + sizeof(AVATAR_INFO))], tAuthInfo, sizeof(AUTH_INFO));
		mSendDataSize = S_UNREGISTER_USER_FOR_ZONE_SEND;
		mRecvDataSize = S_UNREGISTER_USER_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_FIND_AVATAR_FOR_ZONE_SEND
void MyPlayUserCom::U_FIND_AVATAR_FOR_ZONE_SEND(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_FIND_AVATAR_FOR_ZONE_SEND;
		CopyMemory(&mSendData[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mSendDataSize = S_FIND_AVATAR_FOR_ZONE_SEND;
		mRecvDataSize = S_FIND_AVATAR_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_ZoneNumber, &mRecvData[1], 4);
	CopyMemory(&mRecv_Tribe, &mRecvData[5], 4);
	LeaveCriticalSection(&m_lock);
}

//U_TRIBE_BANK_INFO_SAVE_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_SAVE_SEND(int tMoney[4])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_SAVE_SEND;
		CopyMemory(&mSendData[1], &tMoney[0], 16);
		mSendDataSize = S_TRIBE_BANK_INFO_SAVE_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_SAVE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_TRIBE_BANK_INFO_VIEW_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_VIEW_SEND(int tTribe)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_VIEW_SEND;
		CopyMemory(&mSendData[1], &tTribe, 4);
		mSendDataSize = S_TRIBE_BANK_INFO_VIEW_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_VIEW_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_TribeBankInfo[0], &mRecvData[5], (MAX_TRIBE_BANK_SLOT_NUM * 4));
	LeaveCriticalSection(&m_lock);
}

//U_TRIBE_BANK_INFO_LOAD_SEND
void MyPlayUserCom::U_TRIBE_BANK_INFO_LOAD_SEND(int tTribe, int tTribeBankInfoIndex, int tInventoryMoney)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_TRIBE_BANK_INFO_LOAD_SEND;
		CopyMemory(&mSendData[1], &tTribe, 4);
		CopyMemory(&mSendData[5], &tTribeBankInfoIndex, 4);
		CopyMemory(&mSendData[9], &tInventoryMoney, 4);
		mSendDataSize = S_TRIBE_BANK_INFO_LOAD_SEND;
		mRecvDataSize = S_TRIBE_BANK_INFO_LOAD_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_Money, &mRecvData[5], 4);
	LeaveCriticalSection(&m_lock);
}

//U_BLOCK_USER_FOR_ZONE_1_SEND
void MyPlayUserCom::U_BLOCK_USER_FOR_ZONE_1_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH])
{
	EnterCriticalSection(&m_lock);
	while (TRUE) 
	{
		memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_BLOCK_USER_FOR_ZONE_1_SEND;
		CopyMemory(&mSendData[1], &tPlayUserIndex, 4);
		CopyMemory(&mSendData[5], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_BLOCK_USER_FOR_ZONE_1_SEND;
		mRecvDataSize = S_BLOCK_USER_FOR_ZONE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_CHECK_KILL_OTHER_TRIBE_SEND
void MyPlayUserCom::U_CHECK_KILL_OTHER_TRIBE_SEND(char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_CHECK_KILL_OTHER_TRIBE_SEND;
		CopyMemory(&mSendData[1], &tAvatarName1[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[(1 + MAX_AVATAR_NAME_LENGTH)], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		mSendDataSize = S_CHECK_KILL_OTHER_TRIBE_SEND;
		mRecvDataSize = S_CHECK_KILL_OTHER_TRIBE_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}
void MyPlayUserCom::U_REGISTER_PROXY_SHOP_INFO_SEND(char* tID, char* tAvatarName, int tSort, PROXYSHOP_INFO* tProxyInfo)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_REGISTER_PROXY_SHOP_INFO_SEND;
		CopyMemory( &mSendData[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH );
		CopyMemory( &mSendData[1 + MAX_AVATAR_NAME_LENGTH], &tID[0], MAX_USER_ID_LENGTH );
		CopyMemory( &mSendData[1 + MAX_AVATAR_NAME_LENGTH + MAX_USER_ID_LENGTH], &tSort, 4 );
		CopyMemory( &mSendData[1 + MAX_AVATAR_NAME_LENGTH + MAX_USER_ID_LENGTH + 4], tProxyInfo, sizeof(PROXYSHOP_INFO) );
		mSendDataSize = S_REGISTER_PROXY_SHOP_INFO_SEND;
		mRecvDataSize = S_REGISTER_PROXY_SHOP_INFO_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}
void MyPlayUserCom::U_DEMAND_PROXY_SHOP_INFO_SEND(char* tID, char* tAvatarName)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_DEMAND_PROXY_SHOP_INFO_SEND;
		CopyMemory(&mSendData[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[1 + MAX_AVATAR_NAME_LENGTH], &tID[0], MAX_USER_ID_LENGTH);
		mSendDataSize = S_DEMAND_PROXY_SHOP_INFO_SEND;
		mRecvDataSize = S_DEMAND_PROXY_SHOP_INFO_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_Proxy, &mRecvData[5], sizeof(PROXYSHOP_INFO));
	LeaveCriticalSection(&m_lock);
}
void MyPlayUserCom::U_ADD_USER_CASH_SEND(char* tID, int tAmount)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_ADD_USER_CASH_SEND;
		CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
		CopyMemory(&mSendData[1 + MAX_USER_ID_LENGTH], &tAmount, 4);

		mSendDataSize = S_ADD_USER_CASH_SEND;
		mRecvDataSize = S_ADD_USER_CASH_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}
void MyPlayUserCom::U_DEMAND_HERO_RANK_INFO_SEND(int tSort)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_DEMAND_HERO_RANK_INFO_SEND;
		CopyMemory(&mSendData[1], &tSort, 4);

		mSendDataSize = S_DEMAND_HERO_RANK_INFO_SEND;
		mRecvDataSize = S_DEMAND_HERO_RANK_INFO_RECV;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_HeroRank, &mRecvData[5], sizeof(HERO_RANKING_INFO));
	CopyMemory(&mRecv_HeroRankClaimState, &mRecvData[5 + sizeof(HERO_RANKING_INFO)], 160);
	LeaveCriticalSection(&m_lock);
}
void MyPlayUserCom::U_CHANGE_HERO_RANK_INFO_SEND(int tSort, char* tAvatarName, int tPoints, int tTribe)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		::memset(mSendData, 0, MAX_SEND_DATA_SIZE);
		mSendData[0] = P_CHANGE_HERO_RANK_INFO_SEND;
		CopyMemory(&mSendData[1], &tSort, 4);
		CopyMemory(&mSendData[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mSendData[5 + MAX_AVATAR_NAME_LENGTH], &tPoints, 4);
		CopyMemory(&mSendData[5 + MAX_AVATAR_NAME_LENGTH + 4], &tTribe, 4);

		mSendDataSize = S_CHANGE_HERO_RANK_INFO_SEND;
		mRecvDataSize = 5;

		if (ProcessForNetwork())
		{
			break;
		}
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	LeaveCriticalSection(&m_lock);
}




MyCenterCom mCENTER_COM;
MyCenterCom::MyCenterCom(void)
{
	mIsUpdateCashItemInfo = false;
}
//CONNECT
BOOL MyCenterCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tRecvDataSize;
	int tRecvValue01;
	int tRecvValue02;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		Close();
		return FALSE;
	}
	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		Close();
		return FALSE;
	}
	mRecvDataSize = 0;
	memset(mRecvData, 0, MAX_RECV_DATA_SIZE);

	tSendData[0] = P_ZONE_FOR_CENTER_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	CopyMemory(&tSendData[5], &mZonePort, 4);
	tSendDataSize = S_ZONE_FOR_CENTER_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tRecvDataSize = S_ZONE_FOR_CENTER_RECV + S_TOTAL_ZONE_CONNECTION_INFO + S_WORLD_INFO + 1 + sizeof(TOWER_INFO);
	tRecvValue01 = 0;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], tRecvDataSize, 0);
		if (tRecvValue02 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 >= tRecvDataSize)
		{
			break;
		}
	}
	CopyMemory(&mGAME.mZoneConnectionInfo, &mRecvData[2], sizeof(ZONE_CONNECTION_INFO));
	CopyMemory(&mGAME.mWorldInfo, &mRecvData[(3 + sizeof(ZONE_CONNECTION_INFO))], sizeof(WORLD_INFO));
	CopyMemory(&mGAME.mTribeInfo, &mRecvData[(3 + sizeof(ZONE_CONNECTION_INFO) + sizeof(WORLD_INFO))], sizeof(TRIBE_INFO));
	CopyMemory(&mGAME.mTowerInfo, &mRecvData[(4 + sizeof(ZONE_CONNECTION_INFO) + sizeof(WORLD_INFO) + sizeof(TRIBE_INFO))], sizeof(TOWER_INFO));

	// Disable Ally on some maps
	if (mSERVER_INFO.mServerNumber == 295 ||mSERVER_INFO.mServerNumber == 296 ||mSERVER_INFO.mServerNumber == 194) 
	{
		mGAME.mWorldInfo.mAllianceState[0][0] = -1;
		mGAME.mWorldInfo.mAllianceState[0][1] = -1;
		mGAME.mWorldInfo.mAllianceState[1][0] = -1;
		mGAME.mWorldInfo.mAllianceState[1][1] = -1;
	}

	memmove(mRecvData, &mRecvData[tRecvDataSize], (tRecvValue01 - tRecvDataSize));
	mRecvDataSize = tRecvValue01 - tRecvDataSize;
	memmove(mRecvData, &mRecvData[0], tRecvValue01);
	mRecvDataSize = 0;
	mCheckConnectState = TRUE;

	if ( WSAAsyncSelect(mSocket, mSERVER_INFO.mWindow, WM_NETWORK_MESSAGE_2, FD_READ | FD_CLOSE) == SOCKET_ERROR )
	{
		return FALSE;
	}

	return TRUE;
}

//SEND
BOOL MyCenterCom::Send(void)
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}

//CLOSE
void MyCenterCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

//INIT
BOOL MyCenterCom::Init(int tZoneNumber, int tZonePort, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1)
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	mZonePort = tZonePort;
	strcpy(mIP, tIP);
	mPort = tPort;
	InitializeCriticalSection(&m_lock);

	return Connect();
}

//FREE
void MyCenterCom::Free(void)
{
	Close();
	DeleteCriticalSection(&m_lock);
}

//PROCESS_FOR_NETWORK
int MyCenterCom::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int tRecvSize;
	BYTE tProtocol;
	int tTotalPacketSize;

	switch (WSAGETSELECTEVENT(lPrm))
	{
	case FD_READ:
		tRecvSize = recv(mSocket, &mRecvData[mRecvDataSize], (MAX_RECV_DATA_SIZE - mRecvDataSize), 0);
		if (tRecvSize == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				return 0;
			}
			Close();
			return 0;
		}
		mRecvDataSize += tRecvSize;
		while (TRUE)
		{
			if (mRecvDataSize < 1)
			{
				return tRecvSize;
			}
			tProtocol = (BYTE)mRecvData[0];
			switch (tProtocol)
			{
			case P_WORLD_INFO:
				tTotalPacketSize = S_WORLD_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_WORLD_INFO();
				break;
			case P_ZONE_CONNECTION_INFO:
				tTotalPacketSize = S_ZONE_CONNECTION_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_ZONE_CONNECTION_INFO();
				break;
			case P_BROADCAST_INFO:
				tTotalPacketSize = S_BROADCAST_INFO;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_BROADCAST_INFO();
				break;
			case P_NOTICE:
				tTotalPacketSize = S_NOTICE;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_NOTICE();
				break;
			case P_UPDATE_CASH_ITEM_INFO_FOR_ZONE:
				tTotalPacketSize = S_UPDATE_CASH_ITEM_INFO_FOR_ZONE;
				if (mRecvDataSize < tTotalPacketSize) 
				{
					return tRecvSize;
				}
				W_UPDATE_CASH_ITEM_INFO_FOR_ZONE();
				break;
			default:
				Close();
				return 0;
			}
			if (mCheckConnectState)
			{
				memmove(mRecvData, mRecvData + tTotalPacketSize, (mRecvDataSize - tTotalPacketSize));
				mRecvDataSize -= tTotalPacketSize;
			}
		}
		return tRecvSize;
	case FD_CLOSE:
		Close();
		return 0;
	}
	return 0;
}

//W_WORLD_INFO
void MyCenterCom::W_WORLD_INFO(void)
{
	char* tPacket = &mRecvData[0];

	CopyMemory(&mGAME.mWorldInfo, &tPacket[1], sizeof(WORLD_INFO));
	CopyMemory(&mGAME.mTribeInfo, &tPacket[(1 + sizeof(WORLD_INFO))], sizeof(TRIBE_INFO));

	mTRANSFER.B_BROADCAST_WORLD_INFO2(&mGAME.mWorldInfo, &mGAME.mTribeInfo);
	mUTIL.Broadcast(FALSE, NULL, 0, false, 2);
}

//W_ZONE_CONNECTION_INFO
void MyCenterCom::W_ZONE_CONNECTION_INFO(void)
{
	char* tPacket = &mRecvData[0];

	int tZoneNumber;
	char tIP[16];
	int tPort;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);
	CopyMemory(&tIP[0], &tPacket[5], 16);
	CopyMemory(&tPort, &tPacket[21], 4);

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER))
	{
		return;
	}
	strcpy(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], tIP);
	mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)] = tPort;
}

//W_BROADCAST_INFO
void MyCenterCom::W_BROADCAST_INFO(void)
{
	char* tPacket = &mRecvData[0];

	int tInfoSort;
	BYTE tInfoData[MAX_BROADCAST_INFO_SIZE];
	CopyMemory(&tInfoSort, &tPacket[1], 4);
	CopyMemory(&tInfoData[0], &tPacket[5], MAX_BROADCAST_INFO_SIZE);

	mGAME.ProcessForBroadcastInfo(tInfoSort, &tInfoData[0]);
}
//W_NOTICE
void MyCenterCom::W_NOTICE(void)
{
	char* tPacket = &mRecvData[0];

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int tTribe;
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tTribe, &tPacket[(1 + MAX_CHAT_CONTENT_LENGTH)], 4);

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	tSort = 101;
	CopyMemory(&tData[0], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[MAX_CHAT_CONTENT_LENGTH], &tTribe, 4);
	mWORK.ProcessForRelay(tSort, &tData[0], 1);
}
void MyCenterCom::W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(int tResult)
{
	EnterCriticalSection(&m_lock);
	mSendData[0] = P_UPDATE_CASH_ITEM_INFO_FOR_CENTER;
	CopyMemory(&mSendData[1], &tResult, 4);
	mSendDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_CENTER;

	while (1) 
	{
		if (ProcessForSend()) 
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

void MyCenterCom::W_UPDATE_CASH_ITEM_INFO_FOR_ZONE()
{
	char* tPacket = &mRecvData[0];

	SetUpdateCashItemInfo(true);
}
//PROCESS_FOR_SEND
BOOL MyCenterCom::ProcessForSend(void)
{
	if (!mCheckConnectState)
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	if (!Send())
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_CENTER_SEND
void MyCenterCom::U_ZONE_OK_FOR_CENTER_SEND(void)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_ZONE_OK_FOR_CENTER_SEND;
		mSendDataSize = S_ZONE_OK_FOR_CENTER_SEND;

		if (ProcessForSend())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_DEMAND_BROADCAST_INFO
void MyCenterCom::U_DEMAND_BROADCAST_INFO(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	EnterCriticalSection(&m_lock);
	mSendData[0] = P_DEMAND_BROADCAST_INFO;
	CopyMemory(&mSendData[1], &tInfoSort, 4);
	CopyMemory(&mSendData[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mSendDataSize = S_DEMAND_BROADCAST_INFO;

	while (TRUE)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//SEARCH_AVATAR
int MyCenterCom::SearchAvatarforGM(const char* tAvatarName)
{
	int index01;

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (strcmp(mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName) == 0)
		{
			break;
		}
	}
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}
	return -1;
}

void MyCenterCom::W_ZONE_OTHER_CONNECTION_INFO(int tZoneNumber)
{
	EnterCriticalSection(&m_lock);
	mSendData[0] = P_ZONE_CONNECTION_INFO_SEND;
	mSendDataSize = S_ZONE_CONNECTION_INFO_SEND;
	::memcpy(mSendData + 1, &tZoneNumber, 4);

	while (1)
	{
		if (ProcessForSend())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}
bool MyCenterCom::IsUpdateCashItemInfo()
{
	bool isUpdate = false;

	EnterCriticalSection(&m_lock);
	if (mIsUpdateCashItemInfo)
	{
		isUpdate = true;
	}
	LeaveCriticalSection(&m_lock);

	return isUpdate;
}
void MyCenterCom::SetUpdateCashItemInfo(bool isUpdate)
{
	EnterCriticalSection(&m_lock);
	mIsUpdateCashItemInfo = isUpdate;
	LeaveCriticalSection(&m_lock);
}


MyExtraCom mEXTRA_COM;
MyExtraCom::MyExtraCom(void)
{
	mIsValidCashItemInfo = false;
	mCashItemInfoVersion = 0;
}
//CONNECT
BOOL MyExtraCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}

	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tOKRecvCheck;
	char tOKDataCheck;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		Sleep(1);
		return FALSE;
	}
	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		closesocket(mSocket);
		return FALSE;
	}
	tSendData[0] = P_ZONE_FOR_EXTRA_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_EXTRA_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR )
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			closesocket(mSocket);
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	int tRecvValue01 = 0;
	int tRecvValue02 = 0;
	char tRecvData[S_ZONE_FOR_EXTRA_RECV] = { 0 };
	const int RECV_DATA_SIZE = S_ZONE_FOR_EXTRA_RECV;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &tRecvData[tRecvValue01], RECV_DATA_SIZE - tRecvValue01, 0);
		if (tRecvValue02 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			closesocket(mSocket);
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 == RECV_DATA_SIZE)
		{
			break;
		}
	}
	CopyMemory(&mCashItemInfoVersion, &tRecvData[1], 4);
	CopyMemory(mCashItemInfo, &tRecvData[5], 8960);
	mIsValidCashItemInfo = true;
	mCheckConnectState = TRUE;

	return TRUE;
}
//SEND
BOOL MyExtraCom::Send(void)
{
	int nResult = 0;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR )
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}
//RECV
BOOL MyExtraCom::Recv(void)
{
	int nCount = 0;
	int nResult = 0;
	int tRecvValue01;
	int tRecvValue02;

	if (mRecvDataSize > 0)
	{
		tRecvValue01 = 0;
		while (TRUE)
		{
			tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], mRecvDataSize - tRecvValue01, 0);
			if (tRecvValue02 == SOCKET_ERROR)
			{
				if (WSAGetLastError() == WSAEINTR)
				{
					continue;
				}
				Close();
				return FALSE;
			}
			tRecvValue01 += tRecvValue02;
			if (tRecvValue01 == mRecvDataSize)
			{
				break;
			}
		}
	}

	return TRUE;
}

//CLOSE
void MyExtraCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

//INIT
BOOL MyExtraCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1) 
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;

	if (!Connect()) 
	{
		return FALSE;
	}

	return TRUE;
}

//FREE
void MyExtraCom::Free(void)
{
	Close();
}

//PROCESS_FOR_NETWORK
BOOL MyExtraCom::ProcessForNetwork(void)
{
	if (!Connect())
	{
		return FALSE;
	}
	if (!Send())
	{
		return FALSE;
	}
	if (!Recv())
	{
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_EXTRA_SEND
BOOL MyExtraCom::U_ZONE_OK_FOR_EXTRA_SEND(void)
{
	mSendData[0] = P_ZONE_OK_FOR_EXTRA_SEND;
	mSendDataSize = S_ZONE_OK_FOR_EXTRA_SEND;
	mRecvDataSize = 0;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	return TRUE;
}

//U_GUILD_WORK_FOR_EXTRA_SEND
BOOL MyExtraCom::U_GUILD_WORK_FOR_EXTRA_SEND(int tSort, BYTE tData[MAX_GUILD_WORK_SIZE])
{
	mSendData[0] = P_GUILD_WORK_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tSort, 4);
	CopyMemory(&mSendData[5], &tData[0], MAX_GUILD_WORK_SIZE);
	mSendDataSize = S_GUILD_WORK_FOR_EXTRA_SEND;
	mRecvDataSize = S_GUILD_WORK_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_GuildInfo, &mRecvData[5], sizeof(GUILD_INFO));
	return TRUE;
}

//U_GET_CASH_SIZE_FOR_EXTRA_SEND
BOOL MyExtraCom::U_GET_CASH_SIZE_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH])
{
	mSendData[0] = P_GET_CASH_SIZE_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
	mSendDataSize = S_GET_CASH_SIZE_FOR_EXTRA_SEND;
	mRecvDataSize = S_GET_CASH_SIZE_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Cash, &mRecvData[1], 4);
	return TRUE;
}

BOOL MyExtraCom::U_BUY_CASH_ITEM_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex, int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe, int tLevel, int tVersion)
{
	int svr_num = 1;
	mSendData[0] = P_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &tID[0], MAX_USER_ID_LENGTH);
	CopyMemory(&mSendData[(1 + MAX_USER_ID_LENGTH)], &tCostInfoIndex, 4);
	CopyMemory(&mSendData[(5 + MAX_USER_ID_LENGTH)], &iIndex, 4);
	CopyMemory(&mSendData[(9 + MAX_USER_ID_LENGTH)], &iQuantity, 4);
	CopyMemory(&mSendData[(13 + MAX_USER_ID_LENGTH)], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mSendData[(13 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tTribe, 4);
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tLevel, 4);
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4)], &svr_num, 4);
	CopyMemory(&mSendData[(17 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH + 4 + 4)], &tVersion, 4);
	mSendDataSize = S_BUY_CASH_ITEM_FOR_EXTRA_SEND;
	mRecvDataSize = S_BUY_CASH_ITEM_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	CopyMemory(&mRecv_Cash, &mRecvData[5], 4);
	CopyMemory(&mRecv_Cost, &mRecvData[9], 4);
	return TRUE;
}
BOOL MyExtraCom::U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND()
{
	mSendData[0] = P_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mSendDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mRecvDataSize = S_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}

	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	if (mRecv_Result == 0)
	{
		mIsValidCashItemInfo = false;
		return TRUE;
	}
	else if (mRecv_Result == 1)
	{
		return FALSE;
	}
	else
	{
		mIsValidCashItemInfo = false;
		return FALSE;
	}
}

BOOL MyExtraCom::U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND()
{
	mSendData[0] = P_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	CopyMemory(&mSendData[1], &mSERVER_INFO.mServerNumber, 4);
	mSendDataSize = S_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND;
	mRecvDataSize = S_GET_CASH_ITEM_INFO_FOR_EXTRA_RECV;
	if (!ProcessForNetwork())
	{
		return FALSE;
	}
	CopyMemory(&mRecv_Result, &mRecvData[1], 4);
	if (mRecv_Result == 0)
	{
		CopyMemory(&mCashItemInfoVersion, &mRecvData[5], 4);
		CopyMemory(mCashItemInfo, &mRecvData[9], 8960);
		mIsValidCashItemInfo = true;
		return TRUE;
	}
	return FALSE;
} 




MyGameLog mGAMELOG;
MyGameLog::MyGameLog(void)
{

}
//INIT
BOOL MyGameLog::Init(char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	mSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (mSocket == INVALID_SOCKET)
	{
		return FALSE;
	}
	ZeroMemory(&mAddress, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(tIP);
	mAddress.sin_port = htons(tPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		Sleep(1);
		return FALSE;
	}
	mCheckConnectState = TRUE;
	return TRUE;
}
//FREE
void MyGameLog::Free(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}
//CHECK_VALID_STATE
BOOL MyGameLog::CheckValidState(int tUserIndex)
{
	return TRUE;
}
//SEND_TO_LOG_SERVER
void MyGameLog::SendToLogServer(void)
{
	int tTotalPacketSize;
	socklen_t socklen = sizeof(struct sockaddr_in);

	tTotalPacketSize = 5 + strlen(mGameLogData);
	CopyMemory(&mSendBuffer[0], &tTotalPacketSize, 4);
	CopyMemory(&mSendBuffer[4], &mGameLogData[0], (strlen(mGameLogData) + 1));
	sendto(mSocket, &mSendBuffer[0], tTotalPacketSize, 0, (struct sockaddr*)&mAddress, socklen);
}
//SEND_TO_LOG_SERVER_FOR_DB
void MyGameLog::SendToLogServerForDB(void)
{
	int tTotalPacketSize;
	int tTotalQuerySize;
	socklen_t socklen = sizeof(struct sockaddr_in);

	tTotalPacketSize = -1;
	tTotalQuerySize = strlen(mGameLogData) + 1;
	CopyMemory(&mSendBuffer[0], &tTotalPacketSize, 4);
	CopyMemory(&mSendBuffer[4], &tTotalQuerySize, 4);
	CopyMemory(&mSendBuffer[8], &mGameLogData[0], (strlen(mGameLogData) + 1));
	sendto(mSocket, &mSendBuffer[0], tTotalPacketSize + 8, 0, (struct sockaddr*)&mAddress, socklen);
}
//GL_601_GM_CREATE_MONEY
void MyGameLog::GL_601_GM_CREATE_MONEY(int tUserIndex, int tValue)
{
	mLogSort = 601;
	sprintf(mGameLogData, "[%d]<GM_CREATE_MONEY>(%s),(%s),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_602_GM_CREATE_ITEM
void MyGameLog::GL_602_GM_CREATE_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	mLogSort = 602;
	sprintf(mGameLogData, "[%d]<GM_CREATE_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_603_TRACE_USER
void MyGameLog::GL_603_TRACE_USER(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 603;
	sprintf(mGameLogData, "[%d]<TRACE_USER>(%s),(%s),(PACKET)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_604_BUY_CASH_ITEM
void MyGameLog::GL_604_BUY_CASH_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iCostSize, int iBonusCostSize)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 604;
	sprintf(mGameLogData, "[%d]<BUY_CASH_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),(%d,%d)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, iCostSize, iBonusCostSize, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_605_USE_CASH_ITEM
void MyGameLog::GL_605_USE_CASH_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 605;
	sprintf(mGameLogData, "[%d]<USE_CASH_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_606_USE_INVENTORY_ITEM
void MyGameLog::GL_606_USE_INVENTORY_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 606;
	sprintf(mGameLogData, "[%d]<USE_INVENTORY_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tIndex, tQuantity, tValue, mUTIL.ReturnISValue(tValue), mUTIL.ReturnIUValue(tValue), tRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_607_GAIN_SIN_ITEM
void MyGameLog::GL_607_GAIN_SIN_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 607;
	sprintf(mGameLogData, "[%d]<GAIN_SIN_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_608_IMPROVE_ITEM
void MyGameLog::GL_608_IMPROVE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 608;
	sprintf(mGameLogData, "[%d]<IMPROVE_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_609_PSHOP_ITEM
void MyGameLog::GL_609_PSHOP_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 609;
	sprintf(mGameLogData, "[%d]<PSHOP_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_610_QUEST_ITEM
void MyGameLog::GL_610_QUEST_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 610;
	sprintf(mGameLogData, "[%d]<QUEST_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_611_QUEST_MONEY
void MyGameLog::GL_611_QUEST_MONEY(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 611;
	sprintf(mGameLogData, "[%d]<QUEST_MONEY>(%s),(%s),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_612_QUEST_KILL_NUM
void MyGameLog::GL_612_QUEST_KILL_NUM(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 612;
	sprintf(mGameLogData, "[%d]<QUEST_KILL_NUM>(%s),(%s),(KILL_NUM)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_613_QUEST_EXP
void MyGameLog::GL_613_QUEST_EXP(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 613;
	sprintf(mGameLogData, "[%d]<QUEST_EXP>(%s),(%s),(EXP)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_614_QUEST_TEACHER_POINT
void MyGameLog::GL_614_QUEST_TEACHER_POINT(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 614;
	sprintf(mGameLogData, "[%d]<QUEST_TEACHER_POINT>(%s),(%s),(TEACHER_POINT)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_615_TRADE_ITEM
void MyGameLog::GL_615_TRADE_ITEM(int tUserIndex, int tOtherIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if ((!CheckValidState(tUserIndex)) || (!CheckValidState(tOtherIndex)))
	{
		return;
	}
	mLogSort = 615;
	sprintf(mGameLogData, "[%d]<TRADE_ITEM>((%s),(%s))->((%s),(%s)),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_616_TRADE_MONEY
void MyGameLog::GL_616_TRADE_MONEY(int tUserIndex, int tOtherIndex, int tValue, int tValue2)
{
	if ((!CheckValidState(tUserIndex)) || (!CheckValidState(tOtherIndex)))
	{
		return;
	}
	mLogSort = 616;
	sprintf(mGameLogData, "[%d]<TRADE_MONEY>((%s),(%s))->((%s),(%s)),(MONEY)(%d),(MONEY2)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, tValue, tValue2, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_617_GUILD_MONEY
void MyGameLog::GL_617_GUILD_MONEY(int tUserIndex, int tValue, int tAction, int tGrade)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 617;
	sprintf(mGameLogData, "[%d]<GUILD_MONEY>(%s),(%s),(ACTION)(%d),(MONEY)(%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, tGrade, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_618_TRIBE_MONEY
void MyGameLog::GL_618_TRIBE_MONEY(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 618;
	sprintf(mGameLogData, "[%d]<TRIBE_MONEY>(%s),(%s),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_619_GAIN_ITEM
void MyGameLog::GL_619_GAIN_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 619;
	sprintf(mGameLogData, "[%d]<GAIN_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_620_DROP_ITEM
void MyGameLog::GL_620_DROP_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 620;
	sprintf(mGameLogData, "[%d]<DROP_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_621_NSHOP_ITEM
void MyGameLog::GL_621_NSHOP_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 621;
	sprintf(mGameLogData, "[%d]<NPCSHOP_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_622_TRADESLOT_ITEM
void MyGameLog::GL_622_TRADESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 622;
	sprintf(mGameLogData, "[%d]<TRADESLOT_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_623_TRADESLOT_MONEY
void MyGameLog::GL_623_TRADESLOT_MONEY(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 623;
	sprintf(mGameLogData, "[%d]<TRADESLOT_MONEY>(%s),(%s),(ACTION)(%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_624_STROESLOT_ITEM
void MyGameLog::GL_624_STROESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 624;
	sprintf(mGameLogData, "[%d]<STORESLOT_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_625_STORESLOT_MONEY
void MyGameLog::GL_625_STORESLOT_MONEY(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 625;
	sprintf(mGameLogData, "[%d]<STORESLOT_MONEY>(%s),(%s),(ACTION)(%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_626_SAVESLOT_ITEM
void MyGameLog::GL_626_SAVESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 626;
	sprintf(mGameLogData, "[%d]<SAVESLOT_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_627_SAVESLOT_MONEY
void MyGameLog::GL_627_SAVESLOT_MONEY(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 627;
	sprintf(mGameLogData, "[%d]<SAVESLOT_MONEY>(%s),(%s),(ACTION)(%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_628_GM_MONCALL
void MyGameLog::GL_628_GM_MONCALL(int tUserIndex, int tValue)
{
	mLogSort = 628;
	sprintf(mGameLogData, "[%d]<GM_MONCALL>(%s),(%s),(MONSTER)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_629_GM_NCHAT
void MyGameLog::GL_629_GM_NCHAT(int tUserIndex, int tOtherIndex)
{
	mLogSort = 629;
	sprintf(mGameLogData, "[%d]<GM_NCHAT>((%s),(%s))->((%s),(%s)),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_630_GM_YCHAT
void MyGameLog::GL_630_GM_YCHAT(int tUserIndex, int tOtherIndex)
{
	mLogSort = 630;
	sprintf(mGameLogData, "[%d]<GM_YCHAT>((%s),(%s))->((%s),(%s)),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_631_GM_KICK
void MyGameLog::GL_631_GM_KICK(int tUserIndex, int tOtherIndex)
{
	mLogSort = 631;
	sprintf(mGameLogData, "[%d]<GM_KICK>((%s),(%s))->((%s),(%s)),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_632_GM_BLOCK
void MyGameLog::GL_632_GM_BLOCK(int tUserIndex, int tOtherIndex)
{
	mLogSort = 632;
	sprintf(mGameLogData, "[%d]<GM_BLOCK>((%s),(%s))->((%s),(%s)),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherIndex].uID, mUSER[tOtherIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_633_MINUS_EXP_WITH_DIE
void MyGameLog::GL_633_MINUS_EXP_WITH_DIE(int tUserIndex, int tValue1, int tValue2)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 633;
	sprintf(mGameLogData, "[%d]<MINUS_EXP_WITH_DIE>(%s),(%s),(BEFORE_EXP)(%d),(AFTER_EXP)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue1, tValue2, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_634_ADD_ITEM
void MyGameLog::GL_634_ADD_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 634;
	sprintf(mGameLogData, "[%d]<ADD_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_635_HIGH_ITEM
void MyGameLog::GL_635_HIGH_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice, int tItem2)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 635;
	sprintf(mGameLogData, "[%d]<HIGH_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), tItem2, iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_636_LOW_ITEM
void MyGameLog::GL_636_LOW_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice, int tItem2)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 636;
	sprintf(mGameLogData, "[%d]<LOW_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), tItem2, iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_637_EXCHANGE_ITEM
void MyGameLog::GL_637_EXCHANGE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 637;
	sprintf(mGameLogData, "[%d]<EXCHANGE_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),(MONEY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_638_MAKE_ITEM
void MyGameLog::GL_638_MAKE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 638;
	sprintf(mGameLogData, "[%d]<MAKE_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_639_MAKE_SKILL
void MyGameLog::GL_639_MAKE_SKILL(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 639;
	sprintf(mGameLogData, "[%d]<MAKE_SKILL>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_640_USER_CREATE_ITEM
void MyGameLog::GL_640_USER_CREATE_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 640;
	sprintf(mGameLogData, "[%d]<USER_CREATE_ITEM>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_641_MAKE_TRIBE_WEAPON
void MyGameLog::GL_641_MAKE_TRIBE_WEAPON(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 641;
	sprintf(mGameLogData, "[%d]<MAKE_TRIBE_WEAPON>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_642_N_PROTECT
void MyGameLog::GL_642_N_PROTECT(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 642;
	sprintf(mGameLogData, "[%d]<N_PROTECT>(%s),(%s),(VALUE)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_643_CHECK_MONSTER_ATTACK_PACKET
void MyGameLog::GL_643_CHECK_MONSTER_ATTACK_PACKET(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 643;
	sprintf(mGameLogData, "[%d]<CHECK_MONSTER_ATTACK_PACKET>(%s),(%s),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

void MyGameLog::GL_644_CHECK_AUTH_KEY(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 644;
	sprintf(mGameLogData, "[%d]<MISMATCH_MOUSE_PASSWORD>(%s),(%s),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_648_GM_GOD
void MyGameLog::GL_648_GM_GOD(int tUserIndex, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 648;
	sprintf(mGameLogData, "[%d]<GM_GOD>((%s),(%s))->(GOD)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_649_GM_CHAT
void MyGameLog::GL_649_GM_CHAT(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 649;
	sprintf(mGameLogData, "[%d]<GM_CHAT>(%s),(%s),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_650_GM_UMOVE
void MyGameLog::GL_650_GM_UMOVE(int tUserIndex, int tOtherUserIndex, int tZone)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 650;
	sprintf(mGameLogData, "[%d]<GM_UMOVE>((%s),(%s))->(UMOVE)((%s),(%s)),(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherUserIndex].uID, mUSER[tOtherUserIndex].mAvatarInfo.aName, tZone, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_651_GM_LEVEL
void MyGameLog::GL_651_GM_LEVEL(int tUserIndex, int tLevel)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 651;
	sprintf(mGameLogData, "[%d]<GM_LEVEL>((%s),(%s))->(LV)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tLevel, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_652_GM_ZNOTICE
void MyGameLog::GL_652_GM_ZNOTICE(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 652;
	sprintf(mGameLogData, "[%d]<GM_ZNOTICE>(%s),(%s),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_653_GM_RES
void MyGameLog::GL_653_GM_RES(int tUserIndex, int tOtherUserIndex, int tRes)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 653;
	sprintf(mGameLogData, "[%d]<GM_RES>((%s),(%s))->(RES)((%s),(%s))(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherUserIndex].uID, mUSER[tOtherUserIndex].mAvatarInfo.aName, tRes, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_654_GM_RENAME
void MyGameLog::GL_654_GM_RENAME(int tUserIndex, int tOtherUserIndex, char* tName, char* tChangeName)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 654;
	sprintf(mGameLogData, "[%d]<GM_RENAME>((%s),(%s))->(RENAME)((%s),(%s))(%s),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherUserIndex].uID, tName, tChangeName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_655_GM_CALL
void MyGameLog::GL_655_GM_CALL(int tUserIndex, int tOtherUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 655;
	sprintf(mGameLogData, "[%d]<GM_CALL>((%s),(%s))->((%s),(%s)),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tOtherUserIndex].uID, mUSER[tOtherUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_656_GM_EXP
void MyGameLog::GL_656_GM_EXP(int tUserIndex, int tExp)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 656;
	sprintf(mGameLogData, "[%d]<GM_EXP>((%s),(%s))->(EXP)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tExp, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_657_GM_DIE
void MyGameLog::GL_657_GM_DIE(int tUserIndex, int tMonsterNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 657;
	sprintf(mGameLogData, "[%d]<GM_DIE>((%s),(%s))->(MONSTER)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tMonsterNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_658_USE_INVENTORY_ITEM
void MyGameLog::GL_658_USE_INVENTORY_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber, int tCount)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 658;
	sprintf(mGameLogData, "[%d]<USE_INVENTORY_ITEM>(%s),(%s),(ACTION)(%d)(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tCount, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tIndex, tQuantity, tValue, mUTIL.ReturnISValue(tValue), mUTIL.ReturnIUValue(tValue), tRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
// # Defense Hack # {
void MyGameLog::GL_659_AUTO_CHECK(int tUserIndex, int tType, float fValue, int iValue /* = 0 */, int iValue2 /* = 0 */)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 659;
	sprintf(mGameLogData, "[%d]<AUTO_USER>(%s),(%s),(ACTION)(%d)(%5.3f, %d, %d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tType, fValue, iValue, iValue2, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//void MyGameLog::GL_659_AUTO_CHECK (int tUserIndex, int tType, float fValue)
//{
//	if( !CheckValidState( tUserIndex ) )
//	{
//		return;
//	}
//	mLogSort = 659;
//	sprintf( mGameLogData, "[%d]<AUTO_USER>(%s),(%s),(ACTION)(%d)(%5.3f),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tType, fValue, mSERVER_INFO.mServerNumber );
//	SendToLogServer();
//}
// # }

void MyGameLog::GL_660_AUTO_CHECK(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 660;
	sprintf(mGameLogData, "[%d]<SPEED_USER>(%s),(%s),(KICK),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_661_START_MISSION_LABYRINTH
void MyGameLog::GL_661_START_MISSION_LABYRINTH(void)
{
	mLogSort = 661;
	sprintf(mGameLogData, "[%d]<GL_661_START_MISSION_LABYRINTH>,[[%d]]", mLogSort, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_662_END_MISSION_LABYRINTH
void MyGameLog::GL_662_END_MISSION_LABYRINTH(void)
{
	mLogSort = 662;
	sprintf(mGameLogData, "[%d]<GL_662_END_MISSION_LABYRINTH>,[[%d]]", mLogSort, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
// # X-Trap # {
//GL_663_X_TRAP
void MyGameLog::GL_663_X_TRAP(int tUserIndex, unsigned long tErrCode)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 663;
	sprintf(mGameLogData, "[%d]<X_TRAP>(%s),(%s),(ERROR_NUM)(%ld)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tErrCode, mSERVER_INFO.mServerNumber);
	SendToLogServer();
} // # }
//GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM // ÅÍÅ° ÆÐÅ°Áö ¾ÆÀÌÅÛ Àü¿ë ·Î±×.
// ÆÐÅ°Áö ¾ÆÀÌÅÛ »ç¿ë ÈÄ º¸³Ê½º Ä³½¬ Áö±Þ¹Þ±â¿¡ ½ÇÆÐ ½Ã ³²±â´Â ·Î±×ÀÔ´Ï´Ù.
void MyGameLog::GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(int tUserIndex, int iIndex, int failType)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 664;
	sprintf(mGameLogData, "[%d]<BONUS_CASH_FAIL_FOR_PACKAGE_ITEM>(%s),(%s),(%d),(%d)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, failType, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_700_SPHINX_HACK
void MyGameLog::GL_700_SPHINX_HACK(int tUserIndex)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 700;
	sprintf(mGameLogData, "[%d]<SPHINX_HACK>(%s),(%s)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_701_CHEAT_USER
void MyGameLog::GL_701_CHEAT_USER(int tUserIndex, int cheatSort)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 701;
	sprintf(mGameLogData, "[%d]<CHEAT_USER>(%s),(%s),(%d)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, cheatSort, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_702_CHEAT_AVATAR_ACTION
void MyGameLog::GL_702_CHEAT_AVATAR_ACTION(int tUserIndex, int skillNum, int skillGrad1, int skillGrad2, int skillVal)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 702;
	sprintf(mGameLogData, "[%d]<CHEAT_AVATAR_ACTION>(%s),(%s),(%d),(%d),(%d),(%d)[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, skillNum, skillGrad1, skillGrad2, skillVal, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

/** 2009. 12. 18 : ±â¿©µµ °ü·Ã ·Î±× Ãß°¡ (wolf) */
void MyGameLog::GL_800_USE_KILLNUM_TO_ITEM(int tUserIndex, int iBeforeKillOtherTribe, int iAfterKillOtherTribe)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 800;
	sprintf(mGameLogData, "[%d]<USE_KILLNUM_TO_ITEM>(%s),(%s),(%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iBeforeKillOtherTribe, iAfterKillOtherTribe, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
void MyGameLog::GL_801_UPGRADE_AVATAR(int tUserIndex, int tValue01, int tValue02)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 801;
	sprintf(mGameLogData, "[%d]<UPGRADE_AVATAR>(%s),(%s),(%d),(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tValue01, tValue02, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
void MyGameLog::GL_802_USE_KILLOTHERTRIBE_TO_ITEM(int tUserIndex, int iBeforeKillOtherTribe, int iAfterKillOtherTribe)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 802;
	sprintf(mGameLogData, "[%d]<USE_KILLNUM_TO_ITEM>(%s),(%s),(%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iBeforeKillOtherTribe, iAfterKillOtherTribe, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

void MyGameLog::CHAT_LOG_SEND(int tUserIndex, char* aName, char* Chat, char* Type)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 803;
	sprintf(mGameLogData, "[%d]<CL_CHAT_LOG>Username:(%s) - Character Name: (%s) - Message: (%s), Type:(%s) Zone: [%d]", mLogSort, mUSER[tUserIndex].mAvatarInfo.aName, aName, Chat, Type, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_623_TRADESLOT_MONEY2
void MyGameLog::GL_804_TRADESLOT_MONEY2(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 804;
	sprintf(mGameLogData, "[%d]<TRADESLOT_MONEY2>(%s),(%s),(ACTION)(%d),(MONEY2)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_805_INVENSLOT_MONEY2
void MyGameLog::GL_805_INVENSLOT_MONEY2(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 805;
	sprintf(mGameLogData, "[%d]<INVENSLOT_MONEY2>(%s),(%s),(ACTION)(%d),(MONEYMOVED)(%d),(MONEY2)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction,tValue, mUSER[tUserIndex].mAvatarInfo.aMoney2, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_806_STORESLOT_MONEY2
void MyGameLog::GL_806_STORESLOT_MONEY2(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 806;
	sprintf(mGameLogData, "[%d]<STORESLOT_MONEY2>(%s),(%s),(ACTION)(%d),(MONEY2)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_807_SAVESLOT_MONEY2
void MyGameLog::GL_807_SAVESLOT_MONEY2(int tUserIndex, int tAction, int tValue)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 807;
	sprintf(mGameLogData, "[%d]<SAVESLOT_MONEY2>(%s),(%s),(ACTION)(%d),(MONEY2)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, tValue, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_808_ANIMAL_DELETE
void MyGameLog::GL_808_ANIMAL_DELETE(int tUserIndex, int tAnimalNumber, int tAnimalExp, int tAnimalAbility)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 808;
	sprintf(mGameLogData, "[%d]<ANIMAL_DELETE>(%s),(%s),(ANIMALNUMBER)(%d),(ANIMALEXP)(%d),(ANIMALABILITY)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAnimalNumber, tAnimalExp, tAnimalAbility, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_809_COSTUME_DELETE
void MyGameLog::GL_809_COSTUME_DELETE(int tUserIndex, int tCostumeNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 809;
	sprintf(mGameLogData, "[%d]<COSTUME_DELETE>(%s),(%s),(COSTUMENUMBER)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tCostumeNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_810_DAILY_MISSION_REWARD
void MyGameLog::GL_810_DAILY_MISSION_REWARD(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 810;
	sprintf(mGameLogData, "[%d]<DAILY_REWARD>(%s),(%s),(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), iRecognitionNumber, tIndex, tQuantity, tValue, mUTIL.ReturnISValue(tValue), mUTIL.ReturnIUValue(tValue), tRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_811_REFINE_ITEM
void MyGameLog::GL_811_REFINE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 811;
	sprintf(mGameLogData, "[%d]<REFINE_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d),(CPCOST)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), mUTIL.ReturnMemoryValue(iValue, 3), mUTIL.ReturnMemoryValue(iValue, 4), iRecognitionNumber, tPrice, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_812_SOCKET_ITEM
void MyGameLog::GL_812_SOCKET_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iInvenSocket1, int iInvenSocket2, int iInvenSocket3)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 812;
	sprintf(mGameLogData, "[%d]<SOCKET_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d),(SOCKETS)(%d),(GEMS)(%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), mUTIL.ReturnMemoryValue(iValue, 3), mUTIL.ReturnMemoryValue(iValue, 4), iRecognitionNumber, mUTIL.ReturnMemoryValue(iInvenSocket1, 2), mUTIL.ReturnMemoryValue(iInvenSocket1, 4), mUTIL.ReturnMemoryValue(iInvenSocket2, 2), mUTIL.ReturnMemoryValue(iInvenSocket2, 4), mUTIL.ReturnMemoryValue(iInvenSocket3, 2), mUTIL.ReturnMemoryValue(iInvenSocket3, 4), mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_813_LEGEND_DIAMOND_INSERT
void MyGameLog::GL_813_LEGEND_DIAMOND_INSERT(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iInvenSocket1, int iInvenSocket2, int iInvenSocket3)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 813;
	sprintf(mGameLogData, "[%d]<SOCKET_ITEM>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d,%d,%d,%d,%d),(SOCKETS)(%d),(GEMS)(%d,%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), mUTIL.ReturnMemoryValue(iValue, 3), mUTIL.ReturnMemoryValue(iValue, 4), iRecognitionNumber, mUTIL.ReturnMemoryValue(iInvenSocket1, 2), mUTIL.ReturnMemoryValue(iInvenSocket1, 3), mUTIL.ReturnMemoryValue(iInvenSocket2, 1), mUTIL.ReturnMemoryValue(iInvenSocket2, 3), mUTIL.ReturnMemoryValue(iInvenSocket3, 1), mUTIL.ReturnMemoryValue(iInvenSocket3, 3), mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_814_IMPROVE_LEGEND_DECO
void MyGameLog::GL_814_IMPROVE_LEGEND_DECO(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 814;
	sprintf(mGameLogData, "[%d]<IMPROVE_LEGEND_DECO>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d),(DECOSTATS)(%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, iRecognitionNumber, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), mUTIL.ReturnMemoryValue(iValue, 3), mUTIL.ReturnMemoryValue(iValue, 4), mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_815_IMPROVE_ULTIMATE_PET
void MyGameLog::GL_815_IMPROVE_ULTIMATE_PET(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 815;
	sprintf(mGameLogData, "[%d]<IMPROVE_ULTIMATE_PET>(%s),(%s),(ACTION)(%d),(ITEM)(%d,%d,%d,%d),(PETSTATS)(%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tAction, iIndex, iQuantity, iValue, iRecognitionNumber, mUTIL.ReturnISValue(iValue), mUTIL.ReturnIUValue(iValue), mUTIL.ReturnMemoryValue(iValue, 3), mUTIL.ReturnMemoryValue(iValue, 4), mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_816_BUY_BLOODSTAINED_SHOP
void MyGameLog::GL_816_BUY_BLOODSTAINED_SHOP(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 816;
	sprintf(mGameLogData, "[%d]<BUY_BLOODSTAINED_SHOP>(%s),(%s),(ITEM)(%d,%d,%d,%d),(PKPOINTS)(%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, iRecognitionNumber, mUSER[tUserIndex].mAvatarInfo.aPK, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}

//GL_817_BUY_CAPSULE_STORE
void MyGameLog::GL_817_BUY_CAPSULE_STORE(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 816;
	sprintf(mGameLogData, "[%d]<BUY_CAPSULE_STORE>(%s),(%s),(ITEM)(%d,%d,%d,%d),(CAPSULEPOINTS)(%d, %d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, iRecognitionNumber, mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall, mUSER[tUserIndex].mAvatarInfo.aCapsuleOnlineTime, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
//GL_818_DAILY_LOGIN
void MyGameLog::GL_818_DAILY_LOGIN(int tUserIndex, int tResultSort, int tWhatDay, int tCurrentClaimState)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 817;
	switch (tResultSort)
	{
	case 1:
		sprintf(mGameLogData, "[%d]<DAILY_CLAIM_LOGIN>(%s),(%s),(LEVEL NOT M33),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mSERVER_INFO.mServerNumber);
		break;
	case 2:
		sprintf(mGameLogData, "[%d]<DAILY_CLAIM_LOGIN>(%s),(%s),(DAY: %d, tClaimState: %d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, tWhatDay, tCurrentClaimState, mSERVER_INFO.mServerNumber);
		break;
	}
	SendToLogServer();
}
// GL_819_GEAR_BREAK
void MyGameLog::GL_819_GEAR_BREAK(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 819;
	sprintf(mGameLogData, "[%d]<GEAR_BREAK>(%s),(%s),(ITEM)(%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, iRecognitionNumber, mSERVER_INFO.mServerNumber);
	SendToLogServer();
}
// GL_820_AMULET_TO_LEGEND_PET_UPGRADE
void MyGameLog::GL_820_AMULET_TO_LEGEND_PET_UPGRADE(int tUserIndex, int tCraftSort, int iIndex, int iQuantity, int iValue, int iRecognitionNumber)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}
	mLogSort = 820;
	switch (tCraftSort)
	{
	case 1:
		sprintf(mGameLogData, "[%d]<LEGEND_PET_CRAFT>(%s),(%s),(MATERIALS)(ITEM)(%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, iRecognitionNumber, mSERVER_INFO.mServerNumber);
		break;
	case 2:
		sprintf(mGameLogData, "[%d]<LEGEND_PET_CRAFT>(%s),(%s),(RESULT)(ITEM)(%d,%d,%d,%d),[[%d]]", mLogSort, mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, iIndex, iQuantity, iValue, iRecognitionNumber, mSERVER_INFO.mServerNumber);
		break;
	}
	SendToLogServer();
}

void MyGameLog::GL_CHAT_LOG(int tUserIndex, int tSort, MyUser* user_info, char* tContent)
{
	if (!CheckValidState(tUserIndex))
	{
		return;
	}

	switch (tSort) {
	case 0:
		snprintf(mGameLogData, 804, "<CL_CHATLOG> - uID[%s] - WorldNum(%d) - ZoneNum[[%d]] - Type(NORMAL) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;
	case 1:
		snprintf(mGameLogData, 804, "<CL_CHATLOG> - uID[%s] - WorldNum(%d) - ZoneNum[[%d]] - Type(SHOUT) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;
	case 2:
		snprintf(mGameLogData, 804, "<CL_CHATLOG> - uID[%s] - WorldNum(%d) - ZoneNum[[%d]] - Type(SECRET) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;
	case 3:
		snprintf(mGameLogData, 804, "<CL_CHATLOG> - uID[%s] - WorldNum(%d) - ZoneNum[[%d]] - Type(PARTY) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;
	case 4:
		snprintf(mGameLogData, 804, "<CL_CHATLOG> - uID[%s] - WorldNum(%d) - ZoneNum[[%d]] - Type(FACTION) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;
	case 5:
		snprintf(mGameLogData, 805, "<CL_CHATLOG> - uID[%s] - WorldNum((%d)) - ZoneNum[[%d]] - Type(GUILD) - aName{%s} - Content(%s)"
			, user_info->uID, mSERVER_INFO.mWorldNumber, mSERVER_INFO.mServerNumber, user_info->mAvatarInfo.aName
			, tContent);
		break;

	}

	SendToLogServer();
}

//-------------------------------------------------------------------------------------------------
//CLASS_OF_MY_CHATLOG
//-------------------------------------------------------------------------------------------------
//INSTANCE
MyChatLog mCHATLOG;
//CREATE
MyChatLog::MyChatLog(void)
{
}
//INIT
BOOL MyChatLog::Init(char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	mSocket = socket(PF_INET, SOCK_DGRAM, 0);
	if (mSocket == INVALID_SOCKET )
	{
		return FALSE;
	}
	ZeroMemory(&mAddress, sizeof(mAddress));
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(tIP);
	mAddress.sin_port = htons(tPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		closesocket(mSocket);
		return FALSE;
	}
	mCheckConnectState = TRUE;
	return TRUE;
}
//FREE
void MyChatLog::Free(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}
//SEND_TO_LOG_SERVER
void MyChatLog::SendToLogServer(int tTribe, int tChatSort, char tAvatarName01[MAX_AVATAR_NAME_LENGTH], char tAvatarName02[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{

	char tempString01[1000];
	char tempString02[1000];
	socklen_t socklen = sizeof(struct sockaddr_in);

	sprintf(tempString02, "%c%d%c%d%c%d%c%d%c%s%c%s%c%s", 0x0b, tTribe, 0x0b, mSERVER_INFO.mWorldNumber, 0x0b, mSERVER_INFO.mServerNumber, 0x0b, tChatSort, 0x0b, tAvatarName01, 0x0b, tAvatarName02, 0x0b, tContent);
	sprintf(tempString01, "%d%s", (int)strlen(tempString02), tempString02);


	sendto(mSocket, &tempString01[0], strlen(tempString01), 0, (struct sockaddr*)&mAddress, socklen);
	send(mSocket, &tempString01[0], strlen(tempString01), 0);

	/*xLog()->GameLog2("LOG1 %s \n", tempString02);
	xLog()->GameLog2("LOG2 %s \n", tempString01);*/

}



MyRelayCom mRELAY_COM;

MyRelayCom::MyRelayCom(void)
{

}
//CONNECT
BOOL MyRelayCom::Connect(void)
{
	if (mCheckConnectState)
	{
		return TRUE;
	}
	int tConnectRecvCheck;
	char tConnectDataCheck;
	char tSendData[1000];
	int tSendDataSize;
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;
	int tRecvDataSize;
	int tRecvValue01;
	int tRecvValue02;

	mSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (mSocket == INVALID_SOCKET )
	{
		return FALSE;
	}
	mAddress.sin_family = AF_INET;
	mAddress.sin_addr.s_addr = inet_addr(mIP);
	mAddress.sin_port = htons(mPort);
	if (connect(mSocket, (LPSOCKADDR)&mAddress, sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
	{
		Close();
		return FALSE;
	}
	tConnectRecvCheck = recv(mSocket, &tConnectDataCheck, 1, 0);
	if (tConnectRecvCheck != 1)
	{
		Close();
		return FALSE;
	}

	mRecvDataSize = 0;
	memset(mRecvData, 0, MAX_RECV_DATA_SIZE);

	tSendData[0] = P_ZONE_FOR_RELAY_SEND;
	CopyMemory(&tSendData[1], &mZoneNumber, 4);
	tSendDataSize = S_ZONE_FOR_RELAY_SEND;
	tSendValue01 = tSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &tSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR )
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	tRecvDataSize = S_ZONE_FOR_RELAY_RECV;
	tRecvValue01 = 0;
	while (TRUE)
	{
		tRecvValue02 = recv(mSocket, &mRecvData[tRecvValue01], tRecvDataSize, 0);
		if (tRecvValue02 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tRecvValue01 += tRecvValue02;
		if (tRecvValue01 >= tRecvDataSize)
		{
			break;
		}
	}
	memmove(mRecvData, mRecvData + tRecvDataSize, (tRecvValue01 - tRecvDataSize));
	mRecvDataSize = tRecvValue01 - tRecvDataSize;
	mCheckConnectState = TRUE;

	if (WSAAsyncSelect(mSocket, mSERVER_INFO.mWindow, WM_NETWORK_MESSAGE_3, FD_READ | FD_CLOSE) == SOCKET_ERROR)
	{
		return FALSE;
	}

	return TRUE;
}

//SEND
BOOL MyRelayCom::Send(void)
{
	int tSendValue01;
	int tSendValue02;
	int tSendValue03;

	tSendValue01 = mSendDataSize;
	tSendValue02 = 0;
	while (tSendValue01 > 0)
	{
		tSendValue03 = send(mSocket, &mSendData[tSendValue02], tSendValue01, 0);
		if (tSendValue03 == SOCKET_ERROR )
		{
			if (WSAGetLastError() == WSAEINTR)
			{
				continue;
			}
			Close();
			return FALSE;
		}
		tSendValue01 -= tSendValue03;
		tSendValue02 += tSendValue03;
	}
	return TRUE;
}

void MyRelayCom::Close(void)
{
	if (!mCheckConnectState)
	{
		return;
	}
	mCheckConnectState = FALSE;
	closesocket(mSocket);
}

BOOL MyRelayCom::Init(int tZoneNumber, char tIP[16], int tPort)
{
	mCheckConnectState = FALSE;
	if (tZoneNumber < 1) 
	{
		return FALSE;
	}
	mZoneNumber = tZoneNumber;
	strcpy(mIP, tIP);
	mPort = tPort;
	InitializeCriticalSection(&m_lock);

	return Connect();
}
//FREE
void MyRelayCom::Free(void)
{
	Close();
	DeleteCriticalSection(&m_lock);
}

int MyRelayCom::PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm)
{
	int tRecvSize;
	BYTE tProtocol;
	int tTotalPacketSize;

	switch (WSAGETSELECTEVENT(lPrm))
	{
	case FD_READ:
		tRecvSize = recv(mSocket, &mRecvData[mRecvDataSize], (MAX_RECV_DATA_SIZE - mRecvDataSize), 0);
		if (tRecvSize == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				return 0;
			}
			Close();
			return 0;
		}
		mRecvDataSize += tRecvSize;
		while (TRUE)
		{
			if (mRecvDataSize < 1)
			{
				return tRecvSize;
			}
			tProtocol = (BYTE)mRecvData[0];
			switch (tProtocol)
			{
			case P_BROADCAST_DATA:
				tTotalPacketSize = S_BROADCAST_DATA;
				if (mRecvDataSize < tTotalPacketSize)
				{
					return tRecvSize;
				}
				W_BROADCAST_DATA();
				break;
			default:
				Close();
				return 0;
			}
			if (mCheckConnectState)
			{
				memmove(mRecvData, mRecvData + tTotalPacketSize, (mRecvDataSize - tTotalPacketSize));
				mRecvDataSize -= tTotalPacketSize;
			}
		}
		return tRecvSize;

	case FD_CLOSE:
		Close();
		return 0;
	}
	return 0;
}

//W_BROADCAST_DATA
void MyRelayCom::W_BROADCAST_DATA(void)
{
	char* tPacket = &mRecvData[0];

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE);

	mWORK.ProcessForRelay(tSort, &tData[0], 2);
}

//PROCESS_FOR_SEND
BOOL MyRelayCom::ProcessForSend(void)
{
	if (!mCheckConnectState)
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	if (!Send())
	{
		Close();
		Sleep(1);
		return FALSE;
	}

	return TRUE;
}

//U_ZONE_OK_FOR_RELAY_SEND
void MyRelayCom::U_ZONE_OK_FOR_RELAY_SEND(void)
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_ZONE_OK_FOR_RELAY_SEND;
		mSendDataSize = S_ZONE_OK_FOR_RELAY_SEND;

		if (ProcessForSend())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}

//U_DEMAND_BROADCAST_DATA
void MyRelayCom::U_DEMAND_BROADCAST_DATA(int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	EnterCriticalSection(&m_lock);
	while (TRUE)
	{
		mSendData[0] = P_DEMAND_BROADCAST_DATA;
		CopyMemory(&mSendData[1], &tSort, 4);
		CopyMemory(&mSendData[5], &tData[0], MAX_BROADCAST_DATA_SIZE);
		mSendDataSize = S_DEMAND_BROADCAST_DATA;

		if (ProcessForSend())
		{
			break;
		}
	}
	LeaveCriticalSection(&m_lock);
}