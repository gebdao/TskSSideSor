#pragma once

class LEVELSYSTEM
{
private:
	float mGainExpInfoForKillOtherTribe[MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM];
	int mRangeForHigh[MAX_LIMIT_HIGH_LEVEL_NUM];
	LEVEL_INFO mDATA[MAX_LIMIT_LEVEL_NUM];


public:
	LEVELSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	int ReturnLevel(int tGeneralExperience);
	int ReturnLevelFactor1(int tLevel);
	int ReturnLevelFactor2(int tLevel);
	int ReturnLevelFactor3(int tLevel);
	int ReturnLevelFactorAttackPower(int tLevel);
	int ReturnLevelFactorDefensePower(int tLevel);
	int ReturnLevelFactorAttackSuccess(int tLevel);
	int ReturnLevelFactorAttackBlock(int tLevel);
	int ReturnLevelFactorElementAttack(int tLevel);
	int ReturnLevelFactorLife(int tLevel);
	int ReturnLevelFactorMana(int tLevel);
	int ReturnGainExpForKillOtherTribe(int tAttackLevel, int tDefenseLevel);
	int ReturnHighExpValue(int tLevel);
};
extern LEVELSYSTEM mLEVEL;


typedef struct
{
	int mDataNum;
	ITEM_INFO* mDATA;
	int mPartNum[MAX_LIMIT_LEVEL_NUM][MAX_ITEM_TYPE][MAX_ITEM_SORT]; 
	int* mPART[MAX_LIMIT_LEVEL_NUM][MAX_ITEM_TYPE][MAX_ITEM_SORT];
}
SHARED_ITEMSYSTEM;

class ITEMSYSTEM
{

private:
	int mDataNum;
	ITEM_INFO* mDATA;
	int mPartNum[MAX_LIMIT_LEVEL_NUM][MAX_ITEM_TYPE][MAX_ITEM_SORT];
	int* mPART[MAX_LIMIT_LEVEL_NUM][MAX_ITEM_TYPE][MAX_ITEM_SORT];

	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;
	BYTE* mSharedPostMem;
	SHARED_ITEMSYSTEM mSharedItemData;


public:
	ITEMSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	ITEM_INFO* Search(int iIndex);
	ITEM_INFO* Return(int iLevel, int iType, int iSort);
	ITEM_INFO* Return(int iLevel, int iType, int iSort, ITEM_INFO* tITEM_INFO);
	ITEM_INFO* Return_1(int iLevel, ITEM_INFO* tITEM_INFO);
	ITEM_INFO* Return_2(int iLevel, ITEM_INFO* tITEM_INFO);
	ITEM_INFO* ReturnRareItem(int iTribe, int iLevel);
	ITEM_INFO* ReturnRareItem(int iTribe, int iType, int iLevel);
	ITEM_INFO* GetResultItemPtrByGigabyteItem(void);
	ITEM_INFO* GetMoneyBy1WonLuckyBag(void);
	ITEM_INFO* GetPresentItemPtrByGoodwillAmbassador(int& iCounts);
	int ReturnItemForTransfer(int tItemIndex, int tNewWeaponType, int tNewTribe, int tOldTribe);
	int ReturnItemForTransfer2(int tItemIndex, int tNewTribe, int tOldTribe, int tSort);
	int ReturnLegendDecoStats(int tMode, int tEquipImproveValue);
	int ReturnDecoUpStat(int tSort, int tMode, int tImproveValue);
};
extern ITEMSYSTEM mITEM;



class SKILLSYSTEM
{

private:
	int mDataNum;
	SKILL_INFO* mDATA;

public:
	SKILLSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	SKILL_INFO* Search(int sIndex);
	int ReturnAttackType(int sIndex);
	int ReturnTotalHitNumber(int sIndex);
	float ReturnSkillValue(int sIndex, int sPoint, int sFactor);
	void ChangeSkillForTransfer(int tUserIndex, int tNewTribe);

};
extern SKILLSYSTEM mSKILL;



typedef struct
{
	int mDataNum;
	MONSTER_INFO* mDATA;
}
SHARED_MONSTERSYSTEM;

class MONSTERSYSTEM
{

private:
	int mDataNum;
	MONSTER_INFO* mDATA;
	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;
	BYTE* mSharedPostMem;
	SHARED_MONSTERSYSTEM mSharedMonsterData;

public:
	MONSTERSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	MONSTER_INFO* Search(int mIndex);
	MONSTER_INFO* Search(int tMonsterType, int tMonsterSpecialType);

};
extern MONSTERSYSTEM mMONSTER;




typedef struct
{
	int mDataNum;
	NPC_INFO* mDATA;
}
SHARED_NPCSYSTEM;

class NPCSYSTEM
{
private:
	int mDataNum;
	NPC_INFO* mDATA;
	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;
	BYTE* mSharedPostMem;
	SHARED_NPCSYSTEM mSharedNPCData;

public:

	NPCSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	NPC_INFO* Search(int nIndex);

};
extern NPCSYSTEM mNPC;



typedef struct
{
	int mDataNum;
	QUEST_INFO* mDATA;
}
SHARED_QUESTSYSTEM;

class QUESTSYSTEM
{
private:
	int mDataNum;
	QUEST_INFO* mDATA;
	DWORD mSharedMemSize;
	DWORD mSharedMemSizeForCheck;
	HANDLE mSharedMemMap;
	BYTE* mSharedPostMem;
	SHARED_QUESTSYSTEM mSharedQuestData;


public:
	QUESTSYSTEM(void);
	BOOL Init(char* tFileName);
	void Free(void);
	BOOL CheckValidElement(int tArrayIndex);
	QUEST_INFO* Search(int qTribe, int qStep);

};
extern QUESTSYSTEM mQUEST;



class PATSYSTEM
{
public:
	int mMaxRangeValue[8];


	PATSYSTEM(void);
	BOOL Init(void);
	void Free(void);
	float ReturnGrowStep(int pIndex, int pGrowUpValue);
	float ReturnGrowPercent(int pIndex, int pGrowUpValue);
	float ReturnAttackPower(int pIndex, int pGrowUpValue, int pActivityValue);
	float ReturnDefensePower(int pIndex, int pGrowUpValue, int pActivityValue);
	float ReturnLifeValue(int pIndex, int pGrowUpValue);
	float ReturnManaValue(int pIndex, int pGrowUpValue);
	int ReturnAdditionalDamagePower(int pIndex, int pGrowUpValue, int pActivityValue);
	float ReturnAmuletHP(int tPetIndex);
	float ReturnAmuletPetMP(int tPetIndex);
	int ReturnAmuletPetability1(int tAmuletIndex, int tAmuletExp, int tMode);
	float ReturnAmuletPetability3(int tAmuletIndex, int tAmuletExp, int tMode);
	float ReturnLegendPetHPStat(int tPetIndex);
	float ReturnLegendPetMPStat(int tPetIndex);
	int ReturnPetAddSkillPoint(int tPetIndex, int tGrowUpValue, int tSkillMode);
	float ReturnPetAddSkillPoint2(int tSort1, int tSort2, int tPetIndex, int tPetGrowState);

};
extern PATSYSTEM mPAT;

class SOCKETSYSTEM
{
public:
	SOCKET_INFO* mDATA;

	BOOL Init(char* tFileName);
	int GetSocketInfo(int tSort, int tSocket1, int tSocket2, int tSocket3);
	int SetSocketNum(int tSort, int tSocketType, int tSocketValue);
	SOCKET_INFO* Return(int sGemMode, int sGemLevel);
};
extern SOCKETSYSTEM mSOCKET;
