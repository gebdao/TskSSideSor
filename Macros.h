#pragma once


#define mMyId	mUSER[tUserIndex].uID


#define mMyName	mUSER[tUserIndex].mAvatarInfo.aName
#define mMyTribe	mUSER[tUserIndex].mAvatarInfo.aTribe
#define mPrevTribe	mUSER[tUserIndex].mAvatarInfo.aPreviousTribe
#define mCP	mUSER[tUserIndex].mAvatarInfo.aKillOtherTribe
#define mVit	mUSER[tUserIndex].mAvatarInfo.aVit
#define mStr	mUSER[tUserIndex].mAvatarInfo.aStr
#define mDex	mUSER[tUserIndex].mAvatarInfo.aDex
#define mInt	mUSER[tUserIndex].mAvatarInfo.aInt
#define mExp1	mUSER[tUserIndex].mAvatarInfo.aGeneralExperience1
#define mExp2	mUSER[tUserIndex].mAvatarInfo.aGeneralExperience2
#define mLevel1	mUSER[tUserIndex].mAvatarInfo.aLevel1
#define mLevel2	mUSER[tUserIndex].mAvatarInfo.aLevel2
#define mInven	mUSER[tUserIndex].mAvatarInfo.aInventory
#define mBag2	mUSER[tUserIndex].mAvatarInfo.aExpandInventoryDate
#define mSkillPoint	mUSER[tUserIndex].mAvatarInfo.aSkillPoint
#define mStatPoint	mUSER[tUserIndex].mAvatarInfo.aStateBonusPoint
#define mSilver	mUSER[tUserIndex].mAvatarInfo.aMoney
#define mSilver2	mUSER[tUserIndex].mAvatarInfo.aMoney2
#define mPet	mUSER[tUserIndex].mAvatarInfo.aEquip[8][0]
#define mPetFeed	mUSER[tUserIndex].mAvatarInfo.aEquip[8][1]
#define mPetExp	mUSER[tUserIndex].mAvatarInfo.aEquip[8][2]
#define mTwoExp1	mUSER[tUserIndex].mAvatarInfo.aDoubleExpTime1
#define mBeginnerReward	mUSER[tUserIndex].mAvatarInfo.aBeginnerPackageIcon
#define mDoubleCPKill	mUSER[tUserIndex].mAvatarInfo.aDoubleKillNumTime
#define mDoubleExpKill	mUSER[tUserIndex].mAvatarInfo.aDoubleKillExpTime
#define mTimeEffect	mUSER[tUserIndex].mAvatarInfo.aTimeEffect
#define mTimeEffect2	mUSER[tUserIndex].mAvatarInfo.aTimeEffect2
#define mPKPoint	mUSER[tUserIndex].mAvatarInfo.aPK
#define mDailyPVP	mUSER[tUserIndex].mAvatarInfo.aDailyPVPCount
#define mDailyWar	mUSER[tUserIndex].mAvatarInfo.aDailyWarCount
#define mDailyPVM	mUSER[tUserIndex].mAvatarInfo.aDailyPVMKillCount
#define mDailyOnlineTime	mUSER[tUserIndex].mAvatarInfo.aDailyOnlineTime
#define mHSBRank	mUSER[tUserIndex].mAvatarInfo.aRankPoints
#define mAnimalIndex	mUSER[tUserIndex].mAvatarInfo.aAnimalIndex
#define mAnimalTime	mUSER[tUserIndex].mAvatarInfo.aAnimalTime
#define mAnimal	mUSER[tUserIndex].mAvatarInfo.aAnimal
#define mAnimalExp	mUSER[tUserIndex].mAvatarInfo.aAnimalExpActivity
#define mAnimalStat	mUSER[tUserIndex].mAvatarInfo.aAnimalAbilityStats
#define mAbsorbState	mUSER[tUserIndex].mAvatarInfo.aAbsorbState
#define mCapsuleMall	mUSER[tUserIndex].mAvatarInfo.aCapsulePointFromMall
#define mInvenSocket	mUSER[tUserIndex].mAvatarInfo.aInventorySocket
#define mRefinePC	mUSER[tUserIndex].mAvatarInfo.aPreventRefineBreak
#define mDoubleDrop	mUSER[tUserIndex].mAvatarInfo.aDoubleDropTime





