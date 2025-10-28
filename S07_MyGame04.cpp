#include "MainApp.h"

AVATAR_OBJECT mAVATAR_OBJECT[MAX_AVATAR_OBJECT_NUM];

void AVATAR_OBJECT::Init(void)
{
	mSpiritDamage = 0;
	mSpiritDefense = 0;
	mLuck = 0;
	mIndex = 0;
	mMaxLife = 0;
	mMaxMana = 0;
	mCritical = 0;
	mAttackBlock = 0;
	mAttackPower = 0;
	mUniqueNumber = 0;
	mDefensePower = 0;
	mAttackSuccess = 0;
	mSPACE_INDEX[0] = 0;
	mSPACE_INDEX[1] = 0;
	mSPACE_INDEX[2] = 0;
	mCriticalDefense = 0;
	mDuelProcessSort = 0;
	mTradeProcessMenu = 0;
	mDuelProcessState = 0;
	mPartyProcessState = 0;
	mGuildProcessState = 0;
	mTradeProcessState = 0;
	mElementAttackPower = 0;
	mFriendProcessState = 0;
	mElementDefensePower = 0;
	mTeacherProcessState = 0;
	mCheckValidState = false;
	mDuelProcessRemainTime = 0;
	mLastAttackBonusValue = 0.0f;
	mLastAttackBonusProbability = 0;
	mCheckPossibleEatPotion = false;
	::memset(&mPShopInfo, 0x00, sizeof(PSHOP_INFO));
	::memset(&mDATA, 0x00, sizeof(OBJECT_FOR_AVATAR));
	::memset(mDuelProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mTradeProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mPartyProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mGuildProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mFriendProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
	::memset(mTeacherProcessAvatarName, 0x00, MAX_AVATAR_NAME_LENGTH);
}
void AVATAR_OBJECT::SetSpaceIndex(void)
{
	mSPACE_INDEX[0] = (int)(mDATA.aAction.aLocation[0] / MAX_RADIUS_FOR_NETWORK);
	mSPACE_INDEX[1] = (int)(mDATA.aAction.aLocation[1] / MAX_RADIUS_FOR_NETWORK);
	mSPACE_INDEX[2] = (int)(mDATA.aAction.aLocation[2] / MAX_RADIUS_FOR_NETWORK);
}
void AVATAR_OBJECT::SetBasicAbilityFromEquip(void)
{
	if (!mCheckValidState)
	{
		return;
	}

	int index01;
	AVATAR_INFO* tAvatarInfo = &mUSER[mIndex].mAvatarInfo;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		mEquipItem[index01] = mITEM.Search(tAvatarInfo->aEquip[index01][0]);
		mEquipValue[index01] = tAvatarInfo->aEquip[index01][2];
	}

	mMaxLife = GetMaxLife();
	mDATA.aMaxLifeValue = mMaxLife;
	if (mDATA.aLifeValue > mMaxLife)
	{
		mDATA.aLifeValue = mMaxLife;
	}

	mMaxMana = GetMaxMana();
	mDATA.aMaxManaValue = mMaxMana;
	if (mDATA.aManaValue > mMaxMana)
	{
		mDATA.aManaValue = mMaxMana;
	}

	mAttackPower = GetAttackPower();
	mDefensePower = GetDefensePower();
	mAttackSuccess = GetAttackSuccess();
	mAttackBlock = GetAttackBlock();
	mLuck = GetLuck();
	mCritical = GetCritical();
	mCriticalDefense = GetCriticalDefense();
	mElementAttackPower = GetElementAttackPower();
	mElementDefensePower = GetElementDefensePower();

	mLastAttackBonusProbability = 0;
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM - 8; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mLastAttackBonusProbability += mEquipItem[index01]->iLastAttackBonusInfo[0];
	}
	mLastAttackBonusValue = 0.0f;
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM - 8; index01++)
	{
		if (mEquipItem[index01] == NULL)
		{
			continue;
		}
		mLastAttackBonusValue += (float)mEquipItem[index01]->iLastAttackBonusInfo[1];
	}
	mLastAttackBonusValue *= 0.01f;

	 mLog("mMaxLife : %d\n", GetMaxLife());
	 mLog("mMaxMana : %d\n", GetMaxMana());
	 mLog("mAttackPower : %d\n", GetAttackPower());
	 mLog("mDefensePower : %d\n", GetDefensePower());
	 mLog("mAttackSuccess : %d\n", GetAttackSuccess());
	 mLog("mAttackBlock : %d\n", GetAttackBlock());
	 mLog("mElementAttackPower : %d\n", GetElementAttackPower());
	 mLog("mElementDefensePower : %d\n", GetElementDefensePower());
	 mLog("mCritical : %d\n", GetCritical());
	 mLog("mCriticalDefense : %d\n", GetCriticalDefense());
	 mLog("Luck : %d\n", GetLuck());
	 mLog("SpiritDamage : %d\n", mSpiritDamage);
	 mLog("SpiritDefense : %d\n\n", mSpiritDefense);
}
int AVATAR_OBJECT::GetWeaponClass(void)
{
	if (mEquipItem[7] == NULL)
	{
		return 0;
	}
	switch (mEquipItem[7]->iSort)
	{
	case 13: return 1;
	case 14: return 2;
	case 15: return 3;
	case 16: return 1;
	case 17: return 2;
	case 18: return 3;
	case 19: return 1;
	case 20: return 2;
	case 21: return 3;
	}
	return 0;
}
int AVATAR_OBJECT::GetWeaponType(void)
{
	if (mEquipItem[7] == NULL)
	{
		return 0;
	}
	switch (mEquipItem[7]->iSort)
	{
	case 13: return 13;
	case 14: return 14;
	case 15: return 15;
	case 16: return 16;
	case 17: return 17;
	case 18: return 18;
	case 19: return 19;
	case 20: return 20;
	case 21: return 21;
	}
	return 0;
}
int AVATAR_OBJECT::GetWeaponTypeForTransfer(int tNewTribe)
{
	if (mEquipItem[7] == NULL)
	{
		return 0;
	}
	if (tNewTribe == 0)
	{
		switch (mEquipItem[7]->iSort)
		{
		case 13: return 13;
		case 14: return 14;
		case 15: return 15;
		case 16: return 14;
		case 17: return 13;
		case 18: return 15;
		case 19: return 13;
		case 20: return 14;
		case 21: return 15;
		}
	}
	if (tNewTribe == 1)
	{
		switch (mEquipItem[7]->iSort)
		{
		case 13: return 17;
		case 14: return 16;
		case 15: return 18;
		case 16: return 16;
		case 17: return 17;
		case 18: return 18;
		case 19: return 17;
		case 20: return 16;
		case 21: return 18;
		}
	}
	if (tNewTribe == 2)
	{
		switch (mEquipItem[7]->iSort)
		{
		case 13: return 19;
		case 14: return 20;
		case 15: return 21;
		case 16: return 20;
		case 17: return 19;
		case 18: return 21;
		case 19: return 19;
		case 20: return 20;
		case 21: return 21;
		}
	}
	return 0;
}
//GET_MAX_LIFE
int AVATAR_OBJECT::GetMaxLife(void)
{
	int tVitality = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tMountSort = 0;
	int tItemSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tFeed = 0, tExp = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;
	int tISValue = 0, tIUValue = 0;
	int mMaxLife = 0;

	tVitality = mUSER[mIndex].mAvatarInfo.aVit + GetCallVitality();
	tVitality += mUSER[mIndex].mAvatarInfo.aUpgradeValue;
	for (i = 0; i < 21; i++)
	{
		if (mEquipValue[i])
		{
			tVitality += mEquipItem[i]->iVitality;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tVitality += tITEM->iVitality;
	}
	tVitality += ReturnVitalityUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tVitality += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	mMaxLife += (int)((float)tVitality * 20.0f);

	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mMaxLife += 825;
	}
	else if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mMaxLife += 550;
	}
	for (i = 9; i < 13; i++)
	{
		mMaxLife += mITEM.ReturnLegendDecoStats(1, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
	}
	for (i = 0; i < 13; i++)
	{
		if (mEquipValue[i])
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipValue[i]);
			if (i == 0 || i == 2 || i == 3 || i == 4 || i == 5 || i == 7)
			{
				if (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12)
				{
					mMaxLife += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 100);
				}
				if (mMaxLife < 0)
					mMaxLife = 0;
			}
		}
	}
	if (mZONEMAININFO.CheckLevelBattleZoneNumber2() == 0 && mZONEMAININFO.Check267TypeZoneNumber2() == 0 || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mMaxLife += 20 * mUSER[mIndex].mAvatarInfo.aEatLifePotion;
	}
	mMaxLife += (int)mLEVEL.ReturnLevelFactorLife(mUSER[mIndex].mAvatarInfo.aLevel1 + mUSER[mIndex].mAvatarInfo.aLevel2);

	if (mUSER[mIndex].mAvatarInfo.aHealthBoostScroll > 0 || mUSER[mIndex].mAvatarInfo.aHeroPill > 0)
	{
		mMaxLife = (int)((float)mMaxLife * 1.20f);
	}
	switch (mDATA.aAnimalNumber)
	{
	case 1302:
	case 1320:
		mMaxLife = (int)((float)mMaxLife * 1.05f);
		break;
	case 1305:
	case 17045:
	case 1321:
	case 17049:
		mMaxLife = (int)((float)mMaxLife * 1.10f);
		break;
	case 1308:
	case 1322:
	case 17058:
	case 1329:
	case 17059:
	case 819:
	case 821:
		mMaxLife = (int)((float)mMaxLife * 1.15f);
		break;
	case 1331:
		mMaxLife = (int)((float)mMaxLife * 1.20f);
		break;
	case 17061:
		mMaxLife = (int)((float)mMaxLife * 1.20f);
		break;
	}
	if (tMountSort)
	{
		mMaxLife += (int)((float)mUTIL.ReturnEliteMountStats(0, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * mMaxLife);
	}
	if (mMaxLife >= mPAT.ReturnLifeValue(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]))
	{
		mMaxLife += (int)mPAT.ReturnLifeValue(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]);
	}
	else
	{
		mMaxLife *= 2;
	}
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);
	if (tWarlordState == 13)
	{
		mMaxLife += 1000;
	}
	else if (tWarlordState == 18)
	{
		mMaxLife += 1100;
	}

	for (i = 0; i < 13; i++)
	{
		if (mEquipItem[i])
		{
			if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4)
			{
				tIsUltimate = 1;
				if (i == 0)
				{
					tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]);
					if (tISValue > 0)
					{
						if (tISValue > 100)
						{
							tISValue -= 100;
						}
						mMaxLife += 500 * tISValue;
					}
				}
			}
			mMaxLife += mSOCKET.GetSocketInfo(3, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}
	if (tIsUltimate == 1)
	{
		mMaxLife += 30000;
	}
	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 6)
	{
		mMaxLife += 1000;
	}
	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mMaxLife += 100 * s3;
		}
	}
	mMaxLife += ReturnSetItemIUValue_LifeUp(&mUSER[mIndex].mAvatarInfo);

	mMaxLife += (int)mPAT.ReturnAmuletHP(mUSER[mIndex].mAvatarInfo.aEquip[8][0]);

	mMaxLife += mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 2);

	mMaxLife += (int)mPAT.ReturnAmuletPetability3(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 2);

	mMaxLife += (int)mPAT.ReturnLegendPetHPStat(mUSER[mIndex].mAvatarInfo.aEquip[8][0]);

	mMaxLife += (int)mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 3);

	if (mUSER[mIndex].mAvatarInfo.aVigilanteScroll > 0)
	{
		mMaxLife += 500;
	}
	if (mUTIL.ReturnWineState(mIndex, 878))
	{
		mMaxLife -= (int)((float)mMaxLife * 0.10f);
	}

	return mMaxLife;
}
//GET_MAX_MANA
int AVATAR_OBJECT::GetMaxMana(void)
{
	int tKi = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tMountSort = 0;
	int tItemSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tFeed = 0, tExp = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;
	int tISValue = 0, tIUValue = 0;
	int mMaxMana = 0;

	tKi = mUSER[mIndex].mAvatarInfo.aInt + GetCallKi();
	tKi += mUSER[mIndex].mAvatarInfo.aUpgradeValue;

	for (i = 0; i < 21; i++)
	{
		if (mEquipItem[i])
		{
			tKi += mEquipItem[i]->iKi;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tKi += tITEM->iKi;
	}
	tKi += ReturnKiUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tKi += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	mMaxMana += (int)((float)tKi * 15.31f);

	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mMaxMana += 750;
	}
	else if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mMaxMana += 500;
	}
	for (i = 9; i < 13; i++)
	{
		mMaxMana += mITEM.ReturnLegendDecoStats(2, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
	}
	for (i = 0; i < 13; i++)
	{
		if (mEquipItem[i])
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 0 || i == 2 || i == 3 || i == 4 || i == 5 || i == 7)
			{
				if (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12)
				{
					mMaxMana += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 110);
				}
				if (mMaxMana < 0)
					mMaxMana = 0;
			}
		}
	}
	if (mZONEMAININFO.CheckLevelBattleZoneNumber2() == 0 && mZONEMAININFO.Check267TypeZoneNumber2() == 0 || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mMaxMana += 25 * mUSER[mIndex].mAvatarInfo.aEatManaPotion;
	}
	mMaxMana += (int)mLEVEL.ReturnLevelFactorMana(mUSER[mIndex].mAvatarInfo.aLevel1 + mUSER[mIndex].mAvatarInfo.aLevel2);

	switch (mDATA.aAnimalNumber)
	{
	case 1301:
	case 1302:
	case 7011:
	case 1303:
	case 1313:
	case 1317:
	case 1320:
	case 1323:
	case 1326:
		mMaxMana = (int)((float)mMaxMana * 1.05f);
		break;
	case 1304:
	case 17044:
	case 1305:
	case 17045:
	case 1306:
	case 17046:
	case 1314:
	case 17047:
	case 1318:
	case 17048:
	case 1321:
	case 17049:
	case 1324:
	case 17050:
	case 1327:
	case 17051:
	case 559:
		mMaxMana = (int)((float)mMaxMana * 1.10f);
		break;
	case 1307:
	case 1308:
	case 1309:
	case 1315:
	case 1319:
	case 1322:
	case 17058:
	case 1325:
	case 1328:
	case 814:
	case 815:
	case 816:
	case 817:
	case 818:
	case 819:
	case 820:
	case 821:
		mMaxMana = (int)((float)mMaxMana * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mMaxMana += (int)((float)mUTIL.ReturnEliteMountStats(1, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mMaxMana);
	}

	if (mMaxMana >= mPAT.ReturnManaValue(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]))
	{
		mMaxMana += (int)mPAT.ReturnManaValue(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]);
	}
	else
	{
		mMaxMana *= 2;
	}

	tWarlordState = mUTIL.GetWarlordSetState(mIndex);
	if (tWarlordState == 13)
	{
		mMaxMana += 1000;
	}
	else if (tWarlordState == 18)
	{
		mMaxMana += 1100;
	}

	for (i = 0; i < 13; i++)
	{
		if (mEquipItem[i])
		{
			mMaxMana += mSOCKET.GetSocketInfo(4, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mMaxMana += 100 * s4;
		}
	}

	mMaxMana += (int)mPAT.ReturnAmuletPetMP(mUSER[mIndex].mAvatarInfo.aEquip[8][0]);

	mMaxMana += mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 2);

	mMaxMana += (int)mPAT.ReturnLegendPetMPStat(mUSER[mIndex].mAvatarInfo.aEquip[8][0]);

	mMaxMana += (int)mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 3);

	return mMaxMana;
}
//GET_ATTACK_POWER
int AVATAR_OBJECT::GetAttackPower(void)
{
	int mAttackPower = 0;
	int tKi = 0;
	int tStr = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tStr = mUSER[mIndex].mAvatarInfo.aStr + GetCallStrength() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;
	tKi += mUSER[mIndex].mAvatarInfo.aInt + GetCallKi() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;

	for (i = 0; i < 21; i++)
	{
		if (mEquipItem[i])
		{
			tStr += mEquipItem[i]->iStrength;
			tKi += mEquipItem[i]->iKi;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tStr += tITEM->iStrength;
		tKi += tITEM->iKi;
	}
	tStr += ReturnStrengthUp();
	tKi += ReturnKiUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tStr += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
		tKi += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);
	if (mEquipItem[7])
	{
		switch (mEquipItem[7]->iSort)
		{
		case 13:
		case 17:
		case 19:
			mAttackPower += (int)((float)tStr * 2.65f) + (int)((float)tKi * 1.43f);
			break;
		case 14:
		case 16:
		case 20:
			mAttackPower += (int)((float)tStr * 2.80f) + (int)((float)tKi * 1.51f);
			break;
		case 15:
		case 18:
		case 21:
			mAttackPower += (int)((float)tStr * 2.51f) + (int)((float)tKi * 1.35f);
			break;
		default:
			break;
		}
	}
	else
	{
		mAttackPower += (int)((float)tStr * 1.25f) + (int)((float)tKi * 0.67f);
	}

	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mAttackPower += 413;
	}
	else if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mAttackPower += 275;
	}

	mAttackPower += mLEVEL.ReturnLevelFactorAttackPower(mUSER[mIndex].mAvatarInfo.aLevel2 + mUSER[mIndex].mAvatarInfo.aLevel1);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackPower += mEquipItem[i]->iAttackPower;
			if (i != 8)
			{
				tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
				switch (tWarlordState)
				{
				case 2:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.40f);
					break;
				case 4:
				case 12:
				case 17:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.60f);
					break;
				case 5:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 1.0f);
					break;
				case 7:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.40f);
					break;
				case 9:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.60f);
					break;
				case 10:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 1.0f);
					break;
				case 14:
				case 19:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.70f);
					break;
				case 15:
				case 20:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 1.10f);
					break;
				case 21:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.20f);
					break;
				case 22:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
						{
							mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.55f);
						}
						else
						{
							mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 1.10f);
						}
					}
					break;
				case 50:
					mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * 0.55f);
					break;
				default:
					break;
				}
				if (i == 1 && tItemSort != 9 && mEquipItem[i]->iSort == 29)
				{
					tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					if (tISValue > 0)
					{
						mAttackPower += 6 * tISValue;
					}
				}
				if (i == 7)
				{
					if (mUTIL.ReturnItemSort(mEquipItem[7]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue >= 100)
							{
								tISValue -= 100;
							}
							mAttackPower += 1200 * tISValue;
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						mAttackPower += mUTIL.ReturnSetItemIUValue_AttackPower(i, tIUValue, tWarlordState);
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						if (tISValue > 0)
						{
							mAttackPower += (int)((float)mEquipItem[i]->iAttackPower * ((float)tISValue * 0.03f));
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 3)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						mAttackPower += mUTIL.ReturnSet3ItemIUValue_AttackPower(tISValue);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 1);
						mAttackPower += tIUEffectValue * tIUValue;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						if (tISValue > 0)
							mAttackPower += (int)((float)(tIUEffectValue * tIUValue + mEquipItem[i]->iAttackPower) * ((float)tISValue * 0.03f));
					}
				}
				if (i == 10)
				{
					tWingValue = 0.0f;
					if (mEquipItem[i]->iIndex == 213 || mEquipItem[i]->iIndex == 214 || mEquipItem[i]->iIndex == 215 || mEquipItem[i]->iIndex == 216 || mEquipItem[i]->iIndex == 217 || mEquipItem[i]->iIndex == 218 || mEquipItem[i]->iIndex == 2303 || mEquipItem[i]->iIndex == 2304 || mEquipItem[i]->iIndex == 2305)
					{
						tWingValue = 23.4f;
					}
					else if (mEquipItem[i]->iIndex == 219 || mEquipItem[i]->iIndex == 220 || mEquipItem[i]->iIndex == 221)
					{
						tWingValue = 40.0f;
					}
					else if (mEquipItem[i]->iIndex == 222 || mEquipItem[i]->iIndex == 223 || mEquipItem[i]->iIndex == 224)
					{
						tWingValue = 50.0f;
					}
					else if (mEquipItem[i]->iIndex == 225 || mEquipItem[i]->iIndex == 226 || mEquipItem[i]->iIndex == 227)
					{
						tWingValue = 60.0f;
					}
					else if (mEquipItem[i]->iIndex == 228 || mEquipItem[i]->iIndex == 229 || mEquipItem[i]->iIndex == 230)
					{
						tWingValue = 70.0f;
					}
					else
					{
						tWingValue = 11.7f;
					}
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mAttackPower += mITEM.ReturnLegendDecoStats(3, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					else
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
							mAttackPower += (int)((float)tISValue * tWingValue);
					}
				}
				if ((i == 9 || i == 11 || i == 12) && mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
				{
					mAttackPower += mITEM.ReturnLegendDecoStats(3, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mAttackPower += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 10);
					if (mAttackPower < 1)
						mAttackPower = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mAttackPower += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 10);
				if (mAttackPower < 1)
					mAttackPower = 1;
			}
		}
	}
	if (mZONEMAININFO.CheckLevelBattleZoneNumber2() == 0 && mZONEMAININFO.Check267TypeZoneNumber2() == 0 || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mAttackPower += 3 * mUSER[mIndex].mAvatarInfo.aEatStrengthPotion;
	}
	if (mUSER[mIndex].mAvatarInfo.aDamageBoostScroll > 0 || mUSER[mIndex].mAvatarInfo.aHeroPill > 0)
	{
		mAttackPower = (int)((float)mAttackPower * 1.10f);
	}
	if (mUSER[mIndex].mAvatarInfo.aFuryState == 1)
	{
		mAttackPower = (int)(mUTIL.ReturnRageDmgUp(mUSER[mIndex].mAvatarInfo.aFuryCount) * (float)mAttackPower);
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1301:
	case 1313:
	case 1317:
		mAttackPower = (int)((float)mAttackPower * 1.05f);
		break;
	case 7011:
		mAttackPower = (int)((float)mAttackPower * 1.05f);
		break;
	case 1304:
	case 17044:
	case 1314:
	case 17047:
	case 1318:
	case 17048:
	case 510:
	case 559:
		mAttackPower = (int)((float)mAttackPower * 1.10f);
		break;
	case 1307:
	case 1315:
	case 1319:
	case 511:
	case 1329:
	case 17059:
	case 814:
	case 818:
	case 820:
		mAttackPower = (int)((float)mAttackPower * 1.15f);
		break;
	case 1330:
		mAttackPower = (int)((float)mAttackPower * 1.20f);
		break;
	case 17060:
		mAttackPower = (int)((float)mAttackPower * 1.20f);
		break;
	}
	if (tMountSort)
	{
		mAttackPower += (int)((float)mUTIL.ReturnEliteMountStats(2, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mAttackPower);
	}

	if (mUSER[mIndex].mEffectValue[0][0] > 0)
	{
		mAttackPower = (int)((float)(mAttackPower * (mUSER[mIndex].mEffectValue[0][0] + 100)) * 0.01f);
	}

	if (mAttackPower >= (int)mPAT.ReturnAttackPower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]))
	{
		mAttackPower += (int)mPAT.ReturnAttackPower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
	}
	else
	{
		mAttackPower *= 2;
	}

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackPower += mSOCKET.GetSocketInfo(1, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}

	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 7)
		mAttackPower += 500;

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mAttackPower += 50 * s1;
		}
	}

	mAttackPower += (int)mPAT.ReturnAdditionalDamagePower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]);

	/*if (mUSER[mIndex].mMixSkillWaitingTime[0] > 0)
		mAttackPower += (int)((float)mAttackPower * 0.05f);*/
	if (mUTIL.ReturnWineState(mIndex, 878))
		mAttackPower += (int)((float)mAttackPower * 0.10f);
	if (mUTIL.ReturnWineState(mIndex, 879))
		mAttackPower -= (int)((float)mAttackPower * 0.20f);

	if (mGAME.ReturnTribeRole(mUSER[mIndex].mAvatarInfo.aName, mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mAttackPower += 200;
	}
	else if (mGAME.ReturnTribeRole(mUSER[mIndex].mAvatarInfo.aName, mUSER[mIndex].mAvatarInfo.aTribe) == 2)
	{
		mAttackPower += 100;
	}

	mAttackPower += (int)mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 1);

	mAttackPower += (int)mPAT.ReturnAmuletPetability3(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 1);

	mAttackPower += (int)(mPAT.ReturnPetAddSkillPoint2(1, 1, mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]) * (float)mAttackPower / 100.0f);

	mAttackPower += (int)mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 1);

	return mAttackPower;
}
//GET_DEFENSE_POWER
int AVATAR_OBJECT::GetDefensePower(void)
{
	int mDefensePower = 0;
	int tDex = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tDex += mUSER[mIndex].mAvatarInfo.aDex + GetCallWisdom() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;

	for (i = 0; i < 21; i++)
	{
		if (mEquipItem[i])
		{
			tDex += mEquipItem[i]->iWisdom;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tDex += tITEM->iWisdom;
	}
	tDex += ReturnWisdomUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tDex += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	mDefensePower += (int)((float)tDex * 1.63f);

	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mDefensePower += 825;
	}
	else if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1 &&
		mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&
		mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0)
	{
		mDefensePower += 550;
	}

	mDefensePower += mLEVEL.ReturnLevelFactorDefensePower(mUSER[mIndex].mAvatarInfo.aLevel2 + mUSER[mIndex].mAvatarInfo.aLevel1);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mDefensePower += mEquipItem[i]->iDefensePower;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 2:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.40f);
					break;
				case 3:
				case 12:
				case 17:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.60f);
					break;
				case 5:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 1.0f);
					break;
				case 7:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.40f);
					break;
				case 9:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.60f);
					break;
				case 10:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 1.0f);
					break;
				case 13:
				case 19:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.70f);
					break;
				case 15:
				case 20:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 1.10f);
					break;
				case 21:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.20f);
					break;
				case 22:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4)
						{
							mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.55f);
						}
						else
						{
							mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 1.10f);
						}
					}
					break;
				case 50:
					mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * 0.55f);
					break;
				default:
					break;
				}
				switch (i)
				{
				case 1:
					if (mEquipItem[i]->iSort == 29)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
						mDefensePower += mUTIL.ReturnSetItemIUValue_DefensePower(i, tIUValue, tWarlordState);;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 2);
						mDefensePower += tIUEffectValue * tIUValue;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2]);
						if (tISValue > 0)
							mDefensePower += 6 * tISValue;
					}
					break;
				case 2:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue >= 100)
								tISValue -= 100;
							mDefensePower += 1000 * tISValue;
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						mDefensePower += mUTIL.ReturnSetItemIUValue_DefensePower(i, tIUValue, tWarlordState);;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						if (tISValue > 0)
						{
							mDefensePower += (int)((float)mEquipItem[i]->iDefensePower * ((float)tISValue * 0.03f));
						}
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 2);
						mDefensePower += tIUEffectValue * tIUValue;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						if (tISValue > 0)
							mDefensePower += (int)((float)(tIUEffectValue * tIUValue + mEquipItem[i]->iDefensePower) * ((float)tISValue * 0.03f));
					}
					break;
				case 3:
					if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						mDefensePower += mUTIL.ReturnSetItemIUValue_DefensePower(i, tIUValue, tWarlordState);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 2);
						mDefensePower += tIUEffectValue * tIUValue;
					}
					break;
				case 5:
					if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						mDefensePower += mUTIL.ReturnSetItemIUValue_DefensePower(i, tIUValue, tWarlordState);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 2);
						mDefensePower += tIUEffectValue * tIUValue;
					}
					break;
				case 9:
				case 11:
				case 12:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mDefensePower += mITEM.ReturnLegendDecoStats(4, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					break;
				case 10:
					if (mEquipItem[i]->iIndex == 204 || mEquipItem[i]->iIndex == 205 || mEquipItem[i]->iIndex == 206 || mEquipItem[i]->iIndex == 216 || mEquipItem[i]->iIndex == 217 || mEquipItem[i]->iIndex == 218 || mEquipItem[i]->iIndex == 2303 || mEquipItem[i]->iIndex == 2304 || mEquipItem[i]->iIndex == 2305)
					{
						tWingValue = 48.75f;
					}
					else if (mEquipItem[i]->iIndex == 219 || mEquipItem[i]->iIndex == 220 || mEquipItem[i]->iIndex == 221)
					{
						tWingValue = 45.0f;
					}
					else if (mEquipItem[i]->iIndex == 222 || mEquipItem[i]->iIndex == 223 || mEquipItem[i]->iIndex == 224)
					{
						tWingValue = 55.0f;
					}
					else if (mEquipItem[i]->iIndex == 225 || mEquipItem[i]->iIndex == 226 || mEquipItem[i]->iIndex == 227)
					{
						tWingValue = 65.0f;
					}
					else if (mEquipItem[i]->iIndex == 228 || mEquipItem[i]->iIndex == 229 || mEquipItem[i]->iIndex == 230)
					{
						tWingValue = 75.0f;
					}
					else
					{
						tWingValue = 24.35f;
					}
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mDefensePower += mITEM.ReturnLegendDecoStats(4, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					else
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
							mDefensePower += (int)((double)tISValue * tWingValue);
					}
					break;
				default:
					continue;
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mDefensePower += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 20);
					if (mDefensePower < 1)
						mDefensePower = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mDefensePower += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 20);
				if (mDefensePower < 1)
					mDefensePower = 1;
			}
		}
	}
	switch (mDATA.aAnimalNumber)
	{
	case 1326:
		mDefensePower = (int)((float)mDefensePower * 1.05f);
		break;
	case 1327:
		mDefensePower = (int)((float)mDefensePower * 1.10f);
		break;
	case 17051:
		mDefensePower = (int)((float)mDefensePower * 1.10f);
		break;
	case 1328:
	case 816:
		mDefensePower = (int)((float)mDefensePower * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mDefensePower += (int)((float)mUTIL.ReturnEliteMountStats(3, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mDefensePower);
	}

	if (mUSER[mIndex].mEffectValue[1][0] > 0)
	{
		mDefensePower = (int)((float)(mDefensePower * (mUSER[mIndex].mEffectValue[1][0] + 100)) * 0.01f);
	}

	if (mDefensePower >= (int)mPAT.ReturnDefensePower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]))
	{
		mDefensePower += (int)mPAT.ReturnDefensePower(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
	}
	else
	{
		mDefensePower *= 2;
	}

	if (mDATA.aGuildBuff == 1 && mDATA.aBuffSort == 4)
	{
		if (mDefensePower >= 500)
		{
			mDefensePower += 500;
		}
		else
		{
			mDefensePower *= 2;
		}
	}

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mDefensePower += mSOCKET.GetSocketInfo(2, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}

	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 1)
		mDefensePower += 1000;

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mDefensePower += 100 * s2;
		}
	}

	if (mUTIL.ReturnWineState(mIndex, 879))
	{
		mDefensePower *= 2;
	}
	if (mGAME.ReturnTribeRole(mUSER[mIndex].mAvatarInfo.aName, mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mDefensePower += 200;
	}
	else if (mGAME.ReturnTribeRole(mUSER[mIndex].mAvatarInfo.aName, mUSER[mIndex].mAvatarInfo.aTribe) == 2)
	{
		mDefensePower += 100;
	}

	mDefensePower += (int)mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 2);

	return mDefensePower;
}
//GET_ATTACK_SUCCESS
int AVATAR_OBJECT::GetAttackSuccess(void)
{
	int mAttackSuccess = 0;
	int tStr = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tStr += mUSER[mIndex].mAvatarInfo.aStr + GetCallStrength() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;

	for (i = 0; i < 21; i++)
	{
		if (mEquipItem[i])
		{
			tStr += mEquipItem[i]->iStrength;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tStr += tITEM->iStrength;
	}
	tStr += ReturnStrengthUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tStr += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	mAttackSuccess += (int)((float)tStr * 1.71f);

	mAttackSuccess += mLEVEL.ReturnLevelFactorAttackSuccess(mUSER[mIndex].mAvatarInfo.aLevel2 + mUSER[mIndex].mAvatarInfo.aLevel1);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackSuccess += mEquipItem[i]->iAttackSucess;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 3:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.60f);
					break;
				case 5:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 1.0f);
					break;
				case 8:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.40f);
					break;
				case 9:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.60f);
					break;
				case 10:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 1.0f);
					break;
				case 13:
				case 18:
				case 19:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.70f);
					break;
				case 15:
				case 20:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 1.10f);
					break;
				case 21:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.20f);
					break;
				case 22:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
						{
							mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.55f);
						}
						else
						{
							mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 1.10f);
						}
					}
					break;
				case 50:
					mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * 0.55f);
					break;
				default:
					break;
				}
				if (i == 3)
				{
					if (mUTIL.ReturnItemSort(mEquipItem[3]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue >= 100)
								tISValue -= 100;
							mAttackSuccess += 1500 * tISValue;
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						mAttackSuccess += mUTIL.ReturnSetItemIUValue_AttackSuccess(i, tIUValue, tWarlordState);
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						if (tISValue > 0)
							mAttackSuccess += (int)((float)mEquipItem[i]->iAttackSucess * ((float)tISValue * 0.03f));
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 3);
						mAttackSuccess += tIUEffectValue * tIUValue;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[3][2]);
						if (tISValue > 0)
							mAttackSuccess += (int)((float)(tIUEffectValue * tIUValue + mEquipItem[i]->iAttackSucess) * ((float)tISValue * 0.03f));
					}
				}
				else if (i == 7)
				{
					if (mEquipItem[7]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						mAttackSuccess += mUTIL.ReturnSetItemIUValue_AttackSuccess(i, tIUValue, tWarlordState);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[7][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 3);
						mAttackSuccess += tIUEffectValue * tIUValue;
					}
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mAttackSuccess += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 30);
					if (mAttackSuccess < 1)
						mAttackSuccess = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mAttackSuccess += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 30);
				if (mAttackSuccess < 1)
					mAttackSuccess = 1;
			}
		}
	}
	if (!mZONEMAININFO.CheckLevelBattleZoneNumber2() && !mZONEMAININFO.Check267TypeZoneNumber2() || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mAttackSuccess += 2 * mUSER[mIndex].mAvatarInfo.aEatAgilityPotion;
	}
	if (mDATA.aGuildBuff == 1 && !mDATA.aBuffSort)
	{
		mAttackSuccess = (int)((float)mAttackSuccess * 1.10f);
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1313:
		mAttackSuccess = (int)((float)mAttackSuccess * 1.05f);
		break;
	case 1314:
	case 17047:
	case 510:
		mAttackSuccess = (int)((float)mAttackSuccess * 1.10f);
		break;
	case 1315:
	case 511:
	case 820:
		mAttackSuccess = (int)((float)mAttackSuccess * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mAttackSuccess += (int)((float)mUTIL.ReturnEliteMountStats(4, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mAttackSuccess);
	}

	if (mUSER[mIndex].mEffectValue[2][0] > 0)
	{
		mAttackSuccess = (int)((float)(mAttackSuccess * (mUSER[mIndex].mEffectValue[2][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mEffectValue[17][0] > 0)
	{
		mAttackSuccess = (int)((float)(mAttackSuccess * (mUSER[mIndex].mEffectValue[17][0] + 100)) * 0.01f);
	}
	if (tWarlordState == 14)
	{
		mAttackSuccess += 100;
	}

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackSuccess += mSOCKET.GetSocketInfo(5, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}

	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 5)
	{
		mAttackSuccess += 1000;
	}

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mAttackSuccess += 100 * s5;
		}
	}

	mAttackSuccess += mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 3);

	if (mUTIL.ReturnWineState(mIndex, 881))
	{
		mAttackSuccess -= (int)((float)mAttackSuccess * 0.20f);
	}

	return mAttackSuccess;
}
//GET_ATTACK_BLOCK
int AVATAR_OBJECT::GetAttackBlock(void)
{
	int mAttackBlock = 0;
	int tVit = 0;
	int tDex = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tIsUltimate = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tVit += mUSER[mIndex].mAvatarInfo.aVit + GetCallVitality() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;
	tDex += mUSER[mIndex].mAvatarInfo.aDex + GetCallWisdom() + mUSER[mIndex].mAvatarInfo.aUpgradeValue;

	for (i = 0; i < 21; i++)
	{
		if (mEquipItem[i])
		{
			tVit += mEquipItem[i]->iVitality;
			tDex += mEquipItem[i]->iWisdom;
		}
	}
	tITEM = mITEM.Search(mDATA.aFashionNumber);
	if (tITEM && (tITEM->iSort == 35 || tITEM->iSort == 36))
	{
		tVit += tITEM->iVitality;
		tDex += tITEM->iWisdom;
	}
	tVit += ReturnVitalityUp();
	tDex += ReturnWisdomUp();
	if (mDATA.aAnimalAbsorbState == 1)
	{
		tVit += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
		tDex += mUTIL.ReturnMountAbsorbAddStat(mDATA.aAnimalNumber);
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	mAttackBlock += (int)((float)tDex * 1.67f) + (int)((float)tVit * 0.90f);

	mAttackBlock += mLEVEL.ReturnLevelFactorAttackBlock(mUSER[mIndex].mAvatarInfo.aLevel2 + mUSER[mIndex].mAvatarInfo.aLevel1);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackBlock += mEquipItem[i]->iAttackBlock;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 3:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.60f);
					break;
				case 4:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.60f);
					break;
				case 5:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 1.0f);
					break;
				case 8:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.40f);
					break;
				case 9:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.60f);
					break;
				case 10:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 1.0f);
					break;
				case 13:
				case 14:
				case 18:
				case 19:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.70f);
					break;
				case 15:
				case 20:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 1.10f);
					break;
				case 21:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.20f);
					break;
				case 22:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
						{
							mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.55f);
						}
						else
						{
							mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 1.10f);
						}
					}
					break;
				case 50:
					mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * 0.55f);
					break;
				default:
					break;
				}
				switch (i)
				{
				case 2:
					if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						mAttackBlock += mUTIL.ReturnSetItemIUValue_AttackBlock(i, tIUValue, tWarlordState);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[2][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 4);
						mAttackBlock += tIUEffectValue * tIUValue;
					}
					break;
				case 5:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue >= 100)
								tISValue -= 100;
							mAttackBlock += 300 * tISValue;
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						mAttackBlock += mUTIL.ReturnSetItemIUValue_AttackBlock(i, tIUValue, tWarlordState);
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						if (tISValue > 0)
							mAttackBlock += (int)((float)mEquipItem[i]->iAttackBlock * ((float)tISValue * 0.03f));
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 4);
						mAttackBlock += tIUEffectValue * tIUValue;
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[5][2]);
						if (tISValue > 0)
							mAttackBlock += (int)((float)(tIUEffectValue * tIUValue + mEquipItem[i]->iAttackBlock) * ((float)tISValue * 0.03f));
					}
					break;
				case 9:
				case 10:
				case 11:
				case 12:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mAttackBlock += mITEM.ReturnLegendDecoStats(6, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					break;
				default:
					continue;
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mAttackBlock += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 40);
					if (mAttackBlock < 1)
						mAttackBlock = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mAttackBlock += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 40);
				if (mAttackBlock < 1)
					mAttackBlock = 1;
			}
		}
	}
	if (!mZONEMAININFO.CheckLevelBattleZoneNumber2() && !mZONEMAININFO.Check267TypeZoneNumber2() || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mAttackBlock += 2 * mUSER[mIndex].mAvatarInfo.aEatAgilityPotion;
	}
	if (mDATA.aGuildBuff == 1 && mDATA.aBuffSort == 1)
	{
		mAttackBlock = (int)((float)mAttackBlock * 1.10f);
	}

	switch (mDATA.aAnimalNumber)
	{
	case 1323:
	case 1326:
		mAttackBlock = (int)((float)mAttackBlock * 1.05f);
		break;
	case 1324:
	case 17050:
	case 1327:
	case 17051:
		mAttackBlock = (int)((float)mAttackBlock * 1.10f);
		break;
	case 1325:
	case 1328:
	case 815:
	case 816:
		mAttackBlock = (int)((float)mAttackBlock * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mAttackBlock += (int)((float)mUTIL.ReturnEliteMountStats(5, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mAttackBlock);
	}

	if (mUSER[mIndex].mEffectValue[3][0] > 0)
	{
		mAttackBlock = (int)((float)(mAttackBlock * (mUSER[mIndex].mEffectValue[3][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mEffectValue[18][0] > 0)
	{
		mAttackBlock = (int)((float)(mAttackBlock * (mUSER[mIndex].mEffectValue[18][0] + 100)) * 0.01f);
	}

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mAttackBlock += mSOCKET.GetSocketInfo(6, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}

	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 4)
	{
		mAttackBlock += 1000;
	}

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mAttackBlock += 100 * s6;
		}
	}

	mAttackBlock += mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 3);

	if (mUTIL.CheckSpecialSkillState(mIndex, 1, 91389, 0, -1, -1, -1) == 1)
	{
		mAttackBlock += (int)((float)mAttackBlock * 0.10f);
	}

	return mAttackBlock;
}
//GET_ELEMENT_ATTACK_POWER
int AVATAR_OBJECT::GetElementAttackPower(void)
{
	int mElementAttackPower = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mElementAttackPower += mEquipItem[i]->iElementAttackPower;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 1:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.40f);
					break;
				case 5:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 1.0f);
					break;
				case 6:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.40f);
					break;
				case 10:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 1.0f);
					break;
				case 11:
				case 16:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.60f);
					break;
				case 15:
				case 20:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 1.10f);
					break;
				case 21:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.20f);
					break;
				case 22:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
						{
							mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.55f);
						}
						else
						{
							mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 1.10f);
						}
					}
					break;
				case 50:
					mElementAttackPower += (int)((float)mEquipItem[i]->iElementAttackPower * 0.55f);
					break;
				default:
					break;
				}
				if (i == 4)
				{
					if (mUTIL.ReturnItemSort(mEquipItem[4]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue > 100)
								tISValue -= 100;
							mElementAttackPower += 200 * tISValue;
						}
					}
					else if (mEquipItem[i]->iCheckItemSet == 2)
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[4][2]);
						mElementAttackPower += mUTIL.ReturnSetItemIUValue_ElementAttackPower(i, tIUValue, tWarlordState);
					}
					else
					{
						tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[4][2]);
						tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 5);
						mElementAttackPower += tIUEffectValue * tIUValue;
					}
				}
				else if (i == 10)
				{
					if (mEquipItem[10]->iIndex == 210 || mEquipItem[i]->iIndex == 211 || mEquipItem[i]->iIndex == 212 || mEquipItem[i]->iIndex == 216 || mEquipItem[i]->iIndex == 217 || mEquipItem[i]->iIndex == 218 || mEquipItem[i]->iIndex == 2303 || mEquipItem[i]->iIndex == 2304 || mEquipItem[i]->iIndex == 2305)
					{
						tWingValue = 7.80f;
					}
					else if (mEquipItem[i]->iIndex == 219 || mEquipItem[i]->iIndex == 220 || mEquipItem[i]->iIndex == 221)
					{
						tWingValue = 15.0f;
					}
					else if (mEquipItem[i]->iIndex == 222 || mEquipItem[i]->iIndex == 223 || mEquipItem[i]->iIndex == 224)
					{
						tWingValue = 20.0f;
					}
					else if (mEquipItem[i]->iIndex == 225 || mEquipItem[i]->iIndex == 226 || mEquipItem[i]->iIndex == 227)
					{
						tWingValue = 25.0f;
					}
					else if (mEquipItem[i]->iIndex == 228 || mEquipItem[i]->iIndex == 229 || mEquipItem[i]->iIndex == 230)
					{
						tWingValue = 30.0f;
					}
					else
					{
						tWingValue = 3.90f;
					}
					if (mUTIL.ReturnItemSort(mEquipItem[i]) != 2)
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
							mElementAttackPower += (int)((double)tISValue * tWingValue);
					}
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mElementAttackPower += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 50);
					if (mElementAttackPower < 1)
						mElementAttackPower = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mElementAttackPower += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 50);
				if (mElementAttackPower < 1)
					mElementAttackPower = 1;
			}
		}
	}
	mElementAttackPower += mLEVEL.ReturnLevelFactorElementAttack(mUSER[mIndex].mAvatarInfo.aLevel2 + mUSER[mIndex].mAvatarInfo.aLevel1);

	if (mZONEMAININFO.CheckLevelBattleZoneNumber2() == 0 && mZONEMAININFO.Check267TypeZoneNumber2() == 0 || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mElementAttackPower += 10 * (mUSER[mIndex].mAvatarInfo.aEatElementAtkDefPotion / 1000);
	}
	switch (mDATA.aAnimalNumber)
	{
	case 1301:
	case 1303:
	case 1320:
		mElementAttackPower = (int)((float)mElementAttackPower * 1.05f);
		break;
	case 7011:
		mElementAttackPower = (int)((float)mElementAttackPower * 1.05f);
		break;
	case 1304:
	case 17044:
	case 1306:
	case 17046:
	case 1321:
	case 17049:
	case 559:
		mElementAttackPower = (int)((float)mElementAttackPower * 1.10f);
		break;
	case 1307:
	case 1309:
	case 1322:
	case 17058:
	case 814:
	case 817:
	case 821:
		mElementAttackPower = (int)((float)mElementAttackPower * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mElementAttackPower += (int)((float)mUTIL.ReturnEliteMountStats(8, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mElementAttackPower);
	}
	if (mUSER[mIndex].mEffectValue[4][0] > 0)
	{
		mElementAttackPower = (int)((float)(mElementAttackPower * (mUSER[mIndex].mEffectValue[4][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mAvatarInfo.aTitle > 0)
	{
		mElementAttackPower = (int)((float)mElementAttackPower * (float)(mUSER[mIndex].mAvatarInfo.aTitle % 100 + 100) * 0.01f);
	}
	if (tWarlordState == 19)
	{
		mElementAttackPower += 500;
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mElementAttackPower += mSOCKET.GetSocketInfo(7, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}
	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 3)
	{
		mElementAttackPower += 1000;
	}
	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mElementAttackPower += 50 * s7;
		}
	}
	mElementAttackPower += (int)(mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 5));
	mElementAttackPower += (int)(mPAT.ReturnAmuletPetability3(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 3));
	if (mUTIL.ReturnWineState(mIndex, 882))
	{
		mElementAttackPower += (int)((float)mElementAttackPower * 0.30f);
	}
	mElementAttackPower += (int)(mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 5));

	return mElementAttackPower;
}
//GET_ELEMENT_DEFENSE_POWER
int AVATAR_OBJECT::GetElementDefensePower(void)
{
	int mElementDefensePower = 0;
	int i, j, k;
	ITEM_INFO* tITEM;
	int tItemSort = 0;
	int tMountSort = 0;
	int tWarlordState = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	float tWingValue;
	int tExp = 0;
	int tFeed = 0;
	int s1, s2, s3, s4, s5, s6, s7, s8;

	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mElementDefensePower += mEquipItem[i]->iElementDefensePower;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 1:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.40f);
					break;
				case 5:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 1.0f);
					break;
				case 6:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.40f);
					break;
				case 10:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 1.0f);
					break;
				case 11:
				case 16:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.60f);
					break;
				case 15:
				case 20:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 1.10f);
					break;
				case 21:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.20f);
					break;
				case 22:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.10f);
					break;
				case 30:
					if (i == 1 || i == 10)
					{
						mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.55f);
					}
					else if (i != 9 && i != 11 && i != 12)
					{
						if (mUTIL.ReturnItemSort(mEquipItem[i]) == 1
							|| mUTIL.ReturnItemSort(mEquipItem[i]) == 4)
						{
							mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.55f);
						}
						else
						{
							mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 1.10f);
						}
					}
					break;
				case 50:
					mElementDefensePower += (int)((float)mEquipItem[i]->iElementDefensePower * 0.55f);
					break;
				default:
					break;
				}
				switch (i)
				{
				case 0:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) != 1 && mUTIL.ReturnItemSort(mEquipItem[i]) != 4 && mUTIL.ReturnItemSort(mEquipItem[i]) != 11 && mUTIL.ReturnItemSort(mEquipItem[i]) != 12)
					{
						if (mEquipItem[i]->iCheckItemSet == 2)
						{
							tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]);
							mElementDefensePower += mUTIL.ReturnSetItemIUValue_ElementDefensePower(i, tIUValue, tWarlordState);
						}
						else
						{
							tIUValue = mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]);
							tIUEffectValue = mUTIL.ReturnIUEffectValue(mEquipItem[i], 6);
							mElementDefensePower += tIUEffectValue * tIUValue;
						}
					}
					break;
				case 4:
					if (mEquipItem[i] && (mUTIL.ReturnItemSort(mEquipItem[i]) == 1 || mUTIL.ReturnItemSort(mEquipItem[i]) == 4 || mUTIL.ReturnItemSort(mEquipItem[i]) == 11 || mUTIL.ReturnItemSort(mEquipItem[i]) == 12))
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
						{
							if (tISValue > 100)
								tISValue -= 100;
							mElementDefensePower += 200 * tISValue;
						}
					}
					break;
				case 9:
				case 11:
				case 12:
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mElementDefensePower += mITEM.ReturnLegendDecoStats(8, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					break;
				case 10:
					if (mEquipItem[i]->iIndex == 207 || mEquipItem[i]->iIndex == 208 || mEquipItem[i]->iIndex == 209 || mEquipItem[i]->iIndex == 216 || mEquipItem[i]->iIndex == 217 || mEquipItem[i]->iIndex == 218 || mEquipItem[i]->iIndex == 2303 || mEquipItem[i]->iIndex == 2304 || mEquipItem[i]->iIndex == 2305)
					{
						tWingValue = 7.80f;
					}
					else if (mEquipItem[i]->iIndex == 219 || mEquipItem[i]->iIndex == 220 || mEquipItem[i]->iIndex == 221)
					{
						tWingValue = 15.0f;
					}
					else if (mEquipItem[i]->iIndex == 222 || mEquipItem[i]->iIndex == 223 || mEquipItem[i]->iIndex == 224)
					{
						tWingValue = 20.0f;
					}
					else if (mEquipItem[i]->iIndex == 225 || mEquipItem[i]->iIndex == 226 || mEquipItem[i]->iIndex == 227)
					{
						tWingValue = 25.0f;
					}
					else if (mEquipItem[i]->iIndex == 228 || mEquipItem[i]->iIndex == 229 || mEquipItem[i]->iIndex == 230)
					{
						tWingValue = 30.0f;
					}
					else
					{
						tWingValue = 3.90f;
					}
					if (mUTIL.ReturnItemSort(mEquipItem[i]) == 2)
					{
						mElementDefensePower += mITEM.ReturnLegendDecoStats(8, mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
					}
					else
					{
						tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[i][2]);
						if (tISValue > 0)
							mElementDefensePower += (int)((float)tISValue * tWingValue);
					}
					break;
				default:
					continue;
				}
			}
		}
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i] && i != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[i]);
			if (i == 1)
			{
				if (tItemSort == 8)
				{
					mElementDefensePower += mUTIL.ReturnEngraveStats(8, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 60);
					if (mElementDefensePower < 1)
						mElementDefensePower = 1;
				}
			}
			else if ((!i || i == 2 || i == 3 || i == 4 || i == 5 || i == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mElementDefensePower += mUTIL.ReturnEngraveStats(tItemSort, i, mUSER[mIndex].mAvatarInfo.aEquip[i][2], 60);
				if (mElementDefensePower < 1)
					mElementDefensePower = 1;
			}
		}
	}

	if (mZONEMAININFO.CheckLevelBattleZoneNumber2() == 0 && mZONEMAININFO.Check267TypeZoneNumber2() == 0 || mSERVER_INFO.mServerNumber >= 319 && mSERVER_INFO.mServerNumber <= 323)
	{
		mElementDefensePower += 10 * (mUSER[mIndex].mAvatarInfo.aEatElementAtkDefPotion % 1000);
	}
	switch (mDATA.aAnimalNumber)
	{
	case 1302:
	case 1317:
		mElementDefensePower = (int)((float)mElementDefensePower * 1.05f);
		break;
	case 1305:
	case 17045:
	case 1318:
	case 17048:
		mElementDefensePower = (int)((float)mElementDefensePower * 1.10f);
		break;
	case 1308:
	case 1319:
	case 818:
	case 819:
		mElementDefensePower = (int)((float)mElementDefensePower * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mElementDefensePower += (int)((float)mUTIL.ReturnEliteMountStats(9, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mElementDefensePower);
	}
	if (mUSER[mIndex].mEffectValue[5][0] > 0)
	{
		mElementDefensePower = (int)((float)(mElementDefensePower * (mUSER[mIndex].mEffectValue[5][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mAvatarInfo.aTitle > 0)
	{
		mElementDefensePower = (int)((float)mElementDefensePower * (float)(mUSER[mIndex].mAvatarInfo.aTitle % 100 + 100) * 0.01f);
	}
	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mElementDefensePower += mSOCKET.GetSocketInfo(8, mUSER[mIndex].mAvatarInfo.aEquipSocket[i][0], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][1], mUSER[mIndex].mAvatarInfo.aEquipSocket[i][2]);
		}
	}
	if (mUSER[mIndex].mAvatarInfo.aRankAbility == 2)
	{
		mElementDefensePower += 1000;
	}

	if (mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 10 && mUSER[mIndex].mAvatarInfo.aAnimalIndex < 20)
	{
		mUTIL.ReturnMountExp(mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &tFeed, &tExp);
		if (tFeed > 0)
		{
			mUTIL.GetAnimalAbilities(mUSER[mIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10], &s1, &s2, &s3, &s4, &s5, &s6, &s7, &s8);
			mElementDefensePower += 50 * s8;
		}
	}
	mElementDefensePower += (int)(mPAT.ReturnAmuletPetability1(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 6));
	mElementDefensePower += (int)(mPAT.ReturnAmuletPetability3(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 4));
	if (mUTIL.ReturnWineState(mIndex, 882))
	{
		mElementDefensePower -= (int)((float)mElementDefensePower * 0.50f);
	}
	mElementDefensePower += (int)(mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 6));

	return mElementDefensePower;
}
//GET_CRITICAL
int AVATAR_OBJECT::GetCritical(void)
{
	int mCritical = 0;
	int tISValue = 0;
	int tIUValue = 0;
	int tIUEffectValue = 0;
	int i, j;
	int tWarlordState = 0;
	int tMountSort = 0;
	int tItemSort = 0;


	mCritical = 2;
	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mCritical += mEquipItem[i]->iCritical;
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 5:
					mCritical += (int)((float)mEquipItem[i]->iCritical * 0.05f);
					break;
				case 9:
					mCritical += (int)((float)mEquipItem[i]->iCritical * 0.05f);
					break;
				case 10:
					mCritical += (int)((float)mEquipItem[i]->iCritical * 0.05f);
					break;
				case 21:
					mCritical += (int)((float)mEquipItem[i]->iCritical * 0.05f);
					break;
				case 22:
					mCritical += (int)((float)mEquipItem[i]->iCritical * 0.05f);
					break;
				default:
					break;
				}
				if (i == 4 && mUTIL.ReturnItemSort(mEquipItem[4]) != 1 && mUTIL.ReturnItemSort(mEquipItem[4]) != 4 && mUTIL.ReturnItemSort(mEquipItem[4]) != 11 && mUTIL.ReturnItemSort(mEquipItem[4]) != 12)
				{
					tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[4][2]);
					if (tISValue > 0)
						mCritical += tISValue / 4;
				}
			}
		}
	}
	for (j = 0; j < 13; ++j)
	{
		if (mEquipItem[j] && j != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[j]);
			if (j == 1)
			{
				if (tItemSort == 8)
				{
					mCritical += mUTIL.ReturnEngraveStats(8, 1, mUSER[mIndex].mAvatarInfo.aEquip[1][2], 70);
					if (mCritical < 1)
						mCritical = 1;
				}
			}
			else if ((!j || j == 2 || j == 3 || j == 4 || j == 5 || j == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mCritical += mUTIL.ReturnEngraveStats(tItemSort, j, mUSER[mIndex].mAvatarInfo.aEquip[j][2], 70);
				if (mCritical < 1)
					mCritical = 1;
			}
		}
	}
	if (mUSER[mIndex].mAvatarInfo.aCriticalBoostScroll > 0 || mUSER[mIndex].mAvatarInfo.aHeroPill > 0)
	{
		mCritical += 5;
	}
	tMountSort = mUTIL.ReturnMountSort(mDATA.aAnimalNumber) == 30;
	switch (mDATA.aAnimalNumber)
	{
	case 1303:
	case 1323:
		mCritical = (int)((float)mCritical * 1.05f);
		break;
	case 1306:
	case 17046:
	case 510:
	case 1324:
	case 17050:
		mCritical = (int)((float)mCritical * 1.10f);
		break;
	case 1309:
	case 511:
	case 1325:
	case 815:
	case 817:
		mCritical = (int)((float)mCritical * 1.15f);
		break;
	}
	if (tMountSort)
	{
		mCritical += (int)((float)mUTIL.ReturnEliteMountStats(6, mUSER[mIndex].mAvatarInfo.aAnimalExpActivity[mUSER[mIndex].mAvatarInfo.aAnimalIndex - 10]) / 100.0f * (float)mCritical);
	}
	if (mUSER[mIndex].mEffectValue[10][0] > 0)
	{
		mCritical = (int)((float)(mCritical * (mUSER[mIndex].mEffectValue[10][0] + 100)) * 0.01f);
	}
	if (mUSER[mIndex].mAvatarInfo.aRebirth <= 6 || mUSER[mIndex].mAvatarInfo.aRebirth >= 12)
	{
		if (mUSER[mIndex].mAvatarInfo.aRebirth == 12)
		{
			mCritical += 8;
		}
	}
	else
	{
		mCritical = mCritical + mUSER[mIndex].mAvatarInfo.aRebirth - 6;
	}
	switch (tWarlordState)
	{
	case 11:
	case 15:
	case 16:
		mCritical += 2;
		break;
	case 19:
		mCritical += 5;
		break;
	case 20:
	case 30:
	case 50:
		mCritical += 7;
		break;
	default:
		break;
	}
	if (mDATA.aGuildBuff == 1 && mDATA.aBuffSort == 2)
	{
		mCritical += 1;
	}

	mCritical += (int)(ReturnCriticalUp() * (float)mCritical);

	if (mGAME.ReturnTribeRole(mUSER[mIndex].mAvatarInfo.aName, mUSER[mIndex].mAvatarInfo.aTribe) == 1)
	{
		mCritical += 2;
	}
	mCritical += (int)(mPAT.ReturnAmuletPetability3(mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2], 5));

	if (mUTIL.ReturnWineState(mIndex, 880))
	{
		mCritical += (int)((float)mCritical * 0.05f);
	}
	mCritical += (int)(mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 7));

	if (mCritical > 150)
		mCritical = 0;

	return mCritical;
}
//GET_CRITICAL_DEFENSE
int AVATAR_OBJECT::GetCriticalDefense(void)
{
	int mCriticalDefense = 0;
	int i, j, k;
	int tISValue = 0;
	int tIUValue = 0;
	int tWarlordState = 0;
	int tMountSort = 0;
	int tItemSort = 0;


	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mCriticalDefense += mEquipItem[i]->iCapeInfo[1];
			if (i != 8)
			{
				switch (tWarlordState)
				{
				case 5:
					mCriticalDefense += (int)((float)mEquipItem[i]->iCapeInfo[1] * 0.05f);
					break;
				case 10:
					mCriticalDefense += (int)((float)mEquipItem[i]->iCapeInfo[1] * 0.05f);
					break;
				case 21:
					mCriticalDefense += (int)((float)mEquipItem[i]->iCapeInfo[1] * 0.05f);
					break;
				case 22:
					mCriticalDefense += (int)((float)mEquipItem[i]->iCapeInfo[1] * 0.04f);
					break;
				default:
					continue;
				}
			}
		}
	}
	for (j = 0; j < 13; ++j)
	{
		if (mEquipItem[j] && j != 8)
		{
			tItemSort = mUTIL.ReturnItemSort(mEquipItem[j]);
			if (j == 1)
			{
				if (tItemSort == 8)
				{
					mCriticalDefense += mUTIL.ReturnEngraveStats(8, 1, mUSER[mIndex].mAvatarInfo.aEquip[1][2], 80);
					if (mCriticalDefense < 1)
						mCriticalDefense = 1;
				}
			}
			else if ((!j || j == 2 || j == 3 || j == 4 || j == 5 || j == 7) && (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12))
			{
				mCriticalDefense += mUTIL.ReturnEngraveStats(tItemSort, j, mUSER[mIndex].mAvatarInfo.aEquip[j][2], 80);
				if (mCriticalDefense < 1)
					mCriticalDefense = 1;
			}
		}
	}
	switch (tWarlordState)
	{
	case 15:
		mCriticalDefense += 2;
		break;
	case 20:
	case 30:
	case 50:
		mCriticalDefense += 7;
		break;
	default:
		break;
	}
	switch (mUSER[mIndex].mAvatarInfo.aRebirth)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
		mCriticalDefense += mUSER[mIndex].mAvatarInfo.aRebirth;
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		mCriticalDefense += 6;
		break;
	default:
		break;
	}

	mCriticalDefense += (int)(ReturnCriticalDefenceUp() * (float)mCriticalDefense);

	if (mUSER[mIndex].mAvatarInfo.aUpgradeValue == 96)
	{
		mCriticalDefense += 10;
	}
	else
	{
		mCriticalDefense += mUSER[mIndex].mAvatarInfo.aUpgradeValue / 10;
	}
	if (mUTIL.ReturnWineState(mIndex, 880))
	{
		mCriticalDefense -= (int)((float)mCriticalDefense * 0.10f);
	}
	mCriticalDefense += (int)(mUTIL.ReturnCapeAbility(mUSER[mIndex].mAvatarInfo.aEquip[1][0], mUSER[mIndex].mAvatarInfo.aEquip[1][2], 8));

	if (mUSER[mIndex].mAvatarInfo.aVigilanteScroll > 0)
	{
		mCriticalDefense += 1;
	}
	return mCriticalDefense;
}
//GET_LAST_ATTACK_BONUS_PROBABILITY
int AVATAR_OBJECT::GetLastAttackBonusProbability(void)
{
	return mLastAttackBonusProbability;
}
//GET_LAST_ATTACK_BONUS_VALUE
float AVATAR_OBJECT::GetLastAttackBonusValue(void)
{
	return mLastAttackBonusValue;
}
//GET_LUCK
int AVATAR_OBJECT::GetLuck(void)
{
	int tWarlordState = 0;
	int mLuck = 0;
	int i;
	int tISValue = 0;

	tWarlordState = mUTIL.GetWarlordSetState(mIndex);

	for (i = 0; i < 13; ++i)
	{
		if (mEquipItem[i])
		{
			mLuck += mEquipItem[i]->iLuck;
			if (i != 8)
			{
				if (tWarlordState == 10 || tWarlordState == 30 || tWarlordState == 50)
				{
					mLuck += (int)((float)mEquipItem[i]->iLuck * 0.05f);
				}
				if (!i && mUTIL.ReturnItemSort(mEquipItem[0]) != 1 && mUTIL.ReturnItemSort(mEquipItem[0]) != 4)
				{
					tISValue = mUTIL.ReturnISValue(mUSER[mIndex].mAvatarInfo.aEquip[0][2]);
					if (tISValue > 0)
					{
						mLuck += 12 * tISValue;
					}
				}
			}
		}
	}
	if (mUSER[mIndex].mEffectValue[11][0] > 0)
	{
		mLuck = (int)((float)(mLuck * (mUSER[mIndex].mEffectValue[11][0] + 100)) * 0.01f);
	}

	return mLuck;
}
int AVATAR_OBJECT::GetSpiritDamage()
{
	return mSpiritDamage;
}
int AVATAR_OBJECT::GetSpiritDefense()
{
	return mSpiritDefense;
}
//GET_BONUS_SKILL_VALUE
int AVATAR_OBJECT::GetBonusSkillValue(int sIndex)
{
	int index01;
	int tValue = 0;
	ITEM_INFO* tITEM_INFO;
	SKILL_INFO* tSkill;
	int v9 = 0;

	if (mEquipItem[8])
	{
		v9 = mUTIL.ReturnItemSort(mEquipItem[8]->iIndex);
	}
	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		if (mEquipItem[index01])
		{
			if (mEquipItem[index01]->iBonusSkillInfo[0][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[0][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[1][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[1][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[2][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[2][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[3][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[3][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[4][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[4][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[5][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[5][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[6][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[6][1];
			}
			if (mEquipItem[index01]->iBonusSkillInfo[7][0] == sIndex)
			{
				tValue += mEquipItem[index01]->iBonusSkillInfo[7][1];
			}
			tValue += mEquipItem[index01]->iCapeInfo[2];
		}
	}
	if (v9 == 7 || v9 == 5 || v9 == 6)
	{
		switch (sIndex)
		{
		case 103:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 1);
			break;
		case 82:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 2);
			break;
		case 83:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 3);
			break;
		case 105:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 4);
			break;
		case 104:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 5);
			break;
		case 84:
			tValue += mUTIL.ReturnAmuletStats2(mIndex, mUSER[mIndex].mAvatarInfo.aEquip[8][2], 6);
			break;
		}
	}
	tValue += mUTIL.ReturnPetAddSkillPoint2(2, 2, mUSER[mIndex].mAvatarInfo.aEquip[8][0], mUSER[mIndex].mAvatarInfo.aEquip[8][2]);
	tSkill = mSKILL.Search(sIndex);
	if (tSkill)
	{
		if (tSkill->sType == 2 && mDATA.aGuildBuff == 1 && mDATA.aBuffSort == 3)
		{
			tValue++;
		}
	}
	return tValue;
}
int AVATAR_OBJECT::GetReduceManaRatio(void)
{
	int index01;
	int tValue = 0;
	ITEM_INFO* tITEM_INFO;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM; index01++)
	{
		tITEM_INFO = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[index01][0]);
		if (tITEM_INFO == NULL)
		{
			continue;
		}
		tValue += tITEM_INFO->iCapeInfo[0];
	}
	return tValue;
}
int AVATAR_OBJECT::GetCallVitality()
{
	int mTitle = mUSER[mIndex].mAvatarInfo.aTitle;

	if (mTitle <= 100)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 100 && mTitle <= 200)
	{
		switch (mTitle % 100)
		{
		case 1: return 0;
		case 2: return 1;
		case 3: return 3;
		case 4: return 5;
		case 5: return 8;
		case 6: return 11;
		case 7: return 14;
		case 8: return 18;
		case 9: return 23;
		case 10: return 28;
		case 11: return 34;
		case 12: return 41;
		case 13: return 48;
		case 14: return 55;
		default: return 0;
		}
	}
	else if (mTitle > 200 && mTitle <= 300)
	{
		switch (mTitle % 100)
		{
		case 1: return 2;
		case 2: return 6;
		case 3: return 12;
		case 4: return 20;
		case 5: return 30;
		case 6: return 42;
		case 7: return 56;
		case 8: return 72;
		case 9: return 90;
		case 10: return 110;
		case 11: return 134;
		case 12: return 164;
		case 13: return 194;
		case 14: return 224;
		default: return 0;
		}
	}
	else if (mTitle > 300 && mTitle <= 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 0;
		case 2: return 1;
		case 3: return 3;
		case 4: return 5;
		case 5: return 8;
		case 6: return 11;
		case 7: return 14;
		case 8: return 18;
		case 9: return 23;
		case 10: return 28;
		case 11: return 34;
		case 12: return 41;
		case 13: return 48;
		case 14: return 55;
		default: return 0;
		}
	}
	else if (mTitle > 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
}
int AVATAR_OBJECT::GetCallStrength()
{
	int mTitle = mUSER[mIndex].mAvatarInfo.aTitle;

	if (mTitle <= 100)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 100 && mTitle <= 200)
	{
		switch (mTitle % 100)
		{
		case 1: return 2;
		case 2: return 6;
		case 3: return 12;
		case 4: return 20;
		case 5: return 30;
		case 6: return 42;
		case 7: return 56;
		case 8: return 72;
		case 9: return 90;
		case 10: return 110;
		case 11: return 134;
		case 12: return 164;
		case 13: return 194;
		case 14: return 224;
		default: return 0;
		}
	}
	else if (mTitle > 200 && mTitle <= 300)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 5;
		case 5: return 7;
		case 6: return 10;
		case 7: return 14;
		case 8: return 18;
		case 9: return 22;
		case 10: return 27;
		case 11: return 33;
		case 12: return 41;
		case 13: return 49;
		case 14: return 57;
		default: return 0;
		}
	}
	else if (mTitle > 300 && mTitle <= 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 0;
		case 2: return 1;
		case 3: return 3;
		case 4: return 5;
		case 5: return 8;
		case 6: return 11;
		case 7: return 14;
		case 8: return 18;
		case 9: return 23;
		case 10: return 28;
		case 11: return 34;
		case 12: return 41;
		case 13: return 48;
		case 14: return 55;
		default: return 0;
		}
	}
	else if (mTitle > 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
}
int AVATAR_OBJECT::GetCallKi()
{
	int mTitle = mUSER[mIndex].mAvatarInfo.aTitle;

	if (mTitle <= 100)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 100 && mTitle <= 200)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 200 && mTitle <= 300)
	{
		switch (mTitle % 100)
		{
		case 1: return 0;
		case 2: return 1;
		case 3: return 3;
		case 4: return 5;
		case 5: return 8;
		case 6: return 11;
		case 7: return 14;
		case 8: return 18;
		case 9: return 23;
		case 10: return 28;
		case 11: return 34;
		case 12: return 41;
		case 13: return 48;
		case 14: return 55;
		default: return 0;
		}
	}
	else if (mTitle > 300 && mTitle <= 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 2;
		case 2: return 6;
		case 3: return 12;
		case 4: return 20;
		case 5: return 30;
		case 6: return 42;
		case 7: return 56;
		case 8: return 72;
		case 9: return 90;
		case 10: return 110;
		case 11: return 134;
		case 12: return 164;
		case 13: return 194;
		case 14: return 224;
		default: return 0;
		}
	}
}
int AVATAR_OBJECT::GetCallWisdom()
{
	int mTitle = mUSER[mIndex].mAvatarInfo.aTitle;

	if (mTitle <= 100)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
	else if (mTitle > 100 && mTitle <= 200)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 5;
		case 5: return 7;
		case 6: return 10;
		case 7: return 14;
		case 8: return 18;
		case 9: return 22;
		case 10: return 27;
		case 11: return 33;
		case 12: return 41;
		case 13: return 49;
		case 14: return 57;
		default: return 0;
		}
	}
	else if (mTitle > 200 && mTitle <= 300)
	{
		switch (mTitle % 100)
		{
		case 1: return 3;
		case 2: return 8;
		case 3: return 15;
		case 4: return 25;
		case 5: return 37;
		case 6: return 52;
		case 7: return 70;
		case 8: return 90;
		case 9: return 112;
		case 10: return 137;
		case 11: return 167;
		case 12: return 205;
		case 13: return 243;
		case 14: return 281;
		default: return 0;
		}
	}
	else if (mTitle > 300 && mTitle <= 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 2;
		case 3: return 3;
		case 4: return 5;
		case 5: return 7;
		case 6: return 10;
		case 7: return 14;
		case 8: return 18;
		case 9: return 22;
		case 10: return 27;
		case 11: return 33;
		case 12: return 41;
		case 13: return 49;
		case 14: return 57;
		default: return 0;
		}
	}
	else if (mTitle > 400)
	{
		switch (mTitle % 100)
		{
		case 1: return 1;
		case 2: return 3;
		case 3: return 6;
		case 4: return 10;
		case 5: return 15;
		case 6: return 21;
		case 7: return 28;
		case 8: return 36;
		case 9: return 45;
		case 10: return 55;
		case 11: return 67;
		case 12: return 82;
		case 13: return 97;
		case 14: return 112;
		default: return 0;
		}
	}
}
float AVATAR_OBJECT::ReturnCriticalUp()
{
	return (float)(mUTIL.ReturnRFValue(mEquipValue[7]) * 0.01f);
}
int AVATAR_OBJECT::ReturnVitalityUp()
{
	int v1;

	v1 = 5 * mUTIL.ReturnRFValue(mEquipValue[4]);
	if (mUTIL.ReturnRFValue(mEquipValue[4]) == 25)
	{
		v1 += 5;
	}
	return v1;
}
int AVATAR_OBJECT::ReturnStrengthUp()
{
	int v1;

	v1 = 5 * mUTIL.ReturnRFValue(mEquipValue[0]);
	if (mUTIL.ReturnRFValue(mEquipValue[0]) == 25)
	{
		v1 += 5;
	}
	return v1;
}
int AVATAR_OBJECT::ReturnWisdomUp()
{
	int v1;
	int v2;
	int v3;

	v1 = 5 * mUTIL.ReturnRFValue(mEquipValue[3]);
	if (mUTIL.ReturnRFValue(mEquipValue[3]) == 25)
	{
		v1 += 5;
	}
	v2 = v1 + 5 * mUTIL.ReturnRFValue(mEquipValue[5]);
	if (mUTIL.ReturnRFValue(mEquipValue[5]) == 25)
	{
		v2 += 5;
	}
	v3 = v2 + 5 * mUTIL.ReturnRFValue(mEquipValue[1]);
	if (mUTIL.ReturnRFValue(mEquipValue[1]) == 25)
	{
		v3 += 5;
	}
	return v3;
}
int AVATAR_OBJECT::ReturnKiUp()
{
	int v1;
	int v2;

	v1 = 5 * mUTIL.ReturnRFValue(mEquipValue[7]);
	if (mUTIL.ReturnRFValue(mEquipValue[7]) == 25)
	{
		v1 += 5;
	}
	v2 = v1 + 5 * mUTIL.ReturnRFValue(mEquipValue[2]);
	if (mUTIL.ReturnRFValue(mEquipValue[2]) == 25)
	{
		v2 += 5;
	}
	return v2;
}
float AVATAR_OBJECT::ReturnCriticalDefenceUp()
{
	return (mUTIL.ReturnRFValue(mEquipValue[1]) * 0.016f);
}
int AVATAR_OBJECT::ReturnLifeUp(int tUserIndex)
{
	return 400 * mUTIL.ReturnRFValue(mEquipValue[2]);
}
int AVATAR_OBJECT::ReturnSetItemIUValue_LifeUp(AVATAR_INFO* tAVATAR)
{
	int tHP = 0;
	int tCS6 = 0;
	int tCS12 = 0;
	int i;
	int tIUValue = 0;

	for (i = 0; i < 8; ++i)
	{
		if (i != 1 && i != 6 && mEquipItem[i] && mEquipItem[i]->iMartialLevelLimit == 12 && mUTIL.ReturnItemSort(mEquipItem[i]) != 1 && mUTIL.ReturnItemSort(mEquipItem[i]) != 4)
		{
			tIUValue = mUTIL.ReturnIUValue(tAVATAR->aEquip[i][2]);
			if (tIUValue >= 6)
			{
				tCS6++;
			}
			if (tIUValue >= 12)
			{
				tCS12++;
			}
		}
	}
	if (tCS6 >= 6)
	{
		tHP = 5000;
	}
	if (tCS12 >= 6)
	{
		tHP += 15000;
	}
	return tHP;
}

