#include "MainApp.h"

WORKER_FUNCTION W_FUNCTION[256];

void W_TEMP_REGISTER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (mUSER[tUserIndex].mCheckTempRegister)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	int tribe; 

	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tribe, &tPacket[(1 + MAX_USER_ID_LENGTH)], 4);

	if (strcmp(tID, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tribe < 0 || tribe > 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_0_SEND(&tID[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_TEMP_REGISTER_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUSER[tUserIndex].mCheckTempRegister = TRUE;
	mUSER[tUserIndex].mTempRegisterTribe = tribe;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mPlayUserIndex = mPLAYUSER_COM.mRecv_PlayUserIndex;
	strncpy(mUSER[tUserIndex].uID, tID, MAX_USER_ID_LENGTH);
	mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);
}

//W_REGISTER_AVATAR_SEND
void W_REGISTER_AVATAR_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if ((!mUSER[tUserIndex].mCheckTempRegister) || (mUSER[tUserIndex].mCheckValidState))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tID[MAX_USER_ID_LENGTH];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	ACTION_INFO tAction;
	CopyMemory(&tID[0], &tPacket[1], MAX_USER_ID_LENGTH);
	tID[(MAX_USER_ID_LENGTH - 1)] = '\0';
	CopyMemory(&tAvatarName[0], &tPacket[(1 + MAX_USER_ID_LENGTH)], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tAction, &tPacket[(1 + MAX_USER_ID_LENGTH + MAX_AVATAR_NAME_LENGTH)], sizeof(ACTION_INFO));
	if ((strcmp(tID, mUSER[tUserIndex].uID) != 0) || (tAction.aType != 0) || ((tAction.aSort != 0) && (tAction.aSort != 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int tLogoutInfo[6];
	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	tLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	tLogoutInfo[1] = (int)tAction.aLocation[0];
	tLogoutInfo[2] = (int)tAction.aLocation[1];
	tLogoutInfo[3] = (int)tAction.aLocation[2];
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_1_SEND(mUSER[tUserIndex].mPlayUserIndex, &tID[0], &tAvatarName[0], &tLogoutInfo[0]);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//-------------------//
	//EXAMINE_TRIBE_STATE//
	//-------------------//
	switch (mPLAYUSER_COM.mRecv_AvatarInfo.aTribe)
	{
	case 0:
		if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 1:
		if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 2:
		if (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 3:
		if ((mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 0) && (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 1) && (mPLAYUSER_COM.mRecv_AvatarInfo.aPreviousTribe != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	//-------------------//
	//-------------------//
	//-------------------//
	if (mPLAYUSER_COM.mRecv_AuthInfo.AuthType == 0)
	{
		if (((mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 + mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2) < mZONEMAININFO.ReturnMinZoneLevelInfo(mSERVER_INFO.mServerNumber)) || (mPLAYUSER_COM.mRecv_AvatarInfo.aLevel1 > mZONEMAININFO.ReturnMaxZoneLevelInfo(mSERVER_INFO.mServerNumber)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mCheckZone101TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aLevel2 > 0)
			{
				if (mPLAYUSER_COM.mRecv_AvatarInfo.aZone101TypeTime < 1)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mPLAYUSER_COM.mRecv_AvatarInfo.aZone101TypeTime--;
			}
		}
		if (mGAME.mCheckZone125Server)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aZone125TypeTime < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aZone125TypeTime--;
		}
		if (mGAME.mCheckZone126TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aPremiumService < mUTIL.ReturnNowDate())
			{
				if (mPLAYUSER_COM.mRecv_AvatarInfo.aZone126TypeTime < 1)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				mPLAYUSER_COM.mRecv_AvatarInfo.aZone126TypeTime--;
			}
		}
		if (mGAME.mCheckZone175TypeServer)
		{
			if (mGAME.mWorldInfo.mZone175TypeState[mGAME.mZone175TypeZoneIndex1][mGAME.mZone175TypeZoneIndex2] != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aNineTowerKeyNum < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aNineTowerKeyNum--;
		}
		if (mGAME.mCheckZone241TypeServer)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aLifeOrDeath < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}

			// Decrementare tichet LifeOrDeath
			mPLAYUSER_COM.mRecv_AvatarInfo.aLifeOrDeath--;
			mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath = mPLAYUSER_COM.mRecv_AvatarInfo.aLifeOrDeath;

			// Debugging pentru verificare
			printf("Tichet LifeOrDeath eliminat. Tichete rămase: %d\n", mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath);

			// Actualizare manuală în structura utilizatorului
			memcpy(&mUSER[tUserIndex].mAvatarInfo, &mPLAYUSER_COM.mRecv_AvatarInfo, sizeof(AVATAR_INFO));
		}
		if (mSERVER_INFO.mServerNumber == 234)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfBloodTime < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfBloodTime--;
		}
		if (mSERVER_INFO.mServerNumber == 235)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul1Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul1Time--;
		}
		if (mSERVER_INFO.mServerNumber == 236)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul2Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul2Time--;
		}
		if (mSERVER_INFO.mServerNumber == 237)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul3Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul3Time--;
		}
		if (mSERVER_INFO.mServerNumber == 238)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul4Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul4Time--;
		}
		if (mSERVER_INFO.mServerNumber == 239)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul5Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul5Time--;
		}
		if (mSERVER_INFO.mServerNumber == 240)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul6Time < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIslandOfSoul6Time--;
		}
		if (mSERVER_INFO.mServerNumber == 50 || mSERVER_INFO.mServerNumber == 52 || mSERVER_INFO.mServerNumber == 118)
		{
			if (mPLAYUSER_COM.mRecv_AvatarInfo.aIvyHallFishing < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mPLAYUSER_COM.mRecv_AvatarInfo.aIvyHallFishing--;
		}
	}

	mUSER[tUserIndex].mCheckValidState = TRUE;
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].uUserSort = mPLAYUSER_COM.mRecv_UserSort;
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo, &mPLAYUSER_COM.mRecv_AvatarInfo, sizeof(AVATAR_INFO));

#ifdef __IVEN_BUG_FIX__
	int iPage = 0;
	int iIndex = 0;
	int iNewPage = 0;
	int iNewIndex = 0;
	bool bItemMove = false;
	ITEM_INFO* pItemInfo = NULL;

	for (iPage = 0; iPage < 2; iPage++)
	{
		for (iIndex = 0; iIndex < MAX_INVENTORY_SLOT_NUM; iIndex++)
		{
			bItemMove = false;
			if (((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 7) || (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 7)) || ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0) || (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0)))
			{
				pItemInfo = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0]);
				if (pItemInfo == NULL)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
					continue;
				}

				if ((pItemInfo->iSort != 2) && (pItemInfo->iSort != 7) && (pItemInfo->iSort != 11))
				{
					bItemMove = true;
				}
				else if (((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] >= 8) || (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] >= 8)) || ((mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] < 0) || (mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] < 0)))
				{
					bItemMove = true;
				}
				if (bItemMove)
				{
					if (mUTIL.FindEmptyInvenForItem(tUserIndex, pItemInfo, iNewPage, iNewIndex))
					{
						if (iNewPage == iPage)
						{
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1] = iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2] = iNewIndex / 8;
						}
						else
						{
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][1] = iNewIndex % 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][2] = iNewIndex / 8;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][4] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iNewPage][iIndex][5] = mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5];
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][0] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][1] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][2] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][3] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][4] = 0;
							mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iIndex][5] = 0;
						}
					}
				}
			}
		}
	}
#endif
	if (mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] < 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = 1;
	}
	CopyMemory(mUSER[tUserIndex].mEffectValue, mPLAYUSER_COM.mRecv_EffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));

	mUSER[tUserIndex].mGeneralExperienceUpRatio = 0.0f;
	mUSER[tUserIndex].mItemDropUpRatio = 1.0f;
	mUSER[tUserIndex].mGeneralExperienceDownRatio = 1.0f;
	mUSER[tUserIndex].mSupportSkillTimeUpRatio = 1;

	mUSER[tUserIndex].mTickCountFor01Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor30Second = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01Minute = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
	mUSER[tUserIndex].mTickCountFor03Second = mGAME.mTickCount;
	mUSER[tUserIndex].mCheckMaxAttackPacketNum = 1;
	mUSER[tUserIndex].mAttackPacketSort = 0;
	mUSER[tUserIndex].mMaxAttackPacketNum = 0;
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mUSER[tUserIndex].mTickForAttackSpeed = GetTickCount();

	CopyMemory(&mUSER[tUserIndex].mAuthInfo, &mPLAYUSER_COM.mRecv_AuthInfo, sizeof(AUTH_INFO));

	mTRANSFER.B_REGISTER_AVATAR_RECV(&mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_BROADCAST_WORLD_INFO(&mGAME.mWorldInfo, &mGAME.mTribeInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_TOWER_INFO_RECV(&mGAME.mTowerInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mTRANSFER.B_FACTION_TRAP_RECV(&mGAME.mFactionTrap);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	for (index01 = 0; index01 < 500; index01++)
	{
		if (!mPROXY_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		mTRANSFER.B_PROXY_SHOP(mPROXY_OBJECT[index01].mProxyUserIndex, mPROXY_OBJECT[index01].mUniqueNumber, &mPROXY_OBJECT[index01].mProxyShopLocation[0], mPROXY_OBJECT[index01].mProxyShopAvatarName, mPROXY_OBJECT[index01].mProxyShopName, 2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	mTRANSFER.B_AVATAR_CHANGE_INFO_2(56, mGAME.mGeneralExperienceUpRatio);
	mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(57, mGAME.mItemDropUpRatio);
	mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(58, mGAME.mKillOtherTribeAddValue);
	mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);

	mAVATAR_OBJECT[tUserIndex].mCheckValidState = TRUE;
	mAVATAR_OBJECT[tUserIndex].mUniqueNumber = mGAME.mAvatarObjectUniqueNumber;
	mGAME.mAvatarObjectUniqueNumber++;
	mAVATAR_OBJECT[tUserIndex].mDATA.aVisibleState = mUSER[tUserIndex].mAvatarInfo.aVisibleState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aSpecialState = mUSER[tUserIndex].mAvatarInfo.aSpecialState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = mUSER[tUserIndex].mAvatarInfo.aGuildRole;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, mUSER[tUserIndex].mAvatarInfo.aCallName, MAX_CALL_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = mUSER[tUserIndex].mAvatarInfo.aTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPreviousTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
	mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 = mUSER[tUserIndex].mAvatarInfo.aLevel1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2 = mUSER[tUserIndex].mAvatarInfo.aLevel2;
	mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth = mUSER[tUserIndex].mAvatarInfo.aRebirth;
	mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = mUSER[tUserIndex].mAvatarInfo.aTitle;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHalo = mUSER[tUserIndex].mAvatarInfo.aUpgradeValue;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAutoHuntState = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState = mUSER[tUserIndex].mAvatarInfo.aAbsorbState;
	mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint = mUSER[tUserIndex].mAvatarInfo.aRankPoints;
	mAVATAR_OBJECT[tUserIndex].mDATA.aHornVeinShield = mUSER[tUserIndex].mAvatarInfo.aHornVeinShield;

	for (index01 = 0; index01 < MAX_EQUIP_SLOT_NUM - 8; index01++)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[index01][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[index01][2];
	}
	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4];
	mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5];

	for (index01 = 0; index01 < MAX_AVATAR_EFFECT_SORT_NUM; index01++)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[index01] = mUSER[tUserIndex].mEffectValue[index01][0];
	}

	if ((mUSER[tUserIndex].mAvatarInfo.aCostumeIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aCostumeIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = mUSER[tUserIndex].mAvatarInfo.aCostume[(mUSER[tUserIndex].mAvatarInfo.aCostumeIndex - MAX_AVATAR_ANIMAL_NUM)];
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = 0;
	}
	if ((mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM) && (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= (MAX_AVATAR_ANIMAL_NUM + MAX_AVATAR_ANIMAL_NUM - 1)))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[(mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - MAX_AVATAR_ANIMAL_NUM)];
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
	}

	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
	mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mAVATAR_OBJECT[tUserIndex].mUpdateTimeForBroadcast = GetTickCount();
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
	mAVATAR_OBJECT[tUserIndex].mGod = 0;
	mAVATAR_OBJECT[tUserIndex].mChat = 0;

	if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
	}
	mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	if (mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0)
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	if ((mUSER[tUserIndex].mAvatarInfo.aVisibleState == 1) && (mPLAYUSER_COM.mRecv_CheckFirstZone == 1) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0))
	{
		tSort = 110;
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") != 0)
	{
		memset(tData, 0, MAX_BROADCAST_DATA_SIZE);
		CopyMemory(tData, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH);
		CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(108, tData);
	}
	mUSER[tUserIndex].mHeartCheckTime = ::time(NULL);
}
//W_CLIENT_OK_FOR_ZONE_SEND
void W_CLIENT_OK_FOR_ZONE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1) 
	{
		return;
	}

	int tTribe;
	int tZoneNumber;
	time_t tCurrentTime = ::time(NULL);
	CopyMemory(&tTribe, &tPacket[1], 4);
	CopyMemory(&tZoneNumber, &tPacket[5], 4);

	if (mUSER[tUserIndex].mAvatarInfo.aTribe != tTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mSERVER_INFO.mServerNumber != tZoneNumber)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if ((tCurrentTime - mUSER[tUserIndex].mHeartCheckTime) <= 3) 
	{
		mUSER[tUserIndex].mHeartCheckCount++;
		if (mUSER[tUserIndex].mHeartCheckCount > 10) 
		{
			__LogMgr()->Log("![HACK] : %s, %s, %d, %d\n", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, (tCurrentTime - mUSER[tUserIndex].mHeartCheckTime), mUSER[tUserIndex].mHeartCheckCount);
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		return;
	}
	mUSER[tUserIndex].mHeartCheckCount = 0;
	mUSER[tUserIndex].mHeartCheckTime = tCurrentTime;

}


//W_AVATAR_ACTION_SEND
void W_AVATAR_ACTION_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	ACTION_INFO tAction;
	CopyMemory(&tAction, &tPacket[1], sizeof(ACTION_INFO));

	int index01;
	int index02;
	int tSkillSort;
	int tUseManaValue;
	int tReduceManaRatio;
	int tOtherUserIndex;

	if (!mWORK.CheckValidCharacterMotionForSend(tAction.aType, tAction.aSort, tAction.aSkillNumber, &tSkillSort, &mUSER[tUserIndex].mCheckMaxAttackPacketNum, &mUSER[tUserIndex].mAttackPacketSort, &mUSER[tUserIndex].mMaxAttackPacketNum))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mNowAttackPacketNum = 0;
	tUseManaValue = 0;
	switch (tSkillSort)
	{
	case 1:
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1))
				{
					break;
				}
			}
			if (index02 < MAX_HOT_KEY_NUM)
			{
				break;
			}
		}
		if (index01 == 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber) != tAction.aSkillGradeNum2)
		{
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber);
			/*mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;*/
		}
		break;
	case 2:
		if ((mUSER[tUserIndex].mAvatarInfo.aAutoHuntState == 1) && ((mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day > mUTIL.ReturnNowDate()) || (mUSER[tUserIndex].mAvatarInfo.aAutoHunt5Hour > 0)))
		{
			for (index01 = 0; index01 < 2; index01++)
			{
				if ((mUSER[tUserIndex].mAvatarInfo.aAutoSkillAttack[index01][0] == tAction.aSkillNumber) && (mUSER[tUserIndex].mAvatarInfo.aAutoSkillAttack[index01][1] == tAction.aSkillGradeNum1))
				{
					break;
				}
			}
			if (index01 == 2)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		else
		{
			for (index01 = 0; index01 < 3; index01++)
			{
				for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
				{
					if ((mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == tAction.aSkillNumber) && (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] == tAction.aSkillGradeNum1))
					{
						break;
					}
				}
				if (index02 < MAX_HOT_KEY_NUM)
				{
					break;
				}
			}
			if (index01 == 3)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber) != tAction.aSkillGradeNum2)
		{
			tAction.aSkillGradeNum2 = mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber);
			/*mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;*/
		}
		tUseManaValue = (int)mSKILL.ReturnSkillValue(tAction.aSkillNumber, tAction.aSkillGradeNum1, 1);
		tReduceManaRatio = mAVATAR_OBJECT[tUserIndex].GetReduceManaRatio();
		if (tReduceManaRatio > 0)
		{
			tUseManaValue -= ((tUseManaValue * tReduceManaRatio) / 100);
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue < tUseManaValue)
		{
			// mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	switch (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
	{
	case 11:
		return;
	case 12:
		if (tAction.aSort != 0)
		{
			return;
		}
		break;
	}
	if (tUseManaValue > 0)
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue -= tUseManaValue;
	}

	if (tAction.aSkillNumber != 0)
	{
		if (tAction.aSort != 16)
		{
			if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81))
			{
				if ((tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)))
				{
					tAction.aSkillGradeNum1 = mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber);
					tAction.aSkillGradeNum2 = mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber);
					/*mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;*/
				}
			}
			else
			{
				if (tAction.aSkillNumber == 76 || tAction.aSkillNumber == 77)
				{
					if (tAction.aSkillGradeNum1 > 20)
					{
						tAction.aSkillGradeNum1 = 20;
					}
					if (tAction.aSkillGradeNum2 > 2)
					{
						tAction.aSkillGradeNum2 = 2;
					}
				}
				if (tAction.aSkillNumber == 79 || tAction.aSkillNumber == 81)
				{
					if (tAction.aSkillGradeNum1 > 30)
					{
						tAction.aSkillGradeNum1 = 30;
					}
					if (tAction.aSkillGradeNum2 > 2)
					{
						tAction.aSkillGradeNum2 = 2;
					}
				}
			}
		}
	}

	float fRange = 0.0f;
	fRange = mUTIL.ReturnLengthXYZ(&tAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0]);

	if ((fRange > 666.0f) && !mAVATAR_OBJECT[tUserIndex].mCheckDeath && (mUSER[tUserIndex].mAuthInfo.AuthType == 0) && (mAVATAR_OBJECT[tUserIndex].mCheckCount < 1) && (!mGAME.mCheckZone049TypeServer) && (!mGAME.mCheckZone051TypeServer) && (!mGAME.mCheckZone053TypeServer))
	{
		mGAMELOG.GL_659_AUTO_CHECK(tUserIndex, 4, fRange);
		tAction.aLocation[0] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0];
		tAction.aLocation[1] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1];
		tAction.aLocation[2] = mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2];
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
		mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 0);
	}
	else
	{
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
		mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	}
	mAVATAR_OBJECT[tUserIndex].mCheckCount--;
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();

	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
	mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	if (mUSER[tUserIndex].mAvatarInfo.aVisibleState == 0)
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else
	{
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, tUserIndex, false);
	}
	if (tAction.aSort != 0)
	{
		return;
	}
	mUSER[tUserIndex].mTickCountFor01SecondForProtect = mGAME.mTickCount;
	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = (mAVATAR_OBJECT[tUserIndex].GetMaxLife() / 3) + 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//CHECK_VALID_CHARACTER_MOTION_FOR_SEND
