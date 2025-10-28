#include "MainApp.h"

MONSTER_OBJECT mMONSTER_OBJECT[MAX_MONSTER_OBJECT_NUM];

void MONSTER_OBJECT::SetSpaceIndex(void)
{
	mSPACE_INDEX[0] = (int)(mDATA.mAction.aLocation[0] / MAX_RADIUS_FOR_NETWORK);
	mSPACE_INDEX[1] = (int)(mDATA.mAction.aLocation[1] / MAX_RADIUS_FOR_NETWORK);
	mSPACE_INDEX[2] = (int)(mDATA.mAction.aLocation[2] / MAX_RADIUS_FOR_NETWORK);
}
//UPDATE
void MONSTER_OBJECT::Update(int tObjectIndex, float tPostTime)
{
	if (!mCheckValidState)
	{
		return;
	}
	switch (mDATA.mAction.aSort)
	{
	case  0:
		A001(tObjectIndex, tPostTime);
		return;
	case  1:
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
			A002_FOR_ZONE_175_TYPE_BOSS(tObjectIndex, tPostTime);
			return;
		default:
			A002(tObjectIndex, tPostTime);
			return;
		}
		return;
	case  3:
		A004(tObjectIndex, tPostTime);
		SetSpaceIndex();
		return;
	case  4:
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 40:
		case 41:
		case 42:
		case 43:
		case 44:
			A005_FOR_ZONE_175_TYPE_BOSS(tObjectIndex, tPostTime);
			SetSpaceIndex();
			return;
		default:
			A005(tObjectIndex, tPostTime);
			SetSpaceIndex();
			return;
		}
		return;
	case  5:
		A006(tObjectIndex, tPostTime); // Update Monster -> Character Attack
		return;
	case  7:
		A008(tObjectIndex, tPostTime);
		return;
	case  8:
		A009(tObjectIndex, tPostTime);
		return;
	case 12:
		A013(tObjectIndex, tPostTime);
		return;
	case 19:
		A020(tObjectIndex, tPostTime);
		SetSpaceIndex();
		return;
	}
}
//SELECT_AVATAR_INDEX_FOR_POSSIBLE_ATTACK
int MONSTER_OBJECT::SelectAvatarIndexForPossibleAttack(void)
{
	int index01;
	int index02;
	int index03;
	int tSelectAvatarIndex;
	unsigned int tRandom = 0;

	if ((mMONSTER_INFO->mAttackType != 1) && (mMONSTER_INFO->mAttackType != 3) && (mMONSTER_INFO->mAttackType != 6))
	{
		return -1;
	}
	if ((GetTickCount64() - mCheckDetectEnemyTime) < 1000)
	{
		return -1;
	}
	mCheckDetectEnemyTime = GetTickCount64();
	if (mMONSTER_INFO->mRadiusInfo[1] < 1)
	{
		return -1;
	}
	tSelectAvatarIndex = -1;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 1))
		{
			continue;
		}
		if (mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
		{
			continue;
		}
		index03 = 0;
		for (index02 = 0; index02 < MAX_MONSTER_OBJECT_NUM; index02++)
		{
			if (!mMONSTER_OBJECT[index02].mCheckValidState)
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index02].mDATA.mAction.aSort != 4) && (mMONSTER_OBJECT[index02].mDATA.mAction.aSort != 5))
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index02].mDATA.mAction.aTargetObjectIndex != index01) || (mMONSTER_OBJECT[index02].mDATA.mAction.aTargetObjectUniqueNumber != mAVATAR_OBJECT[index01].mUniqueNumber))
			{
				continue;
			}
			index03++;
		}
		if (index03 > (mSameTargetPostNum - 1))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectAvatarIndex = index01;
			break;
		}
	}
	return tSelectAvatarIndex;
}
//SELECT_AVATAR_INDEX_FOR_POSSIBLE_ATTACK_FOR_ZONE_175_TYPE_BOSS
void MONSTER_OBJECT::SelectAvatarIndexForPossibleAttackForZone175TypeBoss(void)
{
	int index01;
	int tWhoAttackMonster;
	unsigned int tRandom = 0;

	if ((GetTickCount64() - mCheckDetectEnemyTime) < 1000)
	{
		return;
	}
	mCheckDetectEnemyTime = GetTickCount64();
	mCheckAttackState = FALSE;
	mTotalAttackNum = 0;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		if (mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]) > (float) (mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			SetAttackInfoWithAvatar(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &tWhoAttackMonster);
		}
	}
}
//SELECT_AVATAR_INDEX_FOR_IDLE_AI
int MONSTER_OBJECT::SelectAvatarIndexForIdleAI(void)
{
	int index01;
	unsigned int tRandom = 0;

	tRandom = rand();
	if (((tRandom % 100) != 0) || (mMONSTER_INFO->mWalkSpeed < 1))
	{
		return -1;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 1))
		{
			continue;
		}
		break;
	}
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}
	return -1;
}
//ADJUST_VALID_ATTACK_TARGET
void MONSTER_OBJECT::AdjustValidAttackTarget(void)
{
	int index01;
	int index02;
	int index03;
	float tLength;
	int tTotalAttackNum;
	int tAttackIndex[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD tAttackUniqueNumber[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD tAttackDamage[MAX_MONSTER_OBJECT_ATTACK_NUM];
	float tAttackLength[MAX_MONSTER_OBJECT_ATTACK_NUM];

	tTotalAttackNum = 0;
	if ((mMONSTER_INFO->mRadiusInfo[0] > 0) && (mMONSTER_INFO->mRadiusInfo[1] > 0))
	{
		for (index01 = 0; index01 < mTotalAttackNum; index01++)
		{
			if (!mAVATAR_OBJECT[mAttackIndex[index01]].mCheckValidState)
			{
				continue;
			}
			if (1 == mAVATAR_OBJECT[mAttackIndex[index01]].mGod) {
				continue;
			}
			if (1 == mUSER[mAttackIndex[index01]].mAuthInfo.AttackFlag) {
				continue;
			}
			if (mAVATAR_OBJECT[mAttackIndex[index01]].mUniqueNumber != mAttackUniqueNumber[index01])
			{
				continue;
			}
			if (mUSER[mAttackIndex[index01]].mMoveZoneResult == 1)
			{
				continue;
			}
			if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aVisibleState == 0)
			{
				continue;
			}
			if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aLifeValue < 1)
			{
				continue;
			}
			if ((mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aSort == 33))
			{
				continue;
			}
			if ((abs(mAVATAR_OBJECT[mAttackIndex[index01]].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 1) || (abs(mAVATAR_OBJECT[mAttackIndex[index01]].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 1) || (abs(mAVATAR_OBJECT[mAttackIndex[index01]].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 1))
			{
				continue;
			}
			tLength = mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]);
			if (tLength > (float)(mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
			{
				continue;
			}
			else
			{
				if (tLength > (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
				{
					index03 = 0;
					for (index02 = 0; index02 < MAX_MONSTER_OBJECT_NUM; index02++)
					{
						if (!mMONSTER_OBJECT[index02].mCheckValidState)
						{
							continue;
						}
						if ((mMONSTER_OBJECT[index02].mDATA.mAction.aSort != 4) && (mMONSTER_OBJECT[index02].mDATA.mAction.aSort != 5))
						{
							continue;
						}
						if ((mMONSTER_OBJECT[index02].mDATA.mAction.aTargetObjectIndex != mAttackIndex[index01]) || (mMONSTER_OBJECT[index02].mDATA.mAction.aTargetObjectUniqueNumber != mAttackUniqueNumber[index01]))
						{
							continue;
						}
						index03++;
					}
					if (index03 > (mSameTargetPostNum - 1))
					{
						continue;
					}
				}
				else
				{
					if (fabsf(mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aLocation[1] - mDATA.mAction.aLocation[1]) > (float)mMONSTER_INFO->mSize[1])
					{
						continue;
					}
				}
			}
			tAttackIndex[tTotalAttackNum] = mAttackIndex[index01];
			tAttackUniqueNumber[tTotalAttackNum] = mAttackUniqueNumber[index01];
			tAttackDamage[tTotalAttackNum] = mAttackDamage[index01];
			tAttackLength[tTotalAttackNum] = tLength;
			tTotalAttackNum++;
		}
	}
	if (tTotalAttackNum < 1)
	{
		mCheckAttackState = FALSE;
		mTotalAttackNum = 0;
		return;
	}
	mTotalAttackNum = tTotalAttackNum;
	for (index01 = 0; index01 < tTotalAttackNum; index01++)
	{
		mAttackIndex[index01] = tAttackIndex[index01];
		mAttackUniqueNumber[index01] = tAttackUniqueNumber[index01];
		mAttackDamage[index01] = tAttackDamage[index01];
		mAttackLength[index01] = tAttackLength[index01];
	}
}
//ADJUST_VALID_ATTACK_TARGET_FOR_ZONE_175_TYPE_BOSS
void MONSTER_OBJECT::AdjustValidAttackTargetForZone175TypeBoss(void)
{
	int index01;
	float tLength;
	int tTotalAttackNum;
	int tAttackIndex[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD tAttackUniqueNumber[MAX_MONSTER_OBJECT_ATTACK_NUM];
	DWORD tAttackDamage[MAX_MONSTER_OBJECT_ATTACK_NUM];
	float tAttackLength[MAX_MONSTER_OBJECT_ATTACK_NUM];

	tTotalAttackNum = 0;
	for (index01 = 0; index01 < mTotalAttackNum; index01++)
	{
		if (!mAVATAR_OBJECT[mAttackIndex[index01]].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[mAttackIndex[index01]].mGod) {
			continue;
		}
		if (1 == mUSER[mAttackIndex[index01]].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mUniqueNumber != mAttackUniqueNumber[index01])
		{
			continue;
		}
		if (mUSER[mAttackIndex[index01]].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		tLength = mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]);
		if (tLength > (float) (mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
		{
			continue;
		}
		tAttackIndex[tTotalAttackNum] = mAttackIndex[index01];
		tAttackUniqueNumber[tTotalAttackNum] = mAttackUniqueNumber[index01];
		tAttackDamage[tTotalAttackNum] = mAttackDamage[index01];
		tAttackLength[tTotalAttackNum] = tLength;
		tTotalAttackNum++;
	}
	if (tTotalAttackNum < 1)
	{
		mCheckAttackState = FALSE;
		mTotalAttackNum = 0;
		return;
	}
	mTotalAttackNum = tTotalAttackNum;
	for (index01 = 0; index01 < tTotalAttackNum; index01++)
	{
		mAttackIndex[index01] = tAttackIndex[index01];
		mAttackUniqueNumber[index01] = tAttackUniqueNumber[index01];
		mAttackDamage[index01] = tAttackDamage[index01];
		mAttackLength[index01] = tAttackLength[index01];
	}
}
//SELECT_AVATAR_INDEX_FOR_ATTACK_ACTION
int MONSTER_OBJECT::SelectAvatarIndexForAttackAction(void)
{
	int index01;
	int tSelectAvatarIndex;
	unsigned int tRandom = 0;

	if ((mMONSTER_INFO->mAttackType != 1) && (mMONSTER_INFO->mAttackType != 3) && (mMONSTER_INFO->mAttackType != 6))
	{
		return -1;
	}
	if ((GetTickCount64() - mCheckDetectEnemyTime) < 1000)
	{
		return -1;
	}
	mCheckDetectEnemyTime = GetTickCount64();
	if (mMONSTER_INFO->mRadiusInfo[0] < 1)
	{
		return -1;
	}
	tSelectAvatarIndex = -1;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 1))
		{
			continue;
		}
		if (mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
		{
			continue;
		}
		else
		{
			if (fabsf(mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1] - mDATA.mAction.aLocation[1]) > (float)mMONSTER_INFO->mSize[1])
			{
				continue;
			}
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectAvatarIndex = index01;
			break;
		}
	}
	return tSelectAvatarIndex;
}
//SELECT_AVATAR_INDEX_FOR_GUARD_ATTACK
int MONSTER_OBJECT::SelectAvatarIndexForGuardAttack(void)
{
	int index01;
	int tMyTribe;
	int tAllianceTribe;
	int tSelectAvatarIndex;
	unsigned int tRandom = 0;

	if ((GetTickCount64() - mCheckDetectEnemyTime) < 1000)
	{
		return -1;
	}
	mCheckDetectEnemyTime = GetTickCount64();
	if (mMONSTER_INFO->mRadiusInfo[0] < 1)
	{
		return -1;
	}
	switch (mMONSTER_INFO->mType)
	{
	case 6:
		tMyTribe = 0;
		break;
	case 7:
		tMyTribe = 1;
		break;
	case 8:
		tMyTribe = 2;
		break;
	case 9:
		tMyTribe = 3;
		break;
	default:
		return -1;
	}
	tAllianceTribe = mGAME.ReturnAllianceTribe(tMyTribe);
	tSelectAvatarIndex = -1;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe == tMyTribe) || (mAVATAR_OBJECT[index01].mDATA.aTribe == tAllianceTribe))
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 2))
		{
			continue;
		}
		if (mUTIL.GetDoubleX_Z(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectAvatarIndex = index01;
			break;
		}
	}
	return tSelectAvatarIndex;
}
//SELECT_AVATAR_INDEX_FOR_IDLE_AI_WITH_THROW_CAR
int MONSTER_OBJECT::SelectAvatarIndexForIdleAIWIthThrowCar(void)
{
	int index01;
	unsigned int tRandom = 0;

	tRandom = rand();
	if (((tRandom % 100) != 0) || (mMONSTER_INFO->mWalkSpeed < 1))
	{
		return -1;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 2))
		{
			continue;
		}
		break;
	}
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}
	return -1;
}
//SELECT_AVATAR_INDEX_FOR_THROW_CAR_ATTACK
int MONSTER_OBJECT::SelectAvatarIndexForThrowCarAttack(void)
{
	int index01;
	int tMyTribe;
	int tAllianceTribe;
	int tSelectAvatarIndex;
	float tLength;
	unsigned int tRandom = 0;

	if ((GetTickCount64() - mCheckDetectEnemyTime) < 1000)
	{
		return -1;
	}
	mCheckDetectEnemyTime = GetTickCount64();
	if (mMONSTER_INFO->mRadiusInfo[0] < 1)
	{
		return -1;
	}
	switch (mMONSTER_INFO->mSpecialType)
	{
	case 35:
		tMyTribe = 0;
		break;
	case 36:
		tMyTribe = 1;
		break;
	case 37:
		tMyTribe = 2;
		break;
	case 38:
		tMyTribe = 3;
		break;
	case 18:
		tMyTribe = -1;
		break;
	default:
		return -1;
	}
	tAllianceTribe = mGAME.ReturnAllianceTribe(tMyTribe);
	tSelectAvatarIndex = -1;
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 == mAVATAR_OBJECT[index01].mGod) {
			continue;
		}
		if (1 == mUSER[index01].mAuthInfo.AttackFlag) {
			continue;
		}
		if (mUSER[index01].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe == tMyTribe) || (mAVATAR_OBJECT[index01].mDATA.aTribe == tAllianceTribe))
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 0) || (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33))
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - mSPACE_INDEX[0]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - mSPACE_INDEX[1]) > 2) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - mSPACE_INDEX[2]) > 2))
		{
			continue;
		}
		tLength = mUTIL.GetLengthXYZ(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mDATA.mAction.aLocation[0]);
		if ((tLength < ((float)mMONSTER_INFO->mRadiusInfo[0] * 0.25f)) || (tLength > (float) mMONSTER_INFO->mRadiusInfo[0]))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectAvatarIndex = index01;
			break;
		}
	}
	return tSelectAvatarIndex;
}
//A001[생성]
void MONSTER_OBJECT::A001(int tObjectIndex, float tPostTime)
{
	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[0])
	{
		return;
	}
	mDATA.mAction.aSort = 1;
	mDATA.mAction.aFrame = 0.0f;
}
//A002[아이들]
void MONSTER_OBJECT::A002(int tObjectIndex, float tPostTime)
{
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeSymbolIndex;
	int tAllianceStoneIndex;
	int tSelectAvatarIndex;
	int tWhoAttackMonster;
	float tPossibleLocation[3];
	float tDirection[3];
	float tLength;
	float tRadius;
	float tLocation[3];
	int tSelectTargetIndex;
	float tAttackLength;
	float tAttackRadius;
	float tAttackDirect;
	float tSinValue;
	float tCosValue;
	unsigned int tRandom = 0;

	switch (mSpecialSortNumber)
	{
	case 1:
		break;
	case 2:
		if (!mCheckFirstAttackForTribeSymbol)
		{
			return;
		}
		if ((GetTickCount64() - mFirstAttackTimeForTribeSymbol) < 3600000)
		{
			return;
		}
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 11:
			tTribeSymbolIndex = 0;
			break;
		case 12:
			tTribeSymbolIndex = 1;
			break;
		case 13:
			tTribeSymbolIndex = 2;
			break;
		case 28:
			tTribeSymbolIndex = 3;
			break;
		case 14:
			tTribeSymbolIndex = 4;
			break;
		case 15:
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 43;
		CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mCheckFirstAttackForTribeSymbol = FALSE;
		mFirstAttackTimeForTribeSymbol = GetTickCount64();
		mTribeDamageForTribeSymbol[0] = 0;
		mTribeDamageForTribeSymbol[1] = 0;
		mTribeDamageForTribeSymbol[2] = 0;
		mTribeDamageForTribeSymbol[3] = 0;
		mDATA.mLifeValue = mMONSTER_INFO->mLife;
		return;
	case 3:
		return;
	case 4:
		if (!mCheckFirstAttackForAllianceStone)
		{
			return;
		}
		if ((GetTickCount64() - mFirstAttackTimeForAllianceStone) < 3600000)
		{
			return;
		}
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 31:
			tAllianceStoneIndex = 0;
			break;
		case 32:
			tAllianceStoneIndex = 1;
			break;
		case 33:
			tAllianceStoneIndex = 2;
			break;
		case 34:
			tAllianceStoneIndex = 3;
			break;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 50;
		CopyMemory(&tBroadcastInfoData[0], &tAllianceStoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mCheckFirstAttackForAllianceStone = FALSE;
		mFirstAttackTimeForAllianceStone = GetTickCount64();
		mDATA.mLifeValue = mMONSTER_INFO->mLife;
		return;
	case 5:
		tSelectAvatarIndex = SelectAvatarIndexForGuardAttack();
		if (tSelectAvatarIndex == -1)
		{
			return;
		}
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = tSelectAvatarIndex;
		mDATA.mAction.aTargetObjectUniqueNumber = mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	case 6:
		if (SelectAvatarIndexForIdleAIWIthThrowCar() != -1)
		{
			tDirection[0] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tDirection[2] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tLength = sqrtf(tDirection[0] * tDirection[0] + tDirection[2] * tDirection[2]);
			if (tLength > 0.0f)
			{
				tDirection[0] /= tLength;
				tDirection[2] /= tLength;
			}
			tRandom = rand();
			tRadius = (float)(50 + (tRandom % 51));
			tLocation[0] = mDATA.mAction.aLocation[0] + tDirection[0] * tRadius;
			tLocation[1] = mDATA.mAction.aLocation[1];
			tLocation[2] = mDATA.mAction.aLocation[2] + tDirection[2] * tRadius;
			mWORLD.Path(&mDATA.mAction.aLocation[0], &tLocation[0], (float)mMONSTER_INFO->mWalkSpeed, 0.033f, &tPossibleLocation[0]);
			if (mUTIL.GetDoubleXYZ(&tPossibleLocation[0], &mDATA.mAction.aLocation[0]) < (50.0f * 50.0f))
			{
				return;
			}
			mDATA.mAction.aSort = 3;
			mDATA.mAction.aFrame = 0.0f;
			mDATA.mAction.aTargetLocation[0] = tPossibleLocation[0];
			mDATA.mAction.aTargetLocation[1] = tPossibleLocation[1];
			mDATA.mAction.aTargetLocation[2] = tPossibleLocation[2];
			mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], tPossibleLocation[0], tPossibleLocation[2]);
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
		tSelectAvatarIndex = SelectAvatarIndexForThrowCarAttack();
		if (tSelectAvatarIndex == -1)
		{
			return;
		}
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aTargetLocation[0] = mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[0];
		mDATA.mAction.aTargetLocation[1] = mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[1];
		mDATA.mAction.aTargetLocation[2] = mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[2];
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = tSelectAvatarIndex;
		mDATA.mAction.aTargetObjectUniqueNumber = mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;

	case 7: // Towers
		return;

	default:
		return;
	}
	if (!mCheckAttackState)
	{
		tSelectAvatarIndex = SelectAvatarIndexForPossibleAttack();
		if (tSelectAvatarIndex != -1)
		{
			SetAttackInfoWithAvatar(tSelectAvatarIndex, mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber, &tWhoAttackMonster);
		}
		else
		{
			if (SelectAvatarIndexForIdleAI() == -1)
			{
				return;
			}
			if ((GetTickCount64() - mCheckFirstLocationTime) > 60000)
			{
				mCheckFirstLocationTime = GetTickCount64();
				mWORLD.Path(&mDATA.mAction.aLocation[0], &mFirstLocation[0], (float)mMONSTER_INFO->mWalkSpeed, 0.033f, &tPossibleLocation[0]);
				if (mUTIL.GetDoubleXYZ(&tPossibleLocation[0], &mFirstLocation[0]) > (1.0f * 1.0f))
				{
					mDATA.mAction.aSort = 19;
					mDATA.mAction.aFrame = 0.0f;
					//------------------------//
					//BROADCAST_MONSTER_ACTION//
					//------------------------//
					mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
					mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
					//------------------------//
					//------------------------//
					//------------------------//
					return;
				}
			}
			tDirection[0] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tDirection[2] = mUTIL.RandomNumber(-100.0f, 100.0f);
			tLength = sqrtf(tDirection[0] * tDirection[0] + tDirection[2] * tDirection[2]);
			if (tLength > 0.0f)
			{
				tDirection[0] /= tLength;
				tDirection[2] /= tLength;
			}
			tRandom = rand();
			tRadius = (float)(50 + (tRandom % 51));
			tLocation[0] = mDATA.mAction.aLocation[0] + tDirection[0] * tRadius;
			tLocation[1] = mDATA.mAction.aLocation[1];
			tLocation[2] = mDATA.mAction.aLocation[2] + tDirection[2] * tRadius;
			mWORLD.Path(&mDATA.mAction.aLocation[0], &tLocation[0], (float)mMONSTER_INFO->mWalkSpeed, 0.033f, &tPossibleLocation[0]);
			if (mUTIL.GetDoubleXYZ(&tPossibleLocation[0], &mDATA.mAction.aLocation[0]) < (50.0f * 50.0f))
			{
				return;
			}
			mDATA.mAction.aSort = 3;
			mDATA.mAction.aFrame = 0.0f;
			mDATA.mAction.aTargetLocation[0] = tPossibleLocation[0];
			mDATA.mAction.aTargetLocation[1] = tPossibleLocation[1];
			mDATA.mAction.aTargetLocation[2] = tPossibleLocation[2];
			mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], tPossibleLocation[0], tPossibleLocation[2]);
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
	}
	AdjustValidAttackTarget();
	if (!mCheckAttackState)
	{
		return;
	}
	tSelectTargetIndex = -1;
	for (index01 = 0; index01 < mTotalAttackNum; index01++)
	{
		if (mAttackLength[index01] > (float) (mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectTargetIndex = index01;
			break;
		}
	}
	if (tSelectTargetIndex == -1)
	{
		tRandom = rand();
		tSelectTargetIndex = (tRandom % mTotalAttackNum);
	}
	if (mAttackLength[tSelectTargetIndex] <= (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
	{
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = mAttackIndex[tSelectTargetIndex];
		mDATA.mAction.aTargetObjectUniqueNumber = mAttackUniqueNumber[tSelectTargetIndex];
		//mAttackCheckForSlowMobs = 1;
		if ((mMONSTER_INFO->mAttackType == 1) || (mMONSTER_INFO->mAttackType == 2) /*|| (mMONSTER_INFO->mAttackType == 6)*/)
		{
			mCheckAttackPacketRecv = TRUE;
			mAttackPacketRecvTime = GetTickCount64();
		}
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if ((mMONSTER_INFO->mRunSpeed < 1) || (mMONSTER_INFO->mRadiusInfo[0] < 1))
	{
		return;
	}
	tAttackLength = sqrtf(mAttackLength[tSelectTargetIndex]);
	tRandom = rand();
	if ((tRandom % 2) == 0)
	{
		tRandom = rand();
		tAttackRadius = (float)(tRandom % mMONSTER_INFO->mRadiusInfo[0]);
	}
	else
	{
		tRandom = rand();
		tAttackRadius = (float)(tRandom % mMONSTER_INFO->mRadiusInfo[0]);
		tAttackRadius = -1.0f * tAttackRadius;
	}
	tAttackDirect = sqrtf((tAttackLength * tAttackLength) - (tAttackRadius * tAttackRadius));
	tSinValue = tAttackRadius / tAttackLength;
	tCosValue = tAttackDirect / tAttackLength;
	tLocation[0] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0] - mDATA.mAction.aLocation[0];
	tLocation[2] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2] - mDATA.mAction.aLocation[2];
	tDirection[0] = tLocation[0] * tCosValue - tLocation[2] * tSinValue;
	tDirection[2] = tLocation[0] * tSinValue + tLocation[2] * tCosValue;
	tLength = sqrtf((tDirection[0] * tDirection[0]) + (tDirection[2] * tDirection[2]));
	if (tLength > 0.0f)
	{
		tDirection[0] /= tLength;
		tDirection[2] /= tLength;
	}
	tLocation[0] = mDATA.mAction.aLocation[0] + tDirection[0] * tAttackLength;
	tLocation[1] = mDATA.mAction.aLocation[1];
	tLocation[2] = mDATA.mAction.aLocation[2] + tDirection[2] * tAttackLength;
	if (!mWORLD.PathForMonsterAttack(&mDATA.mAction.aLocation[0], &tLocation[0], (float)mMONSTER_INFO->mRunSpeed, 0.033f, &mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0], (float)mMONSTER_INFO->mRadiusInfo[0], &tPossibleLocation[0]))
	{
		mDATA.mAction.aSort = 19;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	mDATA.mAction.aSort = 4;
	mDATA.mAction.aFrame = 0.0f;
	mDATA.mAction.aTargetLocation[0] = tPossibleLocation[0];
	mDATA.mAction.aTargetLocation[1] = tPossibleLocation[1];
	mDATA.mAction.aTargetLocation[2] = tPossibleLocation[2];
	mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], tPossibleLocation[0], tPossibleLocation[2]);
	mDATA.mAction.aTargetObjectIndex = mAttackIndex[tSelectTargetIndex];
	mDATA.mAction.aTargetObjectUniqueNumber = mAttackUniqueNumber[tSelectTargetIndex];
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
	mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
	//------------------------//
	//------------------------//
	//------------------------//
}
//A002_FOR_ZONE_175_TYPE_BOSS[아이들]
void MONSTER_OBJECT::A002_FOR_ZONE_175_TYPE_BOSS(int tObjectIndex, float tPostTime)
{
	int index01;
	int tSelectTargetIndex;
	float tDirection[3];
	float tLength;
	float tLocation[3];
	float tPossibleLocation[3];
	unsigned int tRandom = 0;

	SelectAvatarIndexForPossibleAttackForZone175TypeBoss();
	if (!mCheckAttackState)
	{
		return;
	}
	AdjustValidAttackTargetForZone175TypeBoss();
	if (!mCheckAttackState)
	{
		return;
	}
	tRandom = rand();
	if ((tRandom % 3) == 0)
	{
		tSelectTargetIndex = -1;
		for (index01 = 0; index01 < mTotalAttackNum; index01++)
		{
			if (mAttackLength[index01] < (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
			{
				continue;
			}
			tRandom = rand();
			if ((tRandom % 2) == 0)
			{
				tSelectTargetIndex = index01;
				break;
			}
		}
		if (tSelectTargetIndex == -1)
		{
			return;
		}
		mDATA.mAction.aSort = 7;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aTargetLocation[0] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0];
		mDATA.mAction.aTargetLocation[1] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[1];
		mDATA.mAction.aTargetLocation[2] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2];
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = mAttackIndex[tSelectTargetIndex];
		mDATA.mAction.aTargetObjectUniqueNumber = mAttackUniqueNumber[tSelectTargetIndex];
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	tSelectTargetIndex = -1;
	for (index01 = 0; index01 < mTotalAttackNum; index01++)
	{
		if (mAttackLength[index01] > (float) (mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
		{
			continue;
		}
		tRandom = rand();
		if ((tRandom % 2) == 0)
		{
			tSelectTargetIndex = index01;
			break;
		}
	}
	if (tSelectTargetIndex == -1)
	{
		tRandom = rand();
		tSelectTargetIndex = (tRandom % mTotalAttackNum);
	}
	if (mAttackLength[tSelectTargetIndex] <= (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
	{
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = mAttackIndex[tSelectTargetIndex];
		mDATA.mAction.aTargetObjectUniqueNumber = mAttackUniqueNumber[tSelectTargetIndex];
		//mAttackCheckForSlowMobs = 1;
		if ((mMONSTER_INFO->mAttackType == 1) || (mMONSTER_INFO->mAttackType == 2) /*|| (mMONSTER_INFO->mAttackType == 6)*/)
		{
			mCheckAttackPacketRecv = TRUE;
			mAttackPacketRecvTime = GetTickCount64();
		}
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	tDirection[0] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[0] - mDATA.mAction.aLocation[0];
	tDirection[2] = mAVATAR_OBJECT[mAttackIndex[tSelectTargetIndex]].mDATA.aAction.aLocation[2] - mDATA.mAction.aLocation[2];
	tLength = sqrtf((tDirection[0] * tDirection[0]) + (tDirection[2] * tDirection[2]));
	if (tLength > 0.0f)
	{
		tDirection[0] /= tLength;
		tDirection[2] /= tLength;
	}
	tLocation[0] = mDATA.mAction.aLocation[0] + tDirection[0] * 100.0f;
	tLocation[1] = mDATA.mAction.aLocation[1];
	tLocation[2] = mDATA.mAction.aLocation[2] + tDirection[2] * 100.0f;
	mWORLD.Path(&mDATA.mAction.aLocation[0], &tLocation[0], (float)mMONSTER_INFO->mRunSpeed, 0.033f, &tPossibleLocation[0]);
	if (mUTIL.GetDoubleXYZ(&tPossibleLocation[0], &mDATA.mAction.aLocation[0]) < (50.0f * 50.0f))
	{
		return;
	}
	mDATA.mAction.aSort = 4;
	mDATA.mAction.aFrame = 0.0f;
	mDATA.mAction.aTargetLocation[0] = tPossibleLocation[0];
	mDATA.mAction.aTargetLocation[1] = tPossibleLocation[1];
	mDATA.mAction.aTargetLocation[2] = tPossibleLocation[2];
	mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], tPossibleLocation[0], tPossibleLocation[2]);
	mDATA.mAction.aTargetObjectIndex = mAttackIndex[tSelectTargetIndex];
	mDATA.mAction.aTargetObjectUniqueNumber = mAttackUniqueNumber[tSelectTargetIndex];
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
	mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
	//------------------------//
	//------------------------//
	//------------------------//
}
//A004[걷기]
void MONSTER_OBJECT::A004(int tObjectIndex, float tPostTime)
{
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//

	int tSelectAvatarIndex;
	int tWhoAttackMonster;
	BOOL tCheckArrival;

	switch (mSpecialSortNumber)
	{
	case 1:
		if (mCheckAttackState)
		{
			mDATA.mAction.aSort = 1;
			mDATA.mAction.aFrame = 0.0f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
		tSelectAvatarIndex = SelectAvatarIndexForPossibleAttack();
		if (tSelectAvatarIndex != -1)
		{
			SetAttackInfoWithAvatar(tSelectAvatarIndex, mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber, &tWhoAttackMonster);
			mDATA.mAction.aSort = 1;
			mDATA.mAction.aFrame = 0.0f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
		break;
	}
	if (!mWORLD.Move(&mDATA.mAction.aLocation[0], &mDATA.mAction.aTargetLocation[0], (float)mMONSTER_INFO->mWalkSpeed, tPostTime, &tCheckArrival))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		//-----------------------------------------------------------------//
		//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
		//-----------------------------------------------------------------//
		switch (mSpecialSortNumber)
		{
		case 1:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			break;
		case 2:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			break;
		case 3:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 4:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 5:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
			break;
		case 6:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 7:
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			break;
		}
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (tCheckArrival)
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		return;
	}
}
//A005[달려들기]
void MONSTER_OBJECT::A005(int tObjectIndex, float tPostTime)
{
	int tSelectAvatarIndex;
	BOOL tCheckArrival;

	if ((!mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mCheckValidState) || (mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mUniqueNumber != mDATA.mAction.aTargetObjectUniqueNumber) || (mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aLifeValue < 1))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (mUTIL.GetDoubleX_Z(&mDATA.mAction.aLocation[0], &mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	tSelectAvatarIndex = SelectAvatarIndexForAttackAction();
	if (tSelectAvatarIndex != -1)
	{
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = mAVATAR_OBJECT[tSelectAvatarIndex].mIndex;
		mDATA.mAction.aTargetObjectUniqueNumber = mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber;
		//mAttackCheckForSlowMobs = 1;
		if ((mMONSTER_INFO->mAttackType == 1) || (mMONSTER_INFO->mAttackType == 2))
		{
			mCheckAttackPacketRecv = TRUE;
			mAttackPacketRecvTime = GetTickCount64();
		}
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (!mWORLD.Move(&mDATA.mAction.aLocation[0], &mDATA.mAction.aTargetLocation[0], (float)mMONSTER_INFO->mRunSpeed, tPostTime, &tCheckArrival))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (mUTIL.GetDoubleX_Z(&mDATA.mAction.aLocation[0], &mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[0]) <= (float)(mMONSTER_INFO->mRadiusInfo[0] * mMONSTER_INFO->mRadiusInfo[0]))
	{
		if (fabsf(mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[1] - mDATA.mAction.aLocation[1]) <= (float)mMONSTER_INFO->mSize[1])
		{
			mDATA.mAction.aSort = 5;
			mDATA.mAction.aFrame = 0.0f;
			mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[2]);
			//mAttackCheckForSlowMobs = 1;
			if ((mMONSTER_INFO->mAttackType == 1) || (mMONSTER_INFO->mAttackType == 2))
			{
				mCheckAttackPacketRecv = TRUE;
				mAttackPacketRecvTime = GetTickCount64();
			}
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
		else
		{
			mDATA.mAction.aSort = 19;
			mDATA.mAction.aFrame = 0.0f;
			//------------------------//
			//BROADCAST_MONSTER_ACTION//
			//------------------------//
			mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
			mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			//------------------------//
			//------------------------//
			//------------------------//
			return;
		}
	}
	if (tCheckArrival)
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		return;
	}
}
//A005_FOR_ZONE_175_TYPE_BOSS[달려들기]
void MONSTER_OBJECT::A005_FOR_ZONE_175_TYPE_BOSS(int tObjectIndex, float tPostTime)
{
	int tSelectAvatarIndex;
	BOOL tCheckArrival;

	if ((!mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mCheckValidState) || (mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mUniqueNumber != mDATA.mAction.aTargetObjectUniqueNumber) || (mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aLifeValue < 1))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (mUTIL.GetDoubleX_Z(&mDATA.mAction.aLocation[0], &mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[1] * mMONSTER_INFO->mRadiusInfo[1]))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	tSelectAvatarIndex = SelectAvatarIndexForAttackAction();
	if (tSelectAvatarIndex != -1)
	{
		mDATA.mAction.aSort = 5;
		mDATA.mAction.aFrame = 0.0f;
		mDATA.mAction.aFront = mUTIL.GetYAngle(mDATA.mAction.aLocation[0], mDATA.mAction.aLocation[2], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[0], mAVATAR_OBJECT[tSelectAvatarIndex].mDATA.aAction.aLocation[2]);
		mDATA.mAction.aTargetObjectIndex = mAVATAR_OBJECT[tSelectAvatarIndex].mIndex;
		mDATA.mAction.aTargetObjectUniqueNumber = mAVATAR_OBJECT[tSelectAvatarIndex].mUniqueNumber;
		//mAttackCheckForSlowMobs = 1;
		if ((mMONSTER_INFO->mAttackType == 1) || (mMONSTER_INFO->mAttackType == 2))
		{
			mCheckAttackPacketRecv = TRUE;
			mAttackPacketRecvTime = GetTickCount64();
		}
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (!mWORLD.Move(&mDATA.mAction.aLocation[0], &mDATA.mAction.aTargetLocation[0], (float)mMONSTER_INFO->mRunSpeed, tPostTime, &tCheckArrival))
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		//------------------------//
		//BROADCAST_MONSTER_ACTION//
		//------------------------//
		mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
		mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
		//------------------------//
		//------------------------//
		//------------------------//
		return;
	}
	if (tCheckArrival)
	{
		mDATA.mAction.aSort = 1;
		mDATA.mAction.aFrame = 0.0f;
		return;
	}
}

//A006[공격]
void MONSTER_OBJECT::A006(int tObjectIndex, float tPostTime)
{
	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[2])
	{
		return;
	}
	if (mCheckAttackPacketRecv)
	{
		/*if (mUTIL.GetLengthX_Z(&mDATA.mAction.aLocation[0], &mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mDATA.aAction.aLocation[0]) > (float)(mMONSTER_INFO->mRadiusInfo[0]))
		{
			mAttackCheckForSlowMobs = 0;
			mCheckAttackPacketRecv = FALSE;
		}*/
		if ((GetTickCount64() - mAttackPacketRecvTime) < 10000)
		{
			return;
		}
		mCheckAttackPacketRecv = FALSE;
		/*if (mAttackCheckForSlowMobs != 0)
		{
			mUSER[mDATA.mAction.aTargetObjectIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}*/
		if ((mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mCheckValidState) && (mAVATAR_OBJECT[mDATA.mAction.aTargetObjectIndex].mUniqueNumber == mDATA.mAction.aTargetObjectUniqueNumber))
		{

		}
	}
	mDATA.mAction.aSort = 1;
	mDATA.mAction.aFrame = 0.0f;
}
//A008[기술]
void MONSTER_OBJECT::A008(int tObjectIndex, float tPostTime)
{
	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[3])
	{
		return;
	}
	mDATA.mAction.aSort = 1;
	mDATA.mAction.aFrame = 0.0f;
}
//A009[피격]
void MONSTER_OBJECT::A009(int tObjectIndex, float tPostTime)
{
	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[1])
	{
		return;
	}
	mDATA.mAction.aSort = 1;
	mDATA.mAction.aFrame = 0.0f;
}
//A013[죽기]
void MONSTER_OBJECT::A013(int tObjectIndex, float tPostTime)
{
	//-----------------------------------------------------------------//
	//[01].일반,[02].성석,[03].수호비,[04].동맹석,[05].수호석,[06].석차//
	//-----------------------------------------------------------------//

	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeSymbolIndex;
	int tWinTribeForSymbol;
	int tAllianceIndex;
	int tAllianceTribe1;
	int tAllianceTribe2;
	int tPossibleAllianceDate01;
	int tPossibleAllianceDate02;
	int tAllianceStoneIndex;
	int tTowerSort;
	int tTowerIndex;

	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[4])
	{
		return;
	}
	mCheckValidState = FALSE;
	mInvalidTimeForSummon = GetTickCount64();
	switch (mSpecialSortNumber)
	{
	case 2:
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 11:
			tTribeSymbolIndex = 0;
			break;
		case 12:
			tTribeSymbolIndex = 1;
			break;
		case 13:
			tTribeSymbolIndex = 2;
			break;
		case 28:
			tTribeSymbolIndex = 3;
			break;
		case 14:
			tTribeSymbolIndex = 4;
			break;
		case 15:
			return;
		}
		tWinTribeForSymbol = -1;
		if ((mTribeDamageForTribeSymbol[0] >= mTribeDamageForTribeSymbol[1]) && (mTribeDamageForTribeSymbol[0] >= mTribeDamageForTribeSymbol[2]) && (mTribeDamageForTribeSymbol[0] >= mTribeDamageForTribeSymbol[3]))
		{
			tWinTribeForSymbol = 0;
		}
		if ((mTribeDamageForTribeSymbol[1] >= mTribeDamageForTribeSymbol[0]) && (mTribeDamageForTribeSymbol[1] >= mTribeDamageForTribeSymbol[2]) && (mTribeDamageForTribeSymbol[1] >= mTribeDamageForTribeSymbol[3]))
		{
			tWinTribeForSymbol = 1;
		}
		if ((mTribeDamageForTribeSymbol[2] >= mTribeDamageForTribeSymbol[0]) && (mTribeDamageForTribeSymbol[2] >= mTribeDamageForTribeSymbol[1]) && (mTribeDamageForTribeSymbol[2] >= mTribeDamageForTribeSymbol[3]))
		{
			tWinTribeForSymbol = 2;
		}
		if ((mTribeDamageForTribeSymbol[3] >= mTribeDamageForTribeSymbol[0]) && (mTribeDamageForTribeSymbol[3] >= mTribeDamageForTribeSymbol[1]) && (mTribeDamageForTribeSymbol[3] >= mTribeDamageForTribeSymbol[2]))
		{
			tWinTribeForSymbol = 3;
		}
		if (tWinTribeForSymbol == -1)
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 42;
		CopyMemory(&tBroadcastInfoData[0], &tTribeSymbolIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tWinTribeForSymbol, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		switch (tTribeSymbolIndex)
		{
		case 0:
			mGAME.mWorldInfo.mTribe1Symbol = tWinTribeForSymbol;
			break;
		case 1:
			mGAME.mWorldInfo.mTribe2Symbol = tWinTribeForSymbol;
			break;
		case 2:
			mGAME.mWorldInfo.mTribe3Symbol = tWinTribeForSymbol;
			break;
		case 3:
			mGAME.mWorldInfo.mTribe4Symbol = tWinTribeForSymbol;
			break;
		case 4:
			mGAME.mWorldInfo.mMonsterSymbol = tWinTribeForSymbol;
			break;
		}
		return;
	case 4:
		switch (mMONSTER_INFO->mSpecialType)
		{
		case 31:
			tAllianceStoneIndex = 0;
			break;
		case 32:
			tAllianceStoneIndex = 1;
			break;
		case 33:
			tAllianceStoneIndex = 2;
			break;
		case 34:
			tAllianceStoneIndex = 3;
			break;
		}
		if ((mGAME.mWorldInfo.mAllianceState[0][0] == tAllianceStoneIndex) || (mGAME.mWorldInfo.mAllianceState[0][1] == tAllianceStoneIndex))
		{
			tAllianceIndex = 0;
			tAllianceTribe1 = mGAME.mWorldInfo.mAllianceState[0][0];
			tAllianceTribe2 = mGAME.mWorldInfo.mAllianceState[0][1];
		}
		else if ((mGAME.mWorldInfo.mAllianceState[1][0] == tAllianceStoneIndex) || (mGAME.mWorldInfo.mAllianceState[1][1] == tAllianceStoneIndex))
		{
			tAllianceIndex = 1;
			tAllianceTribe1 = mGAME.mWorldInfo.mAllianceState[1][0];
			tAllianceTribe2 = mGAME.mWorldInfo.mAllianceState[1][1];
		}
		else
		{
			return;
		}
		tPossibleAllianceDate01 = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 28);
		tPossibleAllianceDate02 = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 28);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 49;
		CopyMemory(&tBroadcastInfoData[0], &tAllianceTribe1, 4);
		CopyMemory(&tBroadcastInfoData[4], &tAllianceTribe2, 4);
		CopyMemory(&tBroadcastInfoData[8], &tPossibleAllianceDate01, 4);
		CopyMemory(&tBroadcastInfoData[12], &tPossibleAllianceDate02, 4);
		CopyMemory(&tBroadcastInfoData[16], &tAllianceStoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[20], &mLastAttackUserTribe, 4);
		CopyMemory(&tBroadcastInfoData[24], &mLastAttackUserName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][0] = tPossibleAllianceDate01;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe1][1] = 1;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][0] = tPossibleAllianceDate02;
		mGAME.mWorldInfo.mPossibleAllianceInfo[tAllianceTribe2][1] = 1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		return;

	case 7: // Towers
		// Broadcast Destroy Tower
		tBroadcastInfoSort = 752;
		tTowerSort = mUTIL.GetTowerSort(1, 0);
		tTowerIndex = 900 + (mGAME.mTowerInfo.mTowerInfo[tTowerSort] % 100);
		CopyMemory(&tBroadcastInfoData[0], &tTowerSort, 4);
		CopyMemory(&tBroadcastInfoData[4], &tTowerIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		// Broadcast Removal of Tower
		tBroadcastInfoSort = 752;
		tTowerSort = mUTIL.GetTowerSort(1, 0);
		tTowerIndex = 0;
		CopyMemory(&tBroadcastInfoData[0], &tTowerSort, 4);
		CopyMemory(&tBroadcastInfoData[4], &tTowerIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		return;
	}
}
//A020[귀환]
void MONSTER_OBJECT::A020(int tObjectIndex, float tPostTime)
{
	mDATA.mAction.aFrame += (tPostTime * 30.0f);
	if (mDATA.mAction.aFrame < (float)mMONSTER_INFO->mFrameInfo[5])
	{
		return;
	}
	mDATA.mAction.aSort = 0;
	mDATA.mAction.aFrame = 0.0f;
	mDATA.mAction.aLocation[0] = mFirstLocation[0];
	mDATA.mAction.aLocation[1] = mFirstLocation[1];
	mDATA.mAction.aLocation[2] = mFirstLocation[2];
	//------------------------//
	//BROADCAST_MONSTER_ACTION//
	//------------------------//
	mTRANSFER.B_MONSTER_ACTION_RECV(tObjectIndex, mUniqueNumber, &mDATA, 1);
	mUTIL.Broadcast(TRUE, &mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
	//------------------------//
	//------------------------//
	//------------------------//
}
//SET_ATTACK_INFO_WITH_AVATAR
void MONSTER_OBJECT::SetAttackInfoWithAvatar(int tServerIndex, DWORD tUniqueNumber, int* tWhoAttackMonster)
{
	if (!mCheckValidState)
	{
		return;
	}
	int index01;

	if (!mCheckAttackState)
	{
		mCheckAttackState = TRUE;
		mTotalAttackNum = 0;
		mAttackIndex[mTotalAttackNum] = tServerIndex;
		mAttackUniqueNumber[mTotalAttackNum] = tUniqueNumber;
		mAttackDamage[mTotalAttackNum] = 0;
		mTotalAttackNum++;
		*tWhoAttackMonster = mTotalAttackNum - 1;
		return;
	}
	for (index01 = 0; index01 < mTotalAttackNum; index01++)
	{
		if ((mAttackIndex[index01] == tServerIndex) && (mAttackUniqueNumber[index01] = tUniqueNumber))
		{
			break;
		}
	}
	if (index01 < mTotalAttackNum)
	{
		*tWhoAttackMonster = index01;
		return;
	}
	if (mTotalAttackNum == MAX_MONSTER_OBJECT_ATTACK_NUM)
	{
		for (index01 = 1; index01 < mTotalAttackNum; index01++)
		{
			mAttackIndex[(index01 - 1)] = mAttackIndex[index01];
			mAttackUniqueNumber[(index01 - 1)] = mAttackUniqueNumber[index01];
			mAttackDamage[(index01 - 1)] = mAttackDamage[index01];
		}
		mTotalAttackNum--;
	}
	mAttackIndex[mTotalAttackNum] = tServerIndex;
	mAttackUniqueNumber[mTotalAttackNum] = tUniqueNumber;
	mAttackDamage[mTotalAttackNum] = 0;
	mTotalAttackNum++;
	*tWhoAttackMonster = mTotalAttackNum - 1;
}
//SELECT_AVATAR_INDEX_FOR_MAX_ATTACK_DAMAGE
int MONSTER_OBJECT::SelectAvatarIndexForMaxAttackDamage(void)
{
	if (!mCheckValidState)
	{
		return -1;
	}

	int index01;
	int tSelectAvatarIndex;

	if (!mCheckAttackState)
	{
		return -1;
	}
	tSelectAvatarIndex = -1;
	for (index01 = 0; index01 < mTotalAttackNum; index01++)
	{
		if (!mAVATAR_OBJECT[mAttackIndex[index01]].mCheckValidState)
		{
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mUniqueNumber != mAttackUniqueNumber[index01])
		{
			continue;
		}
		if (mUSER[mAttackIndex[index01]].mMoveZoneResult == 1)
		{
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aVisibleState == 0)
		{
			continue;
		}
		if (mAVATAR_OBJECT[mAttackIndex[index01]].mDATA.aLifeValue < 1)
		{
			continue;
		}
		if (tSelectAvatarIndex == -1)
		{
			tSelectAvatarIndex = index01;
		}
		else
		{
			if (mAttackDamage[index01] > mAttackDamage[tSelectAvatarIndex])
			{
				tSelectAvatarIndex = index01;
			}
		}
	}
	if (tSelectAvatarIndex == -1)
	{
		return -1;
	}
	return mAttackIndex[tSelectAvatarIndex];
}
//PROCESS_FOR_DROP_ITEM
void MONSTER_OBJECT::ProcessForDropItem(int tUserIndex)
{
	if (!mCheckValidState)
	{
		return;
	}
	unsigned int tRandom = 0;
	int index01;
	ITEM_INFO* tITEM_INFO;
	char tMasterName[MAX_AVATAR_NAME_LENGTH];
	int tMasterLuck;
	BOOL tCheckPossibleDrop;
	BOOL tCheckDropEvent;
	int tDropMoneySize;
	int tTribeItemList[10];
	int tItemLLevel;
	int tItemHLevel;
	int tItemType;
	int tItemSort;
	int tSearchItemTryNumForSameTribe;
	int tRandomValue;
	int tItemIndex;
	int tLuckyItemInfo[3];
	int tImproveStoneInfo[4];
	int tAddStone[2];
	int tDoubleDrop = 1;
	int tDropRate = 0;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	float tChance = 0.0f;
	int tDropIdx = 0;


	strncpy(tMasterName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	tMasterLuck = mAVATAR_OBJECT[tUserIndex].GetLuck() * 10;
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		if (mMONSTER_INFO->mMartialItemLevel < 1)
		{
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 - mMONSTER_INFO->mItemLevel) > 9)
			{
				tCheckPossibleDrop = FALSE;
			}
			else
			{
				if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 < 1)
				{
					tCheckPossibleDrop = TRUE;
				}
				else
				{
					tCheckPossibleDrop = FALSE;
				}
			}
		}
		else
		{
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 - mMONSTER_INFO->mMartialItemLevel) > 0)
			{
				tCheckPossibleDrop = FALSE;
			}
			else
			{
				tCheckPossibleDrop = TRUE;
			}
		}
	}
	else
	{
		tCheckPossibleDrop = TRUE;
	}
	//----------//
	//DROP_MONEY//
	//----------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;
		if ((mMONSTER_INFO->mDropMoneyInfo[0] > 0) && (mUTIL.RandomNumber() <= (int)((float)(mMONSTER_INFO->mDropMoneyInfo[0] + tMasterLuck) * mGAME.mItemDropUpRatio)))
		{
			tCheckDropEvent = TRUE;
		}

		if (tCheckDropEvent)
		{
			tRandom = rand();
			tDropMoneySize = mMONSTER_INFO->mDropMoneyInfo[1] + (tRandom % (mMONSTER_INFO->mDropMoneyInfo[2] - mMONSTER_INFO->mDropMoneyInfo[1] + 1));
			switch (mGAME.TowerSystemEffect(1, mUSER[tUserIndex].mAvatarInfo.aTribe))
			{
			case 1:
				tDropMoneySize += tDropMoneySize * 0.05f;
				break;
			case 2:
				tDropMoneySize += tDropMoneySize * 0.10f;
				break;
			case 3:
				tDropMoneySize += tDropMoneySize * 0.15f;
				break;
			case 4:
				tDropMoneySize += tDropMoneySize * 0.20f;
				break;
			}
			if (tDropMoneySize > 0)
			{
				mGAME.AddTribeBankInfo(mGAME.ReturnTribeForSymbol(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe), (tDropMoneySize * 0.10f));
				tDropMoneySize -= tDropMoneySize * 0.10f;
				if (!mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tDropMoneySize))
				{
					mUSER[tUserIndex].mAvatarInfo.aMoney += tDropMoneySize;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				//mUTIL.ProcessForDropItem(1, 1, tDropMoneySize, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], mAVATAR_OBJECT[tUserIndex].mDATA.aTribe);
			}
		}
	}
	//-----------//
	//DROP_POTION//
	//-----------//
	if (tCheckPossibleDrop)
	{
		for (index01 = 0; index01 < 5; index01++)
		{
			tCheckDropEvent = FALSE;
			if ((mMONSTER_INFO->mDropPotionInfo[index01][0] > 0) && (mUTIL.RandomNumber() <= (int)((float)mMONSTER_INFO->mDropPotionInfo[index01][0] + tMasterLuck) * mGAME.mItemDropUpRatio))
			{
				tCheckDropEvent = TRUE;
			}
			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, mMONSTER_INFO->mDropPotionInfo[index01][1], 1, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
			}
		}
	}
	//-----------------//
	//DROP_GENERAL_ITEM//
	//-----------------//
	if (tCheckPossibleDrop)
	{
		for (index01 = 0; index01 < 10; index01++)
		{
			if (index01 < 7 && index01 == 0)
			{
				tTribeItemList[index01] = 5;
			}
			else if (index01 < 7 && index01 != 0)
			{
				tTribeItemList[index01] = 6 + index01;
			}
			else
			{
				tTribeItemList[index01] = 13 + 3 * mUSER[tUserIndex].mAvatarInfo.aPreviousTribe + (index01 - 7);
			}
		}

		tDoubleDrop = 1;
		if (mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime > 0)
		{
			tDoubleDrop = 2;
		}
		// Time Effect will not be implemented due to the nature of drop system and its floating point values
		/*if (mUSER[tUserIndex].mAvatarInfo.aTimeEffect == 1)
		{
			tDoubleDrop += (int)((float)tDoubleDrop * 0.10f);
		}*/
		if (mMONSTER_INFO->mMartialItemLevel < 1)
		{
			tItemLLevel = mMONSTER_INFO->mItemLevel;
			tItemHLevel = mMONSTER_INFO->mItemLevel + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
		}
		else
		{
			tItemLLevel = mMONSTER_INFO->mItemLevel + mMONSTER_INFO->mMartialItemLevel;
			tItemHLevel = mMONSTER_INFO->mItemLevel + mMONSTER_INFO->mMartialItemLevel;
		}

		for (index01 = 0; index01 < 12; index01++)
		{
			tCheckDropEvent = FALSE;
			tItemSort = tTribeItemList[(rand() % 10)];
			if (index01 < 3)
			{
				tItemType = 1;
				tDropRate = (int)((float)(mMONSTER_INFO->mDropItemInfo[index01] + tMasterLuck) * ((mUSER[tUserIndex].mItemDropUpRatio * tDoubleDrop) + mGAME.mItemDropUpRatio));
			}
			else if (index01 < 6)
			{
				tItemType = 2;
				tDropRate = (int)((float)(mMONSTER_INFO->mDropItemInfo[index01] + tMasterLuck) * ((mUSER[tUserIndex].mItemDropUpRatio * tDoubleDrop) + mGAME.mItemDropUpRatio));
			}
			else if (index01 < 9)
			{
				tItemType = 3;
				tDropRate = (int)((float)(mMONSTER_INFO->mDropItemInfo[index01]) * ((mUSER[tUserIndex].mItemDropUpRatio * tDoubleDrop) + mGAME.mItemDropUpRatio));
			}
			else
			{
				tItemType = 4;
				tDropRate = mMONSTER_INFO->mDropItemInfo[index01] + mGAME.mItemDropUpRatio;
			}
			if (mUTIL.RandomNumber() <= tDropRate)
			{
				tCheckDropEvent = TRUE;
			}
			if (tCheckDropEvent)
			{
				tSearchItemTryNumForSameTribe = 0;
				while (tSearchItemTryNumForSameTribe < 10)
				{
					tITEM_INFO = mITEM.Return((tItemLLevel + (rand() % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
					if (tITEM_INFO)
					{
						if (((tITEM_INFO->iEquipInfo[0] == 1) || (tITEM_INFO->iEquipInfo[0] == (mAVATAR_OBJECT[tUserIndex].mDATA.aPreviousTribe + 2))) && (tITEM_INFO->iCheckMonsterDrop == 2))
						{
							break;
						}
						tITEM_INFO = NULL;
						tSearchItemTryNumForSameTribe++;
					}
					else
					{
						tSearchItemTryNumForSameTribe++;
					}
				}
				if (tITEM_INFO)
				{
					mUTIL.ProcessForDropItem(1, tITEM_INFO->iIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
				}
			}
		}
	}
	//------------------//
	//-WARLORD_IOS_BOSS-//
	//------------------//
	if (tCheckPossibleDrop)
	{
		if ((mMONSTER_INFO->mIndex == 722) || (mMONSTER_INFO->mIndex == 723) || (mMONSTER_INFO->mIndex == 724))
		{
			tCheckDropEvent = FALSE;

			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				tCheckDropEvent = TRUE;
				switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
				{
				case 0:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 87000 + mUTIL.GetRandomInt(21);
					}
					else
					{
						tDropIdx = 87063 + mUTIL.GetRandomInt(21);
					}
					break;

				case 1:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 87021 + mUTIL.GetRandomInt(21);
					}
					else
					{
						tDropIdx = 87085 + mUTIL.GetRandomInt(21);
					}
					break;

				case 2:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 87042 + mUTIL.GetRandomInt(21);
					}
					else
					{
						tDropIdx = 87107 + mUTIL.GetRandomInt(21);
					}
					break;
				}
			}
			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
				CopyMemory(&tData[0], &mSERVER_INFO.mServerNumber, 4);
				CopyMemory(&tData[4], &tMasterName[0], MAX_AVATAR_NAME_LENGTH);
				CopyMemory(&tData[4 + MAX_AVATAR_NAME_LENGTH], &tDropIdx, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(901, &tData[0]);
			}
		}
	}