BOOL AVATAR_OBJECT::CheckCommunityWork(void)
{
	if (mDATA.aPShopState != 0)
	{
		return TRUE;
	}
	if (mDuelProcessState != 0)
	{
		return TRUE;
	}
	if (mTradeProcessState != 0)
	{
		return TRUE;
	}
	if (mFriendProcessState != 0)
	{
		return TRUE;
	}
	if (mPartyProcessState != 0)
	{
		return TRUE;
	}
	if (mGuildProcessState != 0)
	{
		return TRUE;
	}
	if (mTeacherProcessState != 0)
	{
		return TRUE;
	}
	return FALSE;
}
//UPDATE
void AVATAR_OBJECT::Update(float tPostTime)
{
	if (!mCheckValidState)
	{
		return;
	}
	if ((mUSER[mIndex].mMoveZoneResult == 1))
	{
		mUSER[mIndex].mHeartCheckCount = 0;
		mUSER[mIndex].mHeartCheckTime = ::time(NULL);
		return;
	}

	int index01;
	int HotKeyPage;
	int HotKeyIndex;
	int PotionPage;
	int PotionIndex;
	int PotionQuantity;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tMaxAvatarLife;
	int tRecoverAvatarLife;
	int tMaxAvatarMana;
	int tRecoverAvatarMana;
	float tLifeRecoverTime;
	float tManaRecoverTime;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	BOOL tCheckChangeEffectValue;
	int tOtherAvatarIndex;
	ITEM_INFO* tITEM_INFO;

	if (mUSER[mIndex].mAuthInfo.AuthType == 0)
	{
		if ((mGAME.mCheckZone049TypeServer) || (mGAME.mCheckZone051TypeServer) || (mGAME.mCheckZone053TypeServer))
		{
			if ((mDATA.aAction.aLocation[0] < mWORLD.mQuadtree[0].mBoxMin[0]) || (mDATA.aAction.aLocation[0] > mWORLD.mQuadtree[0].mBoxMax[0]) || (mDATA.aAction.aLocation[1] < mWORLD.mQuadtree[0].mBoxMin[1]) || (mDATA.aAction.aLocation[1] > mWORLD.mQuadtree[0].mBoxMax[1]) || (mDATA.aAction.aLocation[2] < mWORLD.mQuadtree[0].mBoxMin[2]) || (mDATA.aAction.aLocation[2] > mWORLD.mQuadtree[0].mBoxMax[2]))
			{
				mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
	}
	if (mDATA.aPShopState == 1)
	{
		if (!mWORK.CheckPossiblePShopRegion(mDATA.aTribe, mSERVER_INFO.mServerNumber, &mDATA.aAction.aLocation[0]))
		{
			mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}

	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Second) == 2)
	{
		mUSER[mIndex].mTickCountFor01Second = mGAME.mTickCount;
		if (mDATA.aAction.aSort == 11)
		{
			mDATA.aAction.aSkillValue--;
			if (mDATA.aAction.aSkillValue < 1)
			{
				mDATA.aAction.aType = GetWeaponClass() * 2;
				mDATA.aAction.aSort = 1;
				mDATA.aAction.aFrame = 0.0f;
				mTRANSFER.B_AVATAR_ACTION_RECV(mIndex, mUniqueNumber, &mDATA, 1);
				mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
		}
		tMaxAvatarLife = GetMaxLife();
		tRecoverAvatarLife = 0;
		if (mDATA.aAction.aSort == 31)
		{
			if (mDATA.aLifeValue < tMaxAvatarLife)
			{
				tLifeRecoverTime = mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 2);
				if (tLifeRecoverTime > 0.0f)
				{
					tRecoverAvatarLife = (int)((float)tMaxAvatarLife / tLifeRecoverTime);
					if (tRecoverAvatarLife < 1)
					{
						tRecoverAvatarLife = 1;
					}
					else
					{
						if ((mDATA.aLifeValue + tRecoverAvatarLife) > tMaxAvatarLife)
						{
							tRecoverAvatarLife = tMaxAvatarLife - mDATA.aLifeValue;
						}
					}
				}
			}
		}
		if (tRecoverAvatarLife > 0)
		{
			mDATA.aLifeValue += tRecoverAvatarLife;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mDATA.aLifeValue);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		tMaxAvatarMana = GetMaxMana();
		tRecoverAvatarMana = 0;
		if (mDATA.aAction.aSort == 31)
		{
			if (mDATA.aManaValue < tMaxAvatarMana)
			{
				tManaRecoverTime = mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 3);
				if (tManaRecoverTime > 0.0f)
				{
					tRecoverAvatarMana = (int)((float)tMaxAvatarMana / tManaRecoverTime);
					if (tRecoverAvatarMana < 1)
					{
						tRecoverAvatarMana = 1;
					}
					else
					{
						if ((mDATA.aManaValue + tRecoverAvatarMana) > tMaxAvatarMana)
						{
							tRecoverAvatarMana = tMaxAvatarMana - mDATA.aManaValue;
						}
					}
				}
			}
		}
		if (tRecoverAvatarMana > 0)
		{
			mDATA.aManaValue += tRecoverAvatarMana;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(11, mDATA.aManaValue);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (mUSER[mIndex].mAvatarInfo.aAutoHuntState == 1)
		{
			if (mUTIL.CheckIfEmptyHPPills(mIndex))
			{
				if ((mUTIL.GetEmptyHotKeyPage(mIndex) != -1) && (mUTIL.GetEmptyHotKeyIndex(mIndex) != -1))
				{
					if ((mUTIL.GetInventoryHPPillPage(mIndex) != -1) && (mUTIL.GetInventoryHPPillIndex(mIndex) != -1))
					{
						HotKeyPage = mUTIL.GetEmptyHotKeyPage(mIndex);
						HotKeyIndex = mUTIL.GetEmptyHotKeyIndex(mIndex);
						PotionPage = mUTIL.GetInventoryHPPillPage(mIndex);
						PotionIndex = mUTIL.GetInventoryHPPillIndex(mIndex);
						PotionQuantity = mUTIL.GetInventoryHPPillQuantity(mIndex);
						CopyMemory(&tData[0], &PotionPage, 4);
						CopyMemory(&tData[4], &PotionIndex, 4);
						CopyMemory(&tData[8], &PotionQuantity, 4);
						CopyMemory(&tData[12], &HotKeyPage, 4);
						CopyMemory(&tData[16], &HotKeyIndex, 4);
						mWORK.ProcessForData(mIndex, 253, &tData[0]);
					}
				}
			}
			if (mUTIL.CheckIfEmptyMPPills(mIndex))
			{
				if ((mUTIL.GetEmptyHotKeyPage(mIndex) != -1) && (mUTIL.GetEmptyHotKeyIndex(mIndex) != -1))
				{
					if ((mUTIL.GetInventoryMPPillPage(mIndex) != -1) && (mUTIL.GetInventoryMPPillIndex(mIndex) != -1))
					{
						HotKeyPage = mUTIL.GetEmptyHotKeyPage(mIndex);
						HotKeyIndex = mUTIL.GetEmptyHotKeyIndex(mIndex);
						PotionPage = mUTIL.GetInventoryMPPillPage(mIndex);
						PotionIndex = mUTIL.GetInventoryMPPillIndex(mIndex);
						PotionQuantity = mUTIL.GetInventoryMPPillQuantity(mIndex);
						CopyMemory(&tData[0], &PotionPage, 4);
						CopyMemory(&tData[4], &PotionIndex, 4);
						CopyMemory(&tData[8], &PotionQuantity, 4);
						CopyMemory(&tData[12], &HotKeyPage, 4);
						CopyMemory(&tData[16], &HotKeyIndex, 4);
						mWORK.ProcessForData(mIndex, 253, &tData[0]);
					}
				}
			}
		}
		tCheckChangeEffectValue = FALSE;
		for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
		{
			tEffectValueState[index01] = 0;
		}
		for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
		{
			if (mUSER[mIndex].mEffectValue[index01][0] < 1)
			{
				continue;
			}
			mUSER[mIndex].mEffectValue[index01][1]--;
			if (mUSER[mIndex].mEffectValue[index01][1] <= 0)
			{
				tCheckChangeEffectValue = TRUE;
				mUSER[mIndex].mEffectValue[index01][0] = 0;
				mUSER[mIndex].mEffectValue[index01][1] = 0;
				mDATA.aEffectValueForView[index01] = 0;
				tEffectValueState[index01] = 2;
			}
		}
		if (tCheckChangeEffectValue)
		{
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			if (mUSER[mIndex].mAvatarInfo.aAutoHuntState == 1)
			{
				AutoHuntBuff();
			}
		}
		// Wine Time
		if (mUSER[mIndex].mAvatarInfo.aActiveBoozeTime > 0)
		{
			mUSER[mIndex].mAvatarInfo.aActiveBoozeTime--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(112, mUSER[mIndex].mAvatarInfo.aActiveBoozeTime);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUSER[mIndex].mAvatarInfo.aActiveBoozeTime == 0)
			{
				SetBasicAbilityFromEquip();
			}
		}

		// Rage State
		if (mUSER[mIndex].mAvatarInfo.aFuryState == 1)
		{
			mUSER[mIndex].mAvatarInfo.aFuryEffectDuration--;
			if (mUSER[mIndex].mAvatarInfo.aFuryEffectDuration == 0)
			{
				mUSER[mIndex].mAvatarInfo.aFuryState = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(81, mUSER[mIndex].mAvatarInfo.aFuryState);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[mIndex].mAvatarInfo.aFuryCount = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(80, mUSER[mIndex].mAvatarInfo.aFuryCount);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				SetBasicAbilityFromEquip();
			}
		}
		if (mDATA.mFishingState == 1 && mDATA.mFishingStep == 1)
		{
			if (GetTickCount() - mFishPreTime >= 30000)
			{
				mFishPreTime = GetTickCount();
				mFishReel = TRUE;
				if ( (rand() % 5) == 0 )
				{
					mDATA.mFishingStep = 2;
				}
				else
				{
					mDATA.mFishingStep = 3;
				}
				mTRANSFER.B_FISHING_RESULT_RECV(mIndex, mUniqueNumber, 1, mDATA.mFishingState, mDATA.mFishingStep);
				mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			}
		}

		if (mDuelProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex) == -1)
			{
				mDuelProcessState = 0;
			}
		}
		if (124 != mSERVER_INFO.mServerNumber)
		{
			if (mDATA.aDuelState[0] == 1)
			{
				switch (mDATA.aDuelState[2])
				{
				case 1:
					tOtherAvatarIndex = mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex);
					if (tOtherAvatarIndex == -1)
					{
						mTRANSFER.B_DUEL_END_RECV(3);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aLifeValue < 1)
					{
						mTRANSFER.B_DUEL_END_RECV(1);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(1);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mDATA.aLifeValue < 1)
					{
						mTRANSFER.B_DUEL_END_RECV(2);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(2);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					if (mDuelProcessRemainTime == 1)
					{
						mTRANSFER.B_DUEL_END_RECV(0);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mTRANSFER.B_DUEL_END_RECV(0);
						mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
						break;
					}
					mDuelProcessRemainTime--;
					mTRANSFER.B_DUEL_TIME_INFO(mDuelProcessRemainTime);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					break;
				case 2:
					tOtherAvatarIndex = mUTIL.SearchAvatar(mDuelProcessAvatarName, mIndex);
					if (tOtherAvatarIndex == -1)
					{
						mTRANSFER.B_DUEL_END_RECV(3);
						mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mDATA.aDuelState[0] = 0;
						mDATA.aDuelState[1] = 0;
						mDATA.aDuelState[2] = 0;
						mCheckPossibleEatPotion = TRUE;
						mDuelProcessState = 0;
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
						mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
					}
					break;
				}
			}
		}
		else
		{
			if (mDATA.aLifeValue < 1)
			{
				if (1 == mDATA.aDuelState[0])
				{
					mGAME.mDuel_124_Pvp = TRUE;
					if (mDATA.aDuelState[2] == 1)
					{
						mGAME.mDuel_124_AvatarNum[0]--;
						mDATA.aAction.aLocation[0] = -157.0f;
						mDATA.aAction.aLocation[1] = 5.0f;
						mDATA.aAction.aLocation[2] = 1.0f;
					}
					else if (mDATA.aDuelState[2] == 2)
					{
						mGAME.mDuel_124_AvatarNum[1]--;
						mDATA.aAction.aLocation[0] = 157.0f;
						mDATA.aAction.aLocation[1] = 5.0f;
						mDATA.aAction.aLocation[2] = 1.0f;
					}

					mDATA.aDuelState[0] = 0;
					mDATA.aDuelState[1] = 0;
					mDATA.aDuelState[2] = 0;
					mCheckPossibleEatPotion = TRUE;
					mDuelProcessState = 0;
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mUniqueNumber, 7, mDATA.aDuelState[0], mDATA.aDuelState[1], mDATA.aDuelState[2]);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}

		if (mTradeProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mTradeProcessAvatarName, mIndex) == -1)
			{
				mTradeProcessState = 0;
	}
}
		if (mFriendProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mFriendProcessAvatarName, mIndex) == -1)
			{
				mFriendProcessState = 0;
			}
		}
		if (mTeacherProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mTeacherProcessAvatarName, mIndex) == -1)
			{
				mTeacherProcessState = 0;
			}
		}
		if (mPartyProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mPartyProcessAvatarName, mIndex) == -1)
			{
				mPartyProcessState = 0;
			}
		}
		if (mGuildProcessState == 3)
		{
			if (mUTIL.SearchAvatar(mGuildProcessAvatarName, mIndex) == -1)
			{
				mGuildProcessState = 0;
			}
		}
	}
	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor30Second) == 60)
	{
		mUSER[mIndex].mTickCountFor30Second = mGAME.mTickCount;
		if (mUSER[mIndex].mAvatarInfo.aEquip[8][1] > 0)
		{
			if (mUSER[mIndex].mAvatarInfo.aPat_Exp_x2_Time < 1) // Do Not deduct pet food when using pet exp boost scroll
			{
				mUSER[mIndex].mAvatarInfo.aEquip[8][1]--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(12, mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
	}

	/* TickCount for 1 Minute */
	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Minute) == 120)
	{
		mUSER[mIndex].mTickCountFor01Minute = mGAME.mTickCount;
		mUSER[mIndex].mAvatarInfo.aPlayTime1++;
		mUSER[mIndex].mAvatarInfo.aCapsuleOnlineTime++;
		mUSER[mIndex].mAvatarInfo.aTimeEffectTime++;
		mUSER[mIndex].mAvatarInfo.aDailyOnlineTime++;

		mTRANSFER.B_AVATAR_CHANGE_INFO_2(16, mUSER[mIndex].mAvatarInfo.aCapsuleOnlineTime);
		mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		if (mUSER[mIndex].mAvatarInfo.aDoubleBuffTime > 0)
		{
			mUSER[mIndex].mAvatarInfo.aDoubleBuffTime--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(42, mUSER[mIndex].mAvatarInfo.aDoubleBuffTime);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if (mUSER[mIndex].mAvatarInfo.aAutoHuntState == 1)
		{
			if (mUSER[mIndex].mAvatarInfo.aAutoHunt5Hour > 0)
			{
				mUSER[mIndex].mAvatarInfo.aAutoHunt5Hour--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(62, mUSER[mIndex].mAvatarInfo.aAutoHunt5Hour);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}

		// Horn Vein Shield Regeneration
		if (mUSER[mIndex].mAvatarInfo.aEquip[15][0] > 0)
		{
			if (mUSER[mIndex].mAvatarInfo.aHornVeinShield + (2000 + (50 + (10 * (mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[15][2]) + mUTIL.ReturnRFValue(mUSER[mIndex].mAvatarInfo.aEquip[15][2]))))) >= GetSpiritDefense())
			{
				mUSER[mIndex].mAvatarInfo.aHornVeinShield = GetSpiritDefense();
			}
			else
			{
				mUSER[mIndex].mAvatarInfo.aHornVeinShield += 2000 + (50 + (10 * (mUTIL.ReturnIUValue(mUSER[mIndex].mAvatarInfo.aEquip[15][2]) + mUTIL.ReturnRFValue(mUSER[mIndex].mAvatarInfo.aEquip[15][2]))));
			}
			mDATA.aHornVeinShield = mUSER[mIndex].mAvatarInfo.aHornVeinShield;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(159, mUSER[mIndex].mAvatarInfo.aHornVeinShield);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		if ((mSERVER_INFO.mServerNumber != 1) && (mSERVER_INFO.mServerNumber != 6) && (mSERVER_INFO.mServerNumber != 11) && (mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 38))
		{
			// Deduct Boost Scrolls Time
			if (mUSER[mIndex].mAvatarInfo.aDamageBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.aDamageBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[mIndex].mAvatarInfo.aDamageBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.aDamageBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			if (mUSER[mIndex].mAvatarInfo.aHealthBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.aHealthBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[mIndex].mAvatarInfo.aHealthBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.aHealthBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			if (mUSER[mIndex].mAvatarInfo.aCriticalBoostScroll > 0)
			{
				mUSER[mIndex].mAvatarInfo.aCriticalBoostScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[mIndex].mAvatarInfo.aCriticalBoostScroll);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.aCriticalBoostScroll == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}

			if (mUSER[mIndex].mAvatarInfo.aHeroPill > 0)
			{
				mUSER[mIndex].mAvatarInfo.aHeroPill--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(91, mUSER[mIndex].mAvatarInfo.aHeroPill);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				if (mUSER[mIndex].mAvatarInfo.aHeroPill == 0)
				{
					SetBasicAbilityFromEquip();
				}
			}
			// Deduct Exp Pill Time
			if (mUSER[mIndex].mAvatarInfo.aExpPill > 0)
			{
				mUSER[mIndex].mAvatarInfo.aExpPill--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(43, mUSER[mIndex].mAvatarInfo.aExpPill);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			// Deduct Superior Pill Time
			if (mUSER[mIndex].mAvatarInfo.aDoubleExpTime2 > 0)
			{
				mUSER[mIndex].mAvatarInfo.aDoubleExpTime2--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(17, mUSER[mIndex].mAvatarInfo.aDoubleExpTime2);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			// Deduct Pet Exp Boost Scroll
			if (mUSER[mIndex].mAvatarInfo.aPat_Exp_x2_Time > 0)
			{
				mUSER[mIndex].mAvatarInfo.aPat_Exp_x2_Time--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(44, mUSER[mIndex].mAvatarInfo.aPat_Exp_x2_Time);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}

		if (mUSER[mIndex].mAuthInfo.AuthType == 0)
		{
			if (mGAME.mCheckZone101TypeServer)
			{
				if (mUSER[mIndex].mAvatarInfo.aLevel2 > 0)
				{
					if (mUSER[mIndex].mAvatarInfo.aZone101TypeTime > 0)
					{
						mUSER[mIndex].mAvatarInfo.aZone101TypeTime--;
					}
					else
					{
						mUSER[mIndex].mAvatarInfo.aZone101TypeTime = 0;
						mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(18, mUSER[mIndex].mAvatarInfo.aZone101TypeTime);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
			if (mGAME.mCheckZone125Server)
			{
				if (mUSER[mIndex].mAvatarInfo.aZone125TypeTime > 0)
				{
					mUSER[mIndex].mAvatarInfo.aZone125TypeTime--;
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aZone125TypeTime = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(21, mUSER[mIndex].mAvatarInfo.aZone125TypeTime);
				mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (mGAME.mCheckZone126TypeServer)
			{
				if (mUSER[mIndex].uLoginPremiumPCRoom != 2)
				{
					if (mUSER[mIndex].mAvatarInfo.aPremiumService < mUTIL.ReturnNowDate())
					{
						if (mUSER[mIndex].mAvatarInfo.aZone126TypeTime > 0)
						{
							mUSER[mIndex].mAvatarInfo.aZone126TypeTime--;
							mTRANSFER.B_AVATAR_CHANGE_INFO_2(22, mUSER[mIndex].mAvatarInfo.aZone126TypeTime);
							mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						}
						else
						{
							mUSER[mIndex].mAvatarInfo.aZone126TypeTime = 0;
							mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
							return;
						}
					}
				}
			}
			if (mSERVER_INFO.mServerNumber == 234)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfBloodTime > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfBloodTime--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(33, mUSER[mIndex].mAvatarInfo.aIslandOfBloodTime);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfBloodTime = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 235)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul1Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul1Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(34, mUSER[mIndex].mAvatarInfo.aIslandOfSoul1Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul1Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 236)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul2Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul2Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(35, mUSER[mIndex].mAvatarInfo.aIslandOfSoul2Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul2Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 237)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul3Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul3Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(36, mUSER[mIndex].mAvatarInfo.aIslandOfSoul3Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul3Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 238)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul4Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul4Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(37, mUSER[mIndex].mAvatarInfo.aIslandOfSoul4Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul4Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 239)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul5Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul5Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(38, mUSER[mIndex].mAvatarInfo.aIslandOfSoul5Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul5Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 240)
			{
				if (mUSER[mIndex].mAvatarInfo.aIslandOfSoul6Time > 0)
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul6Time--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(39, mUSER[mIndex].mAvatarInfo.aIslandOfSoul6Time);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIslandOfSoul6Time = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			if (mSERVER_INFO.mServerNumber == 50 || mSERVER_INFO.mServerNumber == 52 || mSERVER_INFO.mServerNumber == 118)
			{
				if (mUSER[mIndex].mAvatarInfo.aIvyHallFishing == 0)
				{
					mUSER[mIndex].mAvatarInfo.aIvyHallFishing = 0;
					mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				else
				{
					mUSER[mIndex].mAvatarInfo.aIvyHallFishing--;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(65, mUSER[mIndex].mAvatarInfo.aIvyHallFishing);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}

	// Tick for Instant
	if (mUSER[mIndex].mAvatarInfo.aPat_Exp_x2_Time > 0)
	{
		tITEM_INFO = mITEM.Search(mUSER[mIndex].mAvatarInfo.aEquip[8][0]);
		if (tITEM_INFO)
		{
			if (tITEM_INFO->iSort == 22)
			{
				if (mUSER[mIndex].mAvatarInfo.aEquip[8][1] != 100)
				{
					mUSER[mIndex].mAvatarInfo.aEquip[8][1] = 100;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(12, mUSER[mIndex].mAvatarInfo.aEquip[8][1]);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}

	if ((mGAME.mTickCount - mUSER[mIndex].mTickCountFor01Minute_2) == 120)
	{
		mUSER[mIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		if ((mUSER[mIndex].mAvatarInfo.aAnimalIndex >= 0) && (mUSER[mIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)) && (mAVATAR_OBJECT[mIndex].mDATA.aAnimalNumber != 0))
		{
			if (mUSER[mIndex].mAvatarInfo.aAnimalTime > 0)
			{
				mUSER[mIndex].mAvatarInfo.aAnimalTime--;
			}
			else
			{
				mUSER[mIndex].mAvatarInfo.aAnimalTime = 0;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(26, mUSER[mIndex].mAvatarInfo.aAnimalTime);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		// Absorb Time Decrease
		if (mUSER[mIndex].mAvatarInfo.aAbsorbState == 1)
		{
			if (mUSER[mIndex].mAvatarInfo.aMountAbsorbTime > 0)
			{
				mUSER[mIndex].mAvatarInfo.aMountAbsorbTime--;
				if (mUSER[mIndex].mAvatarInfo.aMountAbsorbTime == 0)
				{
					mUSER[mIndex].mAvatarInfo.aAbsorbState = 0;
					mAVATAR_OBJECT[mIndex].mDATA.aAnimalAbsorbState = 0;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(79, mUSER[mIndex].mAvatarInfo.aAbsorbState);
					mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(mIndex, mAVATAR_OBJECT[mIndex].mUniqueNumber, 26, mAVATAR_OBJECT[mIndex].mDATA.aAnimalAbsorbState, 0, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[mIndex].mDATA.aAction.aLocation[0], 1);
					SetBasicAbilityFromEquip();
				}
			}
			else
			{
				mUSER[mIndex].mAvatarInfo.aMountAbsorbTime = 0;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[mIndex].mAvatarInfo.aMountAbsorbTime);
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		// Deco Stats
		if (mUSER[mIndex].mAvatarInfo.iUseOrnament == 1)
		{
			if (IsUsedOrnament() == 1)
			{
				mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(40, mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
			}
			else if (IsUsedOrnament() == 2)
			{
				mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(32, mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime);
			}

			if (mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime <= 0 && mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime <= 0)
			{
				mUSER[mIndex].mAvatarInfo.iUseOrnament = 0;
			}
			mUSER[mIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			SetBasicAbilityFromEquip();
		}
	}
}
//PROCESS_FOR_CREATE_EFFECT_VALUE
void AVATAR_OBJECT::ProcessForCreateEffectValue(ACTION_INFO* tAction)
{
	if ((mDATA.aAction.aSkillNumber != tAction->aSkillNumber) || (mDATA.aAction.aSkillGradeNum1 != tAction->aSkillGradeNum1) || (mDATA.aAction.aSkillGradeNum2 != tAction->aSkillGradeNum2))
	{
		return;
	}
	if (tAction->aSkillNumber != 0)
	{
		// 동행무공은 검사에서 제외.
		if ((tAction->aSkillNumber != 76) && (tAction->aSkillNumber != 77) && (tAction->aSkillNumber != 78) && (tAction->aSkillNumber != 79) && (tAction->aSkillNumber != 80) && (tAction->aSkillNumber != 81))
		{
			if ((tAction->aSkillGradeNum1 > mUSER[mIndex].GetMaxSkillGradeNum(tAction->aSkillNumber)) || (tAction->aSkillGradeNum2 > this->GetBonusSkillValue(tAction->aSkillNumber)))
			{
				return;
			}
		}
	}

	int index01;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];
	AVATAR_OBJECT* tAVATAR_OBJECT;
	int tRecoverLifeValue;
	int tRecoverManaValue;
	// Double Buff Time
	if (mUSER[mIndex].mAvatarInfo.aDoubleBuffTime > 0)
	{
		mUSER[mIndex].mSupportSkillTimeUpRatio = 2;
	}
	else
	{
		mUSER[mIndex].mSupportSkillTimeUpRatio = 1;
	}

	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}

	switch (mDATA.aAction.aSkillNumber)
	{
	case 6: //[축경]
	case 25:
	case 44:
		mUSER[mIndex].mEffectValue[8][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 11);
		mUSER[mIndex].mEffectValue[8][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[8] = mUSER[mIndex].mEffectValue[8][0];
		tEffectValueState[8] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 7: //[속성공격력],[공격속도]
	case 26:
	case 45:
		mUSER[mIndex].mEffectValue[4][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 16);
		mUSER[mIndex].mEffectValue[4][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[4] = mUSER[mIndex].mEffectValue[4][0];
		tEffectValueState[4] = 1;
		mUSER[mIndex].mEffectValue[6][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 18);
		mUSER[mIndex].mEffectValue[6][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[6] = mUSER[mIndex].mEffectValue[6][0];
		tEffectValueState[6] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 11: //[방어력]
	case 34:
	case 49:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 13) && (mEquipItem[7]->iSort != 17) && (mEquipItem[7]->iSort != 19)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[1][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 13);
		mUSER[mIndex].mEffectValue[1][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[1] = mUSER[mIndex].mEffectValue[1][0];
		tEffectValueState[1] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 15: //[공격력]
	case 30:
	case 53:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 14) && (mEquipItem[7]->iSort != 16) && (mEquipItem[7]->iSort != 20)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[0][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 12);
		mUSER[mIndex].mEffectValue[0][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[0] = mUSER[mIndex].mEffectValue[0][0];
		tEffectValueState[0] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 19: //[이동속도],[공격회피]
	case 38:
	case 57:
		if ((mEquipItem[7] == NULL) || ((mEquipItem[7]->iSort != 15) && (mEquipItem[7]->iSort != 18) && (mEquipItem[7]->iSort != 21)))
		{
			return;
		}
		mUSER[mIndex].mEffectValue[3][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 15);
		mUSER[mIndex].mEffectValue[3][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[3] = mUSER[mIndex].mEffectValue[3][0];
		tEffectValueState[3] = 1;
		mUSER[mIndex].mEffectValue[7][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 19);
		mUSER[mIndex].mEffectValue[7][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[7] = mUSER[mIndex].mEffectValue[7][0];
		tEffectValueState[7] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 82: //[호신강기]
		switch (mUTIL.ReturnMemoryValue(mUSER[mIndex].mAvatarInfo.aEquip[1][2], 4) / 10)
		{
		case 2:
			mUSER[mIndex].mEffectValue[34][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[34][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[34] = mUSER[mIndex].mEffectValue[34][0];
			tEffectValueState[34] = 1;
			break;
		case 3:
			mUSER[mIndex].mEffectValue[29][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[29][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[29] = mUSER[mIndex].mEffectValue[29][0];
			tEffectValueState[29] = 1;
			break;
		case 4:
			mUSER[mIndex].mEffectValue[33][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[33][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[33] = mUSER[mIndex].mEffectValue[33][0];
			tEffectValueState[33] = 1;
			break;
		case 5:
			mUSER[mIndex].mEffectValue[30][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[30][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[30] = mUSER[mIndex].mEffectValue[30][0];
			tEffectValueState[30] = 1;
			break;
		default:
			mUSER[mIndex].mEffectValue[9][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
			mUSER[mIndex].mEffectValue[9][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
			mDATA.aEffectValueForView[9] = mUSER[mIndex].mEffectValue[9][0];
			tEffectValueState[9] = 1;
			break;
		}
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 83: //[치명]
		mUSER[mIndex].mEffectValue[10][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 22);
		mUSER[mIndex].mEffectValue[10][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[10] = mUSER[mIndex].mEffectValue[10][0];
		tEffectValueState[10] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 84: //[운]
		mUSER[mIndex].mEffectValue[11][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 21);
		mUSER[mIndex].mEffectValue[11][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[11] = mUSER[mIndex].mEffectValue[11][0];
		tEffectValueState[11] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 106: //[체력채우기]
	case 108:
	case 110:
		if ((mIndex == mDATA.aAction.aTargetObjectIndex) && (mUniqueNumber == mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if ((mDATA.aAction.aTargetObjectIndex < 0) || (mDATA.aAction.aTargetObjectIndex > (mSERVER.mMAX_USER_NUM - 1)))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT = &mAVATAR_OBJECT[mDATA.aAction.aTargetObjectIndex];
		if ((!tAVATAR_OBJECT->mCheckValidState) || (tAVATAR_OBJECT->mUniqueNumber != mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aPShopState == 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (!mGAME.CheckPossibleAttackTarget(1, tAVATAR_OBJECT->mDATA.aAction.aSort))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue >= tAVATAR_OBJECT->GetMaxLife())
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tRecoverLifeValue = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 2);
		if ((tAVATAR_OBJECT->mDATA.aLifeValue + tRecoverLifeValue) > tAVATAR_OBJECT->GetMaxLife())
		{
			tRecoverLifeValue = tAVATAR_OBJECT->GetMaxLife() - tAVATAR_OBJECT->mDATA.aLifeValue;
		}
		if (tRecoverLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT->mDATA.aLifeValue += tRecoverLifeValue;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mDATA.aAction.aTargetObjectIndex, mDATA.aAction.aTargetObjectUniqueNumber, 8, tRecoverLifeValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 107: //[공력채우기]
	case 109:
	case 111:
		if ((mIndex == mDATA.aAction.aTargetObjectIndex) && (mUniqueNumber == mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if ((mDATA.aAction.aTargetObjectIndex < 0) || (mDATA.aAction.aTargetObjectIndex > (mSERVER.mMAX_USER_NUM - 1)))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT = &mAVATAR_OBJECT[mDATA.aAction.aTargetObjectIndex];
		if ((!tAVATAR_OBJECT->mCheckValidState) || (tAVATAR_OBJECT->mUniqueNumber != mDATA.aAction.aTargetObjectUniqueNumber))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aLifeValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aPShopState == 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (!mGAME.CheckPossibleAttackTarget(1, tAVATAR_OBJECT->mDATA.aAction.aSort))
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		if (tAVATAR_OBJECT->mDATA.aManaValue >= tAVATAR_OBJECT->GetMaxMana())
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tRecoverManaValue = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 3);
		if ((tAVATAR_OBJECT->mDATA.aManaValue + tRecoverManaValue) > tAVATAR_OBJECT->GetMaxMana())
		{
			tRecoverManaValue = tAVATAR_OBJECT->GetMaxMana() - tAVATAR_OBJECT->mDATA.aManaValue;
		}
		if (tRecoverManaValue < 1)
		{
			mDATA.aAction.aSkillNumber = 0;
			return;
		}
		tAVATAR_OBJECT->mDATA.aManaValue += tRecoverManaValue;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mDATA.aAction.aTargetObjectIndex, mDATA.aAction.aTargetObjectUniqueNumber, 9, tRecoverManaValue, 0, 0);
		mUTIL.Broadcast(TRUE, &tAVATAR_OBJECT->mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 103: //[대극방탄세]
		mUSER[mIndex].mEffectValue[12][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 23);
		mUSER[mIndex].mEffectValue[12][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[12] = mUSER[mIndex].mEffectValue[12][0];
		tEffectValueState[12] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 104: //[천문역근공]
		mUSER[mIndex].mEffectValue[13][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 24);
		mUSER[mIndex].mEffectValue[13][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[13] = mUSER[mIndex].mEffectValue[13][0];
		tEffectValueState[13] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 105: //[탈망소혼역]
		mUSER[mIndex].mEffectValue[14][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 25);
		mUSER[mIndex].mEffectValue[14][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10) * mUSER[mIndex].mSupportSkillTimeUpRatio;
		mDATA.aEffectValueForView[14] = mUSER[mIndex].mEffectValue[14][0];
		tEffectValueState[14] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 76: //[오성연환진-공격성공상승]
		mUSER[mIndex].mEffectValue[2][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 14);
		mUSER[mIndex].mEffectValue[2][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[2] = mUSER[mIndex].mEffectValue[2][0];
		tEffectValueState[2] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 77: //[오성환원진-공격회피상승]
		mUSER[mIndex].mEffectValue[3][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 15);
		mUSER[mIndex].mEffectValue[3][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[3] = mUSER[mIndex].mEffectValue[3][0];
		tEffectValueState[3] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 79: //[천왕호각진-호신강기]
		mUSER[mIndex].mEffectValue[9][0] = (int)(mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 20) * (float)GetMaxLife() * 0.01f);
		mUSER[mIndex].mEffectValue[9][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[9] = mUSER[mIndex].mEffectValue[9][0];
		tEffectValueState[9] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	case 81: //[무극천살진-치명타상승]
		mUSER[mIndex].mEffectValue[10][0] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 22);
		mUSER[mIndex].mEffectValue[10][1] = (int)mSKILL.ReturnSkillValue(mDATA.aAction.aSkillNumber, (mDATA.aAction.aSkillGradeNum1 + mDATA.aAction.aSkillGradeNum2), 10);
		mDATA.aEffectValueForView[10] = mUSER[mIndex].mEffectValue[10][0];
		tEffectValueState[10] = 1;
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		mDATA.aAction.aSkillNumber = 0;
		return;
	}
}
//PROCESS_FOR_DELETE_EFFECT_VALUE
void AVATAR_OBJECT::ProcessForDeleteEffectValue(void)
{
	int index01;
	BOOL tCheckChangeEffectValueState;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];

	tCheckChangeEffectValueState = FALSE;
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		if (mUSER[mIndex].mEffectValue[index01][0] < 1)
		{
			continue;
		}
		tCheckChangeEffectValueState = TRUE;
		mUSER[mIndex].mEffectValue[index01][0] = 0;
		mUSER[mIndex].mEffectValue[index01][1] = 0;
		mDATA.aEffectValueForView[index01] = 0;
		tEffectValueState[index01] = 2;
	}
	if (tCheckChangeEffectValueState)
	{
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}
}
//PROCESS_FOR_DEATH
void AVATAR_OBJECT::ProcessForDeath(void)
{
	int index01;

	mCheckCount = 9;

	BOOL tCheckChangeEffectValueState;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];

	tCheckChangeEffectValueState = FALSE;
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		tEffectValueState[index01] = 0;
	}
	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		if (mUSER[mIndex].mEffectValue[index01][0] < 1)
		{
			continue;
		}
		tCheckChangeEffectValueState = TRUE;
		mUSER[mIndex].mEffectValue[index01][0] = 0;
		mUSER[mIndex].mEffectValue[index01][1] = 0;
		mDATA.aEffectValueForView[index01] = 0;
		tEffectValueState[index01] = 2;
	}
	if (tCheckChangeEffectValueState)
	{
		mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(mIndex, mUniqueNumber, mUSER[mIndex].mEffectValue, &tEffectValueState[0]);
		mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	}
}
//PROCESS_FOR_TRADE_INFO
void AVATAR_OBJECT::ProcessForTradeInfo(void)
{
	int tOtherAvatarIndex;

	if (mTradeProcessState != 4)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mTradeProcessAvatarName, mIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mDATA.aName) != 0)
	{
		return;
	}
	mTRANSFER.B_TRADE_STATE_RECV(mUSER[mIndex].mAvatarInfo.aTradeMoney, mUSER[mIndex].mAvatarInfo.aTrade, mUSER[mIndex].mAvatarInfo.aTradeMoney2, mUSER[mIndex].mAvatarInfo.aTradeSocket);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//RETURN_QUEST_PRESENT_STATE
int AVATAR_OBJECT::ReturnQuestPresentState(void)
{
	int index01;
	int index02;
	QUEST_INFO* tQUEST_INFO;

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[2] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] == 0))
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, (mUSER[mIndex].mAvatarInfo.aQuestInfo[0] + 1));
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		if (mUSER[mIndex].mAvatarInfo.aLevel1 < tQUEST_INFO->qLevel)
		{
			return 0;
		}
		return 1;
	}
	if (mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 1)
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 1: //[몬스터 죽이기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < tQUEST_INFO->qSolution[1])
			{
				return 2;
			}
			return 3;
		case 2: //[아이템 입수]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 3: //[아이템 전달]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 4: //[아이템 받아오기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return 2;
			}
			return 3;
		case 5: //[대장 죽이기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return 2;
			}
			return 3;
		case 6: //[아이템 교환하기]
			switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[3])
			{
			case 1: //[교환 전]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[0])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return 2;
				}
				return 3;
			case 2: //[교환 후]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[1])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[1])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return 4;
				}
				return 5;
			}
			break;
		case 7: //[NPC 만나기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			return 2;
		case 8: //[진 점령 참여]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return 2;
			}
			return 3;
		}
	}
	return 0;
}
//RETURN_QUEST_END_CONDITION_STATE
int AVATAR_OBJECT::ReturnQuestEndConditionState(void)
{
	switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
	{
	case 1:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 2:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 3:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 4:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 5:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	case 6:
		if (ReturnQuestPresentState() == 5)
		{
			return 1;
		}
		return 0;
	case 7:
		if (ReturnQuestPresentState() == 2)
		{
			return 1;
		}
		return 0;
	case 8:
		if (ReturnQuestPresentState() == 3)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
//RETURN_QUEST_NEXT_NPC_NUMBER
int AVATAR_OBJECT::ReturnQuestNextNPCNumber(void)
{
	int index01;
	int index02;
	QUEST_INFO* tQUEST_INFO;

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[2] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] == 0) && (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] == 0))
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, (mUSER[mIndex].mAvatarInfo.aQuestInfo[0] + 1));
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		if (mUSER[mIndex].mAvatarInfo.aLevel1 < tQUEST_INFO->qLevel)
		{
			return 0;
		}
		return tQUEST_INFO->qStartNPCNumber;
	}
	if (mUSER[mIndex].mAvatarInfo.aQuestInfo[1] == 1)
	{
		tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
		if (tQUEST_INFO == NULL)
		{
			return 0;
		}
		switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[2])
		{
		case 1: //[몬스터 죽이기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < tQUEST_INFO->qSolution[1])
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 2: //[아이템 입수]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 3: //[아이템 전달]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 4: //[아이템 받아오기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			for (index01 = 0; index01 < 2; index01++)
			{
				for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
				{
					if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
					{
						break;
					}
				}
				if (index02 < MAX_INVENTORY_SLOT_NUM)
				{
					break;
				}
			}
			if (index01 == 2)
			{
				return tQUEST_INFO->qKeyNPCNumber[0];
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 5: //[대장 죽이기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 6: //[아이템 교환하기]
			switch (mUSER[mIndex].mAvatarInfo.aQuestInfo[3])
			{
			case 1: //[교환 전]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[0])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[0])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return tQUEST_INFO->qStartNPCNumber;
				}
				return tQUEST_INFO->qKeyNPCNumber[0];
			case 2: //[교환 후]
				if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] != tQUEST_INFO->qSolution[1])
				{
					return 0;
				}
				for (index01 = 0; index01 < 2; index01++)
				{
					for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
					{
						if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tQUEST_INFO->qSolution[1])
						{
							break;
						}
					}
					if (index02 < MAX_INVENTORY_SLOT_NUM)
					{
						break;
					}
				}
				if (index01 == 2)
				{
					return tQUEST_INFO->qStartNPCNumber;
				}
				return tQUEST_INFO->qEndNPCNumber;
			}
			break;
		case 7: //[NPC 만나기]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			return tQUEST_INFO->qEndNPCNumber;
		case 8: //[진 점령 참여]
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[3] != tQUEST_INFO->qSolution[0])
			{
				return 0;
			}
			if (mUSER[mIndex].mAvatarInfo.aQuestInfo[4] < 1)
			{
				return tQUEST_INFO->qStartNPCNumber;
			}
			return tQUEST_INFO->qEndNPCNumber;
		}
	}
	return 0;
}
//RETURN_ITEM_NUMBER_FOR_QUEST_REWARD
int AVATAR_OBJECT::ReturnItemNumberForQuestReward(void)
{
	int index01;
	QUEST_INFO* tQUEST_INFO;

	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if (tQUEST_INFO->qReward[index01][0] == 6)
		{
			return tQUEST_INFO->qReward[index01][1];
		}
	}
	return 0;
}
//RETURN_ITEM_QUANTITY_FOR_QUEST_REWARD
int AVATAR_OBJECT::ReturnItemQuantityForQuestReward(void)
{
	int index01;
	QUEST_INFO* tQUEST_INFO;
	ITEM_INFO* tITEM_INFO;

	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if (tQUEST_INFO->qReward[index01][0] != 6)
		{
			continue;
		}
		tITEM_INFO = mITEM.Search(tQUEST_INFO->qReward[index01][1]);
		if (tITEM_INFO == NULL)
		{
			return 0;
		}
		if (tITEM_INFO->iSort == 2)
		{
			return 1;
		}
		return 0;
	}
	return 0;
}
//SUMMON_QUEST_BOSS
int AVATAR_OBJECT::SummonQuestBoss(void)
{
	QUEST_INFO* tQUEST_INFO;
	float tCoord[3];

	if ((mUSER[mIndex].mAvatarInfo.aQuestInfo[2] != 5) || (ReturnQuestPresentState() != 2))
	{
		return 0;
	}
	tQUEST_INFO = mQUEST.Search(mUSER[mIndex].mAvatarInfo.aTribe, mUSER[mIndex].mAvatarInfo.aQuestInfo[0]);
	if (tQUEST_INFO == NULL)
	{
		return 0;
	}
	if (mSERVER_INFO.mServerNumber != tQUEST_INFO->qSummonInfo[0])
	{
		return 0;
	}
	tCoord[0] = (float)tQUEST_INFO->qSummonInfo[1];
	tCoord[1] = (float)tQUEST_INFO->qSummonInfo[2];
	tCoord[2] = (float)tQUEST_INFO->qSummonInfo[3];
	if (mUTIL.GetLengthXYZ(&mDATA.aAction.aLocation[0], &tCoord[0]) > 300.0f)
	{
		return 0;
	}
	mSUMMON.SummonMonsterForSpecial(tQUEST_INFO->qSolution[0], &tCoord[0], TRUE);
	return 0;
}
//CHANGE_QUEST_ITEM
int AVATAR_OBJECT::ChangeQuestItem(int tItemNumber1, int tItemNumber2)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tItemNumber1)
			{
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] = tItemNumber2;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][3] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][4] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][5] = 0;
				return index01;
			}
		}
	}
	return -1;
}
//DELETE_QUEST_ITEM
int AVATAR_OBJECT::DeleteQuestItem(int tItemNumber)
{
	int index01;
	int index02;

	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < MAX_INVENTORY_SLOT_NUM; index02++)
		{
			if (mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] == tItemNumber)
			{
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][0] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][1] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][2] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][3] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][4] = 0;
				mUSER[mIndex].mAvatarInfo.aInventory[index01][index02][5] = 0;
				return index01;
			}
		}
	}
	return -1;
}

