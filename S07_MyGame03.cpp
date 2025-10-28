#include "MainApp.h"

MyUtil mUTIL;

MyUtil::MyUtil(void)
{
	mEquipPart[0] = 2;
	mEquipPart[1] = 3;
	mEquipPart[2] = 4;
	mEquipPart[3] = 5;
	mEquipPart[4] = 6;
	mEquipPart[5] = 7;
	mEquipPart[6] = 0;
	mEquipPart[7] = 9;
	mEquipPart[8] = 10;
	mEquipPart[9] = 11;
	mEquipPart[10] = 12;
	mEquipPart[11] = 13;
	mEquipPart[12] = 14;
}
// CHECK_NAME_STRING
BOOL MyUtil::CheckNameString(char* tString)
{
	int index01;
	WORD tUnicode;

	for (index01 = 0; index01 < (int)strlen(tString); index01++)
	{
		if ((BYTE)tString[index01] < 128)
		{
			if (
				(tString[index01] == '0') ||
				(tString[index01] == '1') ||
				(tString[index01] == '2') ||
				(tString[index01] == '3') ||
				(tString[index01] == '4') ||
				(tString[index01] == '5') ||
				(tString[index01] == '6') ||
				(tString[index01] == '7') ||
				(tString[index01] == '8') ||
				(tString[index01] == '9') ||
				(tString[index01] == 'A') ||
				(tString[index01] == 'B') ||
				(tString[index01] == 'C') ||
				(tString[index01] == 'D') ||
				(tString[index01] == 'E') ||
				(tString[index01] == 'F') ||
				(tString[index01] == 'G') ||
				(tString[index01] == 'H') ||
				(tString[index01] == 'I') ||
				(tString[index01] == 'J') ||
				(tString[index01] == 'K') ||
				(tString[index01] == 'L') ||
				(tString[index01] == 'M') ||
				(tString[index01] == 'N') ||
				(tString[index01] == 'O') ||
				(tString[index01] == 'P') ||
				(tString[index01] == 'Q') ||
				(tString[index01] == 'R') ||
				(tString[index01] == 'S') ||
				(tString[index01] == 'T') ||
				(tString[index01] == 'U') ||
				(tString[index01] == 'V') ||
				(tString[index01] == 'W') ||
				(tString[index01] == 'X') ||
				(tString[index01] == 'Y') ||
				(tString[index01] == 'Z') ||
				(tString[index01] == 'a') ||
				(tString[index01] == 'b') ||
				(tString[index01] == 'c') ||
				(tString[index01] == 'd') ||
				(tString[index01] == 'e') ||
				(tString[index01] == 'f') ||
				(tString[index01] == 'g') ||
				(tString[index01] == 'h') ||
				(tString[index01] == 'i') ||
				(tString[index01] == 'j') ||
				(tString[index01] == 'k') ||
				(tString[index01] == 'l') ||
				(tString[index01] == 'm') ||
				(tString[index01] == 'n') ||
				(tString[index01] == 'o') ||
				(tString[index01] == 'p') ||
				(tString[index01] == 'q') ||
				(tString[index01] == 'r') ||
				(tString[index01] == 's') ||
				(tString[index01] == 't') ||
				(tString[index01] == 'u') ||
				(tString[index01] == 'v') ||
				(tString[index01] == 'w') ||
				(tString[index01] == 'x') ||
				(tString[index01] == 'y') ||
				(tString[index01] == 'z'))
			{
				continue;
			}
			return FALSE;
		}
		else
		{
#ifdef __TK__
			index01++;
#else
			return FALSE;
#endif
		}
	}
#if 0
	for (index01 = 0; index01 < (int)strlen(tString); index01++)
	{
		if ((BYTE)tString[index01] < 128)
		{
			continue;
		}
		index01++;
		if (!MultiByteToWideChar(CP_ACP, 0, &tString[(index01 - 1)], 2, &tUnicode, 1))
		{
			return FALSE;
		}
		if ((tUnicode >= 0x4E00) && (tUnicode <= 0x9FBF))
		{
			continue;
		}
		if ((tUnicode >= 0x3400) && (tUnicode <= 0x4DBF))
		{
			continue;
		}
		/*
		if(mbstowcs((wchar_t *)&tUnicode, &tString[(index01 - 1)], 1) < 0 ) {
			return FALSE;
		}

		if( ( tUnicode >= 0x4E00 ) && ( tUnicode <= 0x9FFF ) )
		{
			continue;
		}
		*/
#if 0
		if ((tUnicode >= 0x4E00) && (tUnicode <= 0x9FBF))
		{
			continue;
		}
		if ((tUnicode >= 0x3400) && (tUnicode <= 0x4DBF))
		{
			continue;
		}
#endif
		return FALSE;
	}
#endif
	return TRUE;
}
// CHECK_OVER_MAXIMUM
BOOL MyUtil::CheckOverMaximum(int tValue1, int tValue2)
{
	LONGLONG tCheckValue = (LONGLONG)tValue1 + (LONGLONG)tValue2;

	if (tCheckValue > MAX_NUMBER_SIZE)
	{
		return TRUE;
	}
	return FALSE;
}
// RETURN_FIXED_LEVEL
int MyUtil::ReturnFixedLevel(int tLevel)
{
	if (tLevel < 100)
	{
		return tLevel;
	}
	switch (tLevel)
	{
	case 100:
		return 102;
	case 101:
		return 105;
	case 102:
		return 108;
	case 103:
		return 111;
	case 104:
		return 114;
	case 105:
		return 117;
	case 106:
		return 120;
	case 107:
		return 123;
	case 108:
		return 126;
	case 109:
		return 129;
	case 110:
		return 132;
	case 111:
		return 135;
	case 112:
		return 138;
	case 113:
		return 143;
	case 114:
		return 149;
	case 115:
		return 155;
	case 116:
		return 161;
	case 117:
		return 167;
	case 118:
		return 173;
	case 119:
		return 179;
	case 120:
		return 185;
	case 121:
		return 191;
	case 122:
		return 197;
	case 123:
		return 203;
	case 124:
		return 209;
	case 125:
		return 215;
	case 126:
		return 221;
	case 127:
		return 227;
	case 128:
		return 233;
	case 129:
		return 239;
	case 130:
		return 245;
	case 131:
		return 251;
	case 132:
		return 257;
	case 133:
		return 263;
	case 134:
		return 269;
	case 135:
		return 275;
	case 136:
		return 281;
	case 137:
		return 287;
	case 138:
		return 293;
	case 139:
		return 299;
	case 140:
		return 305;
	case 141:
		return 311;
	case 142:
		return 317;
	case 143:
		return 323;
	case 144:
		return 329;
	case 145:
		return 335;
#ifdef __GOD__
	case 146:
		return 355;
	case 147:
		return 375;
	case 148:
		return 395;
	case 149:
		return 415;
	case 150:
		return 455;
	case 151:
		return 495;
	case 152:
		return 535;
	case 153:
		return 575;
	case 154:
		return 635;
	case 155:
		return 695;
	case 156:
		return 755;
	case 157:
		return 815;
#endif
	}
	return 1;
}
// CHECK_POSSIBLE_EQUIP_ITEM
BOOL MyUtil::CheckPossibleEquipItem(int iIndex, int tTribe, int tEquipIndex, int tLevel, int tRebirthLevel)
{
	ITEM_INFO* tITEM_INFO;

	tITEM_INFO = mITEM.Search(iIndex);
	if (tITEM_INFO == NULL)
	{
		return FALSE;
	}
	if (tITEM_INFO->iEquipInfo[0] != 1)
	{
		if ((tITEM_INFO->iEquipInfo[0] - 2) != tTribe)
		{
			return FALSE;
		}
	}
	if ((tEquipIndex >= 0) && (tEquipIndex <= (MAX_EQUIP_SLOT_NUM - 1)))
	{
		if (tITEM_INFO->iEquipInfo[1] != mEquipPart[tEquipIndex])
		{
			return FALSE;
		}
	}
	if ((tITEM_INFO->iLevelLimit + tITEM_INFO->iMartialLevelLimit) > tLevel)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 13553 || tITEM_INFO->iIndex == 33553 || tITEM_INFO->iIndex == 53553) && tRebirthLevel < 6)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 13554 || tITEM_INFO->iIndex == 33554 || tITEM_INFO->iIndex == 53554) && tRebirthLevel < 12)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex >= 87206 && tITEM_INFO->iIndex <= 87213 || tITEM_INFO->iIndex >= 87228 && tITEM_INFO->iIndex <= 87235 || tITEM_INFO->iIndex >= 87250 && tITEM_INFO->iIndex <= 87257) && tRebirthLevel < 12)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 216 || tITEM_INFO->iIndex == 217 || tITEM_INFO->iIndex == 218) && tRebirthLevel < 7)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 86754 || tITEM_INFO->iIndex == 86756 || tITEM_INFO->iIndex == 86758) && tRebirthLevel < 6)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 86755 || tITEM_INFO->iIndex == 86757 || tITEM_INFO->iIndex == 86759) && tRebirthLevel < 12)
	{
		return FALSE;
	}
	if (tITEM_INFO->iCheckItemSet == 3 && tRebirthLevel < 12)
	{
		return FALSE;
	}
	if ((tITEM_INFO->iIndex == 2303 || tITEM_INFO->iIndex == 2304 || tITEM_INFO->iIndex == 2305) && tRebirthLevel < 7)
	{
		return FALSE;
	}
	int CheckIfLegend = mUTIL.ReturnItemSort(tITEM_INFO->iIndex);
	if ((CheckIfLegend == 1 || CheckIfLegend == 2 || CheckIfLegend == 4 || CheckIfLegend == 5 || CheckIfLegend == 6 || CheckIfLegend == 8 || CheckIfLegend == 9 || CheckIfLegend == 10 || CheckIfLegend == 11 || CheckIfLegend == 12) && tRebirthLevel < 12)
	{
		return FALSE;
	}
	return TRUE;
}

void MyUtil::ProcessForExperience(int tUserIndex, int tGainGeneralExperience, int tGainPatExperience, int tGainLifeValue)
{
	if ((tUserIndex < 0) || (tUserIndex > (mSERVER.mMAX_USER_NUM - 1)) || (!mUSER[tUserIndex].mCheckValidState) || (mUSER[tUserIndex].mMoveZoneResult == 1) || (tGainGeneralExperience < 1))
	{
		return;
	}

	int index01;
	float tMaxGeneralExperienceRange;
	int tPresentGeneralExperienceRatio;
	int tNextGeneralExperienceRatio;
	int tPresentAvatarLevel;
	int tNextAvatarLevel;

	if (mUSER[tUserIndex].mAvatarInfo.aLevel1 == MAX_LIMIT_LEVEL_NUM)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 == MAX_NUMBER_SIZE && mUSER[tUserIndex].mAvatarInfo.aLevel2 <= MAX_LIMIT_HIGH_LEVEL_NUM)
		{
			switch (mUSER[tUserIndex].mAvatarInfo.aLevel2)
			{
#ifdef M33
			case 0:
				break;
#else
			case 0:
				mUSER[tUserIndex].mAvatarInfo.aSkillPoint += 100;
				mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
				mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
				mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
				mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
				mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
				return;
			case 1:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aSkillPoint += 100;
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 2:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aSkillPoint += 100;
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 3:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aSkillPoint += 100;
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;

			case 4:
				if (MAX_LIMIT_HIGH_LEVEL_NUM == mUSER[tUserIndex].mAvatarInfo.aLevel2)
				{
					break;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 5:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 6:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 7:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;

			case 8:
				if (MAX_LIMIT_HIGH_LEVEL_NUM == mUSER[tUserIndex].mAvatarInfo.aLevel2)
				{
					break;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 9:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 10:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 11:
				if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 == mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
					mUSER[tUserIndex].mAvatarInfo.aLevel2 += 1;
					mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
					mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
					mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
					mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 11, mUSER[tUserIndex].mAvatarInfo.aLevel2, mUSER[tUserIndex].mAvatarInfo.aSkillPoint, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
					return;
				}
				break;
			case 12:
				break;
#endif
			}
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tGainGeneralExperience) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tGainGeneralExperience = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			if (tGainGeneralExperience > 0) // God Level Add StatPoints
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tGainGeneralExperience) < mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
				{
					tMaxGeneralExperienceRange = (float)mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2);
					tPresentGeneralExperienceRatio = (int)((float)mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 * 100.0f / tMaxGeneralExperienceRange);
					tNextGeneralExperienceRatio = (int)((float)(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tGainGeneralExperience) * 100.0f / tMaxGeneralExperienceRange);
					if (tPresentGeneralExperienceRatio < tNextGeneralExperienceRatio)
					{
						/*	mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (tNextGeneralExperienceRatio - tPresentGeneralExperienceRatio);
							mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
							mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);	*/
					}
				}
				else
				{
					mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 100;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tGainGeneralExperience;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			if (tGainLifeValue > 0)
			{
				mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]))
				{
					tGainPatExperience = GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
				}
			}
			else
			{
				tGainPatExperience = 0;
			}
			if (tGainPatExperience > 0)
			{
				if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
				{
					mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
					mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
				}
				mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
				mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience) > MAX_NUMBER_SIZE)
		{
			tGainGeneralExperience = MAX_NUMBER_SIZE - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
		}
		if (tGainGeneralExperience > 0) // M33 Add Stat Points
		{
			if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience < MAX_NUMBER_SIZE)
			{
				tMaxGeneralExperienceRange = (float)(MAX_NUMBER_SIZE - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1));
				tPresentGeneralExperienceRatio = (int)((float)(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 100.0f / tMaxGeneralExperienceRange);
				tNextGeneralExperienceRatio = (int)((float)(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 100.0f / tMaxGeneralExperienceRange);
				if (tPresentGeneralExperienceRatio < tNextGeneralExperienceRatio)
				{
					/*	mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (tNextGeneralExperienceRatio - tPresentGeneralExperienceRatio);
						mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);	*/
				}
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 100;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(2, mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		if (tGainGeneralExperience > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tGainGeneralExperience;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 >= MAX_NUMBER_SIZE)
			{
				mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1 = 0;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(34, mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
		}
		if (tGainLifeValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
		{
			if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]))
			{
				tGainPatExperience = GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
			}
		}
		else
		{
			tGainPatExperience = 0;
		}
		if (tGainPatExperience > 0)
		{
			if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
			{
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;
	}

	tPresentAvatarLevel = mLEVEL.ReturnLevel(mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
	tNextAvatarLevel = mLEVEL.ReturnLevel((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tGainGeneralExperience));

	if (tNextAvatarLevel > tPresentAvatarLevel)
	{
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 1, (tNextAvatarLevel - tPresentAvatarLevel), 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
		for (index01 = (tPresentAvatarLevel + 1); index01 <= tNextAvatarLevel; index01++)
		{
			if ((index01 - 1) < 99)
			{
				mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 5;
			}
			else if ((index01 - 1) < 112)
			{
				mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 15;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += 30;
			}

			// Beginner Rewards
			if (index01 == 45)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 75)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 105)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 114)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 123)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 132)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (index01 == 141)
			{
				mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 1;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(107, mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mLEVEL.ReturnLevelFactor3(index01);
		}
		mUSER[tUserIndex].mAvatarInfo.aLevel1 = tNextAvatarLevel;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = tNextAvatarLevel;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
	}

	if (tGainGeneralExperience > 0)
	{
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tGainGeneralExperience;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
	{
		tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	}
	if (tGainLifeValue > 0)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] > 0)
	{
		if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience) > GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]))
		{
			tGainPatExperience = GetPetMaxExpCapacity(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]) - mUSER[tUserIndex].mAvatarInfo.aEquip[8][2];
		}
	}
	else
	{
		tGainPatExperience = 0;
	}
	if (tGainPatExperience > 0)
	{
		if (mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], (mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] + tGainPatExperience)) > mPAT.ReturnGrowStep(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0], mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]))
		{
			mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 10, 0, 0, 0);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[8][2] += tGainPatExperience;
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[8][1] += tGainPatExperience;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(14, mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}