// AvatarObject
#define mChar	mAVATAR_OBJECT[tUserIndex]
#define	mCharUniqueNum	mAVATAR_OBJECT[tUserIndex].mUniqueNumber
#define	mCharTribe	mAVATAR_OBJECT[tUserIndex].mDATA.aTribe
#define	mCharPrevTribe	mAVATAR_OBJECT[tUserIndex].mDATA.aPreviousTribe
#define	mCharLevel1	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel1
#define	mCharLevel2	mAVATAR_OBJECT[tUserIndex].mDATA.aLevel2
#define	mCharLifeValue	mAVATAR_OBJECT[tUserIndex].mDATA.aLifeValue
#define	mCharMaxLifeValue	mAVATAR_OBJECT[tUserIndex].mDATA.aMaxLifeValue
#define	mCharManaValue	mAVATAR_OBJECT[tUserIndex].mDATA.aManaValue
#define	mCharMaxManaValue	mAVATAR_OBJECT[tUserIndex].mDATA.aMaxManaValue
#define	mCharCP	mAVATAR_OBJECT[tUserIndex].mDATA.aKillOtherTribe
#define	mCharHSBRank	mAVATAR_OBJECT[tUserIndex].mDATA.aRankPoint
#define	mCharAnimal	mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalNumber
#define mCharSort	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aSort
#define mCharType	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aType
#define mCharFrame	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aFrame
#define mCharLoc	mAVATAR_OBJECT[tUserIndex].mDATA.aAction.aLocation
#define mCharAbsorbState	mAVATAR_OBJECT[tUserIndex].mDATA.aAnimalAbsorbState
#define mCharDuelState	mAVATAR_OBJECT[tUserIndex].mDATA.aDuelState






// 
#define MapNum	mSERVER_INFO.mServerNumber



// Function Macros
#define CheckCraft2(id1, id2)	\
if( tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > 63 || tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > 63 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}\
if( tPage1 == 1 || tPage2 == 1 )\
{\
	if( mBag2 < mUTIL.ReturnNowDate() )\
	{\
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
		return;\
	}\
}\
if( mInven[tPage1][tIndex1][0] != id1 || mInven[tPage2][tIndex2][0] != id2 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}

#define CheckCraft3(id1, id2, id3)	\
if( tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > 63 || tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > 63 || tPage3 < 0 || tPage3 > 1 || tIndex3 < 0 || tIndex3 > 63 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}\
if( tPage1 == 1 || tPage2 == 1 || tPage3 == 1 )\
{\
	if( mBag2 < mUTIL.ReturnNowDate() )\
	{\
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
		return;\
	}\
}\
if( mInven[tPage1][tIndex1][0] != id1 || mInven[tPage2][tIndex2][0] != id2 || mInven[tPage3][tIndex3][0] != id3 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}

#define CheckCraft4(id1, id2, id3, id4)	\
if( tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > 63 || tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > 63 || tPage3 < 0 || tPage3 > 1 || tIndex3 < 0 || tIndex3 > 63 || tPage4 < 0 || tPage4 > 1 || tIndex4 < 0 || tIndex4 > 63 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}\
if( tPage1 == 1 || tPage2 == 1 || tPage3 == 1 || tPage4 == 1 )\
{\
	if( mBag2 < mUTIL.ReturnNowDate() )\
	{\
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
		return;\
	}\
}\
if( mInven[tPage1][tIndex1][0] != id1 || mInven[tPage2][tIndex2][0] != id2 || mInven[tPage3][tIndex3][0] != id3 || mInven[tPage4][tIndex4][0] != id4 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}

#define CheckCraft4_2()	\
if( tPage1 < 0 || tPage1 > 1 || tIndex1 < 0 || tIndex1 > 63 || tPage2 < 0 || tPage2 > 1 || tIndex2 < 0 || tIndex2 > 63 || tPage3 < 0 || tPage3 > 1 || tIndex3 < 0 || tIndex3 > 63 || tPage4 < 0 || tPage4 > 1 || tIndex4 < 0 || tIndex4 > 63 )\
{\
	mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
	return;\
}\
if( tPage1 == 1 || tPage2 == 1 || tPage3 == 1 || tPage4 == 1 )\
{\
	if( mBag2 < mUTIL.ReturnNowDate() )\
	{\
		mUSER[tUserIndex].Quit(__FILE__, __FUNCTION__, __LINE__);\
		return;\
	}\
}

