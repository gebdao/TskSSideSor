#include "MainApp.h"

MyUser* mUSER = NULL;

MyUser::MyUser(void)
{
	mBUFFER_FOR_SEND = NULL;
	mBUFFER_FOR_RECV = NULL;
}
//INIT
BOOL MyUser::Init(int tUserIndex, int tSendBufferSize, int tRecvBufferSize)
{
	mUserIndex = tUserIndex;
	mCheckConnectState = FALSE;

	mBUFFER_FOR_SEND = (char*)GlobalAlloc(GMEM_FIXED, tSendBufferSize);
	if (mBUFFER_FOR_SEND == NULL)
	{
		return FALSE;
	}
	mBUFFER_FOR_RECV = (char*)GlobalAlloc(GMEM_FIXED, tRecvBufferSize);
	if (mBUFFER_FOR_RECV == NULL)
	{
		return FALSE;
	}

	return TRUE;
}
//FREE
void MyUser::Free(void)
{
	if (mBUFFER_FOR_SEND != NULL)
	{
		GlobalFree(mBUFFER_FOR_SEND);
		mBUFFER_FOR_SEND = NULL;
	}
	if (mBUFFER_FOR_RECV != NULL)
	{
		GlobalFree( mBUFFER_FOR_RECV );
		mBUFFER_FOR_RECV = NULL;
	}

}

void MyUser::Send(BOOL tCheckValidBuffer, char* tBuffer, int tBufferSize, bool bUDPSend)
{
	int tSendValue01;
	int tNetworkMsg = 0;
	int tSendSize = 0;
	if (!mCheckConnectState)
	{
		return;
	}
	if (tCheckValidBuffer)
	{
		if ((ZONE_MAX_SEND_BUFFER_SIZE - mTotalSendSize) < tBufferSize)
		{
			__LogMgr()->WriteErrorToFile("Send Buffer Full, aName: %s", mAvatarInfo.aName);
			Quit();
			return;
		}
		if (mTotalSendSize < 0)
		{
			mTotalSendSize = 0;
		}
		memcpy(mBUFFER_FOR_SEND + mTotalSendSize, tBuffer, tBufferSize);
		mTotalSendSize += tBufferSize;
	}
	while (mTotalSendSize > 0)
	{
		tSendValue01 = send(mSocket, &mBUFFER_FOR_SEND[0], mTotalSendSize, 0);
		if (tSendValue01 == SOCKET_ERROR)
		{
			if (WSAGetLastError() == WSAEWOULDBLOCK)
			{
				return;
			}
			Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mTotalSendSize - tSendValue01) > 0)
		{
			MoveMemory(&mBUFFER_FOR_SEND[0], &mBUFFER_FOR_SEND[tSendValue01], (mTotalSendSize - tSendValue01));
		}
		mTotalSendSize -= tSendValue01;
		if (mTotalSendSize < 0)
		{
			mTotalSendSize = 0;
		}
	}
}

void MyUser::Quit(const char* tFileName, const char* tFuncName, int tLine)
{
	if (!mCheckConnectState)
	{
		return;
	}

	closesocket(mSocket);
	mSocket = -1;
	mCheckConnectState = FALSE;

	mTotalSendSize = 0;
	mTotalRecvSize = 0;

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if ((mCheckValidState) && (mMoveZoneResult == 0))
	{
		mCheckValidState = FALSE;
		if (strcmp(mAvatarInfo.aPartyName, "") != 0)
		{
			if (strcmp(mAvatarInfo.aPartyName, mAvatarInfo.aName) != 0)
			{
				tSort = 106;
				CopyMemory(&tData[0], &mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
				CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			}
			else
			{
				tSort = 109;
				CopyMemory(&tData[0], &mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
				tData[MAX_PARTY_NAME_LENGTH] = '\0';
				mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
			}
		}
		mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
		mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[0];
		mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[1];
		mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[mUserIndex].mDATA.aAction.aLocation[2];
		mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[mUserIndex].mDATA.aLifeValue;
		mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[mUserIndex].mDATA.aManaValue;
		mPLAYUSER_COM.U_UNREGISTER_USER_FOR_ZONE_SEND(mPlayUserIndex, &uID[0], &mAvatarInfo, &mAuthInfo);
	}
	mCheckValidState = FALSE;
	mAVATAR_OBJECT[mUserIndex].mCheckValidState = false;
	::memset(&mAvatarInfo, 0x00, sizeof(AVATAR_INFO));

	//__LogMgr()->Log("![%s] : %s : %s : %s : %d\n", tFuncName, mUSER[mUserIndex].uID, mUSER[mUserIndex].mIP, tFileName, tLine);
	__LogMgr()->QuitLog("![%s] : %s : %s : %s : %d\n", tFuncName, mUSER[mUserIndex].uID, mUSER[mUserIndex].mIP, tFileName, tLine);
}
bool MyUser::IsValidSkillNumber(int skillNumber)
{
	for (int index = 0; index < MAX_SKILL_SLOT_NUM; ++index) 
	{
		if (mAvatarInfo.aSkill[index][0] == skillNumber) 
		{
			return true;
		}
	}
	return false;
}
int MyUser::GetMaxSkillGradeNum(int skillNumber)
{
	for (int index = 0; index < MAX_SKILL_SLOT_NUM; ++index) 
	{
		if (mAvatarInfo.aSkill[index][0] == skillNumber) 
		{
			return mAvatarInfo.aSkill[index][1];
		}
	}
	return -1;
}