// PROCESS_FOR_DROP_ITEM
BOOL MyUtil::ProcessForDropItem(int tDropSort, int tItemIndex, int tItemQuantity, int tItemValue, int tItemRecognitionNumber, float tLocation[3], char tMaster[MAX_AVATAR_NAME_LENGTH], char tPartyName[MAX_AVATAR_NAME_LENGTH], int tPartyState, int tTribe, int tSocket[MAX_SOCKETSYSTEM_ARRAY])
{
	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;

	switch (tDropSort)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		tITEM_INFO = mITEM.Search(tItemIndex);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (tITEM_INFO->iSort == 2 || tITEM_INFO->iCheckExpire == 999)
		{
			tItemQuantity = MAX_ITEM_DUPLICATION_NUM;
		}
		break;
	case 5:
		break;
	case 6:
		break;
	case 7:
		break;
	case 8:
		break;
	case 9:
		break;
	case 10:
		break;
	case 11:
		break;
	case 12:
		break;
	default:
		return FALSE;
	}
	tITEM_INFO = mITEM.Search(tItemIndex);
	if (tITEM_INFO == NULL)
	{
		return FALSE;
	}
	switch (tITEM_INFO->iType)
	{
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	case 4:
		break;
	case 5:
	case 6:
	case 7:
	case 8:
		break;
	default:
		return FALSE;
	}
	switch (tITEM_INFO->iSort)
	{
	case 1:
		tItemValue = 0;
		if ((tItemQuantity < 1) || (tItemQuantity > MAX_NUMBER_SIZE))
		{
			return FALSE;
		}
		if (tDropSort == 1)
		{
			mGAME.AddTribeBankInfo(mGAME.ReturnTribeForSymbol(tTribe), (int)((float)tItemQuantity * 0.1f));
			tItemQuantity -= (int)((float)tItemQuantity * 0.1f);
		}
		break;
	case 2:
		tItemValue = 0;
		if ((tItemQuantity < 1) || (tItemQuantity > MAX_ITEM_DUPLICATION_NUM))
		{
			return FALSE;
		}
		break;
	case 3:
	case 4:
	case 5:
	case 6:
		if (tITEM_INFO->iCheckExpire != 99)
		{
			tItemQuantity = 0;
			tItemValue = 0;
		}
		break;
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
	case 18:
	case 19:
	case 20:
	case 21:
		tItemQuantity = 0;
		if ((mUTIL.ReturnISValue(tItemValue) < 0) || (mUTIL.ReturnISValue(tItemValue) > MAX_IMPROVE_ITEM_NUM_NEXT) || (mUTIL.ReturnIUValue(tItemValue) < 0) || (mUTIL.ReturnIUValue(tItemValue) > MAX_ADD_ITEM_NUM))
		{
			return FALSE;
		}
		break;
	case 22:
		tItemQuantity = 1;
		break;
	case 23:
	case 24:
	case 25:
	case 26:
	case 27:
	case 28:
	case 29:
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
		break;
	default:
		return FALSE;
	}
	for (index01 = 0; index01 < MAX_ITEM_OBJECT_NUM; index01++)
	{
		if (!mITEM_OBJECT[index01].mCheckValidState)
		{
			break;
		}
	}
	if (index01 == MAX_ITEM_OBJECT_NUM)
	{
		return FALSE;
	}
	mITEM_OBJECT[index01].mCheckValidState = TRUE;
	mITEM_OBJECT[index01].mUniqueNumber = mGAME.mItemObjectUniqueNumber;
	mGAME.mItemObjectUniqueNumber++;
	mITEM_OBJECT[index01].mDATA.iIndex = tItemIndex;
	mITEM_OBJECT[index01].mDATA.iQuantity = tItemQuantity;
	mITEM_OBJECT[index01].mDATA.iValue = tItemValue;
	mITEM_OBJECT[index01].mDATA.iItemRecognitionNumber = tItemRecognitionNumber;
	mITEM_OBJECT[index01].mDATA.iLocation[0] = tLocation[0];
	mITEM_OBJECT[index01].mDATA.iLocation[1] = tLocation[1];
	mITEM_OBJECT[index01].mDATA.iLocation[2] = tLocation[2];
	strncpy(mITEM_OBJECT[index01].mDATA.iMaster, tMaster, MAX_AVATAR_NAME_LENGTH);
	strncpy(mITEM_OBJECT[index01].mDATA.iPartyName, tPartyName, MAX_AVATAR_NAME_LENGTH);
	mITEM_OBJECT[index01].mDATA.iPartyState = tPartyState;
	mITEM_OBJECT[index01].mDATA.iCreateTime = GetTickCount();
	mITEM_OBJECT[index01].mDATA.iPresentTime = GetTickCount();
	mITEM_OBJECT[index01].mDATA.iCreateState = 1;
	if (tSocket == 0)
	{
		for (index02 = 0; index02 < MAX_SOCKETSYSTEM_ARRAY; index02++)
		{
			mITEM_OBJECT[index01].mDATA.iSocket[index02] = 0;
		}
	}
	else
	{
		for (index02 = 0; index02 < MAX_SOCKETSYSTEM_ARRAY; index02++)
		{
			mITEM_OBJECT[index01].mDATA.iSocket[index02] = tSocket[index02];
		}
	}
	mITEM_OBJECT[index01].SetSpaceIndex();
	mITEM_OBJECT[index01].mITEM_INFO = tITEM_INFO;
	mITEM_OBJECT[index01].mUpdateTimeForBroadcast = GetTickCount();
	mTRANSFER.B_ITEM_ACTION_RECV(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 4);
	mUTIL.Broadcast(TRUE, &tLocation[0], UNIT_SCALE_RADIUS3, false);
	return TRUE;
}
// BROADCAST
// MIR
void MyUtil::Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, bool bUDPSend, int type)
{
	int index01;
	int tSpaceIndex[3];
	float tLocation[3];
	float tPostDistance = static_cast<float>(iScale) * MAX_RADIUS_FOR_NETWORK;

	if (tCheckInRange)
	{
		tSpaceIndex[0] = (int)(tPostLocation[0] / MAX_RADIUS_FOR_NETWORK);
		tSpaceIndex[1] = (int)(tPostLocation[1] / MAX_RADIUS_FOR_NETWORK);
		tSpaceIndex[2] = (int)(tPostLocation[2] / MAX_RADIUS_FOR_NETWORK);

		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > iScale))
			{
				continue;
			}
			CopyMemory(&tLocation[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 12);
			if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (tPostDistance * tPostDistance))
			{
				continue;
			}
			if (type == 0)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
			else if (type == 1)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else if (type == 2)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C, bUDPSend);
			}
		}
		return;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (mAVATAR_OBJECT[index01].mCheckValidState)
		{
			if (type == 0)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
			else if (type == 1)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else if (type == 2)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal_C[0], mTRANSFER.mOriginalSize_C, bUDPSend);
			}
		}
	}
}
// BROADCAST
void MyUtil::Broadcast(BOOL tCheckInRange, float tPostLocation[3], int iScale, int tUserIndexForNoSend, bool bUDPSend, int type)
{
	int index01;
	int tSpaceIndex[3];
	float tLocation[3];
	float tPostDistance = static_cast<float>(iScale) * MAX_RADIUS_FOR_NETWORK;

	if (tCheckInRange)
	{
		tSpaceIndex[0] = (int)(tPostLocation[0] / MAX_RADIUS_FOR_NETWORK);
		tSpaceIndex[1] = (int)(tPostLocation[1] / MAX_RADIUS_FOR_NETWORK);
		tSpaceIndex[2] = (int)(tPostLocation[2] / MAX_RADIUS_FOR_NETWORK);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (index01 == tUserIndexForNoSend)
			{
				continue;
			}
			if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > iScale) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > iScale))
			{
				continue;
			}
			CopyMemory(&tLocation[0], &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 12);
			if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (tPostDistance * tPostDistance))
			{
				continue;
			}
			if (type)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
		}
		return;
	}
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (mAVATAR_OBJECT[index01].mCheckValidState)
		{
			if (type)
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize, bUDPSend);
			}
			else
			{
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal2[0], mTRANSFER.mOriginalSize2, bUDPSend);
			}
		}
	}
}
// RANDOM_NUMBER
float MyUtil::RandomNumber(float tMinValue, float tMaxValue)
{
	unsigned int tRandom = 0;
	tRandom = rand();
	return (tMinValue + (((tMaxValue - tMinValue) * (float)(tRandom % 10001)) / 10000.0f));
}
// RANDOM_NUMBER
int MyUtil::RandomNumber(void)
{
	unsigned int tRandom1 = 0;
	unsigned int tRandom2 = 0;
	tRandom1 = rand();
	tRandom2 = rand();
	return ((1 + (tRandom1 % 1000)) * (1 + (tRandom2 % 1000)));
}
// CHECK_IN_RANGE
BOOL MyUtil::CheckInRange(float tLocation01[3], float tLocation02[3], float tDistance)
{
	if (((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2])) > (tDistance * tDistance))
	{
		return FALSE;
	}
	return TRUE;
}
// GET_LENGTH_XYZ
float MyUtil::GetLengthXYZ(float tLocation01[3], float tLocation02[3])
{
	return sqrtf((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
// GET_DOUBLE_XYZ
float MyUtil::GetDoubleXYZ(float tLocation01[3], float tLocation02[3])
{
	return ((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[1] - tLocation02[1]) * (tLocation01[1] - tLocation02[1]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
// GET_LENGTH_X_Z
float MyUtil::GetLengthX_Z(float tLocation01[3], float tLocation02[3])
{
	return sqrtf((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
// GET_DOUBLE_X_Z
float MyUtil::GetDoubleX_Z(float tLocation01[3], float tLocation02[3])
{
	return ((tLocation01[0] - tLocation02[0]) * (tLocation01[0] - tLocation02[0]) + (tLocation01[2] - tLocation02[2]) * (tLocation01[2] - tLocation02[2]));
}
// GET_Y_ANGLE
float MyUtil::GetYAngle(float x1, float z1, float x2, float z2)
{
	if ((x1 == x2) && (z1 == z2))
	{
		return 0.0f;
	}

	float tVector[2];
	float tLength;
	float tAngle;
	float tDegreeAngle;

	tVector[0] = x2 - x1;
	tVector[1] = z2 - z1;
	tLength = sqrtf(tVector[0] * tVector[0] + tVector[1] * tVector[1]);
	if (tLength > 0.0f)
	{
		tVector[0] /= tLength;
		tVector[1] /= tLength;
	}
	tVector[1] -= 1.0f;
	tLength = sqrtf(tVector[0] * tVector[0] + tVector[1] * tVector[1]);
	if ((tLength / 2.0f) > 1.0f)
	{
		tAngle = 2.0f * asinf(1.0f);
	}
	else
	{
		tAngle = 2.0f * asinf(tLength / 2.0f);
	}
	if (x1 > x2)
	{
		tAngle = 2.0f * 3.14159265359f - tAngle;
	}
	tDegreeAngle = ((180.0f * tAngle) / 3.14159265359f) + 180.0f;
	if (tDegreeAngle >= 360.0f)
	{
		tDegreeAngle -= 360.0f;
	}
	return tDegreeAngle;
}
// RETURN_ITEM_RECOGNITION_NUMBER
int MyUtil::ReturnItemRecognitionNumber(int tItemType)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	if ((tItemType != 0) && (tItemType != 3) && (tItemType != 4))
	{
		return 0;
	}
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
	snprintf(tempString01, 1000, "%2.2d%2.2d%2.2d%2.2d", tPresentTime->tm_mday, tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_sec);
	return atoi(tempString01);
}
// RETURN_NOW_DATE
int MyUtil::ReturnNowDate(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
	snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);
	return atoi(tempString01);
}
// RETURN_ADD_DATE
int MyUtil::ReturnAddDate(int tPostDateValue, int tAddDayValue)
{
	if (tAddDayValue < 0)
	{
		return -1;
	}

	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];
	int tPresentDateValue;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);

	tPresentDateValue = atoi(tempString01);
	if (tPostDateValue > tPresentDateValue)
	{
		// tAddDayValue += ReturnSubDate( tPostDateValue, tCountSeconds );
		tAddDayValue += ReturnSubDate(tPostDateValue, tPresentDateValue);
	}
	time(&tCountSeconds);
	tCountSeconds += (tAddDayValue * 24 * 3600);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return -1;
	}

	snprintf(tempString01, 1000, "%4.4d%2.2d%2.2d", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1, tPresentTime->tm_mday);

	return atoi(tempString01);
}
// RETURN_SUB_DATE
int MyUtil::ReturnSubDate(int tPostDateValue, int tSubDayValue)
{
	if (tPostDateValue <= tSubDayValue)
	{
		return 0;
	}

#if 0
	struct tm time_str;
	time_t uPostDataValue;
	char tmpBuffer[8];
	char tempString01[1000];

	::snprintf(tempString01, 1000, "%s", tPostDateValue);
	memcpy(&tmpBuffer, &tempString01[0], 4);
	tmpBuffer[4] = '\0';
	time_str.tm_year = atoi(tmpBuffer) - 1900;
	memcpy(&tmpBuffer, &tempString01[4], 2);
	tmpBuffer[2] = '\0';
	time_str.tm_mon = atoi(tmpBuffer) - 1;
	tmpBuffer[2] = '\0';
	memcpy(&tmpBuffer, &tempString01[6], 2);
	time_str.tm_mday = atoi(tmpBuffer);
	time_str.tm_hour = 0;
	time_str.tm_min = 0;
	time_str.tm_sec = 0;

	if ((uPostDataValue = mktime(&time_str)) == -1) {
		return 0;
	}

	return ((uPostDataValue - tSubDayValue) / (24 * 3600)) + 1;
#endif
#if 1
	int index01;
	char tempString01[1000];
	char tempString02[1000];
	int tMonthDay[12];
	int tYear[2];
	int tMonth[2];
	int tDay[2];

	tMonthDay[0] = 31;
	tMonthDay[1] = 29;
	tMonthDay[2] = 31;
	tMonthDay[3] = 30;
	tMonthDay[4] = 31;
	tMonthDay[5] = 30;
	tMonthDay[6] = 31;
	tMonthDay[7] = 31;
	tMonthDay[8] = 30;
	tMonthDay[9] = 31;
	tMonthDay[10] = 30;
	tMonthDay[11] = 31;
#ifdef __WIN32__
	itoa(tPostDateValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tPostDateValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[0] = atoi(tempString02);
	if ((tYear[0] < 1) || (tYear[0] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[0] = atoi(tempString02);
	if ((tMonth[0] < 1) || (tMonth[0] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[0] = atoi(tempString02);
	if ((tDay[0] < 1) || (tDay[0] > 31))
	{
		return 0;
	}
	tDay[0] += (tYear[0] * 365);
	for (index01 = 0; index01 < (tMonth[0] - 1); index01++)
	{
		tDay[0] += tMonthDay[index01];
	}
#ifdef __WIN32__
	itoa(tSubDayValue, &tempString01[0], 10);
#else
	sprintf(&tempString01[0], "%d", tSubDayValue);
#endif
	CopyMemory(&tempString02[0], &tempString01[0], 4);
	tempString02[4] = '\0';
	tYear[1] = atoi(tempString02);
	if ((tYear[1] < 1) || (tYear[1] > 9000))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[4], 2);
	tempString02[2] = '\0';
	tMonth[1] = atoi(tempString02);
	if ((tMonth[1] < 1) || (tMonth[1] > 12))
	{
		return 0;
	}
	CopyMemory(&tempString02[0], &tempString01[6], 2);
	tempString02[2] = '\0';
	tDay[1] = atoi(tempString02);
	if ((tDay[1] < 1) || (tDay[1] > 31))
	{
		return 0;
	}
	tDay[1] += (tYear[1] * 365);
	for (index01 = 0; index01 < (tMonth[1] - 1); index01++)
	{
		tDay[1] += tMonthDay[index01];
	}
	return (tDay[0] - tDay[1]);
#endif
}
// RETURN_VOTE_DATE
int MyUtil::ReturnVoteDate(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	char tempString01[1000];
	char tempString02[1000];

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return 0;
	}
	snprintf(tempString01, 1000, "%4.4d%2.2d06", tPresentTime->tm_year + 1900, tPresentTime->tm_mon + 1);
	return atoi(tempString01);
}
// RETURN_I_S_VALUE
int MyUtil::ReturnISValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[0]);
}
// RETURN_RF_VALUE
int MyUtil::ReturnRFValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
// RETURN_4TH_VALUE
int MyUtil::Return4thValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[3]);
}
// RETURN_FIRST_STAT_VALUE
int MyUtil::ReturnFirstStatValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[0]);
}
// RETURN_FIRST_SECOND_VALUE
int MyUtil::ReturnSecondStatValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[1]);
}
// RETURN_FIRST_THIRD_VALUE
int MyUtil::ReturnThirdStatValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[2]);
}
// RETURN_CAPE_STAT_VALUE
int MyUtil::ReturnCapeStatValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[1]);
}
// RETURN_I_U_VALUE
int MyUtil::ReturnIUValue(int tValue)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[1]);
}
// CHANGE_I_S_VALUE
int MyUtil::ChangeISValue(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] += (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::SetISValue(int tValue, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_REFINE_VALUE
int MyUtil::ChangeRefineValue(int tValue, int tRFValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] += (char)tRFValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::Change4thValue(int tValue, int t4thValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[3] += (char)t4thValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_AMULET_FIRST_STAT
int MyUtil::ChangeAmuletFirstStat(int tValue, int tFirstStatValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[0] = (char)tFirstStatValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_AMULET_SECOND_STAT
int MyUtil::ChangeAmuletSecondStat(int tValue, int tSecondStatValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] = (char)tSecondStatValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_AMULET_THIRD_STAT
int MyUtil::ChangeAmuletThirdStat(int tValue, int tThirdStatValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[2] = (char)tThirdStatValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_CAPE_STAT
int MyUtil::ChangeCapeStat(int tValue, int tStat)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] = (char)tStat;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// CHANGE_I_U_VALUE
int MyUtil::ChangeIUValue(int tValue, int tIUValue)
{
	char tempValue01[4];
	int tResultIValue;

	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[1] += (char)tIUValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// SET_I_S_I_U_VALUE
int MyUtil::SetISIUValue(int tISValue, int tIUValue)
{
	char tempValue01[4];
	int tResultIValue;

	tempValue01[0] = (char)tISValue;
	tempValue01[1] = (char)tIUValue;
	tempValue01[2] = 0;
	tempValue01[3] = 0;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
// RETURN_I_U_EFFECT_VALUE
int MyUtil::ReturnIUEffectValue(ITEM_INFO* tITEM_INFO, int tEffectSort)
{
	switch (tEffectSort)
	{
	case 1: //[°ø°Ý·Â]
		switch (tITEM_INFO->iSort)
		{
		case 13: //[¹«±â]
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(14.34f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.72f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(14.34f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.72f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(14.34f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.72f);
			}
			break;
		}
		break;
	case 2: //[¹æ¾î·Â]
		switch (tITEM_INFO->iSort)
		{
		case 8: //[¸ÁÅä]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.10f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.10f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.10f);
			}
			break;
		case 9: //[º¹Àå]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(6.36f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.32f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(6.36f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.32f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(6.36f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.32f);
			}
			break;
		case 10: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(1.82f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.09f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(1.82f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.09f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(1.82f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.09f);
			}
			break;
		case 12: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(0.91f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(0.91f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(0.91f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.05f);
			}
			break;
		}
		break;
	case 3: //
		switch (tITEM_INFO->iSort)
		{
		case 10: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(13.36f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.67f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(13.36f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.67f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(13.36f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.67f);
			}
			break;
		case 13: //
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(5.73f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.29f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(5.73f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.29f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(5.73f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.29f);
			}
			break;
		}
		break;
	case 4: //
		switch (tITEM_INFO->iSort)
		{
		case 9: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(0.95f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(0.95f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.05f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(0.95f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.05f);
			}
			break;
		case 12: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.23f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.11f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.23f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.11f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.23f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.11f);
			}
			break;
		}
		break;
	case 5: //
		switch (tITEM_INFO->iSort)
		{
		case 11: //
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(2.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.26f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(2.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.26f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(2.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.26f);
			}
			break;
		}
		break;
	case 6: //[¼Ó¼º¹æ¾î]
		switch (tITEM_INFO->iSort)
		{
		case 7: //[¸ñ°ÉÀÌ]
			if (tITEM_INFO->iLevel < 100)
			{
				return (int)(1.00f + (0.00f + (float)(tITEM_INFO->iLevel - 45) * 0.10f) * 0.13f);
			}
			if (tITEM_INFO->iLevel < 113)
			{
				return (int)(1.00f + (6.00f + (float)(tITEM_INFO->iLevel - 100) * 0.20f) * 0.13f);
			}
			if (tITEM_INFO->iLevel < 146)
			{
				return (int)(1.00f + (8.00f + (float)(tITEM_INFO->iLevel - 113) * 0.50f) * 0.13f);
			}
			break;
		}
		break;
	}
	return 0;
}
// RETURN_IS_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnISValueWithLevelLimit(int tLevel, int tISValue)
{
#ifdef __GOD__
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
#else
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer))
#endif
	{
		if (tISValue < 50) // if (tISValue < 40)
		{
			return tISValue;
		}
		else
		{
			return 50;
		}
	}
	if (tLevel <= 15)
	{
		if (tISValue < 4)
		{
			return tISValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 45)
	{
		if (tISValue < 8)
		{
			return tISValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 55)
	{
		if (tISValue < 12)
		{
			return tISValue;
		}
		else
		{
			return 12;
		}
	}
	else if (tLevel <= 65)
	{
		if (tISValue < 16)
		{
			return tISValue;
		}
		else
		{
			return 16;
		}
	}
	else if (tLevel <= 75)
	{
		if (tISValue < 20)
		{
			return tISValue;
		}
		else
		{
			return 20;
		}
	}
	else if (tLevel <= 85)
	{
		if (tISValue < 24)
		{
			return tISValue;
		}
		else
		{
			return 24;
		}
	}
	else if (tLevel <= 95)
	{
		if (tISValue < 28)
		{
			return tISValue;
		}
		else
		{
			return 28;
		}
	}
	else if (tLevel <= 105)
	{
		if (tISValue < 32)
		{
			return tISValue;
		}
		else
		{
			return 32;
		}
	}
	else if (tLevel <= 112)
	{
		if (tISValue < 36)
		{
			return tISValue;
		}
		else
		{
			return 36;
		}
	}
	else
	{
		if (tISValue < 50) // if (tISValue < 40)
		{
			return tISValue;
		}
		else
		{
			return 50;
		}
	}
	return 0;
}
// RETURN_IU_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnIUValueWithLevelLimit(int tLevel, int tIUValue)
{
#ifdef __GOD__
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
#else
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer))
#endif
	{
		if (tIUValue < 12)
		{
			return tIUValue;
		}
		else
		{
			return 12;
		}
	}
	if (tLevel <= 15)
	{
		if (tIUValue < 1)
		{
			return tIUValue;
		}
		else
		{
			return 1;
		}
	}
	else if (tLevel <= 25)
	{
		if (tIUValue < 2)
		{
			return tIUValue;
		}
		else
		{
			return 2;
		}
	}
	else if (tLevel <= 35)
	{
		if (tIUValue < 3)
		{
			return tIUValue;
		}
		else
		{
			return 3;
		}
	}
	else if (tLevel <= 45)
	{
		if (tIUValue < 4)
		{
			return tIUValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 55)
	{
		if (tIUValue < 5)
		{
			return tIUValue;
		}
		else
		{
			return 5;
		}
	}
	else if (tLevel <= 65)
	{
		if (tIUValue < 6)
		{
			return tIUValue;
		}
		else
		{
			return 6;
		}
	}
	else if (tLevel <= 75)
	{
		if (tIUValue < 7)
		{
			return tIUValue;
		}
		else
		{
			return 7;
		}
	}
	else if (tLevel <= 85)
	{
		if (tIUValue < 8)
		{
			return tIUValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 95)
	{
		if (tIUValue < 9)
		{
			return tIUValue;
		}
		else
		{
			return 9;
		}
	}
	else if (tLevel <= 105)
	{
		if (tIUValue < 10)
		{
			return tIUValue;
		}
		else
		{
			return 10;
		}
	}
	else if (tLevel <= 112)
	{
		if (tIUValue < 11)
		{
			return tIUValue;
		}
		else
		{
			return 11;
		}
	}
	else
	{
		if (tIUValue < 12)
		{
			return tIUValue;
		}
		else
		{
			return 12;
		}
	}
	return 0;
}

#ifdef __GOD__
// RETURN_UPGRADE_VALUE_WITH_LEVEL_LIMIT
int MyUtil::ReturnUpgradeValueWithLevelLimit(int tLevel, int tUpgradeValue)
{
	if ((!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer) && (!mGAME.mCheckZone267TypeServer))
	{
		if (tUpgradeValue < 96)
		{
			return tUpgradeValue;
		}
		else
		{
			return 96;
		}
	}
	if (tLevel <= 19)
	{
		if (tUpgradeValue < 4)
		{
			return tUpgradeValue;
		}
		else
		{
			return 4;
		}
	}
	else if (tLevel <= 29)
	{
		if (tUpgradeValue < 8)
		{
			return tUpgradeValue;
		}
		else
		{
			return 8;
		}
	}
	else if (tLevel <= 39)
	{
		if (tUpgradeValue < 13)
		{
			return tUpgradeValue;
		}
		else
		{
			return 13;
		}
	}
	else if (tLevel <= 45)
	{
		if (tUpgradeValue < 17)
		{
			return tUpgradeValue;
		}
		else
		{
			return 17;
		}
	}
	else if (tLevel <= 55)
	{
		if (tUpgradeValue < 21)
		{
			return tUpgradeValue;
		}
		else
		{
			return 21;
		}
	}
	else if (tLevel <= 65)
	{
		if (tUpgradeValue < 25)
		{
			return tUpgradeValue;
		}
		else
		{
			return 25;
		}
	}
	else if (tLevel <= 75)
	{
		if (tUpgradeValue < 29)
		{
			return tUpgradeValue;
		}
		else
		{
			return 29;
		}
	}
	else if (tLevel <= 85)
	{
		if (tUpgradeValue < 33)
		{
			return tUpgradeValue;
		}
		else
		{
			return 33;
		}
	}
	else if (tLevel <= 95)
	{
		if (tUpgradeValue < 38)
		{
			return tUpgradeValue;
		}
		else
		{
			return 38;
		}
	}
	else if (tLevel <= 105)
	{
		if (tUpgradeValue < 42)
		{
			return tUpgradeValue;
		}
		else
		{
			return 42;
		}
	}
	else if (tLevel <= 112)
	{
		if (tUpgradeValue < 46)
		{
			return tUpgradeValue;
		}
		else
		{
			return 46;
		}
	}
	else if (tLevel <= 115)
	{
		if (tUpgradeValue < 50)
		{
			return tUpgradeValue;
		}
		else
		{
			return 50;
		}
	}
	else if (tLevel <= 118)
	{
		if (tUpgradeValue < 54)
		{
			return tUpgradeValue;
		}
		else
		{
			return 54;
		}
	}
	else if (tLevel <= 121)
	{
		if (tUpgradeValue < 58)
		{
			return tUpgradeValue;
		}
		else
		{
			return 58;
		}
	}
	else if (tLevel <= 124)
	{
		if (tUpgradeValue < 63)
		{
			return tUpgradeValue;
		}
		else
		{
			return 63;
		}
	}
	else if (tLevel <= 127)
	{
		if (tUpgradeValue < 67)
		{
			return tUpgradeValue;
		}
		else
		{
			return 67;
		}
	}
	else if (tLevel <= 130)
	{
		if (tUpgradeValue < 71)
		{
			return tUpgradeValue;
		}
		else
		{
			return 71;
		}
	}
	else if (tLevel <= 133)
	{
		if (tUpgradeValue < 75)
		{
			return tUpgradeValue;
		}
		else
		{
			return 75;
		}
	}
	else if (tLevel <= 136)
	{
		if (tUpgradeValue < 79)
		{
			return tUpgradeValue;
		}
		else
		{
			return 79;
		}
	}
	else if (tLevel <= 139)
	{
		if (tUpgradeValue < 83)
		{
			return tUpgradeValue;
		}
		else
		{
			return 83;
		}
	}
	else if (tLevel <= 142)
	{
		if (tUpgradeValue < 88)
		{
			return tUpgradeValue;
		}
		else
		{
			return 88;
		}
	}
	else if (tLevel <= 145)
	{
		if (tUpgradeValue < 92)
		{
			return tUpgradeValue;
		}
		else
		{
			return 92;
		}
	}
	else
	{
		if (tUpgradeValue < 96)
		{
			return tUpgradeValue;
		}
		else
		{
			return 96;
		}
	}
	return 0;
}
#endif

// PROCESS_ITEM_FOR_KILL_OTHER_TRIBE
void MyUtil::ProcessForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber)
{
	if ((!mUSER[tUserIndex].mCheckValidState) || (!mUSER[tOtherIndex].mCheckValidState))
	{
		return;
	}

	int tGainGeneralExperience;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (mGAME.mCheckZone049TypeServer)
	{
		mGAME.mZone049TypeBattleResult[mMyTribe]++;
	}
	if (mGAME.mCheckZone194Server)
	{
		mGAME.mZone194BattleResult[mMyTribe]++;
	}
	if (mGAME.mCheckZone267TypeServer)
	{
		mGAME.mZone267TypeBattleResult[mMyTribe]++;
	}
	if ( (mLevel1 + mLevel2) - (mUSER[tOtherIndex].mAvatarInfo.aLevel1 + mUSER[tOtherIndex].mAvatarInfo.aLevel2) > 9 )
	{
		return;
	}
	mPLAYUSER_COM.U_CHECK_KILL_OTHER_TRIBE_SEND(&mUSER[tUserIndex].mAvatarInfo.aName[0], &mUSER[tOtherIndex].mAvatarInfo.aName[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		return;
	}
	// Drop, CP Only on War Grounds
	if ( mGAME.mCheckZone049TypeServer || mGAME.mCheckZone053TypeServer || mGAME.mCheckZone194Server || mGAME.mWorldInfo.mTribeSymbolBattle == 1 || mGAME.mCheckZone195TypeServer )
	{
		DropItemForKillOtherTribe(tUserIndex, tOtherIndex, tZoneNumber);
		if ( mDoubleCPKill > 0 )
		{
			mCP += ( 1 + mGAME.mKillOtherTribeAddValue ) * 2;
			mCharCP += ( 1 + mGAME.mKillOtherTribeAddValue ) * 2;
			mDoubleCPKill--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(4, mDoubleCPKill);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		else
		{
			mCP += (1 + mGAME.mKillOtherTribeAddValue);
			mCharCP += (1 + mGAME.mKillOtherTribeAddValue);
		}
		if ( mUSER[tUserIndex].mAvatarInfo.aTimeEffect == 4 )
		{
			mCP += 1;
			mCharCP += 1;
		}
		switch (mGAME.TowerSystemEffect(2, mUSER[tUserIndex].mAvatarInfo.aTribe))
		{
		case 3:
			mCP += 1;
			mCharCP += 1;
			break;
		case 4:
			mCP += 2;
			mCharCP += 2;
			break;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mCP);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Hero Point Ranking
		mPLAYUSER_COM.U_CHANGE_HERO_RANK_INFO_SEND(4, mMyName, 1, mMyTribe);

		// PK Points
		/*mPKPoint += 1;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(121, mPKPoint);
		mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);*/

		// Daily PVP Kill
		if ( mDailyPVP < 10 )
		{
			mDailyPVP += 1;
		}

		// Mount Exp
		if (mUTIL.ReturnMountSort(mCharAnimal) != 30)
		{
			if (mAnimalIndex >= 10 && mAnimalIndex < 20)
			{
				mAnimalExp[mAnimalIndex - 10] = ProcessForMountExp(mAnimalExp[mAnimalIndex - 10], 5);
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(71, mAnimalExp[mAnimalIndex - 10]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
	}
	// HSB Ranking Point
	/*if ( mGAME.mWorldInfo.mTribeSymbolBattle == 1 )
	{
		if ( mHSBRank + 10 > 3000 )
		{
			mHSBRank = 3000 - mHSBRank;
			mCharHSBRank = 3000 - mHSBRank;
		}
		else
		{
			mHSBRank += 10;
			mCharHSBRank += 10;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(66, mHSBRank);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		if ( mHSBRank == 3000 )
		{
			CopyMemory(&tData[0], &mMyTribe, 4);
			CopyMemory(&tData[4], &mMyName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(671, &tData[0]);
		}
	}*/
	// PVP Exp
	tGainGeneralExperience = mLEVEL.ReturnGainExpForKillOtherTribe(mLevel1, mUSER[tOtherIndex].mAvatarInfo.aLevel1);
	if ( mGAME.mCheckZone049TypeServer || mGAME.mCheckZone051TypeServer || mGAME.mCheckZone053TypeServer )
	{
		tGainGeneralExperience *= 3;
		if ( mDoubleExpKill > 0 )
		{
			mDoubleExpKill -= 1;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(5, mDoubleExpKill);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			tGainGeneralExperience *= 2;
		}
	}
	ProcessForExperience(tUserIndex, tGainGeneralExperience, 0, 0);
}

void MyUtil::DropItemForSpecialZonesKillOtherInWar(int tUserIndex, int tOtherIndex, int tZoneNumber)
{
	// Verifică dacă starea utilizatorilor este validă pentru a continua procesul
	if ((!mUSER[tUserIndex].mCheckValidState) || (!mUSER[tOtherIndex].mCheckValidState))
	{
		return;  // Dacă unul dintre utilizatori nu este într-o stare validă, ieși din funcție
	}

	// Variabile pentru itemele ce pot fi dropate
	ITEM_INFO* tITEM_INFO;
	int tItemLLevel;   // Nivelul minim al itemului
	int tItemHLevel;   // Nivelul maxim al itemului
	int tTribeItemList[9];  // Lista de iteme ale tribului
	int tRandomValue;  // Valoare aleatorie folosită pentru dropuri
	int tItemType;     // Tipul itemului
	int tItemSort;     // Sortarea itemului
	int tSearchNum;    // Numărul de căutări
	int tRNG;          // Variabila pentru generarea valorilor aleatorii
	std::vector<int> tDrop;  // Vector pentru itemele dropate
	int tValue = 0;    // Valoarea totală calculată pentru dropuri
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	// Dacă diferența de nivel între utilizatorul curent și celălalt este mai mare de 9, nu se întâmplă nimic
	if ((mLevel1 + mLevel2) - (mUSER[tOtherIndex].mAvatarInfo.aLevel1 + mUSER[tOtherIndex].mAvatarInfo.aLevel2) > 9)
	{
		return;  // Dacă diferența de nivel este prea mare, nu se mai face nimic și ieșim din funcție
	}

	// Trimite un mesaj către server pentru a semnala uciderea unui alt trib
	mPLAYUSER_COM.U_CHECK_KILL_OTHER_TRIBE_SEND(&mUSER[tUserIndex].mAvatarInfo.aName[0], &mUSER[tOtherIndex].mAvatarInfo.aName[0]);

	// Verifică rezultatul primit de la server (dacă nu este 0, înseamnă că a apărut o problemă)
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		return;  // Dacă rezultatul nu este 0, înseamnă că a apărut o eroare și ieșim din funcție
	}

	// Dacă suntem într-o zonă de război (Zone 295, Zone 296, sau simbolul de război al tribului este activ), se vor dropa iteme speciale
	if (mGAME.mCheckZone295TypeServer || mGAME.mCheckZone296TypeServer || mGAME.mWorldInfo.mTribeSymbolBattle == 1 || mGAME.mCheckZone195TypeServer)
	{
		// Apelarea funcției pentru a dropa iteme în zonele speciale
		DropItemForSpecialZonesKillOtherInWar(tUserIndex, tOtherIndex, tZoneNumber);

	}
}

// DROP_ITEM_FOR_KILL_OTHER_TRIBE
void MyUtil::DropItemForKillOtherTribe(int tUserIndex, int tOtherIndex, int tZoneNumber)
{
	ITEM_INFO* tITEM_INFO;
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	int tRNG;
	std::vector<int> tDrop;
	int tValue = 0;

	// Drop Labyrinth Key
	tRNG = rand() % 100;
	if (tRNG == 0)
	{
		ProcessForDropItem(2, 1048, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
	}

	// Drop Taiyan Key
	tRNG = rand() % 100;
	if (tRNG == 0)
	{
		ProcessForDropItem(2, 1049, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
	}

	// Drop Item For Kill Other Tribe
	tRNG = rand() % 20;
	if (tRNG == 0)
	{
		tDrop.clear();
		tDrop = { 0 };
		ProcessForDropItem(2, tDrop[rand() % tDrop.size()], 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
	}

	// Dacă suntem într-o zonă de război (Zone 295, Zone 296, sau simbolul de război al tribului este activ), se vor dropa iteme speciale
	if (mGAME.mCheckZone295TypeServer || mGAME.mCheckZone296TypeServer || mGAME.mWorldInfo.mTribeSymbolBattle == 1 || mGAME.mCheckZone195TypeServer)
	{
		// Apelarea funcției pentru a dropa iteme în zonele speciale
		DropItemForSpecialZonesKillOtherInWar(tUserIndex, tOtherIndex, tZoneNumber);
	}

	{
		// Drop pentru item Fahreinth Jade- 1% șansă (număr aleator între 0 și 99, dacă este mai mic decât 1, se va dropa)
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 1) // 1% șansă
		{
			ProcessForDropItem(2, 2150, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1313 - 5% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 5) // 5% șansă
		{
			ProcessForDropItem(2, 1237, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1314 - 10% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 10) // 10% șansă
		{
			ProcessForDropItem(2, 1102, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1315 - 15% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 15) // 15% șansă
		{
			ProcessForDropItem(2, 1130, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1316 - 20% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 20) // 20% șansă
		{
			ProcessForDropItem(2, 1118, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1317 - 30% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 30) // 30% șansă
		{
			ProcessForDropItem(2, 1119, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1318 - 40% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 40) // 40% șansă
		{
			ProcessForDropItem(2, 1124, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item 1319 - 50% șansă
		tRNG = rand() % 100; // Generăm un număr între 0 și 99
		if (tRNG < 50) // 50% șansă
		{
			ProcessForDropItem(2, 1108, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
				&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}

		// Drop pentru item PVP Box - 100% șansă
		ProcessForDropItem(2, 716, 0, 0, 0, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0],
			&mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);

	}

	/*
		// Drop Equipment For Kill Other Tribe
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tRandomValue = (rand() % 10000);
		if (tRandomValue < 1)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 100)
		{
			tItemType = 3;
		}
		else
		{
			tItemType = 2;
		}
		tRNG = rand();
		tItemSort = tTribeItemList[(tRNG % 9)];
		tSearchNum = 0;

		while (tSearchNum < 10)
		{
			tRNG = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRNG % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
			if (tITEM_INFO)
			{

				if (((tITEM_INFO->iEquipInfo[0] == 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)) && (tITEM_INFO->iCheckMonsterDrop == 2))
				{
					break;
				}
				tITEM_INFO = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO == NULL)
		{
			return;
		}
		if (!ProcessForDropItem(2, tITEM_INFO->iIndex, 0, 0, 100000004, &mAVATAR_OBJECT[tOtherIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return;
		}
		if (tITEM_INFO->iType == 4)
		{
			mGAMELOG.GL_607_GAIN_SIN_ITEM(tUserIndex, 5, tITEM_INFO->iIndex, 0, 0, 100000004);
		}*/
}
// mGAMELOG
int MyUtil::SearchAvatar(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tInvalidIndex)
{
	int index01;

	// Parcurgem toți utilizatorii disponibili în server (de la 0 până la maximul permis)
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		// Dacă avatarul de la acest index nu este valid, sărim peste el
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}

		// Dacă indexul curent este cel invalid (de evitat), sărim peste el
		if (index01 == tInvalidIndex)
		{
			continue;
		}

		// Comparăm numele avatarului curent cu numele căutat
		if (strcmp(mAVATAR_OBJECT[index01].mDATA.aName, tAvatarName) == 0)
		{
			// Dacă găsim o potrivire, oprim căutarea
			break;
		}
	}

	// Dacă am găsit un index valid înainte de a ajunge la limita maximă, îl returnăm
	if (index01 < mSERVER.mMAX_USER_NUM)
	{
		return index01;
	}

	// Dacă nu am găsit avatarul, returnăm -1
	return -1;
}
// # Defense Hack # {
bool MyUtil::CheckInvenForItem(int* tUserIndex, ITEM_INFO* pItem, int* tPage, int* tIndex, int* tXPost, int* tYPost)
{
	int iCount = 0;
	int iOccupyRange = 1;
	ITEM_INFO* tItemInfo = NULL;

	if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
	{
		iOccupyRange = 2;
	}

	for (iCount = 0; iCount < MAX_INVENTORY_SLOT_NUM; iCount++)
	{
		if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost - 1) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1))))
		{
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL)
			{
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
			{
				return false;
			}
		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1))))
		{
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL)
			{
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
			{
				return false;
			}
		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost - 1))))
		{
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL)
			{
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
			{
				return false;
			}
		}
		else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost - 1) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost))))
		{
			if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] < 1)
				continue;
			tItemInfo = mITEM.Search(mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0]);
			if (tItemInfo == NULL)
			{
				mUSER[*tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return false;
			}
			if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
			{
				return false;
			}
		}

		if (iOccupyRange == 2)
		{
			if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost))))
			{
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0)
				{
					return false;
				}
			}
			else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost + 1))))
			{
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0)
				{
					return false;
				}
			}
			else if ((mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][1] == (*tXPost + 1) && (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][2] == (*tYPost + 1))))
			{
				if (mUSER[*tUserIndex].mAvatarInfo.aInventory[*tPage][*tIndex][0] > 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}
// # }
bool MyUtil::FindEmptyInvenForItem(int iUserIndex, ITEM_INFO* pItem, int& iPage, int& iIndex) // For getting tXPost, tYPost Inventory
{
	bool bResult = true;
	int iMaxPage = 1, iRange = 8, iOccupyRange = 1;
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	if (pAvatar->aExpandInventoryDate >= mUTIL.ReturnNowDate())
		iMaxPage = 2;

	if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
	{
		iRange = 7;
		iOccupyRange = 2;
	}

	bool bInvenSlots[MAX_INVENTORY_SLOT_NUM];

	for (int i = 0; i < iMaxPage; i++)
	{
		SetInvenSlotHumanReadable(iUserIndex, i, bInvenSlots);
		for (int j = 0; j < iRange; j++)
		{
			for (int k = 0; k < iRange; k++)
			{
				if (bInvenSlots[j * 8 + k] == false)
				{
					// .. .. .. ....
					bResult = true;
					for (int m = 0; m < iOccupyRange; m++)
					{
						for (int n = 0; n < iOccupyRange; n++)
						{
							int iPlus = j * 8 + k + m * 8 + n;
							if (bInvenSlots[iPlus] == true)
							{
								bResult = false;
								break;
							}
						}

						if (bResult == false)
							break;
					}

					if (bResult == true)
					{
						iPage = i;
						iIndex = j * 8 + k;
						return true;
					}
				}
			}
		}
	}

	return false;
}

bool MyUtil::SetInvenSlotHumanReadable(int iUserIndex, int iPage, bool bInvenSlots[MAX_INVENTORY_SLOT_NUM])
{
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	for (int i = 0; i < MAX_INVENTORY_SLOT_NUM; i++)
		bInvenSlots[i] = false;

	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (pAvatar->aInventory[iPage][i * 8 + j][0] > 0)
			{
				int iItemIndex = pAvatar->aInventory[iPage][i * 8 + j][0];
				ITEM_INFO* pItem = mITEM.Search(iItemIndex);
				if (pItem != NULL)
				{
					int iX = pAvatar->aInventory[iPage][i * 8 + j][1];
					int iY = pAvatar->aInventory[iPage][i * 8 + j][2];
					// .. 1 X 1 ... ..... ... 1.. ...
					bInvenSlots[iY * 8 + iX] = true;

					if (pItem->iSort != 2 && pItem->iSort != 7 && pItem->iSort != 11)
					{
						if (iX < 7)
						{
							bInvenSlots[iY * 8 + iX + 1] = true;
						}

						if (iY < 7)
						{
							bInvenSlots[(iY + 1) * 8 + iX] = true;

							if (iX < 7)
							{
								bInvenSlots[(iY + 1) * 8 + iX + 1] = true;
							}
						}
					}
				}
			}
		}
	}

	return true;
}