BOOL MyWork::CheckValidCharacterMotionForSend(int tType, int tSort, int tSkillNumber, int* tSkillSort, int* tCheckMaxAttackPacketNum, int* tAttackPacketSort, int* tMaxAttackPacketNum)
{
	*tSkillSort = 0;
	*tCheckMaxAttackPacketNum = 1;
	*tMaxAttackPacketNum = 0;
	*tAttackPacketSort = 0;
	switch (tSort)
	{
	case 0:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 1:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 2:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 3:
		switch (tType)
		{
		case 0:
		case 2:
		case 4:
		case 6:
			return TRUE;
		}
		break;
	case 4:
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 5:
		*tMaxAttackPacketNum = 1;
		*tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 6:
		*tMaxAttackPacketNum = 2;
		*tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 7:
		*tMaxAttackPacketNum = 3;
		*tSkillSort = 0;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 1;
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 9:
		switch (tType)
		{
		case 1:
		case 3:
		case 5:
		case 7:
			return TRUE;
		}
		break;
	case 10:
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 11: //
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 12: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 13:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 14:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 15:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 16:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 17:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 18:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 20:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 21:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 22:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 23:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 30:
		*tSkillSort = 1;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 31: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 32:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	case 33:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 34: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 35: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 36: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 37: //
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 38:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 39:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 40:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 41:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 42:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 43:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 44:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 45:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 46:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 47:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 48:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 49:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 50:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 51:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 52:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 54:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 55:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 56:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 57:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 58:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 60:
		*tSkillSort = 2;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 61:
		*tSkillSort = 2;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 62:
		*tSkillSort = 2;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 63:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 64:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 65:
		*tSkillSort = 0;
		*tAttackPacketSort = 5;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 0;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 66:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 67:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 68:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 69:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 70:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 71:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 1;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 72:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 3;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 73:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 74:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 0;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 75:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 76:
		*tSkillSort = 2;
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 81:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 82:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 83:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 85:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 86:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 87:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 88:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 89:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 1;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 90:
		*tSkillSort = 2;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 4;
		*tMaxAttackPacketNum = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 91:
	case 92:
	case 93:
	case 94:
	case 95:
		switch (tType)
		{
		case 0:
			return TRUE;
		}
		break;
	case 96:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 3:
			return TRUE;
		}
		break;
	case 97:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 5:
			return TRUE;
		}
		break;
	case 98:
		*tSkillSort = 2;
		*tMaxAttackPacketNum = 5;
		*tCheckMaxAttackPacketNum = 1;
		*tAttackPacketSort = 3;
		switch (tType)
		{
		case 7:
			return TRUE;
		}
		break;
	case 255:
		*tSkillSort = 3;
		switch (tType)
		{
		case 0:
		case 1:
		case 2:
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			return TRUE;
		}
		break;
	}
	return FALSE;
}
BOOL MyWork::SkillForMotion(int tUserIndex, ACTION_INFO* pAction, int tCheckMotion)
{
	switch (pAction->aSkillNumber)
	{
#if 0
	case 6:
	case 25:
	case 44:
		return 40;
#endif
	case 7:
	case 26:
	case 45:
		pAction->aType = 0;
		pAction->aSort = 41;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 11:
	case 30:
	case 49:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1; // - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 60;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 15:
	case 34:
	case 53:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1; // - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 61;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 19:
	case 38:
	case 57:
		pAction->aType = mAVATAR_OBJECT[tUserIndex].GetWeaponClass() * 2 + 1; // - tCheckMotion;
		if (pAction->aType == 1)
			return false;
		pAction->aSort = 62;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 82:
		pAction->aType = 0;
		pAction->aSort = 66;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 83:
		pAction->aType = 0;
		pAction->aSort = 67;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 84:
		pAction->aType = 0;
		pAction->aSort = 68;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	case 103:
	case 104:
	case 105:
		pAction->aType = 0;
		pAction->aSort = 75;
		pAction->aFrame = 0.0f;
		pAction->aTargetLocation[0] = 0.0f;
		pAction->aTargetLocation[1] = 0.0f;
		pAction->aTargetLocation[2] = 0.0f;
		pAction->aTargetObjectSort = 0;
		pAction->aTargetObjectIndex = -1;
		pAction->aTargetObjectUniqueNumber = 0;
		pAction->aSkillValue = 0;
		return true;
	default:
		return false;
	}

	return false;
}
BOOL MyWork::ReturnEffectState(int tUserIndex, int tSkillNumber)
{
	switch (tSkillNumber) {
#if 0
	case 6:
	case 25:
	case 44:
		if (mUSER[tUserIndex].mEffectValue[8][0] == 0)
			return true;
		break;
#endif
	case 7:
	case 26:
	case 45:
		if (mUSER[tUserIndex].mEffectValue[4][0] == 0)
			return true;
		break;
	case 11:
	case 34:
	case 49:
		if (mUSER[tUserIndex].mEffectValue[1][0] == 0)
			return true;
		break;
	case 15:
	case 30:
	case 53:
		if (mUSER[tUserIndex].mEffectValue[0][0] == 0)
			return true;
		break;
	case 19:
	case 38:
	case 57:
		if ((mUSER[tUserIndex].mEffectValue[3][0] == 0)
			|| (mUSER[tUserIndex].mEffectValue[7][0] == 0))
			return true;
		break;
	case 82:
		if (mUSER[tUserIndex].mEffectValue[9][0] == 0)
			return true;
		break;
	case 83:
		if (mUSER[tUserIndex].mEffectValue[10][0] == 0)
			return true;
		break;
	case 84:
		if (mUSER[tUserIndex].mEffectValue[11][0] == 0)
			return true;
		break;
	case 103:
		if (mUSER[tUserIndex].mEffectValue[12][0] == 0)
			return true;
		break;
	case 104:
		if (mUSER[tUserIndex].mEffectValue[13][0] == 0)
			return true;
		break;
	case 105:
		if (mUSER[tUserIndex].mEffectValue[14][0] == 0)
			return true;
		break;
	default:
		return false;
	}
	return false;
}
//W_UPDATE_AVATAR_ACTION
void W_UPDATE_AVATAR_ACTION(int tUserIndex)
{
	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mUSER[tUserIndex].mTickForAttackSpeed = GetTickCount();

	ACTION_INFO tAction;
	CopyMemory(&tAction, &tPacket[1], sizeof(ACTION_INFO));

	switch (tAction.aSort)
	{
	case 1:
		mAVATAR_OBJECT[tUserIndex].ProcessForCreateEffectValue(&tAction);
		if (tAction.aSkillNumber == 999)
		{
			mAVATAR_OBJECT[tUserIndex].AutoBuff(1);
			tAction.aSkillNumber = 0;
		}
		break;
	case 2:
		break;
	case 19:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 31:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 32:
		break;
	case 64:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 91:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 92:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 93:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 94:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 95:
		if (tAction.aType != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mAVATAR_OBJECT[tUserIndex].mPRE_LOCATION[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];

	if (tAction.aSkillNumber != 0)
	{
		if ((tAction.aSkillNumber != 76) && (tAction.aSkillNumber != 77) && (tAction.aSkillNumber != 78) && (tAction.aSkillNumber != 79) && (tAction.aSkillNumber != 80) && (tAction.aSkillNumber != 81) && (tAction.aSkillNumber != 999))
		{
			if ((tAction.aSkillGradeNum1 > mUSER[tUserIndex].GetMaxSkillGradeNum(tAction.aSkillNumber)) || (tAction.aSkillGradeNum2 > mAVATAR_OBJECT[tUserIndex].GetBonusSkillValue(tAction.aSkillNumber)))
			{
				mGAMELOG.GL_702_CHEAT_AVATAR_ACTION(tUserIndex, tAction.aSkillNumber, tAction.aSkillGradeNum1, tAction.aSkillGradeNum2, tAction.aSkillValue);
				// mPLAYUSER_COM.U_BLOCK_USER_FOR_ZONE_1_SEND(605, &mUSER[tUserIndex].uID[0]);
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		else
		{
			if (tAction.aSkillNumber == 76 || tAction.aSkillNumber == 77)
			{
				if (tAction.aSkillGradeNum1 > 20)
				{
					tAction.aSkillGradeNum1 = 20;
				}
				if (tAction.aSkillGradeNum2 > 2)
				{
					tAction.aSkillGradeNum2 = 2;
				}
			}
			if (tAction.aSkillNumber == 79 || tAction.aSkillNumber == 81)
			{
				if (tAction.aSkillGradeNum1 > 30)
				{
					tAction.aSkillGradeNum1 = 30;
				}
				if (tAction.aSkillGradeNum2 > 2)
				{
					tAction.aSkillGradeNum2 = 2;
				}
			}
		}
	}
	CopyMemory(&mAVATAR_OBJECT[tUserIndex].mDATA.aAction, &tAction, sizeof(ACTION_INFO));
	mAVATAR_OBJECT[tUserIndex].SetSpaceIndex();
}

void W_CHANGE_AUTO_INFO(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	int tHP = 0;
	int tMP = 0;
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	CopyMemory(&tHP, &tPacket[1], 4);
	CopyMemory(&tMP, &tPacket[5], 4);

	if (tHP < 0 || tHP > 5 || tMP < 0 || tMP > 5)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aAutoLifeRatio = tHP;
	mUSER[tUserIndex].mAvatarInfo.aAutoChiRatio = tMP;
}

//W_DEMAND_ZONE_SERVER_INFO_2
void W_DEMAND_ZONE_SERVER_INFO_2(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int nCount = 0;
	int tZoneNumber;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tZoneNumber, &tPacket[5], 4);

	if ((tZoneNumber < MIN_VALID_ZONE_NUMBER) || (tZoneNumber > MAX_VALID_ZONE_NUMBER) || (tZoneNumber == mSERVER_INFO.mServerNumber))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tZoneNumber)
	{
	case 200:
		if (mGAME.mWorldInfo.mZone200TypeState != 1)
		{
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(3, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		break;

	case 88:
		if (mGAME.mZone88BattleState2 != 2)
		{
			mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(3, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		break;

	default:
		break;
	}
	switch (tSort)
	{
	case  2: //[GM]::[MOVEZONE]
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAuthInfo.MoveZoneFlag == 0) 
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case  3: //[DEATH]
		break;
	case  4: //[PORTAL]
		break;
	case  5: //[NPC(MONEY)]
		break;
	case  6: //[NPC(MOVE)]
		break;
	case  7: //[RETURN]
		break;
	case  8: //[RETURN(ITEM)]
		break;
	case  9: //[MOVE(ITEM)] // 이동서
		break;
	case 10: //[NPC(지존알현)]
		break;
	case 11: //[AUTO_TO_ZONE_037]
		break;
	case 12://Zone 84
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAuthInfo.UZonemoveFlag == 1)
	{
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(1, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (!strcmp(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], "0.0.0.0")) 
	{
		mCENTER_COM.W_ZONE_OTHER_CONNECTION_INFO(tZoneNumber);
		while (1)
		{
			if (strcmp(mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)], "0.0.0.0") != 0) 
			{
				goto RESULT;
			}
			if (nCount > 100) 
			{
				break;
			}
			nCount++;
			Sleep(10);
		}
		mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(1, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
RESULT:
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_3_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, &mUSER[tUserIndex].mAuthInfo);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mRegisterTime = GetTickCount();
	mUSER[tUserIndex].mMoveZoneResult = 1;
	mTRANSFER.B_DEMAND_ZONE_SERVER_INFO_2_RESULT(0, &mGAME.mZoneConnectionInfo.mIP[(tZoneNumber - 1)][0], mGAME.mZoneConnectionInfo.mPort[(tZoneNumber - 1)]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FAIL_MOVE_ZONE_2_SEND
void W_FAIL_MOVE_ZONE_2_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mMoveZoneResult = 0;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
	mUSER[tUserIndex].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
	mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_2_SEND(mUSER[tUserIndex].mPlayUserIndex, &mUSER[tUserIndex].uID[0], &mUSER[tUserIndex].mAvatarInfo, mUSER[tUserIndex].mEffectValue, &mUSER[tUserIndex].mAuthInfo);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mRegisterTime = GetTickCount();
}

//W_USE_HOTKEY_ITEM_SEND
void W_USE_HOTKEY_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	CopyMemory(&tPage, &tPacket[1], 4);
	CopyMemory(&tIndex, &tPacket[5], 4);
	if ((tPage < 0) || (tPage > 2) || (tIndex < 0) || (tIndex > (MAX_HOT_KEY_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mEffectValue[16][0] > 0)
	{
		mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	ITEM_INFO* tITEM_INFO;
	int tGainLifeValue;
	int tGainManaValue;
	int tGainPatActivityValue;
	int tGainMountActivityValue;
	int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM];

	switch (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2])
	{
	case 3:
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 38))
		{
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0]);
		if (tITEM_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO->iSort != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tGainLifeValue = 0;
		tGainManaValue = 0;
		tGainPatActivityValue = 0;
		switch (tITEM_INFO->iPotionType[0])
		{
		case 1:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = tITEM_INFO->iPotionType[1];
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			break;
		case 2:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			break;
		case 3:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainManaValue = tITEM_INFO->iPotionType[1];
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 4:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainManaValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 5:
			if (!mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue >= mAVATAR_OBJECT[tUserIndex].GetMaxLife()) && (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue >= mAVATAR_OBJECT[tUserIndex].GetMaxMana()))
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainLifeValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxLife() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue + tGainLifeValue) > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
			{
				tGainLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife() - mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue;
			}
			tGainManaValue = (int)((float)(mAVATAR_OBJECT[tUserIndex].GetMaxMana() * tITEM_INFO->iPotionType[1]) * 0.01f);
			if ((mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue + tGainManaValue) > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
			{
				tGainManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana() - mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue;
			}
			break;
		case 6:
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][0] < 1)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] >= MAX_PAT_ACTIVITY_SIZE)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			tGainPatActivityValue = tITEM_INFO->iPotionType[1];
			if ((mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] + tGainPatActivityValue) >= MAX_PAT_ACTIVITY_SIZE)
			{
				tGainPatActivityValue = MAX_PAT_ACTIVITY_SIZE - mUSER[tUserIndex].mAvatarInfo.aEquip[8][1];
			}
			break;
		case 9:
			break;

		case 12: // Poison
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;

			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].mEffectValue[15][0] = 3;
			mUSER[tUserIndex].mEffectValue[15][1] = 40;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[15] = mUSER[tUserIndex].mEffectValue[15][0];
			tEffectValueState[15] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;
		case 13:
			break;
		case 14: //[Attack Rate  Pill]
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].mEffectValue[17][0] = 25;
			mUSER[tUserIndex].mEffectValue[17][1] = 60;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[17] = mUSER[tUserIndex].mEffectValue[17][0];
			tEffectValueState[17] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;

		case 15: //[Dodge  Pill]
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUSER[tUserIndex].mEffectValue[18][0] = 25;
			mUSER[tUserIndex].mEffectValue[18][1] = 60;
			mAVATAR_OBJECT[tUserIndex].mDATA.aEffectValueForView[18] = mUSER[tUserIndex].mEffectValue[18][0];
			tEffectValueState[18] = 1;
			mTRANSFER.B_AVATAR_EFFECT_VALUE_INFO(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, mUSER[tUserIndex].mEffectValue, &tEffectValueState[0]);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;

		case 16: //[Mount Feed]
			if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] >= 100000000)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			if (mUTIL.ReturnMountSort(mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber) == 30)
			{
				mTRANSFER.B_USE_HOTKEY_ITEM_RECV(1, tPage, tIndex);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
			}
			mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			tGainMountActivityValue = tITEM_INFO->iPotionType[1] * 1000000;
			/*if ((mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] + tGainMountActivityValue) > 100100000)
			{
				tGainMountActivityValue =  mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 1000000 - mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] + 100000000;
			}*/
			mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] += tGainMountActivityValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(71, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;

		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1]--;
		if (mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aHotKey[tPage][tIndex][2] = 0;
		}
		mTRANSFER.B_USE_HOTKEY_ITEM_RECV(0, tPage, tIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (tGainLifeValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue += tGainLifeValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(10, mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (tGainManaValue > 0)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue += tGainManaValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(11, mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		if (tGainPatActivityValue > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aEquip[8][1] += tGainPatActivityValue;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(12, mUSER[tUserIndex].mAvatarInfo.aEquip[8][1]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_USE_INVENTORY_ITEM_SEND
void W_USE_INVENTORY_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage;
	int tIndex;
	int tValue;

	CopyMemory(&tPage, &tPacket[1], 4);
	CopyMemory(&tIndex, &tPacket[5], 4);
	CopyMemory(&tValue, &tPacket[9], 4);

	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;
	SKILL_INFO* tSKILL_INFO;
	int tEquipIndex;
	int tEquip[4];
	int tEquipSocket[MAX_SOCKETSYSTEM_ARRAY];
	int tItemLLevel;
	int tItemHLevel;
	int tTribeItemList[9];
	int tRandomValue;
	int tItemType;
	int tItemSort;
	int tSearchNum;
	int tMoney;
	int iInvenSlot = 0;
	int iPage = 0;
	int iInvenIndex = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tTowerSort;
	int tTowerInfo;
	int tValueHolder[8];
	std::vector<int> tItem;
	float tChance = 0.0f;
	int tDropIdx = 0;

	int tNewValue[6];

	ZeroMemory(tBroadcastInfoData, sizeof(tBroadcastInfoData));

	if (tPage == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);
	if (tITEM_INFO == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tITEM_INFO->iSort)
	{
	case 5: //[무공비급]
		if (tITEM_INFO->iEquipInfo[0] != 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe != (tITEM_INFO->iEquipInfo[0] - 2))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2) < (tITEM_INFO->iLevelLimit + tITEM_INFO->iMartialLevelLimit))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == tITEM_INFO->iGainSkillNumber)
			{
				break;
			}
		}
		if (index01 < MAX_SKILL_SLOT_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tSKILL_INFO = mSKILL.Search(tITEM_INFO->iGainSkillNumber);
		if (tSKILL_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkillPoint < tSKILL_INFO->sLearnSkillPoint)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tSKILL_INFO->sType)
		{
		case 1:
			for (index01 = 0; index01 < 10; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 10)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			for (index01 = 20; index01 < 30; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 30)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		case 4:
			for (index01 = 10; index01 < 20; index01++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
				{
					break;
				}
			}
			if (index01 == 20)
			{
				for (index01 = 30; index01 < 40; index01++)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
					{
						break;
					}
				}
				if (index01 == 40)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint -= tSKILL_INFO->sLearnSkillPoint;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = tSKILL_INFO->sIndex;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = tSKILL_INFO->sLearnSkillPoint;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 6:
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
	case 22:
	case 28:
	case 29:
	case 31:
	case 32:
	case 33:
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2), mUSER[tUserIndex].mAvatarInfo.aRebirth))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquipIndex = tITEM_INFO->iEquipInfo[1] - 2;
		if ((tEquipIndex < 0) || (tEquipIndex > ((MAX_EQUIP_SLOT_NUM - 8) - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquip[0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		tEquip[1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1];
		tEquip[2] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		tEquip[3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			tEquipSocket[index01] = mUSER[tUserIndex].mAvatarInfo.aEquipSocket[tEquipIndex][index01];
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			mUSER[tUserIndex].mAvatarInfo.aEquipSocket[tEquipIndex][index01] = mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][index01];
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		mAVATAR_OBJECT[tUserIndex].mDATA.aEquipForView[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tEquip[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tEquip[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tEquip[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tEquip[3];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][index01] = tEquipSocket[index01];
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = 2 * mAVATAR_OBJECT[tUserIndex].GetWeaponClass();
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}
		if (tEquipIndex == 7)
		{
			mAVATAR_OBJECT[tUserIndex].ProcessForDeleteEffectValue();
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 23:
	case 24:
		for (index01 = 0; index01 < 14; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aCombineSkills[tITEM_INFO->iSort - 23][index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < 14)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 14; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aCombineSkills[tITEM_INFO->iSort - 23][index01] == 0)
			{
				break;
			}
		}
		if (index01 == 14)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aCombineSkills[tITEM_INFO->iSort - 23][index01] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 26:
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aWineBottle[index01] == tITEM_INFO->iIndex && mUSER[tUserIndex].mAvatarInfo.aWineBottle1Quantity[index01] > 0)
			{
				mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		for (tValue = 0; tValue < 10; tValue++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aWineBottle1Quantity[tValue] == 0)
			{
				break;
			}
		}
		if (tValue == 10)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aWineBottle[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aWineBottle1Quantity[tValue] = 30;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 34:
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2), mUSER[tUserIndex].mAvatarInfo.aRebirth))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquipIndex = tITEM_INFO->iEquipInfo[1] - 2;
		if ((tEquipIndex < 13) || (tEquipIndex > MAX_EQUIP_SLOT_NUM))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tEquip[0] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0];
		tEquip[1] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1];
		tEquip[2] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2];
		tEquip[3] = mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			tEquipSocket[index01] = mUSER[tUserIndex].mAvatarInfo.aEquipSocket[tEquipIndex][index01];
		}
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aEquip[tEquipIndex][3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			mUSER[tUserIndex].mAvatarInfo.aEquipSocket[tEquipIndex][index01] = mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][index01];
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tEquip[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tEquip[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tEquip[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tEquip[3];
		for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][index01] = tEquipSocket[index01];
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = 2 * mAVATAR_OBJECT[tUserIndex].GetWeaponClass();
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 35:
	case 36:
		if (!mUTIL.CheckPossibleEquipItem(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, -1, (mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2), mUSER[tUserIndex].mAvatarInfo.aRebirth))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aCostume[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 10; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aCostume[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mUSER[tUserIndex].mAvatarInfo.aCostume[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aLegendaryCostume[tValue] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].GetMaxLife())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].GetMaxMana())
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	// ITEM
	switch (tITEM_INFO->iIndex)
	{
	case 1017: //[Health Elixir]
	case 506:
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1018: //[CHI Elixir]
	case 507:
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1026: //[Return Scroll]
		if (124 == mSERVER_INFO.mServerNumber)
			return;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
		mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1301:
	case 1302:
	case 1303:
	case 1304:
	case 1305:
	case 1306:
	case 1307:
	case 1308:
	case 1309:
	case 1313:
	case 1314:
	case 1315:
	case 1316:
	case 1317:
	case 1318:
	case 1319:
	case 1320:
	case 1321:
	case 1322:
	case 1323:
	case 1324:
	case 1325:
	case 1326:
	case 1327:
	case 1328:
	case 1329:
	case 1330:
	case 1331:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = index01;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1109: // TELEPORT-SCROLL
	case 1224: //[Dungeon Teleport Scroll
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
		mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 578: //[Elemental Damage Elixir]
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion += 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 579: //[Elemental Defense Elixir]
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 636: //[Health Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion += 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 637: //[Chi Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion += 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 638: //[Strength Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion += 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 639: //[Agility Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion += 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 640: //[E Dmg Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion += 10000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 641: //[E Def Elixir x10]
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion += 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 651: //[Max Elixir Set All Elixir to 200]
		mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion = 200;
		mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion = 200;
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion = 200;
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion = 200;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 691: //[CP Ticket (5)]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 692: //[CP Ticket (10)]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 10;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 10;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 693: //[CP Ticket (15)]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 15;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 15;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 694: //[CP Ticket (20)]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 20;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 20;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 801: //[Refined Elixir HP]
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aEatLifePotion > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatLifePotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 802: //[Refined Chi HP]
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aEatManaPotion > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatManaPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 803: //[Refined Str HP]
		if (mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 804: //[Refined Dex HP]
		if (mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 805: //[Refined E Dmg Elixir]
		if ((mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion / 1000) < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion / 1000) > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion += 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 806: //[Refined E Def Elixir]
		if ((mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion % 1000) < 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion % 1000) > 300)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatElementAtkDefPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1027: //[Book of Amnesia]
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
			{
				continue;
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 0;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
			}
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1035: //[Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
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
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif
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
		tRandomValue = rand() % 10000;
		if (tRandomValue < 1)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 300)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[tRandomValue % 9];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
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
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000001);
		if (tITEM_INFO->iType == 4)
		{
			mGAMELOG.GL_607_GAIN_SIN_ITEM(tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000001);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000001;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1036: //[Big Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
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
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif

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
		tRandomValue = rand() % 10000;
		if (tRandomValue < 2)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 400)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[(tRandomValue % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
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
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000002);
		if (tITEM_INFO->iType == 4)
		{
			mGAMELOG.GL_607_GAIN_SIN_ITEM(tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000002);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000002;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1037: //[God Lucky Ticket]
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
#endif
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
#ifdef __GOD__
		}
		else
		{
			tItemLLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
			tItemHLevel = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2;
		}

#endif
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
		tRandomValue = rand() % 10000;
		if (tRandomValue < 3)
		{
			tItemType = 4;
		}
		else if (tRandomValue < 500)
		{
			tItemType = 3;
		}
		else if (tRandomValue < 9000)
		{
			tItemType = 2;
		}
		else
		{
			tItemType = 1;
		}
		tRandomValue = rand();
		tItemSort = tTribeItemList[(tRandomValue % 9)];
		tSearchNum = 0;
		while (tSearchNum < 10)
		{
			tRandomValue = rand();
			tITEM_INFO = mITEM.Return((tItemLLevel + (tRandomValue % (tItemHLevel - tItemLLevel + 1))), tItemType, tItemSort);
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
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tValue = tITEM_INFO->iIndex;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tValue, 0, 0, 100000003);
		if (tITEM_INFO->iType == 4)
		{
			mGAMELOG.GL_607_GAIN_SIN_ITEM(tUserIndex, 1, tITEM_INFO->iIndex, 0, 0, 100000003);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 100000003;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1041: //[Superior Pill]
	case 1421:
		mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime2 += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1045: //[Fortune Pouch]
		tMoney = (1000 + rand() % 4001) * 100;
		if (mUTIL.CheckOverMaximum(mUSER[tUserIndex].mAvatarInfo.aMoney, tMoney))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney += tMoney;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 1, tMoney, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1047: //[Solemn Grounds Ticket]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aZone101TypeTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1048: //[Labyrinth Key]
		mUSER[tUserIndex].mAvatarInfo.aNineTowerKeyNum++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1049: //[Taiyan Key]
		mUSER[tUserIndex].mAvatarInfo.aZone125TypeTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMoney, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1066: //[Book of Clear Fog]
		if ((tValue < 0) || (tValue > (MAX_SKILL_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint += mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1];
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1075: //[Guanyin Catapult]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(543, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1076: //[Fujin Catapult]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(544, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1077: //[Jinong Catapult]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(545, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1078: //[Nangin Catapult]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0) || (mUSER[tUserIndex].mAvatarInfo.aTribe != 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mSERVER_INFO.mServerNumber != 2) && (mSERVER_INFO.mServerNumber != 3) && (mSERVER_INFO.mServerNumber != 4) && (mSERVER_INFO.mServerNumber != 7) && (mSERVER_INFO.mServerNumber != 8) && (mSERVER_INFO.mServerNumber != 9) && (mSERVER_INFO.mServerNumber != 12) && (mSERVER_INFO.mServerNumber != 13) && (mSERVER_INFO.mServerNumber != 14) && (mSERVER_INFO.mServerNumber != 141) && (mSERVER_INFO.mServerNumber != 142) && (mSERVER_INFO.mServerNumber != 143))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mSUMMON.SummonMonsterForTribeWeapon(546, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1092: //[Strength Elixir x1]
	case 509:
		if (mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatStrengthPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1093: //[Agility Elixir x1]
	case 508:
		if (mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion >= 200)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aEatAgilityPotion++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1097: //[Solemn Ground Ticket 2Hours]
		mUSER[tUserIndex].mAvatarInfo.aZone101TypeTime += 120;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1098: //[Solemn Ground Ticket 1 Hour]
		mUSER[tUserIndex].mAvatarInfo.aZone101TypeTime += 60;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tNewValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		tNewValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
		tNewValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
		tNewValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		tNewValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		tNewValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		mTRANSFER.B_SEND_ITEM_NEW(0, tPage, tIndex, tNewValue[0], tNewValue[1], tNewValue[2], tNewValue[3], tNewValue[4], tNewValue[5]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1103: //[Protection Charm]
	case 1455:
		mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		
		
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3]--;
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] < 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		tNewValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0];
		tNewValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
		tNewValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
		tNewValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
		tNewValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
		tNewValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
		mTRANSFER.B_SEND_ITEM_NEW(0, tPage, tIndex, tNewValue[0], tNewValue[1], tNewValue[2], tNewValue[3], tNewValue[4], tNewValue[5]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1104: //[Skill Reset Book Again]
		for (index01 = 0; index01 < MAX_SKILL_SLOT_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] < 1)
			{
				continue;
			}
			mUSER[tUserIndex].mAvatarInfo.aSkillPoint += (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] - 1);
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 1;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
			}
		}
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1105: //[Another Skill Reset Book]
		if ((tValue < 0) || (tValue > (MAX_SKILL_SLOT_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 3; index01++)
		{
			for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
			{
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 1)
				{
					continue;
				}
				if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
				{
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
				}
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aSkillPoint += (mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] - 1);
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][1] = 1;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1108: //[Protection Scroll]
		mUSER[tUserIndex].mAvatarInfo.aProtectForDeath += 20;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1171: //[Full Appearance Change Scroll]
		mUSER[tUserIndex].mAvatarInfo.aGender = ((tValue % 10) - 1);
		mUSER[tUserIndex].mAvatarInfo.aHeadType = (((tValue % 100) / 10) - 1);
		mUSER[tUserIndex].mAvatarInfo.aFaceType = ((tValue / 100) - 1);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].mDATA.aGender = mUSER[tUserIndex].mAvatarInfo.aGender;
		mAVATAR_OBJECT[tUserIndex].mDATA.aHeadType = mUSER[tUserIndex].mAvatarInfo.aHeadType;
		mAVATAR_OBJECT[tUserIndex].mDATA.aFaceType = mUSER[tUserIndex].mAvatarInfo.aFaceType;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(mAVATAR_OBJECT[tUserIndex].mIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 90, mUSER[tUserIndex].mAvatarInfo.aGender, mUSER[tUserIndex].mAvatarInfo.aHeadType, mUSER[tUserIndex].mAvatarInfo.aFaceType);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
		return;

	case 1118: //[Scroll of Loyalty]
		mUSER[tUserIndex].mAvatarInfo.aDoubleKillNumTime += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1119: //[Scroll of Battle]
		mUSER[tUserIndex].mAvatarInfo.aDoubleKillExpTime += 30;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1120: //[Scroll of the Gods]
		mUSER[tUserIndex].mAvatarInfo.aDoubleKillExpTime += 30;
		mUSER[tUserIndex].mAvatarInfo.aDoubleKillNumTime += 30;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1121: //[Experience Potion x2 for L1-112]
	case 1122:
	case 1123:
		return;

	case 1124: //[Scroll of Seekers]
		mUSER[tUserIndex].mAvatarInfo.aZone126TypeTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1125: //[Luxury Chest]
		return;

	case 1102: //[Hermits Chest]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 798: //[Storage Chest 7d]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 799: //[Random Elixir Box]
		tRandomValue = rand() % 6;
		switch (tRandomValue)
		{
		case 0:
			tValue = 1017;
			break;
		case 1:
			tValue = 1018;
			break;
		case 2:
			tValue = 1092;
			break;
		case 3:
			tValue = 1093;
			break;
		case 4:
			tValue = 578;
			break;
		case 5:
			tValue = 579;
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 807:
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate = tValue;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1130: //[Storage Chest]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 7);
		if (tValue == -1)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate = tValue;
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1132: //[Double Buff Time]
		mUSER[tUserIndex].mAvatarInfo.aDoubleBuffTime += 60;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1134: //[Stat Reset L1-99]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 1) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit + mUSER[tUserIndex].mAvatarInfo.aStr + mUSER[tUserIndex].mAvatarInfo.aInt + mUSER[tUserIndex].mAvatarInfo.aDex - 4);
		mUSER[tUserIndex].mAvatarInfo.aVit = 1;
		mUSER[tUserIndex].mAvatarInfo.aStr = 1;
		mUSER[tUserIndex].mAvatarInfo.aInt = 1;
		mUSER[tUserIndex].mAvatarInfo.aDex = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1135: //[Stat Reset L100-112]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit + mUSER[tUserIndex].mAvatarInfo.aStr + mUSER[tUserIndex].mAvatarInfo.aInt + mUSER[tUserIndex].mAvatarInfo.aDex - 4);
		mUSER[tUserIndex].mAvatarInfo.aVit = 1;
		mUSER[tUserIndex].mAvatarInfo.aStr = 1;
		mUSER[tUserIndex].mAvatarInfo.aInt = 1;
		mUSER[tUserIndex].mAvatarInfo.aDex = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1136: //[Stat Reset M1-33]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit + mUSER[tUserIndex].mAvatarInfo.aStr + mUSER[tUserIndex].mAvatarInfo.aInt + mUSER[tUserIndex].mAvatarInfo.aDex - 4);
		mUSER[tUserIndex].mAvatarInfo.aVit = 1;
		mUSER[tUserIndex].mAvatarInfo.aStr = 1;
		mUSER[tUserIndex].mAvatarInfo.aInt = 1;
		mUSER[tUserIndex].mAvatarInfo.aDex = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1137: //[Stat Reset One only L1-99]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 1) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 99))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStr - 1);
			mUSER[tUserIndex].mAvatarInfo.aStr = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aDex - 1);
			mUSER[tUserIndex].mAvatarInfo.aDex = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit - 1);
			mUSER[tUserIndex].mAvatarInfo.aVit = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aInt - 1);
			mUSER[tUserIndex].mAvatarInfo.aInt = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1138: //[Stat Reset One Only L100-112
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 100) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 112))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStr - 1);
			mUSER[tUserIndex].mAvatarInfo.aStr = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aDex - 1);
			mUSER[tUserIndex].mAvatarInfo.aDex = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit - 1);
			mUSER[tUserIndex].mAvatarInfo.aVit = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aInt - 1);
			mUSER[tUserIndex].mAvatarInfo.aInt = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1139: //[Stat Reset One Only M1-33]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 145))
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
#ifdef __GOD__
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
#endif
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStr - 1);
			mUSER[tUserIndex].mAvatarInfo.aStr = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aDex - 1);
			mUSER[tUserIndex].mAvatarInfo.aDex = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit - 1);
			mUSER[tUserIndex].mAvatarInfo.aVit = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aInt - 1);
			mUSER[tUserIndex].mAvatarInfo.aInt = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1140: //[Storage Vault 60Days]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate, 60);
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate += tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1141: //[Hermits Chest 60Days]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate, 60);
		mUSER[tUserIndex].mAvatarInfo.aExpandStoreDate += tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1142: //[God Reset Stat]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit + mUSER[tUserIndex].mAvatarInfo.aStr + mUSER[tUserIndex].mAvatarInfo.aInt + mUSER[tUserIndex].mAvatarInfo.aDex - 4);
		mUSER[tUserIndex].mAvatarInfo.aVit = 1;
		mUSER[tUserIndex].mAvatarInfo.aStr = 1;
		mUSER[tUserIndex].mAvatarInfo.aInt = 1;
		mUSER[tUserIndex].mAvatarInfo.aDex = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1143: //[God Reset Stats One Only]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tValue < 1) || (tValue > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aStr - 1);
			mUSER[tUserIndex].mAvatarInfo.aStr = 1;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aDex - 1);
			mUSER[tUserIndex].mAvatarInfo.aDex = 1;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit - 1);
			mUSER[tUserIndex].mAvatarInfo.aVit = 1;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aInt - 1);
			mUSER[tUserIndex].mAvatarInfo.aInt = 1;
			break;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_605_USE_CASH_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5]);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1145: //[SBF]
		mUSER[tUserIndex].mAvatarInfo.aAnimalTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalTime, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1146: //[Lucky Combine L]
		mUSER[tUserIndex].mAvatarInfo.aLuckyCombine += 3;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1147: //[Lucky Combine M]
		mUSER[tUserIndex].mAvatarInfo.aLuckyCombine += 2;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1148: //[Lucky Combine S]
		mUSER[tUserIndex].mAvatarInfo.aLuckyCombine += 1;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1149: //[Lucky Upgrade]
		mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade += 3;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1150: //[Lucky Upgrade M]
		mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade += 2;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1151: //[Lucky Upgrade S]
		mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade += 1;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1152: //[Lucky Drop L]
		mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1153: //[Lucky Drop M]
		mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime += 120;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1154: //[Lucky Drop S]
		mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime += 60;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1166: //[CP Protection Charm]
	case 17033:
		mUSER[tUserIndex].mAvatarInfo.aCPProtectionCharm++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1188: //[CP Protection Charm x3]
		mUSER[tUserIndex].mAvatarInfo.aCPProtectionCharm += 3;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1190: //[Pet Exp Boost Scroll]
		mUSER[tUserIndex].mAvatarInfo.aPat_Exp_x2_Time += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1222: //[Mount Absorb (S)
		mUSER[tUserIndex].mAvatarInfo.aMountAbsorbTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.aMountAbsorbTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1237: //[Wing PC]
		mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1436: //[Exp Pill L]
	case 1458:
		mUSER[tUserIndex].mAvatarInfo.aExpPill += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1438: //[Exp Pill M]
		mUSER[tUserIndex].mAvatarInfo.aExpPill += 108;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1439: //[Exp Pill S]
		mUSER[tUserIndex].mAvatarInfo.aExpPill += 36;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1444: //[CP Chest]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 500;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 500;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1447: //[CP Charm L]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 1000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 1000;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1448: //[CP Charm M]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 500;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 500;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1449: //[CP Charm S]
	case 17139:
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 100;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 100;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1499: //[CP Charm XL]
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5000;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1191: //[Damage Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1192: //[Damage Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll += 90;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1193: //[Damage Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(46, mUSER[tUserIndex].mAvatarInfo.aDamageBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1194: //[Health Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1195: //[Health Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll += 90;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1196: //[Health Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(47, mUSER[tUserIndex].mAvatarInfo.aHealthBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1197: //[Critical Boost Scroll L]
		mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1198: //[Critical Boost Scroll M]
		mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll += 90;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1199: //[Critical Boost Scroll S]
		mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(48, mUSER[tUserIndex].mAvatarInfo.aCriticalBoostScroll);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1434: //[LoD Ticket]
		mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 593: //[Preserve Charm]
		mUSER[tUserIndex].mAvatarInfo.aPreventRefineBreak++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1167: //[Gold Plate Scroll]
		mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime += 240;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(40, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1370: //[Silver Plate Scroll]
		mUSER[tUserIndex].mAvatarInfo.iSilverOrnamentRemainsTime += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(40, mUSER[tUserIndex].mAvatarInfo.iGoldOrnamentRemainsTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1371: //[IOB]
		if (mUSER[tUserIndex].mAvatarInfo.aDoubleIslandOfBloodTimeUse > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aIslandOfBloodTime += 60;
			mUSER[tUserIndex].mAvatarInfo.aDoubleIslandOfBloodTimeUse--;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aIslandOfBloodTime += 30;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1372: // [IOS1]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul1Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1373: //[IOS2]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul2Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1374: //[IOS3]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul3Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1375: //[IOS4]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul4Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1376: //[IOS5]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul5Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1377: //[IOS6]
		mUSER[tUserIndex].mAvatarInfo.aIslandOfSoul6Time += 30;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1201: //[Auto Buff 7D]
	case 2021:
	case 1215: //[Auto Buff 30D]
	case 1216: //[Auto Buff 1D]
		switch (tITEM_INFO->iIndex)
		{
		case 1201:
		case 2021:
			tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoBuffScroll, 7);
			break;
		case 1215:
			tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoBuffScroll, 30);
			break;
		case 1216:
			tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoBuffScroll, 1);
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aAutoBuffScroll = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 574: //[Auto Hunt 5h]
		mUSER[tUserIndex].mAvatarInfo.aAutoHunt5Hour += 300;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(62, mUSER[tUserIndex].mAvatarInfo.aAutoHunt5Hour);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 610: //[Auto Hunt 7D]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day, 7);
		mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(61, mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 686: //[Another Auto Hunt 7D]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day, 7);
		mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(61, mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 687: //[Auto Hunt 15D]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day, 15);
		mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(61, mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1217: //[Auto Hunt 30D]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day, 30);
		mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(61, mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1187: //[SOS 15H]
	case 7016:
		mUSER[tUserIndex].mAvatarInfo.aZone126TypeTime += 900;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 613: //[Mount Absorb 60mins]
		mUSER[tUserIndex].mAvatarInfo.aMountAbsorbTime += 60;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(78, mUSER[tUserIndex].mAvatarInfo.aMountAbsorbTime);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1378: //[Heaven Chest]
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87077; break;
				case 1: tDropIdx = 87078; break;
				case 2: tDropIdx = 87079; break;
				case 3: tDropIdx = 87080; break;
				case 4: tDropIdx = 87081; break;
				case 5: tDropIdx = 87082; break;
				case 6: tDropIdx = 87083; break;
				case 7: tDropIdx = 87084; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(14))
				{
				case 0: tDropIdx = 87063; break;
				case 1: tDropIdx = 87064; break;
				case 2: tDropIdx = 87065; break;
				case 3: tDropIdx = 87066; break;
				case 4: tDropIdx = 87067; break;
				case 5: tDropIdx = 87068; break;
				case 6: tDropIdx = 87069; break;
				case 7: tDropIdx = 87070; break;
				case 8: tDropIdx = 87071; break;
				case 9: tDropIdx = 87072; break;
				case 10: tDropIdx = 87073; break;
				case 11: tDropIdx = 87074; break;
				case 12: tDropIdx = 87075; break;
				case 13: tDropIdx = 87076; break;
				}
			}
			break;

		case 1:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87099; break;
				case 1: tDropIdx = 87100; break;
				case 2: tDropIdx = 87101; break;
				case 3: tDropIdx = 87102; break;
				case 4: tDropIdx = 87103; break;
				case 5: tDropIdx = 87104; break;
				case 6: tDropIdx = 87105; break;
				case 7: tDropIdx = 87106; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(14))
				{
				case 0: tDropIdx = 87085; break;
				case 1: tDropIdx = 87086; break;
				case 2: tDropIdx = 87087; break;
				case 3: tDropIdx = 87088; break;
				case 4: tDropIdx = 87089; break;
				case 5: tDropIdx = 87090; break;
				case 6: tDropIdx = 87091; break;
				case 7: tDropIdx = 87092; break;
				case 8: tDropIdx = 87093; break;
				case 9: tDropIdx = 87094; break;
				case 10: tDropIdx = 87095; break;
				case 11: tDropIdx = 87096; break;
				case 12: tDropIdx = 87097; break;
				case 13: tDropIdx = 87098; break;
				}
			}
			break;

		case 2:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87121; break;
				case 1: tDropIdx = 87122; break;
				case 2: tDropIdx = 87123; break;
				case 3: tDropIdx = 87124; break;
				case 4: tDropIdx = 87125; break;
				case 5: tDropIdx = 87126; break;
				case 6: tDropIdx = 87127; break;
				case 7: tDropIdx = 87128; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(14))
				{
				case 0: tDropIdx = 87107; break;
				case 1: tDropIdx = 87108; break;
				case 2: tDropIdx = 87109; break;
				case 3: tDropIdx = 87110; break;
				case 4: tDropIdx = 87111; break;
				case 5: tDropIdx = 87112; break;
				case 6: tDropIdx = 87113; break;
				case 7: tDropIdx = 87114; break;
				case 8: tDropIdx = 87115; break;
				case 9: tDropIdx = 87116; break;
				case 10: tDropIdx = 87117; break;
				case 11: tDropIdx = 87118; break;
				case 12: tDropIdx = 87119; break;
				case 13: tDropIdx = 87120; break;
				}
			}
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tDropIdx;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tDropIdx, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1379: //[Earth Chest]
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87013; break;
				case 1: tDropIdx = 87014; break;
				case 2: tDropIdx = 87015; break;
				case 3: tDropIdx = 87016; break;
				case 4: tDropIdx = 87017; break;
				case 5: tDropIdx = 87018; break;
				case 6: tDropIdx = 87019; break;
				case 7: tDropIdx = 87020; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(13))
				{
				case 0: tDropIdx = 87000; break;
				case 1: tDropIdx = 87001; break;
				case 2: tDropIdx = 87002; break;
				case 3: tDropIdx = 87003; break;
				case 4: tDropIdx = 87004; break;
				case 5: tDropIdx = 87005; break;
				case 6: tDropIdx = 87006; break;
				case 7: tDropIdx = 87007; break;
				case 8: tDropIdx = 87008; break;
				case 9: tDropIdx = 87009; break;
				case 10: tDropIdx = 87010; break;
				case 11: tDropIdx = 87011; break;
				case 12: tDropIdx = 87012; break;
				}
			}
			break;

		case 1:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87034; break;
				case 1: tDropIdx = 87035; break;
				case 2: tDropIdx = 87036; break;
				case 3: tDropIdx = 87037; break;
				case 4: tDropIdx = 87038; break;
				case 5: tDropIdx = 87039; break;
				case 6: tDropIdx = 87040; break;
				case 7: tDropIdx = 87041; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(13))
				{
				case 0: tDropIdx = 87021; break;
				case 1: tDropIdx = 87022; break;
				case 2: tDropIdx = 87023; break;
				case 3: tDropIdx = 87024; break;
				case 4: tDropIdx = 87025; break;
				case 5: tDropIdx = 87026; break;
				case 6: tDropIdx = 87027; break;
				case 7: tDropIdx = 87028; break;
				case 8: tDropIdx = 87029; break;
				case 9: tDropIdx = 87030; break;
				case 10: tDropIdx = 87031; break;
				case 11: tDropIdx = 87032; break;
				case 12: tDropIdx = 87033; break;
				}
			}
			break;

		case 2:
			if (mUTIL.GetRandomFloat() <= 0.10f)
			{
				switch (mUTIL.GetRandomInt(8))
				{
				case 0: tDropIdx = 87055; break;
				case 1: tDropIdx = 87056; break;
				case 2: tDropIdx = 87057; break;
				case 3: tDropIdx = 87058; break;
				case 4: tDropIdx = 87059; break;
				case 5: tDropIdx = 87060; break;
				case 6: tDropIdx = 87061; break;
				case 7: tDropIdx = 87062; break;
				}
			}
			else
			{
				switch (mUTIL.GetRandomInt(13))
				{
				case 0: tDropIdx = 87042; break;
				case 1: tDropIdx = 87043; break;
				case 2: tDropIdx = 87044; break;
				case 3: tDropIdx = 87045; break;
				case 4: tDropIdx = 87046; break;
				case 5: tDropIdx = 87047; break;
				case 6: tDropIdx = 87048; break;
				case 7: tDropIdx = 87049; break;
				case 8: tDropIdx = 87050; break;
				case 9: tDropIdx = 87051; break;
				case 10: tDropIdx = 87052; break;
				case 11: tDropIdx = 87053; break;
				case 12: tDropIdx = 87054; break;
				}
			}
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tDropIdx;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tDropIdx, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 611: //[Mount Exp Pill 3%]
		if (mUTIL.ReturnMountSort(mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber) == 30)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 100000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mAnimalExp[mAnimalIndex - 10] = mUTIL.ProcessForMountExp(mAnimalExp[mAnimalIndex - 10], 3000);
		tValue = mAnimalExp[mAnimalIndex - 10];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 612: //[Mount Exp Pill 1%]
		if (mUTIL.ReturnMountSort(mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber) == 30)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 100000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mAnimalExp[mAnimalIndex - 10] = mUTIL.ProcessForMountExp(mAnimalExp[mAnimalIndex - 10], 1000);
		tValue = mAnimalExp[mAnimalIndex - 10];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 652: //[Mount Exp Pill 5%]
		if (mUTIL.ReturnMountSort(mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber) == 30)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10] % 100000000) == 100000)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mAnimalExp[mAnimalIndex - 10] = mUTIL.ProcessForMountExp(mAnimalExp[mAnimalIndex - 10], 5000);
		tValue = mAnimalExp[mAnimalIndex - 10];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 601: //[War Box]
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 5) // 10% Range
		{
			tItem.clear();
			tItem = { VECTORTENMOUNT };//10% mount
			tValue = tItem[rand() % tItem.size()];
		}
		else if (tRandomValue <= 10) // 5% Range
		{
			tItem.clear();
			tItem = { VECTORFIVEMOUNT };//5% mount
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { HPLIX, STRLIX, AGILIX, CHLIX, EDMG, EDEF, CPPC, ABSPL, SBF };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mInven[tPage][tIndex][0] = tValue;
		mInven[tPage][tIndex][3] = 0;
		mInven[tPage][tIndex][4] = 0;
		mInven[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 584: // New Sistem Box
		if (mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade < 1) // For example this is the key you want to open. if (key < 1) then disconnect player if he tries to opened it with bypass exe 
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 20) // 1% Chances
		{
			tItem.clear();
			tItem = { VECTOR15MOUNT, 1016, 1012, 1403, 1401, 240, 243, 246, 1980, 1982 };
			tValue = tItem[rand() % tItem.size()];
		}
		else if (tRandomValue <= 60) // 20% Chances
		{
			tItem.clear();
			tItem = { VECTORTENMOUNT };
			tValue = tItem[rand() % tItem.size()];
		}
		else if (tRandomValue <= 200) // 40% Chances
		{
			tItem.clear();
			tItem = { VECTORFIVEMOUNT };
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { CPL, 636, 637, 638, 639, 640, 641, 1185, 2193 };
			tValue = tItem[rand() % tItem.size()];
		}
		mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade--;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1144: //[ WLC Cape Box]-Site
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 5) //0.5%
		{
			tItem.clear();
			tItem = { 1403 };
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { STRLIX, HPLIX, AGILIX, CHLIX, EDMG, EDEF, ABSPL, SBF, CPPC, CPS, BAG2, STORE2, GPS, PC };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mInven[tPage][tIndex][0] = tValue;
		mInven[tPage][tIndex][3] = 0;
		mInven[tPage][tIndex][4] = 0;
		mInven[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2159: //[Pet Deity Box]-Site
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 5) //0.5%
		{
			tItem.clear();
			tItem = { 1310, 1311, 1312 };
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { STRLIX, HPLIX, AGILIX, CHLIX, EDMG, EDEF, ABSPL, SBF, CPPC, CPS, BAG2, STORE2, GPS, PC };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mInven[tPage][tIndex][0] = tValue;
		mInven[tPage][tIndex][3] = 0;
		mInven[tPage][tIndex][4] = 0;
		mInven[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 602: //[Mount 15% Box]
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 5) //0.5%
		{
			tItem.clear();
			tItem = { 1307, 1308, 1309, 1315, 1319, 1322, 1325, 1328 };
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { STRLIX, HPLIX, AGILIX, CHLIX, EDMG, EDEF, ABSPL, SBF, CPPC, CPS, BAG2, STORE2, GPS, PC };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mInven[tPage][tIndex][0] = tValue;
		mInven[tPage][tIndex][3] = 0;
		mInven[tPage][tIndex][4] = 0;
		mInven[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mInven[tPage][tIndex][0], mInven[tPage][tIndex][3], mInven[tPage][tIndex][4], mInven[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1200: //[Title Remove Scroll 100%]
		switch (mUSER[tUserIndex].mAvatarInfo.aTitle % 100)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 800;
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 2500;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 2500;
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 5000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 5000;
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 8400;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 8400;
			break;
		case 5:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 12600;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 12600;
			break;
		case 6:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 17700;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 17700;
			break;
		case 7:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 23600;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 23600;
			break;
		case 8:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 30400;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 30400;
			break;
		case 9:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 38000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 38000;
			break;
		case 10:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 46500;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 46500;
			break;
		case 11:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 55800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 55800;
			break;
		case 12:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 65800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 65800;
			break;
		case 13:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 75800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 75800;
			break;
		case 14:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 85800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 85800;
			break;
		case 15:
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += 95800;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += 95800;
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		if ((mUSER[tUserIndex].mAvatarInfo.aTitle % 100) == 13 || (mUSER[tUserIndex].mAvatarInfo.aTitle % 100) == 14)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 891;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		}
		mUSER[tUserIndex].mAvatarInfo.aTitle = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = 0;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 15, mAVATAR_OBJECT[tUserIndex].mDATA.aTitle, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		tValue = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 864: //[Skill Box]
		tRandomValue = rand() % 100;
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			if (tRandomValue <= 20)
			{
				tRandomValue = rand() % 18;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90317;
					break;
				case 1:
					tValue = 90318;
					break;
				case 2:
					tValue = 90319;
					break;
				case 3:
					tValue = 90320;
					break;
				case 4:
					tValue = 90321;
					break;
				case 5:
					tValue = 90322;
					break;
				case 6:
					tValue = 90570;
					break;
				case 7:
					tValue = 90571;
					break;
				case 8:
					tValue = 90572;
					break;
				case 9:
					tValue = 90573;
					break;
				case 10:
					tValue = 90574;
					break;
				case 11:
					tValue = 90575;
					break;
				case 12:
					tValue = 90542;
					break;
				case 13:
					tValue = 90543;
					break;
				case 14:
					tValue = 90559;
					break;
				case 15:
					tValue = 90567;
					break;
				case 16:
					tValue = 90568;
					break;
				case 17:
					tValue = 90569;
					break;
				}
			}
			else
			{
				tRandomValue = rand() % 6;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90101;
					break;
				case 1:
					tValue = 90102;
					break;
				case 2:
					tValue = 90103;
					break;
				case 3:
					tValue = 90104;
					break;
				case 4:
					tValue = 90105;
					break;
				case 5:
					tValue = 90106;
					break;
				}
			}
			break;
		case 1:
			if (tRandomValue <= 20)
			{
				tRandomValue = rand() % 18;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90323;
					break;
				case 1:
					tValue = 90324;
					break;
				case 2:
					tValue = 90325;
					break;
				case 3:
					tValue = 90326;
					break;
				case 4:
					tValue = 90327;
					break;
				case 5:
					tValue = 90328;
					break;
				case 6:
					tValue = 90576;
					break;
				case 7:
					tValue = 90577;
					break;
				case 8:
					tValue = 90578;
					break;
				case 9:
					tValue = 90579;
					break;
				case 10:
					tValue = 90580;
					break;
				case 11:
					tValue = 90581;
					break;
				case 12:
					tValue = 90542;
					break;
				case 13:
					tValue = 90543;
					break;
				case 14:
					tValue = 90559;
					break;
				case 15:
					tValue = 90567;
					break;
				case 16:
					tValue = 90568;
					break;
				case 17:
					tValue = 90569;
					break;
				}
			}
			else
			{
				tRandomValue = rand() % 6;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90107;
					break;
				case 1:
					tValue = 90108;
					break;
				case 2:
					tValue = 90109;
					break;
				case 3:
					tValue = 90110;
					break;
				case 4:
					tValue = 90111;
					break;
				case 5:
					tValue = 90112;
					break;
				}
			}
			break;
		case 2:
			if (tRandomValue <= 20)
			{
				tRandomValue = rand() % 18;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90329;
					break;
				case 1:
					tValue = 90330;
					break;
				case 2:
					tValue = 90331;
					break;
				case 3:
					tValue = 90332;
					break;
				case 4:
					tValue = 90333;
					break;
				case 5:
					tValue = 90334;
					break;
				case 6:
					tValue = 90582;
					break;
				case 7:
					tValue = 90583;
					break;
				case 8:
					tValue = 90584;
					break;
				case 9:
					tValue = 90585;
					break;
				case 10:
					tValue = 90586;
					break;
				case 11:
					tValue = 90587;
					break;
				case 12:
					tValue = 90542;
					break;
				case 13:
					tValue = 90543;
					break;
				case 14:
					tValue = 90559;
					break;
				case 15:
					tValue = 90567;
					break;
				case 16:
					tValue = 90568;
					break;
				case 17:
					tValue = 90569;
					break;
				}
			}
			else
			{
				tRandomValue = rand() % 6;
				switch (tRandomValue)
				{
				case 0:
					tValue = 90113;
					break;
				case 1:
					tValue = 90114;
					break;
				case 2:
					tValue = 90115;
					break;
				case 3:
					tValue = 90116;
					break;
				case 4:
					tValue = 90117;
					break;
				case 5:
					tValue = 90118;
					break;
				}
			}
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 717: //[Skill Box] 8th //New Box Sistem
		if (mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll < 10) // For example this is the key you want to open. if (key < 1) then disconnect player if he tries to opened it with bypass exe 
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90786;
				break;
			case 1:
				tValue = 90788;
				break;
			case 2:
				tValue = 90787;
				break;
			}
			break;
		case 1:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90790;
				break;
			case 1:
				tValue = 90791;
				break;
			case 2:
				tValue = 90789;
				break;
			}
			break;
		case 2:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90792;
				break;
			case 1:
				tValue = 90794;
				break;
			case 2:
				tValue = 90793;
				break;
			}
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll -= 10;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 587:
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90786;
				break;
			case 1:
				tValue = 90788;
				break;
			case 2:
				tValue = 90787;
				break;
			}
			break;
		case 1:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90790;
				break;
			case 1:
				tValue = 90791;
				break;
			case 2:
				tValue = 90789;
				break;
			}
			break;
		case 2:
			switch (mUTIL.GetRandomInt(3))
			{
			case 0:
				tValue = 90792;
				break;
			case 1:
				tValue = 90794;
				break;
			case 2:
				tValue = 90793;
				break;
			}
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 800: //[Refined Elixir Chest]
		tRandomValue = rand() % 6;
		switch (tRandomValue)
		{
		case 0:
			tValue = 801;
			break; // Ref Hp Lix
		case 1:
			tValue = 802;
			break; // Ref Chi Lix
		case 2:
			tValue = 803;
			break; // Red Str Lix
		case 3:
			tValue = 804;
			break; // Red Dex Lix
		case 4:
			tValue = 805;
			break; // Ref E Dmg Lix
		case 5:
			tValue = 806;
			break; // Red E Def Lix
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 885: //[Elite G1 Pet Chest]
		tRandomValue = rand() % 3;
		switch (tRandomValue)
		{
		case 0:
			tValue = 1310;
			break; // SP
		case 1:
			tValue = 1311;
			break; //MR
		case 2:
			tValue = 1312;
			break; // WD
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1157: //[Elite M15 Pet Chest]
		tRandomValue = rand() % 3;
		switch (tRandomValue)
		{
		case 0:
			tValue = 1012;
			break; // Iron Condor
		case 1:
			tValue = 1013;
			break; // Divine Ancient Bird
		case 2:
			tValue = 1014;
			break; // Lightning Drake
		case 3:
			tValue = 1015;
			break; // Dark Cave Falcon
		case 4:
			tValue = 1016;
			break; // Red Scale Bird
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 883: //Pet Rare M1 Chest]
		tRandomValue = rand() % 3;
		switch (tRandomValue)
		{
		case 0:
			tValue = 1006;
			break; // Bloodthirsty Beetle
		case 1:
			tValue = 1007;
			break; //Flying Owl
		case 2:
			tValue = 1008;
			break; // Hell Bat
		case 3:
			tValue = 1009;
			break; // Shaman Tortoise
		case 4:
			tValue = 1010;
			break; // Armored Unicorn
		case 5:
			tValue = 1011;
			break; // Hellion 1011
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 829: //[Pet Inventory Expand]
		tValue = mUTIL.ReturnAddDate(mUSER[tUserIndex].mAvatarInfo.aPetInventoryDate, 30);
		mUSER[tUserIndex].mAvatarInfo.aPetInventoryDate = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1043: //[Lucky Refinement]
		tRandomValue = rand() % 500;
		if (tRandomValue <= 50)
		{
			tRandomValue = rand() % 7;
			switch (tRandomValue)
			{
			case 0:
				tValue = 699;
				break; // Precious Jade
			case 1:
				tValue = 576;
				break; // Genuine Jade
			case 2:
				tValue = 1023;
				break; // 15%
			case 3:
				tValue = 1022;
				break; // 12%
			case 4:
				tValue = 1021;
				break; // 9%
			case 5:
				tValue = 1020;
				break; // 6%
			case 6:
				tValue = 1019;
				break; // 3%
			}
		}
		else
		{
			tRandomValue = rand() % 5;
			switch (tRandomValue)
			{
			case 0:
				tValue = 1023;
				break; // 15%
			case 1:
				tValue = 1022;
				break; // 12%
			case 2:
				tValue = 1021;
				break; // 9%
			case 3:
				tValue = 1020;
				break; // 6%
			case 4:
				tValue = 1019;
				break; // 3%
			}
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 591: //[FL Teleport Scroll]
		if (!mGAME.ReturnTribeRole(mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aTribe))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].mCheckDeath = true;
		mAVATAR_OBJECT[tUserIndex].mCheckCount = 9;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1490: //[Instant 1% Exp Pill God]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) * 0.01f);
		if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
		{
			tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
		}
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1489: //[Instant 3% Exp Pill Master]
		if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (mUSER[tUserIndex].mAvatarInfo.aLevel2 > 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.03f);
		if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
		{
			tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
		}
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 649: //[Instant Exp Pill 5%]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.05f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
			{
				tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) * 0.05f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tValue;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

	case 650: //[Instant 10% Exp Pill]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 < 1)
		{
			tValue = ((mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mLEVEL.ReturnLevelFactor1(mUSER[tUserIndex].mAvatarInfo.aLevel1)) * 0.1f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 + tValue) > mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1))
			{
				tValue = mLEVEL.ReturnLevelFactor2(mUSER[tUserIndex].mAvatarInfo.aLevel1) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1 += tValue;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(13, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			tValue = (mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) * 0.1f);
			if ((mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 + tValue) > mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2))
			{
				tValue = mLEVEL.ReturnHighExpValue(mUSER[tUserIndex].mAvatarInfo.aLevel2) - mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2;
			}
			mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 += tValue;
			mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(24, mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

	case 1189: //[Faction Return Scroll]
		mUSER[tUserIndex].mAvatarInfo.aFactionReturnScroll++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1180: //[Blood Boost]
		mUSER[tUserIndex].mAvatarInfo.aDoubleIslandOfBloodTimeUse++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 566: //[Faction Notice Scroll]
		mUSER[tUserIndex].mAvatarInfo.aFactionNoticeScroll += 5;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2138: //[Premium Service]
	case 2292:
		if (tITEM_INFO->iIndex == 2138)
		{
			tValue = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 30);
		}
		else if (tITEM_INFO->iIndex == 2292)
		{
			tValue = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 1);
		}
		mUSER[tUserIndex].mAvatarInfo.aPremiumService = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2249: //[Cloak Random Box]
		tValue = 2208 + (rand() % 40);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2169: //[Amulet Box]
		tRandomValue = rand() % 100;
		if (tRandomValue <= 10)
		{
			tValue = 2151 + (rand() % 4);
		}
		else
		{
			tValue = 2174 + (rand() % 16);
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2298: // Unknown Red Nine Tailed Fox
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 2266;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(1);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2299: // Unknown Blue Nine Tailed Fox
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 2276;
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(2);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1938: //[Unindentified Green Deer]
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 1917;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(3);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1939: //[Unindentified Blue Deer]
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 1927 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(4);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2327: //[Purple Kirin]
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 2316;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(5);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2328: //[Dragon Kirin]
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 2317;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(6);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19000: // War Green Devil Mount
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19002 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(7);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19001: // War Pink Devil Mount
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19012 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(8);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19045: // Unk Green Turtle
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19025 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(9);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19046: // Unk Orange Turtle
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19035 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(9);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19071: // Unk White Horse
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19051 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(9);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19072: // Unk Red Horse
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue = 19061 + (rand() % 10);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(9);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tValue), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1332:
	case 1333:
	case 1334:
	case 1335:
	case 1336:
	case 1337:
	case 1338:
	case 1339:
	case 1340:
	case 1341:
	case 1342:
	case 1343:
	case 1344:
	case 1345:
	case 1346:
	case 1347:
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == tITEM_INFO->iIndex)
			{
				break;
			}
		}
		if (index01 < MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_ANIMAL_NUM; index01++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] == 0)
			{
				break;
			}
		}
		if (index01 == MAX_AVATAR_ANIMAL_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimal[index01] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01] = mUTIL.SetEliteAnimalAbility(1);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(((index01 * 100000) + tITEM_INFO->iIndex), tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[index01], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 891: // [ Title Ticket ]
		if ((mUSER[tUserIndex].mAvatarInfo.aTitle % 100) >= 15)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mUSER[tUserIndex].mAvatarInfo.aTitle % 100) < 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aTitle++;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTitle++;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 15, mAVATAR_OBJECT[tUserIndex].mDATA.aTitle, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 665: //[Construction Scroll]
		tTowerSort = mUTIL.GetTowerSort(1, 0);
		if (mGAME.mTowerInfo.mTowerInfo[tTowerSort] != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 12; index01++)
		{
			if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == tValue)
			{
				if (3 * mUSER[tUserIndex].mAvatarInfo.aTribe <= index01 && 3 * mUSER[tUserIndex].mAvatarInfo.aTribe + 2 >= index01)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mGAME.ReturnTribeRole(mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aTribe) != 1 &&
			mGAME.ReturnTribeRole(mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aTribe) != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tValue)
		{
		case 1:
			tTowerInfo = 201;
			CopyMemory(&tBroadcastInfoData[0], &tTowerSort, 4);
			CopyMemory(&tBroadcastInfoData[4], &tTowerInfo, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(752, &tBroadcastInfoData[0]);
			break;
		case 2:
			tTowerInfo = 202;
			CopyMemory(&tBroadcastInfoData[0], &tTowerSort, 4);
			CopyMemory(&tBroadcastInfoData[4], &tTowerInfo, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(752, &tBroadcastInfoData[0]);
			break;
		case 3:
			tTowerInfo = 203;
			CopyMemory(&tBroadcastInfoData[0], &tTowerSort, 4);
			CopyMemory(&tBroadcastInfoData[4], &tTowerInfo, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(752, &tBroadcastInfoData[0]);
			break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mSUMMON.SummonTowerForConstruction(mUTIL.GetTowerSort(4, tTowerInfo));
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 18014: // [ Engrave Scroll Box ]
		tRandomValue = rand() % 1000;
		if (tRandomValue == 0)
		{
			tRandomValue = rand() % 9;
			switch (tRandomValue)
			{
			case 0:
				tValue = 17266;
				break;
			case 1:
				tValue = 17267;
				break;
			case 2:
				tValue = 17268;
				break;
			case 3:
				tValue = 17269;
				break;
			case 4:
				tValue = 17270;
				break;
			case 5:
				tValue = 17271;
				break;
			case 6:
				tValue = 17272;
				break;
			case 7:
				tValue = 17273;
				break;
			case 8:
				tValue = 17274;
				break;
			}
		}
		else if (tRandomValue <= 100)
		{
			tRandomValue = rand() % 10;
			switch (tRandomValue)
			{
			case 0:
				tValue = 17256;
				break;
			case 1:
				tValue = 17257;
				break;
			case 2:
				tValue = 17258;
				break;
			case 3:
				tValue = 17259;
				break;
			case 4:
				tValue = 17260;
				break;
			case 5:
				tValue = 17261;
				break;
			case 6:
				tValue = 17262;
				break;
			case 7:
				tValue = 17263;
				break;
			case 8:
				tValue = 17264;
				break;
			case 9:
				tValue = 17265;
				break;
			}
		}
		else if (tRandomValue <= 300)
		{
			tRandomValue = rand() % 12;
			switch (tRandomValue)
			{
			case 0:
				tValue = 17244;
				break;
			case 1:
				tValue = 17245;
				break;
			case 2:
				tValue = 17246;
				break;
			case 3:
				tValue = 17247;
				break;
			case 4:
				tValue = 17248;
				break;
			case 5:
				tValue = 17249;
				break;
			case 6:
				tValue = 17250;
				break;
			case 7:
				tValue = 17251;
				break;
			case 8:
				tValue = 17252;
				break;
			case 9:
				tValue = 17253;
				break;
			case 10:
				tValue = 17254;
				break;
			case 11:
				tValue = 17255;
				break;
			}
		}
		else
		{
			tRandomValue = rand() % 28;
			switch (tRandomValue)
			{
			case 0:
				tValue = 17216;
				break;
			case 1:
				tValue = 17217;
				break;
			case 2:
				tValue = 17218;
				break;
			case 3:
				tValue = 17219;
				break;
			case 4:
				tValue = 17220;
				break;
			case 5:
				tValue = 17221;
				break;
			case 6:
				tValue = 17222;
				break;
			case 7:
				tValue = 17223;
				break;
			case 8:
				tValue = 17224;
				break;
			case 9:
				tValue = 17225;
				break;
			case 10:
				tValue = 17226;
				break;
			case 11:
				tValue = 17227;
				break;
			case 12:
				tValue = 17228;
				break;
			case 13:
				tValue = 17229;
				break;
			case 14:
				tValue = 17230;
				break;
			case 15:
				tValue = 17231;
				break;
			case 16:
				tValue = 17232;
				break;
			case 17:
				tValue = 17233;
				break;
			case 18:
				tValue = 17234;
				break;
			case 19:
				tValue = 17235;
				break;
			case 20:
				tValue = 17236;
				break;
			case 21:
				tValue = 17237;
				break;
			case 22:
				tValue = 17238;
				break;
			case 23:
				tValue = 17239;
				break;
			case 24:
				tValue = 17240;
				break;
			case 25:
				tValue = 17241;
				break;
			case 26:
				tValue = 17242;
				break;
			case 27:
				tValue = 17243;
				break;
			}
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 843: // [ Lvl 45 Beginner Reward ]//(87077, 87078, 87079, 87080, 87081, 87082, 87083, 87084);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(13031 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86762);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(33031 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86763);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40; // Enchant %
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40); // Enchant %
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(53031 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86764);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 844: // [ Lvl 75 Beginner Reward ]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(13040 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86765);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(33040 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86766);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(53040 + (index01 * 15));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86767);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 845: // [ Lvl 105 Beginner Reward ]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(13199 + (index01 * 27));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86768);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(33199 + (index01 * 27));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86769);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(53199 + (index01 * 27));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86770);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 847: //[M2 Beginner Reward]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(61007 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86771);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(71007 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86772);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(81007 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86773);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 848: //[M11 Beginner Reward]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(61079 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86774);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(71079 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86775);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(81079 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86776);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 850: //[M20 Beginner Reward]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(61151 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86777);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(71151 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86778);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(81151 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86779);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 851: //[M29 Beginner Reward]
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		switch (mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
		case 0:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(61223 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86780);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 1:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(71223 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86781);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 40;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		case 2:
			for (index01 = 0; index01 < 6; index01++)
			{
				tITEM_INFO = mITEM.Search(81223 + (index01 * 3));
				if (index01 == 0)
				{
					tITEM_INFO = mITEM.Search(86782);
				}
				if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex) == true)
				{
					iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
					if (iInvenSlot != -1)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 2400;
						mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 41633;
						tValueHolder[0] = tITEM_INFO->iIndex;
						mTRANSFER.B_BEGINNER_REWARD_RECV(11001, iPage, iInvenSlot, 0, iInvenIndex, 0, &tValueHolder[0], 40);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
				else
				{
					mUTIL.ProcessForDropItem(3, tITEM_INFO->iIndex, 0, 40, 41633, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 0);
				}
			}
			return;
		}

	case 828: // [Prevent Improve Down]
	case 837:
		mUSER[tUserIndex].mAvatarInfo.aPreventImproveDown++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 620: //[Rage Burst Pill]
		mUSER[tUserIndex].mAvatarInfo.aRageBurstPill++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 592: // Proxy Shop 7D
		tValue = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 7);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aProxyShopTime = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 567: // Proxy Shop 1D
		tValue = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 1);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aProxyShopTime = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 553: // Fishing Ticket
		mUSER[tUserIndex].mAvatarInfo.aIvyHallFishing += 180;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 590: // Faction Trap
		for (index01 = 0; index01 < 5; index01++)
		{
			if (mGAME.mFactionTrap.mTrapLocation[index01][0] != 0.0 || mGAME.mFactionTrap.mTrapLocation[index01][1] != 0.0 || mGAME.mFactionTrap.mTrapLocation[index01][2] != 0.0)
			{
				continue;
			}
			mGAME.mFactionTrap.mTrapLocation[index01][0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
			mGAME.mFactionTrap.mTrapLocation[index01][1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
			mGAME.mFactionTrap.mTrapLocation[index01][2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
			break;
		}
		if (index01 == 5)
		{
			mTRANSFER.B_USE_INVENTORY_ITEM_RECV(1, tPage, tIndex, tValue, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_FACTION_TRAP_RECV(&mGAME.mFactionTrap);
		mUTIL.Broadcast(FALSE, 0, 0);
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2193: // +1 Halo Ticket
		if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue >= 96)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aUpgradeValue++;
		mAVATAR_OBJECT[tUserIndex].mDATA.aHalo++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aUpgradeValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19416: // Cheonganbu
		tValue = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 7);
		mUSER[tUserIndex].mAvatarInfo.aCheonganbu = tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 635:///Mount Box///
		tRandomValue = rand() % 8;
		switch (tRandomValue)
		{
		case 0: tValue = 1307; break;
		case 1: tValue = 1308; break;
		case 2: tValue = 1309; break;
		case 3: tValue = 1315; break;
		case 4: tValue = 1319; break;
		case 5: tValue = 1322; break;
		case 6: tValue = 1325; break;
		case 7: tValue = 1328; break;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19512:
		if(mUSER[tUserIndex].mAvatarInfo.aRebirth < 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if(mUSER[tUserIndex].mAvatarInfo.aHornVeinUnlockCount < 0 || mUSER[tUserIndex].mAvatarInfo.aHornVeinUnlockCount > 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	case 19513:
	case 19514:
	case 19515:
	case 19516:
	case 19517:
	case 19518:
	case 19519:
		if(mUSER[tUserIndex].mAvatarInfo.aRebirth < 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aHornVeinUnlockCount++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19533:
	case 19534:
	case 19535:
	case 19536:
	case 19537:
	case 19538:
	case 19539:
	case 19540:
	case 19541:
	case 19542:
		if(mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel / 10 < tITEM_INFO->iIndex - 19532)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if(mUSER[tUserIndex].mAvatarInfo.aThousandMoonBuff != tITEM_INFO->iIndex - 19533)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aThousandMoonBuff++;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aThousandMoonBuff, 0);
		mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19614:
		for(index01 = 0; index01 < 3; index01++)
		{
			for(index02 = 0; index02 < 14; index02++)
			{
				if(mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] == 1)
				{
					if(mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
					{
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
						mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
					}
				}
			}
		}
		for(index01 = 0; index01 < 8; index01++)
		{
			if(mUSER[tUserIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[index01][0] == mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
			{
				mUSER[tUserIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[index01][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aAutoBuffScrollSkillSlots[index01][1] = 0;
			}
		}
		for(index01 = 0; index01 < 2; index01++)
		{
			for(index02 = 0; index02 < 2; index02++)
			{
				mUSER[tUserIndex].mAvatarInfo.aAutoSkillAttack[index01][index02] = 0;
			}
		}
		for(index01 = 0; index01 < 8; index01++)
		{
			for(index02 = 0; index02 < 2; index02++)
			{
				mUSER[tUserIndex].mAvatarInfo.aAutoHuntData[index01][index02] = 0;
			}
		}
		switch(mUSER[tUserIndex].mAvatarInfo.aSkill[tValue][0])
		{
			case 112: tValue = tValue * 1000000 + 151; break;
			case 113: tValue = tValue * 1000000 + 169; break;
			case 114: tValue = tValue * 1000000 + 187; break;
			case 115: tValue = tValue * 1000000 + 205; break;
			case 116: tValue = tValue * 1000000 + 223; break;
			case 117: tValue = tValue * 1000000 + 241; break;
			case 118: tValue = tValue * 1000000 + 259; break;
			case 119: tValue = tValue * 1000000 + 277; break;
			case 120: tValue = tValue * 1000000 + 295; break;
			default: tValue = tValue * 1000000 + 1; break;
		}
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue / 1000000][0] = tValue % 1000000;
		mUSER[tUserIndex].mAvatarInfo.aSkill[tValue / 1000000][1] = 1;
		if(tITEM_INFO->iIndex >= 19574 && tITEM_INFO->iIndex <= 19610)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkillUpgradePoints -= 100;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return; 

	case 19543:
	case 19545: // Hwangoldan
		if (tITEM_INFO->iIndex == 19543)
		{
			mUSER[tUserIndex].mAvatarInfo.aHwangoldan++;
		}
		else if (tITEM_INFO->iIndex == 19545)
		{
			mUSER[tUserIndex].mAvatarInfo.aHwangoldan += 11;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aHwangoldan, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19544:
	case 19567: // Sungoldan
		mUSER[tUserIndex].mAvatarInfo.aSungoldan++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aSungoldan, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19546:
	case 19568:
		mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19547:
	case 19569:
		mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19548:
	case 19570:
		mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 19549:
	case 19571:
		mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb++;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1837: // Warlord Cape Box
		tRandomValue = rand() % 1000;
		if (tRandomValue == 0) // Warlord Cape
		{
			tValue = 1403;
		}
		else
		{
			tItem.clear();
			tItem = {1103, 1166, 1237, 1092, 1093, 1017, 1018, 578, 579, 694, 696, 695, 1118};
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 714: // Premium Wing Box
		tRandomValue = rand() % 1000;
		if (tRandomValue == 0)
		{
			switch (mPrevTribe)
			{
			case 0: tValue = 216; break;
			case 1: tValue = 217; break;
			case 2: tValue = 218; break;
			}
		}
		else
		{
			tItem.clear();
			tItem = { GF, BF, WF, CPS, SBF, PC, CPPC, HERB, HPLIX, CHLIX, AGILIX, STRLIX, 801, 802, 803, 804, 805, 806 };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 715: // CP Bag
		tRandomValue = rand() % 1000;
		if (tRandomValue <= 10) //1%
			tValue = 500;
		else if (tRandomValue <= 40) //3%
			tValue = 400;
		else if (tRandomValue <= 140) // 10%
			tValue = 300;
		else if (tRandomValue <= 340) // 20%
			tValue = 200;
		else if (tRandomValue <= 640) // 30%
			tValue = 100;
		else
			tValue = 50; // 36%
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += tValue;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += tValue;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 716: // PVP Box
		tRandomValue = rand() % 500;
		if (tRandomValue == 0)
		{
			tItem.clear();
			tItem = { VECTOR15MOUNT };
			tValue = tItem[rand() % tItem.size()];
		}
		else if (tRandomValue <= 4)
		{
			tItem.clear();
			tItem = { VECTORTENMOUNT };
			tValue = tItem[rand() % tItem.size()];
		}
		else
		{
			tItem.clear();
			tItem = { CPM, CPS, STRLIX, HPLIX, AGILIX, CHLIX, EDMG, EDEF, PC, CPPC, WPC, BAG2, STORE2, SOL, ABS7, SBF, ABSPL, WF, BF, GF, HERB, 801, 802, 803, 804, 805, 806 };
			tValue = tItem[rand() % tItem.size()];
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
//
//	case 717: // 15% Mount Box
//		tRandomValue = rand() % 1000;
//		if (tRandomValue == 0)
//		{
//			tItem.clear();
//			tItem = { VECTOR15MOUNT, 1329, 1330, 1331 };
//			tValue = tItem[rand() % tItem.size()];
//		}
//		else
//		{
//			tItem.clear();
//			tItem = { CPS, SBF, PC, CPPC, HERB, HPLIX, CHLIX, AGILIX, STRLIX, 801, 802, 803, 804, 805, 806 };
//			tValue = tItem[rand() % tItem.size()];
//		}
//		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
//		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
//		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
//		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
//		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//		return;

	case 718: // Enchant Talisman
		mUSER[tUserIndex].mAvatarInfo.aEnchantTalisman += 1;	
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 719: // Enchant Talisman(SP)
		mUSER[tUserIndex].mAvatarInfo.aEnchantTalismanSP += 1;	
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 720: // Wing Talisman
		mUSER[tUserIndex].mAvatarInfo.aWingEnchantTalisman += 1;	
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 632: //Rebirth Pill
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth >= 6)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 != 1481117817)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_606_USE_INVENTORY_ITEM(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], 0, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
		mUSER[tUserIndex].mAvatarInfo.aRebirth++;
		mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth++;
		mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath += 10;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 14, mCP, mUSER[tUserIndex].mAvatarInfo.aRebirth, mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath);
		mUTIL.Broadcast(TRUE, &mCharLoc[0], UNIT_SCALE_RADIUS1);
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth == 6)
		{
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(904, &tBroadcastInfoData[0]);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth == 12)
		{
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(902, &tBroadcastInfoData[0]);
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.B_USE_INVENTORY_ITEM_RECV(0, tPage, tIndex, tValue, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_TRIBE_BANK_SEND
void W_TRIBE_BANK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue; 
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tMoney;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	switch (tSort)
	{
	case 1: //[Lookup]
		if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
		{
			if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_VIEW_SEND(mUSER[tUserIndex].mAvatarInfo.aTribe);
		mTRANSFER.B_TRIBE_BANK_RECV(mPLAYUSER_COM.mRecv_Result, 1, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2: //[Withdrawal]
		if ((tValue < 0) || (tValue > (MAX_TRIBE_BANK_SLOT_NUM - 1)) || (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) || (mGAME.ReturnTribeSubMasterNum(mUSER[tUserIndex].mAvatarInfo.aTribe) < 3))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_LOAD_SEND(mUSER[tUserIndex].mAvatarInfo.aTribe, tValue, mUSER[tUserIndex].mAvatarInfo.aMoney);
		switch (mPLAYUSER_COM.mRecv_Result)
		{
		case 0:
			tMoney = mPLAYUSER_COM.mRecv_Money - mUSER[tUserIndex].mAvatarInfo.aMoney;
			mGAMELOG.GL_618_TRIBE_MONEY(tUserIndex, tMoney);
			mUSER[tUserIndex].mAvatarInfo.aMoney = mPLAYUSER_COM.mRecv_Money;
			mTRANSFER.B_TRIBE_BANK_RECV(0, 2, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], mPLAYUSER_COM.mRecv_Money);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mPLAYUSER_COM.U_TRIBE_BANK_INFO_VIEW_SEND(mUSER[tUserIndex].mAvatarInfo.aTribe);
			mTRANSFER.B_TRIBE_BANK_RECV(0, 1, &mPLAYUSER_COM.mRecv_TribeBankInfo[0], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			//--------------//
			// BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 62;
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &tMoney, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			return;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_TRIBE_WORK_SEND
void W_TRIBE_WORK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int iCount = 0;
	BYTE tData[MAX_TRIBE_WORK_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_TRIBE_WORK_SIZE);

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tOtherUserIndex;
	int tTribeWeaponItemNumber = 0;
	int tCPCost = 0;
	int tRandomValue;
	int tTribeSkillSort = 0;
	int tKillOtherTribeNum;
	int tRandomNumber;
	int iIndex;
	ITEM_INFO* tITEM_INFO;

	switch (tSort)
	{
	case 1: //[FREE_STAT_RESET]
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 > 39)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint += (mUSER[tUserIndex].mAvatarInfo.aVit + mUSER[tUserIndex].mAvatarInfo.aStr + mUSER[tUserIndex].mAvatarInfo.aInt + mUSER[tUserIndex].mAvatarInfo.aDex - 4);
		mUSER[tUserIndex].mAvatarInfo.aVit = 1;
		mUSER[tUserIndex].mAvatarInfo.aStr = 1;
		mUSER[tUserIndex].mAvatarInfo.aInt = 1;
		mUSER[tUserIndex].mAvatarInfo.aDex = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 2: //[VFL_APPOINT]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (strcmp(tAvatarName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName) == 0)
			{
				break;
			}
		}
		if (index01 < MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "") == 0)
			{
				break;
			}
		}
		if (index01 == MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tOtherUserIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
		if (tOtherUserIndex == -1)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mMoveZoneResult == 1)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(2, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUSER[tOtherUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mTRANSFER.B_TRIBE_WORK_RECV(3, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		/* SubMaster aName duplicate check */
		for (iCount = 0; iCount < MAX_TRIBE_SUBMASTER_NUM; iCount++)
		{
			if (!::strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount], tAvatarName))
			{
				mTRANSFER.B_TRIBE_WORK_RECV(4, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		/* SubMaster duplicate check */
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		// BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 60;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &index01, 4);
		CopyMemory(&tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName, MAX_AVATAR_NAME_LENGTH);
		return;
	case 3: //[부세력장_제명]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], tAvatarName) == 0)
			{
				break;
			}
		}
		if (index01 == MAX_TRIBE_SUBMASTER_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		// BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 61;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &index01, 4);
		CopyMemory(&tBroadcastInfoData[8], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mGAME.mTribeInfo.mTribeSubMaster[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "");
		return;
	case 4: //[FACTION_WEAPON]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 100000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			tTribeWeaponItemNumber = 1075;
			break;
		case 1:
			tTribeWeaponItemNumber = 1076;
			break;
		case 2:
			tTribeWeaponItemNumber = 1077;
			break;
		case 3:
			tTribeWeaponItemNumber = 1078;
			break;
		}
		if (!mUTIL.ProcessForDropItem(10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 100000000;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 5: //[세력진법]
		CopyMemory(&tTribeSkillSort, &tData[0], 4);
		if ((tTribeSkillSort < 0) || (tTribeSkillSort > 4))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((mGAME.mWorldInfo.mTribePoint[0] <= 100) || (mGAME.mWorldInfo.mTribePoint[1] <= 100) || (mGAME.mWorldInfo.mTribePoint[2] <= 100) || (mGAME.mWorldInfo.mTribePoint[3] <= 100))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.ReturnSmallTribe() != mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mWorldInfo.mTribeSymbolBattle != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		// BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 302;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tTribeSkillSort, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//

	#ifdef TITLE
	case 6:	// Title System
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 71)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 72)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 73)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTitle % 100 >= 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTitle % 100)
		{
		case 0:
			tCPCost = 800;
			break;
		case 1:
			tCPCost = 1700;
			break;
		case 2:
			tCPCost = 2500;
			break;
		case 3:
			tCPCost = 3400;
			break;
		case 4:
			tCPCost = 4200;
			break;
		case 5:
			tCPCost = 5100;
			break;
		case 6:
			tCPCost = 5900;
			break;
		case 7:
			tCPCost = 6800;
			break;
		case 8:
			tCPCost = 7600;
			break;
		case 9:
			tCPCost = 8500;
			break;
		case 10:
			tCPCost = 9300;
			break;
		case 11:
			tCPCost = 10000;
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < tCPCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCPCost;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tCPCost;
		if (mUSER[tUserIndex].mAvatarInfo.aTitle || tData[0] <= 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aTitle++;
			mAVATAR_OBJECT[tUserIndex].mDATA.aTitle++;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aTitle = 100 * (tData[0] - 1) + 1;
			mAVATAR_OBJECT[tUserIndex].mDATA.aTitle = 100 * (tData[0] - 1) + 1;
		}
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 15, mAVATAR_OBJECT[tUserIndex].mDATA.aTitle, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		return;
	#endif

	#ifdef CPRFC
	case 7: // CP-RFC
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue >= 96)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		// Pay CP
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 100;
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;

		if (mUTIL.GetRandomFloat() <= 0.50f)
		{
			// Success
			mUSER[tUserIndex].mAvatarInfo.aUpgradeValue++;
			mAVATAR_OBJECT[tUserIndex].mDATA.aHalo++;
			mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue == 96)
			{
				CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(672, &tData[0]);
			}
		}
		else
		{
			// Fail
			if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue == 0)
			{
				mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			else
			{
				if (mUTIL.GetRandomFloat() <= 0.20f)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aCPProtectionCharm > 0)
					{
						mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						mUSER[tUserIndex].mAvatarInfo.aCPProtectionCharm--;
						mTRANSFER.B_AVATAR_CHANGE_INFO_2(31, mUSER[tUserIndex].mAvatarInfo.aCPProtectionCharm);
						mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
						return;
					}
					mUSER[tUserIndex].mAvatarInfo.aUpgradeValue--;
					mAVATAR_OBJECT[tUserIndex].mDATA.aHalo--;
					mTRANSFER.B_TRIBE_WORK_RECV(2, tSort, &tData[0]);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
				else
				{
					mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
			}
		}
		return;
	#endif

	case 8: //[Beginner Reward]
		if (mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 45 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 75)
		{
			mUTIL.ProcessForDropItem(3, 843, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 75 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 105)
		{
			mUTIL.ProcessForDropItem(3, 844, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 105 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 114)
		{
			mUTIL.ProcessForDropItem(3, 845, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 114 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 123)
		{
			mUTIL.ProcessForDropItem(3, 847, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 123 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 132)
		{
			mUTIL.ProcessForDropItem(3, 848, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 132 && mUSER[tUserIndex].mAvatarInfo.aLevel1 < 141)
		{
			mUTIL.ProcessForDropItem(3, 850, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 >= 141 && mUSER[tUserIndex].mAvatarInfo.aLevel1 <= 145)
		{
			mUTIL.ProcessForDropItem(3, 851, 1, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);
		}
		mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon = 0;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 9: //[Turn On Ornament]
		mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 10: //[Turn Off Ornament
		mUSER[tUserIndex].mAvatarInfo.iUseOrnament = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	#ifdef REBIRTH
	case 11: //Max aRebirth
		if (mUSER[tUserIndex].mAvatarInfo.aLevel2 != 12)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 != 1481117817)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth >= 6)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mAvatarInfo.aRebirth++;
		mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth++;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 10000;
		mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2 = 0;
		mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath += 10;
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 14, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mAVATAR_OBJECT[tUserIndex].mDATA.aRebirth, mUSER[tUserIndex].mAvatarInfo.aLifeOrDeath);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth == 6)
		{
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(904, &tBroadcastInfoData[0]);
		}
		return;
		if (mUSER[tUserIndex].mAvatarInfo.aRebirth == 12)
		{
			CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
			CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(902, &tBroadcastInfoData[0]);
		}
		return;
	#endif

	case 16: // [ FL Teleport Scroll ]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeWeaponItemNumber = 591;
		if (!mUTIL.ProcessForDropItem(10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 17: // [Alert Charm]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeWeaponItemNumber = 590;
		if (!mUTIL.ProcessForDropItem(10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 10;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 18: //[ Construction Scroll ]
		if ((mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 1) && (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 2))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 500000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tTribeWeaponItemNumber = 665;
		if (!mUTIL.ProcessForDropItem(10, tTribeWeaponItemNumber, 0, 0, 0, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[tUserIndex].mDATA.aName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0))
		{
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_641_MAKE_TRIBE_WEAPON(tUserIndex, tTribeWeaponItemNumber, 0, 0, 0);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 500000000;
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	#ifdef METASTATIS
	case 19: // Redistribute Metastatis
		if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue < 96)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel < 1 || mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel >= 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aHwangoldan < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSungoldan > 0)
		{
			tRandomValue = 7 + (rand() % 3 + 1);
			mUSER[tUserIndex].mAvatarInfo.aMetastatisStr = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr / 100) * 100) + tRandomValue;
			tRandomValue = 7 + (rand() % 3 + 1);
			mUSER[tUserIndex].mAvatarInfo.aMetastatisVit = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit / 100) * 100) + tRandomValue;
			tRandomValue = 7 + (rand() % 3 + 1);
			mUSER[tUserIndex].mAvatarInfo.aMetastatisDex = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex / 100) * 100) + tRandomValue;
			tRandomValue = 7 + (rand() % 3 + 1);
			mUSER[tUserIndex].mAvatarInfo.aMetastatisInt = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt / 100) * 100) + tRandomValue;
			mUSER[tUserIndex].mAvatarInfo.aSungoldan--;
		}
		else
		{
			tRandomValue = rand() % 10 + 1;
			mUSER[tUserIndex].mAvatarInfo.aMetastatisStr = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr / 100) * 100) + tRandomValue;
			tRandomValue = rand() % 10 + 1;
			mUSER[tUserIndex].mAvatarInfo.aMetastatisVit = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit / 100) * 100) + tRandomValue;
			tRandomValue = rand() % 10 + 1;
			mUSER[tUserIndex].mAvatarInfo.aMetastatisDex = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex / 100) * 100) + tRandomValue;
			tRandomValue = rand() % 10 + 1;
			mUSER[tUserIndex].mAvatarInfo.aMetastatisInt = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt / 100) * 100) + tRandomValue;
		}
		mUSER[tUserIndex].mAvatarInfo.aHwangoldan--;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
		mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel, 4);
		CopyMemory(&tData[4], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVit, 4);
		CopyMemory(&tData[8], &mUSER[tUserIndex].mAvatarInfo.aMetastatisInt, 4);
		CopyMemory(&tData[12], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStr, 4);
		CopyMemory(&tData[16], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDex, 4);
		CopyMemory(&tData[20], &mUSER[tUserIndex].mAvatarInfo.aHwangoldan, 4);
		CopyMemory(&tData[24], &mUSER[tUserIndex].mAvatarInfo.aSungoldan, 4);
		CopyMemory(&tData[28], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb, 4);
		CopyMemory(&tData[32], &mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb, 4);
		CopyMemory(&tData[36], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb, 4);
		CopyMemory(&tData[40], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb, 4);
		mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	case 20: // Metastatis
		if (mUSER[tUserIndex].mAvatarInfo.aUpgradeValue < 96)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel >= 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((rand() % 100) <= 50)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb > 0)
			{
				tRandomValue = 7 + (rand() % 3 + 1);
				mUSER[tUserIndex].mAvatarInfo.aMetastatisStr = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr % 100) * 100) + tRandomValue;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb--;
			}
			else
			{
				tRandomValue = rand() % 10 + 1;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisStr = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisStr % 100) * 100) + tRandomValue;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb > 0)
			{
				tRandomValue = 7 + (rand() % 3 + 1);
				mUSER[tUserIndex].mAvatarInfo.aMetastatisVit = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit % 100) * 100) + tRandomValue;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb--;
			}
			else
			{
				tRandomValue = rand() % 10 + 1;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisVit = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisVit % 100) * 100) + tRandomValue;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb > 0)
			{
				tRandomValue = 7 + (rand() % 3 + 1);
				mUSER[tUserIndex].mAvatarInfo.aMetastatisDex = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex % 100) * 100) + tRandomValue;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb--;
			}
			else
			{
				tRandomValue = rand() % 10 + 1;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisDex = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisDex % 100) * 100) + tRandomValue;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb > 0)
			{
				tRandomValue = 7 + (rand() % 3 + 1);
				mUSER[tUserIndex].mAvatarInfo.aMetastatisInt = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt % 100) * 100) + tRandomValue;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb--;
			}
			else
			{
				tRandomValue = rand() % 10 + 1;
				mUSER[tUserIndex].mAvatarInfo.aMetastatisInt = ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt / 100) * 100) + ((mUSER[tUserIndex].mAvatarInfo.aMetastatisInt % 100) * 100) + tRandomValue;
			}
			mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel++;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
			CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel, 4);
			CopyMemory(&tData[4], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVit, 4);
			CopyMemory(&tData[8], &mUSER[tUserIndex].mAvatarInfo.aMetastatisInt, 4);
			CopyMemory(&tData[12], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStr, 4);
			CopyMemory(&tData[16], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDex, 4);
			CopyMemory(&tData[20], &mUSER[tUserIndex].mAvatarInfo.aHwangoldan, 4);
			CopyMemory(&tData[24], &mUSER[tUserIndex].mAvatarInfo.aSungoldan, 4);
			CopyMemory(&tData[28], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb, 4);
			CopyMemory(&tData[32], &mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb, 4);
			CopyMemory(&tData[36], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb, 4);
			CopyMemory(&tData[40], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb, 4);
			mTRANSFER.B_TRIBE_WORK_RECV(0, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].GetMaxLife();
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].GetMaxMana();
			CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aMetastatisLevel, 4);
			CopyMemory(&tData[4], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVit, 4);
			CopyMemory(&tData[8], &mUSER[tUserIndex].mAvatarInfo.aMetastatisInt, 4);
			CopyMemory(&tData[12], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStr, 4);
			CopyMemory(&tData[16], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDex, 4);
			CopyMemory(&tData[20], &mUSER[tUserIndex].mAvatarInfo.aHwangoldan, 4);
			CopyMemory(&tData[24], &mUSER[tUserIndex].mAvatarInfo.aSungoldan, 4);
			CopyMemory(&tData[28], &mUSER[tUserIndex].mAvatarInfo.aMetastatisVitOrb, 4);
			CopyMemory(&tData[32], &mUSER[tUserIndex].mAvatarInfo.aMetastatisIntOrb, 4);
			CopyMemory(&tData[36], &mUSER[tUserIndex].mAvatarInfo.aMetastatisStrOrb, 4);
			CopyMemory(&tData[40], &mUSER[tUserIndex].mAvatarInfo.aMetastatisDexOrb, 4);
			mTRANSFER.B_TRIBE_WORK_RECV(1, tSort, &tData[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		return;
	#endif

	default: //[오류]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_ADD_ITEM_SEND
void W_ADD_ITEM_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int tProbability = 0;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckHighImprove != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_ADD_ITEM_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO2->iIndex != 2001 && tITEM_INFO2->iIndex != 2002 && tITEM_INFO2->iIndex != 2003)
	{
		if (tITEM_INFO2->iType != 3 && tITEM_INFO2->iCheckItemSet != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO2->iSort != 7) && (tITEM_INFO2->iSort != 8) && (tITEM_INFO2->iSort != 9) && (tITEM_INFO2->iSort != 10) && (tITEM_INFO2->iSort != 11) && (tITEM_INFO2->iSort != 12) && (tITEM_INFO2->iSort != 13) && (tITEM_INFO2->iSort != 14) && (tITEM_INFO2->iSort != 15) && (tITEM_INFO2->iSort != 16) && (tITEM_INFO2->iSort != 17) && (tITEM_INFO2->iSort != 18) && (tITEM_INFO2->iSort != 19) && (tITEM_INFO2->iSort != 20) && (tITEM_INFO2->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (tITEM_INFO2->iCheckItemSet == 2)
	{
		if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4]) > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	else
	{
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4]) > 0 || mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4]) > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (tITEM_INFO2->iIndex != 2001 && tITEM_INFO2->iIndex != 2002 && tITEM_INFO2->iIndex != 2003)
	{
		if (tITEM_INFO1->iSort != tITEM_INFO2->iSort)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iCheckItemSet == 2)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 44)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iCheckItemSet != tITEM_INFO2->iCheckItemSet || tITEM_INFO1->iType != tITEM_INFO2->iType)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO1->iType)
		{
		case 3:
			if ((tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel) != (tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel))
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 4:
			switch (tITEM_INFO1->iLevel)
			{
			case 100:
				if (tITEM_INFO2->iLevel != 95)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 110:
				if (tITEM_INFO2->iLevel != 105)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 115:
				if (tITEM_INFO2->iLevel != 114)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 118:
				if (tITEM_INFO2->iLevel != 117)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 121:
				if (tITEM_INFO2->iLevel != 120)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 124:
				if (tITEM_INFO2->iLevel != 123)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 127:
				if (tITEM_INFO2->iLevel != 126)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 130:
				if (tITEM_INFO2->iLevel != 129)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 133:
				if (tITEM_INFO2->iLevel != 132)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 136:
				if (tITEM_INFO2->iLevel != 135)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 139:
				if (tITEM_INFO2->iLevel != 138)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 142:
				if (tITEM_INFO2->iLevel != 141)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				break;
			case 145:
#ifdef __GOD__
				if (tITEM_INFO1->iMartialLevel < 1)
				{
#endif
					if ((tITEM_INFO2->iLevel != 144) && (tITEM_INFO2->iLevel != 145))
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
#ifdef __GOD__
				}
				else
				{
					if ((tITEM_INFO2->iLevel + tITEM_INFO2->iMartialLevel) != (tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel))
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
#endif
				break;
			}
			break;
		}
	}
	// Warlord CS
	if (tITEM_INFO1->iCheckItemSet == 2)
	{
		switch (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]))
		{
		case 0:
			tCost = 100000000;
			tProbability = 65;
			break;
		case 1:
			tCost = 150000000;
			tProbability = 60;
			break;
		case 2:
			tCost = 200000000;
			tProbability = 55;
			break;
		case 3:
			tCost = 250000000;
			tProbability = 50;
			break;
		case 4:
			tCost = 300000000;
			tProbability = 45;
			break;
		case 5:
			tCost = 350000000;
			tProbability = 40;
			break;
		case 6:
			tCost = 400000000;
			tProbability = 35;
			break;
		case 7:
			tCost = 450000000;
			tProbability = 30;
			break;
		case 8:
			tCost = 500000000;
			tProbability = 25;
			break;
		case 9:
			tCost = 550000000;
			tProbability = 20;
			break;
		case 10:
			tCost = 600000000;
			tProbability = 15;
			break;
		case 11:
			tCost = 650000000;
			tProbability = 10;
			break;
		}
	}
	else
	{
		switch (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]))
		{
		case 0:
			tCost = 1000000;
			tProbability = 65;
			break;
		case 1:
			tCost = 1500000;
			tProbability = 60;
			break;
		case 2:
			tCost = 2000000;
			tProbability = 55;
			break;
		case 3:
			tCost = 2500000;
			tProbability = 50;
			break;
		case 4:
			tCost = 3000000;
			tProbability = 45;
			break;
		case 5:
			tCost = 3500000;
			tProbability = 40;
			break;
		case 6:
			tCost = 4000000;
			tProbability = 35;
			break;
		case 7:
			tCost = 4500000;
			tProbability = 30;
			break;
		case 8:
			tCost = 5000000;
			tProbability = 25;
			break;
		case 9:
			tCost = 5500000;
			tProbability = 20;
			break;
		case 10:
			tCost = 6000000;
			tProbability = 15;
			break;
		case 11:
			tCost = 6500000;
			tProbability = 10;
			break;
		}
	}
	if (mUSER[tUserIndex].mAvatarInfo.aPremiumService > 0)
	{
		tCost = tCost - (tCost * 0.20f);
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	// Lucky Combine
	if (mUSER[tUserIndex].mAvatarInfo.aLuckyCombine > 0)
	{
		tProbability += 5;
		mUSER[tUserIndex].mAvatarInfo.aLuckyCombine--;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(28, mUSER[tUserIndex].mAvatarInfo.aLuckyCombine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	if (tITEM_INFO2->iIndex == 2001 || tITEM_INFO2->iIndex == 2002 || tITEM_INFO2->iIndex == 2003)
	{
		switch (tITEM_INFO2->iIndex)
		{
		case 2001: tProbability = 50; break;
		case 2002: tProbability = 80; break;
		case 2003: tProbability = 100; break;
		}
	}

	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mGAMELOG.GL_634_ADD_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mGAMELOG.GL_634_ADD_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
		mTRANSFER.B_ADD_ITEM_RECV(0, tCost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_634_ADD_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
	mTRANSFER.B_ADD_ITEM_RECV(1, tCost);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_IMPROVE_ITEM_SEND
void W_IMPROVE_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost = 0;
	int tValue = 0;
	int tIsUseTicket = 0;
	int tProbability1 = 0;
	int tProbability2 = 0;
	int tRandom = 0;
	BYTE tBroadcastInfoData[100];

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);

	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 6) && (tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21) && (tITEM_INFO1->iSort != 29))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckImprove != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iType > 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tITEM_INFO2->iIndex)
	{
	case 1019: tCost = 10000; tValue = 1; break;
	case 1020: tCost = 30000; tValue = 2; break;
	case 1021: tCost = 50000; tValue = 3; break;
	case 1022: tCost = 70000; tValue = 4; break;
	case 1023: tCost = 90000; tValue = 5; break;
	case 1437: tCost = 130000; tValue = 2; break;
	case 1422: tCost = 0; tValue = 1; break;
	// Tickets
	case 619: tCost = 0; tValue = 40; tIsUseTicket = 1; break;
	case 825: tCost = 0; tValue = 50; tIsUseTicket = 1; break;
	case 633: tCost = 0; tValue = 1; break;
	case 695: tCost = 50; tValue = 1; break;
	case 696: tCost = 50; tValue = 2; break;
	case 698: tCost = 50; tValue = 3; break;
	case 826: tCost = 50; tValue = 40; tIsUseTicket = 1; break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tSort)
	{
	case 1: // Equipment Enchant 0 ~ 120%
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 40) // Only for 0 ~ 120
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// Check Mats
		if ( tITEM_INFO2->iIndex != 1019 && tITEM_INFO2->iIndex != 1020 && tITEM_INFO2->iIndex != 1021 && tITEM_INFO2->iIndex != 1022 && tITEM_INFO2->iIndex != 1023
			&& tITEM_INFO2->iIndex != 825 && tITEM_INFO2->iIndex != 619 && tITEM_INFO2->iIndex != 633)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tIsUseTicket == 0)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue > 40)
			{
				tValue = 40 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
		}
		tProbability1 = 93 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue) * 3 + (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
		if (tProbability1 < 20)
		{
			tProbability1 = 20;
		}
		// Tickets 100% Success
		if ( tITEM_INFO2->iIndex == 825 || tITEM_INFO2->iIndex == 619 || tITEM_INFO2->iIndex == 633 )
		{
			tProbability1 = 100;
		}
		tProbability2 = -57 + (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue) * 3; /*- (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 1000.0f);*/
		if (tProbability2 < 0)
		{
			tProbability2 = 0;
		}
		// Enchant Talisman
		if ( mUSER[tUserIndex].mAvatarInfo.aEnchantTalisman > 0 )
		{
			tProbability1 += 10;
			mUSER[tUserIndex].mAvatarInfo.aEnchantTalisman--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(170, mUSER[tUserIndex].mAvatarInfo.aEnchantTalisman);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		tRandom = rand() % 100;
		// Success
		if (tRandom < tProbability1)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			if (tIsUseTicket == 1)
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			else
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			
			// Non Stackable Mat
			/*mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;*/

			// Stackable Mat
			if (tITEM_INFO2->iCheckExpire == 99 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] > 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] --;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			}
			//


			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_IMPROVE_ITEM_NUM)
			{
				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(111, &tBroadcastInfoData[0]);
			}
			return;
		}
		// Break
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 20)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);

			// Non Stackable Mat
			/*mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;*/

			// Stackable Mat
			if (tITEM_INFO2->iCheckExpire == 99 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] > 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] --;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			}
			//
			mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand() % 100;
		if ( tRandom < tProbability2 ) // Break Chance
		{
			if (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);

				// Non Stackable Mat
				/*mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;*/

				// Stackable Mat
				if (tITEM_INFO2->iCheckExpire == 99 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] > 1)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] --;
				}
				else
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				}
				//
				mInvenSocket[tPage2][tIndex2][0] = 0;
				mInvenSocket[tPage2][tIndex2][1] = 0;
				mInvenSocket[tPage2][tIndex2][2] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;

			// Non Stackable Mat
			/*mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;*/

			// Stackable Mat
			if (tITEM_INFO2->iCheckExpire == 99 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] > 1)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] --;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			}
			//
			mInvenSocket[tPage1][tIndex1][0] = 0;
			mInvenSocket[tPage1][tIndex1][1] = 0;
			mInvenSocket[tPage1][tIndex1][2] = 0;
			mInvenSocket[tPage2][tIndex2][0] = 0;
			mInvenSocket[tPage2][tIndex2][1] = 0;
			mInvenSocket[tPage2][tIndex2][2] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(2, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);

		// Non Stackable Mat
		/*mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;*/

		// Stackable Mat
		if (tITEM_INFO2->iCheckExpire == 99 && mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] > 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] --;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		}
		//
		mInvenSocket[tPage2][tIndex2][0] = 0;
		mInvenSocket[tPage2][tIndex2][1] = 0;
		mInvenSocket[tPage2][tIndex2][2] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2: // Wing Enchant 0 ~ 120%
		if ( tITEM_INFO1->iSort != 6 ) // Not Wing
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 40) // Max Enchant Reached
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < tCost)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// Check Feathers
		if (tITEM_INFO2->iIndex != 695 && tITEM_INFO2->iIndex != 696 && tITEM_INFO2->iIndex != 698 && tITEM_INFO2->iIndex != 826)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tIsUseTicket == 0)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue > 40)
			{
				tValue = 40 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
		}
		tProbability1 = 93 - (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue) * 3 + (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 100.0f);
		if (tProbability1 < 10)
		{
			tProbability1 = 10;
		}
		// Wing Talisman
		if ( mUSER[tUserIndex].mAvatarInfo.aWingEnchantTalisman > 0 )
		{
			tProbability1 += 10;
			mUSER[tUserIndex].mAvatarInfo.aWingEnchantTalisman--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(172, mUSER[tUserIndex].mAvatarInfo.aWingEnchantTalisman);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		// Tickets 100% Success
		if ( tITEM_INFO2->iIndex == 826 )
		{
			tProbability1 = 100;
		}
		tProbability2 = -57 + (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue) * 3; /*- (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 1000.0f);*/
		if (tProbability2 < 0)
		{
			tProbability2 = 0;
		}
		tRandom = rand() % 100;
		// Success
		if (tRandom < tProbability1)
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tCost;
			if (tIsUseTicket == 1)
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			else
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 40)
			{
				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(115, &tBroadcastInfoData[0]);
			}
			return;
		}
		// Break Chance
		tRandom = rand() % 100;
		if (tRandom < tProbability2)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(99, mUSER[tUserIndex].mAvatarInfo.aWingProtectionScroll);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tCost;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tCost;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mInvenSocket[tPage1][tIndex1][0] = 0;
			mInvenSocket[tPage1][tIndex1][1] = 0;
			mInvenSocket[tPage1][tIndex1][2] = 0;
			mInvenSocket[tPage2][tIndex2][0] = 0;
			mInvenSocket[tPage2][tIndex2][1] = 0;
			mInvenSocket[tPage2][tIndex2][2] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(2, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= tCost;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= tCost;
		mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3: // Overenchant 123 ~ 150
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_IMPROVE_ITEM_NUM) // Max Enchant Reached
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 41) // Not Allowed below 123%
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tCost = 25000000;
		if ( mUSER[tUserIndex].mAvatarInfo.aMoney < tCost )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// Check Mats
		if (tITEM_INFO2->iIndex != 1437 && tITEM_INFO2->iIndex != 1023 && tITEM_INFO2->iIndex != 825 && tITEM_INFO2->iIndex != 633)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// 15% Mats Becomes 3%
		if ( tITEM_INFO2->iIndex == 1023 )
		{
			tValue = 1;
		}
		if (tIsUseTicket == 0)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + tValue > MAX_IMPROVE_ITEM_NUM)
			{
				tValue = MAX_IMPROVE_ITEM_NUM - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
		}
		tProbability1 = 30; // 30% Success Rate
		// Tickets 100% Success
		if (tITEM_INFO2->iIndex == 825 || tITEM_INFO2->iIndex == 619 || tITEM_INFO2->iIndex == 633)
		{
			tProbability1 = 100;
		}
		// Enchant Talisman
		if (mUSER[tUserIndex].mAvatarInfo.aEnchantTalismanSP > 0)
		{
			tProbability1 += 10;
			mUSER[tUserIndex].mAvatarInfo.aEnchantTalismanSP--;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(171, mUSER[tUserIndex].mAvatarInfo.aEnchantTalismanSP);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		tProbability2 = 100;
		tRandom = rand() % 100;
		// Success
		if (tRandom < tProbability1)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			if (tIsUseTicket == 1)
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			else
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= MAX_IMPROVE_ITEM_NUM)
			{
				CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
				CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(111, &tBroadcastInfoData[0]);
			}
			return;
		}
		// Break
		tRandom = rand() % 100;
		if (tRandom < tProbability2)
		{
			if ( mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 41 )
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 40);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy--;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(15, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_IMPROVE_ITEM_RECV(1, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 40);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 40);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV(3, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal, mTRANSFER.mOriginalSize);
		return;

	case 4: // Unseal
		if (tITEM_INFO1->iSort == 6) // Can Not use Unseal on Deco/Wings
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 40) // Not For Unsealment
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		// Check Mats
		if (tITEM_INFO2->iIndex != 1422 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tValue);
		mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_IMPROVE_ITEM_RECV(0, tCost, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;


	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;


	}
}

