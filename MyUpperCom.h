#pragma once

#define MAX_SEND_DATA_SIZE											50000
#define MAX_RECV_DATA_SIZE											50000

class MyPlayUserCom
{
private:

	BOOL mCheckConnectState;
	int mZoneNumber;
	char mIP[16];
	int mPort;
	CRITICAL_SECTION m_lock;

	SOCKET mSocket;
	SOCKADDR_IN mAddress;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect(void);
	BOOL Send(void);
	BOOL Recv(void);
	void Close(void);

public:
	int mRecv_Result;
	int mRecv_PlayUserIndex;
	int mRecv_UserSort;
	AVATAR_INFO mRecv_AvatarInfo;
	int mRecv_EffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2];
	int mRecv_CheckFirstZone;
	int mRecv_ZoneNumber;
	int mRecv_Tribe;
	int mRecv_TribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM];
	int mRecv_Money;
	AUTH_INFO mRecv_AuthInfo;
	PROXYSHOP_INFO mRecv_Proxy;
	HERO_RANKING_INFO mRecv_HeroRank;
	int mRecv_HeroRankClaimState[4][10];

	MyPlayUserCom(void);

	BOOL Init(int tZoneNumber, char tIP[16], int tPort);
	void Free(void);

	BOOL ProcessForNetwork(void);

	void U_ZONE_OK_FOR_PLAYUSER_SEND(void);
	void U_REGISTER_USER_FOR_ZONE_0_SEND(char tID[MAX_USER_ID_LENGTH]);
	void U_REGISTER_USER_FOR_ZONE_1_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLogoutInfo[6]);
	void U_REGISTER_USER_FOR_ZONE_2_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO* tAuthInfo);
	void U_REGISTER_USER_FOR_ZONE_3_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], AUTH_INFO* tAuthInfo);
	void U_UNREGISTER_USER_FOR_ZONE_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH], AVATAR_INFO* tAvatarInfo, AUTH_INFO* tAuthInfo);
	void U_FIND_AVATAR_FOR_ZONE_SEND(char tAvatarName[MAX_AVATAR_NAME_LENGTH]);
	void U_TRIBE_BANK_INFO_SAVE_SEND(int tMoney[4]);
	void U_TRIBE_BANK_INFO_VIEW_SEND(int tTribe);
	void U_TRIBE_BANK_INFO_LOAD_SEND(int tTribe, int tTribeBankInfoIndex, int tInventoryMoney);
	void U_BLOCK_USER_FOR_ZONE_1_SEND(int tPlayUserIndex, char tID[MAX_USER_ID_LENGTH]);
	void U_CHECK_KILL_OTHER_TRIBE_SEND(char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH]);
	void U_REGISTER_PROXY_SHOP_INFO_SEND(char* tID, char* tAvatarName, int tSort, PROXYSHOP_INFO* tProxyInfo);
	void U_DEMAND_PROXY_SHOP_INFO_SEND(char* tID, char* tAvatarName);
	void U_ADD_USER_CASH_SEND(char* tID, int tAmount);
	void U_DEMAND_HERO_RANK_INFO_SEND(int tSort);
	void U_CHANGE_HERO_RANK_INFO_SEND(int tSort, char* tAvatarName, int tPoints, int tTribe);

};
extern MyPlayUserCom mPLAYUSER_COM;



class MyCenterCom
{
private:
	BOOL mCheckConnectState;
	int mZoneNumber;
	int mZonePort;
	char mIP[16];
	int mPort;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;
	CRITICAL_SECTION m_lock;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect(void);
	BOOL Send(void);
	void Close(void);

public:
	MyCenterCom(void);
	BOOL Init(int tZoneNumber, int tZonePort, char tIP[16], int tPort);
	void Free(void);
	int PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm);
	void W_WORLD_INFO(void);
	void W_ZONE_CONNECTION_INFO(void);
	void W_BROADCAST_INFO(void);
	void W_NOTICE(void);
	bool mIsUpdateCashItemInfo;
	bool IsUpdateCashItemInfo();
	void SetUpdateCashItemInfo(bool isUpdate);
	void W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(int updateResult);
	void W_UPDATE_CASH_ITEM_INFO_FOR_ZONE();

	BOOL ProcessForSend(void);

	void U_ZONE_OK_FOR_CENTER_SEND(void);
	void U_DEMAND_BROADCAST_INFO(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE]);

	int SearchAvatarforGM(const char* tAvatarName);
	void MoveZone(int tUserIndex, int tZoneNumber);
	void W_ZONE_OTHER_CONNECTION_INFO(int tZoneNumber);
};
extern MyCenterCom mCENTER_COM;



