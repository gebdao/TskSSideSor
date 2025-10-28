#include "MainApp.h"

void W_WARLORDV2_TO_LEGENDARY_SEND(int tUserIndex)
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
	int tPage3;
	int tIndex3;
	int tPage4;
	int tIndex4;
	int tValue[6];
	int tRandom;
	int tWeapon = 0;
	int tProbability;
	ITEM_INFO* tITEM_INFO1;
	ITEM_INFO* tITEM_INFO2;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
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
	case 0: // Weapon -> Ultimate Weapon
		// mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // Disabled
		// return;

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
		if (!tITEM_INFO1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iType == 5)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iIndex >= 87206 && tITEM_INFO1->iIndex <= 87213 ||
			tITEM_INFO1->iIndex >= 87228 && tITEM_INFO1->iIndex <= 87235 ||
			tITEM_INFO1->iIndex >= 87250 && tITEM_INFO1->iIndex <= 87257)
		{
			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 50 || mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 12)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			//tWeapon = 87206 + (895 + (8 * (tITEM_INFO1->iEquipInfo[0] - 2)));
			tWeapon = tITEM_INFO1->iIndex + (895 - (14 * (tITEM_INFO1->iEquipInfo[0] - 2)));
		}
		else if (tITEM_INFO1->iIndex >= 86754 && tITEM_INFO1->iIndex <= 86761)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // Disabled
			return;

			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 50 || mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iIndex >= 86754 && tITEM_INFO1->iIndex <= 86759)
			{
				tWeapon = 88175 + (3 * mUSER[tUserIndex].mAvatarInfo.aPreviousTribe);
			}
			if (tITEM_INFO1->iIndex == 86760)
			{
				tWeapon = 88174 + (3 * mUSER[tUserIndex].mAvatarInfo.aPreviousTribe);
			}
			if (tITEM_INFO1->iIndex == 86761)
			{
				tWeapon = 88173 + (3 * mUSER[tUserIndex].mAvatarInfo.aPreviousTribe);
			}
		}
		else if (tITEM_INFO1->iSort == 29)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__); // Disabled
			return;

			if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 50 || mUTIL.ReturnIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 1 || mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) < 1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tWeapon = 17001 + (tITEM_INFO1->iIndex - 2208);
		}
		else
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		tRandom = rand() % 100;
		tProbability = 30;
		if (tRandom < tProbability)
		{
			tValue[0] = tWeapon;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
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
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tPage1][tIndex1][2] = 0;
			mTRANSFER.B_UPGRADE_TO_LEGENDARY_RECV(0, 1, 0, 1000, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
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
			mTRANSFER.B_UPGRADE_TO_LEGENDARY_RECV(1, 2, 0, 1000, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

	case 1:
		if ((tPage1 == 1) || (tPage2 == 1) || (tPage3 == 1) || (tPage4 == 1))
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 1000)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tPage1 >= 0 && tPage2 >= 0 && tPage3 >= 0 && tPage4 >= 0)
		{
			tProbability = 90;
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iIndex != 2394)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5]);
		}
		else if (tPage1 >= 0 && tPage2 >= 0 && tPage3 >= 0)
		{
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iIndex != 2394)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5]);
		}
		else if (tPage1 >= 0 && tPage2 >= 0)
		{
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iIndex != 2394)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
			if (!tITEM_INFO1)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			if (tITEM_INFO1->iSort != 28)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5]);
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 1, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4], mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5]);
		}
		else
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}

		tRandom = rand() % 7;
		switch (tRandom)
		{
		case 0:
			tValue[0] = 1839;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 1:
			tValue[0] = 1840;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 2:
			tValue[0] = 1841;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 3:
			tValue[0] = 1842;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 4:
			tValue[0] = 1889;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 5:
			tValue[0] = 1890;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 6:
			tValue[0] = 17204;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		}
		tRandom = rand() % 100;
		if (tRandom < tProbability)
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
			mGAMELOG.GL_820_AMULET_TO_LEGEND_PET_UPGRADE(tUserIndex, 2, tValue[0], tValue[3], tValue[4], tValue[5]);
			mUTIL.BroadcastGameEvent(1, tUserIndex, tValue[0]);
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = tValue[0];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = tValue[1];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = tValue[2];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = tValue[3];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = tValue[4];
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = tValue[5];
			if (tPage2 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			}
			if (tPage3 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			}
			if (tPage4 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			}
			mTRANSFER.B_UPGRADE_TO_LEGENDARY_RECV(0, 13, 0, 1000, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
		else
		{
			mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 1000;
			mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 1000;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
			if (tPage2 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
			}
			if (tPage3 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage3][tIndex3][5] = 0;
			}
			if (tPage4 >= 0)
			{
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][2] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][3] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][4] = 0;
				mUSER[tUserIndex].mAvatarInfo.aInventory[tPage4][tIndex4][5] = 0;
			}
			mTRANSFER.B_UPGRADE_TO_LEGENDARY_RECV(4, 13, 0, 1000, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}

	case 2:
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
		if (mUTIL.ReturnItemSort(tITEM_INFO1->iIndex) != 5)
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
		if (tITEM_INFO2->iIndex != 984 && tITEM_INFO2->iIndex != 2394)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 500)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tRandom = rand() % 7;
		switch (tRandom)
		{
		case 0:
			tValue[0] = 1839;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 1:
			tValue[0] = 1840;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 2:
			tValue[0] = 1841;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 3:
			tValue[0] = 1842;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 4:
			tValue[0] = 1889;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 5:
			tValue[0] = 1890;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		case 6:
			tValue[0] = 17204;
			tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
			tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
			tValue[3] = 0;
			tValue[4] = 0;
			tValue[5] = 0;
			break;
		}
		mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe -= 500;
		mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe -= 500;
		mUTIL.BroadcastGameEvent(2, tUserIndex, tValue[0]);
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
		mTRANSFER.B_UPGRADE_TO_LEGENDARY_RECV(0, 21, 0, 500, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 5: // Soul Costume Enchant 2
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
		if (tITEM_INFO1->iSort != 36)
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
		if (tITEM_INFO2->iSort != 36)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
		mTRANSFER.B_ULTIMATE_ENCHANT_RECV(61, 100, mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 0);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 6: // Horn Vein Upgrade
		tITEM_INFO1 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (!tITEM_INFO1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iSort != 34)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tITEM_INFO2 = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
		if (!tITEM_INFO2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO2->iSort != 34)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tITEM_INFO1->iEquipInfo[1] != tITEM_INFO2->iEquipInfo[1])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe < 100)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) >= 20)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
		{
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		if (mUTIL.ReturnISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) == 0)
		{
			if (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]) > 0)
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeISValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 1);
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.ChangeIUValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4]));
		mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = mUTIL.SetSocketValue(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4], 3, 0);
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
void W_TOWER_UPGRADE_SEND(int tUserIndex)
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

	int tTowerInfo;
	int tTowerSort;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	int tZoneNumber;
	int tTowerType;
	int tTowerLevel;
	int tPage1;
	int tIndex1;
	CopyMemory(&tZoneNumber, &tPacket[1], 4);
	CopyMemory(&tTowerType, &tPacket[5], 4);
	CopyMemory(&tTowerLevel, &tPacket[9], 4);
	CopyMemory(&tPage1, &tPacket[13], 4);
	CopyMemory(&tIndex1, &tPacket[17], 4);

	if (tZoneNumber != mSERVER_INFO.mServerNumber)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber) == -1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.mTowerInfo.mTowerInfo[mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber)] % 100 != tTowerType)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mGAME.mTowerInfo.mTowerInfo[mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber)] / 100 != tTowerLevel)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ( tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > MAX_INVENTORY_SLOT_NUM - 1 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] != 666)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if ( mUSER[tUserIndex].mAvatarInfo.aMoney < 500000000 )
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 2:
	case 3:
	case 4:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 7:
	case 8:
	case 9:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe != 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 12:
	case 13:
	case 14:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe != 2)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	case 141:
	case 142:
	case 143:
		if (mUSER[tUserIndex].mAvatarInfo.aTribe != 3)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		break;
	}
	if (mGAME.mTowerInfo.mTowerInfo[mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber)] <= 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	switch (mGAME.mTowerInfo.mTowerInfo[mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber)] / 100)
	{
	case 8:
	case 9:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	case 1:
	case 3:
	case 5:
	case 7:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= 500000000;


	tTowerSort = mUTIL.ReturnTowerSort(mSERVER_INFO.mServerNumber);
	tTowerInfo = 200 + mGAME.mTowerInfo.mTowerInfo[tTowerSort];
	CopyMemory(&tData[0], &tTowerSort, 4);
	CopyMemory(&tData[4], &tTowerInfo, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(752, &tData[0]);
	mSUMMON.SummonTowerSystem(TRUE, mUTIL.GetTowerSort(4, tTowerInfo));
	mTRANSFER.B_TOWER_UPGRADE_RECV(0, tPage1, tIndex1);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}


// W_RAGE_BURST
void W_RAGE_BURST_SEND(int tUserIndex)
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

	if (mUSER[tUserIndex].mAvatarInfo.aRageBurstPill < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aFuryCount < 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aFuryState = 1;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(81, mUSER[tUserIndex].mAvatarInfo.aFuryState);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUSER[tUserIndex].mAvatarInfo.aFuryEffectDuration = 30;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(82, mUSER[tUserIndex].mAvatarInfo.aFuryEffectDuration);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mUSER[tUserIndex].mAvatarInfo.aRageBurstPill--;
	mTRANSFER.B_AVATAR_CHANGE_INFO_2(84, mUSER[tUserIndex].mAvatarInfo.aRageBurstPill);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	mAVATAR_OBJECT[tUserIndex].SetBasicAbilityFromEquip();
}
// W_DEMAND_BLOODSTAINED_SHOP_INFO_SEND
void W_DEMAND_BLOODSTAINED_SHOP_INFO_SEND(int tUserIndex)
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
	mTRANSFER.B_DEMAND_BLOODSTAINED_SHOP_INFO_RECV(40, &mGAME.mBSInfo);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// W_BUY_BLOODSTAINED_SHOP_SEND
void W_BUY_BLOODSTAINED_SHOP_SEND(int tUserIndex)
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

	int tItemPage;
	int tItemIndex;
	int tPage;
	int tIndex;
	int tValue[6];
	ITEM_INFO* tITEM_INFO;

	CopyMemory(&tItemPage, &tPacket[1], 4);
	CopyMemory(&tItemIndex, &tPacket[5], 4);
	CopyMemory(&tPage, &tPacket[9], 4);
	CopyMemory(&tIndex, &tPacket[13], 4);
	CopyMemory(&tValue, &tPacket[17], 24);

	if (tItemPage < 0 || tItemPage > 5 || tItemIndex < 0 || tItemIndex > 9)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tPage < 0 || tPage > 1 || tIndex < 0 || tIndex > MAX_INVENTORY_SLOT_NUM - 1)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aPK < mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][1])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tValue[0] != mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][0])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tValue[3] != mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][2])
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	tValue[0] = mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][0];
	tValue[3] = mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][2];
	tValue[4] = 0;
	tValue[5] = 0;
	if (mInven[tPage][tIndex][0] == tValue[0] && mInven[tPage][tIndex][1] == tValue[1] && mInven[tPage][tIndex][2] == tValue[2])
	{
		tITEM_INFO = mITEM.Search(mInven[tPage][tIndex][0]);
		if (tITEM_INFO && (tITEM_INFO->iSort == 2 || tITEM_INFO->iCheckExpire == 99) && mInven[tPage][tIndex][3] + tValue[3] <= MAX_ITEM_DUPLICATION_NUM)
		{
			tValue[3] = mInven[tPage][tIndex][3] + tValue[3];
		}
	}
	if (mInven[tPage][tIndex][0] > 0)
	{
		tITEM_INFO = mITEM.Search(mInven[tPage][tIndex][0]);
		if (tITEM_INFO && tITEM_INFO->iSort != 2 && tITEM_INFO->iCheckExpire != 99)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][0] = tValue[0];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][1] = tValue[1];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][2] = tValue[2];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][3] = tValue[3];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][4] = tValue[4];
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tIndex][5] = tValue[5];
	mUSER[tUserIndex].mAvatarInfo.aPK -= mGAME.mBSInfo.mItemInfo[tItemPage][tItemIndex][1];
	mGAMELOG.GL_816_BUY_BLOODSTAINED_SHOP(tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5]);
	mTRANSFER.B_BUY_BLOODSTAINED_SHOP_RECV(0, mUSER[tUserIndex].mAvatarInfo.aPK, tPage, tIndex, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// W_BUY_CAPSULE_SEND
void W_BUY_CAPSULE_SEND(int tUserIndex)
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
	int Unknown;
	int tSort;
	int tBuyQuantity;
	int tPage, tIndex, tInvenSlot = 0;
	ITEM_INFO* tITEM_INFO;
	int tValue[8];
	int tCost;
	int index01 = 0;
	int tRandom;
	int tRandomItems[6];
	int tWinItem = 0;
	int tPageForSend = 0;
	int tIndexForSend = 0;
	int tIndex2ForSend = 0;
	int tInvenSlotForSend = 0;
	int tInvenSlot2ForSend = 0;
	std::vector<int>t;
	CopyMemory(&Unknown, &tPacket[1], 4);
	CopyMemory(&tSort, &tPacket[5], 4);
	CopyMemory(&tBuyQuantity, &tPacket[9], 4);

	switch (tSort)
	{
	case 1:
		tCost = 2000;
		break;
	case 2:
		tCost = 4000;
		break;
	default:
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tSort == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall < (tCost * tBuyQuantity))
		{
			mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(6, 0, 0, 0, 0, 0, 0, 0, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
	if (tSort == 2)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aCapsuleOnlineTime < (tCost * tBuyQuantity))
		{
			mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(4, 0, 0, 0, 0, 0, 0, 0, &tValue[0]);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			return;
		}
	}
	for (index01 = 0; index01 < tBuyQuantity; index01++)
	{
		// Drops same paid and online time
		if (tSort == 1)
		{
			t.clear();
			t = { 1422, 1437, 1447, 1103, 636, 637, 638, 639, 640, 641 };
			tWinItem = t[rand() % t.size()];
		}
		else if (tSort == 2)
		{
			t.clear();
			t = { 1422, 1437, 1447, 1103, 636, 637, 638, 639, 640, 641 };
			tWinItem = t[rand() % t.size()];
		}

		tITEM_INFO = mITEM.Search(tWinItem);
		if (tITEM_INFO)
		{
			tPage, tIndex, tInvenSlot = 0;
			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, tPage, tIndex) == true)
			{
				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tPage);
				if (tInvenSlot != -1)
				{
					tValue[index01] = tITEM_INFO->iIndex;
					if (index01 >= 4)
					{
						tPageForSend += tPage * pow(10, index01);
						tIndex2ForSend += tInvenSlot * pow(100, 0);
						tInvenSlot2ForSend += tIndex * pow(100, 0);
					}
					else
					{
						tPageForSend += tPage * pow(10, index01);
						tIndexForSend += tInvenSlot * pow(100, index01);
						tInvenSlotForSend += tIndex * pow(100, index01);
					}
					switch (tSort)
					{
					case 1:
						mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall -= tCost;
						break;
					case 2:
						mUSER[tUserIndex].mAvatarInfo.aCapsuleOnlineTime -= tCost;
						break;
					}
					mGAMELOG.GL_817_BUY_CAPSULE_STORE(tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5]);
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][0] = tITEM_INFO->iIndex;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][1] = tIndex % 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][2] = tIndex / 8;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][3] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][4] = 0;
					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][5] = 0;
				}
			}
			else
			{
				if (index01 == 0)
				{
					mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(8, 0, 0, 0, 0, 0, 0, 0, &tValue[0]);
					mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					return;
				}
				mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(1000 * index01, tPageForSend, tIndexForSend, tIndex2ForSend, tInvenSlotForSend, tInvenSlot2ForSend, tSort, tCost, &tValue[0]);
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		else
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(1000 * tBuyQuantity, tPageForSend, tIndexForSend, tIndex2ForSend, tInvenSlotForSend, tInvenSlot2ForSend, tSort, tCost, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
}
// void W_BUY_CAPSULE_SEND(int tUserIndex)
// {
// 	char *tPacket = &mUSER[tUserIndex].mBUFFER_FOR_RECV[8];
// 	if (!mAVATAR_OBJECT[tUserIndex].mCheckValidState)
// 	{
// 		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
// 		return;
// 	}
// 	if (mUSER[tUserIndex].mMoveZoneResult == 1)
// 	{
// 		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
// 		return;
// 	}
// 	int Unknown;
// 	int tSort;
// 	int tBuyQuantity;
// 	int tPage, tIndex, tInvenSlot = 0;
// 	ITEM_INFO *tITEM_INFO;
// 	int tValue[6];
// 	int tResultQuantity;
// 	int tCost;
// 	int index01 = 0;
// 	int tRandom;
// 	int tRandomItems[6];
// 	int tWinItem = 0;
// 	CopyMemory(&Unknown, &tPacket[1], 4);
// 	CopyMemory(&tSort, &tPacket[5], 4);
// 	CopyMemory(&tBuyQuantity, &tPacket[9], 4);

// 	tResultQuantity = 1000 * tBuyQuantity;
// 	switch (tSort)
// 	{
// 	case 1:
// 		tCost = 2000;
// 		break;
// 	case 2:
// 		tCost = 4000;
// 		break;
// 	default:
// 		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
// 		return;
// 	}
// 	if (tSort == 1)
// 	{
// 		if (mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall < (tCost * tBuyQuantity))
// 		{
// 			mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(6, 0, 0, 0, 0, 0, &tValue[0]);
// 			mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
// 			return;
// 		}
// 	}
// 	if (tSort == 2)
// 	{
// 		if (mUSER[tUserIndex].mAvatarInfo.aCapsuleOnlineTime < (tCost * tBuyQuantity))
// 		{
// 			mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(4, 0, 0, 0, 0, 0, &tValue[0]);
// 			mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
// 			return;
// 		}
// 	}
// 	for (index01 = 0; index01 < tBuyQuantity; index01++)
// 	{
// 		if (tSort == 1) // Paid Points
// 		{
// 			tRandom = rand() % 2;
// 			if (tRandom == 0)
// 			{
// 				tRandom = rand() % 4;
// 				switch (tRandom)
// 				{
// 				case 0:
// 					tWinItem = 1447;
// 					break;
// 				case 1:
// 					tWinItem = 1422;
// 					break;
// 				case 2:
// 					tWinItem = 1437;
// 					break;
// 				case 3:
// 					tWinItem = 828;
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				tRandom = rand() % 12;
// 				switch (tRandom)
// 				{
// 				case 0:
// 					tWinItem = 1017;
// 					break;
// 				case 1:
// 					tWinItem = 1018;
// 					break;
// 				case 2:
// 					tWinItem = 1092;
// 					break;
// 				case 3:
// 					tWinItem = 1093;
// 					break;
// 				case 4:
// 					tWinItem = 636;
// 					break;
// 				case 5:
// 					tWinItem = 637;
// 					break;
// 				case 6:
// 					tWinItem = 638;
// 					break;
// 				case 7:
// 					tWinItem = 639;
// 					break;
// 				case 8:
// 					tWinItem = 640;
// 					break;
// 				case 9:
// 					tWinItem = 641;
// 					break;
// 				case 10:
// 					tWinItem = 578;
// 					break;
// 				case 11:
// 					tWinItem = 579;
// 					break;
// 				}
// 			}
// 		}
// 		else if (tSort == 2) // Online Time
// 		{
// 			tRandom = rand() % 5;
// 			if (tRandom == 0)
// 			{
// 				tRandom = rand() % 4;
// 				switch (tRandom)
// 				{
// 				case 0:
// 					tWinItem = 1449;
// 					break;
// 				case 1:
// 					tWinItem = 1422;
// 					break;
// 				case 2:
// 					tWinItem = 1437;
// 					break;
// 				case 3:
// 					tWinItem = 828;
// 					break;
// 				}
// 			}
// 			else
// 			{
// 				tRandom = rand() % 12;
// 				switch (tRandom)
// 				{
// 				case 0:
// 					tWinItem = 1017;
// 					break;
// 				case 1:
// 					tWinItem = 1018;
// 					break;
// 				case 2:
// 					tWinItem = 1092;
// 					break;
// 				case 3:
// 					tWinItem = 1093;
// 					break;
// 				case 4:
// 					tWinItem = 636;
// 					break;
// 				case 5:
// 					tWinItem = 637;
// 					break;
// 				case 6:
// 					tWinItem = 638;
// 					break;
// 				case 7:
// 					tWinItem = 639;
// 					break;
// 				case 8:
// 					tWinItem = 640;
// 					break;
// 				case 9:
// 					tWinItem = 641;
// 					break;
// 				case 10:
// 					tWinItem = 578;
// 					break;
// 				case 11:
// 					tWinItem = 579;
// 					break;
// 				}
// 			}
// 		}
// 		tITEM_INFO = mITEM.Search(tWinItem);
// 		if (tITEM_INFO)
// 		{
// 			tPage, tIndex, tInvenSlot = 0;
// 			if (mUTIL.FindEmptyInvenForItem(tUserIndex, tITEM_INFO, tPage, tIndex) == true)
// 			{
// 				tInvenSlot = mUTIL.GetEmptyInvenSlotIndex(tUserIndex, tPage);
// 				if (tInvenSlot != -1)
// 				{
// 					tValue[0] = tITEM_INFO->iIndex;
// 					tValue[1] = tIndex % 8;
// 					tValue[2] = tIndex / 8;
// 					tValue[3] = 0;
// 					tValue[4] = 0;
// 					tValue[5] = 0;
// 					switch (tSort)
// 					{
// 					case 1:
// 						mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall -= tCost;
// 						break;
// 					case 2:
// 						mUSER[tUserIndex].mAvatarInfo.aCapsuleOnlineTime -= tCost;
// 						break;
// 					}
// 					mGAMELOG.GL_817_BUY_CAPSULE_STORE(tUserIndex, tValue[0], tValue[3], tValue[4], tValue[5]);
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][0] = tValue[0];
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][1] = tValue[1];
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][2] = tValue[2];
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][3] = tValue[3];
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][4] = tValue[4];
// 					mUSER[tUserIndex].mAvatarInfo.aInventory[tPage][tInvenSlot][5] = tValue[5];
// 					mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(1000, tPage, tInvenSlot, tIndex, tSort, tCost, &tValue[0]);
// 					mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
// 				}
// 			}
// 			else
// 			{
// 				mTRANSFER.B_BUY_CAPSULE_SHOP_RECV(8, 0, 0, 0, 0, 0, &tValue[0]);
// 				mUSER[tUserIndex].Send(TRUE, (char *)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
// 				return;
// 			}
// 		}
// 		else
// 		{
// 			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
// 			return;
// 		}
// 	}
// }
// W_PROXY_MENU_SEND
void W_PROXY_MENU_SEND(int tUserIndex)
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
	if (mSERVER_INFO.mServerNumber != 1 && mSERVER_INFO.mServerNumber != 6 && mSERVER_INFO.mServerNumber != 11 && mSERVER_INFO.mServerNumber != 140)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}

	int tSort;
	int tUniqueNumber;
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tSellerProxyIndex;
	int index01;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tUniqueNumber, &tPacket[5], 4);
	CopyMemory(&tAvatarName, &tPacket[9], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[MAX_AVATAR_NAME_LENGTH - 1] = '\0';

	PROXYSHOP_INFO tProxyInfo;
	ZeroMemory(&tProxyInfo, sizeof(PROXYSHOP_INFO));

	switch (tSort)
	{
	case 1:
		if (mUSER[tUserIndex].mAvatarInfo.aProxyShopTime < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		for (index01 = 0; index01 < MAX_AVATAR_OBJECT_NUM; index01++)
		{
			if ((strcmp(mPROXY_OBJECT[index01].mID, mUSER[tUserIndex].uID) == 0) && (strcmp(mPROXY_OBJECT[index01].mProxyShopAvatarName, mUSER[tUserIndex].mAvatarInfo.aName) == 0))
			{
				mTRANSFER.B_DEMAND_PROXY_INFO(1, 1, &tProxyInfo); // close
				mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				return;
			}
		}
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));
		strncpy(tProxyInfo.mAvatarName, tAvatarName, MAX_AVATAR_NAME_LENGTH);
		mTRANSFER.B_DEMAND_PROXY_INFO(1, 0, &tProxyInfo); // open
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2:
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));
		strncpy(tProxyInfo.mAvatarName, tAvatarName, MAX_AVATAR_NAME_LENGTH);
		mTRANSFER.B_DEMAND_PROXY_INFO(2, 0, &tProxyInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 3:
		tSellerProxyIndex = mPROXY_OBJECT->GetProxyIndex(tAvatarName);
		if (tSellerProxyIndex == -1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mPROXY_OBJECT[tSellerProxyIndex].mID, mPROXY_OBJECT[tSellerProxyIndex].mProxyShopAvatarName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));
		strncpy(tProxyInfo.mAvatarName, tAvatarName, MAX_AVATAR_NAME_LENGTH);
		mTRANSFER.B_DEMAND_PROXY_INFO(3, 0, &tProxyInfo);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
}
// W_BUY_PROXY_SHOP
void W_BUY_PROXY_SHOP(int tUserIndex)
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
	char tAvatarName[MAX_AVATAR_NAME_LENGTH];
	int tProxyShopPage;
	int tProxyShopIndex;
	int tItemIndex;
	int tBuyerInventoryPage;
	int tBuyerInventoryIndex;
	int tXPost;
	int tYPost;
	int tSort;
	//
	int tQuantity;
	int tImproveState;
	int tItemRecognitionNumber;
	int tPrice;
	PROXYSHOP_INFO tProxyInfo;
	int tValue[12];
	int index01;
	int index02;
	int tSellerProxyIndex;
	int tProxyMoney;
	int tProxyMoney2;
	int tSocket[MAX_SOCKETSYSTEM_ARRAY];

	CopyMemory(&tAvatarName, &tPacket[1], MAX_AVATAR_NAME_LENGTH);
	tAvatarName[MAX_AVATAR_NAME_LENGTH - 1] = '\0';
	CopyMemory(&tProxyShopPage, &tPacket[14], 4);
	CopyMemory(&tProxyShopIndex, &tPacket[18], 4);
	CopyMemory(&tItemIndex, &tPacket[22], 4);
	CopyMemory(&tBuyerInventoryPage, &tPacket[26], 4);
	CopyMemory(&tBuyerInventoryIndex, &tPacket[30], 4);
	CopyMemory(&tXPost, &tPacket[34], 4);
	CopyMemory(&tYPost, &tPacket[38], 4);
	CopyMemory(&tSort, &tPacket[42], 4);
	CopyMemory(&tQuantity, &tPacket[46], 4);
	CopyMemory(&tImproveState, &tPacket[50], 4);
	CopyMemory(&tItemRecognitionNumber, &tPacket[54], 4);
	CopyMemory(&tPrice, &tPacket[58], 4);
	CopyMemory(&tSocket[0], &tPacket[62], 20);
	ZeroMemory(&tProxyInfo, sizeof(tProxyInfo));

	switch (tSort)
	{
	case 1: // Retrieve Consigned Item
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));

		if (tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0] < 1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tProxyShopPage < 0 || tProxyShopPage > 5 || tProxyShopIndex < 0 || tProxyShopIndex > 5)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tBuyerInventoryPage < 0 || tBuyerInventoryPage > 1 || tBuyerInventoryIndex < 0 || tBuyerInventoryIndex > 63)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tBuyerInventoryPage == 1)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
			{
				mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
				return;
			}
		}

		tValue[0] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0];
		tValue[1] = tXPost;
		tValue[2] = tYPost;
		tValue[3] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1];
		tValue[4] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2];
		tValue[5] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3];
		tValue[6] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0];
		tValue[7] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1];
		tValue[8] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2];
		tValue[9] = 0;
		tValue[10] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3];
		tValue[11] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][0] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][1] = tXPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][2] = tYPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][3] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][4] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][5] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][0] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][1] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][2] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][3] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][4] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4];
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][4] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4] = 0;
		strncpy(tProxyInfo.mAvatarName, tAvatarName, MAX_AVATAR_NAME_LENGTH);
		mPLAYUSER_COM.U_REGISTER_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, 1, &tProxyInfo);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_BUY_PROXY_SHOP_ITEM(1000, &tProxyInfo, tBuyerInventoryPage, tBuyerInventoryIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;

	case 2: // Proxy Buy Item
		tSellerProxyIndex = mPROXY_OBJECT->GetProxyIndex(tAvatarName);
		if (tSellerProxyIndex == -1)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mPROXY_OBJECT[tSellerProxyIndex].mID, mPROXY_OBJECT[tSellerProxyIndex].mProxyShopAvatarName);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));

		if (mUSER[tUserIndex].mAvatarInfo.aMoney < tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][4])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tItemIndex != tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tQuantity != tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tImproveState != tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		if (tItemRecognitionNumber != tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3])
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		tValue[0] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0];
		tValue[1] = tXPost;
		tValue[2] = tYPost;
		tValue[3] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1];
		tValue[4] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2];
		tValue[5] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3];
		tValue[6] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0];
		tValue[7] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1];
		tValue[8] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2];
		tValue[9] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][4]; // Price
		tValue[10] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3];
		tValue[11] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][0] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][1] = tXPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][2] = tYPost;
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][3] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][4] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventory[tBuyerInventoryPage][tBuyerInventoryIndex][5] = tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][0] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][1] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][2] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][3] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3];
		mUSER[tUserIndex].mAvatarInfo.aInventorySocket[tBuyerInventoryPage][tBuyerInventoryIndex][4] = tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4];
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][0] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][1] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][2] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][3] = 0;
		tProxyInfo.mItemInfo[tProxyShopPage][tProxyShopIndex][4] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][0] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][1] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][2] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][3] = 0;
		tProxyInfo.mItemSocket[tProxyShopPage][tProxyShopIndex][4] = 0;
		mUSER[tUserIndex].mAvatarInfo.aMoney -= tValue[9];

		strncpy(tProxyInfo.mAvatarName, tAvatarName, MAX_AVATAR_NAME_LENGTH);
		tProxyInfo.mMoney = tValue[9];
		tProxyInfo.mMoney2 = 0;
		mPLAYUSER_COM.U_REGISTER_PROXY_SHOP_INFO_SEND(mPROXY_OBJECT[tSellerProxyIndex].mID, mPROXY_OBJECT[tSellerProxyIndex].mProxyShopAvatarName, 2, &tProxyInfo);
		if (mPLAYUSER_COM.mRecv_Result != 0)
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
		mTRANSFER.B_BUY_PROXY_SHOP_ITEM(1000, &tProxyInfo, tBuyerInventoryPage, tBuyerInventoryIndex, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		for (index01 = 0; index01 < 5; index01++)
		{
			for (index02 = 0; index02 < 5; index02++)
			{
				if (tProxyInfo.mItemInfo[index01][index02][0] > 0)
				{
					break;
				}
			}
			if (index02 < 5)
			{
				break;
			}
		}
		if (index01 == 5)
		{
			mTRANSFER.B_PROXY_SHOP(mPROXY_OBJECT[tSellerProxyIndex].mProxyUserIndex, mPROXY_OBJECT[tSellerProxyIndex].mUniqueNumber, &mPROXY_OBJECT[tSellerProxyIndex].mProxyShopLocation[0], mPROXY_OBJECT[tSellerProxyIndex].mProxyShopAvatarName, mPROXY_OBJECT[tSellerProxyIndex].mProxyShopName, 3);
			mUTIL.Broadcast(FALSE, NULL, 0);
			mPROXY_OBJECT[tSellerProxyIndex].Free();
		}
		return;
	}
}
void W_CLAIM_MONEY_PROXY_SHOP_SEND(int tUserIndex)
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

	int aMoneyForClaim;
	int aMoney2ForClaim;
	LONGLONG tCheckValue;
	LONGLONG tempvalueformoney;
	int tempmoneyfortransfer;
	PROXYSHOP_INFO tProxyInfo;

	CopyMemory(&aMoneyForClaim, &tPacket[1], 4);
	CopyMemory(&aMoney2ForClaim, &tPacket[5], 4);

	mPLAYUSER_COM.U_DEMAND_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	ZeroMemory(&tProxyInfo, sizeof(tProxyInfo));
	CopyMemory(&tProxyInfo, &mPLAYUSER_COM.mRecv_Proxy, sizeof(PROXYSHOP_INFO));
	if (aMoneyForClaim != tProxyInfo.mMoney)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (aMoney2ForClaim != tProxyInfo.mMoney2)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tProxyInfo.mMoney = 0;
	tProxyInfo.mMoney2 = 0;
	mPLAYUSER_COM.U_REGISTER_PROXY_SHOP_INFO_SEND(mUSER[tUserIndex].uID, mUSER[tUserIndex].mAvatarInfo.aName, 1, &tProxyInfo);
	if (mPLAYUSER_COM.mRecv_Result != 0)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tCheckValue = (LONGLONG)mUSER[tUserIndex].mAvatarInfo.aMoney + (LONGLONG)aMoneyForClaim;
	if (tCheckValue > MAX_NUMBER_SIZE)
	{
		tempvalueformoney = (LONGLONG)tCheckValue - (LONGLONG)MAX_NUMBER_SIZE;
		tempmoneyfortransfer = -1 * (mUSER[tUserIndex].mAvatarInfo.aMoney - tempvalueformoney);
		aMoney2ForClaim += 2;
		aMoneyForClaim = tempvalueformoney;
		mUSER[tUserIndex].mAvatarInfo.aMoney = aMoneyForClaim;
		mUSER[tUserIndex].mAvatarInfo.aMoney2 += aMoney2ForClaim;
		mTRANSFER.B_CLAIM_MONEY_PROXY_SHOP(0, tempmoneyfortransfer, aMoney2ForClaim);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aMoney += aMoneyForClaim;
	mUSER[tUserIndex].mAvatarInfo.aMoney2 += aMoney2ForClaim;
	mTRANSFER.B_CLAIM_MONEY_PROXY_SHOP(0, aMoneyForClaim, aMoney2ForClaim);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}