//W_PROCESS_ATTACK_SEND
void W_PROCESS_ATTACK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	ATTACK_FOR_PROTOCOL tAttackInfo;
	CopyMemory(&tAttackInfo, &tPacket[1], sizeof(ATTACK_FOR_PROTOCOL));

	tAttackInfo.mPitifulStrikeValue = 0;
	tAttackInfo.mNewAttackValue = 0;
	tAttackInfo.mSpiritDamage = 0;

	switch (tAttackInfo.mCase)
	{
	case 1: //[bismut]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack01(tUserIndex, &tAttackInfo);
		return;
	case 2: //[Influence]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack02(tUserIndex, &tAttackInfo);
		return;
	case 3: //[Character->Monster]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum != 1)
			{
				if (mAVATAR_OBJECT[tUserIndex].CheckIfSpeedHack(tUserIndex, &tAttackInfo))
				{
					return;
				}
			}
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				// mLog("time = %d", GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed); // Measure in-between skill duration
				if (mAVATAR_OBJECT[tUserIndex].CheckIfSpeedHack(tUserIndex, &tAttackInfo))
				{
					return;
				}
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack03(tUserIndex, &tAttackInfo);
		return;
	case 4: //[Monster->Character]
		mGAME.ProcessAttack04(tUserIndex, &tAttackInfo);
		return;
	case 5: //[puncture]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack05(tUserIndex, &tAttackInfo);
		return;
	case 6: //[Stun]
		if ((tAttackInfo.mServerIndex1 == tUserIndex) && (tAttackInfo.mUniqueNumber1 == mAVATAR_OBJECT[tUserIndex].mUniqueNumber))
		{
			if (mUSER[tUserIndex].mCheckMaxAttackPacketNum == 1)
			{
				mUSER[tUserIndex].mNowAttackPacketNum++;
				if (mUSER[tUserIndex].mNowAttackPacketNum > mUSER[tUserIndex].mMaxAttackPacketNum)
				{
					return;
				}
				if (tAttackInfo.mAttackActionValue4 != mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort)
				{
					return;
				}
			}
		}
		mGAME.ProcessAttack06(tUserIndex, &tAttackInfo);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_PROCESS_DATA_SEND
void W_PROCESS_DATA_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_BROADCAST_DATA_SIZE);

	mWORK.ProcessForData(tUserIndex, tSort, &tData[0]);
}
//W_GENERAL_CHAT_SEND
void W_GENERAL_CHAT_SEND(int tUserIndex)
{
	// unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int index01;
	float tPostLocation[3];
	int tSpaceIndex[3];
	float tLocation[3];

	tPostLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
	tPostLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
	tPostLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
	tSpaceIndex[0] = (int)(tPostLocation[0] / MAX_RADIUS_FOR_NETWORK);
	tSpaceIndex[1] = (int)(tPostLocation[1] / MAX_RADIUS_FOR_NETWORK);
	tSpaceIndex[2] = (int)(tPostLocation[2] / MAX_RADIUS_FOR_NETWORK);

#ifdef __WREGION__
	mUSER[tUserIndex].monsterforspawn = atoi(tContent);
#endif

	mTRANSFER.B_GENERAL_CHAT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0]);
	mGAMELOG.CHAT_LOG_SEND(tUserIndex, &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0], "W_GENERAL_CHAT_SEND");
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if (1 != mUSER[tUserIndex].mAuthInfo.AuthType)
		{
			if ((1 != mUSER[index01].mAuthInfo.AuthType) || (1 != mAVATAR_OBJECT[index01].mChat))
			{
				if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
				{
					continue;
				}
			}
		}
		else
		{
			if (1 != mAVATAR_OBJECT[tUserIndex].mChat)
			{
				if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
				{
					continue;
				}
			}
		}
		if ((1 != mUSER[tUserIndex].mAuthInfo.AuthType) && (1 != mUSER[index01].mAuthInfo.AuthType))
		{
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
			{
				continue;
			}
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
		{
			continue;
		}
		if ((abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[0] - tSpaceIndex[0]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[1] - tSpaceIndex[1]) > 1) || (abs(mAVATAR_OBJECT[index01].mSPACE_INDEX[2] - tSpaceIndex[2]) > 1))
		{
			continue;
		}
		tLocation[0] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0];
		tLocation[1] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1];
		tLocation[2] = mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2];
		if (((tLocation[0] - tPostLocation[0]) * (tLocation[0] - tPostLocation[0]) + (tLocation[1] - tPostLocation[1]) * (tLocation[1] - tPostLocation[1]) + (tLocation[2] - tPostLocation[2]) * (tLocation[2] - tPostLocation[2])) > (MAX_RADIUS_FOR_NETWORK * MAX_RADIUS_FOR_NETWORK))
		{
			continue;
		}
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}

