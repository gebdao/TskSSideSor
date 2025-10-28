#pragma once

#include "../include/zlib.h"

class AVATAR_OBJECT;
class MyGame
{
	unsigned int getCriticalAttackDefValue(AVATAR_OBJECT* _attacker, AVATAR_OBJECT* _defenser);

public:
	ZONE_CONNECTION_INFO mZoneConnectionInfo;

	WORLD_INFO mWorldInfo;
	TRIBE_INFO mTribeInfo;
	TOWER_INFO mTowerInfo;
	BLOODSTAINEDSHOP_INFO mBSInfo;
	FACTION_TRAP mFactionTrap;

	int mAutoCheckAnswer1;
	int mAutoCheckAnswer2;
	int mAutoCheckDataSize;
	BYTE mAutoCheckData[1000];

	float mGeneralExperienceUpRatio;
	float mItemDropUpRatio;
	float mItemDropUpRatioForMyoung;
	int mKillOtherTribeAddValue;
	int mKillOtherTribeUpValue;

	int mTeacherPointUpRatio;
	float mPatExperienceUpRatio;
	float mBonusGainGeneralExperienceUpRatio;
	int mGeneralExperienceDownRatio;
	int mKillOtherTribeExperienceUpRatio;

	SELL_ITEM_INFO mSellItemInfo[MAX_SELL_ITEM_INFO_NUM];

	DWORD mAvatarObjectUniqueNumber;
	DWORD mMonsterObjectUniqueNumber;
	DWORD mItemObjectUniqueNumber;
	int mAvatarDuelUniqueNumber;
	DWORD mAvatarPShopUniqueNumber;

	DWORD mTickCount;

	DWORD mUpdateTimeForTribeBankInfo;
	int mTribeBankInfo[4];

	float mSymbolDamageUp[4];
	float mSymbolDamageDown[4];

	BOOL mCheckActiveBattleLogic;

	BOOL mCheckTribeVoteServer;

	BOOL mCheckAllienceServer;
	DWORD mAlliencePostTick;
	BYTE mAllienceBattleState;
	int mAllienceRemainTime;
	float mAllienceBattlePostLocation[2][3];
	float mAllienceBattlePostRadius[2];
	int mAlliencePostAvatarIndex[2];
	DWORD mAlliencePostAvatarUniqueNumber[2];
	int mAlliencePostAvatarTribe[2];

	BOOL mCheckZone037Server;
	DWORD mZone037PostTick;
	BYTE mZone037BattleState;
	int mZone037RemainTime;

	BOOL mCheckZone124Server;

	BOOL mCheckZone071TypeServer;
	int mZone071TypeZoneIndex;

	BOOL mCheckZone049TypeServer;
	int mZone049TypeZoneIndex;
	DWORD mZone049TypePostTick;
	BYTE mZone049TypeBattleState;
	int mZone049TypeRemainTime1;
	int mZone049TypeRemainTime2;
	int mZone049TypeBattleResult[4];

	BOOL mCheckZone051TypeServer;
	int mZone051TypeZoneIndex;
	DWORD mZone051TypePostTick;
	BYTE mZone051TypeBattleState;
	int mZone051TypeRemainTime;

	BOOL mCheckZone053TypeServer;
	int mZone053TypeZoneIndex;
	DWORD mZone053TypePostTick;
	BYTE mZone053TypeBattleState;
	int mZone053TypeRemainTime;
	float mZone053TypeBattlePostLocation[3];
	float mZone053TypeBattlePostRadius;
	int mZone053TypePostAvatarIndex;
	DWORD mZone053TypePostAvatarUniqueNumber;
	DWORD mZone053TypeSaveTick;

	BOOL mCheckZone038Server;
	DWORD mZone038PostTick;
	BYTE mZone038BattleState;
	int mZone038RemainTime;
	float mZone038BattlePostLocation[3];
	float mZone038BattlePostRadius;
	int mZone038PostAvatarIndex;
	DWORD mZone038PostAvatarUniqueNumber;