int MyUtil::GetEmptyInvenSlotIndex(int iUserIndex, int iPage) // For getting [x][tIndex][0] bag
{
	AVATAR_INFO* pAvatar = &mUSER[iUserIndex].mAvatarInfo;

	if (pAvatar == NULL)
		return -1;

	for (int i = 0; i < MAX_INVENTORY_SLOT_NUM; i++)
	{
		if (pAvatar->aInventory[iPage][i][0] < 1)
			return i;
	}

	return -1;
}

BOOL MyUtil::CheckIfEmptyHPPills(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < MAX_HOT_KEY_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aHotKey[i][j][0]);
			if ((pItem != NULL) && (pAvatar->aHotKey[i][j][2] == 3) && (((pItem->iPotionType[0] == 1) || (pItem->iPotionType[0] == 2) || (pItem->iPotionType[0] == 5))))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL MyUtil::CheckIfEmptyMPPills(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < MAX_HOT_KEY_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aHotKey[i][j][0]);
			if ((pItem != NULL) && (pAvatar->aHotKey[i][j][2] == 3) && (((pItem->iPotionType[0] == 3) || (pItem->iPotionType[0] == 4) || (pItem->iPotionType[0] == 5))))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}

BOOL MyUtil::GetEmptyHotKeyPage(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < MAX_HOT_KEY_NUM; j++)
		{
			if (pAvatar->aHotKey[i][j][0] < 1)
			{
				return i;
			}
		}
	}
	return -1;
}