//W_SECRET_CHAT_SEND
void W_SECRET_CHAT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tContent[0], &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((strncmp(mUSER[tUserIndex].mAvatarInfo.aName, tAvatarName, MAX_AVATAR_NAME_LENGTH) == 0) || (strcmp(tAvatarName, "") == 0))
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
	if (mPLAYUSER_COM.mRecv_ZoneNumber < 1)
	{
		mTRANSFER.B_SECRET_CHAT_RECV(1, 0, &tAvatarName[0], &tContent[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		if ((mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe) && (mUSER[tUserIndex].mAvatarInfo.aTribe != mGAME.ReturnAllianceTribe(mPLAYUSER_COM.mRecv_Tribe)))
		{
			mTRANSFER.B_SECRET_CHAT_RECV(2, 0, &tAvatarName[0], &tContent[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
	mTRANSFER.B_SECRET_CHAT_RECV(0, mPLAYUSER_COM.mRecv_ZoneNumber, &tAvatarName[0], &tContent[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAuthInfo.AuthType, 1);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(103, &tData[0]);
}

//W_TRIBE_NOTICE_SEND
void W_TRIBE_NOTICE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tTribeRole = 0;

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tTribeRole = mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe);
	if (tTribeRole != 1 && tTribeRole != 2)
	{
		return;
	}
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
	CopyMemory(&tData[(MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH) + 4], &tTribeRole, 4);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(113, &tData[0]);
}

//W_GENERAL_NOTICE_SEND
void W_GENERAL_NOTICE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		return;
	}
	if (mUSER[tUserIndex].mAuthInfo.AuthType == 0)
	{
		return;
	}
	if (mUSER[tUserIndex].mAuthInfo.NoticeFlag == 0) 
	{
		return;
	}
	CopyMemory(&tData[0], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
}
//W_TRIBE_CHAT_SEND
void W_TRIBE_CHAT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if ( mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1 < 10 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int index01;

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.aSpecialState == 2)
	{
		return;
	}

	mTRANSFER.B_TRIBE_CHAT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0]);
	mGAMELOG.CHAT_LOG_SEND(tUserIndex, &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0], "W_TRIBE_CHAT_SEND");
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[tUserIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tUserIndex].mDATA.aTribe)))
		{
			continue;
		}
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}