	BOOL mCheckZone039TypeServer;
	DWORD mZone039TypePostTick;
	BYTE mZone039TypeBattleState;

	BOOL mCheckZone101TypeServer;
	BOOL mCheckZone125Server;
	BOOL mCheckZone126TypeServer;
	BOOL mCheckZone175TypeServer;

	BOOL mCheckZone88TypeServer;
	DWORD mZone88PostTick;
	int mZone88BattleState1;
	int mZone88BattleState2;
	int mZone88RemainTime1;
	float mZone88BattlePostLocation[3];
	float mZone88BattlePostRadius;
	int mZone88PostAvatarIndex;
	DWORD mZone88PostAvatarUniqueNumber;

	bool mCheckZoneDuelTypeServer;
	bool mCheckZoneAllDuelTypeServer;
	bool mCheckZone084TypeServer;

	int mZone175TypeZoneIndex1;
	int mZone175TypeZoneIndex2;
	DWORD mZone175TypePostTick;
	BYTE mZone175TypeBattleState;
	int mZone175TypeRemainTime;

	BOOL mCheckZone194Server;
	DWORD mZone194PostTick;
	BYTE mZone194BattleState;
	int mZone194RemainTime1;
	int mZone194RemainTime2;
	int mZone194BattleResult[4];

	BOOL mCheckZone195TypeServer;
	DWORD mZone195PostTick;
	BYTE mZone195BattleState;
	int mZone195RemainTime;
	float mZone195BattlePostLocation[3];
	float mZone195BattlePostRadius;
	int mZone195PostAvatarIndex;
	DWORD mZone195PostAvatarUniqueNumber;
	int mZone195LevelState;

	BOOL mCheckZone200TypeServer;
	DWORD mZone200PostTick;
	BYTE mZone200BattleState;
	int mZone200RemainTime1;
	int mZone200RemainTime2;
	int mZone200ZoneIndex;
	int mZone200MonsterCount[4];

	BOOL mCheckZone241TypeServer;
	DWORD mZone241PostTick;
	int mZone241Type;
	BYTE mZone241BattleState[12];
	int mZone241RemainTime;
	int mZone241PostAvatarIndex;
	DWORD mZone241PostAvatarUniqueNumber;

	BOOL mCheckZone267TypeServer;
	int mZone267TypeZoneIndex;
	DWORD mZone267TypePostTick;
	BYTE mZone267TypeBattleState;
	int mZone267TypeRemainTime1;
	int mZone267TypeRemainTime2;
	int mZone267TypeBattleResult[4];

	BOOL mCheckZone319TypeServer;
	int mZone319TypeZoneIndex;
	DWORD mZone319TypePostTick;
	BYTE mZone319TypeBattleState;
	int mZone319TypeRemainTime1;
	int mZone319TypeRemainTime2;
	int mZone319TypeBattleResult[4];

	bool mCheckZone295Server;
	bool mCheckZone295TypeServer;
	bool mCheckZone296TypeServer;
	int mZone296TypeBattleResult[4];
	int mZone295TypeBattleResult[4];

	bool bAttackMonsterSymbol;
	DWORD dwAttackMonsterSymbolTime;

	BOOL mDuel_124;
	int mDuel_124_RemainTime;
	int mDuel_124_AvatarNum[2];
	BOOL mDuel_124_Pvp;

	int mZone84Time;

	int mPremiumExpirationCountDownDate;  
	int mPremiumServerExpirationCountDown;

///	int mTreasureHunterEventState; ////Saigo monsters////
	int mHappyHourEventState;	   // Happy Hour Increase CP Event
	int mYanggokEventState;////Yanggok monsters///
	int mKillOtherTribeAddValueOriginal;

	// Special Shop
	int tSpecialShop[3][28];

	MyGame(void);

	BOOL Init(void);
	void Free(void);

	BOOL Decompress(DWORD tCompressSize, BYTE* tCompress, DWORD tOriginalSize, BYTE* tOriginal);