class MyRelayCom
{
private:
	BOOL mCheckConnectState;
	int mZoneNumber;
	char mIP[16];
	int mPort;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;
	CRITICAL_SECTION m_lock;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect(void);
	BOOL Send(void);
	void Close(void);

public:
	MyRelayCom(void);
	BOOL Init(int tZoneNumber, char tIP[16], int tPort);
	void Free(void);
	int PROCESS_FOR_NETWORK(HWND hWnd, WPARAM wPrm, LPARAM lPrm);
	void W_BROADCAST_DATA(void);
	BOOL ProcessForSend(void);
	void U_ZONE_OK_FOR_RELAY_SEND(void);
	void U_DEMAND_BROADCAST_DATA(int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE]);

};
extern MyRelayCom mRELAY_COM;



class MyExtraCom
{
private:
	BOOL mCheckConnectState;
	int mZoneNumber;
	char mIP[16];
	int mPort;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;
	CRITICAL_SECTION m_lock;

	char mSendData[MAX_SEND_DATA_SIZE];
	int mSendDataSize;
	char mRecvData[MAX_RECV_DATA_SIZE];
	int mRecvDataSize;

	BOOL Connect(void);
	BOOL Send(void);
	BOOL Recv(void);
	void Close(void);

public:

	int mRecv_Result;
	GUILD_INFO mRecv_GuildInfo;

	int mRecv_Cash;
	int mRecv_Cost;

	bool mIsValidCashItemInfo;
	int mCashItemInfoVersion;
	int mCashItemInfo[4][14][10][4];

	BOOL U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND(); 
	BOOL U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND();
	MyExtraCom(void);
	BOOL Init(int tZoneNumber, char tIP[16], int tPort);
	void Free(void);
	BOOL ProcessForNetwork(void);
	BOOL U_ZONE_OK_FOR_EXTRA_SEND(void);
	BOOL U_GUILD_WORK_FOR_EXTRA_SEND(int tSort, BYTE tData[MAX_GUILD_WORK_SIZE]);
	BOOL U_GET_CASH_SIZE_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH]);
	BOOL U_BUY_CASH_ITEM_FOR_EXTRA_SEND(char tID[MAX_USER_ID_LENGTH], int tCostInfoIndex, int iIndex, int iQuantity, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe, int tLevel, int tVersion);
};
extern MyExtraCom mEXTRA_COM;


class MyGameLog
{
private:
	BOOL mCheckConnectState;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;
	int mLogSort;
	char mGameLogData[MAX_GAMELOG_LENGTH];
	char mSendBuffer[(MAX_GAMELOG_LENGTH * 2)];


public:

	MyGameLog(void);

	BOOL Init(char tIP[16], int tPort);
	void Free(void);
	BOOL CheckValidState(int tUserIndex);

	void SendToLogServer(void);
	void SendToLogServerForDB(void);