BOOL MyUtil::GetEmptyHotKeyIndex(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < MAX_HOT_KEY_NUM; j++)
		{
			if (pAvatar->aHotKey[i][j][0] < 1)
			{
				return j;
			}
		}
	}
	return -1;
}
int MyUtil::GetInventoryHPPillPage(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 1) || (pItem->iPotionType[0] == 2) || (pItem->iPotionType[0] == 5))
			{
				return i;
			}
		}
	}
	return -1;
}

int MyUtil::GetInventoryHPPillIndex(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 1) || (pItem->iPotionType[0] == 2) || (pItem->iPotionType[0] == 5))
			{
				return j;
			}
		}
	}
	return -1;
}
int MyUtil::GetInventoryMPPillPage(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 3) || (pItem->iPotionType[0] == 4) || (pItem->iPotionType[0] == 5))
			{
				return i;
			}
		}
	}
	return -1;
}

int MyUtil::GetInventoryMPPillIndex(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 3) || (pItem->iPotionType[0] == 4) || (pItem->iPotionType[0] == 5))
			{
				return j;
			}
		}
	}
	return -1;
}

int MyUtil::GetInventoryHPPillQuantity(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 1) || (pItem->iPotionType[0] == 2) || (pItem->iPotionType[0] == 5))
			{
				return pAvatar->aInventory[i][j][3];
			}
		}
	}
	return -1;
}
int MyUtil::GetInventoryMPPillQuantity(int tUserIndex)
{
	AVATAR_INFO* pAvatar = &mUSER[tUserIndex].mAvatarInfo;
	ITEM_INFO* pItem;

	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < MAX_INVENTORY_SLOT_NUM; j++)
		{
			pItem = mITEM.Search(pAvatar->aInventory[i][j][0]);
			if (pItem == NULL)
			{
				continue;
			}
			if ((pItem->iPotionType[0] == 3) || (pItem->iPotionType[0] == 4) || (pItem->iPotionType[0] == 5))
			{
				return pAvatar->aInventory[i][j][3];
			}
		}
	}
	return -1;
}