	BOOL LoadForItemMoneyInfo(void);
	int ReturnBigTribe(void);
	void Process_Zone_194(void);
	void Process_Zone_195(void);
	void Process_Zone_200(void);
	void Process_Zone_241(void);
	void Process_Zone_267(void);
	void Process_Zone_319_TYPE(void);
	void ReturnLevelWarReward3(int tLevel1, int tLevel2, int* tGainExperience, int* tGainMoney);
//	void ProcesForTreasureHunterEvent();////Saigo monsters////
	void ProcessforYanggokBoss();////Yanggok monsters///
	void ProcessForValidAvatarInfoWithItem(AVATAR_INFO* tAvatarInfo);

	void Logic(float dTime);

	int ReturnTribeRole(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe);
	int ReturnTribeSubMasterNum(int tTribe);

	void AddTribeBankInfo(int tTribe, int tMoney);
	BOOL LoadBloodStainedShopInfo();

	BOOL LoadSpecialShop();

	int TowerSystemEffect(int tType, int tTribe);

	int ReturnTribeForSymbol(int tTribe);
	int ReturnAllianceTribe(int tTribe);

	int ReturnTribePointWithAlliance(int tTribe);
	int CheckPossibleChangeToTribe4(int tTribe);
	int CheckPossibleChangeToTribe4_2(int tTribe);
	BOOL CheckSmallTribeForAdvantage(int tTribe);
	int ReturnSmallTribe(void);

	void AdjustSymbolDamageInfo(void);
	float ReturnSymbolDamageUp(int tTribe);
	float ReturnSymbolDamageDown(int tTribe);

	void ProcessForGuardState(void);

	void Process_TribeVote_Server(void);
	void Process_Allience_Server(void);
	void Process_Zone_037(void);
	void Process_Zone_88(void);
	void Process_Zone_124(void);
	void Process_Zone_071_TYPE(void);
	void Process_Zone_049_TYPE(void);
	void Process_Zone_051_TYPE(void);
	void Process_Zone_053_TYPE(void);
	void GetLevelBattleRewardInfo(int tLevel1, int tLevel2, int* tGainExperience, int* tGainMoney, BOOL tWin);
	void Process_Zone_038(void);
	void Process_Zone_039_TYPE(void);
	void Process_Zone_175_TYPE(void);
	void GetZone175TypeRewardInfo(int tLevel, int tLevel2, int tStep, int* tGainExperience, int* tGainMoney);