//------------------//
///-Tainted Blade Generam-/// Battle Field
//------------------//
	if (tCheckPossibleDrop)
	{
		if (mMONSTER_INFO->mIndex == 703)
		{
			tCheckDropEvent = FALSE;

			if (mUTIL.GetRandomFloat() <= 100)
			{
				tCheckDropEvent = TRUE;

				switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
				{
				case 0:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;

				case 1:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;

				case 2:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;
				}
			}
			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
				CopyMemory(&tData[0], &mSERVER_INFO.mServerNumber, 4);
				CopyMemory(&tData[4], &tMasterName[0], MAX_AVATAR_NAME_LENGTH);
				CopyMemory(&tData[4 + MAX_AVATAR_NAME_LENGTH], &tDropIdx, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(901, &tData[0]);
			}
		}
	}
//------------------//
///-Ice King Boss-///  GV
//------------------//
	if (tCheckPossibleDrop)
	{
		if (mMONSTER_INFO->mIndex == 705)
		{
			tCheckDropEvent = FALSE;

			if (mUTIL.GetRandomFloat() <= 100)
			{

				tCheckDropEvent = FALSE;

				switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
				{
				case 0:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;

				case 1:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;

				case 2:
					if (mUTIL.GetRandomInt(2) == 0)
					{
						tDropIdx = 1378;
					}
					else
					{
						tDropIdx = 1447;
					}
					break;
				}
			}
			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
				CopyMemory(&tData[0], &mSERVER_INFO.mServerNumber, 4);
				CopyMemory(&tData[4], &tMasterName[0], MAX_AVATAR_NAME_LENGTH);
				CopyMemory(&tData[4 + MAX_AVATAR_NAME_LENGTH], &tDropIdx, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(901, &tData[0]);
			}
		}
	}
	//------------------//