/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */
int AVATAR_OBJECT::IsUsedOrnament(void)
{
	if (mUSER[mIndex].mAvatarInfo.iUseOrnament == true && mUSER[mIndex].mAvatarInfo.aLevel1 > 112)
	{
		if (mUSER[mIndex].mAvatarInfo.aEquip[9][0] > 0 &&   // 안면?
			mUSER[mIndex].mAvatarInfo.aEquip[10][0] > 0 &&  // 가슴?
			mUSER[mIndex].mAvatarInfo.aEquip[11][0] > 0 &&  // 복부?
			mUSER[mIndex].mAvatarInfo.aEquip[12][0] > 0) {  // 팔, 다리, 어깨?
				// 장식 해방 시스템 옵션이 켜져 있고 모든 장식 아이템을
				// 착용 중이면서 갑 레벨 이상인 경우에 활성화 된다.
			if (mUSER[mIndex].mAvatarInfo.iGoldOrnamentRemainsTime > 0)
			{
				return 1;
			}
			else if (mUSER[mIndex].mAvatarInfo.iSilverOrnamentRemainsTime > 0)
			{
				return 2;
			}
			return 0;
		}

	}

	return 0;
}
/** 2009. 11. 18 : 장식 해방 시스템 (wolf) */

void AVATAR_OBJECT::AutoBuff(int tCheckMotion)
{
	int tCount = 0;
	ACTION_INFO tAction;

	if (mUSER[mIndex].mAvatarInfo.aAutoBuffScroll < mUTIL.ReturnNowDate()) 
	{
		mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	for (tCount = 0; tCount < 8; tCount++) 
	{
		if ((mUSER[mIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[tCount][0] == 0))
		{
			continue;
		}
		::memset(&tAction, 0, sizeof(ACTION_INFO));
		tAction.aSkillNumber = mUSER[mIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[tCount][0];

		tAction.aSkillGradeNum1 = mUSER[mIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[tCount][1];
		tAction.aSkillGradeNum2 = mAVATAR_OBJECT[mIndex].GetBonusSkillValue(tAction.aSkillNumber);
		tAction.aType = 0;
		tAction.aSort = 41;
		tAction.aFrame = 0.0f;
		tAction.aTargetLocation[0] = 0.0f;
		tAction.aTargetLocation[1] = 0.0f;
		tAction.aTargetLocation[2] = 0.0f;
		tAction.aTargetObjectSort = 0;
		tAction.aTargetObjectIndex = -1;
		tAction.aTargetObjectUniqueNumber = 0;
		tAction.aSkillValue = 0;
		AutoBuffStart(&tAction);
	}
}
void AVATAR_OBJECT::AutoHuntBuff()
{
	int tCount = 0;
	ACTION_INFO tAction;

	if ( (mUSER[mIndex].mAvatarInfo.aAutoHunt7Day < mUTIL.ReturnNowDate()) || (mUSER[mIndex].mAvatarInfo.aAutoHunt5Hour < 0))
	{
		mUSER[mIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mDATA.aAction.aType = 0;
	mDATA.aAction.aSort = 41;
	mDATA.aAction.aFrame = 0.0f;
	mDATA.aAction.aTargetLocation[0] = 0.0f;
	mDATA.aAction.aTargetLocation[1] = 0.0f;
	mDATA.aAction.aTargetLocation[2] = 0.0f;
	mDATA.aAction.aTargetObjectSort = 0;
	mDATA.aAction.aTargetObjectIndex = -1;
	mDATA.aAction.aTargetObjectUniqueNumber = 0;
	mDATA.aAction.aSkillValue = 0;
	mTRANSFER.B_AVATAR_ACTION_RECV(mIndex, mUniqueNumber, &mDATA, 1);
	mUTIL.Broadcast(TRUE, &mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	if (mUSER[mIndex].mAvatarInfo.aAutoBuffScroll > mUTIL.ReturnNowDate())
	{
		for (tCount = 0; tCount < 8; tCount++)
		{
			if ((mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0] == 0))
			{
				continue;
			}
			if (!mWORK.ReturnEffectState(mIndex, mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0]))
			{
				continue;
			}
			::memset(&tAction, 0, sizeof(ACTION_INFO));
			tAction.aSkillNumber = mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0];
			tAction.aSkillGradeNum1 = mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][1];
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[mIndex].GetBonusSkillValue(tAction.aSkillNumber);
			mWORK.SkillForMotion(mIndex, &tAction, 0);
			AutoBuffStart(&tAction);
		}
	}
	else
	{
		for (tCount = 0; tCount < 2; tCount++)
		{
			if ((mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0] == 0))
			{
				continue;
			}
			if (!mWORK.ReturnEffectState(mIndex, mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0]))
			{
				continue;
			}
			::memset(&tAction, 0, sizeof(ACTION_INFO));
			tAction.aSkillNumber = mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][0];
			tAction.aSkillGradeNum1 = mUSER[mIndex].mAvatarInfo.aAutoHuntData[tCount][1];
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[mIndex].GetBonusSkillValue(tAction.aSkillNumber);
			mWORK.SkillForMotion(mIndex, &tAction, 0);
			AutoBuffStart(&tAction);
		}
	}
}
void AVATAR_OBJECT::AutoBuffStart(ACTION_INFO* pAction)
{
	int tUseManaValue = 0;
	int tReduceManaRatio = 0;

	if (mUSER[mIndex].mAvatarInfo.aAutoHuntState == 0)
	{
		goto NONAUTOHUNT;
	}

	tUseManaValue = (int)mSKILL.ReturnSkillValue(pAction->aSkillNumber, pAction->aSkillGradeNum1, 1);
	tReduceManaRatio = GetReduceManaRatio();

	if (tReduceManaRatio > 0) {
		tUseManaValue -= ((tUseManaValue * tReduceManaRatio) / 100);
	}
	if (mDATA.aManaValue < tUseManaValue) 
	{
		return;
	}
	if (tUseManaValue > 0) 
	{
		mDATA.aManaValue -= tUseManaValue;
	}

NONAUTOHUNT:
	mDATA.aAction.aSkillNumber = pAction->aSkillNumber;
	mDATA.aAction.aSkillGradeNum1 = pAction->aSkillGradeNum1;
	mDATA.aAction.aSkillGradeNum2 = pAction->aSkillGradeNum2;
	mDATA.aAction.aSort = pAction->aSort;
	mDATA.aAction.aType = pAction->aType;
	mDATA.aAction.aFrame = pAction->aFrame;
	mDATA.aAction.aTargetLocation[0] = pAction->aTargetLocation[0];
	mDATA.aAction.aTargetLocation[1] = pAction->aTargetLocation[1];
	mDATA.aAction.aTargetLocation[2] = pAction->aTargetLocation[2];
	mDATA.aAction.aTargetObjectSort = pAction->aTargetObjectSort;
	mDATA.aAction.aTargetObjectIndex = pAction->aTargetObjectIndex;
	mDATA.aAction.aTargetObjectUniqueNumber = pAction->aTargetObjectUniqueNumber;
	mDATA.aAction.aSkillValue = pAction->aSkillValue;
	ProcessForCreateEffectValue(pAction);
}
BOOL AVATAR_OBJECT::CheckIfSpeedHack(int tUserIndex, ATTACK_FOR_PROTOCOL* tAttackInfo)
{
	// TRUE = speed hack
	// False = not speed hack
	// Round to low for better accuracy

	if ( (mCharAnimal > 0 && mAbsorbState == 0) || GetBonusSkillValue(7) > 6 || GetBonusSkillValue(26) > 6 || GetBonusSkillValue(45) > 6)
	{
		switch (mAVATAR_OBJECT[tUserIndex].GetWeaponType())
		{
		case 13: // Sword
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 10: // Normal AOE
				CheckAttackSpeed(620);
				break;
			case 121: // 9th
				CheckAttackSpeed(340);
				break;
			case 85: // 6th
				CheckAttackSpeed(360);
				break;
			case 58: // 4th
				CheckAttackSpeed(200);
				break;
			case 86: // 7th
				CheckAttackSpeed_2(1, 150);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 1360);
				break;
			case 122: // 10th
				CheckAttackSpeed_2(1, 90);
				CheckAttackSpeed_2(2, 650);
				CheckAttackSpeed_2(3, 1060);
				break;
			case 59: // 5th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 590);
				CheckAttackSpeed_2(3, 830);
				break;
			}
			break;
		case 14: // Blade
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 14: // Normal AOE // 650 normal max +8 buff minus 30ms
				CheckAttackSpeed(620);
				break;
			case 123: // 9th
				CheckAttackSpeed(360);
				break;
			case 87: // 6th
				CheckAttackSpeed(470);
				break;
			case 60: // 4th
				CheckAttackSpeed(260);
				break;
			case 88: // 7th
				CheckAttackSpeed_2(1, 620);
				CheckAttackSpeed_2(2, 860);
				CheckAttackSpeed_2(3, 1330);
				break;
			case 124: // 10th
				CheckAttackSpeed_2(1, 560);
				CheckAttackSpeed_2(2, 760);
				CheckAttackSpeed_2(3, 1090);
				break;
			case 61: // 5th
				CheckAttackSpeed_2(1, 330);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 830);
				break;
			}
			break;
		case 15: // Marble
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 18: // Normal AOE
				CheckAttackSpeed(500);
				break;
			case 125: // 9th
				CheckAttackSpeed(330);
				break;
			case 89: // 6th
				CheckAttackSpeed(530);
				break;
			case 62: // 4th
				CheckAttackSpeed(360);
				break;
			case 126: // 10th
				CheckAttackSpeed_2(1, 420);
				CheckAttackSpeed_2(2, 650);
				CheckAttackSpeed_2(3, 920);
				break;
			case 90: // 7th
				CheckAttackSpeed_2(1, 390);
				CheckAttackSpeed_2(2, 730);
				CheckAttackSpeed_2(3, 12260);
				break;
			case 63: // 5th
				CheckAttackSpeed_2(1, 290);
				CheckAttackSpeed_2(2, 560);
				CheckAttackSpeed_2(3, 830);
				break;
			}
			break;
		case 16: // Katana
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 29: // Normal AOE
				CheckAttackSpeed(620);
				break;
			case 127: // 9th
				CheckAttackSpeed(390);
				break;
			case 91: // 6th
				CheckAttackSpeed(470);
				break;
			case 64: // 4th
				CheckAttackSpeed(260);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 230);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 1290);
				break;
			case 128: // 10th
				CheckAttackSpeed_2(1, 200);
				CheckAttackSpeed_2(2, 440);
				CheckAttackSpeed_2(3, 1120);
				break;
			case 65: // 5th
				CheckAttackSpeed_2(1, 470);
				CheckAttackSpeed_2(2, 700);
				CheckAttackSpeed_2(3, 860);
				break;
			}
			break;
		case 17: // Double Blades
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 33: // Normal AOE
				CheckAttackSpeed(6220);
				break;
			case 129: // 9th
				CheckAttackSpeed(360);
				break;
			case 93: // 6th
				CheckAttackSpeed(360);
				break;
			case 66: // 4th
				CheckAttackSpeed(200);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 890);
				CheckAttackSpeed_2(3, 1220);
				break;
			case 130: // 10th
				CheckAttackSpeed_2(1, 200);
				CheckAttackSpeed_2(2, 470);
				CheckAttackSpeed_2(3, 1000);
				break;
			case 67: // 5th
				CheckAttackSpeed_2(1, 230);
				CheckAttackSpeed_2(2, 470);
				CheckAttackSpeed_2(3, 900);
				break;
			}
			break;
		case 18: // Lute
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 37: // Normal AOE
				CheckAttackSpeed(500);
				break;
			case 131: // 9th
				CheckAttackSpeed(330);
				break;
			case 95: // 6th
				CheckAttackSpeed(500);
				break;
			case 68: // 4th
				CheckAttackSpeed(360);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 890);
				CheckAttackSpeed_2(3, 12220);
				break;
			case 132: // 10th
				CheckAttackSpeed_2(1, 500);
				CheckAttackSpeed_2(2, 700);
				CheckAttackSpeed_2(3, 890);
				break;
			case 69: // 5th
				CheckAttackSpeed_2(1, 90);
				CheckAttackSpeed_2(2, 230);
				CheckAttackSpeed_2(3, 860);
				break;
			}
			break;
		case 19: // Light Blade
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 48: // Normal AOE
				CheckAttackSpeed(620);
				break;
			case 133: // 9th
				CheckAttackSpeed(360);
				break;
			case 97: // 6th
				CheckAttackSpeed(360);
				break;
			case 70: // 4th
				CheckAttackSpeed(2200);
				break;
			case 134: // 10th
				CheckAttackSpeed_2(1, 90);
				CheckAttackSpeed_2(2, 530);
				CheckAttackSpeed_2(3, 1030);
				break;
			case 98: // 7th
				CheckAttackSpeed_2(1, 360);
				CheckAttackSpeed_2(2, 890);
				CheckAttackSpeed_2(3, 1260);
				break;
			case 71: // 5th
				CheckAttackSpeed_2(1, 330);
				CheckAttackSpeed_2(2, 590);
				CheckAttackSpeed_2(3, 900);
				break;
			}
			break;
		case 20: // Long Spear
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 52: // Normal AOE
				CheckAttackSpeed(620);
				break;
			case 135: // 9th
				CheckAttackSpeed(400);
				break;
			case 99: // 6th
				CheckAttackSpeed(470);
				break;
			case 72: // 4th
				CheckAttackSpeed(260);
				break;
			case 136: // 10th
				CheckAttackSpeed_2(1, 140);
				CheckAttackSpeed_2(2, 670);
				CheckAttackSpeed_2(3, 12200);
				break;
			case 100: // 7th
				CheckAttackSpeed_2(1, 290);
				CheckAttackSpeed_2(2, 610);
				CheckAttackSpeed_2(3, 1450);
				break;
			case 73: // 5th
				CheckAttackSpeed_2(1, 390);
				CheckAttackSpeed_2(2, 560);
				CheckAttackSpeed_2(3, 1030);
				break;
			}
			break;
		case 21: // Scepter
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 56: // Normal AOE
				CheckAttackSpeed(500);
				break;
			case 137: // 9th
				CheckAttackSpeed(330);
				break;
			case 101: // 6th
				CheckAttackSpeed(500);
				break;
			case 74: // 4th
				CheckAttackSpeed(330);
				break;
			case 138: // 10th
				CheckAttackSpeed_2(1, 360);
				CheckAttackSpeed_2(2, 590);
				CheckAttackSpeed_2(3, 940);
				break;
			case 102: // 7th
				CheckAttackSpeed_2(1, 470);
				CheckAttackSpeed_2(2, 940);
				CheckAttackSpeed_2(3, 1290);
				break;
			case 75: // 5th
				CheckAttackSpeed_2(1, 230);
				CheckAttackSpeed_2(2, 530);
				CheckAttackSpeed_2(3, 790);
				break;
			}
			break;
		}
	}
	else
	{
		switch (mAVATAR_OBJECT[tUserIndex].GetWeaponType())
		{
		case 13: // Sword
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 10: // Normal AOE
				CheckAttackSpeed(650);
				break;
			case 121: // 9th
				CheckAttackSpeed(370);
				break;
			case 85: // 6th
				CheckAttackSpeed(390);
				break;
			case 58: // 4th
				CheckAttackSpeed(230);
				break;
			case 86: // 7th
				CheckAttackSpeed_2(1, 180);
				CheckAttackSpeed_2(2, 650);
				CheckAttackSpeed_2(3, 1390);
				break;
			case 122: // 10th
				CheckAttackSpeed_2(1, 120);
				CheckAttackSpeed_2(2, 680);
				CheckAttackSpeed_2(3, 1090);
				break;
			case 59: // 5th
				CheckAttackSpeed_2(1, 290);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 860);
				break;
			}
			break;
		case 14: // Blade
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 14: // Normal AOE // 650 normal max +8 buff minus 30ms
				CheckAttackSpeed(650);
				break;
			case 123: // 9th
				CheckAttackSpeed(420);
				break;
			case 87: // 6th
				CheckAttackSpeed(500);
				break;
			case 60: // 4th
				CheckAttackSpeed(290);
				break;
			case 88: // 7th
				CheckAttackSpeed_2(1, 650);
				CheckAttackSpeed_2(2, 890);
				CheckAttackSpeed_2(3, 1360);
				break;
			case 124: // 10th
				CheckAttackSpeed_2(1, 590);
				CheckAttackSpeed_2(2, 790);
				CheckAttackSpeed_2(3, 1120);
				break;
			case 61: // 5th
				CheckAttackSpeed_2(1, 360);
				CheckAttackSpeed_2(2, 650);
				CheckAttackSpeed_2(3, 860);
				break;
			}
			break;
		case 15: // Marble
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 18: // Normal AOE
				CheckAttackSpeed(530);
				break;
			case 125: // 9th
				CheckAttackSpeed(360);
				break;
			case 89: // 6th
				CheckAttackSpeed(560);
				break;
			case 62: // 4th
				CheckAttackSpeed(390);
				break;
			case 126: // 10th
				CheckAttackSpeed_2(1, 450);
				CheckAttackSpeed_2(2, 680);
				CheckAttackSpeed_2(3, 950);
				break;
			case 90: // 7th
				CheckAttackSpeed_2(1, 420);
				CheckAttackSpeed_2(2, 760);
				CheckAttackSpeed_2(3, 1290);
				break;
			case 63: // 5th
				CheckAttackSpeed_2(1, 320);
				CheckAttackSpeed_2(2, 590);
				CheckAttackSpeed_2(3, 860);
				break;
			}
			break;
		case 16: // Katana
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 29: // Normal AOE
				CheckAttackSpeed(650);
				break;
			case 127: // 9th
				CheckAttackSpeed(420);
				break;
			case 91: // 6th
				CheckAttackSpeed(500);
				break;
			case 64: // 4th
				CheckAttackSpeed(290);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 650);
				CheckAttackSpeed_2(3, 1320);
				break;
			case 128: // 10th
				CheckAttackSpeed_2(1, 230);
				CheckAttackSpeed_2(2, 470);
				CheckAttackSpeed_2(3, 1150);
				break;
			case 65: // 5th
				CheckAttackSpeed_2(1, 500);
				CheckAttackSpeed_2(2, 730);
				CheckAttackSpeed_2(3, 890);
				break;
			}
			break;
		case 17: // Double Blades
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 33: // Normal AOE
				CheckAttackSpeed(650);
				break;
			case 129: // 9th
				CheckAttackSpeed(390);
				break;
			case 93: // 6th
				CheckAttackSpeed(390);
				break;
			case 66: // 4th
				CheckAttackSpeed(230);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 290);
				CheckAttackSpeed_2(2, 920);
				CheckAttackSpeed_2(3, 1250);
				break;
			case 130: // 10th
				CheckAttackSpeed_2(1, 230);
				CheckAttackSpeed_2(2, 500);
				CheckAttackSpeed_2(3, 1030);
				break;
			case 67: // 5th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 500);
				CheckAttackSpeed_2(3, 930);
				break;
			}
			break;
		case 18: // Lute
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 37: // Normal AOE
				CheckAttackSpeed(530);
				break;
			case 131: // 9th
				CheckAttackSpeed(360);
				break;
			case 95: // 6th
				CheckAttackSpeed(530);
				break;
			case 68: // 4th
				CheckAttackSpeed(390);
				break;
			case 92: // 7th
				CheckAttackSpeed_2(1, 290);
				CheckAttackSpeed_2(2, 920);
				CheckAttackSpeed_2(3, 1250);
				break;
			case 132: // 10th
				CheckAttackSpeed_2(1, 530);
				CheckAttackSpeed_2(2, 730);
				CheckAttackSpeed_2(3, 920);
				break;
			case 69: // 5th
				CheckAttackSpeed_2(1, 120);
				CheckAttackSpeed_2(2, 260);
				CheckAttackSpeed_2(3, 890);
				break;
			}
			break;
		case 19: // Light Blade
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 48: // Normal AOE
				CheckAttackSpeed(650);
				break;
			case 133: // 9th
				CheckAttackSpeed(390);
				break;
			case 97: // 6th
				CheckAttackSpeed(390);
				break;
			case 70: // 4th
				CheckAttackSpeed(230);
				break;
			case 134: // 10th
				CheckAttackSpeed_2(1, 120);
				CheckAttackSpeed_2(2, 560);
				CheckAttackSpeed_2(3, 1060);
				break;
			case 98: // 7th
				CheckAttackSpeed_2(1, 360);
				CheckAttackSpeed_2(2, 890);
				CheckAttackSpeed_2(3, 1260);
				break;
			case 71: // 5th
				CheckAttackSpeed_2(1, 360);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 930);
				break;
			}
			break;
		case 20: // Long Spear
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 52: // Normal AOE
				CheckAttackSpeed(650);
				break;
			case 135: // 9th
				CheckAttackSpeed(430);
				break;
			case 99: // 6th
				CheckAttackSpeed(500);
				break;
			case 72: // 4th
				CheckAttackSpeed(290);
				break;
			case 136: // 10th
				CheckAttackSpeed_2(1, 170);
				CheckAttackSpeed_2(2, 700);
				CheckAttackSpeed_2(3, 1230);
				break;
			case 100: // 7th
				CheckAttackSpeed_2(1, 320);
				CheckAttackSpeed_2(2, 640);
				CheckAttackSpeed_2(3, 1480);
				break;
			case 73: // 5th
				CheckAttackSpeed_2(1, 420);
				CheckAttackSpeed_2(2, 590);
				CheckAttackSpeed_2(3, 1060);
				break;
			}
			break;
		case 21: // Scepter
			switch (tAttackInfo->mAttackActionValue2)
			{
			case 56: // Normal AOE
				CheckAttackSpeed(530);
				break;
			case 137: // 9th
				CheckAttackSpeed(360);
				break;
			case 101: // 6th
				CheckAttackSpeed(530);
				break;
			case 74: // 4th
				CheckAttackSpeed(360);
				break;
			case 138: // 10th
				CheckAttackSpeed_2(1, 390);
				CheckAttackSpeed_2(2, 620);
				CheckAttackSpeed_2(3, 970);
				break;
			case 102: // 7th
				CheckAttackSpeed_2(1, 500);
				CheckAttackSpeed_2(2, 970);
				CheckAttackSpeed_2(3, 1320);
				break;
			case 75: // 5th
				CheckAttackSpeed_2(1, 260);
				CheckAttackSpeed_2(2, 560);
				CheckAttackSpeed_2(3, 820);
				break;
			}
			break;
		}
	}


	//switch (mAVATAR_OBJECT[tUserIndex].GetWeaponType())
	//{
	//case 13: // Sword
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 10: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 121: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (370 - (370 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 85: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 58: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (230 - (230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 86: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (180 - (180 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1390 - (1390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 122: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (120 - (120 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (680 - (680 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1090 - (1090 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 59: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (620 - (620 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (860 - (860 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 14: // Blade
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 14: // Normal AOE // 650 normal max +8 buff minus 30ms
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 123: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (420 - (420 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 87: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 60: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 88: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (890 - (890 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1360 - (1360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 124: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (590 - (590 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (790 - (790 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1120 - (1120 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 61: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (860 - (860 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 15: // Marble
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 18: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 125: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 89: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (560 - (560 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 62: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 126: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (450 - (450 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (680 - (680 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (950 - (950 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 90: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (420 - (420 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (760 - (760 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1290 - (1290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 63: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (320 - (320 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (590 - (590 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (860 - (860 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 16: // Katana
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 29: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 127: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (420 - (420 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 91: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 64: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 92: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (260 - (260 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1320 - (1320 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 128: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (230 - (230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (470 - (470 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1150 - (1150 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 65: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (730 - (730 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (890 - (890 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 17: // Double Blades
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 33: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 129: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 93: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 66: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (230 - (230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 92: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (920 - (920 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1250 - (1250 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 130: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (230 - (230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1030 - (1030 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 67: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (260 - (260 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (930 - (930 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 18: // Lute
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 37: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 131: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 95: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 68: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 92: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (920 - (920 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1250 - (1250 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 132: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (730 - (730 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (920 - (920 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 69: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (120 - (120 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (260 - (260 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (890 - (890 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 19: // Light Blade
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 48: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 133: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 97: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 70: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (230 - (230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 134: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (120 - (120 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (560 - (560 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1060 - (1060 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 98: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (890 - (890 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1260 - (1260 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 71: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (620 - (620 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (930 - (930 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 20: // Long Spear
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 52: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (650 - (650 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 135: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (430 - (430 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 99: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 72: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (290 - (290 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 136: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (170 - (170 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (700 - (700 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1230 - (1230 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 100: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (320 - (320 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (640 - (640 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1480 - (1480 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 73: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (420 - (420 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (590 - (590 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1060 - (1060 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//case 21: // Scepter
	//	switch (tAttackInfo->mAttackActionValue2)
	//	{
	//	case 56: // Normal AOE
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 137: // 9th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 101: // 6th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (530 - (530 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 74: // 4th
	//		if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (360 - (360 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//		{
	//			return TRUE;
	//		}
	//		break;
	//	case 138: // 10th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (390 - (390 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (620 - (620 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (970 - (970 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 102: // 7th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (500 - (500 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (970 - (970 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (1320 - (1320 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	case 75: // 5th
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 1)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (260 - (260 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 2)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (560 - (560 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		if (mUSER[tUserIndex].mNowAttackPacketNum == 3)
	//		{
	//			if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (820 - (820 * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))
	//			{
	//				return TRUE;
	//			}
	//		}
	//		break;
	//	}
	//	break;
	//}
	return FALSE;
}