#define LogCraft2(type)	\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage2][tIndex2][0], mInven[tPage2][tIndex2][3], mInven[tPage2][tIndex2][4], mInven[tPage2][tIndex2][5]);

#define LogCraft3(type)	\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage2][tIndex2][0], mInven[tPage2][tIndex2][3], mInven[tPage2][tIndex2][4], mInven[tPage2][tIndex2][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage3][tIndex3][0], mInven[tPage3][tIndex3][3], mInven[tPage3][tIndex3][4], mInven[tPage3][tIndex3][5]);

#define LogCraft4(type)	\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage1][tIndex1][0], mInven[tPage1][tIndex1][3], mInven[tPage1][tIndex1][4], mInven[tPage1][tIndex1][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage2][tIndex2][0], mInven[tPage2][tIndex2][3], mInven[tPage2][tIndex2][4], mInven[tPage2][tIndex2][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage3][tIndex3][0], mInven[tPage3][tIndex3][3], mInven[tPage3][tIndex3][4], mInven[tPage3][tIndex3][5]);\
mGAMELOG.GL_638_MAKE_ITEM(tUserIndex, type, mInven[tPage4][tIndex4][0], mInven[tPage4][tIndex4][3], mInven[tPage4][tIndex4][4], mInven[tPage4][tIndex4][5]);



#define ClearInv(tpage, tindex)	\
mInven[tpage][tindex][0] = 0;\
mInven[tpage][tindex][1] = 0;\
mInven[tpage][tindex][2] = 0;\
mInven[tpage][tindex][3] = 0;\
mInven[tpage][tindex][4] = 0;\
mInven[tpage][tindex][5] = 0;

#define ClearSocket(tpage, tindex)	\
mInvenSocket[tpage][tindex][0] = 0;\
mInvenSocket[tpage][tindex][1] = 0;\
mInvenSocket[tpage][tindex][2] = 0;\
mInvenSocket[tpage][tindex][3] = 0;\
mInvenSocket[tpage][tindex][4] = 0;

#define CheckAttackSpeed(val)	\
if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (val - (val * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))\
{\
	return TRUE;\
}

#define CheckAttackSpeed_2(attacknum, val)	\
if (mUSER[tUserIndex].mNowAttackPacketNum == attacknum)\
{\
	if ((GetTickCount() - mUSER[tUserIndex].mTickForAttackSpeed) < (val - (val * (mUTIL.ReturnRFValue(mUSER[tUserIndex].mAvatarInfo.aEquip[3][2]) * 0.005))))\
	{\
		return TRUE;\
	}\
}

#define InitDropVector(...)	\
tDropTable.clear();\
tDropTable = { __VA_ARGS__ };\
mUTIL.ProcessForDropItem(1, tDropTable[rand() % tDropTable.size()], 0, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);

#define InitDropVector_2(...)	\
tDropTable.clear();\
tDropTable = { __VA_ARGS__ };\
for (auto it : tDropTable)\
{\
	mUTIL.ProcessForDropItem(3, it, 1, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);\
}

#define InitDropVector_LOD(...)	\
tDropTable.clear();\
tDropTable = { __VA_ARGS__ };\
tLodDropValue = tDropTable[rand() % tDropTable.size()];\
mUTIL.ProcessForDropItem(1, tLodDropValue, 0, 0, 0, &mDATA.mAction.aLocation[0], &tMasterName[0], "", 0, mUSER[tUserIndex].mAvatarInfo.aTribe, 0);


#define InitUseItem(...) \
tItem.clear();\
tItem = { __VA_ARGS__ };\
tValue = tItem[rand() % tItem.size()];

#define PickFrmVec(...)	\
tItem.clear();\
tItem = { __VA_ARGS__ };\
tValue = tItem[rand() % tItem.size()];