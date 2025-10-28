#pragma once

class MyUser
{
public:
	int mUserIndex;

	BOOL mCheckConnectState;
	BOOL mCheckValidState;

	DWORD mConnectTime;
	SOCKET mSocket;
	char mIP[16];

	char mPacketEncryptionValue[2];

	char* mBUFFER_FOR_SEND;
	int mTotalSendSize;
	char* mBUFFER_FOR_RECV;
	int mTotalRecvSize;

	BOOL mCheckTempRegister;
	int mTempRegisterTribe;
	DWORD mRegisterTime;
	int mPlayUserIndex;
	char uID[MAX_USER_ID_LENGTH];
	int uUserSort;
	int uGoodFellow;
	int uLoginPlace;
	int uLoginPremium;
	int uLoginPremiumPCRoom;
	int uTraceState;
	char uBonus100Money;
	int uPremiumServerExpirationDate;
	AVATAR_INFO mAvatarInfo;
	int mEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	float mGeneralExperienceUpRatio;
	float mItemDropUpRatio;
	float mGeneralExperienceDownRatio;
	float mSelfPatExperienceUpRatio;
	int mSupportSkillTimeUpRatio;

	DWORD mTickCountFor01Second;
	DWORD mTickCountFor01SecondForProtect;
	DWORD mTickCountFor30Second;
	DWORD mTickCountFor01Minute;

	DWORD mTickForAttackSpeed;

	DWORD mTickCountFor01Minute_2;
	DWORD mTickCountFor03Second;
	DWORD mUniqueNumber;
	int mCheckMaxAttackPacketNum;
	int mMaxAttackPacketNum;
	int mNowAttackPacketNum;
	int mMoveZoneResult;
	AUTH_INFO mAuthInfo;
	int mAttackPacketSort;
	int mHeartCheckCount;
	time_t mHeartCheckTime;

#ifdef __WREGION__
	int monsterforspawn;
#endif


	MyUser(void);

	BOOL Init(int tUserIndex, int tSendBufferSize, int tRecvBufferSize);
	void Free(void);
	void Send(BOOL tCheckValidBuffer, char* tBuffer, int tBufferSize, bool bUDPSend = false);
	void Quit(const char* tFileName = __FILE__, const char* tFuncName = NULL, int tLine = __LINE__);

	bool mIsValidCashItemInfo;

	bool IsValidSkillNumber(int skillNumber);
	int GetMaxSkillGradeNum(int skillNumber);
};
extern MyUser* mUSER;