	void ProcessForBroadcastInfo(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE]);

	BOOL CheckPossibleAttackTarget(int tTargetSort, int tActionSort);

	void ProcessAttack01(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
	void ProcessAttack02(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
	void ProcessAttack03(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
	void ProcessAttack04(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
	void ProcessAttack05(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
	void ProcessAttack06(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);

	void CheckUpdateCashItemInfo();

	int ReturnAlliance(int tTribe);
	int CheckMoveZoneForMoveZoneItem(int tTribe, int tLevel, int tZoneNumber);
};
extern MyGame mGAME;

#define UNIT_SCALE_RADIUS1 1 // 브로드 캐스팅 범위 (MAX_RADIUS_FOR_NETWORK * 1)
#define UNIT_SCALE_RADIUS2 2 // 브로드 캐스팅 범위 (MAX_RADIUS_FOR_NETWORK * 2)
#define UNIT_SCALE_RADIUS3 3 // 브로드 캐스팅 범위 (MAX_RADIUS_FOR_NETWORK * 3)



class MyUtil
{

private:
	int mEquipPart[MAX_EQUIP_SLOT_NUM];

public:
	MyUtil(void);

	BOOL CheckNameString(char* tString);

	BOOL CheckOverMaximum(int tValue1, int tValue2);

	int ReturnFixedLevel(int tLevel);

	BOOL CheckPossibleEquipItem(int iIndex, int tTribe, int tEquipIndex, int tLevel, int tRebirthLevel);

	void ProcessForExperience(int tUserIndex, int tGainGeneralExperience, int tGainPatExperience, int tGainLifeValue);
	BOOL ProcessForDropItem(int tDropSort, int tItemIndex, int tItemQuantity, int tItemValue, int tItemRecognitionNumber, float tLocation[3], char tMaster[MAX_AVATAR_NAME_LENGTH], char tPartyName[MAX_AVATAR_NAME_LENGTH], int tPartyState, int tTribe, int tSocket[MAX_SOCKETSYSTEM_ARRAY]);

	void Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, bool bUDPSend = true, int type = 1);
	void Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, int tUserIndexForNoSend, bool bUDPSend = true, int type = 1);

	float RandomNumber(float tMinValue, float tMaxValue);
	int RandomNumber(void);

	BOOL CheckInRange(float tLocation01[3], float tLocation02[3], float tDistance);

	float GetLengthXYZ(float tLocation01[3], float tLocation02[3]);
	float GetDoubleXYZ(float tLocation01[3], float tLocation02[3]);
	float GetLengthX_Z(float tLocation01[3], float tLocation02[3]);
	float GetDoubleX_Z(float tLocation01[3], float tLocation02[3]);

	float GetYAngle(float x1, float z1, float x2, float z2);

	int ReturnItemRecognitionNumber(int tItemType);

	int ReturnNowDate(void);
	int ReturnAddDate(int tPostDateValue, int tAddDayValue);
	int ReturnSubDate(int tPostDateValue, int tSubDayValue);

	int ReturnVoteDate(void);

	int ReturnISValue(int tValue);
	int ReturnRFValue(int tValue);
	int Return4thValue(int tValue);
	int ReturnFirstStatValue(int tValue);
	int ReturnSecondStatValue(int tValue);
	int ReturnThirdStatValue(int tValue);
	int ReturnCapeStatValue(int tValue);
	int ReturnIUValue(int tValue);
	int ChangeISValue(int tValue, int tISValue);
	int SetISValue(int tValue, int tISValue);
	int ChangeRefineValue(int tValue, int tRFValue);
	int Change4thValue(int tValue, int t4thValue);
	int ChangeAmuletFirstStat(int tValue, int tFirstStatValue);
	int ChangeAmuletSecondStat(int tValue, int tSecondStatValue);
	int ChangeAmuletThirdStat(int tValue, int tThirdStatValue);
	int ChangeCapeStat(int tValue, int tStat);
	int ChangeIUValue(int tValue, int tIUValue);
	int SetISIUValue(int tISValue, int tIUValue);
	int ReturnIUEffectValue(ITEM_INFO* tITEM_INFO, int tEffectSort);
	int ReturnISValueWithLevelLimit(int tLevel, int tISValue);
	int ReturnIUValueWithLevelLimit(int tLevel, int tIUValue);

	void ProcessForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber);
	void DropItemForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber);
	void DropItemForSpecialZones(int tUserIndex, int tOtherIndex, int tZoneNumber);
	void DropItemForSpecialZonesKillOtherInWar(int tUserIndex, int tOtherIndex, int tZoneNumber);

	int SearchAvatar(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tInvalidIndex);

	bool FindEmptyInvenForItem(int iUserIndex, ITEM_INFO* pItem, int& iPage, int& iIndex);
	bool SetInvenSlotHumanReadable(int iUserIndex, int iPage, bool bInvenSlots[MAX_INVENTORY_SLOT_NUM]);
	int GetEmptyInvenSlotIndex(int iUserIndex, int iPage);
	BOOL CheckIfEmptyHPPills(int tUserIndex);
	BOOL CheckIfEmptyMPPills(int tUserIndex);
	BOOL GetEmptyHotKeyPage(int tUserIndex);
	BOOL GetEmptyHotKeyIndex(int tUserIndex);
	int GetInventoryHPPillPage(int tUserIndex);
	int GetInventoryHPPillIndex(int tUserIndex);
	int GetInventoryMPPillPage(int tUserIndex);
	int GetInventoryMPPillIndex(int tUserIndex);
	int GetInventoryHPPillQuantity(int tUserIndex);
	int GetInventoryMPPillQuantity(int tUserIndex);
	int ReturnHealthState(int tPlayTime);
	BOOL ProcessForChange(int tUserIndex);
	bool CheckInvenForItem(int* tUserIndex, ITEM_INFO* pItem, int* tPage, int* tIndex, int* tXPost, int* tYPost);
	int GetAttackRadius(int tSkillNumber);
	bool CheckRAttackRange(int tUserIndex, int tSkillNumber, float tLocation1[3], float tLocation2[3], float tObjectSize);
	float ReturnLengthXYZ(float tLocation01[3], float tLocation02[3]);
	int CheckPVNumber(int tTribe);
	int GetRandomGachaItem();
	int ReturnAmuletStats2(int tUserIndex, int AmuletStats, int WhatSkill);
	double ReturnPetAddSkillPoint2(int Mode1, int Mode2, int tPetIndex, int tPetGrowState);
	int ReturnCapeAbility(int tCapeIndex, int tCapeImprove, int tMode);
	int SetSocketValue(int tValue, int WhatByte, int tISValue);
	int ReturnMemoryValue(int tValue, int WhatByte);
	int ChangeMemoryValue(int tValue, int WhatByte, int tNewValue);
	int ReturnMountAbsorbAddStat(int tAnimalNumber);
	int SetEliteAnimalAbility(int tSort);
	float ReturnEliteMountStats(int tStatType, int tAnimalExpActivity);
	int ReturnItemSort(ITEM_INFO* t);
	int ReturnItemSort(int tItemIndex);
	int GetWarlordSetState(int tUserIndex);
	BOOL Set1Rare(int a1, int a2);
	BOOL Set2Rare(int a1, int a2);
	BOOL Set3Rare(int a1, int a2, int a3);
	BOOL Set4Rare(int a1, int a2);
	BOOL Set5Rare(int a1, int a2, int a3, int a4, int a5, int a6);
	BOOL Set1Elite(int a1, int a2);
	BOOL Set2Elite(int a1, int a2);
	BOOL Set3Elite(int a1, int a2);
	BOOL Set4Elite(int a1, int a2, int a3, int a4);
	BOOL Set5Elite(int a1, int a2, int a3, int a4, int a5, int a6);
	BOOL HeroSet1(int a1, int a2, int a3, int a4, int a5, int a6);
	BOOL HeroSet2(int a1, int a2, int a3, int a4, int a5, int a6);
	BOOL IsWarlord(int a1);
	int ReturnEngraveStats(int tItemSort, int tItemIndex, int tImproveValue, int tSort);
	int ReturnMountSort(int aAnimalNumber);
	int GetTowerSort(int iType, int iIndex);
	float ReturnRageDmgUp(int a1);
	void GetGMTimeNow(int tUserIndex);
	int GetPetMaxExpCapacity(int pIndex);
	BOOL CheckAnimalExpMaximum(int AnimalExp, int ToAdd);
	void BroadcastGameEvent(int tSort, int tUserIndex, int tItemIndex);
	int ReturnUpgradeValueWithLevelLimit(int tLevel, int tUpgradeValue);
	BOOL CheckChangeTribeTime(void);
	BOOL CheckActiveSpecialSkill(int tUserIndex, int tSort, int tSkillIndex);
	BOOL CheckSpecialSkillState(int tUserIndex, int tSort, int tItemIndex, int tSkillIndex, int tMonsterSort, int tMonsterIndex, DWORD tMonsterUniqueNumber);
	int ReturnSortForUltEnchant(int tItemIndex);
	int ReturnMaterialForEngrave(int tItemIndex);
	int ReturnTowerSort(int tZoneNumber);
	void ReturnMountExp(int tMountExpIndex, int* tMountFeed, int* tMountExp);
	void SetMountExp(int tFeed, int tExp, int* tResult);
	int ProcessForMountExp(int tAnimalExp, int ToAdd);
	BOOL TowerMapToTribeIndex(int tZoneNumber, int tTribe);
	BOOL WorkForTowerBuild(int tUserIndex, int tWhatTower);
	int GetSocketAbility(int tSocket1, int tSocket2, int tSocket3, int* s1, int* s2, int* s3, int* s4, int* s5);
	void GetAnimalAbilities(int tAnimalAbility, int* s1, int* s2, int* s3, int* s4, int* s5, int* s6, int* s7, int* s8);
	BOOL ReturnWineState(int tUserIndex, int tWine);
	int ReturnSetItemIUValue_AttackPower(int tIndex, int tIUValue, int tSort);
	int ReturnSetItemIUValue_DefensePower(int tIndex, int tIUValue, int tSort);
	int ReturnSetItemIUValue_AttackSuccess(int tIndex, int tIUValue, int tSort);
	int ReturnSetItemIUValue_AttackBlock(int tIndex, int tIUValue, int tSort);
	int ReturnSetItemIUValue_ElementAttackPower(int tIndex, int tIUValue, int tSort);
	int ReturnSetItemIUValue_ElementDefensePower(int tIndex, int tIUValue, int tSort);
	int ReturnSet3ItemIUValue_AttackPower(int tIUValue);
	float GetRandomFloat();
	int GetRandomInt(int tNumber);
};
extern MyUtil mUTIL;