//W_FACTION_NOTICE_SEND
void W_FACTION_NOTICE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aFactionNoticeScroll < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	int index01;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aFactionNoticeScroll--;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(69, mUSER[tUserIndex].mAvatarInfo.aFactionNoticeScroll);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH], &tContent, MAX_CHAT_CONTENT_LENGTH);
	CopyMemory(&tData[MAX_AVATAR_NAME_LENGTH + MAX_CHAT_CONTENT_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(114, &tData[0]);
}

//W_TRADE_ASK_SEND
void W_TRADE_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;
	if ( mUSER[tUserIndex].mAuthInfo.TradeFlag == 1)
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 119) && (mSERVER_INFO.mServerNumber != 124))
	{
		if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag)
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TRADE_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aLevel1);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRADE_CANCEL_SEND
void W_TRADE_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRADE_ANSWER_SEND
void W_TRADE_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		break;
	default:
		return;
	}

	if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
	else 
	{
		mTRANSFER.B_TRADE_ANSWER_RECV(tAnswer);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}
//W_TRADE_START_SEND
void W_TRADE_START_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		return;
	}
	if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag)
	{
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_ANSWER_RECV(6);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV(mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney2, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeSocket);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu = 0;
	mTRANSFER.B_TRADE_START_RECV(mUSER[tUserIndex].mAvatarInfo.aTradeMoney, mUSER[tUserIndex].mAvatarInfo.aTrade, mUSER[tUserIndex].mAvatarInfo.aTradeMoney2, mUSER[tUserIndex].mAvatarInfo.aTradeSocket);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TRADE_MENU_SEND
void W_TRADE_MENU_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int index01;
	int index02;
	int tOtherAvatarIndex;
	int tTradeMoney;
	int tTradeMoney2;
	int tTrade[MAX_TRADE_SLOT_NUM][4];
	int tTradeSocket[MAX_TRADE_SLOT_NUM][MAX_SOCKETSYSTEM_ARRAY];

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4)
	{
		return;
	}
	switch (mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu)
	{
	case 0:
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
		{
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			return;
		}
		if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 2)
		{
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag)
		{
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 1;
		mTRANSFER.B_TRADE_MENU_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_MENU_RECV(1);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 1:
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
		{
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			return;
		}
		if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu == 0)
		{
			return;
		}
		if (1 == mUSER[tUserIndex].mAuthInfo.TradeFlag)
		{
			return;
		}
		else if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.TradeFlag)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessMenu = 2;
		mTRANSFER.B_TRADE_MENU_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRADE_MENU_RECV(1);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessMenu != 2)
		{
			return;
		}
		tTradeMoney = mUSER[tUserIndex].mAvatarInfo.aTradeMoney;
		tTradeMoney2 = mUSER[tUserIndex].mAvatarInfo.aTradeMoney2;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			tTrade[index01][0] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0];
			tTrade[index01][1] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1];
			tTrade[index01][2] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2];
			tTrade[index01][3] = mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3];
			for (index02 = 0; index02 < MAX_SOCKETSYSTEM_ARRAY; index02++)
			{
				tTradeSocket[index01][index02] = mUSER[tUserIndex].mAvatarInfo.aTradeSocket[index01][index02];
			}
		}
		if (mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney > 0 || mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney2 > 0)
		{
			mGAMELOG.GL_616_TRADE_MONEY(tOtherAvatarIndex, tUserIndex, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney, mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney2);
		}
		mUSER[tUserIndex].mAvatarInfo.aTradeMoney = mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney;
		mUSER[tUserIndex].mAvatarInfo.aTradeMoney2 = mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney2;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			if (mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] > 0)
			{
				mGAMELOG.GL_615_TRADE_ITEM(tOtherAvatarIndex, tUserIndex, mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2], mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3]);
			}
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][0] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][1] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][2] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2];
			mUSER[tUserIndex].mAvatarInfo.aTrade[index01][3] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3];
			for (index02 = 0; index02 < MAX_SOCKETSYSTEM_ARRAY; index02++)
			{
				mUSER[tUserIndex].mAvatarInfo.aTradeSocket[index01][index02] = mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeSocket[index01][index02];
			}
		}
		if (tTradeMoney > 0 || tTradeMoney2 > 0)
		{
			mGAMELOG.GL_616_TRADE_MONEY(tUserIndex, tOtherAvatarIndex, tTradeMoney, tTradeMoney2);
		}
		mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney = tTradeMoney;
		mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeMoney2 = tTradeMoney2;
		for (index01 = 0; index01 < MAX_TRADE_SLOT_NUM; index01++)
		{
			if (tTrade[index01][0] > 0)
			{
				mGAMELOG.GL_615_TRADE_ITEM(tUserIndex, tOtherAvatarIndex, tTrade[index01][0], tTrade[index01][1], tTrade[index01][2], tTrade[index01][3]);
			}
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][0] = tTrade[index01][0];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][1] = tTrade[index01][1];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][2] = tTrade[index01][2];
			mUSER[tOtherAvatarIndex].mAvatarInfo.aTrade[index01][3] = tTrade[index01][3];
			for (index02 = 0; index02 < MAX_SOCKETSYSTEM_ARRAY; index02++)
			{
				mUSER[tOtherAvatarIndex].mAvatarInfo.aTradeSocket[index01][index02] = tTradeSocket[index01][index02];
			}
		}
		mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_END_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
		mTRANSFER.B_TRADE_END_RECV(0);
		mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_TRADE_END_SEND
void W_TRADE_END_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTradeProcessState != 4)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV(1);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTradeProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState != 4)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTradeProcessState = 0;
	mTRANSFER.B_TRADE_END_RECV(1);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_FRIEND_ASK_SEND
void W_FRIEND_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int index01;
	int tOtherAvatarIndex;

	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") == 0)
		{
			break;
		}
	}
	if (index01 == MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], tAvatarName) == 0)
		{
			break;
		}
	}
	if (index01 < MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_FRIEND_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_FRIEND_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_CANCEL_SEND
void W_FRIEND_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
	mTRANSFER.B_FRIEND_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_ANSWER_SEND
void W_FRIEND_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_FRIEND_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_MAKE_SEND
void W_FRIEND_MAKE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tOtherAvatarIndex;

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mFriendProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mFriendProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFriendProcessState = 0;
	strncpy(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_FRIEND_MAKE_RECV(tIndex, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mFriendProcessState = 0;
}
//W_FRIEND_FIND_SEND
void W_FRIEND_FIND_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex][0]);
	if (mUSER[tUserIndex].mAvatarInfo.aTribe != mPLAYUSER_COM.mRecv_Tribe)
	{
		mTRANSFER.B_FRIEND_FIND_RECV(tIndex, -1);
	}
	else
	{
		mTRANSFER.B_FRIEND_FIND_RECV(tIndex, mPLAYUSER_COM.mRecv_ZoneNumber);
	}
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_FRIEND_DELETE_SEND
void W_FRIEND_DELETE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tIndex;
	CopyMemory(&tIndex, &tPacket[1], 4);
	if ((tIndex < 0) || (tIndex > (MAX_FRIEND_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo.aFriend[tIndex], "");
	mTRANSFER.B_FRIEND_DELETE_RECV(tIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

void W_COSTUME_STATE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO;
	int tSort;
	int tValue;
	int iPage = 0, iInvenIndex = 0, iInvenSlot = 0;
	int index01;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	switch (tSort)
	{
	case 1:
		if (tValue < 0 || tValue > 9)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aCostume[tValue] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aCostumeIndex = tValue;
		mTRANSFER.B_COSTUME_STATE_RECV(0, tSort, tValue, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:
		if (tValue < 0 || tValue > 9)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aCostumeIndex = -1;
		mTRANSFER.B_COSTUME_STATE_RECV(0, tSort, tValue, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3:
		if (mUSER[tUserIndex].mAvatarInfo.aCostumeIndex < 0 || mUSER[tUserIndex].mAvatarInfo.aCostumeIndex > 9)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = mUSER[tUserIndex].mAvatarInfo.aCostume[mUSER[tUserIndex].mAvatarInfo.aCostumeIndex];
		mUSER[tUserIndex].mAvatarInfo.aCostumeIndex += 10;
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_COSTUME_STATE_RECV(0, tSort, tValue, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 16, mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		return;

	case 4:
		if (mUSER[tUserIndex].mAvatarInfo.aCostumeIndex < 10 || mUSER[tUserIndex].mAvatarInfo.aCostumeIndex > 19)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aFashionNumber = 0;
		mUSER[tUserIndex].mAvatarInfo.aCostumeIndex -= 10;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_COSTUME_STATE_RECV(0, tSort, tValue, 0, 0, 0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 17, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		return;

	case 5:
		if (tValue < 0 || tValue > 9)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aCostumeIndex == -1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aCostumeIndex >= 10 && mUSER[tUserIndex].mAvatarInfo.aCostumeIndex <= 19)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aCostume[tValue] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTimedCostumeInventory[tValue] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aCostume[tValue]);
		if (tITEM_INFO == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, iPage, iInvenIndex))
		{
			mTRANSFER.B_COSTUME_STATE_RECV(2, tSort, tValue, 0, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		iInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, iPage);
		if (iInvenSlot == -1)
		{
			mTRANSFER.B_COSTUME_STATE_RECV(2, tSort, tValue, 0, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][0] = tITEM_INFO->iIndex;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][1] = iInvenIndex % 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][2] = iInvenIndex / 8;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
		mGAMELOG.GL_809_COSTUME_DELETE(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aCostume[tValue]);
		mUSER[tUserIndex].mAvatarInfo.aCostume[tValue] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTimedCostumeInventory[tValue] = 0;
		mUSER[tUserIndex].mAvatarInfo.aLegendaryCostume[tValue] = 0;
		for (index01 = mUSER[tUserIndex].mAvatarInfo.aCostumeIndex; index01 < 9; index01++)
		{
			mUSER[tUserIndex].mAvatarInfo.aCostume[index01] = mUSER[tUserIndex].mAvatarInfo.aCostume[index01 + 1];
			mUSER[tUserIndex].mAvatarInfo.aTimedCostumeInventory[index01] = mUSER[tUserIndex].mAvatarInfo.aTimedCostumeInventory[index01 + 1];
			mUSER[tUserIndex].mAvatarInfo.aLegendaryCostume[index01] = mUSER[tUserIndex].mAvatarInfo.aLegendaryCostume[index01 + 1];
		}
		mUSER[tUserIndex].mAvatarInfo.aCostumeIndex = -1;
		mUSER[tUserIndex].mAvatarInfo.aCostume[9] = 0;
		mUSER[tUserIndex].mAvatarInfo.aTimedCostumeInventory[9] = 0;
		mUSER[tUserIndex].mAvatarInfo.aLegendaryCostume[9] = 0;
		mTRANSFER.B_COSTUME_STATE_RECV(0, tSort, tValue, iPage, iInvenSlot, iInvenIndex, tITEM_INFO->iIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		return;
	}
}

//W_ABSORB_STATE_SEND
void W_ABSORB_STATE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMountAbsorbTime <= 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ( mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber == 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	CopyMemory(&tSort, &tPacket[1], 4);

	switch (tSort)
	{
	case 1:
		mUSER[tUserIndex].mAvatarInfo.aAbsorbState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState = 1;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 26, mUSER[tUserIndex].mAvatarInfo.aAbsorbState, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], TRUE);	
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		return;

	case 2:
		mUSER[tUserIndex].mAvatarInfo.aAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 26, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], TRUE);
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_ANIMAL_STATE_SEND
void W_ANIMAL_STATE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	int tRandomAbility[8];
	int tRandom;
	int index01;
	int tMountLevel = 0;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	switch (tSort)
	{
	case 1: //[SELECT]
		if ( tValue < 0 || tValue > MAX_AVATAR_ANIMAL_NUM - 1 )
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimal[tValue] == 0)
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM && mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= 19 )
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = tValue;
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2: //[CANCEL SELECT]
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex >= MAX_AVATAR_ANIMAL_NUM && mUSER[tUserIndex].mAvatarInfo.aAnimalIndex <= 19 )
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3: //[SUMMON]
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 0 || mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > MAX_AVATAR_ANIMAL_NUM - 1 )
		{
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalTime < 1)
		{
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex += 10;
		mUSER[tUserIndex].mAvatarInfo.aAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex - 10];
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
		if ( mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 12, mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mUSER[tUserIndex].mTickCountFor01Minute_2 = mGAME.mTickCount;
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 4: //[UNSUMMON]
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 10 || mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > 19 )
		{
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex -= 10;
		mUSER[tUserIndex].mAvatarInfo.aAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
		mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState = 0;
		mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip(); 
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue;
		}
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue > mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue)
		{
			mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue = mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue;
		}
		mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 13, 0, 0, 0);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], 1);
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 5: //[DELETE]
		if (mSERVER_INFO.mServerNumber >= 270 && mSERVER_INFO.mServerNumber <= 274)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimalIndex < 0 || mUSER[tUserIndex].mAvatarInfo.aAnimalIndex > MAX_AVATAR_ANIMAL_NUM - 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] != tValue )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] < 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mGAMELOG.GL_808_ANIMAL_DELETE(tUserIndex, mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex], mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex], mUSER[tUserIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex]);
		mUSER[tUserIndex].mAvatarInfo.aAnimal[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.aAnimalAbilityStats[mUSER[tUserIndex].mAvatarInfo.aAnimalIndex] = 0;
		mUSER[tUserIndex].mAvatarInfo.aAnimalIndex = -1;
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 6: //[Mount Exp -> Stats]
		if ( mAnimal[mAnimalIndex - 10] < 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mAnimalExp[mAnimalIndex - 10] % 1000000 < 100000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < 8; index01++)
		{
			tMountLevel += mAnimalStat[mAnimalIndex - 10] % (int)pow(10, index01 + 1) / pow(10, index01);
		}
		if (tMountLevel >= 25)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnMountSort(mCharAnimal) != 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand() % 8;
		if ( mAnimalStat[mAnimalIndex - 10] % (int)pow(10, tRandom + 1) / pow(10, tRandom) < 9 )
		{
			mAnimalExp[mAnimalIndex - 10] -= 100000;
			mAnimalStat[mAnimalIndex - 10] += pow(10, tRandom);
			mTRANSFER.B_ANIMAL_STATE_RECV(tSort, mAnimalStat[mAnimalIndex - 10]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_ANIMAL_STATE_RECV(tSort, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_START_PSHOP_SEND
#define tPage	tPShopInfo.mItemInfo[index01][index02][5]
#define tIndex	tPShopInfo.mItemInfo[index01][index02][6]
void W_START_PSHOP_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ( mSERVER_INFO.mServerNumber == 124 )
	{
		return;
	}

	int tSort;
	PSHOP_INFO tPShopInfo;
	PROXYSHOP_INFO tProxyInfo;
	int tProxyShopForStartIndex;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPShopInfo, &tPacket[5], sizeof(PSHOP_INFO));

	if ( mUSER[tUserIndex].mAuthInfo.PShopFlag == 1)
	{
		mTRANSFER.B_START_PSHOP_RECV(1, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	int index01;
	int index02;
	ITEM_INFO* tITEM_INFO;

	if (mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mPROXY_OBJECT->CheckIfProxyActive(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName))
	{
		mTRANSFER.B_START_PSHOP_RECV(102, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (!mWORK.CheckPossiblePShopRegion(mUSER[tUserIndex].mAvatarInfo.aTribe, mSERVER_INFO.mServerNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0]))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort != 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tSort)
	{
	case 1:
		if (strcmp(tPShopInfo.mName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] > 0)
				{
					break;
				}
			}
			if (index02 < MAX_PSHOP_SLOT_NUM)
			{
				break;
			}
		}
		if (index01 == MAX_PSHOP_PAGE_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] < 1)
				{
					continue;
				}
				tITEM_INFO = mITEM.Search(tPShopInfo.mItemInfo[index01][index02][0]);
				if (tITEM_INFO == NULL)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tITEM_INFO->iCheckAvatarShop == 1)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if ((tPShopInfo.mItemInfo[index01][index02][5] < 0) || (tPShopInfo.mItemInfo[index01][index02][5] > 1) || (tPShopInfo.mItemInfo[index01][index02][6] < 0) || (tPShopInfo.mItemInfo[index01][index02][6] > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPShopInfo.mItemInfo[index01][index02][7] < 0) || (tPShopInfo.mItemInfo[index01][index02][7] > 7) || (tPShopInfo.mItemInfo[index01][index02][8] < 0) || (tPShopInfo.mItemInfo[index01][index02][8] > 7))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if (tPShopInfo.mItemInfo[index01][index02][5] == 1)
				{
					if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				if ((tPShopInfo.mItemInfo[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][0]) || (tPShopInfo.mItemInfo[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][3]) || (tPShopInfo.mItemInfo[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][4]) || (tPShopInfo.mItemInfo[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][5]) || (tPShopInfo.mItemInfo[index01][index02][7] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][1]) || (tPShopInfo.mItemInfo[index01][index02][8] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPShopInfo.mItemInfo[index01][index02][5]][tPShopInfo.mItemInfo[index01][index02][6]][2]))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
				if ((tPShopInfo.mItemInfo[index01][index02][4] < 1) || (tPShopInfo.mItemInfo[index01][index02][4] > 999999999))
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 1;
		strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, tPShopInfo.mName, MAX_PSHOP_NAME_LENGTH);
		CopyMemory(&mAVATAR_OBJECT[tUserIndex].mPShopInfo, &tPShopInfo, sizeof(PSHOP_INFO));
		mAVATAR_OBJECT[tUserIndex].mPShopInfo.mUniqueNumber = mGAME.mAvatarPShopUniqueNumber;
		mGAME.mAvatarPShopUniqueNumber++;
		mTRANSFER.B_START_PSHOP_RECV(0, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		break;

	case 2:
		switch (mMyTribe)
		{
		case 0:
			if (mSERVER_INFO.mServerNumber != 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 1:
			if (mSERVER_INFO.mServerNumber != 6)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2:
			if (mSERVER_INFO.mServerNumber != 11)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 3:
			if (mSERVER_INFO.mServerNumber != 140)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		}
		tProxyShopForStartIndex = mPROXY_OBJECT->GetFreeProxyIndexForStart();
		if (tProxyShopForStartIndex == -1)
		{
			mTRANSFER.B_START_PSHOP_RECV(105, &tPShopInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (strcmp(tPShopInfo.mName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_PSHOP_PAGE_NUM; index01++)
		{
			for (index02 = 0; index02 < MAX_PSHOP_SLOT_NUM; index02++)
			{
				if (tPShopInfo.mItemInfo[index01][index02][0] > 0)
				{
					break;
				}
			}
			if (index02 < MAX_PSHOP_SLOT_NUM)
			{
				break;
			}
		}
		if (index01 == MAX_PSHOP_PAGE_NUM)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		ZeroMemory(&tProxyInfo, sizeof(tProxyInfo));
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));
		for (index01 = 0; index01 < 5; index01++)
		{
			for (index02 = 0; index02 < 5; index02++)
			{
				if(mPLAYUSER_COM.mRecv_Proxy.mItemInfo[index01][index02][0] > 0)
				{
					if(tPShopInfo.mItemInfo[index01][index02][5] != -1 ||
					   tPShopInfo.mItemInfo[index01][index02][6] != -1 ||
					   tPShopInfo.mItemInfo[index01][index02][7] != -1 ||
					   tPShopInfo.mItemInfo[index01][index02][8] != -1)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					if( tPShopInfo.mItemInfo[index01][index02][0] != tProxyInfo.mItemInfo[index01][index02][0] ||
						tPShopInfo.mItemInfo[index01][index02][1] != tProxyInfo.mItemInfo[index01][index02][1] ||
						tPShopInfo.mItemInfo[index01][index02][2] != tProxyInfo.mItemInfo[index01][index02][2] ||
						tPShopInfo.mItemInfo[index01][index02][3] != tProxyInfo.mItemInfo[index01][index02][3] ||
						tPShopInfo.mItemInfo[index01][index02][4] != tProxyInfo.mItemInfo[index01][index02][4] )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					if ( tPShopInfo.mItemSocket[index01][index02][0] != tProxyInfo.mItemSocket[index01][index02][0] ||
						tPShopInfo.mItemSocket[index01][index02][1] != tProxyInfo.mItemSocket[index01][index02][1] ||
						tPShopInfo.mItemSocket[index01][index02][2] != tProxyInfo.mItemSocket[index01][index02][2] ||
						tPShopInfo.mItemSocket[index01][index02][3] != tProxyInfo.mItemSocket[index01][index02][3] ||
						tPShopInfo.mItemSocket[index01][index02][4] != tProxyInfo.mItemSocket[index01][index02][4] )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
				else
				{
					if ( tPShopInfo.mItemInfo[index01][index02][0] < 1 )
					{
						continue;
					}
					if( tPShopInfo.mItemInfo[index01][index02][5] < 0 ||
						tPShopInfo.mItemInfo[index01][index02][5] > 1 || 
						tPShopInfo.mItemInfo[index01][index02][6] < 0 || 
						tPShopInfo.mItemInfo[index01][index02][6] > (MAX_INVENTORY_SLOT_NUM - 1) || 
						tPShopInfo.mItemInfo[index01][index02][7] < 0 || 
						tPShopInfo.mItemInfo[index01][index02][7] > 7 || 
						tPShopInfo.mItemInfo[index01][index02][8] < 0 || 
						tPShopInfo.mItemInfo[index01][index02][8] > 7 )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					if (tPShopInfo.mItemInfo[index01][index02][5] == 1)
					{
						if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
						{
							mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
							return;
						}
					}
					if( tPShopInfo.mItemInfo[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] ||
						tPShopInfo.mItemInfo[index01][index02][7] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] ||
						tPShopInfo.mItemInfo[index01][index02][8] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] ||
						tPShopInfo.mItemInfo[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] ||
						tPShopInfo.mItemInfo[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] ||
						tPShopInfo.mItemInfo[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					if( tPShopInfo.mItemSocket[index01][index02][0] != mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][0] ||
						tPShopInfo.mItemSocket[index01][index02][1] != mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][1] ||
						tPShopInfo.mItemSocket[index01][index02][2] != mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][2] ||
						tPShopInfo.mItemSocket[index01][index02][3] != mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][3] ||
						tPShopInfo.mItemSocket[index01][index02][4] != mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][4] )
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					if( tPShopInfo.mItemInfo[index01][index02][4] < 1 ||
						tPShopInfo.mItemInfo[index01][index02][4] > 999999999)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
				}
			}
		}
		strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, tPShopInfo.mName, MAX_PSHOP_NAME_LENGTH); // incase of error, uncomment
		mAVATAR_OBJECT[tUserIndex].mPShopInfo.mUniqueNumber = mGAME.mAvatarPShopUniqueNumber;
		mPROXY_OBJECT[tProxyShopForStartIndex].mProxyUserIndex = tProxyShopForStartIndex;
		mPROXY_OBJECT[tProxyShopForStartIndex].mUniqueNumber = mGAME.mAvatarPShopUniqueNumber;
		mPROXY_OBJECT[tProxyShopForStartIndex].mCheckValidState = TRUE;
		strncpy(mPROXY_OBJECT[tProxyShopForStartIndex].mProxyShopAvatarName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		strncpy(mPROXY_OBJECT[tProxyShopForStartIndex].mProxyShopName, mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, MAX_PSHOP_NAME_LENGTH);
		strncpy(mPROXY_OBJECT[tProxyShopForStartIndex].mID, mUSER[tUserIndex].uID, MAX_USER_ID_LENGTH);
		mPROXY_OBJECT[tProxyShopForStartIndex].mProxyShopLocation[0] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0];
		mPROXY_OBJECT[tProxyShopForStartIndex].mProxyShopLocation[1] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[1];
		mPROXY_OBJECT[tProxyShopForStartIndex].mProxyShopLocation[2] = mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[2];
		mGAME.mAvatarPShopUniqueNumber++;
		for (index01 = 0; index01 < 5; index01++)
		{
			for (index02 = 0; index02 < 5; index02++)
			{
				for (int i = 0; i < 5; i++)
				{
					tProxyInfo.mItemInfo[index01][index02][i] = tPShopInfo.mItemInfo[index01][index02][i];
					tProxyInfo.mItemSocket[index01][index02][i] = tPShopInfo.mItemSocket[index01][index02][i];
				}
				if (tPShopInfo.mItemInfo[index01][index02][5] < 0 && tPShopInfo.mItemInfo[index01][index02][6] < 0)
				{
					continue;
				}
				for (int i = 0; i < 6; i++)
				{
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][i] = 0;
					if (i < 5)
					{
						mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage][tIndex][i] = 0;
					}
				}
				for (int i = 0; i < 9; i++)
				{
					tPShopInfo.mItemInfo[index01][index02][i] = 0;
					if (i < 5)
					{
						tPShopInfo.mItemSocket[index01][index02][i] = 0;
					}
				}
			}
		}
		mPLAYUSER_COM.U_REGISTER_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, 1, &tProxyInfo);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_START_PSHOP_RECV(100, &tPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_PROXY_SHOP(tProxyShopForStartIndex, mAVATAR_OBJECT[tUserIndex].mPShopInfo.mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], mUSER[tUserIndex].mAvatarInfo.aName, mAVATAR_OBJECT[tUserIndex].mDATA.aPShopName, 2);
		mUTIL.Broadcast(FALSE, NULL, 0);
		return;
	}
}
#undef tPage
#undef tIndex
//CHECK_POSSIBLE_PSHOP_REGION
BOOL MyWork::CheckPossiblePShopRegion(int tTribe, int tZoneNumber, float tCoord[3])
{
	float tCenter[3];
	float tRadius;

	switch (tZoneNumber)
	{
	case   1:
		if (tTribe != 0)
		{
			return FALSE;
		}
		tCenter[0] = 4.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -2.0f;
		tRadius = 1000.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case   6:
		if (tTribe != 1)
		{
			return FALSE;
		}
		tCenter[0] = -189.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 1150.0f;
		tRadius = 1000.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case  11:
		if (tTribe != 2)
		{
			return FALSE;
		}
		tCenter[0] = 449.0f;
		tCenter[1] = 1.0f;
		tCenter[2] = 439.0f;
		tRadius = 1000.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case 140:
		if (tTribe != 3)
		{
			return FALSE;
		}
		tCenter[0] = 452.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = 487.0f;
		tRadius = 1000.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	case  37:
		tCenter[0] = 1.0f;
		tCenter[1] = 0.0f;
		tCenter[2] = -1478.0f;
		tRadius = 1000.0f;
		if (mUTIL.GetLengthXYZ(&tCoord[0], &tCenter[0]) < tRadius)
		{
			return TRUE;
		}
		return FALSE;
	}
	return FALSE;
}
//W_END_PSHOP_SEND
void W_END_PSHOP_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	int tResult;
	int tProxyIndex;
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	CopyMemory(&tResult, &tPacket[1], 4);

	switch (tResult)
	{
	case 1: // PSHOP
		if (mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState != 1)
		{
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mDATA.aPShopState = 0;
		mTRANSFER.B_END_PSHOP_RECV(tResult);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2: // PROXY_SHOP
		tProxyIndex = mPROXY_OBJECT->GetProxyIndex2(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
		if (tProxyIndex != -1)
		{
			mTRANSFER.B_PROXY_SHOP(mPROXY_OBJECT[tProxyIndex].mProxyUserIndex, mPROXY_OBJECT[tProxyIndex].mUniqueNumber, &mPROXY_OBJECT[tProxyIndex].mProxyShopLocation[0], mPROXY_OBJECT[tProxyIndex].mProxyShopAvatarName, mPROXY_OBJECT[tProxyIndex].mProxyShopName, 3);
			mUTIL.Broadcast(FALSE, NULL, 0);
			mPROXY_OBJECT[tProxyIndex].Free();
			mTRANSFER.B_END_PSHOP_RECV(tResult);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		return;

	default:
		break;
	}
}
// W_DEMAND_PSHOP_SEND
void W_DEMAND_PSHOP_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);

	int tOtherAvatarIndex;

	tOtherAvatarIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(1, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(1, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1)
	{
		mTRANSFER.B_DEMAND_PSHOP_RECV(2, &mAVATAR_OBJECT[0].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// W_PSHOP_ITEM_INFO_SEND
void W_PSHOP_ITEM_INFO_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tSort1;
	int tSort2;
	int index01;
	int index02;
	int index03;
	int tValue[9];
	CopyMemory(&tSort1, &tPacket[1], 4);
	CopyMemory(&tSort2, &tPacket[5], 4);

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (mAVATAR_OBJECT[index01].mDATA.aPShopState == 1)
		{
			for (index02 = 0; index02 < 5; index02++)
			{
				for (index03 = 0; index03 < 5; index03++)
				{
					if (mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][0] < 1)
					{
						continue;
					}
					tValue[0] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][0];
					tValue[1] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][1];
					tValue[2] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][2];
					tValue[3] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][3];
					tValue[4] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][4];
					tValue[5] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][5];
					tValue[6] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][6];
					tValue[7] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][7];
					tValue[8] = mAVATAR_OBJECT[index01].mPShopInfo.mItemInfo[index02][index03][8];
					mTRANSFER.B_PSHOP_ITEM_INFO_RECV(mAVATAR_OBJECT[index01].mPShopInfo.mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA.aName[0], index02, index03, &tValue[0], &mAVATAR_OBJECT[index01].mPShopInfo.mItemSocket[index02][index03][0]);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
	}
}
// W_BUY_PSHOP_SEND
void W_BUY_PSHOP_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	DWORD tUniqueNumber;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tPage1;
	int tIndex1;
	int tQuantity1;
	int tPage2;
	int tIndex2;
	int tXPost2;
	int tYPost2;
	CopyMemory(&tUniqueNumber, &tPacket[1], 4);
	CopyMemory(&tAvatarName[0], &tPacket[5], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tPage1, &tPacket[(5 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tIndex1, &tPacket[(9 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tQuantity1, &tPacket[(13 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tPage2, &tPacket[(17 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tIndex2, &tPacket[(21 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tXPost2, &tPacket[(25 + MAX_AVATAR_NAME_LENGTH)], 4);
	CopyMemory(&tYPost2, &tPacket[(29 + MAX_AVATAR_NAME_LENGTH)], 4);

	if ((tPage1 < 0) || (tPage1 > (MAX_PSHOP_PAGE_NUM - 1)) || (tIndex1 < 0) || (tIndex1 > (MAX_PSHOP_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tXPost2 < 0) || (tXPost2 > 7) || (tYPost2 < 0) || (tYPost2 > 7))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tOtherAvatarIndex;
	int tItemInfo[9];
	int tValue[6];
	int tItemSocket[MAX_SOCKETSYSTEM_ARRAY];
	int index01;
	int index02;
	int index03;

	if (mUSER[tUserIndex].mAuthInfo.PShopFlag == 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(8, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	tOtherAvatarIndex = mUTIL.SearchAvatar(&tAvatarName[0], tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(1, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(1, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPShopState != 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(2, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mUniqueNumber != tUniqueNumber)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(7, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (1 == mUSER[tOtherAvatarIndex].mAuthInfo.PShopFlag)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(9, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	CopyMemory(&tItemInfo[0], &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0], 36);
	if (tItemInfo[0] < 1)
	{
		mTRANSFER.B_BUY_PSHOP_RECV(3, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] != tItemInfo[0]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] != tItemInfo[7]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] != tItemInfo[8]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] != tItemInfo[1]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] != tItemInfo[2]) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] != tItemInfo[3]))
	{
		mTRANSFER.B_BUY_PSHOP_RECV(4, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mUTIL.CheckOverMaximum(mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney, tItemInfo[4]))
	{
		mTRANSFER.B_BUY_PSHOP_RECV(5, 0, 0, 0, &tValue[0], &tItemSocket[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tItemInfo[4])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] > 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tValue[0] = tItemInfo[0];
	tValue[1] = tXPost2;
	tValue[2] = tYPost2;
	tValue[3] = tItemInfo[1];
	tValue[4] = tItemInfo[2];
	tValue[5] = tItemInfo[3];
	for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
	{
		tItemSocket[index01] = mUSER[tOtherAvatarIndex].mAvatarInfo.aInventorySocket[tItemInfo[5]][tItemInfo[6]][index01];
	}
	mGAMELOG.GL_609_PSHOP_ITEM(tUserIndex, 1, tItemInfo[0], tItemInfo[1], tItemInfo[2], tItemInfo[3], tItemInfo[4]);
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tItemInfo[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = tValue[5];
	// Transfer Socket
	for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
	{
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][index01] = tItemSocket[index01];
	}
	// Transfer Done
	mTRANSFER.B_BUY_PSHOP_RECV(0, tItemInfo[4], tPage2, tIndex2, &tValue[0], &tItemSocket[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mGAMELOG.GL_609_PSHOP_ITEM(tOtherAvatarIndex, 2, tItemInfo[0], tItemInfo[1], tItemInfo[2], tItemInfo[3], tItemInfo[4]);
	mUSER[tOtherAvatarIndex].mAvatarInfo.aMoney += tItemInfo[4];
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][0] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][1] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][2] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][3] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][4] = 0;
	mUSER[tOtherAvatarIndex].mAvatarInfo.aInventory[tItemInfo[5]][tItemInfo[6]][5] = 0;
	// Transfer Socket
	for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
	{
		mUSER[tOtherAvatarIndex].mAvatarInfo.aInventorySocket[tItemInfo[5]][tItemInfo[6]][index01] = 0;
	}
	// Transfer Done
	mTRANSFER.B_BUY_PSHOP_RECV(6, tItemInfo[4], tItemInfo[5], tItemInfo[6], &tValue[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aInventorySocket[tItemInfo[5]][tItemInfo[6]][0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][0] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][1] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][2] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][3] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][4] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][5] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][6] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][7] = 0;
	mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemInfo[tPage1][tIndex1][8] = 0;
	// Transfer Socket
	for (index01 = 0; index01 < MAX_SOCKETSYSTEM_ARRAY; index01++)
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo.mItemSocket[tPage1][tIndex1][index01] = 0;
	}
	// Transfer Done
	mTRANSFER.B_DEMAND_PSHOP_RECV(0, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_DEMAND_PSHOP_RECV(3, &mAVATAR_OBJECT[tOtherAvatarIndex].mPShopInfo);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}

//W_GET_CASH_SIZE_SEND
void W_GET_CASH_SIZE_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mEXTRA_COM.U_GET_CASH_SIZE_FOR_EXTRA_SEND(&mUSER[tUserIndex].uID[0]))
	{
		mTRANSFER.B_GET_CASH_SIZE_RECV(0, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mTRANSFER.B_GET_CASH_SIZE_RECV(mEXTRA_COM.mRecv_Cash, 1);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_BUY_CASH_ITEM_SEND
void W_BUY_CASH_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tCostInfoIndex;
	int tPage;
	int tIndex;
	int tValue[6];
	int tVersion = 0;
	ITEM_INFO* tITEM_INFO;
	CopyMemory(&tCostInfoIndex, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tValue[0], &tPacket[13], 24);
	CopyMemory(&tVersion, &tPacket[37], 4);

	if (tVersion != mEXTRA_COM.mCashItemInfoVersion)
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(3, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mUSER[tUserIndex].mIsValidCashItemInfo = false;
		return;
	}
	if (mEXTRA_COM.mIsValidCashItemInfo == false)
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(4, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (tPage == 1)
	{
		if (mBag2 < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (!mEXTRA_COM.U_BUY_CASH_ITEM_FOR_EXTRA_SEND(&mMyId[0], tCostInfoIndex, tValue[0], tValue[3], &mMyName[0], mMyTribe, mLevel1, tVersion))
	{
		mTRANSFER.B_BUY_CASH_ITEM_RECV(2, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mEXTRA_COM.mRecv_Result != 0)
	{
		int result = 1;
		if (mEXTRA_COM.mRecv_Result == 2)
		{
			result = 4;
		}
		else if (mEXTRA_COM.mRecv_Result == 3)
		{
			mEXTRA_COM.U_GET_CASH_ITEM_INFO_FOR_EXTRA_SEND();
			result = 3;
		}
		mTRANSFER.B_BUY_CASH_ITEM_RECV(result, 0, tPage, tIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tValue[0] = tValue[0];
	tValue[1] = tValue[1];
	tValue[2] = tValue[2];
	tValue[3] = tValue[3];
	tValue[4] = 0;
	tValue[5] = mUTIL.ReturnItemRecognitionNumber(0);

	if (mInven[tPage][tIndex][0] == tValue[0] && mInven[tPage][tIndex][1] == tValue[1] && mInven[tPage][tIndex][2] == tValue[2])
	{
		tITEM_INFO = mITEM.Search(mInven[tPage][tIndex][0]);
		if (tITEM_INFO && (tITEM_INFO->iSort == 2 || tITEM_INFO->iCheckExpire == 99) && mInven[tPage][tIndex][3] + tValue[3] <= MAX_ITEM_DUPLICATION_NUM)
		{
			tValue[3] = mInven[tPage][tIndex][3] + tValue[3];
		}
	}
	if (mInven[tPage][tIndex][0] > 0 && tITEM_INFO->iSort != 2 && tITEM_INFO->iCheckExpire != 99)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	// BloodStained Shop Points Gain by Using Mall Points
	mCapsuleMall += 2 * (mEXTRA_COM.mRecv_Cost / 10);
	mInven[tPage][tIndex][0] = tValue[0];
	mInven[tPage][tIndex][1] = tValue[1];
	mInven[tPage][tIndex][2] = tValue[2];
	mInven[tPage][tIndex][3] = tValue[3];
	mInven[tPage][tIndex][4] = tValue[4];
	mInven[tPage][tIndex][5] = tValue[5];
	mInvenSocket[tPage][tIndex][0] = 0;
	mInvenSocket[tPage][tIndex][1] = 0;
	mInvenSocket[tPage][tIndex][2] = 0;
	mInvenSocket[tPage][tIndex][3] = 0;
	mInvenSocket[tPage][tIndex][4] = 0;
	mGAMELOG.GL_604_BUY_CASH_ITEM(tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5], mEXTRA_COM.mRecv_Cash, mEXTRA_COM.mRecv_Cost);
	mTRANSFER.B_BUY_CASH_ITEM_RECV(0, mEXTRA_COM.mRecv_Cash, tPage, tIndex, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_GET_CASH_ITEM_INFO_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mIsValidCashItemInfo == true)
	{
		return;
	}

	mTRANSFER.B_GET_CASH_ITEM_INFO_RECV(0, mEXTRA_COM.mCashItemInfoVersion, mEXTRA_COM.mCashItemInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mUSER[tUserIndex].mIsValidCashItemInfo = true;
}

//W_DUEL_ASK_SEND
void W_DUEL_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if ( mSERVER_INFO.mServerNumber == 124 )
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tSort;
	int tOtherAvatarIndex;
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
	CopyMemory(&tSort, &tPacket[(1 + MAX_AVATAR_NAME_LENGTH)], 4);


	if ( mCharDuelState[0] != 0 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ( mChar.CheckCommunityWork() )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ( mCharSort == 11 || mCharSort == 12 )
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ( MapNum != 37 && MapNum != 119 && MapNum != 124 )
	{
		if( mCharTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe && mCharTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_DUEL_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tUserIndex].mDuelProcessSort = tSort;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort = tSort;
	mTRANSFER.B_DUEL_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], tSort);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_CANCEL_SEND
void W_DUEL_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
	mTRANSFER.B_DUEL_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_ANSWER_SEND
void W_DUEL_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_DUEL_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_DUEL_START_SEND
void W_DUEL_START_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAvatarDuelUniqueNumber;
	int tOtherAvatarIndex;

	tAvatarDuelUniqueNumber = mGAME.mAvatarDuelUniqueNumber;
	mGAME.mAvatarDuelUniqueNumber++;
	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessState != 3)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2] = 1;
	if (mAVATAR_OBJECT[tUserIndex].mDuelProcessSort == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tUserIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV(&mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDuelProcessRemainTime, mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_1(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState[2]);
	mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mDuelProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState != 3)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0] = 1;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1] = tAvatarDuelUniqueNumber;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2] = 2;
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessSort == 1)
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = FALSE;
	}
	else
	{
		mAVATAR_OBJECT[tOtherAvatarIndex].mCheckPossibleEatPotion = TRUE;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessState = 4;
	mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime = 180;
	mTRANSFER.B_DUEL_START_RECV(&mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDuelProcessRemainTime, mAVATAR_OBJECT[tUserIndex].mCheckPossibleEatPotion);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mTRANSFER.B_AVATAR_CHANGE_INFO_1(tOtherAvatarIndex, mAVATAR_OBJECT[tOtherAvatarIndex].mUniqueNumber, 7, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[0], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[1], mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aDuelState[2]);
	mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
}
//W_TRIBE_VOTE_SEND
void W_TRIBE_VOTE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tValue;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tValue, &tPacket[5], 4);

	int index01 = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tLevelForTribeVote;
	int tPointForTribeVote;

	switch (tSort)
	{
	case 1: //[REGISTER]
		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01)
		{
			if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], mUSER[tUserIndex].mAvatarInfo.aName) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		for (index01 = 0; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01) 
		{
			if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01], "") != 0)
			{
				continue;
			}
			tValue = index01;
			break;
		}
		if (MAX_TRIBE_VOTE_AVATAR_NUM == index01) 
		{
			tValue = 0;
			for (index01 = 1; index01 < MAX_TRIBE_VOTE_AVATAR_NUM; ++index01)
			{
				if (mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] < mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][index01]) 
				{
					continue;
				}
				tValue = index01;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe <= mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue]) 
			{
				mTRANSFER.B_TRIBE_VOTE_RECV(1, tSort, tValue);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		tLevelForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2 - 112;

		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 57;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		CopyMemory(&tBroadcastInfoData[8], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(8 + MAX_AVATAR_NAME_LENGTH)], &tLevelForTribeVote, 4);
		CopyMemory(&tBroadcastInfoData[(12 + MAX_AVATAR_NAME_LENGTH)], &mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = tLevelForTribeVote;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		return;

	case 2: //[취소]
		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], mUSER[tUserIndex].mAvatarInfo.aName) != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 58;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "");
		mGAME.mTribeInfo.mTribeVoteLevel[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVoteKillOtherTribe[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		mGAME.mTribeInfo.mTribeVotePoint[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue] = 0;
		return;

	case 3: //[투표]
		if ((tValue < 0) || (tValue > (MAX_TRIBE_VOTE_AVATAR_NUM - 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mGAME.mWorldInfo.mTribeVoteState[mUSER[tUserIndex].mAvatarInfo.aTribe] != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][tValue], "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate >= mUTIL.ReturnVoteDate())
		{
			mTRANSFER.B_TRIBE_VOTE_RECV(1, tSort, tValue);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aTribeVoteDate = mUTIL.ReturnNowDate();
		mTRANSFER.B_TRIBE_VOTE_RECV(0, tSort, tValue);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		tPointForTribeVote = mUSER[tUserIndex].mAvatarInfo.aLevel1 + mUSER[tUserIndex].mAvatarInfo.aLevel2 * 3 - 112;
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 59;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tValue, 4);
		CopyMemory(&tBroadcastInfoData[8], &tPointForTribeVote, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_GUILD_ASK_SEND
void W_GUILD_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || ((mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) && (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_GUILD_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_GUILD_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_CANCEL_SEND
void W_GUILD_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
	mTRANSFER.B_GUILD_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_ANSWER_SEND
void W_GUILD_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_GUILD_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_GUILD_WORK_SEND
void W_GUILD_WORK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	BYTE tData[MAX_GUILD_WORK_SIZE];
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tData[0], &tPacket[5], MAX_GUILD_WORK_SIZE);

	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tOtherAvatarIndex;
	char tGuildName[MAX_GUILD_NAME_LENGTH];
	char tGuildName2[MAX_GUILD_NAME_LENGTH];
	char tGuildName3[MAX_GUILD_NAME_LENGTH];
	char tGuildNotice[4][MAX_GUILD_NOTICE_LENGTH];
	int tTotalMemberNum;
	int tCost;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	char tAvatarName2[MAX_AVATAR_NAME_LENGTH];
	int tGuildRole;
	char tCallName[MAX_CALL_NAME_LENGTH];

	if (124 == mSERVER_INFO.mServerNumber)
	{
		switch (tSort) 
		{
		case 2:
		case 5:
		case 9:
			break;
		default:
			return;
		}
	}
	switch (tSort)
	{
	case  1: //[Basic]
		CopyMemory(&tGuildName[0], &tData[0], MAX_GUILD_NAME_LENGTH);
		tGuildName[(MAX_GUILD_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tGuildName, "") == 0) || (!mUTIL.CheckNameString(tGuildName)) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 30)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 10000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &tGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(mEXTRA_COM.mRecv_Result, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		strncpy(mEXTRA_COM.mRecv_GuildInfo.gName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 101;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &tGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, 10000000, 1, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 10000000;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		strncpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, tGuildName, MAX_GUILD_NAME_LENGTH);
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  2: //[Info]
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  3: //[Join]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || ((mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) && (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 1)))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mAVATAR_OBJECT[tUserIndex].mGuildProcessState != 3)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mAVATAR_OBJECT[tUserIndex].mGuildProcessState = 0;
		tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mGuildProcessAvatarName, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState != 3)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mAVATAR_OBJECT[tOtherAvatarIndex].mGuildProcessState = 0;
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum >= (mEXTRA_COM.mRecv_GuildInfo.gGrade * 10))
		{
			mTRANSFER.B_GUILD_WORK_RECV(2, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 102;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
		mUSER[tOtherAvatarIndex].mAvatarInfo.aGuildRole = 2;
		strcpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aCallName, "");
		strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildName, mUSER[tUserIndex].mAvatarInfo.aGuildName, MAX_GUILD_NAME_LENGTH);
		mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aGuildRole = 2;
		strcpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aCallName, "");
		return;
	case  4: //[Resign]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole == 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 103;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, "");
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "");
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  5: //[NOTICE]
		CopyMemory(tGuildNotice, &tData[0], (4 * MAX_GUILD_NOTICE_LENGTH));
		tGuildNotice[0][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[1][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[2][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		tGuildNotice[3][(MAX_GUILD_NOTICE_LENGTH - 1)] = '\0';
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], tGuildNotice, (4 * MAX_GUILD_NOTICE_LENGTH));
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 104;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case  6: //[DISBAND]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum != 1)
		{
			mTRANSFER.B_GUILD_WORK_RECV(2, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, 0, 3, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 105;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		strcpy(mUSER[tUserIndex].mAvatarInfo.aGuildName, "");
		mUSER[tUserIndex].mAvatarInfo.aGuildRole = 0;
		strcpy(mUSER[tUserIndex].mAvatarInfo.aCallName, "");
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aGuildName, "");
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildRole = 0;
		strcpy(mAVATAR_OBJECT[tUserIndex].mDATA.aCallName, "");
		return;
	case  7: //[EXPAND]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(2, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tTotalMemberNum = 0;
		for (index01 = 0; index01 < MAX_GUILD_AVATAR_NUM; index01++)
		{
			if (strcmp(mEXTRA_COM.mRecv_GuildInfo.gMemberName[index01], "") != 0)
			{
				tTotalMemberNum++;
			}
		}
		if (tTotalMemberNum < (mEXTRA_COM.mRecv_GuildInfo.gGrade * 10))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (mEXTRA_COM.mRecv_GuildInfo.gGrade)
		{
		case 1:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 50)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 20000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 20000000;
			break;
		case 2:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 70)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 30000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 30000000;
			break;
		case 3:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 90)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 40000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 40000000;
			break;
		case 4:
			if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUSER[tUserIndex].mAvatarInfo.aMoney < 50000000)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tCost = 50000000;
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 106;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mGAMELOG.GL_617_GUILD_MONEY(tUserIndex, tCost, 2, mEXTRA_COM.mRecv_GuildInfo.gGrade);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(19, mUSER[tUserIndex].mAvatarInfo.aMoney);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case  8: //[KICK]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tAvatarName, "") == 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 107;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case  9: //[임명]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tGuildRole, &tData[MAX_AVATAR_NAME_LENGTH], 4);
		if ((strcmp(tAvatarName, "") == 0) || (tGuildRole < 1) || (tGuildRole > 2) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tGuildRole, 4);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 108;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH)], &tGuildRole, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 10: //[칭호]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tCallName[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_CALL_NAME_LENGTH);
		tCallName[(MAX_CALL_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tAvatarName, "") == 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tCallName[0], MAX_CALL_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 109;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[(MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH)], &tCallName[0], MAX_CALL_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 11: //[문장]
		if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum < 1))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkNum--;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 12: //[문파깃발-ON]
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 1;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 13: //[문파깃발-OFF]
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aGuildMarkEffect = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.aGuildMarkEffect = 0;
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	case 17: //[Delegate Guild Master]
		CopyMemory(&tAvatarName[0], &tData[0], MAX_AVATAR_NAME_LENGTH);
		tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		CopyMemory(&tAvatarName2[0], &tData[MAX_AVATAR_NAME_LENGTH], MAX_AVATAR_NAME_LENGTH);
		tAvatarName2[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';
		if ((strcmp(tAvatarName, "") == 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tAvatarName2, MAX_AVATAR_NAME_LENGTH);
		if (!mEXTRA_COM.U_GUILD_WORK_FOR_EXTRA_SEND(tSort, &tData[0]))
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mEXTRA_COM.mRecv_Result != 0)
		{
			mTRANSFER.B_GUILD_WORK_RECV(1, tSort, &mEXTRA_COM.mRecv_GuildInfo);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mTRANSFER.B_GUILD_WORK_RECV(0, tSort, &mEXTRA_COM.mRecv_GuildInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 114;
		CopyMemory(&tBroadcastInfoData[0], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[MAX_AVATAR_NAME_LENGTH + MAX_GUILD_NAME_LENGTH], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	default: //[오류]
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_GUILD_NOTICE_SEND
void W_GUILD_NOTICE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0) || (mUSER[tUserIndex].mAvatarInfo.aGuildRole != 0))
	{
		return;
	}
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
	CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(111, &tData[0]);
}
//W_GUILD_CHAT_SEND
void W_GUILD_CHAT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
	{
		return;
	}
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aGuildName[0], MAX_GUILD_NAME_LENGTH);
	CopyMemory(&tData[MAX_GUILD_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_GUILD_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(112, &tData[0]);
	mGAMELOG.CHAT_LOG_SEND(tUserIndex, &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0], "W_GUILD_CHAT_SEND");
}
//W_GUILD_FIND_SEND
void W_GUILD_FIND_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") == 0)
	{
		return;
	}
	mPLAYUSER_COM.U_FIND_AVATAR_FOR_ZONE_SEND(&tAvatarName[0]);
	mTRANSFER.B_GUILD_FIND_RECV(mPLAYUSER_COM.mRecv_ZoneNumber);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//RANK_SEND