	void GL_601_GM_CREATE_MONEY(int tUserIndex, int tValue);
	void GL_602_GM_CREATE_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_603_TRACE_USER(int tUserIndex, int tValue);
	void GL_604_BUY_CASH_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iCostSize, int iBonusCostSize);
	void GL_605_USE_CASH_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_606_USE_INVENTORY_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber);
	void GL_607_GAIN_SIN_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_608_IMPROVE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_609_PSHOP_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_610_QUEST_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_611_QUEST_MONEY(int tUserIndex, int tValue);
	void GL_612_QUEST_KILL_NUM(int tUserIndex, int tValue);
	void GL_613_QUEST_EXP(int tUserIndex, int tValue);
	void GL_614_QUEST_TEACHER_POINT(int tUserIndex, int tValue);
	void GL_615_TRADE_ITEM(int tUserIndex, int tOtherIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_616_TRADE_MONEY(int tUserIndex, int tOtherIndex, int tValue, int tValue2);
	void GL_617_GUILD_MONEY(int tUserIndex, int tValue, int tAction, int tGrade);
	void GL_618_TRIBE_MONEY(int tUserIndex, int tValue);
	void GL_619_GAIN_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_620_DROP_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_621_NSHOP_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_622_TRADESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_623_TRADESLOT_MONEY(int tUserIndex, int tAction, int tValue);
	void GL_624_STROESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_625_STORESLOT_MONEY(int tUserIndex, int tAction, int tValue);
	void GL_626_SAVESLOT_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_627_SAVESLOT_MONEY(int tUserIndex, int tAction, int tValue);
	void GL_628_GM_MONCALL(int tUserIndex, int tValue);
	void GL_629_GM_NCHAT(int tUserIndex, int tOtherIndex);
	void GL_630_GM_YCHAT(int tUserIndex, int tOtherIndex);
	void GL_631_GM_KICK(int tUserIndex, int tOtherIndex);
	void GL_632_GM_BLOCK(int tUserIndex, int tOtherIndex);
	void GL_633_MINUS_EXP_WITH_DIE(int tUserIndex, int tValue1, int tValue2);
	void GL_634_ADD_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_635_HIGH_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice, int tItem2);
	void GL_636_LOW_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice, int tItem2);
	void GL_637_EXCHANGE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_638_MAKE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_639_MAKE_SKILL(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_640_USER_CREATE_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_641_MAKE_TRIBE_WEAPON(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_642_N_PROTECT(int tUserIndex, int tValue);
	void GL_643_CHECK_MONSTER_ATTACK_PACKET(int tUserIndex);
	void GL_644_CHECK_AUTH_KEY(int tUserIndex);
	void GL_648_GM_GOD(int tUserIndex, int tValue);
	void GL_649_GM_CHAT(int tUserIndex);
	void GL_650_GM_UMOVE(int tUserIndex, int tOtherUserIndex, int tZone);
	void GL_651_GM_LEVEL(int tUserIndex, int tLevel);
	void GL_652_GM_ZNOTICE(int tUserIndex);
	void GL_653_GM_RES(int tUserIndex, int tOtherUserIndex, int tRes);
	void GL_654_GM_RENAME(int tUserIndex, int tOtherUserIndex, char* tName, char* tChangeName);
	void GL_655_GM_CALL(int tUserIndex, int tOtherUserIndex);
	void GL_656_GM_EXP(int tUserIndex, int tExp);
	void GL_657_GM_DIE(int tUserIndex, int tMonsterNumber);
	void GL_658_USE_INVENTORY_ITEM(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber, int tCount);
	void GL_659_AUTO_CHECK(int tUserIndex, int tType, float fValue, int iValue1 = 0, int iValue2 = 0);
	void GL_660_AUTO_CHECK(int tUserIndex);
	void GL_661_START_MISSION_LABYRINTH(void);
	void GL_662_END_MISSION_LABYRINTH(void);
	void GL_663_X_TRAP(int tUserIndex, unsigned long tErrCode);
	void GL_664_BONUS_CASH_FAIL_FOR_PACKAGE_ITEM(int tUserIndex, int iIndex, int failType);
	void GL_700_SPHINX_HACK(int tUserIndex);
	void GL_701_CHEAT_USER(int tUserIndex, int cheatSort);
	void GL_702_CHEAT_AVATAR_ACTION(int tUserIndex, int skillNum, int skillGrad1, int skillGrad2, int skillVal);
	void GL_800_USE_KILLNUM_TO_ITEM(int tUserIndex, int iBeforeKillOtherTribe, int iAfterKillOtherTribe);
	void GL_801_UPGRADE_AVATAR(int tUserIndex, int tValue01, int tValue02);
	void GL_802_USE_KILLOTHERTRIBE_TO_ITEM(int tUserIndex, int iBeforeKillOtherTribe, int iAfterKillOtherTribe);
	void GL_804_TRADESLOT_MONEY2(int tUserIndex, int tAction, int tValue);
	void CHAT_LOG_SEND(int tUserIndex, char* aName, char* Chat, char* Type);
	void GL_805_INVENSLOT_MONEY2(int tUserIndex, int tAction, int tValue);
	void GL_806_STORESLOT_MONEY2(int tUserIndex, int tAction, int tValue);
	void GL_807_SAVESLOT_MONEY2(int tUserIndex, int tAction, int tValue);
	void GL_808_ANIMAL_DELETE(int tUserIndex, int tAnimalNumber, int tAnimalExp, int tAnimalAbility);
	void GL_809_COSTUME_DELETE(int tUserIndex, int tCostumeNumber);
	void GL_810_DAILY_MISSION_REWARD(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tIndex, int tQuantity, int tValue, int tRecognitionNumber);
	void GL_811_REFINE_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int tPrice);
	void GL_812_SOCKET_ITEM(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iInvenSocket1, int iInvenSocket2, int iInvenSocket3);
	void GL_813_LEGEND_DIAMOND_INSERT(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber, int iInvenSocket1, int iInvenSocket2, int iInvenSocket3);
	void GL_814_IMPROVE_LEGEND_DECO(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_815_IMPROVE_ULTIMATE_PET(int tUserIndex, int tAction, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_816_BUY_BLOODSTAINED_SHOP(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_817_BUY_CAPSULE_STORE(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_818_DAILY_LOGIN(int tUserIndex, int tResultSort, int tWhatDay, int tCurrentClaimState);
	void GL_819_GEAR_BREAK(int tUserIndex, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_820_AMULET_TO_LEGEND_PET_UPGRADE(int tUserIndex, int tCraftSort, int iIndex, int iQuantity, int iValue, int iRecognitionNumber);
	void GL_CHAT_LOG(int tUserIndex, int tSort, MyUser* user_info, char* tContent);
};
extern MyGameLog mGAMELOG;



class MyChatLog
{
private:
	BOOL mCheckConnectState;
	SOCKET mSocket;
	SOCKADDR_IN mAddress;

public:
	MyChatLog(void);
	BOOL Init(char tIP[16], int tPort);
	void Free(void);

	void SendToLogServer(int tTribe, int tChatSort, char tAvatarName01[MAX_AVATAR_NAME_LENGTH], char tAvatarName02[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH]);

};
extern MyChatLog mCHATLOG;