class AVATAR_OBJECT
{
private:
	ITEM_INFO* mEquipItem[MAX_EQUIP_SLOT_NUM];
	int mEquipValue[MAX_EQUIP_SLOT_NUM];

	int mMaxLife;
	int mMaxMana;
	int mAttackPower;
	int mDefensePower;
	int mAttackSuccess;
	int mAttackBlock;
	int mElementAttackPower;
	int mElementDefensePower;
	int mCritical;
	int mCriticalDefense;
	int mLastAttackBonusProbability;
	float mLastAttackBonusValue;
	int mLuck;
	int mSpiritDamage;
	int mSpiritDefense;

public:
	int mIndex;

	BOOL mCheckValidState;
	DWORD mUniqueNumber;

	OBJECT_FOR_AVATAR mDATA;

	BOOL mCheckPossibleEatPotion;

	PSHOP_INFO mPShopInfo;

	int mDuelProcessState;
	char mDuelProcessAvatarName[MAX_AVATAR_NAME_LENGTH];
	int mDuelProcessSort;
	int mDuelProcessRemainTime;
	int mTradeProcessState;
	char mTradeProcessAvatarName[MAX_AVATAR_NAME_LENGTH];
	int mTradeProcessMenu;
	int mFriendProcessState;
	char mFriendProcessAvatarName[MAX_AVATAR_NAME_LENGTH];
	int mPartyProcessState;
	char mPartyProcessAvatarName[MAX_AVATAR_NAME_LENGTH];
	int mGuildProcessState;
	char mGuildProcessAvatarName[MAX_AVATAR_NAME_LENGTH];
	int mTeacherProcessState;
	char mTeacherProcessAvatarName[MAX_AVATAR_NAME_LENGTH];