void W_CHAR_RANK_BUFF_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tValue01;
	CopyMemory(&tValue01, &tPacket[1], 4);
	switch (tValue01)
	{
	case 1:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 100)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 2:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 300)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 3:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 600)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 4:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 1000)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 5:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 1500)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 6:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 2100)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 7:
		if (mUSER[tUserIndex].mAvatarInfo.aRankPoints >= 3000)
		{
			mUSER[tUserIndex].mAvatarInfo.aRankAbility = tValue01;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(68, mUSER[tUserIndex].mAvatarInfo.aRankAbility);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
			return;
		}
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

}
//W_AUTO_CONFIG_SEND
void W_AUTO_CONFIG_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ACTION_INFO pAction;
	int index01;

	if (mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day < 1 /*|| mUSER[tUserIndex].mAvatarInfo.aAutoHunt5Hour < 1 */)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.aAutoHuntState, &tPacket[1], 4);
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.aAutoHuntUNK, &tPacket[5], 68);
	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.aStandStillOrMovingHunt, &tPacket[5 + 68], 44);

	if ((mUSER[tUserIndex].mAvatarInfo.aAutoHuntState == 0) && (mAVATAR_OBJECT[tUserIndex].mDATA.aAutoHuntState == 0))
	{
		return;
	}

	if ((mUSER[tUserIndex].mAvatarInfo.aAutoHuntState == 1) && (mUSER[tUserIndex].mAvatarInfo.aAutoHunt7Day != 0))
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAutoHuntState = 1;
		mTRANSFER.B_AUTOHUNT_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAVATAR_OBJECT[tUserIndex].AutoHuntBuff();
	}
	else
	{
		mAVATAR_OBJECT[tUserIndex].mDATA.aAutoHuntState = 0;
		mTRANSFER.B_AUTOHUNT_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}

// W_AUTOBUFF_REGISTER_SEND
void W_AUTOBUFF_REGISTER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	CopyMemory(&mUSER[tUserIndex].mAvatarInfo.aAutoBuffScrollSkillSlots, &tPacket[1], sizeof(AUTOBUFF_DATA));
}