////Ice King Drop ///
//------------------//
	if (tCheckPossibleDrop)
		tCheckDropEvent = FALSE;
	{
		if (mMONSTER_INFO->mIndex == 705)
		{
			{
				tCheckDropEvent = FALSE;
				tRandomValue = rand() % 100;
				if (tRandomValue < 5) //5%
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 698, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1448, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 10) //5%
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 696, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 20) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 30) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 40) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 100) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}
//------------------//
////The Lost Angel ///
//------------------//
	if (tCheckPossibleDrop)
		tCheckDropEvent = FALSE;
	{
		if (mMONSTER_INFO->mIndex == 1478)
		{
			{
				tCheckDropEvent = FALSE;
				tRandomValue = rand() % 100;
				if (tRandomValue < 5) //5%
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 698, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1448, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 10) //5%
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 696, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 20) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 30) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 40) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					tDropIdx = 578 + mUTIL.GetRandomInt(2);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 100) //
				{
					tCheckDropEvent = TRUE;
					tDropIdx = 506 + mUTIL.GetRandomInt(4);
					mUTIL.ProcessForDropItem(1, tDropIdx, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUTIL.ProcessForDropItem(1, 1072, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}
	//------------------//
	//---LOD-----BOSS---//
	//------------------//
	if (tCheckPossibleDrop)
	{
		if ((mMONSTER_INFO->mIndex == 725) || (mMONSTER_INFO->mIndex == 726) || (mMONSTER_INFO->mIndex == 727) || (mMONSTER_INFO->mIndex == 728) || (mMONSTER_INFO->mIndex == 729) || (mMONSTER_INFO->mIndex == 730))
		{
			{
				tCheckDropEvent = FALSE;
				tRandomValue = rand() % 100;
				if (tRandomValue < 5) //5%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1401, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 10) //10%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1378, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 20) //20%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1378, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 30) //30%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1378, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 40) //40%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1378, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else if (tRandomValue < 100) //100%
				{
					tCheckDropEvent = TRUE;
					mUTIL.ProcessForDropItem(1, 1378, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}

	//	//-------------------//
	//	//---DROP_V2_STONE---//
	//	//-------------------//
	//	if (tCheckPossibleDrop)
	//	{
	//		if ((mMONSTER_INFO->mIndex == 725) || (mMONSTER_INFO->mIndex == 726) || (mMONSTER_INFO->mIndex == 727) || (mMONSTER_INFO->mIndex == 728) || (mMONSTER_INFO->mIndex == 729) || (mMONSTER_INFO->mIndex == 730))
	//		{
	//			if(mUTIL.GetRandomFloat() <= 0.10f)
	//			{
	//				tDropIdx = 501 + mUTIL.GetRandomInt(4);
	//				CopyMemory(&tData[0], &mSERVER_INFO.mServerNumber, 4);
	//				CopyMemory(&tData[4], &tMasterName[0], MAX_AVATAR_NAME_LENGTH);
	//				CopyMemory(&tData[4 + MAX_AVATAR_NAME_LENGTH], &tDropIdx, 4);
	//				mCENTER_COM.U_DEMAND_BROADCAST_INFO(901, &tData[0]);
	//			}
	//		}
	//	}
	//	//-----------------//
	//DROP_FEATHER_ITEM//
	//-----------------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;
		if (mUTIL.RandomNumber() <= 70)
		{
			tCheckDropEvent = TRUE;

			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, 695, 0, 0, mUTIL.ReturnItemRecognitionNumber(tItemType), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
			}
		}
	}
	//----------------//
	//DROP_SILVER_ITEM//
	//----------------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;
		if (mUTIL.RandomNumber() <= 10)
		{
			tCheckDropEvent = TRUE;
			tRandomValue = rand() % 100;
			if (tRandomValue <= 10)
			{
				tItemIndex = 1074;
			}
			else if (tRandomValue <= 50)
			{
				tItemIndex = 1073;
			}
			else
			{
				tItemIndex = 1072;
			}

			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, tItemIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
			}
		}
	}
	//--------------//
	//DROP_SKILL_BOX//
	//--------------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;
		//if (mUTIL.RandomNumber() <= 70)
		if (mUTIL.RandomNumber() <= 200)
		{
			tCheckDropEvent = TRUE;
		}

		if (tCheckDropEvent)
		{
			mUTIL.ProcessForDropItem(1, 864, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}
	// Event Monsters
	
	//


	//---------------//
	//DROP_EXTRA_ITEM//
	//---------------//
	if (tCheckPossibleDrop)
	{
		for (index01 = 0; index01 < 50; index01++)
		{
			tCheckDropEvent = FALSE;
			if ((mMONSTER_INFO->mDropExtraItemInfo[index01][0] > 0) && (mUTIL.RandomNumber() <= mMONSTER_INFO->mDropExtraItemInfo[index01][0]))
			{
				tCheckDropEvent = TRUE;
				switch (mMONSTER_INFO->mDropExtraItemInfo[index01][1])
				{
				case 1019:
				case 1020:
				case 1021:
				case 1022:
				case 1027:
				case 1045:
				case 1066:
				case 1036:
					tCheckDropEvent = TRUE;
					break;
				default:
					tCheckDropEvent = FALSE;
					break;
				}
			}

			if (tCheckDropEvent)
			{
				mUTIL.ProcessForDropItem(1, mMONSTER_INFO->mDropExtraItemInfo[index01][1], 0, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
			}
		}
	}
	//---------------//
	//DROP_LUCKY_ITEM//
	//---------------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;

		if (mUTIL.GetRandomFloat() <= 0.0001f)
		{
			tCheckDropEvent = TRUE;
			tItemIndex = 1035 + mUTIL.GetRandomInt(3);
		}
		if (tCheckDropEvent)
		{
			mUTIL.ProcessForDropItem(1, tItemIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}
	//------------------//
	//DROP_IMPROVE_STONE//
	//------------------//
	if (tCheckPossibleDrop)
	{
		tImproveStoneInfo[0] = 1019;
		tImproveStoneInfo[1] = 1020;
		tImproveStoneInfo[2] = 1021;
		tImproveStoneInfo[3] = 1022;
		tCheckDropEvent = FALSE;
		if (mUTIL.RandomNumber() <= 250)
		{
			tCheckDropEvent = TRUE;
			tRandomValue = rand() % 100;
			if (tRandomValue < 40)
			{
				tItemIndex = tImproveStoneInfo[0];
			}
			else if (tRandomValue < 70)
			{
				tItemIndex = tImproveStoneInfo[1];
			}
			else if (tRandomValue < 90)
			{
				tItemIndex = tImproveStoneInfo[2];
			}
			else
			{
				tItemIndex = tImproveStoneInfo[3];
			}
		}
		if (tCheckDropEvent)
		{
			mUTIL.ProcessForDropItem(1, tItemIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}
	//--------------//
	//DROP_ADD_STONE//
	//--------------//
	if (tCheckPossibleDrop)
	{
		tAddStone[0] = 1024;
		tAddStone[1] = 1025;
		tCheckDropEvent = FALSE;
		if (mUTIL.RandomNumber() <= 250)
		{
			tCheckDropEvent = TRUE;
			tRandomValue = rand() % 100;
			if (tRandomValue < 70)
			{
				tItemIndex = tAddStone[0];
			}
			else
			{
				tItemIndex = tAddStone[1];
			}
		}
		if (tCheckDropEvent)
		{
			mUTIL.ProcessForDropItem(1, tItemIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}
	// Drop Key Item
	if (tCheckPossibleDrop)
	{
		if (mUTIL.GetRandomFloat() <= 0.02f)
		{
			mUTIL.ProcessForDropItem(1, 1048, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}

	//-------------//
	//DROP_PET_ITEM//
	//-------------//
	if (tCheckPossibleDrop)
	{
		tCheckDropEvent = FALSE;
		switch (mUTIL.GetRandomInt(4))
		{
		case 0:
			if (mUTIL.GetRandomFloat() <= 0.000007f)
			{
				tCheckDropEvent = TRUE;
				tItemIndex = 1002 + mUTIL.GetRandomInt(4);
			}
			break;

		case 1:
			if ( mUTIL.GetRandomFloat() <= 0.000006f)
			{
				if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 100)
				{
					tCheckDropEvent = TRUE;
					tItemIndex = 1002 + mUTIL.GetRandomInt(4);
				}
				else
				{
					switch (mUTIL.GetRandomInt(2))
					{
					case 0:
						tCheckDropEvent = TRUE;
						tItemIndex = 1006 + mUTIL.GetRandomInt(5);
						break;
					case 1:
						tCheckDropEvent = TRUE;
						tItemIndex = 1002 + mUTIL.GetRandomInt(4);
						break;
					}
				}
			}
			break;

		case 2:
			if (mUTIL.GetRandomFloat() <= 0.000005f)
			{
				if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 100)
				{
					tCheckDropEvent = TRUE;
					tItemIndex = 1002 + mUTIL.GetRandomInt(4);
				}
				else if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 113)
				{
					switch ( mUTIL.GetRandomInt(2) )
					{
					case 0:
						tCheckDropEvent = TRUE;
						tItemIndex = 1006 + mUTIL.GetRandomInt(5);
						break;
					case 1:
						tCheckDropEvent = TRUE;
						tItemIndex = 1002 + mUTIL.GetRandomInt(4);
						break;
					}
				}
				else
				{
					switch (mUTIL.GetRandomInt(3))
					{
					case 0:
						tCheckDropEvent = TRUE;
						tItemIndex = 1011 + mUTIL.GetRandomInt(4);
						break;
					case 1:
						tCheckDropEvent = TRUE;
						tItemIndex = 1006 + mUTIL.GetRandomInt(5);
						break;
					case 2:
						tCheckDropEvent = TRUE;
						tItemIndex = 1002 + mUTIL.GetRandomInt(4);
						break;
					}
				}
			}
			break;

		case 3:
			if (mUTIL.GetRandomFloat() <= 0.000004f)
			{
				if (mGAME.mCheckZone125Server)
				{
					tCheckDropEvent = TRUE;
					tItemIndex = 1015 + mUTIL.GetRandomInt(4);
				}
				else
				{
					if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 100)
					{
						tCheckDropEvent = TRUE;
						tItemIndex = 1002 + mUTIL.GetRandomInt(4);
					}
					else if (mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 113)
					{
						switch (mUTIL.GetRandomInt(2))
						{
						case 0:
							tCheckDropEvent = TRUE;
							tItemIndex = 1006 + mUTIL.GetRandomInt(5);
							break;
						case 1:
							tCheckDropEvent = TRUE;
							tItemIndex = 1002 + mUTIL.GetRandomInt(4);
							break;
						}
					}
					else
					{
						switch (mUTIL.GetRandomInt(3))
						{
						case 0:
							tCheckDropEvent = TRUE;
							tItemIndex = 1011 + mUTIL.GetRandomInt(4);
							break;
						case 1:
							tCheckDropEvent = TRUE;
							tItemIndex = 1006 + mUTIL.GetRandomInt(5);
							break;
						case 2:
							tCheckDropEvent = TRUE;
							tItemIndex = 1002 + mUTIL.GetRandomInt(4);
							break;
						}
					}
				}
			}
			break;
		}
		if (tCheckDropEvent)
		{
			mUTIL.ProcessForDropItem(1, tItemIndex, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
	}
}