	int mSPACE_INDEX[3];

	BOOL mCheckDeath;
	int mCheckCount;
	float mPRE_LOCATION[3];
	DWORD mUpdateTimeForBroadcast;
	int mGod;
	int mChat;
	DWORD mFishPreTime;
	BOOL mFishReel;

	void Init(void);
	void SetSpaceIndex(void);

	void SetBasicAbilityFromEquip(void);

	int GetWeaponClass(void);
	int GetWeaponType(void);
	int GetWeaponTypeForTransfer(int tNewTribe);
	int GetMaxLife(void);
	int GetMaxMana(void);
	int GetAttackPower(void);
	int GetDefensePower(void);
	int GetAttackSuccess(void);
	int GetAttackBlock(void);
	int GetElementAttackPower(void);
	int GetElementDefensePower(void);
	int GetCritical(void);
	int GetCriticalDefense(void);
	int GetLastAttackBonusProbability(void);
	float GetLastAttackBonusValue(void);
	int GetLuck(void);
	int GetSpiritDamage();
	int GetSpiritDefense();
	int GetBonusSkillValue(int sIndex);
	int GetReduceManaRatio(void);
	int GetCallVitality();
	int GetCallStrength();
	int GetCallKi();
	int GetCallWisdom();
	float ReturnCriticalUp();
	int ReturnVitalityUp();
	int ReturnStrengthUp();
	int ReturnWisdomUp();
	int ReturnKiUp();
	float ReturnCriticalDefenceUp();
	int ReturnLifeUp(int tUserIndex);
	int ReturnSetItemIUValue_LifeUp(AVATAR_INFO* tAVATAR);
	BOOL CheckCommunityWork(void);
	void Update(float tPostTime);
	void ProcessForCreateEffectValue(ACTION_INFO* tAction);
	void ProcessForDeleteEffectValue(void);
	void ProcessForDeath(void);
	void ProcessForTradeInfo(void);
	int ReturnQuestPresentState(void);
	int ReturnQuestEndConditionState(void);
	int ReturnQuestNextNPCNumber(void);
	int ReturnItemNumberForQuestReward(void);
	int ReturnItemQuantityForQuestReward(void);
	int SummonQuestBoss(void);
	int ChangeQuestItem(int tItemNumber1, int tItemNumber2);
	int DeleteQuestItem(int tItemNumber);
	int IsUsedOrnament(void);
	void AutoBuff(int tCheckMotion);
	void AutoHuntBuff();
	void AutoBuffStart(ACTION_INFO* pAction);
	BOOL CheckIfSpeedHack(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo);
};
extern AVATAR_OBJECT mAVATAR_OBJECT[MAX_AVATAR_OBJECT_NUM];