//W_AUTOBUFF_SEND
void W_AUTOBUFF_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aAutoBuffScroll < mUTIL.ReturnNowDate())
	{
		return;
	}

	if (mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue < (mAVATAR_OBJECT[tUserIndex].GetMaxMana() * 0.9f))
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue -= (mAVATAR_OBJECT[tUserIndex].GetMaxMana() * 0.9f);

	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort = 41;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame = 0.0f;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetLocation[0] = 0.0f;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetLocation[1] = 0.0f;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetLocation[2] = 0.0f;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetObjectSort = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetObjectIndex = -1;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aTargetObjectUniqueNumber = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillValue = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSkillNumber = 999;
	mTRANSFER.B_AVATAR_ACTION_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, &mAVATAR_OBJECT[tUserIndex].mDATA, 1);
	mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
}
//W_MAKE_ITEM_SEND
void W_MAKE_ITEM_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	int tCost = 0;
	int tIdx = 0;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	ITEM_INFO* tITEM_INFO;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int tValue[6];
	int tValue2[6];
	int tValue3[6];
	int tValue4[6];

	switch (tSort)
	{
	case 0:// 4x Mats 3%=Random Mats
		CheckCraft4(1019, 1019, 1019, 1019);

		// Log Initial Craft Materials
		LogCraft4(1);
	
		mInven[tPage1][tIndex1][0] = 1020 + rand() % 4;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		// Log Output
		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1:// 4x Mats 15%=PUS 6%
		CheckCraft4(1023, 1023, 1023, 1023);
		
		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1437;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:// 4xBlue Jade Stone=Upgrade Stone
		CheckCraft4(983, 983, 983, 983);

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 984;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3:// 4xPUS=Upgrade Perfect Stone 3%
		CheckCraft4(1437, 1437, 1437, 1437);

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 633;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 4:// Ultimate Cape=War Lord Cape
		CheckCraft4_2();
		if ( mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1401)
			{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
			}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 1403;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 5:// War Lord Cape=God Warrior Cape
		CheckCraft4_2();
		if ( mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1403)
			{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
			}
		if (mCP < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)//Succes chance 40%
		{
			mInven[tPage1][tIndex1][0] = 1404;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 5000;
			mCharCP -= 5000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 6:// God Warrior Cape=Zeus Cape
		CheckCraft4_2();
		if ( mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1404)
			{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
			}
		if (mCP < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.3f)//Succes chance 30%
		{
			mInven[tPage1][tIndex1][0] = 1406;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 10000;
			mCharCP -= 10000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(6, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(13, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 7:// Deco V0=Deco V1 Mask
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 101)
		{
			if (mInven[tPage4][tIndex4][0] != 102)
			{
				if (mInven[tPage4][tIndex4][0] != 103)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 240;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 8:// Deco V0=Deco V1 Daiko
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 107)
		{
			if (mInven[tPage4][tIndex4][0] != 108)
			{
				if (mInven[tPage4][tIndex4][0] != 109)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 243;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 9:// Deco V0=Deco V1 Gaunlet
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 110)
		{
			if (mInven[tPage4][tIndex4][0] != 111)
			{
				if (mInven[tPage4][tIndex4][0] != 112)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 246;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 10:// Deco V1 Legendary Glasses=Deco V2 Legendary Glasses
		CheckCraft4_2();
		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 240)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 241;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 11:// Deco V1 Legendary Fauld=Deco V2 Legendary Fauld
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 243)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 244;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 12:// Deco V1 Legendary Gloves=Deco V2 Legendary Gloves
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 246)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 247;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 13:// Deco V2 Legendary Glasses=Deco V3 Legendary Glasses
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 241)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 242;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 14:// Deco V2 Legendary Fauld=Deco V3 Legendary Fauld
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 244)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 245;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 15:// Deco V2 Legendary Gloves=Deco V3 Legendary Gloves
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 247)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 248;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 40:// Wings V0
		CheckCraft4_2();
		if ( mInven[tPage1][tIndex1][0] != 695 && mInven[tPage1][tIndex1][0] != 2387)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage2][tIndex2][0] != 695 && mInven[tPage2][tIndex2][0] != 2387)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mInven[tPage3][tIndex3][0] != 695 && mInven[tPage3][tIndex3][0] != 2387)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 104)
		{
			if (mInven[tPage4][tIndex4][0] != 105)
			{
				if (mInven[tPage4][tIndex4][0] != 106)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.06f)
		{
			switch (mUTIL.GetRandomInt(2))
			{
			case 0: tIdx = 204 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe; break;
			case 1: tIdx = 213 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe; break;
			}
		}
		else if (mUTIL.GetRandomFloat() <= 0.0001f)
		{
			tIdx = 219 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
		}
		else
		{
			switch (mUTIL.GetRandomInt(3))
			{
			case 0: tIdx = 201 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe; break;
			case 1: tIdx = 207 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe; break;
			case 2: tIdx = 210 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe; break;
			}
		}

		mInven[tPage1][tIndex1][0] = tIdx;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);
		mCP -= 50;
		mCharCP -= 50;

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(1, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 41:// White Feather=Black Feather
		CheckCraft3(695, 695, 695, 695);

		LogCraft3(1);

		mInven[tPage1][tIndex1][0] = 696;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft3(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 42:// Black Feathr=Gold Feather
		CheckCraft3(696, 696, 696, 696);

		LogCraft3(1);

		mInven[tPage1][tIndex1][0] = 698;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft3(2);

		mTRANSFER.B_MAKE_ITEM_RECV(0, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 43:// Blue Dragon Wings V2==Yellow Phoenix Wings V1
		CheckCraft4_2();

		if ( mInven[tPage1][tIndex1][0] != 698 || mInven[tPage2][tIndex2][0] != 698 || mInven[tPage3][tIndex3][0] != 1473 || mInven[tPage4][tIndex4][0] != 213 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mUTIL.ReturnISValue(mInven[tPage4][tIndex4][4]) != 40 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 3000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 3000;

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)// success rate. 0.4f) = 50%
		{
			mInven[tPage1][tIndex1][0] = 219 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
	
		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 44:// Yellow Phoenix Wings V1==Blue Phoenix Wings Wings V2
		CheckCraft4_2();

		if ( mInven[tPage1][tIndex1][0] != 698 || mInven[tPage2][tIndex2][0] != 698 || mInven[tPage3][tIndex3][0] != 1473 || mInven[tPage4][tIndex4][0] != 219 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( mUTIL.ReturnISValue(mInven[tPage4][tIndex4][4]) != 40 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 5000;

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)// success rate. 0.4f) = 40%
		{
			mInven[tPage1][tIndex1][0] = 222 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
	
		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 45:// Blue Phoenix Wings V2==Golden Sparrow Wings V3
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 698 || mInven[tPage2][tIndex2][0] != 698 || mInven[tPage3][tIndex3][0] != 1473 || mInven[tPage4][tIndex4][0] != 222 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mInven[tPage4][tIndex4][4]) != 40)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 5000;

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)// success rate. 0.4f) = 40%
		{
			mInven[tPage1][tIndex1][0] = 225 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 46:// Golden Sparrow Wings V3==Suzaku Wings V4
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 698 || mInven[tPage2][tIndex2][0] != 698 || mInven[tPage3][tIndex3][0] != 1473 || mInven[tPage4][tIndex4][0] != 225 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mInven[tPage4][tIndex4][4]) != 40)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 5000;

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)// success rate. 0.4f) = 40%
		{
			mInven[tPage1][tIndex1][0] = 228 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 47:// Suzaku Wings V4 ==Dragon Wings V5
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 698 || mInven[tPage2][tIndex2][0] != 698 || mInven[tPage3][tIndex3][0] != 1473 || mInven[tPage4][tIndex4][0] != 228 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mInven[tPage4][tIndex4][4]) != 40)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 5000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 5000;

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)// success rate. 0.4f) = 40%
		{
			mInven[tPage1][tIndex1][0] = 231 + mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 60:// Produce Pet M1
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1002 && mInven[tPage1][tIndex1][0] != 1003 && mInven[tPage1][tIndex1][0] != 1004 && mInven[tPage1][tIndex1][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1002 && mInven[tPage2][tIndex2][0] != 1003 && mInven[tPage2][tIndex2][0] != 1004 && mInven[tPage2][tIndex2][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1002 && mInven[tPage3][tIndex3][0] != 1003 && mInven[tPage3][tIndex3][0] != 1004 && mInven[tPage3][tIndex3][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1006 + rand() % 6;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);
		mCP -= 1000;
		mCharCP -= 1000;

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 61:// Produce Pet M15
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1006 && mInven[tPage1][tIndex1][0] != 1007 && mInven[tPage1][tIndex1][0] != 1008 && mInven[tPage1][tIndex1][0] != 1009 && mInven[tPage1][tIndex1][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1006 && mInven[tPage2][tIndex2][0] != 1007 && mInven[tPage2][tIndex2][0] != 1008 && mInven[tPage2][tIndex2][0] != 1009 && mInven[tPage2][tIndex2][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1006 && mInven[tPage3][tIndex3][0] != 1007 && mInven[tPage3][tIndex3][0] != 1008 && mInven[tPage3][tIndex3][0] != 1009 && mInven[tPage3][tIndex3][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1012 + rand() % 5;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);
		mCP -= 2000;
		mCharCP -= 2000;

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 62:// Produce Pet G1
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1012 && mInven[tPage1][tIndex1][0] != 1013 && mInven[tPage1][tIndex1][0] != 1014 && mInven[tPage1][tIndex1][0] != 1015 && mInven[tPage1][tIndex1][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1012 && mInven[tPage2][tIndex2][0] != 1013 && mInven[tPage2][tIndex2][0] != 1014 && mInven[tPage2][tIndex2][0] != 1015 && mInven[tPage2][tIndex2][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1012 && mInven[tPage3][tIndex3][0] != 1013 && mInven[tPage3][tIndex3][0] != 1014 && mInven[tPage3][tIndex3][0] != 1015 && mInven[tPage3][tIndex3][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1310 + rand() % 3;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);
		mCP -= 3000;
		mCharCP -= 3000;

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 63:// Produce Amulet Box
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1310 && mInven[tPage1][tIndex1][0] != 1311 && mInven[tPage1][tIndex1][0] != 1312)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1310 && mInven[tPage2][tIndex2][0] != 1311 && mInven[tPage2][tIndex2][0] != 1312)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 2169;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_PET_COMBINE_SEND
void W_PET_COMBINE_SEND(int tUserIndex)// Craft Pet Trader Nungsi 
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int a = 0;
	int b = 0;
	int c = 0;

	switch (tSort)
	{
	case 0:// Produce Pet M1
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1002 && mInven[tPage1][tIndex1][0] != 1003 && mInven[tPage1][tIndex1][0] != 1004 && mInven[tPage1][tIndex1][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1002 && mInven[tPage2][tIndex2][0] != 1003 && mInven[tPage2][tIndex2][0] != 1004 && mInven[tPage2][tIndex2][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1002 && mInven[tPage3][tIndex3][0] != 1003 && mInven[tPage3][tIndex3][0] != 1004 && mInven[tPage3][tIndex3][0] != 1005)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1006 + rand() % 6;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1:// Produce Pet M15
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1006 && mInven[tPage1][tIndex1][0] != 1007 && mInven[tPage1][tIndex1][0] != 1008 && mInven[tPage1][tIndex1][0] != 1009 && mInven[tPage1][tIndex1][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1006 && mInven[tPage2][tIndex2][0] != 1007 && mInven[tPage2][tIndex2][0] != 1008 && mInven[tPage2][tIndex2][0] != 1009 && mInven[tPage2][tIndex2][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1006 && mInven[tPage3][tIndex3][0] != 1007 && mInven[tPage3][tIndex3][0] != 1008 && mInven[tPage3][tIndex3][0] != 1009 && mInven[tPage3][tIndex3][0] != 1010 && mInven[tPage3][tIndex3][0] != 1011)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1012 + rand() % 5;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:// Produce Pet G1
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1012 && mInven[tPage1][tIndex1][0] != 1013 && mInven[tPage1][tIndex1][0] != 1014 && mInven[tPage1][tIndex1][0] != 1015 && mInven[tPage1][tIndex1][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1012 && mInven[tPage2][tIndex2][0] != 1013 && mInven[tPage2][tIndex2][0] != 1014 && mInven[tPage2][tIndex2][0] != 1015 && mInven[tPage2][tIndex2][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 1012 && mInven[tPage3][tIndex3][0] != 1013 && mInven[tPage3][tIndex3][0] != 1014 && mInven[tPage3][tIndex3][0] != 1015 && mInven[tPage3][tIndex3][0] != 1016)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1235)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1310 + rand() % 3;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3:// Produce Amulet Box
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 1310 && mInven[tPage1][tIndex1][0] != 1311 && mInven[tPage1][tIndex1][0] != 1312)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 1310 && mInven[tPage2][tIndex2][0] != 1311 && mInven[tPage2][tIndex2][0] != 1312)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 2169;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
// W_CRAFT_COSTUME_SEND
void W_CRAFT_COSTUME_SEND(int tUserIndex)// Craft 3 Tailor
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int a = 0;
	int b = 0;
	int c = 0;

	switch (tSort)
	{
	case 0:
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 984)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 984)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 984)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1401)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 1404;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
// W_MAKE_SKILL_SEND
void W_MAKE_SKILL_SEND(int tUserIndex)// Craft Skill Elder
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int a = 0;
	int b = 0;
	int c = 0;

	switch (tSort)
	{
	case 0:// Produce Skill 8th Box
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		mInven[tPage1][tIndex1][0] = 717;
		mInven[tPage1][tIndex1][3] = 0;
		mInven[tPage1][tIndex1][4] = 0;
		mInven[tPage1][tIndex1][5] = 0;
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);
		ClearInv(tPage4, tIndex4);

		LogCraft4(2);
		mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
//W_GEAR_BREAK_SEND
void W_GEAR_BREAK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tMoney = 0;
	ITEM_INFO* tITEM_INFO1;
	int EquipPercent;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);

	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (!tITEM_INFO1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iType != 3 && tITEM_INFO1->iType != 4)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iSort < 7)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckPossibleDestroy == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] == 41644)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	EquipPercent = mUTIL.ReturnISValue(mUTIL.ReturnISValue(mInven[tPage1][tIndex1][4]));
	if (EquipPercent == 0 || EquipPercent > 40)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if ( EquipPercent >= 1 && EquipPercent < 10)
	{
		tMoney = 1000000;
		mInven[tPage1][tIndex1][0] = 1021;
	}
	else if ( EquipPercent >= 10 && EquipPercent < 19 )
	{
		tMoney = 2000000;
		mInven[tPage1][tIndex1][0] = 1021;
	}
	else if ( EquipPercent >= 20 && EquipPercent < 29 )
	{
		tMoney = 3000000;
		mInven[tPage1][tIndex1][0] = 1022;
	}
	else if ( EquipPercent >= 30 && EquipPercent < 39 )
	{
		tMoney = 5000000;
		mInven[tPage1][tIndex1][0] = 1023;
	}
	else if ( EquipPercent == 40 )
	{
		tMoney = 10000000;
		mInven[tPage1][tIndex1][0] = 1437;
	}
	mGAMELOG.GL_819_GEAR_BREAK(tUserIndex, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5]);
	mInven[tPage1][tIndex1][3] = 0;
	mInven[tPage1][tIndex1][4] = 0;
	mInven[tPage1][tIndex1][5] = 0;
	ClearSocket(tPage1, tIndex1);
	if ( !mUTIL.CheckOverMaximum(mSilver, tMoney) )
	{
		mSilver += tMoney;
	}
	mTRANSFER.B_GEAR_BREAK_RECV(0, tMoney, &mInven[tPage1][tIndex1][0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_PARTY_ASK_SEND
void W_PARTY_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	if (124 == mSERVER_INFO.mServerNumber)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;
	int index01;

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") != 0)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName) != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName, "") != 0)
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mGAME.ReturnAllianceTribe(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aLevel2 <= 0)
	{
		if (abs(mUSER[tUserIndex].mAvatarInfo.aLevel1 - mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1) > 9)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_PARTY_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_PARTY_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PARTY_CANCEL_SEND
void W_PARTY_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	mTRANSFER.B_PARTY_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PARTY_ANSWER_SEND
void W_PARTY_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	int index01;
	int index02;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	CopyMemory(&tAnswer, &tPacket[1], 4);

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_PARTY_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PARTY_MAKE_SEND
void W_PARTY_MAKE_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") != 0)
	{
		return;
	}
	strncpy(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	strncpy(mAVATAR_OBJECT[tUserIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_PARTY_MAKE_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_PARTY_JOIN_SEND
void W_PARTY_JOIN_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mPartyProcessState != 3)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") == 0)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mPartyProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mPartyProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState != 3)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH);
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aPartyName, mUSER[tUserIndex].mAvatarInfo.aPartyName, MAX_PARTY_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mPartyProcessState = 0;
	tSort = 104;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_PARTY_CHAT_SEND
void W_PARTY_CHAT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	char tContent[MAX_CHAT_CONTENT_LENGTH];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") == 0)
	{
		return;
	}
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&tData[(MAX_PARTY_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(105, &tData[0]);
	mGAMELOG.CHAT_LOG_SEND(tUserIndex, &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0], "W_PARTY_CHAT_SEND");
}
//W_PARTY_LEAVE_SEND
void W_PARTY_LEAVE_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") == 0)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
	{
		return;
	}
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(106, &tData[0]);
}
//W_PARTY_EXILE_SEND
void W_PARTY_EXILE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") == 0)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}
	tSort = 107;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_PARTY_BREAK_SEND
void W_PARTY_BREAK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];

	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, "") == 0)
	{
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aPartyName, mUSER[tUserIndex].mAvatarInfo.aName) != 0)
	{
		return;
	}
	tSort = 109;
	CopyMemory(&tData[0], &mUSER[tUserIndex].mAvatarInfo.aPartyName[0], MAX_PARTY_NAME_LENGTH);
	CopyMemory(&tData[MAX_PARTY_NAME_LENGTH], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mRELAY_COM.U_DEMAND_BROADCAST_DATA(tSort, &tData[0]);
}
//W_REFINE_SEND//Refine sistem//
void W_REFINE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tRandomValue;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int iValue = 0;
	int tVisualValue;
	int tCPCost = 50;
	float tSuccessChance;
	float tBreakChance;
	int tRefineStage;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);

	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mBag2 < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mInven[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iSort != 7 && tITEM_INFO1->iSort != 8 && tITEM_INFO1->iSort != 9 && tITEM_INFO1->iSort != 10 && tITEM_INFO1->iSort != 11 && tITEM_INFO1->iSort != 12 && tITEM_INFO1->iSort != 13 && tITEM_INFO1->iSort != 14 && tITEM_INFO1->iSort != 15 && tITEM_INFO1->iSort != 16 && tITEM_INFO1->iSort != 17 && tITEM_INFO1->iSort != 18 && tITEM_INFO1->iSort != 19 && tITEM_INFO1->iSort != 20 && tITEM_INFO1->iSort != 21 && tITEM_INFO1->iSort != 29)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iType != 3 && tITEM_INFO1->iType != 4 && tITEM_INFO1->iType != 5)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckImprove != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckItemSet == 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}


	tITEM_INFO2 = mITEM.Search(mInven[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO2->iIndex != 576 && tITEM_INFO2->iIndex != 824 && tITEM_INFO2->iIndex != 699 && tITEM_INFO2->iIndex != 2390 && tITEM_INFO2->iIndex != 2395)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (tITEM_INFO2->iIndex)
	{
	case 576: iValue = 1; break;
	case 699: iValue = mUTIL.GetRandomInt(3) + 1; break;
	case 824: iValue = 1; break;
	}
	if (mCP < tCPCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 25)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tSuccessChance = 0.50f;
	tBreakChance = 0.40f;
	if (tITEM_INFO2->iIndex == 824)
	{
		tSuccessChance = 1.0f;
	}
	if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 25)
	{
		iValue = 25 - mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
	}

	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 50;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 50;
	ClearInv(tPage2, tIndex2);

	// LOG / 1 = Success / 2 = Failure / 3 = Break Use PC / 4 = Break No PC

	if (mUTIL.GetRandomFloat() <= tSuccessChance)
	{
		// Success

		int currentRefine = mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		int newRefine = currentRefine + iValue;

		// Limitează rafinarea maximă la 25 — asta blochează peste 25, nu dă fail
		if (newRefine > 25)
			newRefine = 25;

		int deltaRefine = newRefine - currentRefine; // diferența efectivă de rafinare

		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeRefineValue(
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], deltaRefine);

		// Curățare piatră folosită
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;

		mGAMELOG.GL_811_REFINE_ITEM(tUserIndex, 1, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5], tCPCost);
		mTRANSFER.B_REFINE_ITEM_RECV(0, tCPCost, deltaRefine);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Obține refine-ul real după modificare din avatarInfo (nu din mInven)
		int finalRefine = mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);

		if (finalRefine > 20)
		{
			tRefineStage = finalRefine;

			int tItemNum = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]; // VNUM-ul itemului

			CopyMemory(&tBroadcastInfoData[0], &mMyTribe, 4);                           // Tribul
			CopyMemory(&tBroadcastInfoData[4], &tRefineStage, 4);                       // Nivel refine
			CopyMemory(&tBroadcastInfoData[8], &mMyName[0], MAX_AVATAR_NAME_LENGTH);   // Nume jucător
			CopyMemory(&tBroadcastInfoData[32], &tItemNum, 4);                          // VNUM item (opțional)

			mCENTER_COM.U_DEMAND_BROADCAST_INFO(673, &tBroadcastInfoData[0]);
		}
		return;
	}
	// Failure
	if (mUTIL.GetRandomFloat() <= tBreakChance && mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 7)
	{
		// Break
		if (mUSER[tUserIndex].mAvatarInfo.aPreventRefineBreak > 0)
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeRefineValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);
			mGAMELOG.GL_811_REFINE_ITEM(tUserIndex, 3, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5], tCPCost);
			mTRANSFER.B_REFINE_ITEM_RECV(1, tCPCost, -1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			mGAMELOG.GL_811_REFINE_ITEM(tUserIndex, 4, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5], tCPCost);
			ClearInv(tPage1, tIndex1);
			ClearInv(tPage2, tIndex2);
			mTRANSFER.B_REFINE_ITEM_RECV(2, tCPCost, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
	// Did not break but failure
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeRefineValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], -1);
	mGAMELOG.GL_811_REFINE_ITEM(tUserIndex, 2, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5], tCPCost);
	mTRANSFER.B_REFINE_ITEM_RECV(1, tCPCost, -1);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// W_HIGH_ITEM_SEND
void W_HIGH_ITEM_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	ITEM_INFO* tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckHighItem != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 4) || (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 1))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#ifdef __GOD__
	if (tITEM_INFO1->iMartialLevel >= 12)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#else
	switch (tITEM_INFO1->iType)
	{
	case 3:
		if (tITEM_INFO1->iLevel >= 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4:
		if (tITEM_INFO1->iLevel >= 145)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
}
		break;
	}
#endif
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 1024) && (tITEM_INFO2->iIndex != 1025))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		switch (tITEM_INFO1->iLevel)
		{
		case 45:
			tCost = 100000;
			tItemLevel = 55;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 520;
			}
			else
			{
				tProbability = 570;
			}
			break;
		case 55:
			tCost = 200000;
			tItemLevel = 65;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 490;
			}
			else
			{
				tProbability = 540;
			}
			break;
		case 65:
			tCost = 300000;
			tItemLevel = 75;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 460;
			}
			else
			{
				tProbability = 510;
			}
			break;
		case 75:
			tCost = 400000;
			tItemLevel = 85;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 430;
			}
			else
			{
				tProbability = 480;
			}
			break;
		case 85:
			tCost = 500000;
			tItemLevel = 95;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 400;
			}
			else
			{
				tProbability = 450;
			}
			break;
		case 95:
			tCost = 600000;
			tItemLevel = 105;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 370;
			}
			else
			{
				tProbability = 420;
			}
			break;
		case 105:
			tCost = 700000;
			tItemLevel = 114;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 340;
			}
			else
			{
				tProbability = 390;
			}
			break;
		case 114:
			tCost = 800000;
			tItemLevel = 117;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 310;
			}
			else
			{
				tProbability = 360;
			}
			break;
		case 117:
			tCost = 900000;
			tItemLevel = 120;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 280;
			}
			else
			{
				tProbability = 330;
			}
			break;
		case 120:
			tCost = 1000000;
			tItemLevel = 123;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 250;
			}
			else
			{
				tProbability = 300;
			}
			break;
		case 123:
			tCost = 1100000;
			tItemLevel = 126;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 220;
			}
			else
			{
				tProbability = 270;
			}
			break;
		case 126:
			tCost = 1200000;
			tItemLevel = 129;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 190;
			}
			else
			{
				tProbability = 240;
			}
			break;
		case 129:
			tCost = 1300000;
			tItemLevel = 132;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 160;
			}
			else
			{
				tProbability = 210;
			}
			break;
		case 132:
			tCost = 1400000;
			tItemLevel = 135;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 130;
			}
			else
			{
				tProbability = 180;
			}
			break;
		case 135:
			tCost = 1500000;
			tItemLevel = 138;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 100;
			}
			else
			{
				tProbability = 150;
			}
			break;
		case 138:
			tCost = 1600000;
			tItemLevel = 141;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 70;
			}
			else
			{
				tProbability = 120;
			}
			break;
		case 141:
			tCost = 1700000;
			tItemLevel = 144;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 90;
			}
			break;
		case 144:
			tCost = 1800000;
			tItemLevel = 145;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 60;
			}
			break;
#ifdef __GOD__
		case 145:
			switch (tITEM_INFO1->iMartialLevel)
			{
			case 0:
				tCost = 1900000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 1:
				tCost = 2000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 2:
				tCost = 2100000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 3:
				tCost = 2200000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 4:
				tCost = 2300000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 5:
				tCost = 2400000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 6:
				tCost = 2500000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 7:
				tCost = 2600000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 8:
				tCost = 2700000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 9:
				tCost = 2800000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 10:
				tCost = 2900000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			case 11:
				tCost = 3000000;
				tItemLevel = 157;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 10;
				}
				else
				{
					tProbability = 20;
				}
				break;
			}
			break;
#endif
		}
		break;
	case 4:
		switch (tITEM_INFO1->iLevel)
		{
		case 100:
			tCost = 1000000;
			tItemLevel = 110;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 340;
			}
			else
			{
				tProbability = 600;
				// tProbability = 390;
			}
			break;
		case 110:
			tCost = 2000000;
			tItemLevel = 115;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 310;
			}
			else
			{
				tProbability = 600;
				// tProbability = 360;
			}
			break;
		case 115:
			tCost = 3000000;
			tItemLevel = 118;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 280;
			}
			else
			{
				tProbability = 600;
				// tProbability = 330;
			}
			break;
		case 118:
			tCost = 4000000;
			tItemLevel = 121;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 250;
			}
			else
			{
				tProbability = 600;
				// tProbability = 500;
			}
			break;
		case 121:
			tCost = 5000000;
			tItemLevel = 124;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 220;
			}
			else
			{
				tProbability = 600;
				// tProbability = 270;
			}
			break;
		case 124:
			tCost = 6000000;
			tItemLevel = 127;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 190;
			}
			else
			{
				tProbability = 600;
				// tProbability = 240;
			}
			break;
		case 127:
			tCost = 7000000;
			tItemLevel = 130;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 160;
			}
			else
			{
				tProbability = 600;
				// tProbability = 210;
			}
			break;
		case 130:
			tCost = 8000000;
			tItemLevel = 133;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 130;
			}
			else
			{
				tProbability = 600;
				// tProbability = 180;
			}
			break;
		case 133:
			tCost = 9000000;
			tItemLevel = 136;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 100;
			}
			else
			{
				tProbability = 600;
				// tProbability = 150;
			}
			break;
		case 136:
			tCost = 10000000;
			tItemLevel = 139;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 70;
			}
			else
			{
				tProbability = 600;
				// tProbability = 120;
			}
			break;
		case 139:
			tCost = 11000000;
			tItemLevel = 142;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 40;
			}
			else
			{
				tProbability = 600;
				// tProbability = 90;
			}
			break;
		case 142:
			tCost = 12000000;
			tItemLevel = 145;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 500;
				// tProbability = 10;
			}
			else
			{
				tProbability = 600;
				// tProbability = 60;
			}
			break;
#ifdef __GOD__
		case 145:
			switch (tITEM_INFO1->iMartialLevel)
			{
			case 0:
				tCost = 13000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 1:
				tCost = 14000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 2:
				tCost = 15000000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					//	tProbability = 4;
				}
				break;
			case 3:
				tCost = 16000000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 4:
				tCost = 17000000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 5:
				tCost = 18000000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 6:
				tCost = 19000000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 7:
				tCost = 20000000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 8:
				tCost = 21000000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					//	tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 9:
				tCost = 22000000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 10:
				tCost = 23000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			case 11:
				tCost = 24000000;
				tItemLevel = 157;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 400;
					// tProbability = 2;
				}
				else
				{
					tProbability = 500;
					// tProbability = 4;
				}
				break;
			}
			break;
#endif
		}
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aPremiumService > 0)
	{
		tCost = tCost - (tCost * 0.20f);
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO3 = mITEM.Return_1(tItemLevel, tITEM_INFO1);
	if (tITEM_INFO3 == NULL)
	{
		mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mTRANSFER.B_HIGH_ITEM_RECV(2, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	if (mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade > 0)
	{
		tProbability += 5;
		mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade--;
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(29, mUSER[tUserIndex].mAvatarInfo.aLuckyUpgrade);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}

	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
	tRandom = rand();
	if ((tRandom % 1000) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUTIL.SetISIUValue((mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - 4), (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - 1));
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
		mTRANSFER.B_HIGH_ITEM_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_635_HIGH_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
	mTRANSFER.B_HIGH_ITEM_RECV(1, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// W_LOW_ITEM_SEND
void W_LOW_ITEM_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	ITEM_INFO* tITEM_INFO3;
	int tCost;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckLowItem != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		if (tITEM_INFO1->iLevel <= 45)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 4:
		if (tITEM_INFO1->iLevel <= 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 1024) && (tITEM_INFO2->iIndex != 1025))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iType)
	{
	case 3:
		switch (tITEM_INFO1->iLevel)
		{
		case 55:
			tCost = 100000;
			tItemLevel = 45;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 52;
			}
			else
			{
				tProbability = 57;
			}
			break;
		case 65:
			tCost = 200000;
			tItemLevel = 55;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 49;
			}
			else
			{
				tProbability = 54;
			}
			break;
		case 75:
			tCost = 300000;
			tItemLevel = 65;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 46;
			}
			else
			{
				tProbability = 51;
			}
			break;
		case 85:
			tCost = 400000;
			tItemLevel = 75;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 43;
			}
			else
			{
				tProbability = 48;
			}
			break;
		case 95:
			tCost = 500000;
			tItemLevel = 85;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 40;
			}
			else
			{
				tProbability = 45;
			}
			break;
		case 105:
			tCost = 600000;
			tItemLevel = 95;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 37;
			}
			else
			{
				tProbability = 42;
			}
			break;
		case 114:
			tCost = 700000;
			tItemLevel = 105;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 117:
			tCost = 800000;
			tItemLevel = 114;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 120:
			tCost = 900000;
			tItemLevel = 117;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 123:
			tCost = 1000000;
			tItemLevel = 120;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 126:
			tCost = 1100000;
			tItemLevel = 123;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 129:
			tCost = 1200000;
			tItemLevel = 126;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 132:
			tCost = 1300000;
			tItemLevel = 129;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 135:
			tCost = 1400000;
			tItemLevel = 132;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 138:
			tCost = 1500000;
			tItemLevel = 135;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 141:
			tCost = 1600000;
			tItemLevel = 138;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 144:
			tCost = 1700000;
			tItemLevel = 141;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145:
#ifdef __GOD__
			switch (tITEM_INFO1->iMartialLevel)
			{
			case 0:
#endif
				tCost = 1800000;
				tItemLevel = 144;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 6;
				}
				break;
#ifdef __GOD__
			case 1:
				tCost = 1900000;
				tItemLevel = 145;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 2:
				tCost = 2000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 3:
				tCost = 2100000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 4:
				tCost = 2200000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 5:
				tCost = 2300000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 6:
				tCost = 2400000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 7:
				tCost = 2500000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 8:
				tCost = 2600000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 9:
				tCost = 2700000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 10:
				tCost = 2800000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 11:
				tCost = 2900000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 12:
				tCost = 3000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			}
			break;
#endif
		}
		break;
	case 4:
		switch (tITEM_INFO1->iLevel)
		{
		case 110:
			tCost = 1000000;
			tItemLevel = 100;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 34;
			}
			else
			{
				tProbability = 39;
			}
			break;
		case 115:
			tCost = 2000000;
			tItemLevel = 110;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 31;
			}
			else
			{
				tProbability = 36;
			}
			break;
		case 118:
			tCost = 3000000;
			tItemLevel = 115;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 28;
			}
			else
			{
				tProbability = 33;
			}
			break;
		case 121:
			tCost = 4000000;
			tItemLevel = 118;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 25;
			}
			else
			{
				tProbability = 30;
			}
			break;
		case 124:
			tCost = 5000000;
			tItemLevel = 121;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 22;
			}
			else
			{
				tProbability = 27;
			}
			break;
		case 127:
			tCost = 6000000;
			tItemLevel = 124;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 19;
			}
			else
			{
				tProbability = 24;
			}
			break;
		case 130:
			tCost = 7000000;
			tItemLevel = 127;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 16;
			}
			else
			{
				tProbability = 21;
			}
			break;
		case 133:
			tCost = 8000000;
			tItemLevel = 130;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 13;
			}
			else
			{
				tProbability = 18;
			}
			break;
		case 136:
			tCost = 9000000;
			tItemLevel = 133;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 10;
			}
			else
			{
				tProbability = 15;
			}
			break;
		case 139:
			tCost = 10000000;
			tItemLevel = 136;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 7;
			}
			else
			{
				tProbability = 12;
			}
			break;
		case 142:
			tCost = 11000000;
			tItemLevel = 139;
			if (tITEM_INFO2->iIndex == 1024)
			{
				tProbability = 4;
			}
			else
			{
				tProbability = 9;
			}
			break;
		case 145:
#ifdef __GOD__
			switch (tITEM_INFO1->iMartialLevel)
			{
			case 0:
#endif
				tCost = 12000000;
				tItemLevel = 142;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 6;
				}
				break;
#ifdef __GOD__
			case 1:
				tCost = 13000000;
				tItemLevel = 145;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 2:
				tCost = 14000000;
				tItemLevel = 146;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 3:
				tCost = 15000000;
				tItemLevel = 147;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 4:
				tCost = 16000000;
				tItemLevel = 148;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 5:
				tCost = 17000000;
				tItemLevel = 149;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 6:
				tCost = 18000000;
				tItemLevel = 150;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 7:
				tCost = 19000000;
				tItemLevel = 151;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 8:
				tCost = 20000000;
				tItemLevel = 152;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 9:
				tCost = 21000000;
				tItemLevel = 153;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 10:
				tCost = 22000000;
				tItemLevel = 154;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 11:
				tCost = 23000000;
				tItemLevel = 155;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			case 12:
				tCost = 24000000;
				tItemLevel = 156;
				if (tITEM_INFO2->iIndex == 1024)
				{
					tProbability = 1;
				}
				else
				{
					tProbability = 2;
				}
				break;
			}
			break;
#endif
		}
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO3 = mITEM.Return_2(tItemLevel, tITEM_INFO1);
	if (tITEM_INFO3 == NULL)
	{
		mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 4, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mTRANSFER.B_LOW_ITEM_RECV(2, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tProbability += (int)((float)mAVATAR_OBJECT[tUserIndex].GetLuck() / 300.0f);
	tRandom = rand();
	if ((tRandom % 100) < (unsigned int)tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tITEM_INFO3->iIndex;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_LOW_ITEM_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	mGAMELOG.GL_636_LOW_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost, tITEM_INFO2->iIndex);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mTRANSFER.B_LOW_ITEM_RECV(1, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TIME_EFFECT_SEND
void W_TIME_EFFECT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tSort;
	CopyMemory(&tSort, &tPacket[1], 4);

	if (tSort < 1 || tSort > 5)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aTimeEffectTime < (60 * tSort))
	{
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(55, -1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aTimeEffect = tSort;
	mUSER[tUserIndex].mAvatarInfo.aTimeEffect2 = tSort;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(55, mUSER[tUserIndex].mAvatarInfo.aTimeEffect);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
//W_DAILY_MISSION_SEND
void W_DAILY_MISSION_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tResult;
	int tRandom;
	int tItem;
	int tPage;
	int tIndex;
	int tXPost;
	int tYPost;

	CopyMemory(&tResult, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tXPost, &tPacket[13], 4);
	CopyMemory(&tYPost, &tPacket[17], 4);

	switch (tResult)
	{
	case 1:
		mTRANSFER.W_DAILY_MISSION_RECV(tResult, 0, mDailyWar, mDailyPVP, mDailyPVM, mDailyOnlineTime, -1, -1, -1, -1, -1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:
		if (mDailyWar < 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mDailyPVP < 10)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mDailyPVM < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mDailyOnlineTime < 60)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( tPage < 0 || tPage > 1 || tIndex < 0 || tIndex > MAX_INVENTORY_SLOT_NUM - 1 )
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ( tPage == -1 )
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		switch(mUTIL.GetRandomInt(14))
		{
		case 0: tItem = 1103; break;
		case 1: tItem = 1124; break;
		case 2: tItem = 1166; break;
		case 3: tItem = 1237; break;
		case 4: tItem = 1023; break;
		case 5: tItem = 1092; break;
		case 6: tItem = 1093; break;
		case 7: tItem = 1017; break;
		case 8: tItem = 1018; break;
		case 9: tItem = 92009; break;
		case 10: tItem = 698; break;
		case 11: tItem = 1072; break;
		case 12: tItem = 1073; break;
		case 13: tItem = 1216; break;
		}
		mDailyWar = 0;
		mDailyPVP = 0;
		mDailyPVM = 0;
		mDailyOnlineTime = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tItem;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tXPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tYPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = 0;
		mTRANSFER.W_DAILY_MISSION_RECV(tResult, 0, mDailyWar, mDailyPVP, mDailyPVM, mDailyOnlineTime, tItem, tPage, tIndex, tXPost, tYPost);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	}
}
// W_EXCHANGE_ITEM_SEND
void W_EXCHANGE_ITEM_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage;
	int tIndex;
	int tPage2;
	int tIndex2;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage, &tPacket[5], 4);
	CopyMemory(&tIndex, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	if ((tPage < 0) || (tPage > 1) || (tIndex < 0) || (tIndex > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int tTribeItemList[9];
	int tValue[6];
	int index01;
	int index02;
	int tRandomValue;

	if (tPage == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO1->iCheckExchange != 2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO1->iLevel)
	{
	case 45:
		tCost = 1000000;
		break;
	case 55:
		tCost = 1200000;
		break;
	case 65:
		tCost = 1400000;
		break;
	case 75:
		tCost = 1600000;
		break;
	case 85:
		tCost = 1800000;
		break;
	case 95:
	case 100:
		tCost = 2000000;
		break;
	case 105:
	case 110:
		tCost = 2200000;
		break;
	case 114:
		tCost = 2400000;
		break;
	case 117:
	case 115:
		tCost = 2600000;
		break;
	case 120:
	case 118:
		tCost = 2800000;
		break;
	case 123:
	case 121:
		tCost = 3000000;
		break;
	case 126:
	case 124:
		tCost = 3200000;
		break;
	case 129:
	case 127:
		tCost = 3400000;
		break;
	case 132:
	case 130:
		tCost = 3600000;
		break;
	case 135:
	case 133:
		tCost = 3800000;
		break;
	case 138:
	case 136:
		tCost = 4000000;
		break;
	case 141:
	case 139:
		tCost = 4200000;
		break;
	case 144:
	case 142:
		tCost = 4400000;
		break;
	case 145:
		switch (tITEM_INFO1->iMartialLevel)
		{
		case 0:
			tCost = 4600000;
			break;
		case 1:
			tCost = 4800000;
			break;
		case 2:
			tCost = 5000000;
			break;
		case 3:
			tCost = 5200000;
			break;
		case 4:
			tCost = 5400000;
			break;
		case 5:
			tCost = 5600000;
			break;
		case 6:
			tCost = 5800000;
			break;
		case 7:
			tCost = 6000000;
			break;
		case 8:
			tCost = 6200000;
			break;
		case 9:
			tCost = 6400000;
			break;
		case 10:
			tCost = 6600000;
			break;
		case 11:
			tCost = 6800000;
			break;
		case 12:
			tCost = 7000000;
			break;
		}
		break;
	}
	if (tITEM_INFO1->iType == 4)
	{
		tCost *= 2;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
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
	tRandom = rand();

	tITEM_INFO2 = mITEM.Return((tITEM_INFO1->iLevel + tITEM_INFO1->iMartialLevel), tITEM_INFO1->iType, tTribeItemList[(rand() % 9)], tITEM_INFO1);

	if ((tITEM_INFO2 == NULL) || (tITEM_INFO2->iIndex == tITEM_INFO1->iIndex))
	{
		mTRANSFER.B_EXCHANGE_ITEM_RECV(1, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((tITEM_INFO2->iCheckAvatarTrade == 1) || (tITEM_INFO2->iCheckItemSet == 2) || (tITEM_INFO2->iCheckItemSet == 3))
	{
		mGAMELOG.GL_637_EXCHANGE_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost);
		mTRANSFER.B_EXCHANGE_ITEM_RECV(1, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
	tValue[0] = tITEM_INFO2->iIndex;
	tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1];
	tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2];
	tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3];
	tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4];
	tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5];
	mGAMELOG.GL_637_EXCHANGE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost);
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
	mGAMELOG.GL_637_EXCHANGE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5], tCost);
	mTRANSFER.B_EXCHANGE_ITEM_RECV(0, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_WARLORD_V2_SEND
void W_WARLORD_V2_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int tV2;
	int tEnchantLoss;
	int tItemLevel;
	int tProbability;
	int tValue[6];

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iType != 3) && (tITEM_INFO1->iType != 4))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((tITEM_INFO2->iIndex != 501) && (tITEM_INFO2->iIndex != 502) && (tITEM_INFO2->iIndex != 503) && (tITEM_INFO2->iIndex != 504))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tV2 = tITEM_INFO1->iIndex + 129;

	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 501:
		tCost = 30000000;
		tProbability = 40;
		tEnchantLoss = -8;
		break;
	case 502:
		tCost = 30000000;
		tProbability = 30;
		tEnchantLoss = -6;
		break;
	case 503:
		tCost = 30000000;
		tProbability = 20;
		tEnchantLoss = -4;
		break;
	case 504:
		tCost = 30000000;
		tProbability = 10;
		tEnchantLoss = 0;
		break;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < tCost)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 30)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tRandom = rand();
	if ((tRandom % 100) < tProbability)
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = tV2;
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tEnchantLoss);
		tValue[5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		// GameLogger(1, "<WARLORD_V2_UPGRADE_SUCCESS>(%s),(%s), (NEWITEM: %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_WARLORD_V2_RECV(0, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else
	{
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		tValue[0] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0];
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3];
		tValue[4] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4];
		tValue[5] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		// GameLogger(1, "<WARLORD_V2_UPGRADE_FAIL>(%s),(%s), (ITEM: %d), [[%d]]", mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mSERVER_INFO.mServerNumber);
		mTRANSFER.B_WARLORD_V2_RECV(1, tCost, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_GENERAL_SHOUT_SEND
void W_GENERAL_SHOUT_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tContent[MAX_CHAT_CONTENT_LENGTH];

	CopyMemory(&tContent[0], &tPacket[1], MAX_CHAT_CONTENT_LENGTH);
	tContent[(MAX_CHAT_CONTENT_LENGTH - 1)] = '\0';
	if (strcmp(tContent, "") == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mSERVER_INFO.mServerNumber != 37) && (mSERVER_INFO.mServerNumber != 119) && (mSERVER_INFO.mServerNumber != 124) && (mSERVER_INFO.mServerNumber != 84))
	{
		return;
	}
	mTRANSFER.B_GENERAL_SHOUT_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0]);
	mUTIL.Broadcast(FALSE, NULL, 0, false);
	mGAMELOG.CHAT_LOG_SEND(tUserIndex, &mUSER[tUserIndex].mAvatarInfo.aName[0], &tContent[0], "W_GENERAL_SHOUT_SEND");
}
//W_SOCKET_ITEM_SEND
void W_SOCKET_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tRandomSocket[5];
	int tRandom;
	int tCost;
	int tGemEffect[10];
	char tLegendNewSocket[10];
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	std::vector<int> tDrillNum;
	int tGems[5];
	int tSocketNum;
	int index01;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);

	switch (tSort)
	{
	case 1: //[Socket]
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] > 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 100000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tDrillNum = { 1, 2, 3, 4, 5 };
		tCost = 100000000;

		tRandom = rand() % tDrillNum.size();
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 2, tDrillNum[tRandom]);
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tCost;
		mTRANSFER.B_SOCKET_ITEM_RECV(0, tDrillNum[tRandom], &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		return;

	case 2: //[Socket Remove]
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1212)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		/*if (mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 2) == 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}*/
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_SOCKET_ITEM_RECV(1, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		return;

	case 3: // NORMAL_GEM
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iType != 3 && tITEM_INFO1->iType != 4)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 531)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tGems[0] = 0;
		tGems[1] = 0;
		tGems[2] = 0;
		tGems[3] = 0;
		tGems[4] = 0;
		tSocketNum = mUTIL.GetSocketAbility(mInvenSocket[tPage1][tIndex1][0], mInvenSocket[tPage1][tIndex1][1], mInvenSocket[tPage1][tIndex1][2], &tGems[0], &tGems[1], &tGems[2], &tGems[3], &tGems[4]);
		for (index01 = 0; index01 < 5; index01++)
		{
			if (tGems[index01] == 0)
			{
				break;
			}
		}
		if (index01 == 5)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tSocketNum < index01)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (index01 + 1)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 3, 1);
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 4, (rand() % 15 + 1));
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 1, 1);
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 2, (rand() % 15 + 1));
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 3, 1);
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 4, (rand() % 15 + 1));
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 1, 1);
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 2, (rand() % 15 + 1));
			break;
		case 5:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 3, 1);
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 4, (rand() % 15 + 1));
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_SOCKET_ITEM_RECV(2, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		return;

	case 4: // LEGENDARY SOCKET
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iType != 5 && tITEM_INFO1->iType != 6 && tITEM_INFO1->iType != 7 && tITEM_INFO1->iType != 8)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2385)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tGems[0] = 0;
		tGems[1] = 0;
		tGems[2] = 0;
		tGems[3] = 0;
		tGems[4] = 0;
		tSocketNum = mUTIL.GetSocketAbility(mInvenSocket[tPage1][tIndex1][0], mInvenSocket[tPage1][tIndex1][1], mInvenSocket[tPage1][tIndex1][2], &tGems[0], &tGems[1], &tGems[2], &tGems[3], &tGems[4]);
		for (index01 = 0; index01 < 5; index01++)
		{
			if (tGems[index01] == 0)
			{
				break;
			}
		}
		if (index01 == 5)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tSocketNum < index01)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (index01 + 1)
		{
		case 1:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 3, (rand() % 28 + 2));
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 4, 100);
			break;
		case 2:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 1, (rand() % 28 + 2));
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 2, 100);
			break;
		case 3:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 3, (rand() % 28 + 2));
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 4, 100);
			break;
		case 4:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 1, (rand() % 28 + 2));
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 2, 100);
			break;
		case 5:
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 3, (rand() % 28 + 2));
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 4, 100);
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_SOCKET_ITEM_RECV(2, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 3, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		return;

	case 501: // 1st Gem Remove
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1213)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 3, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], 4, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 501, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mTRANSFER.B_SOCKET_ITEM_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 502: // 2ND GEM REMOVE
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1213)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 1, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 2, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 502, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mTRANSFER.B_SOCKET_ITEM_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 503: // 3RD GEM REMOVE
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1213)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 3, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], 4, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 503, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mTRANSFER.B_SOCKET_ITEM_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 504: // 4TH GEM REMOVE
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1213)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 1, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 2, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 504, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mTRANSFER.B_SOCKET_ITEM_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 505: // 5TH GEM REMOVE
		if (tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > MAX_INVENTORY_SLOT_NUM - 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage2 == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tITEM_INFO1->iSort != 7) && (tITEM_INFO1->iSort != 8) && (tITEM_INFO1->iSort != 9) && (tITEM_INFO1->iSort != 10) && (tITEM_INFO1->iSort != 11) && (tITEM_INFO1->iSort != 12) && (tITEM_INFO1->iSort != 13) && (tITEM_INFO1->iSort != 14) && (tITEM_INFO1->iSort != 15) && (tITEM_INFO1->iSort != 16) && (tITEM_INFO1->iSort != 17) && (tITEM_INFO1->iSort != 18) && (tITEM_INFO1->iSort != 19) && (tITEM_INFO1->iSort != 20) && (tITEM_INFO1->iSort != 21))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 1213)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] <= 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 3, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2], 4, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_812_SOCKET_ITEM(tUserIndex, 504, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1], mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2]);
		mTRANSFER.B_SOCKET_ITEM_RECV(3, 0, &mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}