int MyUtil::ReturnHealthState(int tPlayTime)
{
	if (tPlayTime <= 60)
	{
		return 1;
	}
	if (tPlayTime <= 120)
	{
		return 2;
	}
	if (tPlayTime <= 180)
	{
		return 3;
	}
	if (tPlayTime <= 299)
	{
		return 4;
	}
	return 5;
}
// PROCESS_FOR_CHANGE
BOOL MyUtil::ProcessForChange(int tUserIndex)
{
	int tRandomNumber;
	int tSort;
	ITEM_INFO* tITEM_INFO;
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tItemType;
	int tItemSort;
	int tSearchNum;

	tRandomNumber = rand() % 10000;
	if (tRandomNumber < 3000)
	{
		tSort = 1;
	}
	else if (tRandomNumber < 5000)
	{
		tSort = 2;
	}
	else if (tRandomNumber < 6000)
	{
		tSort = 3;
	}
	else if (tRandomNumber < 6400)
	{
		tSort = 4;
	}
	else if (tRandomNumber < 6500)
	{
		tSort = 5;
	}
	else if (tRandomNumber < 6600)
	{
		tSort = 6;
	}
	else if (tRandomNumber < 6700)
	{
		tSort = 7;
	}
	else if (tRandomNumber < 6800)
	{
		tSort = 8;
	}
	else if (tRandomNumber < 9999)
	{
		tSort = 9;
		tItemType = 3;
	}
	else
	{
		tSort = 9;
		tItemType = 4;
	}
	switch (tSort)
	{
	case 1:
		tITEM_INFO = mITEM.Search(1022);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 2:
		tITEM_INFO = mITEM.Search(1023);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 3:
		tITEM_INFO = mITEM.Search(1037);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 4:
		tITEM_INFO = mITEM.Search(1041);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 5:
		tITEM_INFO = mITEM.Search(1017);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 6:
		tITEM_INFO = mITEM.Search(1018);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 7:
		tITEM_INFO = mITEM.Search(1092);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 8:
		tITEM_INFO = mITEM.Search(1093);
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	case 9:
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 - 5;
			if (tItemLLevel < 1)
			{
				tItemLLevel = 1;
			}
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + 5;
			if (tItemHLevel > MAX_LIMIT_LEVEL_NUM)
			{
				tItemHLevel = MAX_LIMIT_LEVEL_NUM;
			}
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 13;
			tTribeItemList[7] = 14;
			tTribeItemList[8] = 15;
			break;
		case 1:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 16;
			tTribeItemList[7] = 17;
			tTribeItemList[8] = 18;
			break;
		case 2:
			tTribeItemList[0] = 7;
			tTribeItemList[1] = 8;
			tTribeItemList[2] = 9;
			tTribeItemList[3] = 10;
			tTribeItemList[4] = 11;
			tTribeItemList[5] = 12;
			tTribeItemList[6] = 19;
			tTribeItemList[7] = 20;
			tTribeItemList[8] = 21;
			break;
		}
		tItemSort = tTribeItemList[(rand() % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tITEM_INFO = mITEM.Return((tItemLLevel + (rand() % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
			if (tITEM_INFO)
			{
				if (((tITEM_INFO->iEquipInfo[0] == 1) || ((tITEM_INFO->iEquipInfo[0] - 2) == mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)) && (tITEM_INFO->iCheckMonsterDrop == 2))
				{
					break;
				}
				tITEM_INFO = NULL;
				tSearchNum++;
			}
			else
			{
				tSearchNum++;
			}
		}
		if (tITEM_INFO == NULL)
		{
			return FALSE;
		}
		if (!ProcessForDropItem(12, tITEM_INFO->iIndex, 0, 0, ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			return FALSE;
		}
		// mGAMELOG.GL_647_KILLOTHERTRIBE_TO_ITEM( tUserIndex, tITEM_INFO->iIndex );
		return TRUE;
	}
	return FALSE;
}
#ifdef __GOD__
// CHECK_CHANGE_TRIBE_TIME
BOOL MyUtil::CheckChangeTribeTime(void)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return FALSE;
	}
	if (tPresentTime->tm_wday != 6)
	{
		return FALSE;
	}
	if (tPresentTime->tm_hour < 12)
	{
		return FALSE;
	}
	return TRUE;
}
#endif
// # Defense Hack # {
int MyUtil::GetAttackRadius(int tSkillNumber)
{
	switch (tSkillNumber)
	{
	case 1:
		return 25;
	case 2:
		return 25;
	case 3:
		return 25;
	case 4:
		return 15;
	case 5:
		return 15;
	case 6:
		return 0;
	case 7:
		return 0;
	case 8:
		return 20;
	case 9:
		return 20;
	case 10:
		return 45;
	case 11:
		return 0;
	case 12:
		return 25;
	case 13:
		return 25;
	case 14:
		return 50;
	case 15:
		return 0;
	case 16:
		return 120;
	case 17:
		return 120;
	case 18:
		return 45;
	case 19:
		return 0;
	case 20:
		return 0;
	case 21:
		return 0;
	case 22:
		return 0;
	case 23:
		return 15;
	case 24:
		return 15;
	case 25:
		return 0;
	case 26:
		return 0;
	case 27:
		return 25;
	case 28:
		return 25;
	case 29:
		return 50;
	case 30:
		return 0;
	case 31:
		return 15;
	case 32:
		return 15;
	case 33:
		return 45;
	case 34:
		return 0;
	case 35:
		return 120;
	case 36:
		return 120;
	case 37:
		return 45;
	case 38:
		return 0;
	case 39:
		return 0;
	case 40:
		return 0;
	case 41:
		return 0;
	case 42:
		return 15;
	case 43:
		return 15;
	case 44:
		return 0;
	case 45:
		return 0;
	case 46:
		return 20;
	case 47:
		return 20;
	case 48:
		return 45;
	case 49:
		return 0;
	case 50:
		return 25;
	case 51:
		return 25;
	case 52:
		return 50;
	case 53:
		return 0;
	case 54:
		return 120;
	case 55:
		return 120;
	case 56:
		return 45;
	case 57:
		return 0;
	case 58:
		return 20;
	case 59:
		return 20;
	case 60:
		return 25;
	case 61:
		return 25;
	case 62:
		return 120;
	case 63:
		return 120;
	case 64:
		return 25;
	case 65:
		return 25;
	case 66:
		return 15;
	case 67:
		return 15;
	case 68:
		return 120;
	case 69:
		return 120;
	case 70:
		return 20;
	case 71:
		return 20;
	case 72:
		return 25;
	case 73:
		return 25;
	case 74:
		return 120;
	case 75:
		return 120;
	case 76:
		return 30;
	case 77:
		return 30;
	case 78:
		return 30;
	case 79:
		return 30;
	case 80:
		return 150;
	case 81:
		return 30;
	case 82:
		return 0;
	case 83:
		return 0;
	case 84:
		return 0;
	case 85:
		return 20;
	case 86:
		return 20;
	case 87:
		return 25;
	case 88:
		return 25;
	case 89:
		return 120;
	case 90:
		return 120;
	case 91:
		return 25;
	case 92:
		return 25;
	case 93:
		return 15;
	case 94:
		return 15;
	case 95:
		return 120;
	case 96:
		return 120;
	case 97:
		return 20;
	case 98:
		return 20;
	case 99:
		return 25;
	case 100:
		return 25;
	case 101:
		return 120;
	case 102:
		return 120;
	case 103:
		return 0;
	case 104:
		return 0;
	case 105:
		return 0;
	case 106:
		return 300;
	case 107:
		return 300;
	case 108:
		return 300;
	case 109:
		return 300;
	case 110:
		return 300;
	case 111:
		return 300;
	case 112:
		return 70;
	case 113:
		return 70;
	case 114:
		return 70;
	case 115:
		return 70;
	case 116:
		return 70;
	case 117:
		return 70;
	case 118:
		return 70;
	case 119:
		return 70;
	case 120:
		return 70;
#ifdef __GOD__
	case 121:
		return 20;
	case 122:
		return 20;
	case 123:
		return 25;
	case 124:
		return 25;
	case 125:
		return 120;
	case 126:
		return 120;
	case 127:
		return 25;
	case 128:
		return 25;
	case 129:
		return 15;
	case 130:
		return 15;
	case 131:
		return 120;
	case 132:
		return 120;
	case 133:
		return 20;
	case 134:
		return 20;
	case 135:
		return 25;
	case 136:
		return 25;
	case 137:
		return 120;
	case 138:
		return 120;
#endif
	}
	return 0;
}

float MyUtil::ReturnLengthXYZ(float tLocation01[3], float tLocation02[3])
{
	return ::sqrtf(::powf((tLocation01[0] - tLocation02[0]), 2) + ::powf((tLocation01[1] - tLocation02[1]), 2) + ::powf((tLocation01[2] - tLocation02[2]), 2));
}

bool MyUtil::CheckRAttackRange(int tUserIndex, int tSkillNumber, float tLocation1[3], float tLocation2[3], float tObjectSize)
{
	int iTemp = 0;
	float fTemp = 0.0f;
	fTemp = ReturnLengthXYZ(&tLocation1[0], &tLocation2[0]);
	// iTemp = GetAttackRadius(tSkillNumber) + 40;

	// iTemp = GetAttackRadius(tSkillNumber) + tObjectSize + 40;
	// LOG_TO_FILE_2("GetAttackRadius : %d, %d\n", GetAttackRadius(tSkillNumber), tObjectSize);

	// # Defense Hack Add02 #
#if 0
	if (tObjectSize < 20.0f) {
		tObjectSize = 20.0f;
	}
#endif
	iTemp = GetAttackRadius(tSkillNumber) + (int)(ceilf(tObjectSize));

	if ((int)fTemp <= iTemp)
	{
		return true;
	}
	return false;
}

int MyUtil::CheckPVNumber(int tTribe)
{
	int a = 0;

	if (mGAME.mWorldInfo.mProvingGroundsState[0] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[1] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[2] == (tTribe + 1))
	{
		a++;
	}
	if (mGAME.mWorldInfo.mProvingGroundsState[3] == (tTribe + 1))
	{
		a++;
	}

	return a;
}

int MyUtil::GetRandomGachaItem()
{
	int tRandom;
	tRandom = rand() % 9;
	switch (tRandom)
	{
	case 0:
		return 1023; // 15% Mats
	case 1:
		return 1018; // Chi Elixir
	case 2:
		return 1092; // Strength Elixir
	case 3:
		return 1017; // Health Elixir
	case 4:
		return 1022; // 12% Mats
	case 5:
		return 1103; // Protection Charm
	case 6:
		return 692; // CP Ticket (10)
	case 7:
		return 695; // White Feather
	case 8:
		return 1021; // 9% Mats
	}
}
int MyUtil::ReturnAmuletStats2(int tUserIndex, int AmuletStats, int WhatSkill)
{
	ITEM_INFO* tITEM_INFO;
	int AmuletPetStats;
	int AmuletPetStats2;
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]);
	if (tITEM_INFO == NULL)
	{
		return 0;
	}
	if (tITEM_INFO->iSort != 28)
	{
		return 0;
	}
	if ((tITEM_INFO->iIndex == 2253) || (tITEM_INFO->iIndex == 2254))
	{
		return 0;
	}
	if ((tITEM_INFO->iIndex == 2261) || (tITEM_INFO->iIndex == 2262) || (tITEM_INFO->iIndex == 2300) || (tITEM_INFO->iIndex == 2301))
	{
		return 0;
	}
	AmuletPetStats = mUTIL.ReturnSecondStatValue(AmuletStats);
	if (AmuletPetStats < 10)
	{
		return 0;
	}
	if (AmuletPetStats / 10 == WhatSkill)
	{
		return AmuletPetStats % 10;
	}
	return 0;
}
double MyUtil::ReturnPetAddSkillPoint2(int Mode1, int Mode2, int tPetIndex, int tPetGrowState)
{
	double result;	  // st7
	int v5;			  // [esp+14h] [ebp-14h]
	int tLegendState; // [esp+18h] [ebp-10h]
	int v7;			  // [esp+1Ch] [ebp-Ch]
	int v8;			  // [esp+20h] [ebp-8h]
	int v9;			  // [esp+24h] [ebp-4h]

	tLegendState = ReturnItemSort(tPetIndex);
	if (tLegendState != 5 && tLegendState != 6)
		return 0.0;
	switch (Mode1)
	{
	case 1:
		v9 = ReturnISValue(tPetGrowState);
		if (Mode2 == 1)
		{
			switch (v9)
			{
			case 1:
				return 1.0;
			case 2:
				return 2.0;
			case 3:
				return 3.0;
			}
			return 0.0;
		}
		return 0.0;
	case 2:
		v5 = ReturnIUValue(tPetGrowState);
		if (Mode2 != 2)
		{
			return 0.0;
		}
		switch (v5)
		{
		case 11:
			result = 1.0;
			break;
		case 12:
			result = 2.0;
			break;
		case 13:
			result = 3.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 3:
		v8 = ReturnRFValue(tPetGrowState);
		if (Mode2 != 3)
		{
			return 0.0;
		}
		switch (v8)
		{
		case 21:
			result = 1.0;
			break;
		case 22:
			result = 2.0;
			break;
		case 23:
			result = 3.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	case 4:
		v7 = Return4thValue(tPetGrowState);
		if (Mode2 != 3)
		{
			return 0.0;
		}
		switch (v7)
		{
		case 31:
			result = 2.0;
			break;
		case 32:
			result = 4.0;
			break;
		case 33:
			result = 6.0;
			break;
		default:
			result = 0.0;
			break;
		}
		break;
	default:
		return 0.0;
	}
	return result;
}

int MyUtil::ReturnCapeAbility(int tCapeIndex, int tCapeImprove, int tMode)
{
	if (tCapeIndex == -1 || !tCapeIndex || !tCapeImprove)
		return 0.0f;

	ITEM_INFO* tITEM = mITEM.Search(tCapeIndex);
	if (!tITEM || tITEM->iSort != 29)
		return 0.0f;

	int tIUValue = mUTIL.ReturnIUValue(tCapeImprove);
	if (tIUValue < 10)
		return 0.0f;

	int v14 = tIUValue % 10;
	if (tIUValue / 10 != tMode)
		return 0.0f;

	switch (tMode)
	{
	case 1:
		return (float)(v14 + 1) * 50.0f;
	case 2:
		return (float)(v14 + 1) * 50.0f;
	case 3:
		return (float)(v14 + 1) * 200.0f;
	case 4:
		return (float)(v14 + 1) * 250.0f;
	case 5:
		return (float)(v14 + 1) * 100.0f;
	case 6:
		return (float)(v14 + 1) * 100.0f;
	case 7:
		return (float)(v14 + 1) * 0.5f;
	case 8:
		return (float)(v14 + 1) * 0.5f;
	default:
		return 0.0f;
	}
}
int MyUtil::SetSocketValue(int tValue, int WhatByte, int tISValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[WhatByte - 1] = (char)tISValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::ReturnMemoryValue(int tValue, int WhatByte)
{
	char tempValue01[4];

	CopyMemory(&tempValue01[0], &tValue, 4);
	return ((int)tempValue01[WhatByte - 1]);
}
int MyUtil::ChangeMemoryValue(int tValue, int WhatByte, int tNewValue)
{
	char tempValue01[4];
	int tResultIValue;
	CopyMemory(&tempValue01[0], &tValue, 4);
	tempValue01[WhatByte - 1] += (char)tNewValue;
	CopyMemory(&tResultIValue, &tempValue01[0], 4);
	return tResultIValue;
}
int MyUtil::ReturnMountAbsorbAddStat(int tAnimalNumber)
{
	switch (tAnimalNumber)
	{
	case 1301:
	case 1302:
	case 1303:
		return 30;
	case 559:
		return 20;
	case 814:
	case 815:
	case 816:
	case 817:
	case 818:
	case 819:
	case 820:
	case 821:
		return 10;
	default:
		if ((tAnimalNumber >= 2266 && tAnimalNumber <= 2285) ||
			(tAnimalNumber >= 2316 && tAnimalNumber <= 2317) ||
			(tAnimalNumber >= 2422 && tAnimalNumber <= 2441))
		{
			return 10;
		}
		if ((tAnimalNumber >= 19002 && tAnimalNumber <= 19021) ||
			(tAnimalNumber >= 19025 && tAnimalNumber <= 19044) ||
			(tAnimalNumber >= 19051 && tAnimalNumber <= 19070) ||
			(tAnimalNumber >= 19261 && tAnimalNumber <= 19280))
		{
			return 10;
		}
		if (tAnimalNumber >= 1917 && tAnimalNumber <= 1936)
		{
			return 10;
		}
		if (tAnimalNumber >= 1304 && tAnimalNumber <= 1331)
		{
			if (tAnimalNumber == 1304 || tAnimalNumber == 1305 || tAnimalNumber == 1306 ||
				tAnimalNumber == 1314 || tAnimalNumber == 1318 || tAnimalNumber == 1321 ||
				tAnimalNumber == 1324 || tAnimalNumber == 1327)
			{
				return 20;
			}
			if (tAnimalNumber == 1307 || tAnimalNumber == 1308 || tAnimalNumber == 1309 ||
				tAnimalNumber == 1315 || tAnimalNumber == 1319 || tAnimalNumber == 1322 ||
				tAnimalNumber == 1325 || tAnimalNumber == 1328)
			{
				return 10;
			}
			if (tAnimalNumber == 1313 || tAnimalNumber == 1317 || tAnimalNumber == 1320 ||
				tAnimalNumber == 1323 || tAnimalNumber == 1326)
			{
				return 30;
			}
			if (tAnimalNumber == 1329 || tAnimalNumber == 1330 || tAnimalNumber == 1331)
			{
				return 15;
			}
		}
		return 0;
	}
}
int MyUtil::SetEliteAnimalAbility(int tSort)
{
	int tAbilityValue = 0;
	int tStat1, tStat2, tStat3, tStat4;

	switch (tSort)
	{
	case 1: // Red Fox
		tStat1 = 21 + rand() % 9; // Damage
		tStat2 = 1 + rand() % 9; // HP
		tStat3 = 81 + rand() % 9; // Attr Damage
		tStat4 = 0;
		tAbilityValue = mUTIL.ChangeISValue(tAbilityValue, tStat1);
		tAbilityValue = mUTIL.ChangeIUValue(tAbilityValue, tStat2);
		tAbilityValue = mUTIL.ChangeRefineValue(tAbilityValue, tStat3);
		tAbilityValue = mUTIL.Change4thValue(tAbilityValue, tStat4);
		return tAbilityValue;

	case 2: // Blue Fox
		tStat1 = rand() % 10;
		tStat2 = rand() % 10 + 60;
		tStat3 = rand() % 10 + 70;
		tStat4 = 0;
		tAbilityValue = mUTIL.ChangeISValue(tAbilityValue, tStat1);
		tAbilityValue = mUTIL.ChangeIUValue(tAbilityValue, tStat2);
		tAbilityValue = mUTIL.ChangeRefineValue(tAbilityValue, tStat3);
		tAbilityValue = mUTIL.Change4thValue(tAbilityValue, tStat4);
		return tAbilityValue;
	}
}
float MyUtil::ReturnEliteMountStats(int tStatType, int tAnimalExpActivity)
{
	BYTE tData[4];
	int i;
	float tIncrease = 0.0f;

	CopyMemory(&tData[0], &tAnimalExpActivity, 4);
	for (i = 0; i < 4; i++)
	{
		if (tData[i])
		{
			if (tData[i] / 10 == tStatType)
			{
				tIncrease += 11.0f;
				tIncrease += (float)((int)tData[i] % 10);
			}
		}
	}

	return tIncrease;
}
int MyUtil::ReturnItemSort(ITEM_INFO* t)
{
	if (!t)
	{
		return -1;
	}
	switch (t->iType)
	{
	case 5:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 1;
		}
		if (t->iEquipInfo[1] == 11 || t->iEquipInfo[1] == 12 || t->iEquipInfo[1] == 13 || t->iEquipInfo[1] == 14)
		{
			return 2;
		}
		switch (t->iSort)
		{
		case 31:
			return 5;
		case 32:
			return 6;
		case 33:
			return 10;
		case 8:
			return 8;
		case 29:
			return 9;
		}
		break;
	case 6:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 4;
		}
		break;
	case 7:
		if(t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 11;
		}
		break;
	case 8:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 12;
		}
		break;
	default:
		if (t->iIndex >= 201 && t->iIndex <= 218 || t->iIndex >= 2303 && t->iIndex <= 2305)
		{
			return 3;
		}
		if (t->iSort == 28)
		{
			return 7;
		}
		break;
	}
	return 0;
}
int MyUtil::ReturnItemSort(int tItemIndex)
{
	ITEM_INFO* t;

	if (tItemIndex == 0)
	{
		return -1;
	}
	t = mITEM.Search(tItemIndex);
	if (!t)
	{
		return -1;
	}
	switch (t->iType)
	{
	case 5:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 1;
		}
		if (t->iEquipInfo[1] == 11 || t->iEquipInfo[1] == 12 || t->iEquipInfo[1] == 13 || t->iEquipInfo[1] == 14)
		{
			return 2;
		}
		switch (t->iSort)
		{
		case 31:
			return 5;
		case 32:
			return 6;
		case 33:
			return 10;
		case 8:
			return 8;
		case 29:
			return 9;
		}
		break;
	case 6:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 4;
		}
		break;
	case 7:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 11;
		}
		break;
	case 8:
		if (t->iEquipInfo[1] == 2 || t->iEquipInfo[1] == 4 || t->iEquipInfo[1] == 5 || t->iEquipInfo[1] == 6 || t->iEquipInfo[1] == 7 || t->iEquipInfo[1] == 9)
		{
			return 12;
		}
		break;
	default:
		if (t->iIndex >= 201 && t->iIndex <= 218 || t->iIndex >= 2303 && t->iIndex <= 2305)
		{
			return 3;
		}
		if (t->iSort == 28)
		{
			return 7;
		}
		break;
	}
	return 0;
}
int MyUtil::GetWarlordSetState(int tUserIndex)
{
	int result; // eax
	int j;		// [esp+4h] [ebp-E0h]
	int v5;		// [esp+DCh] [ebp-8h]
	int v6;		// [esp+E0h] [ebp-4h]
	int index01;
	ITEM_INFO* mEquipItem[MAX_EQUIP_SLOT_NUM];

	if (mUTIL.Set1Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
		return 1;
	else if (mUTIL.Set2Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0]) == 1)
		return 2;
	else if (mUTIL.Set3Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0]) == 1)
		return 3;
	else if (mUTIL.Set4Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0]) == 1)
		return 4;
	else if (mUTIL.Set5Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0], mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
		return 5;
	else if (mUTIL.Set1Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
		return 6;
	else if (mUTIL.Set2Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0]) == 1)
		return 7;
	else if (mUTIL.Set3Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0]) == 1)
		return 8;
	else if (mUTIL.Set4Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0]) == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88007 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88015 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88023 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88031 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88039 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88047 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88008 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88016 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88024 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88032 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88040 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88048)
		{
			result = 0;
		}
		else
		{
			result = 9;
		}
	}
	else if (mUTIL.Set5Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0], mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
	{
		result = 10;
	}
	else if (mUTIL.HeroSet1(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0], mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
	{
		result = 21;
	}
	else if (mUTIL.HeroSet2(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0], mUSER[tUserIndex].mAvatarInfo.aEquip[2][0], mUSER[tUserIndex].mAvatarInfo.aEquip[3][0], mUSER[tUserIndex].mAvatarInfo.aEquip[5][0], mUSER[tUserIndex].mAvatarInfo.aEquip[4][0], mUSER[tUserIndex].mAvatarInfo.aEquip[0][0]) == 1)
	{
		result = 22;
	}
	/*else if (mUTIL.sub_547470(mEquipItem[7]->iIndex, mEquipItem[2]->iIndex, mEquipItem[3]->iIndex, mEquipItem[5]->iIndex, mEquipItem[4]->iIndex, mEquipItem[0]->iIndex) == 1)
	{
		result = 15;
	}*/
	else
	{
		if (mUTIL.Set1Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] - 129) == 1)
		{
			result = 11;
		}
		else if (mUTIL.Set2Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[2][0] - 129) == 1)
		{
			result = 12;
		}
		else if (mUTIL.Set3Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[2][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[3][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[5][0] - 129) == 1)
		{
			result = 13;
		}
		else if (mUTIL.Set4Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[5][0] - 129) == 1)
		{
			result = 14;
		}
		else if (mUTIL.Set5Rare(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[2][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[3][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[5][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] - 129) == 1)
		{
			result = 15;
		}
		else if (mUTIL.Set1Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] - 129) == 1)
		{
			result = 16;
		}
		else if (mUTIL.Set2Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[2][0] - 129) == 1)
		{
			result = 17;
		}
		else if (mUTIL.Set3Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[3][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[5][0] - 129) == 1)
		{
			result = 18;
		}
		else if (mUTIL.Set4Elite(mUSER[tUserIndex].mAvatarInfo.aEquip[7][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[2][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[3][0] - 129, mUSER[tUserIndex].mAvatarInfo.aEquip[5][0] - 129) == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88007 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88015 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88023 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88031 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88039 || mUSER[tUserIndex].mAvatarInfo.aEquip[4][0] == 88047 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88008 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88016 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88024 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88032 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88040 || mUSER[tUserIndex].mAvatarInfo.aEquip[0][0] == 88048)
			{
				result = 0;
			}
			else
			{
				result = 19;
			}
		}
		else
		{
			v6 = 0;
			v5 = 0;
			for (j = 0; j < 13; ++j)
			{
				if ((!j || j == 2 || j == 3 || j == 4 || j == 5 || j == 7))
				{
					if (mUTIL.IsWarlord(mUSER[tUserIndex].mAvatarInfo.aEquip[j][0]) == 1)
						++v6;
					if (mUTIL.ReturnItemSort(mUSER[tUserIndex].mAvatarInfo.aEquip[j][0]) == 1 || mUTIL.ReturnItemSort(mUSER[tUserIndex].mAvatarInfo.aEquip[j][0]) == 4 || mUTIL.ReturnItemSort(mUSER[tUserIndex].mAvatarInfo.aEquip[j][0]) == 11 || mUTIL.ReturnItemSort(mUSER[tUserIndex].mAvatarInfo.aEquip[j][0]) == 12)
						++v5;
				}
			}
			if (v5 == 6)
			{
				result = 50;
			}
			else if (v6 == 6)
			{
				result = 20;
			}
			else if (v6 + v5 == 6)
			{
				result = 30;
			}
			else
			{
				result = 0;
			}
		}
	}
	return result;
}
BOOL MyUtil::Set1Rare(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87000 && v4 == 87001)
		return 1;
	if (v3 == 87021 && v4 == 87022)
		return 1;
	if (v3 == 87042 && v4 == 87043)
		return 1;
	if (v3 == 87500 && v4 == 87501)
		return 1;
	if (v3 == 87521 && v4 == 87522)
		return 1;
	return v3 == 87542 && v4 == 87543;
}
BOOL MyUtil::Set2Rare(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87002 && v4 == 87005)
		return 1;
	if (v3 == 87003 && v4 == 87005)
		return 1;
	if (v3 == 87004 && v4 == 87005)
		return 1;
	if (v3 == 87023 && v4 == 87026)
		return 1;
	if (v3 == 87024 && v4 == 87026)
		return 1;
	if (v3 == 87025 && v4 == 87026)
		return 1;
	if (v3 == 87044 && v4 == 87047)
		return 1;
	if (v3 == 87045 && v4 == 87047)
		return 1;
	if (v3 == 87046 && v4 == 87047)
		return 1;
	if (v3 == 87502 && v4 == 87505)
		return 1;
	if (v3 == 87503 && v4 == 87505)
		return 1;
	if (v3 == 87504 && v4 == 87505)
		return 1;
	if (v3 == 87523 && v4 == 87526)
		return 1;
	if (v3 == 87524 && v4 == 87526)
		return 1;
	if (v3 == 87525 && v4 == 87526)
		return 1;
	if (v3 == 87544 && v4 == 87547)
		return 1;
	if (v3 == 87545 && v4 == 87547)
		return 1;
	return v3 == 87546 && v4 == 87547;
}
BOOL MyUtil::Set3Rare(int a1, int a2, int a3)
{
	int v4; // [esp+4h] [ebp-18h]
	int v5; // [esp+8h] [ebp-14h]
	int v6; // [esp+Ch] [ebp-10h]
	int i;	// [esp+10h] [ebp-Ch]
	int v8; // [esp+14h] [ebp-8h]
	int j;	// [esp+18h] [ebp-4h]

	v4 = a1;
	v5 = a2;
	v6 = a3;

	if (v4 == NULL || v5 == NULL || v6 == NULL)
		return 0;

	if (v4 == 87006 && v5 == 87007 && v6 == 87008)
		return 1;
	if (v4 == 87027 && v5 == 87028 && v6 == 87029)
		return 1;
	if (v4 == 87048 && v5 == 87049 && v6 == 87050)
		return 1;
	if (v4 == 87506 && v5 == 87507 && v6 == 87508)
		return 1;
	if (v4 == 87527 && v5 == 87528 && v6 == 87529)
		return 1;
	return v4 == 87548 && v5 == 87549 && v6 == 87550;
}
BOOL MyUtil::Set4Rare(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87009 && v4 == 87012)
		return 1;
	if (v3 == 87010 && v4 == 87012)
		return 1;
	if (v3 == 87011 && v4 == 87012)
		return 1;
	if (v3 == 87030 && v4 == 87033)
		return 1;
	if (v3 == 87031 && v4 == 87033)
		return 1;
	if (v3 == 87032 && v4 == 87033)
		return 1;
	if (v3 == 87051 && v4 == 87054)
		return 1;
	if (v3 == 87052 && v4 == 87054)
		return 1;
	if (v3 == 87053 && v4 == 87054)
		return 1;
	if (v3 == 87509 && v4 == 87512)
		return 1;
	if (v3 == 87510 && v4 == 87512)
		return 1;
	if (v3 == 87511 && v4 == 87512)
		return 1;
	if (v3 == 87530 && v4 == 87533)
		return 1;
	if (v3 == 87531 && v4 == 87533)
		return 1;
	if (v3 == 87532 && v4 == 87533)
		return 1;
	if (v3 == 87551 && v4 == 87554)
		return 1;
	if (v3 == 87552 && v4 == 87554)
		return 1;
	return v3 == 87553 && v4 == 87554;
}
BOOL MyUtil::Set5Rare(int a1, int a2, int a3, int a4, int a5, int a6)
{
	int v7;	 // [esp+4h] [ebp-24h]
	int v8;	 // [esp+8h] [ebp-20h]
	int v9;	 // [esp+Ch] [ebp-1Ch]
	int v10; // [esp+10h] [ebp-18h]
	int v11; // [esp+14h] [ebp-14h]
	int v12; // [esp+18h] [ebp-10h]
	int i;	 // [esp+1Ch] [ebp-Ch]
	int v14; // [esp+20h] [ebp-8h]
	int j;	 // [esp+24h] [ebp-4h]

	v7 = a1;
	v8 = a2;
	v9 = a3;
	v10 = a4;
	v11 = a5;
	v12 = a6;

	if (v7 == NULL || v8 == NULL || v9 == NULL || v10 == NULL || v11 == NULL || v12 == NULL)
		return 0;

	if (v7 == 87013 && v8 == 87016 && v9 == 87017 && v10 == 87018 && v11 == 87019 && v12 == 87020)
		return 1;
	if (v7 == 87014 && v8 == 87016 && v9 == 87017 && v10 == 87018 && v11 == 87019 && v12 == 87020)
		return 1;
	if (v7 == 87015 && v8 == 87016 && v9 == 87017 && v10 == 87018 && v11 == 87019 && v12 == 87020)
		return 1;
	if (v7 == 86816 && v8 == 87016 && v9 == 87017 && v10 == 87018 && v11 == 87019 && v12 == 87020)
		return 1;
	if (v7 == 87034 && v8 == 87037 && v9 == 87038 && v10 == 87039 && v11 == 87040 && v12 == 87041)
		return 1;
	if (v7 == 87035 && v8 == 87037 && v9 == 87038 && v10 == 87039 && v11 == 87040 && v12 == 87041)
		return 1;
	if (v7 == 87036 && v8 == 87037 && v9 == 87038 && v10 == 87039 && v11 == 87040 && v12 == 87041)
		return 1;
	if (v7 == 86817 && v8 == 87037 && v9 == 87038 && v10 == 87039 && v11 == 87040 && v12 == 87041)
		return 1;
	if (v7 == 87055 && v8 == 87058 && v9 == 87059 && v10 == 87060 && v11 == 87061 && v12 == 87062)
		return 1;
	if (v7 == 87056 && v8 == 87058 && v9 == 87059 && v10 == 87060 && v11 == 87061 && v12 == 87062)
		return 1;
	if (v7 == 87057 && v8 == 87058 && v9 == 87059 && v10 == 87060 && v11 == 87061 && v12 == 87062)
		return 1;
	if (v7 == 86818 && v8 == 87058 && v9 == 87059 && v10 == 87060 && v11 == 87061 && v12 == 87062)
		return 1;
	if (v7 == 87013 && v8 == 87516 && v9 == 87517 && v10 == 87518 && v11 == 87519 && v12 == 87520)
		return 1;
	if (v7 == 87014 && v8 == 87516 && v9 == 87517 && v10 == 87518 && v11 == 87519 && v12 == 87520)
		return 1;
	if (v7 == 87015 && v8 == 87516 && v9 == 87517 && v10 == 87518 && v11 == 87519 && v12 == 87520)
		return 1;
	if (v7 == 86816 && v8 == 87516 && v9 == 87517 && v10 == 87518 && v11 == 87519 && v12 == 87520)
		return 1;
	if (v7 == 87534 && v8 == 87537 && v9 == 87538 && v10 == 87539 && v11 == 87540 && v12 == 87541)
		return 1;
	if (v7 == 87535 && v8 == 87537 && v9 == 87538 && v10 == 87539 && v11 == 87540 && v12 == 87541)
		return 1;
	if (v7 == 87536 && v8 == 87537 && v9 == 87538 && v10 == 87539 && v11 == 87540 && v12 == 87541)
		return 1;
	if (v7 == 86817 && v8 == 87537 && v9 == 87538 && v10 == 87539 && v11 == 87540 && v12 == 87541)
		return 1;
	if (v7 == 87555 && v8 == 87558 && v9 == 87559 && v10 == 87560 && v11 == 87561 && v12 == 87562)
		return 1;
	if (v7 == 87556 && v8 == 87558 && v9 == 87559 && v10 == 87560 && v11 == 87561 && v12 == 87562)
		return 1;
	if (v7 == 87557 && v8 == 87558 && v9 == 87559 && v10 == 87560 && v11 == 87561 && v12 == 87562)
		return 1;
	return v7 == 86818 && v8 == 87558 && v9 == 87559 && v10 == 87560 && v11 == 87561 && v12 == 87562;
}
BOOL MyUtil::Set1Elite(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87063 && v4 == 87064)
		return 1;
	if (v3 == 87085 && v4 == 87086)
		return 1;
	return v3 == 87107 && v4 == 87108;
}
BOOL MyUtil::Set2Elite(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87065 && v4 == 87068)
		return 1;
	if (v3 == 87066 && v4 == 87068)
		return 1;
	if (v3 == 87067 && v4 == 87068)
		return 1;
	if (v3 == 87087 && v4 == 87090)
		return 1;
	if (v3 == 87088 && v4 == 87090)
		return 1;
	if (v3 == 87089 && v4 == 87090)
		return 1;
	if (v3 == 87109 && v4 == 87112)
		return 1;
	if (v3 == 87110 && v4 == 87112)
		return 1;
	return v3 == 87111 && v4 == 87112;
}
BOOL MyUtil::Set3Elite(int a1, int a2)
{
	int v3; // [esp+4h] [ebp-14h]
	int v4; // [esp+8h] [ebp-10h]
	int i;	// [esp+Ch] [ebp-Ch]
	int v6; // [esp+10h] [ebp-8h]
	int j;	// [esp+14h] [ebp-4h]

	v3 = a1;
	v4 = a2;

	if (v3 == NULL || v4 == NULL)
		return 0;

	if (v3 == 87069 && v4 == 87070)
		return 1;
	if (v3 == 87091 && v4 == 87092)
		return 1;
	return v3 == 87113 && v4 == 87114;
}
BOOL MyUtil::Set4Elite(int a1, int a2, int a3, int a4)
{
	int v5;	 // [esp+4h] [ebp-1Ch]
	int v6;	 // [esp+8h] [ebp-18h]
	int v7;	 // [esp+Ch] [ebp-14h]
	int v8;	 // [esp+10h] [ebp-10h]
	int i;	 // [esp+14h] [ebp-Ch]
	int v10; // [esp+18h] [ebp-8h]
	int j;	 // [esp+1Ch] [ebp-4h]

	v5 = a1;
	v6 = a2;
	v7 = a3;
	v8 = a4;

	if (v5 == NULL || v6 == NULL || v7 == NULL || v8 == NULL)
		return 0;

	if (v5 == 87071 && v6 == 87074 && v7 == 87075 && v8 == 87076)
		return 1;
	if (v5 == 87072 && v6 == 87074 && v7 == 87075 && v8 == 87076)
		return 1;
	if (v5 == 87073 && v6 == 87074 && v7 == 87075 && v8 == 87076)
		return 1;
	if (v5 == 87093 && v6 == 87096 && v7 == 87097 && v8 == 87098)
		return 1;
	if (v5 == 87094 && v6 == 87096 && v7 == 87097 && v8 == 87098)
		return 1;
	if (v5 == 87095 && v6 == 87096 && v7 == 87097 && v8 == 87098)
		return 1;
	if (v5 == 87115 && v6 == 87118 && v7 == 87119 && v8 == 87120)
		return 1;
	if (v5 == 87116 && v6 == 87118 && v7 == 87119 && v8 == 87120)
		return 1;
	return v5 == 87117 && v6 == 87118 && v7 == 87119 && v8 == 87120;
}
BOOL MyUtil::Set5Elite(int a1, int a2, int a3, int a4, int a5, int a6)
{
	int v7;	 // [esp+4h] [ebp-24h]
	int v8;	 // [esp+8h] [ebp-20h]
	int v9;	 // [esp+Ch] [ebp-1Ch]
	int v10; // [esp+10h] [ebp-18h]
	int v11; // [esp+14h] [ebp-14h]
	int v12; // [esp+18h] [ebp-10h]
	int i;	 // [esp+1Ch] [ebp-Ch]
	int v14; // [esp+20h] [ebp-8h]
	int j;	 // [esp+24h] [ebp-4h]

	v7 = a1;
	v8 = a2;
	v9 = a3;
	v10 = a4;
	v11 = a5;
	v12 = a6;

	if (v7 == NULL || v8 == NULL || v9 == NULL || v10 == NULL || v11 == NULL || v12 == NULL)
		return 0;

	if (v7 == 87077 && v8 == 87080 && v9 == 87081 && v10 == 87082 && v11 == 87083 && v12 == 87084)
		return 1;
	if (v7 == 87078 && v8 == 87080 && v9 == 87081 && v10 == 87082 && v11 == 87083 && v12 == 87084)
		return 1;
	if (v7 == 87079 && v8 == 87080 && v9 == 87081 && v10 == 87082 && v11 == 87083 && v12 == 87084)
		return 1;
	if (v7 == 87099 && v8 == 87102 && v9 == 87103 && v10 == 87104 && v11 == 87105 && v12 == 87106)
		return 1;
	if (v7 == 87100 && v8 == 87102 && v9 == 87103 && v10 == 87104 && v11 == 87105 && v12 == 87106)
		return 1;
	if (v7 == 87101 && v8 == 87102 && v9 == 87103 && v10 == 87104 && v11 == 87105 && v12 == 87106)
		return 1;
	if (v7 == 87121 && v8 == 87124 && v9 == 87125 && v10 == 87126 && v11 == 87127 && v12 == 87128)
		return 1;
	if (v7 == 87122 && v8 == 87124 && v9 == 87125 && v10 == 87126 && v11 == 87127 && v12 == 87128)
		return 1;
	return v7 == 87123 && v8 == 87124 && v9 == 87125 && v10 == 87126 && v11 == 87127 && v12 == 87128;
}
BOOL MyUtil::HeroSet1(int a1, int a2, int a3, int a4, int a5, int a6)
{
	int v7;	 // [esp+4h] [ebp-24h]
	int v8;	 // [esp+8h] [ebp-20h]
	int v9;	 // [esp+Ch] [ebp-1Ch]
	int v10; // [esp+10h] [ebp-18h]
	int v11; // [esp+14h] [ebp-14h]
	int v12; // [esp+18h] [ebp-10h]
	int i;	 // [esp+1Ch] [ebp-Ch]
	int v14; // [esp+20h] [ebp-8h]
	int j;	 // [esp+24h] [ebp-4h]

	v7 = a1;
	v8 = a2;
	v9 = a3;
	v10 = a4;
	v11 = a5;
	v12 = a6;

	if (v7 == NULL || v8 == NULL || v9 == NULL || v10 == NULL || v11 == NULL || v12 == NULL)
		return 0;

	if (v7 == 88001 && v8 == 88004 && v9 == 88005 && v10 == 88006 && v11 == 88007 && v12 == 88008)
		return 1;
	if (v7 == 88002 && v8 == 88004 && v9 == 88005 && v10 == 88006 && v11 == 88007 && v12 == 88008)
		return 1;
	if (v7 == 88003 && v8 == 88004 && v9 == 88005 && v10 == 88006 && v11 == 88007 && v12 == 88008)
		return 1;
	if (v7 == 88009 && v8 == 88012 && v9 == 88013 && v10 == 88014 && v11 == 88015 && v12 == 88016)
		return 1;
	if (v7 == 88010 && v8 == 88012 && v9 == 88013 && v10 == 88014 && v11 == 88015 && v12 == 88016)
		return 1;
	if (v7 == 88011 && v8 == 88012 && v9 == 88013 && v10 == 88014 && v11 == 88015 && v12 == 88016)
		return 1;
	if (v7 == 88017 && v8 == 88020 && v9 == 88021 && v10 == 88022 && v11 == 88023 && v12 == 88024)
		return 1;
	if (v7 == 88018 && v8 == 88020 && v9 == 88021 && v10 == 88022 && v11 == 88023 && v12 == 88024)
		return 1;
	return v7 == 88019 && v8 == 88020 && v9 == 88021 && v10 == 88022 && v11 == 88023 && v12 == 88024;
}
BOOL MyUtil::HeroSet2(int a1, int a2, int a3, int a4, int a5, int a6)
{
	int v7;	 // [esp+4h] [ebp-24h]
	int v8;	 // [esp+8h] [ebp-20h]
	int v9;	 // [esp+Ch] [ebp-1Ch]
	int v10; // [esp+10h] [ebp-18h]
	int v11; // [esp+14h] [ebp-14h]
	int v12; // [esp+18h] [ebp-10h]
	int i;	 // [esp+1Ch] [ebp-Ch]
	int v14; // [esp+20h] [ebp-8h]
	int j;	 // [esp+24h] [ebp-4h]

	v7 = a1;
	v8 = a2;
	v9 = a3;
	v10 = a4;
	v11 = a5;
	v12 = a6;

	if (v7 == NULL || v8 == NULL || v9 == NULL || v10 == NULL || v11 == NULL || v12 == NULL)
		return 0;

	if (v7 == 88025 && v8 == 88028 && v9 == 88029 && v10 == 88030 && v11 == 88031 && v12 == 88032)
		return 1;
	if (v7 == 88026 && v8 == 88028 && v9 == 88029 && v10 == 88030 && v11 == 88031 && v12 == 88032)
		return 1;
	if (v7 == 88027 && v8 == 88028 && v9 == 88029 && v10 == 88030 && v11 == 88031 && v12 == 88032)
		return 1;
	if (v7 == 88033 && v8 == 88036 && v9 == 88037 && v10 == 88038 && v11 == 88039 && v12 == 88040)
		return 1;
	if (v7 == 88034 && v8 == 88036 && v9 == 88037 && v10 == 88038 && v11 == 88039 && v12 == 88040)
		return 1;
	if (v7 == 88035 && v8 == 88036 && v9 == 88037 && v10 == 88038 && v11 == 88039 && v12 == 88040)
		return 1;
	if (v7 == 88041 && v8 == 88044 && v9 == 88045 && v10 == 88046 && v11 == 88047 && v12 == 88048)
		return 1;
	if (v7 == 88042 && v8 == 88044 && v9 == 88045 && v10 == 88046 && v11 == 88047 && v12 == 88048)
		return 1;
	return v7 == 88043 && v8 == 88044 && v9 == 88045 && v10 == 88046 && v11 == 88047 && v12 == 88048;
}
BOOL MyUtil::IsWarlord(int a1)
{
	if (a1 >= 87206 && a1 <= 87213)
		return 1;
	if (a1 >= 87228 && a1 <= 87235)
		return 1;
	return a1 >= 87250 && a1 <= 87257;
}
int MyUtil::ReturnEngraveStats(int tItemSort, int tItemIndex, int tImproveValue, int tSort)
{
	int t4thValue = Return4thValue(tImproveValue);

	if (t4thValue < 1 || t4thValue >  59)
	{
		return 0;
	}

	if (tItemSort == 8)
	{
		if (tItemIndex != 1)
		{
			return 0;
		}
		switch (tSort)
		{
		case 10:
			switch (t4thValue)
			{
			case 2: return -3600;
			case 5: return 1200;
			case 8: return 2400;
			case 17: return -1200;
			case 24: return 2400;
			case 31: return 1200;
			case 46: return 1200;
			case 49: return -1200;
			case 53: return 1200;
			case 58: return 2400;
			default: return 0;
			}
			break;
		case 20:
			switch (t4thValue)
			{
			case 1: return -3000;
			case 3: return 2000;
			case 6: return 1000;
			case 15: return 1000;
			case 18: return -1000;
			case 20: return 3000;
			case 21: return 1000;
			case 22: return 1000;
			case 24: return 1000;
			case 29: return -2000;
			case 30: return 1000;
			case 34: return 3000;
			case 35: return 1000;
			case 42: return 1000;
			case 51: return 1000;
			case 52: return 2000;
			case 54: return 1000;
			case 58: return 1000;
			default: return 0;
			}
			break;
		case 30:
			switch (t4thValue)
			{
			case 10: return 1500;
			case 41: return 1500;
			default: return 0;
			}
			break;
		case 40:
			switch (t4thValue)
			{
			case 9: return 300;
			default: return 0;
			}
			break;
		case 50:
			switch (t4thValue)
			{
			case 7: return -600;
			case 25: return 200;
			case 35: return 400;
			case 36: return 200;
			case 38: return -200;
			case 39: return 200;
			case 44: return 200;
			case 47: return 200;
			case 51: return 100;
			case 55: return 200;
			default: return 0;
			}
			break;
		case 60:
			switch (t4thValue)
			{
			case 21: return 200;
			case 22: return 200;
			case 25: return 200;
			case 37: return 200;
			case 38: return 200;
			case 39: return -200;
			case 45: return 200;
			case 47: return 200;
			case 55: return 200;
			case 58: return 100;
			default: return 0;
			}
			break;
		case 70:
			switch (t4thValue)
			{
			case 11: return -3;
			case 28: return -3;
			case 40: return -3;
			default: return 0;
			}
			break;
		case 80:
			switch (t4thValue)
			{
			case 1: return 2;
			case 2: return 2;
			case 3: return -3;
			case 4: return 2;
			case 5: return -3;
			case 6: return 1;
			case 7: return 2;
			case 8: return -2;
			case 9: return 1;
			case 10: return 1;
			case 11: return 3;
			case 12: return 1;
			case 14: return -3;
			case 15: return -3;
			case 16: return 2;
			case 17: return 2;
			case 18: return 2;
			case 19: return -2;
			case 20: return -2;
			case 21: return 1;
			case 23: return 2;
			case 27: return 1;
			case 28: return 3;
			case 29: return 4;
			case 30: return 2;
			case 31: return 2;
			case 32: return 2;
			case 33: return 3;
			case 36: return 2;
			case 37: return 2;
			case 38: return 3;
			case 39: return 3;
			case 40: return 4;
			case 41: return 4;
			case 42: return 4;
			case 43: return 4;
			case 44: return 4;
			case 45: return 4;
			case 46: return 4;
			case 47: return 4;
			case 48: return 6;
			case 49: return 5;
			case 50: return 5;
			case 51: return 5;
			case 52: return 5;
			case 53: return 5;
			case 54: return 5;
			case 55: return 5;
			case 56: return 5;
			case 57: return 5;
			case 58: return 5;
			case 59: return 6;
			default: return 0;
			}
			break;
		case 90:
			switch (t4thValue)
			{
			case 4: return -3;
			case 5: return 1;
			case 9: return -1;
			case 10: return -1;
			case 13: return 1;
			case 14: return 2;
			case 15: return 1;
			case 16: return -1;
			case 19: return 3;
			case 26: return 2;
			case 27: return 1;
			case 32: return 1;
			case 41: return 1;
			case 43: return 1;
			case 48: return -2;
			case 49: return 1;
			case 53: return 1;
			case 54: return 1;
			case 56: return 2;
			default: return 0;
			}
			break;

		}
		return 0;
	}
	else if (tItemSort == 1 || tItemSort == 4 || tItemSort == 11 || tItemSort == 12)
	{
		if (tItemIndex && tItemIndex != 2 && tItemIndex != 3 && tItemIndex != 4 && tItemIndex != 5)
		{
			return 0;
		}
		switch (tSort)
		{
		case 10:
			switch (t4thValue)
			{
			case 2: return -3600;
			case 8: return -3600;
			case 17: return -1200;
			case 24: return -2400;
			case 49: return -2400;
			default: return 0;
			}
			break;
		case 20:
			switch (t4thValue)
			{
			case 1: return -3000;
			case 3: return 2000;
			case 5: return 1000;
			case 6: return 1000;
			case 8: return 2000;
			case 9: return -1000;
			case 10: return -1000;
			case 13: return 1000;
			case 15: return 1000;
			case 16: return -2000;
			case 18: return -1000;
			case 19: return 3000;
			case 20: return 3000;
			case 21: return 1000;
			case 22: return 1000;
			case 24: return 2000;
			case 26: return 3000;
			case 27: return 1000;
			case 29: return -2000;
			case 30: return 1000;
			case 31: return 3000;
			case 34: return 3000;
			case 42: return 1000;
			case 48: return -2000;
			case 49: return 1000;
			case 51: return 1000;
			case 52: return 1000;
			case 53: return 500;
			case 54: return 1000;
			case 56: return 1000;
			default: return 0;
			}
			break;
		case 30:
			switch (t4thValue)
			{
			case 10: return 1500;
			case 11: return -4500;
			case 13: return 1500;
			case 31: return 1500;
			case 36: return 1500;
			case 41: return -1500;
			case 46: return 1500;
			case 53: return 1500;
			default: return 0;
			}
			break;
		case 40:
			switch (t4thValue)
			{
			case 9:  return 300;
			case 12: return 300;
			case 15: return 300;
			case 16: return -300;
			case 34: return 300;
			case 37: return 300;
			case 41: return 600;
			case 43: return 300;
			case 54: return 300;
			default: return 0;
			}
			break;
		case 50:
			switch (t4thValue)
			{
			case 4: return -600;
			case 5: return 200;
			case 25: return 200;
			case 35: return 200;
			case 38: return -200;
			case 39: return 200;
			case 44: return 200;
			case 47: return -200;
			case 51: return 100;
			case 55: return 100;
			case 58: return 300;
			default: return 0;
			}
			break;
		case 60:
			switch (t4thValue)
			{
			case 7: return -600;
			case 14: return 400;
			case 21: return 200;
			case 22: return 200;
			case 25: return 200;
			case 35: return 200;
			case 38: return 200;
			case 39: return -200;
			case 45: return 200;
			case 47: return -200;
			case 55: return 100;
			case 56: return 100;
			case 57: return 300;
			default: return 0;
			}
			break;
		case 70:
			switch (t4thValue)
			{
			case 28: return -2;
			case 40: return -2;
			default: return 0;
			}
			break;
		case 80:
			switch (t4thValue)
			{
			case 19: return -2;
			case 32: return 2;
			default: return 0;
			}
			break;
		case 100:
			switch (t4thValue)
			{
			case 1: return 2000;
			case 2: return 2000;
			case 3: return -3000;
			case 4: return 2000;
			case 5: return -3000;
			case 6: return 1000;
			case 7: return 2000;
			case 9: return 1000;
			case 10: return 1000;
			case 11: return 3000;
			case 12: return 1000;
			case 14: return -2000;
			case 15: return -3000;
			case 16: return 3000;
			case 17: return 3000;
			case 18: return 3000;
			case 20: return -3000;
			case 21: return 2000;
			case 23: return 3000;
			case 27: return 1000;
			case 28: return 3000;
			case 29: return 4000;
			case 30: return 2000;
			case 32: return 5000;
			case 33: return 4000;
			case 35: return 2000;
			case 36: return 3000;
			case 37: return 3000;
			case 38: return 3000;
			case 39: return 3000;
			case 40: return 5000;
			case 41: return 5000;
			case 42: return 5000;
			case 43: return 5000;
			case 44: return 5000;
			case 45: return 5000;
			case 46: return 5000;
			case 47: return 7000;
			case 48: return 7000;
			case 49: return 6000;
			case 50: return 6000;
			case 51: return 7000;
			case 52: return 7000;
			case 53: return 7000;
			case 54: return 7000;
			case 55: return 7000;
			case 56: return 7000;
			case 57: return 7000;
			case 58: return 7000;
			case 59: return 8000;
			default: return 0;
			}
			break;
		}
		return 0;
	}

	return 0;
}
int MyUtil::ReturnMountSort(int aAnimalNumber)
{
	ITEM_INFO* tITEM_INFO = mITEM.Search(aAnimalNumber);
	if (tITEM_INFO == NULL)
	{
		return 0;
	}
	if (tITEM_INFO->iSort == 30)
	{
		return 30;
	}
	return 3;
}
int MyUtil::GetTowerSort(int iType, int iIndex)
{
	switch (iType)
	{
	case 1: // Get TowerSort
		switch (mSERVER_INFO.mServerNumber)
		{
		case 2:
			return 0;
		case 3:
			return 1;
		case 4:
			return 2;
		case 7:
			return 3;
		case 8:
			return 4;
		case 9:
			return 5;
		case 12:
			return 6;
		case 13:
			return 7;
		case 14:
			return 8;
		case 141:
			return 9;
		case 142:
			return 10;
		case 143:
			return 11;
		default:
			return 0;
		}
		break;
	case 2: // GetTowerIndexNumber
		switch (iIndex)
		{
		case 589:
		case 590:
		case 591:
		case 592:
			return 0;
		case 593:
		case 594:
		case 595:
		case 596:
			return 1;
		case 597:
		case 598:
		case 599:
		case 600:
			return 2;
		}
		break;

	case 3: // Get What Tower to Summon From mGAME
		switch (mGAME.mTowerInfo.mTowerInfo[iIndex])
		{
		case 201:
			return 589;
		case 202:
			return 593;
		case 203:
			return 597;
		case 401:
			return 590;
		case 402:
			return 594;
		case 403:
			return 598;
		case 601:
			return 591;
		case 602:
			return 595;
		case 603:
			return 599;
		case 801:
			return 592;
		case 802:
			return 596;
		case 803:
			return 600;
		default:
			return 0;
		}
		break;

	case 4:
		switch (iIndex)
		{
		case 201:
			return 589;
		case 202:
			return 593;
		case 203:
			return 597;
		case 401:
			return 590;
		case 402:
			return 594;
		case 403:
			return 598;
		case 601:
			return 591;
		case 602:
			return 595;
		case 603:
			return 599;
		case 801:
			return 592;
		case 802:
			return 596;
		case 803:
			return 600;
		default:
			return 0;
		}
		break;
	}
}
float MyUtil::ReturnRageDmgUp(int a1)
{
	switch (a1)
	{
	case 1:
		return 1.05f;
	case 2:
		return 1.07f;
	case 3:
		return 1.09f;
	case 4:
		return 1.11f;
	case 5:
		return 1.14f;
	case 6:
		return 1.17f;
	case 7:
		return 1.2f;
	case 8:
		return 1.25f;
	case 9:
		return 1.3f;
	case 10:
		return 1.4f;
	default:
		return 1.0f;
	}
}
void MyUtil::GetGMTimeNow(int tUserIndex)
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	char TimeBuffer[100];
	sprintf(TimeBuffer, "%02d%02d%02d%02d%d", tPresentTime->tm_mon, tPresentTime->tm_mday, tPresentTime->tm_hour, tPresentTime->tm_min, tPresentTime->tm_wday);
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(98, atoi(TimeBuffer));
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
int MyUtil::GetPetMaxExpCapacity(int pIndex)
{
	switch (pIndex)
	{
	case 547:
	case 541:
		return mPAT.mMaxRangeValue[0];
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		return mPAT.mMaxRangeValue[1];
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		return mPAT.mMaxRangeValue[2];
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		return mPAT.mMaxRangeValue[3];
	case 1016:
	case 1310:
	case 1311:
	case 1312:
	case 2133:
	case 2144:
	case 2160:
	case 1980: // Seasonal M33 Custom Pet
	case 1981: // Seasonal M33 Custom Pet
	case 1982: // Seasonal M33 Custom Pet
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
	case 1990: // Seasonal M33 Custom Pet
		return mPAT.mMaxRangeValue[7];
	}
}
BOOL MyUtil::CheckAnimalExpMaximum(int AnimalExp, int ToAdd)
{
	int AnimalExpBuffer = 0;
	if ((AnimalExp % 100000) == 0)
	{
		AnimalExpBuffer = 100000;
	}
	else
	{
		AnimalExpBuffer = AnimalExp % 100000;
	}

	if ((AnimalExpBuffer + ToAdd) > 100000)
	{
		return TRUE;
	}
	return FALSE;
}
void MyUtil::BroadcastGameEvent(int tSort, int tUserIndex, int tItemIndex)
{
	ITEM_INFO* tITEM_INFO;
	BYTE tData[100];
	tITEM_INFO = mITEM.Search(tItemIndex);
	if (!tITEM_INFO)
	{
		return;
	}
	switch (tSort)
	{
	case 1: // Legendary Pet Craft
		sprintf((char*)&tData[0], "%s has successfully crafted %s", mUSER[tUserIndex].mAvatarInfo.aName, tITEM_INFO->iName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		return;
	case 2: // Legendary Pet Exchange
		sprintf((char*)&tData[0], "%s exchanged legendary pet into %s", mUSER[tUserIndex].mAvatarInfo.aName, tITEM_INFO->iName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		return;
	case 3: // Elite Drop
		sprintf((char*)&tData[0], "[DROP] %s gained %s", mUSER[tUserIndex].mAvatarInfo.aName, tITEM_INFO->iName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		return;
	case 4:
		sprintf((char*)&tData[0], "King Turtle has spawned at Proving Grounds!");
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		return;
	case 5:
		sprintf((char*)&tData[0], "King Turtle has been defeated by %s", mUSER[tUserIndex].mAvatarInfo.aName);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
		return;

	default:
		return;
	}
}
BOOL MyUtil::CheckActiveSpecialSkill(int tUserIndex, int tSort, int tSkillIndex)
{
	int index01;

	if (tSort == 1 && mAVATAR_OBJECT[tUserIndex].mDATA.mSpecialSkillState != 1)
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 14; index01++)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aCombineSkills[tSort][index01] == tSkillIndex)
		{
			return TRUE;
		}
	}
	return FALSE;
}
BOOL MyUtil::CheckSpecialSkillState(int tUserIndex, int tSort, int tItemIndex, int tSkillIndex, int tMonsterSort, int tMonsterIndex, DWORD tMonsterUniqueNumber)
{
	int index01;
	// Sort 1 = Active, 0 = Passive

	if (!CheckActiveSpecialSkill(tUserIndex, tSort, tItemIndex))
		return 0;
	if (tSort)
	{
		if (tSort == 1)
		{
			switch (tItemIndex)
			{
			case 91388:
				if (mUSER[tUserIndex].mEffectValue[9][0] <= 0 && mUSER[tUserIndex].mEffectValue[29][0] <= 0 && mUSER[tUserIndex].mEffectValue[30][0] <= 0 && mUSER[tUserIndex].mEffectValue[31][0] <= 0 && mUSER[tUserIndex].mEffectValue[32][0] <= 0 && mUSER[tUserIndex].mEffectValue[33][0] <= 0 && mUSER[tUserIndex].mEffectValue[34][0] <= 0)
				{
					return FALSE;
				}
				return TRUE;
			case 91389:
				return TRUE;
			case 91390:
				return TRUE;
			case 91391:
				return TRUE;
			case 91392:
				if (mUSER[tUserIndex].mEffectValue[12][0] <= 0)
				{
					return FALSE;
				}
				return TRUE;
			default:
				return FALSE;
			}
		}
		else
		{
			return FALSE;
		}
	}
	else
	{
		switch (tItemIndex)
		{
		case 91383:
			switch (tSkillIndex)
			{
			case 10:
			case 14:
			case 18:
			case 29:
			case 33:
			case 37:
			case 48:
			case 52:
			case 56:
				if (mUSER[tUserIndex].mAvatarInfo.aFuryState != 1)
				{
					return FALSE;
				}
				return TRUE;
			default:
				return FALSE;
			}
			break;
		case 91384:
			switch (tSkillIndex)
			{
			case 86:
			case 88:
			case 90:
			case 92:
			case 94:
			case 96:
			case 98:
			case 100:
			case 102:
				if (tMonsterSort != 5)
				{
					return FALSE;
				}
				return FALSE; // Disabled
			default:
				return FALSE; // Disabled
			}
			break;
		case 91385:
			switch (tSkillIndex)
			{
			case 122:
			case 124:
			case 126:
			case 128:
			case 130:
			case 132:
			case 134:
			case 136:
			case 138:
				return TRUE;
			default:
				return FALSE;
			}
			break;
		case 91386:
			if (tSkillIndex != 84)
			{
				return FALSE;
			}
			return TRUE;
		case 91387:
			if (tSkillIndex != 104)
			{
				return FALSE;
			}
			return TRUE;
		default:
			return FALSE;
		}
	}
}
int MyUtil::ReturnSortForUltEnchant(int tItemIndex)
{
	ITEM_INFO* tITEM_INFO;
	tITEM_INFO = mITEM.Search(tItemIndex);
	if (tITEM_INFO)
	{
		switch (tITEM_INFO->iSort)
		{
		case 7:
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
		case 20:
		case 21:
			return 0;
		case 29:
			return 1;
		case 31:
		case 32:
		case 33:
			return 2;
		case 36:
			return 3;
		case 34:
			return 4;
		}
	}
}
int MyUtil::ReturnMaterialForEngrave(int tItemIndex)
{
	if (tItemIndex >= 17453 && tItemIndex <= 17511)
	{
		return 1;
	}
	else if (tItemIndex >= 17513 && tItemIndex <= 17571)
	{
		return 2;
	}
	else if (tItemIndex >= 17216 && tItemIndex <= 17274)
	{
		return 3;
	}
	else if (tItemIndex >= 17276 && tItemIndex <= 17334)
	{
		return 4;
	}
	else if (tItemIndex >= 17216 && tItemIndex <= 17274)
	{
		return 5;
	}
	else if (tItemIndex >= 17045 && tItemIndex <= 17103)
	{
		return 6;
	}
	else if (tItemIndex >= 17105 && tItemIndex <= 17163)
	{
		return 7;
	}
}
int MyUtil::ReturnTowerSort(int tZoneNumber)
{
	switch (tZoneNumber)
	{
	case 2: return 0;
	case 3: return 1;
	case 4: return 2;
	case 7: return 3;
	case 8: return 4;
	case 9: return 5;
	case 12: return 6;
	case 13: return 7;
	case 14: return 8;
	case 141: return 9;
	case 142: return 10;
	case 143: return 11;
	default: return -1;
	}
}
void MyUtil::ReturnMountExp(int tMountExpIndex, int* tMountFeed, int* tMountExp)
{
	if (tMountExpIndex >= 0)
	{
		*tMountFeed = tMountExpIndex / 1000000;
		*tMountExp = tMountExpIndex % 1000000;
		if (*tMountFeed > 100)
			*tMountFeed = 0;
		if (*tMountExp > 100000)
			*tMountExp = 0;
	}
	else
	{
		*tMountFeed = 0;
		*tMountExp = 0;
	}
}
void MyUtil::SetMountExp(int tFeed, int tExp, int* tResult)
{
	if (tFeed >= 0 && tFeed <= 100 && tExp >= 0 && tExp <= 100000)
		*tResult = tExp + 1000000 * tFeed;
	else
		*tResult = 0;
}
int MyUtil::ProcessForMountExp(int tAnimalExp, int ToAdd)
{
	int tFeed = 0;
	int tExp = 0;
	int tNewAnimalExp = 0;

	ReturnMountExp(tAnimalExp, &tFeed, &tExp);
	tExp += ToAdd;
	if (tExp > 100000)
		tExp = 100000;

	SetMountExp(tFeed, tExp, &tNewAnimalExp);
	return tNewAnimalExp;
}
BOOL MyUtil::TowerMapToTribeIndex(int tZoneNumber, int tTribe)
{
	BOOL result;

	switch (tZoneNumber)
	{
	case 2:
	case 3:
	case 4:
		result = tTribe == 0;
		break;
	case 7:
	case 8:
	case 9:
		result = tTribe == 1;
		break;
	case 12:
	case 13:
	case 14:
		result = tTribe == 2;
		break;
	case 141:
	case 142:
	case 143:
		result = tTribe == 3;
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
BOOL MyUtil::WorkForTowerBuild(int tUserIndex, int tWhatTower)
{
	int tTowerIndex = -1;
	int i = 0;
	int tTowerNum = 0;

	if (mGAME.ReturnTribeRole(mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aTribe) != 1 &&
		mGAME.ReturnTribeRole(mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aTribe) != 2)
	{
		return FALSE;
	}
	if (!TowerMapToTribeIndex(mSERVER_INFO.mServerNumber, mUSER[tUserIndex].mAvatarInfo.aTribe))
	{
		return FALSE;
	}
	tTowerIndex = ReturnTowerSort(mSERVER_INFO.mServerNumber);
	if (tTowerIndex == -1)
	{
		return FALSE;
	}
	if (mGAME.mTowerInfo.mTowerInfo[tTowerIndex] <= 0)
	{
		for (i = 0; i < 12; i++)
		{
			if (mGAME.mTowerInfo.mTowerInfo[i] % 100 == tWhatTower)
			{
				if (3 * mUSER[tUserIndex].mAvatarInfo.aTribe <= i && 3 * mUSER[tUserIndex].mAvatarInfo.aTribe + 2 >= i)
				{
					return FALSE;
				}
				if (mGAME.mTowerInfo.mTowerInfo[i] / 100 != 9)
				{
					tTowerNum++;
				}
				if (tTowerNum >= 3)
				{
					return FALSE;
				}
			}
		}
		return TRUE;
	}
	else if (mGAME.mTowerInfo.mTowerInfo[tTowerIndex] / 100 == 9)
	{
		return FALSE;
	}
	else
	{
		return FALSE;
	}
	return FALSE;
}
int MyUtil::GetSocketAbility(int tSocket1, int tSocket2, int tSocket3, int* s1, int* s2, int* s3, int* s4, int* s5)
{
	BYTE tS1[4];
	BYTE tS2[4];
	BYTE tS3[4];
	int tSocketNum = 0;
	int tSockets[8] = { 0 };

	CopyMemory(&tS1, &tSocket1, 4);
	CopyMemory(&tS2, &tSocket2, 4);
	CopyMemory(&tS3, &tSocket3, 4);

	tSocketNum = tS1[1];
	if (tSocketNum == 0)
	{
		return 0;
	}
	tSockets[0] = tS2[0];
	tSockets[1] = tS2[1];
	tSockets[2] = tS2[2];
	tSockets[3] = tS2[3];
	tSockets[4] = tS3[0];
	tSockets[5] = tS3[1];
	tSockets[6] = tS3[2];
	tSockets[7] = tS3[3];
	*s1 = tS1[3] + 1000 * tS1[2];
	*s2 = tSockets[1] + 1000 * tSockets[0];
	*s3 = tSockets[3] + 1000 * tSockets[2];
	*s4 = tSockets[5] + 1000 * tSockets[4];
	*s5 = tSockets[7] + 1000 * tSockets[6];
	return tSocketNum;
}
void MyUtil::GetAnimalAbilities(int tAnimalAbility, int* s1, int* s2, int* s3, int* s4, int* s5, int* s6, int* s7, int* s8)
{
	int v9[8];
	int i;

	v9[0] = 0;
	v9[1] = 0;
	v9[2] = 0;
	v9[3] = 0;
	v9[4] = 0;
	v9[5] = 0;
	v9[6] = 0;
	v9[7] = 0;
	for (i = 0; i < 8; ++i)
	{
		v9[i] = tAnimalAbility % 10;
		tAnimalAbility /= 10;
	}
	*s8 = v9[0];
	*s7 = v9[1];
	*s6 = v9[2];
	*s5 = v9[3];
	*s4 = v9[4];
	*s3 = v9[5];
	*s2 = v9[6];
	*s1 = v9[7];
}
BOOL MyUtil::ReturnWineState(int tUserIndex, int tWine)
{
	return tWine == mUSER[tUserIndex].mAvatarInfo.aWineBottle[mUSER[tUserIndex].mAvatarInfo.aWineDrinkIndex] && mUSER[tUserIndex].mAvatarInfo.aActiveBoozeTime > 0;
}
int MyUtil::ReturnSetItemIUValue_AttackPower(int tIndex, int tIUValue, int tSort)
{
	if (tIndex != 7)
	{
		return 0;
	}
	switch (tIUValue)
	{
	case 1: return 400;
	case 2: return 800;
	case 3: return 1200;
	case 4: return 1600;
	case 5: return 2000;
	case 6: return 2400;
	case 7: return 2800;
	case 8: return 3200;
	case 9: return 3600;
	case 10: return 4000;
	case 11: return 4400;
	case 12: return 4800;
	default: return 0;
	}
}
int MyUtil::ReturnSetItemIUValue_DefensePower(int tIndex, int tIUValue, int tSort)
{
	switch (tIndex)
	{
	case 1:
		switch (tIUValue)
		{
		case 1: return 40;
		case 2: return 80;
		case 3: return 120;
		case 4: return 160;
		case 5: return 200;
		case 6: return 240;
		case 7: return 280;
		case 8: return 320;
		case 9: return 360;
		case 10: return 400;
		case 11: return 440;
		case 12: return 520;
		default: return 0;
		}
		break;
	case 2:
		switch (tIUValue)
		{
		case 1: return 300;
		case 2: return 600;
		case 3: return 900;
		case 4: return 1200;
		case 5: return 1500;
		case 6: return 1800;
		case 7: return 2100;
		case 8: return 2400;
		case 9: return 2700;
		case 10: return 3000;
		case 11: return 3300;
		case 12: return 3600;
		default: return 0;
		}
		break;
	case 3:
		switch (tIUValue)
		{
		case 1: return 50;
		case 2: return 100;
		case 3: return 150;
		case 4: return 200;
		case 5: return 250;
		case 6: return 300;
		case 7: return 350;
		case 8: return 400;
		case 9: return 450;
		case 10: return 500;
		case 11: return 550;
		case 12: return 600;
		default: return 0;
		}
		break;
	case 5:
		switch (tIUValue)
		{
		case 1: return 30;
		case 2: return 60;
		case 3: return 90;
		case 4: return 120;
		case 5: return 150;
		case 6: return 180;
		case 7: return 210;
		case 8: return 240;
		case 9: return 270;
		case 10: return 300;
		case 11: return 330;
		case 12: return 360;
		default: return 0;
		}
		break;

	default:
		return 0;
	}
}

int MyUtil::ReturnSetItemIUValue_AttackSuccess(int tIndex, int tIUValue, int tSort)
{
	if (tIndex == 3)
	{
		switch (tIUValue)
		{
		case 1: return 200;
		case 2: return 400;
		case 3: return 600;
		case 4: return 800;
		case 5: return 1000;
		case 6: return 1200;
		case 7: return 1400;
		case 8: return 1600;
		case 9: return 1800;
		case 10: return 2000;
		case 11: return 2200;
		case 12: return 2400;
		default: return 0;
		}
	}
	else if (tIndex == 7)
	{
		switch (tIUValue)
		{
		case 1: return 60;
		case 2: return 120;
		case 3: return 180;
		case 4: return 240;
		case 5: return 300;
		case 6: return 360;
		case 7: return 420;
		case 8: return 480;
		case 9: return 540;
		case 10: return 600;
		case 11: return 660;
		case 12: return 720;
		default: return 0;
		}
	}

	return 0;
}
int MyUtil::ReturnSetItemIUValue_AttackBlock(int tIndex, int tIUValue, int tSort)
{
	if (tIndex == 2)
	{
		switch (tIUValue)
		{
		case 1: return 20;
		case 2: return 40;
		case 3: return 60;
		case 4: return 80;
		case 5: return 100;
		case 6: return 120;
		case 7: return 140;
		case 8: return 160;
		case 9: return 180;
		case 10: return 200;
		case 11: return 220;
		case 12: return 240;
		default: return 0;
		}
	}
	else if (tIndex == 5)
	{
		switch (tIUValue)
		{
		case 1: return 80;
		case 2: return 160;
		case 3: return 240;
		case 4: return 320;
		case 5: return 400;
		case 6: return 480;
		case 7: return 560;
		case 8: return 640;
		case 9: return 720;
		case 10: return 800;
		case 11: return 880;
		case 12: return 960;
		default: return 0;
		}
	}

	return 0;
}
int MyUtil::ReturnSetItemIUValue_ElementAttackPower(int tIndex, int tIUValue, int tSort)
{
	if (tIndex != 4)
	{
		return 0;
	}
	switch (tIUValue)
	{
	case 1: return 40;
	case 2: return 80;
	case 3: return 120;
	case 4: return 160;
	case 5: return 200;
	case 6: return 240;
	case 7: return 280;
	case 8: return 320;
	case 9: return 360;
	case 10: return 400;
	case 11: return 440;
	case 12: return 480;
	default: return 0;
	}
}
int MyUtil::ReturnSetItemIUValue_ElementDefensePower(int tIndex, int tIUValue, int tSort)
{
	if (tIndex)
	{
		return 0;
	}
	switch (tIUValue)
	{
	case 1: return 40;
	case 2: return 80;
	case 3: return 120;
	case 4: return 160;
	case 5: return 200;
	case 6: return 240;
	case 7: return 280;
	case 8: return 320;
	case 9: return 360;
	case 10: return 400;
	case 11: return 440;
	case 12: return 480;
	default: return 0;
	}
}
int MyUtil::ReturnSet3ItemIUValue_AttackPower(int tIUValue)
{
	switch (tIUValue)
	{
	case 0: return 0;
	case 1: return 3500;
	case 2: return 4500;
	case 3: return 5500;
	case 4: return 6500;
	case 5: return 7500;
	case 6: return 8000;
	case 7: return 8500;
	case 8: return 9000;
	case 9: return 9500;
	case 10: return 10000;
	case 11: return 10500;
	case 12: return 11000;
	default: return 0;
	}
}
float MyUtil::GetRandomFloat()
{
	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_real_distribution<float> generate(0.0f, 1.0f);

	return generate(rng);
}
int MyUtil::GetRandomInt(int tNumber)
{
	if (tNumber == 0)
	{
		return -1;
	}

	std::random_device rd;
	std::mt19937 rng(rd());
	std::uniform_int_distribution<int> generate(0, tNumber - 1);

	return generate(rng);
}