class MONSTER_OBJECT
{

private:
	int SelectAvatarIndexForPossibleAttack(void);
	void SelectAvatarIndexForPossibleAttackForZone175TypeBoss(void);
	int SelectAvatarIndexForIdleAI(void);
	void AdjustValidAttackTarget(void);
	void AdjustValidAttackTargetForZone175TypeBoss(void);
	int SelectAvatarIndexForAttackAction(void);
	int SelectAvatarIndexForGuardAttack(void);
	int SelectAvatarIndexForIdleAIWIthThrowCar(void);
	int SelectAvatarIndexForThrowCarAttack(void);

	void A001(int tObjectIndex, float tPostTime);
	void A002(int tObjectIndex, float tPostTime);
	void A002_FOR_ZONE_175_TYPE_BOSS(int tObjectIndex, float tPostTime);
	void A004(int tObjectIndex, float tPostTime);
	void A005(int tObjectIndex, float tPostTime);
	void A005_FOR_ZONE_175_TYPE_BOSS(int tObjectIndex, float tPostTime);
	void A006(int tObjectIndex, float tPostTime);
	void A008(int tObjectIndex, float tPostTime);
	void A009(int tObjectIndex, float tPostTime);
	void A013(int tObjectIndex, float tPostTime);
	void A020(int tObjectIndex, float tPostTime);

public:
	BOOL mCheckValidState;
	DWORD mUniqueNumber;

	OBJECT_FOR_MONSTER mDATA;

	int mSPACE_INDEX[3];

	MONSTER_INFO* mMONSTER_INFO;
	int mSameTargetPostNum;

	DWORD mInvalidTimeForSummon;

	DWORD mCheckFirstLocationTime;
	float mFirstLocation[3];

	float mRadiusForSize;

	DWORD mCheckDetectEnemyTime;