//W_TEACHER_ASK_SEND
void W_TEACHER_ASK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	CopyMemory(&tAvatarName[0], &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[(MAX_AVATAR_NAME_LENGTH - 1)] = '\0';

	int tOtherAvatarIndex;

	if ((mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0) || (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].CheckCommunityWork())
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(3);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(tAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(4);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tUserIndex].mDATA.aTribe != mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aTribe) || (mUSER[tOtherAvatarIndex].mAvatarInfo.aLevel1 > 112))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ((mUSER[tOtherAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[tOtherAvatarIndex].CheckCommunityWork()))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if ((mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 11) || (mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aAction.aSort == 12))
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(5);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(6);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, "") != 0)
	{
		mTRANSFER.B_TEACHER_ANSWER_RECV(7);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 1;
	strncpy(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tOtherAvatarIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 2;
	strncpy(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_ASK_RECV(&mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_ANSWER_SEND
void W_TEACHER_ANSWER_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tAnswer;
	int tOtherAvatarIndex;
	CopyMemory(&tAnswer, &tPacket[1], 4);

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 2)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		break;
	default:
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 1)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	switch (tAnswer)
	{
	case 0:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 3;
		break;
	case 1:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	case 2:
		mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
		break;
	default:
		return;
	}
	mTRANSFER.B_TEACHER_ANSWER_RECV(tAnswer);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_CANCEL_SEND
void W_TEACHER_CANCEL_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 1)
	{
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 2)
	{
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		return;
	}
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	mTRANSFER.B_TEACHER_CANCEL_RECV();
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_START_SEND
void W_TEACHER_START_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if (mAVATAR_OBJECT[tUserIndex].mTeacherProcessState != 3)
	{
		return;
	}
	tOtherAvatarIndex = mUTIL.SearchAvatar(mAVATAR_OBJECT[tUserIndex].mTeacherProcessAvatarName, tUserIndex);
	if (tOtherAvatarIndex == -1)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState != 3)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (strcmp(mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessAvatarName, mAVATAR_OBJECT[tUserIndex].mDATA.aName) != 0)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	if (mUSER[tOtherAvatarIndex].mMoveZoneResult == 1)
	{
		mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mTeacherProcessState = 0;
	strncpy(mUSER[tUserIndex].mAvatarInfo.aStudent, mUSER[tOtherAvatarIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_START_RECV(1, &mUSER[tOtherAvatarIndex].mAvatarInfo.aName[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tOtherAvatarIndex].mTeacherProcessState = 0;
	strncpy(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName, MAX_AVATAR_NAME_LENGTH);
	mTRANSFER.B_TEACHER_START_RECV(2, &mUSER[tUserIndex].mAvatarInfo.aName[0]);
	mUSER[tOtherAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_END_SEND
void W_TEACHER_END_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") == 0) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	strcpy(mUSER[tUserIndex].mAvatarInfo.aTeacher, "");
	strcpy(mUSER[tUserIndex].mAvatarInfo.aStudent, "");
	mTRANSFER.B_TEACHER_END_RECV();
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_TEACHER_STATE_SEND
void W_TEACHER_STATE_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		return;
	}

	int tOtherAvatarIndex;

	if ((strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") == 0) && (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") == 0))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar(mUSER[tUserIndex].mAvatarInfo.aTeacher, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aStudent, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
		{
			mTRANSFER.B_TEACHER_STATE_RECV(0);
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV(1);
		}
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
	{
		tOtherAvatarIndex = mUTIL.SearchAvatar(mUSER[tUserIndex].mAvatarInfo.aStudent, tUserIndex);
		if (tOtherAvatarIndex == -1)
		{
			return;
		}
		if (strcmp(mUSER[tOtherAvatarIndex].mAvatarInfo.aTeacher, mUSER[tUserIndex].mAvatarInfo.aName) == 0)
		{
			mTRANSFER.B_TEACHER_STATE_RECV(0);
		}
		else
		{
			mTRANSFER.B_TEACHER_STATE_RECV(1);
		}
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_CHANGE_TO_TRIBE4_SEND
void W_CHANGE_TO_TRIBE4_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	time_t tCountSeconds;
	struct tm* tPresentTime;

	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(1);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}

	// saturday, 12:00 ~ 24:00
	 if (((tPresentTime->tm_wday != 6) || (tPresentTime->tm_hour < 12)) && ((tPresentTime->tm_wday != 0) || (tPresentTime->tm_hour > 0) || (tPresentTime->tm_min > 0)))
	 {
	 	mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(1);
	 	mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	 	return;
	 }
	int index01;
	int iCount = 0;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	switch (mUSER[tUserIndex].mAvatarInfo.aTribe)
	{
	case 0:
		if (mSERVER_INFO.mServerNumber != 71)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 1:
		if (mSERVER_INFO.mServerNumber != 72)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 2:
		if (mSERVER_INFO.mServerNumber != 73)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}

	for (iCount = 0; iCount < MAX_TRIBE_VOTE_AVATAR_NUM; iCount++)
	{
		if (!::strcmp(mGAME.mTribeInfo.mTribeVoteName[mUSER[tUserIndex].mAvatarInfo.aTribe][iCount], mUSER[tUserIndex].mAvatarInfo.aName))
		{
			mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}

	if (mUSER[tUserIndex].mAvatarInfo.aTribe == 3)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aFactionReturnScroll < 1)
		{
			mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(1);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
		mPLAYUSER_COM.U_CHANGE_HERO_RANK_INFO_SEND(6, mUSER[tUserIndex].mAvatarInfo.aName, 0, mUSER[tUserIndex].mAvatarInfo.aTribe);
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aFactionReturnScroll--;
		mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = mUSER[tUserIndex].mAvatarInfo.aPreviousTribe;
		mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		//--------------//
		// BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 419;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aLevel1 < 113)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#if 0
	if (mGAME.ReturnTribePointWithAlliance(mUSER[tUserIndex].mAvatarInfo.aTribe) < 100)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.CheckPossibleChangeToTribe4(mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
#endif
	if (mGAME.mWorldInfo.mTribePoint[mUSER[tUserIndex].mAvatarInfo.aTribe] < 100)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.CheckPossibleChangeToTribe4_2(mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
	 	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
	 	return;
	}
	if (mGAME.ReturnTribeRole(&mUSER[tUserIndex].mAvatarInfo.aName[0], mUSER[tUserIndex].mAvatarInfo.aTribe) != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aGuildName, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aTeacher, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (strcmp(mUSER[tUserIndex].mAvatarInfo.aStudent, "") != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < MAX_FRIEND_NUM; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aFriend[index01], "") != 0)
		{
			break;
		}
	}
	if (index01 < MAX_FRIEND_NUM)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.aTribe = 3;
	mPLAYUSER_COM.U_CHANGE_HERO_RANK_INFO_SEND(6, mUSER[tUserIndex].mAvatarInfo.aName, 0, mUSER[tUserIndex].mAvatarInfo.aTribe);
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aQuestInfo[4] = 0;
	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe = 3;
	mTRANSFER.B_CHANGE_TO_TRIBE4_RECV(0);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	//--------------//
	// BROADCAST_INFO//
	//--------------//
	tBroadcastInfoSort = 51;
	CopyMemory(&tBroadcastInfoData[0], &mUSER[tUserIndex].mAvatarInfo.aPreviousTribe, 4);
	CopyMemory(&tBroadcastInfoData[4], &mUSER[tUserIndex].mAvatarInfo.aName[0], MAX_AVATAR_NAME_LENGTH);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
	//--------------//
	//--------------//
	//--------------//
}
//W_BOOZE_DRINK_SEND
void W_BOOZE_DRINK_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	int tSort;
	int tBottleIndex;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tBottleIndex, &tPacket[5], 4);
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tBottleIndex < 0 || tBottleIndex > 9)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aWineBottle[tBottleIndex] < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aWineBottle1Quantity[tBottleIndex] == 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aWineDrinkIndex = tBottleIndex;
	mUSER[tUserIndex].mAvatarInfo.aWineBottle1Quantity[tBottleIndex]--;
	mUSER[tUserIndex].mAvatarInfo.aActiveBoozeTime = 60;
	mTRANSFER.B_BOOZE_DRINK_RECV(0, tBottleIndex);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();

}
//W_COMBINE_G12_PET_SEND
void W_COMBINE_G12_PET_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	int tRandomNumber;
	int a = 0;
	int b = 0;
	int c = 0;

	switch (tSort)
	{
	case 0:// Ultimate Cape=War Lord Cape
		CheckCraft4_2();
		if (mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1401)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 1403;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1:// War Lord Cape=God Warrior Cape
		CheckCraft4_2();
		if (mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1403)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 5000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.4f)//Succes chance 40%
		{
			mInven[tPage1][tIndex1][0] = 1404;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 5000;
			mCharCP -= 5000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(5, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(12, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:// God Warrior Cape=Zeus Cape
		CheckCraft4_2();
		if (mInven[tPage1][tIndex1][0] != 984 && mInven[tPage1][tIndex1][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 984 && mInven[tPage2][tIndex2][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 984 && mInven[tPage3][tIndex3][0] != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 1404)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 10000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.3f)//Succes chance 30%
		{
			mInven[tPage1][tIndex1][0] = 1406;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 10000;
			mCharCP -= 10000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(6, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(13, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
// W_ADD_AMULET_ABILITY_SEND
void W_ADD_AMULET_ABILITY_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tNewStat;
	int SkillLists[18];
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);

	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	switch (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0])
	{
	case 2155: //[Diopside/First Stat]
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 28)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2155)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnFirstStatValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 0)
		{
			mTRANSFER.B_ADD_AMULET_ABILITY(1, 1, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand();
		tNewStat = 10 + (tRandom % 60);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeAmuletFirstStat(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tNewStat);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_AMULET_ABILITY(0, 1, mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3));
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2156: //[Cat's Eye/Skill Point]
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 28)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2156)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnSecondStatValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 0)
		{
			mTRANSFER.B_ADD_AMULET_ABILITY(1, 2, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		SkillLists[0] = 11;
		SkillLists[1] = 12;
		SkillLists[2] = 13;
		SkillLists[3] = 21;
		SkillLists[4] = 22;
		SkillLists[5] = 23;
		SkillLists[6] = 31;
		SkillLists[7] = 32;
		SkillLists[8] = 33;
		SkillLists[9] = 41;
		SkillLists[10] = 42;
		SkillLists[11] = 43;
		SkillLists[12] = 51;
		SkillLists[13] = 52;
		SkillLists[14] = 53;
		SkillLists[15] = 61;
		SkillLists[16] = 62;
		SkillLists[17] = 63;
		tRandom = rand();
		tNewStat = SkillLists[tRandom % 18];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeAmuletSecondStat(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tNewStat);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_AMULET_ABILITY(0, 2, mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3));
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2190: //[Shiny Stone/Additional Stat]
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 28)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2190)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnFirstStatValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
		{
			mTRANSFER.B_ADD_AMULET_ABILITY(1, 3, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		if (mUTIL.ReturnThirdStatValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 0)
		{
			mTRANSFER.B_ADD_AMULET_ABILITY(1, 1, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand();
		tNewStat = 10 + (tRandom % 50);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeAmuletThirdStat(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tNewStat);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_AMULET_ABILITY(0, 4, mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3));
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2157: //[Oblivion/Remove All Stats and Points]
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 28)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2157)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2, 0);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_AMULET_ABILITY(0, 3, mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3));
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2150: //[Fahrenheit Jade/Add Ability to Cape]
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (tITEM_INFO1 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 29)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
		if (tITEM_INFO2 == NULL)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iIndex != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnCapeStatValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 0)
		{
			mTRANSFER.B_ADD_AMULET_ABILITY(1, 1, 0, 0, 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		tRandom = rand();
		tNewStat = 10 + (tRandom % 80);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeCapeStat(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], tNewStat);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ADD_AMULET_ABILITY(0, 2, mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2), mUTIL.ReturnMemoryValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3));
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}
// W_HERO_RANKING_SEND
void W_HERO_RANKING_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mPLAYUSER_COM.U_DEMAND_HERO_RANK_INFO_SEND(1);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_GET_CURRENT_HERO_RANKING_RECV(0, &mPLAYUSER_COM.mRecv_HeroRank);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

	mPLAYUSER_COM.U_DEMAND_HERO_RANK_INFO_SEND(2);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mTRANSFER.B_GET_OLD_HERO_RANKING_RECV(0, &mPLAYUSER_COM.mRecv_HeroRank);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_CLAIM_HERO_RANK_SEND
void W_CLAIM_HERO_RANK_REWARD_SEND(int tUserIndex)
{
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int index01;
	int tValue[8];
	int tRewardValue = 0;

	mPLAYUSER_COM.U_DEMAND_HERO_RANK_INFO_SEND(2);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	for (index01 = 0; index01 < 10; index01++)
	{
		if (strcmp(mUSER[tUserIndex].mAvatarInfo.aName, mPLAYUSER_COM.mRecv_HeroRank.mAvatarName[mUSER[tUserIndex].mAvatarInfo.aTribe][index01]) == 0)
		{
			break;
		}
	}
	if (index01 == 10)
	{
		mTRANSFER.B_CLAIM_HERO_RANK_REWARD_RECV(1, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (mPLAYUSER_COM.mRecv_HeroRankClaimState[mUSER[tUserIndex].mAvatarInfo.aTribe][index01] != 0)
	{
		mTRANSFER.B_CLAIM_HERO_RANK_REWARD_RECV(3, 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mPLAYUSER_COM.U_CHANGE_HERO_RANK_INFO_SEND(5, mUSER[tUserIndex].mAvatarInfo.aName, 0, mUSER[tUserIndex].mAvatarInfo.aTribe);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tRewardValue = (1000 - (index01 * 100));
	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe += tRewardValue;
	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe += tRewardValue;
	mTRANSFER.B_CLAIM_HERO_RANK_REWARD_RECV(0, tRewardValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
void W_ULTIMATE_ENCHANT_SEND(int tUserIndex)
{
	unsigned int tRandom = 0;
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int tVisualValue;
	int tCPCost;
	int tProbability1;
	int tProbability2;
	int tProtectIS = 0;
	int CapeIUValue, CapeAttribValue, CapeAttribImproveValue, CapeImproveMethod = 0;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (tITEM_INFO2->iIndex)
	{
	case 2332: iValue = 1; break;
	case 2383: iValue = 1; break;
	case 1831:
	case 1832:
		iValue = rand() % 3 + 1;
		break;
	case 18043: iValue = 1; break;
	case 18045: iValue = 1; break;
	case 17583: iValue = 1; break;
	case 17587: iValue = 1; break;
	case 1948: iValue = 20; break;
	case 1949: iValue = 30; break;
	case 1950: iValue = 40; break;
	case 1951: iValue = 50; break;
	case 1952: iValue = 20; break;
	case 1953: iValue = 30; break;
	case 1954: iValue = 40; break;
	case 1955: iValue = 50; break;
	}
	if (mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 1 || mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 11)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2332:
		case 2383:
		case 1831:
		case 1832:
		case 18043:
		case 18045:
		case 17583:
		case 17587:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 15)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue >= 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
			break;
		case 2150:
		case 1878:
			if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		case 2477:
			if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand();
		if ((tRandom % 100) < 40)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mTRANSFER.B_ULTIMATE_ENCHANT_RECV(0, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			if ((tRandom % 100) < 50) // Seal Equipment
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
				{
					mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
					mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
					mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
				else
				{
					mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
					//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), -1);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), 100);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
					mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
					mTRANSFER.B_ULTIMATE_ENCHANT_RECV(5, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
	}
	if (mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 8 || mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 9)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2332:
		case 2383:
		case 1831:
		case 1832:
		case 18043:
		case 18045:
		case 17583:
		case 17587:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 15)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue >= 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
			tRandom = rand();
			if ((tRandom % 100) < 40)
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(0, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			return;


		case 1948:
		case 1949:
		case 1950:
		case 1951:
		case 1952:
		case 1953:
		case 1954:
		case 1955:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 15)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			CapeIUValue = mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			CapeAttribValue = 10 * (CapeIUValue / 10);
			CapeAttribImproveValue = CapeAttribValue % 10;
			CapeImproveMethod = 1;
			if (!CapeIUValue)
			{

			}
			switch (tITEM_INFO2->iIndex)
			{
			case 1952:
			case 1948:
				if (CapeAttribValue == 20)
				{
					if (CapeAttribImproveValue >= 9)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					CapeImproveMethod = 0;
				}
				break;
			case 1953:
			case 1949:
				if (CapeAttribValue == 30)
				{
					if (CapeAttribImproveValue >= 9)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					CapeImproveMethod = 0;
				}
				break;
			case 1954:
			case 1950:
				if (CapeAttribValue == 40)
				{
					if (CapeAttribImproveValue >= 9)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					CapeImproveMethod = 0;
				}
				break;
			case 1955:
			case 1951:
				if (CapeAttribValue == 50)
				{
					if (CapeAttribImproveValue >= 9)
					{
						mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
						return;
					}
					CapeImproveMethod = 0;
				}
				break;
			}
			if (CapeImproveMethod == 1) // Initialize
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(21, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mGAMELOG.GL_814_IMPROVE_LEGEND_DECO(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
				return;
			}
			else // Improve
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(31, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mGAMELOG.GL_814_IMPROVE_LEGEND_DECO(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
				return;
			}
			return;

		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;

		}
	}
	if (tITEM_INFO1->iSort == 6 && tITEM_INFO1->iType == 5)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2373:
		case 2400:
			if (mUTIL.Return4thValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1, rand() % 100 + 1);
				goto enchantdeco;
			}
			if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 2, rand() % 100 + 1);
				goto enchantdeco;
			}
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3, rand() % 100 + 1);
				goto enchantdeco;
			}
			if (mUTIL.Return4thValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, rand() % 50 + 1);
				goto enchantdeco;
			}
		enchantdeco:
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ULTIMATE_ENCHANT_RECV(11, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mGAMELOG.GL_814_IMPROVE_LEGEND_DECO(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
			return;

		case 2374:
		case 2375:
		case 18037:
			if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO2->iIndex == 2375)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(13, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mGAMELOG.GL_814_IMPROVE_LEGEND_DECO(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
				return;
			}
			if (mUTIL.Return4thValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, 0);
				goto eraseenchantdeco;
			}
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, 0);
				goto eraseenchantdeco;
			}
			if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, 0);
				goto eraseenchantdeco;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, 0);
				goto eraseenchantdeco;
			}
		eraseenchantdeco:
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mTRANSFER.B_ULTIMATE_ENCHANT_RECV(12, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mGAMELOG.GL_814_IMPROVE_LEGEND_DECO(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
			return;
		}
	}
	if (mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 4 || mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 12)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2332:
		case 2383:
		case 1831:
		case 1832:
		case 18043:
		case 18045:
		case 17583:
		case 17587:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 15)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) + iValue >= 15)
			{
				iValue = 15 - mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if ((tRandom % 100) < 40)
		{
			mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], iValue);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 0, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
			mTRANSFER.B_ULTIMATE_ENCHANT_RECV(0, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			if ((tRandom % 100) < 50) // Seal Equipment
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
				{
					mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
					mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
					mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
				else
				{
					mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
					//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), -1);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]), 100);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
					mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 2, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
					mTRANSFER.B_ULTIMATE_ENCHANT_RECV(5, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
				mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
	}
	if (mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 5 || mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 6 || mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) == 10)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aMoney < 1000000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2150:
		case 1878:
			if (mUTIL.Return4thValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue();
			}
			if (mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue();
			}
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue();
			}
			if (mUTIL.Return4thValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				//mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue();
			}
			break;

		case 2477:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			break;

		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 1000000;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mGAMELOG.GL_608_IMPROVE_ITEM(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5], tCost);
		mTRANSFER.B_ULTIMATE_ENCHANT_RECV(1, 1000000, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tITEM_INFO1->iSort == 34) // Horn Vein
	{
		if (tITEM_INFO2->iIndex != 19509 && tITEM_INFO2->iIndex != 18072 && tITEM_INFO2->iIndex != 19510)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (!mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]))
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 19509:
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeRefineValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], rand() % 5 + 1);
			break;
		case 18072:
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeRefineValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 5);
			break;
		case 19510:
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) <= 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 100;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ULTIMATE_ENCHANT_RECV(61, 100, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	if (tITEM_INFO1->iSort == 36) // Legendary Costume
	{
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) - mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		switch (tITEM_INFO2->iIndex)
		{
		case 2332:
		case 2383:
		case 17583:
		case 17587:
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 50)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			break;
		default:
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 100;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ULTIMATE_ENCHANT_RECV(61, 100, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
//W_COSTUME_HIDE_SEND
void W_COSTUME_HIDE_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tValue;
	CopyMemory(&tValue, &tPacket[1], 4);

	mAVATAR_OBJECT[tUserIndex].mDATA.aCostumeHide = tValue;
	mTRANSFER.B_COSTUME_HIDE_RECV(tValue);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
//W_ENGRAVE_WEAPONS_SEND
void W_ENGRAVE_ITEM_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);
	if ((tPage1 < 0) || (tPage1 > 1) || (tIndex1 < 0) || (tIndex1 > (MAX_INVENTORY_SLOT_NUM - 1)) || (tPage2 < 0) || (tPage2 > 1) || (tIndex2 < 0) || (tIndex2 > (MAX_INVENTORY_SLOT_NUM - 1)))
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	int tCost;
	int iValue;
	int tRandom;
	int tProbability1;
	int tProbability2;
	int LegendarySort = 0;

	if ((tPage1 == 1) || (tPage2 == 1))
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (tITEM_INFO1 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
	if (tITEM_INFO2 == NULL)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	LegendarySort = mUTIL.ReturnItemSort(tITEM_INFO1->iIndex);
	if (LegendarySort == 8)
	{
		if (tITEM_INFO2->iIndex >= 17045 && tITEM_INFO2->iIndex <= 17072
			|| tITEM_INFO2->iIndex >= 17105 && tITEM_INFO2->iIndex <= 17132)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		else if (tITEM_INFO2->iIndex >= 17073 && tITEM_INFO2->iIndex <= 17103
			|| tITEM_INFO2->iIndex >= 17133 && tITEM_INFO2->iIndex <= 17163)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		else
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	else if (LegendarySort == 1 || LegendarySort == 4 || LegendarySort == 11 || LegendarySort == 12)
	{
		if (tITEM_INFO1->iSort == 7 || tITEM_INFO1->iSort == 9 || tITEM_INFO1->iSort == 10 || tITEM_INFO1->iSort == 11 || tITEM_INFO1->iSort == 12)
		{
			if (tITEM_INFO2->iIndex >= 17216 && tITEM_INFO2->iIndex <= 17243
				|| tITEM_INFO2->iIndex >= 17276 && tITEM_INFO2->iIndex <= 17303)
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			else if (tITEM_INFO2->iIndex >= 17244 && tITEM_INFO2->iIndex <= 17274
				|| tITEM_INFO2->iIndex >= 17304 && tITEM_INFO2->iIndex <= 17334)
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			else
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		else if (tITEM_INFO1->iSort == 13 || tITEM_INFO1->iSort == 14 || tITEM_INFO1->iSort == 15 || tITEM_INFO1->iSort == 16 || tITEM_INFO1->iSort == 17 || tITEM_INFO1->iSort == 18 || tITEM_INFO1->iSort == 19 || tITEM_INFO1->iSort == 20 || tITEM_INFO1->iSort == 21)
		{
			if (tITEM_INFO2->iIndex >= 17453 && tITEM_INFO2->iIndex <= 17480
				|| tITEM_INFO2->iIndex >= 17513 && tITEM_INFO2->iIndex <= 17540)
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			else if (tITEM_INFO2->iIndex >= 17481 && tITEM_INFO2->iIndex <= 17511
				|| tITEM_INFO2->iIndex >= 17541 && tITEM_INFO2->iIndex <= 17571)
			{
				if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 16)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
			else
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
	}
	else
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mUTIL.ReturnMaterialForEngrave(tITEM_INFO2->iIndex))
	{
	case 1: iValue = tITEM_INFO2->iIndex - 17452; break;
	case 2: iValue = tITEM_INFO2->iIndex - 17512; break;
	case 3: iValue = tITEM_INFO2->iIndex - 17215; break;
	case 4: iValue = tITEM_INFO2->iIndex - 17275; break;
	case 5: iValue = tITEM_INFO2->iIndex - 17215; break;
	case 6: iValue = tITEM_INFO2->iIndex - 17044; break;
	case 7: iValue = tITEM_INFO2->iIndex - 17104; break;
	}
	tProbability1 = 30;
	tRandom = rand() % 100;
	if (tRandom < tProbability1)
	{
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 4, iValue);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
		mTRANSFER.B_ENGRAVE_WEAPON_RECV(0, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	else
	{
		tProbability2 = 50;
		tRandom = rand() % 100;
		if (tRandom < tProbability2)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy > 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy--;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
				mTRANSFER.B_ENGRAVE_WEAPON_RECV(2, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
			else
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
				mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
				mTRANSFER.B_ENGRAVE_WEAPON_RECV(3, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage2][tIndex2][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
			mTRANSFER.B_ENGRAVE_WEAPON_RECV(1, mUSER[tUserIndex].mAvatarInfo.aMoney, mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe, mUSER[tUserIndex].mAvatarInfo.aProtectForDestroy, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
}
// W_UNSEAL_LEGENDARY_SEND
void W_UNSEAL_LEGENDARY_SEND(int tUserIndex)
{
	char* tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (!mUSER[tUserIndex].mCheckValidState)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	if (mUSER[tUserIndex].mMoveZoneResult == 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tPage1;
	int tIndex1;
	int tPage2;
	int tIndex2;
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tPage1, &tPacket[5], 4);
	CopyMemory(&tIndex1, &tPacket[9], 4);
	CopyMemory(&tPage2, &tPacket[13], 4);
	CopyMemory(&tIndex2, &tPacket[17], 4);
	CopyMemory(&tPage3, &tPacket[21], 4);
	CopyMemory(&tIndex3, &tPacket[25], 4);
	CopyMemory(&tPage4, &tPacket[29], 4);
	CopyMemory(&tIndex4, &tPacket[33], 4);

	switch (tSort)
	{
	case 0:// Deco V0=Deco V1 Mask
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 101)
		{
			if (mInven[tPage4][tIndex4][0] != 102)
			{
				if (mInven[tPage4][tIndex4][0] != 103)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 240;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 1:// Deco V0=Deco V1 Daiko
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 107)
		{
			if (mInven[tPage4][tIndex4][0] != 108)
			{
				if (mInven[tPage4][tIndex4][0] != 109)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 243;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:// Deco V0=Deco V1 Gaunlet
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 110)
		{
			if (mInven[tPage4][tIndex4][0] != 111)
			{
				if (mInven[tPage4][tIndex4][0] != 112)
				{
					mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
					return;
				}
			}
		}
		if (mCP < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 246;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 1000;
			mCharCP -= 1000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(2, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(8, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3:// Deco V1 Legendary Glasses=Deco V2 Legendary Glasses
		CheckCraft4_2();
		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 240)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 241;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 4:// Deco V1 Legendary Fauld=Deco V2 Legendary Fauld
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 243)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 244;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 5:// Deco V1 Legendary Gloves=Deco V2 Legendary Gloves
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 246)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 2000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 247;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 2000;
			mCharCP -= 2000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(3, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(9, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 6:// Deco V2 Legendary Glasses=Deco V3 Legendary Glasses
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 241)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 242;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 7:// Deco V2 Legendary Fauld=Deco V3 Legendary Fauld
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 244)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 245;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 8:// Deco V2 Legendary Gloves=Deco V3 Legendary Gloves
		CheckCraft4_2();

		if (mInven[tPage1][tIndex1][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage2][tIndex2][0] != 2383)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage3][tIndex3][0] != 2150)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mInven[tPage4][tIndex4][0] != 247)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mCP < 3000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		LogCraft4(1);

		if (mUTIL.GetRandomFloat() <= 0.5f)//Succes chance 50%
		{
			mInven[tPage1][tIndex1][0] = 248;
			mInven[tPage1][tIndex1][3] = 0;
			mInven[tPage1][tIndex1][4] = 0;
			mInven[tPage1][tIndex1][5] = 0;
			ClearInv(tPage2, tIndex2);
			ClearInv(tPage3, tIndex3);
			ClearInv(tPage4, tIndex4);
			mCP -= 3000;
			mCharCP -= 3000;

			LogCraft4(2);

			mTRANSFER.B_MAKE_ITEM_RECV(4, &mInven[tPage1][tIndex1][0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

		ClearInv(tPage1, tIndex1);
		ClearInv(tPage2, tIndex2);
		ClearInv(tPage3, tIndex3);

		LogCraft4(2);

		mTRANSFER.B_MAKE_ITEM_RECV(10, &mInven[tPage1][tIndex1][0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
}