void W_FISHING_STATE_SEND(int tUserIndex)
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
	float tCoordX;
	float tCoordZ;

	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tCoordX, &tPacket[5], 4);
	CopyMemory(&tCoordZ, &tPacket[9], 4);

	switch (tSort)
	{
	case 1:
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 1;
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 1;
		mAVATAR_OBJECT[tUserIndex].mFishPreTime = GetTickCount();
		mAVATAR_OBJECT[tUserIndex].mFishReel = FALSE;
		mTRANSFER.B_FISHING_STATE_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 1, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
		return;

	case 2:
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState = 0;
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = 0;
		mAVATAR_OBJECT[tUserIndex].mFishReel = FALSE;
		mTRANSFER.B_FISHING_STATE_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 2, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
		return;
	}
}
void W_FISHING_RESULT_SEND(int tUserIndex)
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
	int tFishingStep;
	CopyMemory(&tSort, &tPacket[1], 4);
	CopyMemory(&tFishingStep, &tPacket[5], 4);

	switch (tSort)
	{
	case 1:
		mAVATAR_OBJECT[tUserIndex].mFishPreTime = GetTickCount();
		mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep = tFishingStep;
		return;
	}
}
void W_FISHING_REWARD_SEND(int tUserIndex)
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

	int tRandomNumber;
	ITEM_INFO* tITEM_INFO;
	int iPage = 0, iInvenIndex = 0, iInvenSlot = 0;

	if (!mAVATAR_OBJECT[tUserIndex].mFishReel)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep != 2 && mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep != 3)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	mAVATAR_OBJECT[tUserIndex].mFishReel = FALSE;

	tRandomNumber = rand() % 6;
	switch (tRandomNumber)
	{
	case 0:
		tITEM_INFO = mITEM.Search(1103);
		break;
	case 1:
		tITEM_INFO = mITEM.Search(1019);
		break;
	case 2:
		tITEM_INFO = mITEM.Search(1020);
		break;
	case 3:
		tITEM_INFO = mITEM.Search(1021);
		break;
	case 4:
		tITEM_INFO = mITEM.Search(1022);
		break;
	case 5:
		tITEM_INFO = mITEM.Search(1023);
		break;
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
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][4] = 0;
			mUSER[tUserIndex].mAvatarInfo.aInventory[iPage][iInvenSlot][5] = 0;
			mTRANSFER.B_FISHING_SUCCESS_RECV(1, tITEM_INFO->iIndex, iPage, iInvenSlot, iInvenIndex);
			mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_FISHING_STATE_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 3, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
			return;
		}
	}
	else
	{
		mTRANSFER.B_FISHING_SUCCESS_RECV(2, tITEM_INFO->iIndex, iPage, iInvenSlot, iInvenIndex);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_FISHING_STATE_RECV(tUserIndex, mAVATAR_OBJECT[tUserIndex].mUniqueNumber, 3, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingState, mAVATAR_OBJECT[tUserIndex].mDATA.mFishingStep);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1);
		return;
	}
}
void W_FACTION_TRAP_ACTIVATE(int tUserIndex)
{
	int TrapIndex;
	float tEnemyLocation[3];
	BYTE tData[100];
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
	CopyMemory(&TrapIndex, &tPacket[1], 4);
	CopyMemory(&tEnemyLocation[0], &tPacket[5], 12);

	mGAME.mFactionTrap.mTrapLocation[TrapIndex][0] = 0.0f;
	mGAME.mFactionTrap.mTrapLocation[TrapIndex][1] = 0.0f;
	mGAME.mFactionTrap.mTrapLocation[TrapIndex][2] = 0.0f;

	mTRANSFER.B_FACTION_TRAP_RECV(&mGAME.mFactionTrap);
	mUTIL.Broadcast(FALSE, 0, 0);

	CopyMemory(&tData[4], &mSERVER_INFO.mServerNumber, 4);
	CopyMemory(&tData[8], &mUSER[tUserIndex].mAvatarInfo.aTribe, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(628, &tData[0]);
}
void W_CLOAK_UPGRADE_SEND(int tUserIndex)
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
	ITEM_INFO* tITEM_INFO;
	int tRandom;
	int tValue[6];

	CopyMemory(&tPage1, &tPacket[1], 4);
	CopyMemory(&tIndex1, &tPacket[5], 4);
	CopyMemory(&tPage2, &tPacket[9], 4);
	CopyMemory(&tIndex2, &tPacket[13], 4);

	if (tPage1 < 0 || tPage1 > 1 || tPage2 < 0 || tPage2 > 1 || tIndex1 < 0 || tIndex1 > 63 || tIndex2 < 0 || tIndex2 > 63)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tPage1 == 1 || tPage2 == 1)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate < mUTIL.ReturnNowDate())
		{
			mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
			return;
		}
	}
	tITEM_INFO = mITEM.Search(mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][0]);
	if (!tITEM_INFO)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (tITEM_INFO->iIndex != 1401 && tITEM_INFO->iIndex != 1402 && tITEM_INFO->iIndex != 1403 && tITEM_INFO->iIndex != 1404)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] != 984)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	if (mUSER[tUserIndex].mAvatarInfo.aMoney < 100000000)
	{
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);
		return;
	}
	tRandom = rand() % 300;
	if (tRandom <= 2)
	{
		if (tITEM_INFO->iIndex == 1401)
		{
			tValue[0] = 86760;
		}
		if (tITEM_INFO->iIndex == 1403 || tITEM_INFO->iIndex == 1404)
		{
			tValue[0] = 86761;
		}
		tValue[1] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][1];
		tValue[2] = mUSER[tUserIndex].mAvatarInfo.aInventory[tPage1][tIndex1][2];
		tValue[3] = 0;
		tValue[4] = 0;
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
		mUSER[tUserIndex].mAvatarInfo.aMoney -= 100000000;
		mTRANSFER.B_CLOAK_UPGRADE_RECV(0, &tValue[0]);
		mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		return;
	}
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][0] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][1] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][2] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][3] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][4] = 0;
	mUSER[tUserIndex].mAvatarInfo.aInventory[tPage2][tIndex2][5] = 0;
	mUSER[tUserIndex].mAvatarInfo.aMoney -= 100000000;
	mTRANSFER.B_CLOAK_UPGRADE_RECV(1, &tValue[0]);
	mUSER[tUserIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
	return;
}