	BOOL mCheckAttackState;
	int mTotalAttackNum;
	char mAvatarName[MAX_AVATAR_NAME_LENGTH]; 
	int mAttackIndex[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD mAttackUniqueNumber[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD mAttackDamage[MAX_MONSTER_OBJECT_ATTACK_NUM];
	float mAttackLength[MAX_MONSTER_OBJECT_ATTACK_NUM];

	DWORD mUpdateTimeForBroadcast;

	int mLastAttackUserIndex;
	DWORD mLastAttackUniqueNumber;
	int mLastAttackUserTribe;
	char mLastAttackUserName[MAX_AVATAR_NAME_LENGTH];

	int mSpecialSortNumber;

	BOOL mCheckFirstAttackForTribeSymbol;
	DWORD mFirstAttackTimeForTribeSymbol;
	DWORD mTribeDamageForTribeSymbol[4];

	BOOL mCheckFirstAttackForAllianceStone;
	DWORD mFirstAttackTimeForAllianceStone;

	BOOL mCheckAttackPacketRecv;
	DWORD mAttackPacketRecvTime;

	// New
	int mAttackCheckForSlowMobs; // Protect for Slow Mob/God Mode

	void SetSpaceIndex(void);
	void Update(int tObjectIndex, float tPostTime);
	void SetAttackInfoWithAvatar(int tServerIndex, DWORD tUniqueNumber, int* tWhoAttackMonster);
	int SelectAvatarIndexForMaxAttackDamage(void);
	void ProcessForDropItem(int tUserIndex);
	void ProcessForDropItem(int tUserIndex, int tMonsterIndex);
};
extern MONSTER_OBJECT mMONSTER_OBJECT[MAX_MONSTER_OBJECT_NUM];



class ITEM_OBJECT
{

public:
	BOOL mCheckValidState;
	DWORD mUniqueNumber;

	OBJECT_FOR_ITEM mDATA;

	int mSPACE_INDEX[3];

	ITEM_INFO* mITEM_INFO;

	DWORD mUpdateTimeForBroadcast;

	void SetSpaceIndex(void);

	void Update(int tObjectIndex);

	BOOL CheckPossibleGetItem(int tUserIndex);
};
extern ITEM_OBJECT mITEM_OBJECT[MAX_ITEM_OBJECT_NUM];



class PROXY_SHOP_OBJECT
{
public:
	BOOL mCheckValidState;
	DWORD mUniqueNumber;
	int mProxyUserIndex;
	char mProxyShopAvatarName[MAX_AVATAR_NAME_LENGTH];
	char mProxyShopName[MAX_PSHOP_NAME_LENGTH];
	char mID[MAX_USER_ID_LENGTH];
	float mProxyShopLocation[3];

	void Free();
	int GetProxyIndex(char* tAvatarName);
	int GetProxyIndex2(char* tID, char* tAvatarName);
	BOOL CheckIfProxyActive(char* tID, char* tAvatarName);
	int GetFreeProxyIndexForStart();
};
extern PROXY_SHOP_OBJECT mPROXY_OBJECT[500];



class ZONEMAININFO
{

private:
	int mZoneLevelInfo[MAX_ZONE_NUMBER_NUM][2];
	int mZoneTribeInfo[MAX_ZONE_NUMBER_NUM][2];

public:
	ZONEMAININFO(void);
	BOOL Init(void);
	void Free(void);
	int ReturnMinZoneLevelInfo(int tZoneNumber);
	int ReturnMaxZoneLevelInfo(int tZoneNumber);
	int ReturnZoneTribeInfo1(int tZoneNumber);
	int ReturnZoneTribeInfo2(int tZoneNumber);
	BOOL CheckLevelBattleZoneNumber2();
	BOOL Check267TypeZoneNumber2();
};
extern ZONEMAININFO mZONEMAININFO;


typedef struct
{
	int mTotalNPCNum;
	int mNPCNumber[MAX_NPC_OBJECT_NUM];
	float mNPCCoord[MAX_NPC_OBJECT_NUM][3];
	float mNPCAngle[MAX_NPC_OBJECT_NUM];
} 
ZONENPCINFODATA;

class ZONENPCINFO
{

public:
	ZONENPCINFODATA mDATA[MAX_ZONE_NUMBER_NUM];

	ZONENPCINFO(void);

	BOOL Init(void);
	void Free(void);

	int ReturnZoneNumber(int tNPCNumber);
	int ReturnZoneCoord(int tNPCNumber, float tCoord[3]);

	BOOL CheckNPCFunction(float tCoord[3], int tMenuIndex);
};
extern ZONENPCINFO mZONENPCINFO;