#include "MainApp.h"


MyGame mGAME;

//CREATE
MyGame::MyGame(void)
{
	//mCompressLibrary = NULL;
}

//INIT
BOOL MyGame::Init(void)
{
	int index01;

	time_t tCountSeconds;
	struct tm* tPresentTime;

	mGeneralExperienceUpRatio = mSERVER_INFO.WORLD_EXP;
	mItemDropUpRatio = mSERVER_INFO.WORLD_ITEM_DROP;
	mKillOtherTribeAddValue = mSERVER_INFO.WORLD_KTAV;
	mPatExperienceUpRatio = mSERVER_INFO.WORLD_PATEXP;

	mTeacherPointUpRatio = 1;
	mBonusGainGeneralExperienceUpRatio = 1.0f;
	mGeneralExperienceDownRatio = 1;
	mKillOtherTribeExperienceUpRatio = 1;

	mAvatarObjectUniqueNumber = 1;
	mMonsterObjectUniqueNumber = 1;
	mItemObjectUniqueNumber = 1;
	mAvatarDuelUniqueNumber = 1;
	mAvatarPShopUniqueNumber = 1;
	mTickCount = 0;
	mUpdateTimeForTribeBankInfo = GetTickCount64();
	mTribeBankInfo[0] = 0;
	mTribeBankInfo[1] = 0;
	mTribeBankInfo[2] = 0;
	mTribeBankInfo[3] = 0;
	mSymbolDamageUp[0] = 0.0f;
	mSymbolDamageUp[1] = 0.0f;
	mSymbolDamageUp[2] = 0.0f;
	mSymbolDamageUp[3] = 0.0f;
	mSymbolDamageDown[0] = 0.0f;
	mSymbolDamageDown[1] = 0.0f;
	mSymbolDamageDown[2] = 0.0f;
	mSymbolDamageDown[3] = 0.0f;
	AdjustSymbolDamageInfo();
	mCheckActiveBattleLogic = FALSE;
	mWorldInfo.mTribeVoteState[0] = 0;
	mWorldInfo.mTribeVoteState[1] = 0;
	mWorldInfo.mTribeVoteState[2] = 0;
	mWorldInfo.mTribeVoteState[3] = 0;

	mWorldInfo.mTribeGuardState[0][0] = 1;
	mWorldInfo.mTribeGuardState[0][1] = 1;
	mWorldInfo.mTribeGuardState[0][2] = 1;
	mWorldInfo.mTribeGuardState[0][3] = 1;
	mWorldInfo.mTribeGuardState[1][0] = 1;
	mWorldInfo.mTribeGuardState[1][1] = 1;
	mWorldInfo.mTribeGuardState[1][2] = 1;
	mWorldInfo.mTribeGuardState[1][3] = 1;
	mWorldInfo.mTribeGuardState[2][0] = 1;
	mWorldInfo.mTribeGuardState[2][1] = 1;
	mWorldInfo.mTribeGuardState[2][2] = 1;
	mWorldInfo.mTribeGuardState[2][3] = 1;
	mWorldInfo.mTribeGuardState[3][0] = 1;
	mWorldInfo.mTribeGuardState[3][1] = 1;
	mWorldInfo.mTribeGuardState[3][2] = 1;
	mWorldInfo.mTribeGuardState[3][3] = 1;

	mDuel_124 = FALSE;
	mDuel_124_RemainTime = 0;
	mDuel_124_AvatarNum[0] = 0;
	mDuel_124_AvatarNum[1] = 0;
	mDuel_124_Pvp = FALSE;

	switch (mSERVER_INFO.mServerNumber)
	{
	case  37:
		mCheckTribeVoteServer = TRUE;
///		mTreasureHunterEventState = 0;
		break;
	default:
		mCheckTribeVoteServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  37:
		mCheckAllienceServer = TRUE;
		mAlliencePostTick = 0;
		mAllienceBattleState = 0;
		mAllienceRemainTime = 0;
		mAllienceBattlePostLocation[0][0] = -41.0f;
		mAllienceBattlePostLocation[0][1] = 8.0f;
		mAllienceBattlePostLocation[0][2] = -272.0f;
		mAllienceBattlePostLocation[1][0] = 35.0f;
		mAllienceBattlePostLocation[1][1] = 8.0f;
		mAllienceBattlePostLocation[1][2] = -272.0f;
		mAllienceBattlePostRadius[0] = 10.0f;
		mAllienceBattlePostRadius[1] = 10.0f;
		mAlliencePostAvatarIndex[0] = -1;
		mAlliencePostAvatarIndex[1] = -1;
		mAlliencePostAvatarUniqueNumber[0] = 0;
		mAlliencePostAvatarUniqueNumber[1] = 0;
		mAlliencePostAvatarTribe[0] = -1;
		mAlliencePostAvatarTribe[1] = -1;
		break;
	default:
		mCheckAllienceServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  37:
		mCheckZone037Server = TRUE;
		mZone037PostTick = 0;
		mZone037BattleState = 0;
		mZone037RemainTime = 0;
		break;
	default:
		mCheckZone037Server = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 124:
		mCheckZone124Server = TRUE;
		break;
	default:
		mCheckZone124Server = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  71:
		mCheckZone071TypeServer = TRUE;
		mZone071TypeZoneIndex = 0;
		break;
	case  72:
		mCheckZone071TypeServer = TRUE;
		mZone071TypeZoneIndex = 1;
		break;
	case  73:
		mCheckZone071TypeServer = TRUE;
		mZone071TypeZoneIndex = 2;
		break;
	default:
		mCheckZone071TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  49:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 0;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 146:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 1;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 149:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 2;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 154:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 3;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 157:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 4;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 160:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 5;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 120:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 6;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 121:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 7;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 122:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 8;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 295:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 9;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	case 296:
		mCheckZone049TypeServer = TRUE;
		mZone049TypeZoneIndex = 10;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime1 = 0;
		mZone049TypeRemainTime2 = 0;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		break;
	default:
		mCheckZone049TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  51:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 0;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	case 147:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 1;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	case 150:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 2;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	case 155:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 3;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	case 158:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 4;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	case 161:
		mCheckZone051TypeServer = TRUE;
		mZone051TypeZoneIndex = 5;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		mZone051TypeRemainTime = 0;
		break;
	default:
		mCheckZone051TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  53:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 0;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 0.0f;
		mZone053TypeBattlePostLocation[1] = 0.0f;
		mZone053TypeBattlePostLocation[2] = 400.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 148:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 1;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 0.0f;
		mZone053TypeBattlePostLocation[1] = 0.0f;
		mZone053TypeBattlePostLocation[2] = 400.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 151:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 2;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 0.0f;
		mZone053TypeBattlePostLocation[1] = 0.0f;
		mZone053TypeBattlePostLocation[2] = 400.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 152:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 3;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 0.0f;
		mZone053TypeBattlePostLocation[1] = 0.0f;
		mZone053TypeBattlePostLocation[2] = 400.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 153:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 4;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 0.0f;
		mZone053TypeBattlePostLocation[1] = 0.0f;
		mZone053TypeBattlePostLocation[2] = 400.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 156:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 5;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 60.0f;
		mZone053TypeBattlePostLocation[1] = 106.0f;
		mZone053TypeBattlePostLocation[2] = 4190.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 159:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 6;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 60.0f;
		mZone053TypeBattlePostLocation[1] = 106.0f;
		mZone053TypeBattlePostLocation[2] = 4190.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 162:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 7;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 60.0f;
		mZone053TypeBattlePostLocation[1] = 106.0f;
		mZone053TypeBattlePostLocation[2] = 4190.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 163:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 8;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 60.0f;
		mZone053TypeBattlePostLocation[1] = 106.0f;
		mZone053TypeBattlePostLocation[2] = 4190.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	case 164:
		mCheckZone053TypeServer = TRUE;
		mZone053TypeZoneIndex = 9;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		mZone053TypeRemainTime = 0;
		mZone053TypeBattlePostLocation[0] = 60.0f;
		mZone053TypeBattlePostLocation[1] = 106.0f;
		mZone053TypeBattlePostLocation[2] = 4190.0f;
		mZone053TypeBattlePostRadius = 25.0f;
		mZone053TypePostAvatarIndex = -1;
		mZone053TypePostAvatarUniqueNumber = 0;
		mZone053TypeSaveTick = 0;
		break;
	default:
		mCheckZone053TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  38:
		mCheckZone038Server = TRUE;
		mZone038PostTick = 0;
		mZone038BattleState = 0;
		mZone038RemainTime = 0;
		mZone038BattlePostLocation[0] = -40.0f;
		mZone038BattlePostLocation[1] = 200.0f;
		mZone038BattlePostLocation[2] = 6379.0f;
		mZone038BattlePostRadius = 25.0f;
		mZone038PostAvatarIndex = -1;
		mZone038PostAvatarUniqueNumber = 0;
		mYanggokEventState = 0;////Yanggok monsters///
		break;
	default:
		mCheckZone038Server = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case  39:
	case 144:
	case 145:
	case  74:
		mCheckZone039TypeServer = TRUE;
		mZone039TypePostTick = 0;
		mZone039TypeBattleState = 0;
		break;
	default:
		mCheckZone039TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 101:
	case 102:
	case 103:
	case 104:
	case 105:
	case 106:
	case 107:
	case 108:
	case 109:
	case 110:
	case 111:
	case 112:
	case 113:
	case 114:
	case 115:
	case 116:
	case 117:
	case 167:
	case 168:
	case 169:
	case 251:
	case 252:
	case 253:
	case 254:
	case 255:
	case 256:
	case 257:
	case 258:
	case 259:
	case 260:
	case 261:
	case 262:
	case 263:
	case 264:
	case 265:
	case 266:
		mCheckZone101TypeServer = TRUE;
		break;
	default:
		mCheckZone101TypeServer = FALSE;
		break;
	}

	switch (mSERVER_INFO.mServerNumber)
	{
	case 125:
		mCheckZone125Server = TRUE;
		break;
	default:
		mCheckZone125Server = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 126:
	case 127:
	case 128:
	case 129:
	case 130:
	case 131:
	case 132:
	case 133:
	case 134:
	case 135:
	case 136:
	case 137:
	case 171:
	case 172:
	case 173:
	case 174:
	case 210:
	case 211:
	case 212:
	case 213:
	case 214:
	case 215:
	case 216:
	case 217:
	case 218:
	case 219:
	case 220:
	case 221:
	case 222:
	case 223:
	case 224:
	case 225:
	case 226:
	case 227:
	case 228:
	case 229:
	case 230:
	case 231:
	case 232:
	case 233:
	case 295:
		mCheckZone126TypeServer = TRUE;
		break;
	default:
		mCheckZone126TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 175:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 0;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 176:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 0;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 177:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 0;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 178:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 1;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 179:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 1;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 180:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 1;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 181:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 1;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 182:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 2;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 183:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 2;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 184:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 2;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 185:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 2;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 186:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 3;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 187:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 3;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 188:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 3;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 189:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 3;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 190:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 4;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 191:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 4;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 192:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 4;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case 193:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 4;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  19:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 5;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  25:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 6;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  31:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 0;
		mZone175TypeZoneIndex2 = 7;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  20:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 5;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  26:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 6;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  32:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 1;
		mZone175TypeZoneIndex2 = 7;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  21:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 5;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  27:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 6;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  33:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 2;
		mZone175TypeZoneIndex2 = 7;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  34:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 5;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  35:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 6;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	case  36:
		mCheckZone175TypeServer = TRUE;
		mZone175TypeZoneIndex1 = 3;
		mZone175TypeZoneIndex2 = 7;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		mZone175TypeRemainTime = 0;
		break;
	default:
		mCheckZone175TypeServer = FALSE;
		break;
	}
#ifdef __GOD__
	switch (mSERVER_INFO.mServerNumber)
	{
	case 194:
		mCheckZone194Server = TRUE;
		mZone194PostTick = 0;
		mZone194BattleState = 0;
		mZone194RemainTime1 = 0;
		mZone194RemainTime2 = 0;
		mZone194BattleResult[0] = 0;
		mZone194BattleResult[1] = 0;
		mZone194BattleResult[2] = 0;
		mZone194BattleResult[3] = 0;
		break;
	default:
		mCheckZone194Server = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 196:
		mCheckZone195TypeServer = TRUE;
		mZone195PostTick = 0;
		mZone195BattleState = 0;
		mZone195RemainTime = 0;
		mZone195BattlePostLocation[0] = -20.0f;
		mZone195BattlePostLocation[1] = -144.0f;
		mZone195BattlePostLocation[2] = 2511.0f;
		mZone195BattlePostRadius = 25.0f;
		mZone195PostAvatarIndex = -1;
		mZone195PostAvatarUniqueNumber = 0;
		mZone195LevelState = 0;
		break;
	case 85:
		mCheckZone195TypeServer = TRUE;
		mZone195PostTick = 0;
		mZone195BattleState = 0;
		mZone195RemainTime = 0;
		mZone195BattlePostLocation[0] = -20.0f;
		mZone195BattlePostLocation[1] = -144.0f;
		mZone195BattlePostLocation[2] = 2511.0f;
		mZone195BattlePostRadius = 25.0f;
		mZone195PostAvatarIndex = -1;
		mZone195PostAvatarUniqueNumber = 0;
		mZone195LevelState = 1;
		break;
	case 99:
		mCheckZone195TypeServer = TRUE;
		mZone195PostTick = 0;
		mZone195BattleState = 0;
		mZone195RemainTime = 0;
		mZone195BattlePostLocation[0] = -20.0f;
		mZone195BattlePostLocation[1] = -144.0f;
		mZone195BattlePostLocation[2] = 2511.0f;
		mZone195BattlePostRadius = 25.0f;
		mZone195PostAvatarIndex = -1;
		mZone195PostAvatarUniqueNumber = 0;
		mZone195LevelState = 2;
		break;
	case 100:
		mCheckZone195TypeServer = TRUE;
		mZone195PostTick = 0;
		mZone195BattleState = 0;
		mZone195RemainTime = 0;
		mZone195BattlePostLocation[0] = -20.0f;
		mZone195BattlePostLocation[1] = -144.0f;
		mZone195BattlePostLocation[2] = 2511.0f;
		mZone195BattlePostRadius = 25.0f;
		mZone195PostAvatarIndex = -1;
		mZone195PostAvatarUniqueNumber = 0;
		mZone195LevelState = 3;
		break;
	default:
		mCheckZone195TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 250:
		mCheckZone267TypeServer = TRUE;
		mZone267TypeZoneIndex = 3;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		mZone267TypeRemainTime1 = 0;
		mZone267TypeRemainTime2 = 0;
		mZone267TypeBattleResult[0] = 0;
		mZone267TypeBattleResult[1] = 0;
		mZone267TypeBattleResult[2] = 0;
		mZone267TypeBattleResult[3] = 0;
		break;
	case 267:
		mCheckZone267TypeServer = TRUE;
		mZone267TypeZoneIndex = 0;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		mZone267TypeRemainTime1 = 0;
		mZone267TypeRemainTime2 = 0;
		mZone267TypeBattleResult[0] = 0;
		mZone267TypeBattleResult[1] = 0;
		mZone267TypeBattleResult[2] = 0;
		mZone267TypeBattleResult[3] = 0;
		break;
	case 268:
		mCheckZone267TypeServer = TRUE;
		mZone267TypeZoneIndex = 1;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		mZone267TypeRemainTime1 = 0;
		mZone267TypeRemainTime2 = 0;
		mZone267TypeBattleResult[0] = 0;
		mZone267TypeBattleResult[1] = 0;
		mZone267TypeBattleResult[2] = 0;
		mZone267TypeBattleResult[3] = 0;
		break;
	case 269:
		mCheckZone267TypeServer = TRUE;
		mZone267TypeZoneIndex = 2;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		mZone267TypeRemainTime1 = 0;
		mZone267TypeRemainTime2 = 0;
		mZone267TypeBattleResult[0] = 0;
		mZone267TypeBattleResult[1] = 0;
		mZone267TypeBattleResult[2] = 0;
		mZone267TypeBattleResult[3] = 0;
		break;
	default:
		mCheckZone267TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber)
	{
	case 241:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 0;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 242:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 1;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 243:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 2;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 244:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 3;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 245:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 4;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 246:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 5;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 247:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 6;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 248:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 7;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 249:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 8;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 292:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 9;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 293:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 10;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	case 294:
		mCheckZone241TypeServer = TRUE;
		mZone241Type = 11;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mZone241PostTick = 0;
		mZone241RemainTime = 0;
		mSERVER.mMAX_USER_NUM = 1;
		break;
	default:
		mCheckZone241TypeServer = FALSE;
		break;
	}
	switch (mSERVER_INFO.mServerNumber) 
	{
	case 84:
		mCheckZone084TypeServer = true;
		break;
	default:
		mCheckZone084TypeServer = false;
		break;
	}

	switch (mSERVER_INFO.mServerNumber)
	{
	case 200:
		mCheckZone200TypeServer = TRUE;
		mZone200PostTick = 0;
		mZone200RemainTime1 = 0;
		mZone200RemainTime2 = 0;
		mZone200BattleState = 0;
		break;
	default:
		mCheckZone200TypeServer = FALSE;
		break;
	}

	switch (mSERVER_INFO.mServerNumber)
	{
	case 88:
		mCheckZone88TypeServer = TRUE;
		mZone88PostTick = 0;
		mZone88PostAvatarIndex = -1;
		mZone88PostAvatarUniqueNumber = 0;
		mZone88BattleState1 = 0;
		mZone88BattleState2 = 0;
		mZone88BattlePostLocation[0] = 4.0f;
		mZone88BattlePostLocation[1] = -140.0f;
		mZone88BattlePostLocation[2] = 2514.0f;
		mZone88BattlePostRadius = 50.0f;
		break;
	default:
		mCheckZone88TypeServer = FALSE;
		break;
	}

	switch (mSERVER_INFO.mServerNumber)
	{
	case 319:
		mCheckZone319TypeServer = TRUE;
		mZone319TypeZoneIndex = 0;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime1 = 0;
		mZone319TypeRemainTime2 = 0;
		mZone319TypeBattleResult[0] = 0;
		mZone319TypeBattleResult[1] = 0;
		mZone319TypeBattleResult[2] = 0;
		mZone319TypeBattleResult[3] = 0;
		break;
	case 320:
		mCheckZone319TypeServer = TRUE;
		mZone319TypeZoneIndex = 1;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime1 = 0;
		mZone319TypeRemainTime2 = 0;
		mZone319TypeBattleResult[0] = 0;
		mZone319TypeBattleResult[1] = 0;
		mZone319TypeBattleResult[2] = 0;
		mZone319TypeBattleResult[3] = 0;
		break;
	case 321:
		mCheckZone319TypeServer = TRUE;
		mZone319TypeZoneIndex = 2;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime1 = 0;
		mZone319TypeRemainTime2 = 0;
		mZone319TypeBattleResult[0] = 0;
		mZone319TypeBattleResult[1] = 0;
		mZone319TypeBattleResult[2] = 0;
		mZone319TypeBattleResult[3] = 0;
		break;
	case 322:
		mCheckZone319TypeServer = TRUE;
		mZone319TypeZoneIndex = 3;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime1 = 0;
		mZone319TypeRemainTime2 = 0;
		mZone319TypeBattleResult[0] = 0;
		mZone319TypeBattleResult[1] = 0;
		mZone319TypeBattleResult[2] = 0;
		mZone319TypeBattleResult[3] = 0;
		break;
	case 295:
		mCheckZone295TypeServer = TRUE;
		mZone295TypeBattleResult[0] = 0;
		mZone295TypeBattleResult[1] = 0;
		mZone295TypeBattleResult[2] = 0;
		mZone295TypeBattleResult[3] = 0;
		break;
	case 296:
		mCheckZone295TypeServer = TRUE;
		mZone295TypeBattleResult[0] = 0;
		mZone295TypeBattleResult[1] = 0;
		mZone295TypeBattleResult[2] = 0;
		mZone295TypeBattleResult[3] = 0;
		break;
	case 99:
		mCheckZone295TypeServer = TRUE;
		mZone295TypeBattleResult[0] = 0;
		mZone295TypeBattleResult[1] = 0;
		mZone295TypeBattleResult[2] = 0;
		mZone295TypeBattleResult[3] = 0;
		break;
	case 323:
		mCheckZone319TypeServer = TRUE;
		mZone319TypeZoneIndex = 4;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime1 = 0;
		mZone319TypeRemainTime2 = 0;
		mZone319TypeBattleResult[0] = 0;
		mZone319TypeBattleResult[1] = 0;
		mZone319TypeBattleResult[2] = 0;
		mZone319TypeBattleResult[3] = 0;
		break;
	default:
		mCheckZone319TypeServer = FALSE;
		break;
	}

	mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 0;
	mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 0;
	mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 0;
	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 0;

	if (mCheckZone126TypeServer)
	{
		mGeneralExperienceUpRatio = mSERVER_INFO.WORLD_EXP * 2;
		mItemDropUpRatio = mSERVER_INFO.WORLD_ITEM_DROP * 2;
		mPatExperienceUpRatio = mSERVER_INFO.WORLD_PATEXP * 2;
	}

	// Traps
	memset(&mFactionTrap, 0, sizeof(mFactionTrap));
#endif
	for (index01 = 0; index01 < MAX_AVATAR_OBJECT_NUM; index01++)
	{
		mAVATAR_OBJECT[index01].mIndex = index01;
		mAVATAR_OBJECT[index01].mCheckDeath = false;
		mAVATAR_OBJECT[index01].mCheckCount = 0;
		mAVATAR_OBJECT[index01].mCheckValidState = FALSE;
	}
	for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		mMONSTER_OBJECT[index01].mCheckValidState = FALSE;
		mMONSTER_OBJECT[index01].mInvalidTimeForSummon = GetTickCount64();
		memset(mMONSTER_OBJECT[index01].mAvatarName, 0, MAX_AVATAR_NAME_LENGTH);
	}
	for (index01 = 0; index01 < MAX_ITEM_OBJECT_NUM; index01++)
	{
		mITEM_OBJECT[index01].mCheckValidState = FALSE;
	}
	if (!mZONEMAININFO.Init())
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : ZoneMainInfo start", __FUNCTION__);
	if (!mZONENPCINFO.Init())
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : ZoneNPCInfo start", __FUNCTION__);
	if (!mLEVEL.Init("DATA/005_00001.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Level start", __FUNCTION__);
	if (!mITEM.Init("DATA/005_00002.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Item start", __FUNCTION__);
	if (!mSKILL.Init("DATA/005_00003.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Skill start", __FUNCTION__);
	if (!mMONSTER.Init("DATA/005_00004.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Monster start", __FUNCTION__);
	if (!mNPC.Init("DATA/005_00005.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : NPC start", __FUNCTION__);
	if (!mQUEST.Init("DATA/005_00006.IMG"))
	{
		return FALSE;
	}
	if (!mSOCKET.Init("DATA/005_00010.IMG"))
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Quest start", __FUNCTION__);
	if (!mPAT.Init())
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : Pat start", __FUNCTION__);

	if (!mWORLD.LoadWM())
	{
		return FALSE;
	}
	//__LogMgr()->Log("![%s] : World start", __FUNCTION__);

	mSUMMON.Init();
	mSUMMON.SummonGuard(FALSE, TRUE);
	mSUMMON.SummonGuard(TRUE, TRUE);
	mSUMMON.SummonTribeSymbol();
	mSUMMON.SummonTowerSystem(FALSE, 0);
	LoadBloodStainedShopInfo();
	LoadSpecialShop();
	switch (mSERVER_INFO.mServerNumber)
	{
	case 1: case 6: case 11: case 140:
		mSUMMON.SummonMonsterWithoutTimeLimit();
		break;
	}
	bAttackMonsterSymbol = true;

	return TRUE;
}

//DECOMPRESS
BOOL MyGame::Decompress(DWORD tCompressSize, BYTE* tCompress, DWORD tOriginalSize, BYTE* tOriginal)
{
	//tOriginalSize = 0;
	uLongf to = tOriginalSize;
	if ((uncompress(tOriginal, (uLongf*)&to, tCompress, tCompressSize)) != 0)
	{
		return FALSE;
	}

	return TRUE;
}

//ADD_TRIBE_BANK_INFO
void MyGame::AddTribeBankInfo(int tTribe, int tMoney)
{
	if ((tTribe < 0) || (tTribe > 3))
	{
		return;
	}
	if (mUTIL.CheckOverMaximum(mTribeBankInfo[tTribe], tMoney))
	{
		return;
	}
	mTribeBankInfo[tTribe] += tMoney;
}
BOOL MyGame::LoadBloodStainedShopInfo()
{
	std::ifstream tFile("DATA\\BLOODSTAINED.TXT");

	if (!tFile.is_open())
	{
		std::cerr << "Could not open the file: " << "DATA\\BLOODSTAINED.TXT" << std::endl;
		return FALSE;
	}

	std::string tLine;
	int i = 0, j = 0, k = 0;

	while (std::getline(tFile, tLine) && i < 5) 
	{
		std::istringstream iss(tLine);
		std::string value;
		int count = 0;

		while (std::getline(iss, value, ','))
		{
			// Remove brackets if any
			value.erase(std::remove(value.begin(), value.end(), '['), value.end());
			value.erase(std::remove(value.begin(), value.end(), ']'), value.end());

			mBSInfo.mItemInfo[i][j][count] = std::stoi(value);
			count++;

			if (count == 3) 
			{
				count = 0;
				j++;
				if (j == 10)
				{
					j = 0;
					i++;
				}
				if (i == 5) 
				{
					break;
				}
			}
		}
	}
	tFile.close();
	return TRUE;
}

BOOL MyGame::LoadSpecialShop()
{
	int i;
	int j;

	for (i = 0; i < 3; i++)
	{
		for (j = 0; j < 28; j++)
		{
			tSpecialShop[i][j] = 0;
		}
	}
	tSpecialShop[0][0] = 23;
	tSpecialShop[0][1] = 24;
	tSpecialShop[0][2] = 25;
	tSpecialShop[0][3] = 0;

	tSpecialShop[0][4] = 29;
	tSpecialShop[0][5] = 30;
	tSpecialShop[0][6] = 31;
	tSpecialShop[0][7] = 0;

	tSpecialShop[0][8] = 32;
	tSpecialShop[0][9] = 33;
	tSpecialShop[0][10] = 34;
	tSpecialShop[0][11] = 0;

	tSpecialShop[0][12] = 1437;
	tSpecialShop[0][13] = 1422;
	tSpecialShop[0][14] = 0;
	tSpecialShop[0][15] = 0;

	tSpecialShop[0][16] = 1026;
	tSpecialShop[0][17] = 1001;
	tSpecialShop[0][18] = 1471;
	tSpecialShop[0][19] = 1472;

	tSpecialShop[0][20] = 1103;
	tSpecialShop[0][21] = 1237;
	tSpecialShop[0][22] = 1166;
	tSpecialShop[0][23] = 984;

	tSpecialShop[0][24] = 1371;

	return TRUE;
}

//TOWER_SYSTEM
int MyGame::TowerSystemEffect(int tType, int tTribe)
{
	int index01;

	switch (tTribe)
	{
	case 0: // Guanyin
		switch (tType)
		{
		case 1: // Silver Tower
			for (index01 = 0; index01 < 3; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 1)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 2: // CP Tower
			for (index01 = 0; index01 < 3; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 2)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 3: // EXP Tower
			for (index01 = 0; index01 < 3; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 3)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		}
		break;
	case 1: // Snake
		switch (tType)
		{
		case 1: // Silver Tower
			for (index01 = 3; index01 < 6; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 1)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 2: // CP Tower
			for (index01 = 3; index01 < 6; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 2)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 3: // EXP Tower
			for (index01 = 3; index01 < 6; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 3)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		}
		break;
	case 2: // Tiger
		switch (tType)
		{
		case 1: // Silver Tower
			for (index01 = 6; index01 < 9; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 1)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 2: // CP Tower
			for (index01 = 6; index01 < 9; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 2)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 3: // EXP Tower
			for (index01 = 6; index01 < 9; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 3)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		}
		break;
	case 3: // Sky
		switch (tType)
		{
		case 1: // Silver Tower
			for (index01 = 9; index01 < 12; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 1)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 2: // CP Tower
			for (index01 = 9; index01 < 12; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 2)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		case 3: // EXP Tower
			for (index01 = 9; index01 < 12; index01++)
			{
				if (mGAME.mTowerInfo.mTowerInfo[index01] % 100 == 3)
				{
					return mGAME.mTowerInfo.mTowerInfo[index01] / 200;
				}
			}
			return 0;
		}
		break;
	}

}

//PROCESS_TRIBE_VOTE_SERVER
void MyGame::Process_TribeVote_Server(void)
{
	int index01;
	int index02;
	int index03;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	if (tPresentTime == NULL)
	{
		return;
	}
	if ((tPresentTime->tm_mday >= 1) && (tPresentTime->tm_mday <= 5))
	{
		if (mWorldInfo.mTribeVoteState[0] == 1)
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 52;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mTribeVoteState[0] = 1;
		mWorldInfo.mTribeVoteState[1] = 1;
		mWorldInfo.mTribeVoteState[2] = 1;
		mWorldInfo.mTribeVoteState[3] = 1;
		for (index01 = 0; index01 < 4; index01++)
		{
			for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
			{
				strcpy(mTribeInfo.mTribeVoteName[index01][index02], "");
				mTribeInfo.mTribeVoteLevel[index01][index02] = 0;
				mTribeInfo.mTribeVoteKillOtherTribe[index01][index02] = 0;
				mTribeInfo.mTribeVotePoint[index01][index02] = 0;
			}
		}
		return;
	}
	if ((tPresentTime->tm_mday >= 6) && (tPresentTime->tm_mday <= 10))
	{
		if (mWorldInfo.mTribeVoteState[0] == 2)
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 53;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mTribeVoteState[0] = 2;
		mWorldInfo.mTribeVoteState[1] = 2;
		mWorldInfo.mTribeVoteState[2] = 2;
		mWorldInfo.mTribeVoteState[3] = 2;
		return;
	}
	if ((tPresentTime->tm_mday >= 11) && (tPresentTime->tm_mday <= 11))
	{
		switch (tPresentTime->tm_hour)
		{
		case  0:
			if (mWorldInfo.mTribeVoteState[0] == 3)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 54;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mTribeVoteState[0] = 3;
			mWorldInfo.mTribeVoteState[1] = 3;
			mWorldInfo.mTribeVoteState[2] = 3;
			mWorldInfo.mTribeVoteState[3] = 3;
			return;
		case 21:
			if (mWorldInfo.mTribeVoteState[0] == 4)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 55;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mTribeVoteState[0] = 4;
			mWorldInfo.mTribeVoteState[1] = 4;
			mWorldInfo.mTribeVoteState[2] = 4;
			mWorldInfo.mTribeVoteState[3] = 4;
			for (index01 = 0; index01 < 4; index01++)
			{
				index03 = -1;
				for (index02 = 0; index02 < MAX_TRIBE_VOTE_AVATAR_NUM; index02++)
				{
					if (strcmp(mTribeInfo.mTribeVoteName[index01][index02], "") == 0)
					{
						continue;
					}
					if (mTribeInfo.mTribeVotePoint[index01][index02] < 1)
					{
						continue;
					}
					if (index03 == -1)
					{
						index03 = index02;
					}
					else
					{
						if (mTribeInfo.mTribeVotePoint[index01][index02] > mTribeInfo.mTribeVotePoint[index01][index03])
						{
							index03 = index02;
						}
					}
				}
				if (index03 == -1)
				{
					strcpy(mTribeInfo.mTribeMaster[index01], "");
				}
				else
				{
					strncpy(mTribeInfo.mTribeMaster[index01], mTribeInfo.mTribeVoteName[index01][index03], MAX_AVATAR_NAME_LENGTH);
				}
				for (index02 = 0; index02 < MAX_TRIBE_SUBMASTER_NUM; index02++)
				{
					strcpy(mTribeInfo.mTribeSubMaster[index01][index02], "");
				}
			}
			return;
		case 22:
			if (mWorldInfo.mTribeVoteState[0] == 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 56;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mTribeVoteState[0] = 0;
			mWorldInfo.mTribeVoteState[1] = 0;
			mWorldInfo.mTribeVoteState[2] = 0;
			mWorldInfo.mTribeVoteState[3] = 0;
			return;
		}
		return;
	}
}

int MyGame::ReturnAlliance(int tTribe)
{
	if (mWorldInfo.mAllianceState[0][0] == tTribe)
	{
		return mWorldInfo.mAllianceState[0][1];
	}
	else if (mWorldInfo.mAllianceState[0][1] == tTribe)
	{
		return mWorldInfo.mAllianceState[0][0];
	}
	else if (mWorldInfo.mAllianceState[1][0] == tTribe)
	{
		return mWorldInfo.mAllianceState[1][1];
	}
	else if (mWorldInfo.mAllianceState[1][1] == tTribe)
	{
		return mWorldInfo.mAllianceState[1][0];
	}
	else;
	return -1;
}

int MyGame::ReturnAllianceTribe(int tTribe)
{
	if ((49 == mSERVER_INFO.mServerNumber) || (51 == mSERVER_INFO.mServerNumber) || (53 == mSERVER_INFO.mServerNumber)
		|| (146 == mSERVER_INFO.mServerNumber) || (147 == mSERVER_INFO.mServerNumber) || (148 == mSERVER_INFO.mServerNumber)
		|| (149 == mSERVER_INFO.mServerNumber) || (150 == mSERVER_INFO.mServerNumber) || (151 == mSERVER_INFO.mServerNumber)
		|| (152 == mSERVER_INFO.mServerNumber) || (153 == mSERVER_INFO.mServerNumber)) 
	{
		return -1;
	}

	return ReturnAlliance(tTribe);
}
//RETURN_TRIBE_FOR_SYMBOL
int MyGame::ReturnTribeForSymbol(int tTribe)
{
	switch (tTribe)
	{
	case 0: return mWorldInfo.mTribe1Symbol;
	case 1: return mWorldInfo.mTribe2Symbol;
	case 2: return mWorldInfo.mTribe3Symbol;
	case 3: return mWorldInfo.mTribe4Symbol;
	}
	return -1;
}

//RETURN_TRIBE_POINT_WITH_ALLIANCE
int MyGame::ReturnTribePointWithAlliance(int tTribe)
{
	int tAllianceTribe;

	tAllianceTribe = ReturnAllianceTribe(tTribe);
	switch (tTribe)
	{
	case 0:
		if (tAllianceTribe == -1)
		{
			return mWorldInfo.mTribePoint[0];
		}
		else
		{
			return (mWorldInfo.mTribePoint[0] + mWorldInfo.mTribePoint[tAllianceTribe]);
		}
		break;
	case 1:
		if (tAllianceTribe == -1)
		{
			return mWorldInfo.mTribePoint[1];
		}
		else
		{
			return (mWorldInfo.mTribePoint[1] + mWorldInfo.mTribePoint[tAllianceTribe]);
		}
		break;
	case 2:
		if (tAllianceTribe == -1)
		{
			return mWorldInfo.mTribePoint[2];
		}
		else
		{
			return (mWorldInfo.mTribePoint[2] + mWorldInfo.mTribePoint[tAllianceTribe]);
		}
		break;
	case 3:
		if (tAllianceTribe == -1)
		{
			return mWorldInfo.mTribePoint[3];
		}
		else
		{
			return (mWorldInfo.mTribePoint[3] + mWorldInfo.mTribePoint[tAllianceTribe]);
		}
		break;
	}
	return 0;
}

//CHECK_SMALL_TRIBE_FOR_ADVANTAGE
BOOL MyGame::CheckSmallTribeForAdvantage(int tTribe)
{
	int index01;
	int tSmallTribePointTribe;

	tSmallTribePointTribe = -1;
	for (index01 = 0; index01 < 4; index01++)
	{
		if (ReturnTribePointWithAlliance(index01) < 10)
		{
			continue;
		}
		if (tSmallTribePointTribe == -1)
		{
			tSmallTribePointTribe = index01;
		}
		else
		{
			if (ReturnTribePointWithAlliance(index01) < ReturnTribePointWithAlliance(tSmallTribePointTribe))
			{
				tSmallTribePointTribe = index01;
			}
		}
	}
	if (tSmallTribePointTribe == tTribe)
	{
		return TRUE;
	}
	return FALSE;
}

#ifdef __GOD__
//RETURN_BIG_TRIBE
int MyGame::ReturnBigTribe(void)
{
	int index01;
	int tBigTribePointTribe;

	tBigTribePointTribe = 0;
	for (index01 = 1; index01 < 4; index01++)
	{
		if (mWorldInfo.mTribePoint[index01] > mWorldInfo.mTribePoint[tBigTribePointTribe])
		{
			tBigTribePointTribe = index01;
		}
	}
	return tBigTribePointTribe;
}
#endif
// @ Tribe Formation Skill @
//RETURN_SMALL_TRIBE
int MyGame::ReturnSmallTribe(void)
{
	int index01;
	int tSmallTribePointTribe;

	tSmallTribePointTribe = 0;
	for (index01 = 1; index01 < 4; index01++)
	{
		if (mWorldInfo.mTribePoint[index01] < mWorldInfo.mTribePoint[tSmallTribePointTribe])
		{
			tSmallTribePointTribe = index01;
		}
	}
	return tSmallTribePointTribe;
} // @

//LOGIC
void MyGame::Logic(float dTime)
{
	int index01;
	DWORD tGetTickCount;
	time_t PostCheckTime;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);

	mTickCount++;
	tGetTickCount = GetTickCount64();

	// Yaoguai Holy Stone Reset
	if ((bAttackMonsterSymbol == false) && (tGetTickCount - dwAttackMonsterSymbolTime >= 10800000))
	{
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(401, &tData[0]);
		bAttackMonsterSymbol = true;
	}

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mUSER[index01].mCheckConnectState)
		{
			continue;
		}
		if (mUSER[index01].mCheckValidState)
		{
			if ((tGetTickCount - mUSER[index01].mRegisterTime) >= 180000)
			{
				if (mUSER[index01].mMoveZoneResult == 0)
				{
					mUSER[index01].mAvatarInfo.aLogoutInfo[0] = mSERVER_INFO.mServerNumber;
					mUSER[index01].mAvatarInfo.aLogoutInfo[1] = (int)mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0];
					mUSER[index01].mAvatarInfo.aLogoutInfo[2] = (int)mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[1];
					mUSER[index01].mAvatarInfo.aLogoutInfo[3] = (int)mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[2];
					mUSER[index01].mAvatarInfo.aLogoutInfo[4] = mAVATAR_OBJECT[index01].mDATA.aLifeValue;
					mUSER[index01].mAvatarInfo.aLogoutInfo[5] = mAVATAR_OBJECT[index01].mDATA.aManaValue;
					mPLAYUSER_COM.U_REGISTER_USER_FOR_ZONE_2_SEND(mUSER[index01].mPlayUserIndex, &mUSER[index01].uID[0], &mUSER[index01].mAvatarInfo, mUSER[index01].mEffectValue, &mUSER[index01].mAuthInfo);
					if (mPLAYUSER_COM.mRecv_Result != 0)
					{
						mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
						continue;
					}
					mUSER[index01].mRegisterTime = tGetTickCount;
				}
			}
		}
		else
		{
			if ((tGetTickCount - mUSER[index01].mConnectTime) >= 300000)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
	}

	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		mAVATAR_OBJECT[index01].Update(dTime);
		if ((tGetTickCount - mAVATAR_OBJECT[index01].mUpdateTimeForBroadcast) < 5000)
		{
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
		{
			mAVATAR_OBJECT[index01].mUpdateTimeForBroadcast = tGetTickCount;
			continue;
		}
		if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 12)
		{
			mAVATAR_OBJECT[index01].mUpdateTimeForBroadcast = tGetTickCount;
			continue;
		}
		if (mAVATAR_OBJECT[index01].mCheckCount < 0) 
		{
			mAVATAR_OBJECT[index01].mCheckCount = 0;
		}
		mTRANSFER.B_AVATAR_ACTION_RECV2(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 2);
		mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, index01, true, 0);
	}

	for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		mMONSTER_OBJECT[index01].Update(index01, dTime);
		if ((tGetTickCount - mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast) < 5000)
		{
			continue;
		}
		if (mMONSTER_OBJECT[index01].mDATA.mAction.aSort == 12)
		{
			mMONSTER_OBJECT[index01].mUpdateTimeForBroadcast = tGetTickCount;
			continue;
		}
		mTRANSFER.B_MONSTER_ACTION_RECV(index01, mMONSTER_OBJECT[index01].mUniqueNumber, &mMONSTER_OBJECT[index01].mDATA, 2);
		switch (mMONSTER_OBJECT[index01].mSpecialSortNumber)
		{
		case 1:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS1, false, 0);
			break;
		case 2:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 3:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 4:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 5:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS2, false, 0);
			break;
		case 6:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		case 7:
			mUTIL.Broadcast(TRUE, &mMONSTER_OBJECT[index01].mDATA.mAction.aLocation[0], UNIT_SCALE_RADIUS3, false, 0);
			break;
		}
	}
	for (index01 = 0; index01 < MAX_ITEM_OBJECT_NUM; index01++)
	{
		if (!mITEM_OBJECT[index01].mCheckValidState)
		{
			continue;
		}
		mITEM_OBJECT[index01].Update(index01);
		if ((tGetTickCount - mITEM_OBJECT[index01].mUpdateTimeForBroadcast) < 5000)
		{
			continue;
		}
		mTRANSFER.B_ITEM_ACTION_RECV2(index01, mITEM_OBJECT[index01].mUniqueNumber, &mITEM_OBJECT[index01].mDATA, 2);
		mUTIL.Broadcast(TRUE, &mITEM_OBJECT[index01].mDATA.iLocation[0], UNIT_SCALE_RADIUS1, false, 0);
	}
	if ((tGetTickCount - mUpdateTimeForTribeBankInfo) >= 600000)
	{
		mUpdateTimeForTribeBankInfo = tGetTickCount;
		mPLAYUSER_COM.U_TRIBE_BANK_INFO_SAVE_SEND(&mTribeBankInfo[0]);
		mTribeBankInfo[0] = 0;
		mTribeBankInfo[1] = 0;
		mTribeBankInfo[2] = 0;
		mTribeBankInfo[3] = 0;
	}
	AdjustSymbolDamageInfo();
	ProcessForGuardState();

	if (mCheckTribeVoteServer)
	{
		Process_TribeVote_Server();
	}
	if (mCheckAllienceServer)
	{
		Process_Allience_Server();
	}
	if (mCheckZone037Server)
	{
		Process_Zone_037();
//		ProcesForTreasureHunterEvent();////Saigo Monsters////
	}
	else if (mCheckZone124Server)
	{
		Process_Zone_124();
	}
	else if (mCheckZone071TypeServer)
	{
		Process_Zone_071_TYPE();
	}
	else if (mCheckZone049TypeServer)
	{
		Process_Zone_049_TYPE();
	}
	else if (mCheckZone051TypeServer)
	{
		Process_Zone_051_TYPE();
	}
	else if (mCheckZone053TypeServer)
	{
		Process_Zone_053_TYPE();
	}
	else if (mCheckZone038Server)
	{
		Process_Zone_038();
		if ((mTickCount % 20) == 0)
		{
			mSUMMON.SummonMonster();
			mSUMMON.SummonGuard(FALSE, FALSE);
			mSUMMON.SummonGuard(TRUE, FALSE);
			ProcessforYanggokBoss();////Yanggok monsters///
		}
	}
	else if (mCheckZone039TypeServer)
	{
		Process_Zone_039_TYPE();
		if ((mTickCount % 20) == 0)
		{
			mSUMMON.SummonMonster();
			mSUMMON.SummonBossMonster();
			mSUMMON.SummonTribeSymbol();
		}
	}
	else if (mCheckZone88TypeServer)
	{
		Process_Zone_88();
	}
	else if (mCheckZone175TypeServer)
	{
		Process_Zone_175_TYPE();
	}
	else if (mCheckZone194Server)
	{
		Process_Zone_194();
	}
	else if (mCheckZone195TypeServer)
	{
		Process_Zone_195();
		if ((mTickCount % 20) == 0)
		{
			mSUMMON.SummonMonster();
		}
	}
	else if (mCheckZone200TypeServer)
	{
		Process_Zone_200();
	}
	else if (mCheckZone241TypeServer)
	{
		Process_Zone_241();
	}
	else if (mCheckZone267TypeServer)
	{
		Process_Zone_267();
	}
	else if (mCheckZone319TypeServer)
	{
		Process_Zone_319_TYPE();
	}
	else
	{
		if ((mTickCount % 20) == 0)
		{
			mSUMMON.SummonMonster();
			mSUMMON.SummonBossMonster();
			mSUMMON.SummonGuard(FALSE, FALSE);
			mSUMMON.SummonTribeSymbol();
		}
	}
	if ((mTickCount % 120) == 0) 
	{
		mPLAYUSER_COM.U_ZONE_OK_FOR_PLAYUSER_SEND();
		mCENTER_COM.U_ZONE_OK_FOR_CENTER_SEND();
		mRELAY_COM.U_ZONE_OK_FOR_RELAY_SEND();
		mEXTRA_COM.U_ZONE_OK_FOR_EXTRA_SEND();
	}
}

//ADJUST_SYMBOL_DAMAGE_INFO
void MyGame::AdjustSymbolDamageInfo(void)
{
	int tAllianceTribe;

	tAllianceTribe = ReturnAllianceTribe(0);
	mSymbolDamageUp[0] = 0.0f;
	if ((mWorldInfo.mTribe1Symbol == 0) || (mWorldInfo.mTribe1Symbol == tAllianceTribe))
	{
		if ((mWorldInfo.mTribe2Symbol == 0) || (mWorldInfo.mTribe2Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[0] += 0.1f;
			mSymbolDamageUp[0] = 500;
		}
		if ((mWorldInfo.mTribe3Symbol == 0) || (mWorldInfo.mTribe3Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[0] += 0.1f;
			mSymbolDamageUp[0] += 500;
		}
		if ((mWorldInfo.mTribe4Symbol == 0) || (mWorldInfo.mTribe4Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[0] += 0.1f;
			mSymbolDamageUp[0] += 500;
		}
		if (mWorldInfo.mMonsterSymbol == 0)
		{
			//mSymbolDamageUp[0] += 0.1f;
			mSymbolDamageUp[0] += 500;
		}
		else
		{
			if (tAllianceTribe != -1)
			{
				if (mWorldInfo.mMonsterSymbol == tAllianceTribe)
				{
					//mSymbolDamageUp[0] += 0.1f;
					mSymbolDamageUp[0] += 500;
				}
			}
		}
		if (mSymbolDamageUp[0] == 0.0f)
		{
			if (CheckSmallTribeForAdvantage(0))
			{
				//mSymbolDamageUp[0] += 0.1f;
				mSymbolDamageUp[0] = 500;
			}
		}
	}
	mSymbolDamageDown[0] = 0.0f;
	if ((mWorldInfo.mTribe1Symbol != 0) && (mWorldInfo.mTribe1Symbol != tAllianceTribe))
	{
		//mSymbolDamageDown[0] += 0.1f;
		mSymbolDamageDown[0] += 0.2f;
	}
	tAllianceTribe = ReturnAllianceTribe(1);
	mSymbolDamageUp[1] = 0.0f;
	if ((mWorldInfo.mTribe2Symbol == 1) || (mWorldInfo.mTribe2Symbol == tAllianceTribe))
	{
		if ((mWorldInfo.mTribe1Symbol == 1) || (mWorldInfo.mTribe1Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[1] += 0.1f;
			mSymbolDamageUp[1] = 500;
		}
		if ((mWorldInfo.mTribe3Symbol == 1) || (mWorldInfo.mTribe3Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[1] += 0.1f;
			mSymbolDamageUp[1] += 500;
		}
		if ((mWorldInfo.mTribe4Symbol == 1) || (mWorldInfo.mTribe4Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[1] += 0.1f;
			mSymbolDamageUp[1] += 500;
		}
		if (mWorldInfo.mMonsterSymbol == 1)
		{
			//mSymbolDamageUp[1] += 0.1f;
			mSymbolDamageUp[1] += 500;
		}
		else
		{
			if (tAllianceTribe != -1)
			{
				if (mWorldInfo.mMonsterSymbol == tAllianceTribe)
				{
					//mSymbolDamageUp[1] += 0.1f;
					mSymbolDamageUp[1] += 500;
				}
			}
		}
		if (mSymbolDamageUp[1] == 0.0f)
		{
			if (CheckSmallTribeForAdvantage(1))
			{
				//mSymbolDamageUp[1] += 0.1f;
				mSymbolDamageUp[1] = 500;
			}
		}
	}
	mSymbolDamageDown[1] = 0.0f;
	if ((mWorldInfo.mTribe2Symbol != 1) && (mWorldInfo.mTribe2Symbol != tAllianceTribe))
	{
		//mSymbolDamageDown[1] += 0.1f;
		mSymbolDamageDown[1] += 0.2f;
	}
	tAllianceTribe = ReturnAllianceTribe(2);
	mSymbolDamageUp[2] = 0.0f;
	if ((mWorldInfo.mTribe3Symbol == 2) || (mWorldInfo.mTribe3Symbol == tAllianceTribe))
	{
		if ((mWorldInfo.mTribe1Symbol == 2) || (mWorldInfo.mTribe1Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[2] += 0.1f;
			mSymbolDamageUp[2] = 500;
		}
		if ((mWorldInfo.mTribe2Symbol == 2) || (mWorldInfo.mTribe2Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[2] += 0.1f;
			mSymbolDamageUp[2] += 500;
		}
		if ((mWorldInfo.mTribe4Symbol == 2) || (mWorldInfo.mTribe4Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[2] += 0.1f;
			mSymbolDamageUp[2] += 500;
		}
		if (mWorldInfo.mMonsterSymbol == 2)
		{
			//mSymbolDamageUp[2] += 0.1f;
			mSymbolDamageUp[2] += 500;
		}
		else
		{
			if (tAllianceTribe != -1)
			{
				if (mWorldInfo.mMonsterSymbol == tAllianceTribe)
				{
					//mSymbolDamageUp[2] += 0.1f;
					mSymbolDamageUp[2] += 500;
				}
			}
		}
		if (mSymbolDamageUp[2] == 0.0f)
		{
			if (CheckSmallTribeForAdvantage(2))
			{
				//mSymbolDamageUp[2] += 0.1f;
				mSymbolDamageUp[2] = 500;
			}
		}
	}
	mSymbolDamageDown[2] = 0.0f;
	if ((mWorldInfo.mTribe3Symbol != 2) && (mWorldInfo.mTribe3Symbol != tAllianceTribe))
	{
		//mSymbolDamageDown[2] += 0.1f;
		mSymbolDamageDown[2] += 0.2f;
	}
	tAllianceTribe = ReturnAllianceTribe(3);
	mSymbolDamageUp[3] = 0.0f;
	if ((mWorldInfo.mTribe4Symbol == 3) || (mWorldInfo.mTribe4Symbol == tAllianceTribe))
	{
		if ((mWorldInfo.mTribe1Symbol == 3) || (mWorldInfo.mTribe1Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[3] += 0.1f;
			mSymbolDamageUp[3] = 500;
		}
		if ((mWorldInfo.mTribe2Symbol == 3) || (mWorldInfo.mTribe2Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[3] += 0.1f;
			mSymbolDamageUp[3] += 500;
		}
		if ((mWorldInfo.mTribe3Symbol == 3) || (mWorldInfo.mTribe3Symbol == tAllianceTribe))
		{
			//mSymbolDamageUp[3] += 0.1f;
			mSymbolDamageUp[3] += 500;
		}
		if (mWorldInfo.mMonsterSymbol == 3)
		{
			//mSymbolDamageUp[3] += 0.1f;
			mSymbolDamageUp[3] += 500;
		}
		else
		{
			if (tAllianceTribe != -1)
			{
				if (mWorldInfo.mMonsterSymbol == tAllianceTribe)
				{
					//mSymbolDamageUp[3] += 0.1f;
					mSymbolDamageUp[3] += 500;
				}
			}
		}
		if (mSymbolDamageUp[3] == 0.0f)
		{
			if (CheckSmallTribeForAdvantage(3))
			{
				//mSymbolDamageUp[3] += 0.1f;
				mSymbolDamageUp[3] = 500;
			}
		}
	}
	mSymbolDamageDown[3] = 0.0f;
	if ((mWorldInfo.mTribe4Symbol != 3) && (mWorldInfo.mTribe4Symbol != tAllianceTribe))
	{
		//mSymbolDamageDown[3] += 0.1f;
		mSymbolDamageDown[3] += 0.2f;
	}
}
//RETURN_SYMBOL_DAMAGE_UP
float MyGame::ReturnSymbolDamageUp(int tTribe)
{
	switch (tTribe)
	{
	case 0: return mSymbolDamageUp[0];
	case 1: return mSymbolDamageUp[1];
	case 2: return mSymbolDamageUp[2];
	case 3: return mSymbolDamageUp[3];
	}
	return 0.0f;
}
//RETURN_SYMBOL_DAMAGE_DOWN
float MyGame::ReturnSymbolDamageDown(int tTribe)
{
	switch (tTribe)
	{
	case 0: return mSymbolDamageDown[0];
	case 1: return mSymbolDamageDown[1];
	case 2: return mSymbolDamageDown[2];
	case 3: return mSymbolDamageDown[3];
	}
	return 0.0f;
}
//PROCESS_FOR_GUARD_STATE
void MyGame::ProcessForGuardState(void)
{
	int index01;
	int index02;
	int index03;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	const int tGuardTribePostNum = 5;
	BOOL tExamineGuardState[4];
	int tExamineGuardIndex[4];
	BOOL tResultGuardState[4];

	tExamineGuardState[0] = FALSE;
	tExamineGuardState[1] = FALSE;
	tExamineGuardState[2] = FALSE;
	tExamineGuardState[3] = FALSE;
	switch (mSERVER_INFO.mServerNumber)
	{
	case  38:
		tExamineGuardState[0] = TRUE;
		tExamineGuardIndex[0] = 0;
		tResultGuardState[0] = FALSE;
		tExamineGuardState[1] = TRUE;
		tExamineGuardIndex[1] = 0;
		tResultGuardState[1] = FALSE;
		tExamineGuardState[2] = TRUE;
		tExamineGuardIndex[2] = 0;
		tResultGuardState[2] = FALSE;
		tExamineGuardState[3] = TRUE;
		tExamineGuardIndex[3] = 0;
		tResultGuardState[3] = FALSE;
		break;
	case   4:
		tExamineGuardState[0] = TRUE;
		tExamineGuardIndex[0] = 1;
		tResultGuardState[0] = FALSE;
		break;
	case   3:
		tExamineGuardState[0] = TRUE;
		tExamineGuardIndex[0] = 2;
		tResultGuardState[0] = FALSE;
		break;
	case   2:
		tExamineGuardState[0] = TRUE;
		tExamineGuardIndex[0] = 3;
		tResultGuardState[0] = FALSE;
		break;
	case   9:
		tExamineGuardState[1] = TRUE;
		tExamineGuardIndex[1] = 1;
		tResultGuardState[1] = FALSE;
		break;
	case   8:
		tExamineGuardState[1] = TRUE;
		tExamineGuardIndex[1] = 2;
		tResultGuardState[1] = FALSE;
		break;
	case   7:
		tExamineGuardState[1] = TRUE;
		tExamineGuardIndex[1] = 3;
		tResultGuardState[1] = FALSE;
		break;
	case  14:
		tExamineGuardState[2] = TRUE;
		tExamineGuardIndex[2] = 1;
		tResultGuardState[2] = FALSE;
		break;
	case  13:
		tExamineGuardState[2] = TRUE;
		tExamineGuardIndex[2] = 2;
		tResultGuardState[2] = FALSE;
		break;
	case  12:
		tExamineGuardState[2] = TRUE;
		tExamineGuardIndex[2] = 3;
		tResultGuardState[2] = FALSE;
		break;
	case 143:
		tExamineGuardState[3] = TRUE;
		tExamineGuardIndex[3] = 1;
		tResultGuardState[3] = FALSE;
		break;
	case 142:
		tExamineGuardState[3] = TRUE;
		tExamineGuardIndex[3] = 2;
		tResultGuardState[3] = FALSE;
		break;
	case 141:
		tExamineGuardState[3] = TRUE;
		tExamineGuardIndex[3] = 3;
		tResultGuardState[3] = FALSE;
		break;
	default:
		return;
	}
	index03 = MAX_MONSTER_OBJECT_BASE_1_NUM;
	for (index01 = 0; index01 < 4; index01++)
	{
		if (!tExamineGuardState[index01])
		{
			index03 += tGuardTribePostNum;
			continue;
		}
		for (index02 = 0; index02 < tGuardTribePostNum; index02++)
		{
			if (mMONSTER_OBJECT[index03].mCheckValidState)
			{
				tResultGuardState[index01] = TRUE;
			}
			index03++;
		}
		if (!tResultGuardState[index01])
		{
			if (mWorldInfo.mTribeGuardState[index01][tExamineGuardIndex[index01]] == 1)
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 31;
				CopyMemory(&tBroadcastInfoData[0], &index01, 4);
				CopyMemory(&tBroadcastInfoData[4], &tExamineGuardIndex[index01], 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mWorldInfo.mTribeGuardState[index01][tExamineGuardIndex[index01]] = 0;
			}
		}
		else
		{
			if (mWorldInfo.mTribeGuardState[index01][tExamineGuardIndex[index01]] == 0)
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 32;
				CopyMemory(&tBroadcastInfoData[0], &index01, 4);
				CopyMemory(&tBroadcastInfoData[4], &tExamineGuardIndex[index01], 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mWorldInfo.mTribeGuardState[index01][tExamineGuardIndex[index01]] = 1;
			}
		}
	}
}


//RETURN_TRIBE_ROLE
int MyGame::ReturnTribeRole(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe)
{
	int index01;

	if (strcmp(tAvatarName, mTribeInfo.mTribeMaster[tTribe]) == 0)
	{
		return 1;
	}
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		if (strcmp(tAvatarName, mTribeInfo.mTribeSubMaster[tTribe][index01]) == 0)
		{
			return 2;
		}
	}
	return 0;
}
//RETURN_TRIBE_SUB_MASTER_NUM
int MyGame::ReturnTribeSubMasterNum(int tTribe)
{
	int index01;
	int index02;

	index02 = 0;
	for (index01 = 0; index01 < MAX_TRIBE_SUBMASTER_NUM; index01++)
	{
		if (strcmp(mTribeInfo.mTribeSubMaster[tTribe][index01], "") != 0)
		{
			index02++;
		}
	}
	return index02;
}

//CHECK_POSSIBLE_CHANGE_TO_TRIBE_4
int MyGame::CheckPossibleChangeToTribe4(int tTribe)
{
	int index01;
	int tBigTribe;
	int tSmallTribe;

	tBigTribe = 0;
	for (index01 = 1; index01 < 4; index01++)
	{
		if (ReturnTribePointWithAlliance(index01) >= ReturnTribePointWithAlliance(tBigTribe))
		{
			tBigTribe = index01;
		}
	}
	if (tBigTribe == 3)
	{
		return 1;
	}
	tSmallTribe = 0;
	for (index01 = 1; index01 < 4; index01++)
	{
		if (ReturnTribePointWithAlliance(index01) <= ReturnTribePointWithAlliance(tSmallTribe))
		{
			tSmallTribe = index01;
		}
	}
	if (tTribe == tSmallTribe)
	{
		return 2;
	}
	return 0;
}
//CHECK_POSSIBLE_CHANGE_TO_TRIBE_4_2
int MyGame::CheckPossibleChangeToTribe4_2(int tTribe)
{
	int index01;
	int tBigTribe;

	tBigTribe = 0;
	for (index01 = 1; index01 < 4; index01++)
	{
		if (mWorldInfo.mTribePoint[index01] >= mWorldInfo.mTribePoint[tBigTribe])
		{
			tBigTribe = index01;
		}
	}
	if (tBigTribe == 3)
	{
		return 1;
	}
	if (tTribe != tBigTribe) 
	{
		return 2;
	}
	return 0;
}
//PROCESS_ALLIENCE_SERVER
void MyGame::Process_Allience_Server(void)
{
	int index01;
	int index02;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	BOOL tCheckBigTribePoint[2];
	int tBigTribePointTribe;
	int tAllianceIndex;
	int tPossibleAllianceDate01;
	int tPossibleAllianceDate02;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}

	mAlliencePostTick++;
	switch (mAllienceBattleState)
	{
	case 0:
		mAlliencePostAvatarIndex[0] = -1;
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
			if (ReturnTribeRole(&mUSER[index01].mAvatarInfo.aName[0], mUSER[index01].mAvatarInfo.aTribe) != 1)
			{
				continue;
			}
			if (mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[0][0], mAllienceBattlePostRadius[0]))
			{
				mAlliencePostAvatarIndex[0] = index01;
				mAlliencePostAvatarUniqueNumber[0] = mAVATAR_OBJECT[index01].mUniqueNumber;
				mAlliencePostAvatarTribe[0] = mAVATAR_OBJECT[index01].mDATA.aTribe;
				tCheckBigTribePoint[0] = FALSE;
				tBigTribePointTribe = 0;
				for (index02 = 1; index02 < 4; index02++)
				{
					if (ReturnTribePointWithAlliance(index02) > ReturnTribePointWithAlliance(tBigTribePointTribe))
					{
						tBigTribePointTribe = index02;
					}
				}
				if (tBigTribePointTribe == mAlliencePostAvatarTribe[0])
				{
					tCheckBigTribePoint[0] = TRUE;
				}
				break;
			}
		}
		mAlliencePostAvatarIndex[1] = -1;
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
			if (ReturnTribeRole(&mUSER[index01].mAvatarInfo.aName[0], mUSER[index01].mAvatarInfo.aTribe) != 1)
			{
				continue;
			}
			if (mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[1][0], mAllienceBattlePostRadius[1]))
			{
				mAlliencePostAvatarIndex[1] = index01;
				mAlliencePostAvatarUniqueNumber[1] = mAVATAR_OBJECT[index01].mUniqueNumber;
				mAlliencePostAvatarTribe[1] = mAVATAR_OBJECT[index01].mDATA.aTribe;
				tCheckBigTribePoint[1] = FALSE;
				tBigTribePointTribe = 0;
				for (index02 = 1; index02 < 4; index02++)
				{
					if (ReturnTribePointWithAlliance(index02) > ReturnTribePointWithAlliance(tBigTribePointTribe))
					{
						tBigTribePointTribe = index02;
					}
				}
				if (tBigTribePointTribe == mAlliencePostAvatarTribe[1])
				{
					tCheckBigTribePoint[1] = TRUE;
				}
				break;
			}
		}
		if ((mAlliencePostAvatarIndex[0] == -1) || (mAlliencePostAvatarIndex[1] == -1))
		{
			return;
		}
		if (mAlliencePostAvatarTribe[0] != ReturnAllianceTribe(mAlliencePostAvatarTribe[1]))
		{
			if (
				(mWorldInfo.mAllianceState[0][0] == mAlliencePostAvatarTribe[0]) ||
				(mWorldInfo.mAllianceState[0][1] == mAlliencePostAvatarTribe[0]) ||
				(mWorldInfo.mAllianceState[1][0] == mAlliencePostAvatarTribe[0]) ||
				(mWorldInfo.mAllianceState[1][1] == mAlliencePostAvatarTribe[0]) ||
				(mWorldInfo.mAllianceState[0][0] == mAlliencePostAvatarTribe[1]) ||
				(mWorldInfo.mAllianceState[0][1] == mAlliencePostAvatarTribe[1]) ||
				(mWorldInfo.mAllianceState[1][0] == mAlliencePostAvatarTribe[1]) ||
				(mWorldInfo.mAllianceState[1][1] == mAlliencePostAvatarTribe[1]) ||
				(ReturnTribePointWithAlliance(mAlliencePostAvatarTribe[0]) < 100) ||
				(ReturnTribePointWithAlliance(mAlliencePostAvatarTribe[1]) < 100) ||
				(tCheckBigTribePoint[0]) ||
				(tCheckBigTribePoint[1]) ||
				((mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][1] == 1) && (mUTIL.ReturnNowDate() <= mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][0])) ||
				((mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][1] == 1) && (mUTIL.ReturnNowDate() <= mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][0]))
				)
			{
				mTRANSFER.B_TRIBE_ALLIANCE_INFO(1, 0);
				mUSER[mAlliencePostAvatarIndex[0]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mTRANSFER.B_TRIBE_ALLIANCE_INFO(1, 0);
				mUSER[mAlliencePostAvatarIndex[1]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mAlliencePostTick = 0;
				mAllienceBattleState = 1;
				return;
			}
			else
			{
				mAlliencePostTick = 0;
				mAllienceBattleState = 2;
				mAllienceRemainTime = 60;
				return;
			}
		}
		else
		{
			mAlliencePostTick = 0;
			mAllienceBattleState = 3;
			mAllienceRemainTime = 60;
			return;
		}
		return;
	case 1:
		if (mAlliencePostTick < (120 * 1))
		{
			return;
		}
		mAlliencePostTick = 0;
		mAllienceBattleState = 0;
		return;
	case 2:
		if ((mAlliencePostTick % 2) != 0)
		{
			return;
		}
		if (
			(!mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mCheckValidState) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mUniqueNumber != mAlliencePostAvatarUniqueNumber[0]) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aLifeValue < 1) ||
			(!mUTIL.CheckInRange(&mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[0][0], mAllienceBattlePostRadius[0])) ||
			(mUSER[mAlliencePostAvatarIndex[0]].mMoveZoneResult == 1) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aVisibleState == 0) ||
			(!mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mCheckValidState) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mUniqueNumber != mAlliencePostAvatarUniqueNumber[1]) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aLifeValue < 1) ||
			(!mUTIL.CheckInRange(&mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[1][0], mAllienceBattlePostRadius[1])) ||
			(mUSER[mAlliencePostAvatarIndex[1]].mMoveZoneResult == 1) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aVisibleState == 0)
			)
		{
			mTRANSFER.B_TRIBE_ALLIANCE_INFO(3, 0);
			mUSER[mAlliencePostAvatarIndex[0]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_TRIBE_ALLIANCE_INFO(3, 0);
			mUSER[mAlliencePostAvatarIndex[1]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAlliencePostTick = 0;
			mAllienceBattleState = 0;
			return;
		}
		mTRANSFER.B_TRIBE_ALLIANCE_INFO(2, mAllienceRemainTime);
		mUSER[mAlliencePostAvatarIndex[0]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRIBE_ALLIANCE_INFO(2, mAllienceRemainTime);
		mUSER[mAlliencePostAvatarIndex[1]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAllienceRemainTime--;
		if (mAllienceRemainTime > 0)
		{
			return;
		}
		if ((mWorldInfo.mAllianceState[0][0] == -1) && (mWorldInfo.mAllianceState[0][1] == -1))
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 46;
		CopyMemory(&tBroadcastInfoData[0], &mAlliencePostAvatarTribe[0], 4);
		CopyMemory(&tBroadcastInfoData[4], &mAlliencePostAvatarTribe[1], 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][0] = 0;
		mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][1] = 0;
		mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][0] = 0;
		mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][1] = 0;
		mWorldInfo.mAllianceState[tAllianceIndex][0] = mAlliencePostAvatarTribe[0];
		mWorldInfo.mAllianceState[tAllianceIndex][1] = mAlliencePostAvatarTribe[1];
		mAlliencePostTick = 0;
		mAllienceBattleState = 4;
		return;
	case 3:
		if ((mAlliencePostTick % 2) != 0)
		{
			return;
		}
		if (
			(!mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mCheckValidState) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mUniqueNumber != mAlliencePostAvatarUniqueNumber[0]) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aLifeValue < 1) ||
			(!mUTIL.CheckInRange(&mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[0][0], mAllienceBattlePostRadius[0])) ||
			(mUSER[mAlliencePostAvatarIndex[0]].mMoveZoneResult == 1) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[0]].mDATA.aVisibleState == 0) ||
			(!mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mCheckValidState) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mUniqueNumber != mAlliencePostAvatarUniqueNumber[1]) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aLifeValue < 1) ||
			(!mUTIL.CheckInRange(&mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aAction.aLocation[0], &mAllienceBattlePostLocation[1][0], mAllienceBattlePostRadius[1])) ||
			(mUSER[mAlliencePostAvatarIndex[1]].mMoveZoneResult == 1) ||
			(mAVATAR_OBJECT[mAlliencePostAvatarIndex[1]].mDATA.aVisibleState == 0)
			)
		{
			mTRANSFER.B_TRIBE_ALLIANCE_INFO(5, 0);
			mUSER[mAlliencePostAvatarIndex[0]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mTRANSFER.B_TRIBE_ALLIANCE_INFO(5, 0);
			mUSER[mAlliencePostAvatarIndex[1]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mAlliencePostTick = 0;
			mAllienceBattleState = 0;
			return;
		}
		mTRANSFER.B_TRIBE_ALLIANCE_INFO(4, mAllienceRemainTime);
		mUSER[mAlliencePostAvatarIndex[0]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mTRANSFER.B_TRIBE_ALLIANCE_INFO(4, mAllienceRemainTime);
		mUSER[mAlliencePostAvatarIndex[1]].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		mAllienceRemainTime--;
		if (mAllienceRemainTime > 0)
		{
			return;
		}
		if (((mWorldInfo.mAllianceState[0][0] == mAlliencePostAvatarTribe[0]) && (mWorldInfo.mAllianceState[0][1] == mAlliencePostAvatarTribe[1])) || ((mWorldInfo.mAllianceState[0][1] == mAlliencePostAvatarTribe[0]) && (mWorldInfo.mAllianceState[0][0] == mAlliencePostAvatarTribe[1])))
		{
			tAllianceIndex = 0;
		}
		else
		{
			tAllianceIndex = 1;
		}
		tPossibleAllianceDate01 = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 14);
		tPossibleAllianceDate02 = mUTIL.ReturnAddDate(mUTIL.ReturnNowDate(), 14);
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 47;
		CopyMemory(&tBroadcastInfoData[0], &mAlliencePostAvatarTribe[0], 4);
		CopyMemory(&tBroadcastInfoData[4], &mAlliencePostAvatarTribe[1], 4);
		CopyMemory(&tBroadcastInfoData[8], &tPossibleAllianceDate01, 4);
		CopyMemory(&tBroadcastInfoData[12], &tPossibleAllianceDate02, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mGAME.mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][0] = tPossibleAllianceDate01;
		mGAME.mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[0]][1] = 1;
		mGAME.mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][0] = tPossibleAllianceDate02;
		mGAME.mWorldInfo.mPossibleAllianceInfo[mAlliencePostAvatarTribe[1]][1] = 1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][0] = -1;
		mGAME.mWorldInfo.mAllianceState[tAllianceIndex][1] = -1;
		mAlliencePostTick = 0;
		mAllienceBattleState = 4;
		return;
	case 4:
		if (mAlliencePostTick < (120 * 60))
		{
			return;
		}
		mAlliencePostTick = 0;
		mAllienceBattleState = 0;
		return;
	}
}
//PROCESS_ZONE_037
void MyGame::Process_Zone_037(void)//HSB Event
{
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone037PostTick++;
	switch (mWorldInfo.mTribeSymbolBattle)
	{
	case 0:
		switch (mZone037BattleState)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}

			// Luni (1), Marți (2), Miercuri (3), Joi (4), Vineri (5), Sâmbătă (6), Duminică (0) — exclus Miercuri (3)
			if (
				((tPresentTime->tm_wday != 0) && // Duminică
					(tPresentTime->tm_wday != 1) && // Luni
					(tPresentTime->tm_wday != 2) && // Marți
//					(tPresentTime->tm_wday != 3) && // Miercuri
					(tPresentTime->tm_wday != 4) && // Joi
					(tPresentTime->tm_wday != 5) && // Vineri
					(tPresentTime->tm_wday != 6))   // Sâmbătă
				|| (tPresentTime->tm_hour != 16)//Ora Inceput Countdown
				|| (tPresentTime->tm_min > 55))//Minut Inceput Countdown
			{
				return;
			}


			mZone037PostTick = 0;
			mZone037BattleState = 1;
			mZone037RemainTime = 10;
			return;
		case 1:
			if ((mZone037PostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 39;
			CopyMemory(&tBroadcastInfoData[0], &mZone037RemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone037RemainTime--;
			if (mZone037RemainTime == 0)
			{
				mZone037PostTick = 0;
				mZone037BattleState = 2;
			}
			return;
		case 2:
			if (mZone037PostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 40;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mTribeSymbolBattle = 1;
			mZone037PostTick = 0;
			mZone037BattleState = 0;
			mSUMMON.SummonGuard(FALSE, TRUE);
			return;
		}
		return;
	case 1:
		switch (mZone037BattleState)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}
			// Luni (1), Marți (2), Miercuri (3), Joi (4), Vineri (5), Sâmbătă (6), Duminică (0) — exclus Miercuri (3)
			if (
				((tPresentTime->tm_wday != 0) && // Duminică
					(tPresentTime->tm_wday != 1) && // Luni
					(tPresentTime->tm_wday != 2) && // Marți
					//					(tPresentTime->tm_wday != 3) && // Miercuri
					(tPresentTime->tm_wday != 4) && // Joi
					(tPresentTime->tm_wday != 5) && // Vineri
					(tPresentTime->tm_wday != 6))   // Sâmbătă
				|| (tPresentTime->tm_hour != 18)//Ora Inceput Countdown de Sfarsit//trebuie 2 ore diferenta
				|| (tPresentTime->tm_min > 55))//Minut Inceput Countdown de Sfarsit//diferenta e cat vrei sa tina evenimentul
			{
				return;
			}


			mZone037PostTick = 0;
			mZone037BattleState = 1;
			mZone037RemainTime = 10;
			return;
		case 1:
			if ((mZone037PostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 44;
			CopyMemory(&tBroadcastInfoData[0], &mZone037RemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone037RemainTime--;
			if (mZone037RemainTime == 0)
			{
				mZone037PostTick = 0;
				mZone037BattleState = 2;
			}
			return;
		case 2:
			if (mZone037PostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 45;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mTribeSymbolBattle = 0;
			// @ Tribe Formation Skill @
			mWorldInfo.mTribeMasterCallAbility[0] = 0;
			mWorldInfo.mTribeMasterCallAbility[1] = 0;
			mWorldInfo.mTribeMasterCallAbility[2] = 0;
			mWorldInfo.mTribeMasterCallAbility[3] = 0;
			// @
			mZone037PostTick = 0;
			mZone037BattleState = 0;
			return;
		}
		return;
	}
}
//PROCESS_ZONE_88
void MyGame::Process_Zone_88(void)
{
	int index01;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeWinner = -1;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone88PostTick++;
	switch (mZone88BattleState1)
	{
	case 0:
		switch (mZone88BattleState2)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}

			if ((tPresentTime->tm_hour != 18) || (tPresentTime->tm_min > 10))
			{
				return;
			}
			mZone88PostTick = 0;
			mZone88BattleState2 = 1;
			mZone88RemainTime1 = 10;
			CopyMemory(&tBroadcastInfoData[0], &mZone88RemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(620, &tBroadcastInfoData[0]);
			return;

		case 1:
			if ((mZone88PostTick % (120 * 1)) != 0)
			{
				return;
			}
			mZone88RemainTime1--;
			if (mZone88RemainTime1 == 0)
			{
				mZone88PostTick = 0;
				mZone88BattleState2 = 2;
				mZone88RemainTime1 = 2;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(621, &tBroadcastInfoData[0]);
				return;
			}
			CopyMemory(&tBroadcastInfoData[0], &mZone88RemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(620, &tBroadcastInfoData[0]);
			return;

		case 2:
			if ((mZone88PostTick % (120 * 1)) != 0)
			{
				return;
			}
			mZone88RemainTime1--;
			if (mZone88RemainTime1 == 0)
			{
				mZone88PostTick = 0;
				mZone88BattleState1 = 1;
				mZone88BattleState2 = 0;
				mZone88RemainTime1 = 0;
				mWorldInfo.mValleyOfTearsState = 1;
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(622, &tBroadcastInfoData[0]);
				for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
				{
					if (!mAVATAR_OBJECT[index01].mCheckValidState)
					{
						continue;
					}
					mTRANSFER.B_ZONE_88_INFO_RECV(2, mUSER[index01].mAvatarInfo.aTribe);
					mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
				return;
			}
			CopyMemory(&tBroadcastInfoData[0], &mZone88RemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(625, &tBroadcastInfoData[0]);
			return;
		}
		return;


	case 1:
		if (mZone88PostAvatarIndex == -1)
		{
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
				if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
				{
					continue;
				}
				if (!mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mZone88BattlePostLocation[0], mZone88BattlePostRadius))
				{
					continue;
				}
				break;
			}
			if (index01 == mSERVER.mMAX_USER_NUM)
			{
				tTribeWinner = -1;
				CopyMemory(&tBroadcastInfoData[0], &tTribeWinner, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(624, &tBroadcastInfoData[0]);
				mZone88PostTick = 0;
				mZone88BattleState1 = 2;
				return;
			}
			mZone88PostTick = 0;
			mZone88RemainTime1 = 5;
			mZone88PostAvatarIndex = index01;
			mZone88PostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}
				mTRANSFER.B_ZONE_88_INFO2_RECV(1, mUSER[mZone88PostAvatarIndex].mAvatarInfo.aName, mUSER[mZone88PostAvatarIndex].mAvatarInfo.aTribe);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			return;
		}
		if ((!mAVATAR_OBJECT[mZone88PostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone88PostAvatarIndex].mUniqueNumber != mZone88PostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone88PostAvatarIndex].mDATA.aLifeValue < 1) || (!mUTIL.CheckInRange(&mAVATAR_OBJECT[mZone88PostAvatarIndex].mDATA.aAction.aLocation[0], &mZone88BattlePostLocation[0], mZone88BattlePostRadius)) || (mUSER[mZone88PostAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[mZone88PostAvatarIndex].mDATA.aVisibleState == 0) || (mAVATAR_OBJECT[mZone88PostAvatarIndex].mDATA.aAction.aSort == 33))
		{
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}
				mTRANSFER.B_ZONE_88_INFO2_RECV(2, mUSER[mZone88PostAvatarIndex].mAvatarInfo.aName, mUSER[mZone88PostAvatarIndex].mAvatarInfo.aTribe);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			mZone88PostAvatarIndex = -1;
			mZone88PostAvatarUniqueNumber = 0;
			return;
		}
		if ((mZone88PostTick % 120) != 20)
		{
			return;
		}
		if (mZone88RemainTime1 > 0)
		{
			mZone88RemainTime1--;
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
			{
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}
				mTRANSFER.B_ZONE_88_INFO_RECV(5, mZone88RemainTime1);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			return;
		}
		tTribeWinner = mUSER[mZone88PostAvatarIndex].mAvatarInfo.aTribe;
		CopyMemory(&tBroadcastInfoData[0], &mUSER[mZone88PostAvatarIndex].mAvatarInfo.aTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(624, &tBroadcastInfoData[0]);
		// Battle Win Reward
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mUSER[index01].mAvatarInfo.aTribe != tTribeWinner)
			{
				continue;
			}
			mUTIL.ProcessForDropItem(3, 1103, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], mUSER[index01].mAvatarInfo.aName, "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		}
		mZone88PostTick = 0;
		mZone88BattleState1 = 2;
		return;

	case 2:
		if ((mZone88PostTick % (120 * 1)) != 0)
		{
			return;
		}
		mWorldInfo.mValleyOfTearsState = tTribeWinner;
		mZone88PostTick = 0;
		mZone88BattleState1 = 0;
		mZone88BattleState2 = 0;
		mZone88PostAvatarIndex = -1;
		mZone88PostAvatarUniqueNumber = 0;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(626, &tBroadcastInfoData[0]);
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (mAVATAR_OBJECT[index01].mCheckValidState)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
		return;
	}
}
//PROCESS_ZONE_124
// Funcția care gestionează logica evenimentului PvP din zona 124
void MyGame::Process_Zone_124(void)
{
	int index01 = 0;

	// Dacă evenimentul nu este activ, ieșim imediat din funcție
	if (!mDuel_124)
		return;

	// Dacă mai există timp rămas din eveniment
	if (0 < mDuel_124_RemainTime)
	{
		// Verificăm dacă ambele echipe au cel puțin 1 jucător
		if (mDuel_124_AvatarNum[0] < 1 || mDuel_124_AvatarNum[1] < 1)
		{
			// Parcurgem toți jucătorii din server
			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01)
			{
				// Dacă jucătorul nu este valid, îl sărim
				if (!mAVATAR_OBJECT[index01].mCheckValidState)
				{
					continue;
				}

				// Dacă jucătorul se află în proces de mutare între zone, îl sărim
				if (mUSER[index01].mMoveZoneResult == 1)
				{
					continue;
				}

				// Dacă echipa 0 nu are jucători, trimite semnal de încheiere pentru echipa 2 câștigătoare
				if (mDuel_124_AvatarNum[0] < 1)
				{
					mTRANSFER.B_DUEL_END_RECV(2);
				}
				// Dacă echipa 1 nu are jucători, echipa 1 pierde, echipa 0 câștigă
				else if (mDuel_124_AvatarNum[1] < 1)
				{
					mTRANSFER.B_DUEL_END_RECV(1);
				}

				// Trimite rezultatul duelului către jucător
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

				// Dacă jucătorul nu este în stare de duel activ, îl sărim
				if (mAVATAR_OBJECT[index01].mDuelProcessState != 4)
				{
					continue;
				}

				// Resetăm starea de duel a jucătorului
				mAVATAR_OBJECT[index01].mDATA.aDuelState[0] = 0;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[1] = 0;
				mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 0;
				mAVATAR_OBJECT[index01].mCheckPossibleEatPotion = TRUE;
				mAVATAR_OBJECT[index01].mDuelProcessState = 0;
				mAVATAR_OBJECT[index01].mDuelProcessRemainTime = 0;

				// Trimite actualizarea stării avatarului către ceilalți
				mTRANSFER.B_AVATAR_CHANGE_INFO_1(index01, mAVATAR_OBJECT[index01].mUniqueNumber, 7,
					mAVATAR_OBJECT[index01].mDATA.aDuelState[0],
					mAVATAR_OBJECT[index01].mDATA.aDuelState[1],
					mAVATAR_OBJECT[index01].mDATA.aDuelState[2]);

				// Trimite broadcast la locația avatarului
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
			}

			// Resetăm evenimentul complet
			mDuel_124 = FALSE;
			mDuel_124_RemainTime = 0;
			mDuel_124_AvatarNum[0] = 0;
			mDuel_124_AvatarNum[1] = 0;
			mDuel_124_Pvp = FALSE;
			return;
		}

		// Dacă tick-ul curent este par (la fiecare 2 ticks) și timpul este > 0
		if (((mTickCount % 2) == 0) && (0 < mDuel_124_RemainTime))
		{
			// La fiecare 5 secunde, trimite timpul rămas jucătorilor
			if ((mDuel_124_RemainTime % 5) == 0)
			{
				mTRANSFER.B_DUEL_TIME_INFO(mDuel_124_RemainTime);

				for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
				{
					if (mAVATAR_OBJECT[index01].mCheckValidState)
					{
						mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
					}
				}
			}
			else
			{
				// Dacă a mai rămas o singură secundă din duel
				if (mDuel_124_RemainTime == 1)
				{
					for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; ++index01)
					{
						if (!mAVATAR_OBJECT[index01].mCheckValidState)
						{
							continue;
						}
						if (mUSER[index01].mMoveZoneResult == 1)
						{
							continue;
						}

						// Determină câștigătorul sau remiza
						if ((mDuel_124_AvatarNum[0] == mDuel_124_AvatarNum[1]) || (!mDuel_124_Pvp))
						{
							mTRANSFER.B_DUEL_END_RECV(0); // remiză
						}
						else if (mDuel_124_AvatarNum[0] > mDuel_124_AvatarNum[1])
						{
							mTRANSFER.B_DUEL_END_RECV(1); // echipa 0 câștigă
						}
						else
						{
							mTRANSFER.B_DUEL_END_RECV(2); // echipa 1 câștigă
						}

						// Trimite mesajul de final jucătorului
						mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

						// Dacă e GM, nu îi aplicăm schimbări de stare
						if (mUSER[index01].mAuthInfo.AuthType == 1)
						{
							continue;
						}

						// Dacă nu este în stare de duel, îl sărim
						if (mAVATAR_OBJECT[index01].mDuelProcessState != 4)
						{
							continue;
						}

						// Resetăm starea de duel a jucătorului
						mAVATAR_OBJECT[index01].mDATA.aDuelState[0] = 0;
						mAVATAR_OBJECT[index01].mDATA.aDuelState[1] = 0;
						mAVATAR_OBJECT[index01].mDATA.aDuelState[2] = 0;
						mAVATAR_OBJECT[index01].mCheckPossibleEatPotion = TRUE;
						mAVATAR_OBJECT[index01].mDuelProcessState = 0;
						mAVATAR_OBJECT[index01].mDuelProcessRemainTime = 0;

						// Trimite actualizarea avatarului
						mTRANSFER.B_AVATAR_CHANGE_INFO_1(index01, mAVATAR_OBJECT[index01].mUniqueNumber, 7,
							mAVATAR_OBJECT[index01].mDATA.aDuelState[0],
							mAVATAR_OBJECT[index01].mDATA.aDuelState[1],
							mAVATAR_OBJECT[index01].mDATA.aDuelState[2]);

						// Broadcast locație
						mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], UNIT_SCALE_RADIUS1, false);
					}

					// Resetăm evenimentul complet
					mDuel_124 = FALSE;
					mDuel_124_RemainTime = 0;
					mDuel_124_AvatarNum[0] = 0;
					mDuel_124_AvatarNum[1] = 0;
					mDuel_124_Pvp = FALSE;
					return;
				}
			}

			// Scădem timpul rămas cu 1 secundă
			--mDuel_124_RemainTime;
		}
	}
}
//PROCESS_ZONE_071_TYPE
void MyGame::Process_Zone_071_TYPE(void)
{
}
//PROCESS_ZONE_049_TYPE (°ËÅõ¼º)
void MyGame::Process_Zone_049_TYPE(void)
{
	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeUserNum[4];
	int tWinTribe;
	int tGainExperience;
	int tGainMoney;
	int tMedalCnt = 0;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone049TypePostTick++;
	switch (mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex])
	{
	case 0:
		switch (mZone049TypeBattleState)
		{
		case 0:
			if ((mZone049TypeZoneIndex >= 3) && (mZone049TypeZoneIndex <= 5))
			{
				if (mWorldInfo.mTribeSymbolBattle == 1)
				{
					return;
				}
			}
			if (mZone049TypePostTick < (120 * 5))
			{
				return;
			}
			mZone049TypePostTick = 0;
			mZone049TypeBattleState = 1;
			mZone049TypeRemainTime1 = 10;
			return;
		case 1:
			if ((mZone049TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 1;
			CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone049TypeRemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone049TypeRemainTime1--;
			if (mZone049TypeRemainTime1 == 0)
			{
				mZone049TypePostTick = 0;
				mZone049TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone049TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 2;
			CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 1;
			mZone049TypePostTick = 0;
			mZone049TypeBattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone049TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 3;
		CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 2;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		return;
	case 2:
		if (mZone049TypePostTick < (120 * 1))
		{
			return;
		}
		mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 3;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		mZone049TypeRemainTime2 = 1800;
		mZone049TypeBattleResult[0] = 0;
		mZone049TypeBattleResult[1] = 0;
		mZone049TypeBattleResult[2] = 0;
		mZone049TypeBattleResult[3] = 0;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimit();
		//--------------//
		//--------------//
		//--------------//
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 4;
		CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone049TypeRemainTime2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 5;
			CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 5;
			mZone049TypePostTick = 0;
			mZone049TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
		/* Auto Win if no one inside */
		tTribeUserNum[0] = 0;
		tTribeUserNum[1] = 0;
		tTribeUserNum[2] = 0;
		tTribeUserNum[3] = 0;
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
			switch (mAVATAR_OBJECT[index01].mDATA.aTribe)
			{
			case 0: tTribeUserNum[0]++; break;
			case 1: tTribeUserNum[1]++; break;
			case 2: tTribeUserNum[2]++; break;
			case 3: tTribeUserNum[3]++; break;
			}
		}
		if ((tTribeUserNum[0] > 0 && tTribeUserNum[1] == 0 && tTribeUserNum[2] == 0 && tTribeUserNum[3] == 0) || (tTribeUserNum[0] == 0 && tTribeUserNum[1] > 0 && tTribeUserNum[2] == 0 && tTribeUserNum[3] == 0) || (tTribeUserNum[0] == 0 && tTribeUserNum[1] == 0 && tTribeUserNum[2] > 0 && tTribeUserNum[3] == 0) || (tTribeUserNum[0] == 0 && tTribeUserNum[1] == 0 && tTribeUserNum[2] == 0 && tTribeUserNum[3] > 0))
		{
			mZone049TypeRemainTime2 = 1;
		}

		mZone049TypeRemainTime2--;
		if ((mZone049TypeRemainTime2 % 10) == 0)
		{
			mTRANSFER.B_049_TYPE_BATTLE_INFO(&mZone049TypeBattleResult[0], mZone049TypeRemainTime2);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
		}
#if 0
		if (mZone049TypePostTick == (120 * 60))
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 6;
			CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 5;
			mZone049TypePostTick = 0;
			mZone049TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
		tTribeUserNum[0] = 0;
		tTribeUserNum[1] = 0;
		tTribeUserNum[2] = 0;
		tTribeUserNum[3] = 0;
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
			switch (mAVATAR_OBJECT[index01].mDATA.aTribe)
			{
			case 0: tTribeUserNum[0]++; break;
			case 1: tTribeUserNum[1]++; break;
			case 2: tTribeUserNum[2]++; break;
			case 3: tTribeUserNum[3]++; break;
			}
		}
		//-----------//
		//BATTLE_INFO//
		//-----------//
		if ((mZone049TypePostTick % 10) == 1)
		{
			mTRANSFER.B_049_TYPE_BATTLE_INFO(&tTribeUserNum[0]);
			mUTIL.Broadcast(FALSE, NULL, 0);
		}
		//-----------//
		//-----------//
		//-----------//
#endif
		if (0 != mZone049TypeRemainTime2) 
		{
			return;
		}

		tWinTribe = -1;
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(0))
			{
			case 1:
				if ((mZone049TypeBattleResult[0] > mZone049TypeBattleResult[2]) && (mZone049TypeBattleResult[0] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 0;
				}
				break;
			case 2:
				if ((mZone049TypeBattleResult[0] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[0] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 0;
				}
				break;
			case 3:
				if ((mZone049TypeBattleResult[0] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[0] > mZone049TypeBattleResult[2]))
				{
					tWinTribe = 0;
				}
				break;
			default:
				if ((mZone049TypeBattleResult[0] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[0] > mZone049TypeBattleResult[2]) && (mZone049TypeBattleResult[0] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 0;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(1))
			{
			case 0:
				if ((mZone049TypeBattleResult[1] > mZone049TypeBattleResult[2]) && (mZone049TypeBattleResult[1] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 1;
				}
				break;
			case 2:
				if ((mZone049TypeBattleResult[1] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[1] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 1;
				}
				break;
			case 3:
				if ((mZone049TypeBattleResult[1] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[1] > mZone049TypeBattleResult[2]))
				{
					tWinTribe = 1;
				}
				break;
			default:
				if ((mZone049TypeBattleResult[1] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[1] > mZone049TypeBattleResult[2]) && (mZone049TypeBattleResult[1] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 1;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(2))
			{
			case 0:
				if ((mZone049TypeBattleResult[2] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[2] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 2;
				}
				break;
			case 1:
				if ((mZone049TypeBattleResult[2] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[2] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 2;
				}
				break;
			case 3:
				if ((mZone049TypeBattleResult[2] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[2] > mZone049TypeBattleResult[1]))
				{
					tWinTribe = 2;
				}
				break;
			default:
				if ((mZone049TypeBattleResult[2] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[2] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[2] > mZone049TypeBattleResult[3]))
				{
					tWinTribe = 2;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(3))
			{
			case 0:
				if ((mZone049TypeBattleResult[3] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[3] > mZone049TypeBattleResult[2]))
				{
					tWinTribe = 3;
				}
				break;
			case 1:
				if ((mZone049TypeBattleResult[3] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[3] > mZone049TypeBattleResult[2]))
				{
					tWinTribe = 3;
				}
				break;
			case 2:
				if ((mZone049TypeBattleResult[3] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[3] > mZone049TypeBattleResult[1]))
				{
					tWinTribe = 3;
				}
				break;
			default:
				if ((mZone049TypeBattleResult[3] > mZone049TypeBattleResult[0]) && (mZone049TypeBattleResult[3] > mZone049TypeBattleResult[1]) && (mZone049TypeBattleResult[3] > mZone049TypeBattleResult[2]))
				{
					tWinTribe = 3;
				}
				break;
			}
		}
#if 0
		if (tWinTribe == -1)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 6;
			CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 5;
			mZone049TypePostTick = 0;
			mZone049TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
		if (tWinTribe == -1)
		{
			return;
		}
#endif
		if (-1 == tWinTribe) {
			tWinTribe = -2;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 7;
		CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tWinTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 4;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		//----------------//
		//BATTLE_WIN_BONUS//
		//----------------//
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
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(tWinTribe)))
			{
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, FALSE);
				tMedalCnt = 3;
			}
			else 
			{
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, TRUE);
				tMedalCnt = 10;
			}
#if 0
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			{
				continue;
			}
			GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, &tGainExperience, &tGainMoney);
#endif
			if (tGainExperience < 1)
			{
				continue;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);
			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (mUSER[index01].mAvatarInfo.aDailyWarCount < 3) 
			{ 
				mUSER[index01].mAvatarInfo.aDailyWarCount++; 
			}

			// Quest
			if ((mUSER[index01].mAvatarInfo.aQuestInfo[2] == 8) && (mUSER[index01].mAvatarInfo.aQuestInfo[3] == mSERVER_INFO.mServerNumber) && (mAVATAR_OBJECT[index01].ReturnQuestPresentState() == 2))
			{
				mUSER[index01].mAvatarInfo.aQuestInfo[4]++;
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 9, 0, 0, 0, 0);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 4:
		if (mZone049TypePostTick < (60 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 8;
		CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 5;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		//--------------//
		//DELETE_MONSTER//
		//--------------//
		mSUMMON.DeleteMonster();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 5:
		switch (mZone049TypeZoneIndex)
		{
		case 0:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 1:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 2:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 3:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 4:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 5:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
#ifdef __GOD__
		case 6:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 7:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 8:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 9:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 10:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 11:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 12:
			if (mZone049TypePostTick < (120 * 60))
			{
				return;
			}
			break;
#endif
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (mAVATAR_OBJECT[index01].mCheckValidState)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 9;
		CopyMemory(&tBroadcastInfoData[0], &mZone049TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone049TypeState[mZone049TypeZoneIndex] = 0;
		mZone049TypePostTick = 0;
		mZone049TypeBattleState = 0;
		return;
	}
}
//PROCESS_ZONE_051_TYPE (±¤µµ¼º 20 ~ 29).
void MyGame::Process_Zone_051_TYPE(void)
{
	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tExistStone[4];
	int tWinTribe;
	int tGainExperience;
	int tGainMoney;
	int tMedalCnt = 0;
	int tRemainTime = 1800;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone051TypePostTick++;
	switch (mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex])
	{
	case 0:
		switch (mZone051TypeBattleState)
		{
		case 0:
			if ((mZone051TypeZoneIndex >= 3) && (mZone051TypeZoneIndex <= 5))
			{
				if (mWorldInfo.mTribeSymbolBattle == 1)
				{
					return;
				}
			}
			if (mZone051TypePostTick < (120 * 5))
			{
				return;
			}
			mZone051TypePostTick = 0;
			mZone051TypeBattleState = 1;
			mZone051TypeRemainTime = 10;
			return;
		case 1:
			if ((mZone051TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 10;
			CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone051TypeRemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone051TypeRemainTime--;
			if (mZone051TypeRemainTime == 0)
			{
				mZone051TypePostTick = 0;
				mZone051TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone051TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 11;
			CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 1;
			mZone051TypePostTick = 0;
			mZone051TypeBattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone051TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 12;
		CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 2;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		return;
	case 2:
		if (mZone051TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 13;
		CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tRemainTime, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 3;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimit();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 14;
			CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 5;
			mZone051TypePostTick = 0;
			mZone051TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
#if 0
		if (mZone051TypePostTick == (120 * 30))
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 15;
			CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 5;
			mZone051TypePostTick = 0;
			mZone051TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
#endif
		tExistStone[0] = 0;
		tExistStone[1] = 0;
		tExistStone[2] = 0;
		tExistStone[3] = 0;
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_BASE_1_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			switch (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType)
			{
			case 21:
				tExistStone[0] = 1;
				break;
			case 22:
				tExistStone[1] = 1;
				break;
			case 23:
				tExistStone[2] = 1;
				break;
			case 29:
				tExistStone[3] = 1;
				break;
			}
		}
		//-----------//
		//BATTLE_INFO//
		//-----------//
		if ((mZone051TypePostTick % 10) == 0)
		{
			mTRANSFER.B_051_TYPE_BATTLE_INFO(&tExistStone[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
		}
		//-----------//
		//-----------//
		//-----------//

		tWinTribe = -1;
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(0))
			{
			case 1:
				if ((tExistStone[0]) && (!tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 0;
				}
				break;
			case 2:
				if ((tExistStone[0]) && (!tExistStone[1]) && (!tExistStone[3]))
				{
					tWinTribe = 0;
				}
				break;
			case 3:
				if ((tExistStone[0]) && (!tExistStone[1]) && (!tExistStone[2]))
				{
					tWinTribe = 0;
				}
				break;
			default:
				if ((tExistStone[0]) && (!tExistStone[1]) && (!tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 0;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(1))
			{
			case 0:
				if ((tExistStone[1]) && (!tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 1;
				}
				break;
			case 2:
				if ((!tExistStone[0]) && (tExistStone[1]) && (!tExistStone[3]))
				{
					tWinTribe = 1;
				}
				break;
			case 3:
				if ((!tExistStone[0]) && (tExistStone[1]) && (!tExistStone[2]))
				{
					tWinTribe = 1;
				}
				break;
			default:
				if ((!tExistStone[0]) && (tExistStone[1]) && (!tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 1;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(2))
			{
			case 0:
				if ((!tExistStone[1]) && (tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 2;
				}
				break;
			case 1:
				if ((!tExistStone[0]) && (tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 2;
				}
				break;
			case 3:
				if ((!tExistStone[0]) && (!tExistStone[1]) && (tExistStone[2]))
				{
					tWinTribe = 2;
				}
				break;
			default:
				if ((!tExistStone[0]) && (!tExistStone[1]) && (tExistStone[2]) && (!tExistStone[3]))
				{
					tWinTribe = 2;
				}
				break;
			}
		}
		if (tWinTribe == -1)
		{
			switch (ReturnAllianceTribe(3))
			{
			case 0:
				if ((!tExistStone[1]) && (!tExistStone[2]) && (tExistStone[3]))
				{
					tWinTribe = 3;
				}
				break;
			case 1:
				if ((!tExistStone[0]) && (!tExistStone[2]) && (tExistStone[3]))
				{
					tWinTribe = 3;
				}
				break;
			case 2:
				if ((!tExistStone[0]) && (!tExistStone[1]) && (tExistStone[3]))
				{
					tWinTribe = 3;
				}
				break;
			default:
				if ((!tExistStone[0]) && (!tExistStone[1]) && (!tExistStone[2]) && (tExistStone[3]))
				{
					tWinTribe = 3;
				}
				break;
			}
		}
#if 0
		if (tWinTribe == -1)
		{
			return;
		}
#endif
		if (-1 == tWinTribe) 
		{
			if (mZone051TypePostTick != (120 * 30))
			{
				return;
			}
			else 
			{
				tWinTribe = -2;
			}
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 16;
		CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tWinTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 4;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		//----------------//
		//BATTLE_WIN_BONUS//
		//----------------//
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
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(tWinTribe)))
			{
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, FALSE);
				tMedalCnt = 3;
			}
			else {
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, TRUE);
				tMedalCnt = 10;
			}
#if 0
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(tWinTribe)))
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			{
				continue;
			}
			GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, &tGainExperience, &tGainMoney);
#endif
			if (tGainExperience < 1)
			{
				continue;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);
			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if ((mSERVER_INFO.mServerNumber >= 154) && (mSERVER_INFO.mServerNumber <= 164)) {
				//mUTIL.ProcessForDropItem(8, 1328, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			else if ((mSERVER_INFO.mServerNumber >= 150) && (mSERVER_INFO.mServerNumber <= 153)) {

				//mUTIL.ProcessForDropItem(8, 1329, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			else {
				//mUTIL.ProcessForDropItem(8, 1330, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			//-----//
			//QUEST//
			//-----//
			if ((mUSER[index01].mAvatarInfo.aQuestInfo[2] == 8) && (mUSER[index01].mAvatarInfo.aQuestInfo[3] == mSERVER_INFO.mServerNumber) && (mAVATAR_OBJECT[index01].ReturnQuestPresentState() == 2))
			{
				mUSER[index01].mAvatarInfo.aQuestInfo[4]++;
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 9, 0, 0, 0, 0);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			//-----//
			//-----//
			//-----//
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 4:
		if (mZone051TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 17;
		CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 5;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		//--------------//
		//DELETE_MONSTER//
		//--------------//
		mSUMMON.DeleteMonster();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 5:
		switch (mZone051TypeZoneIndex)
		{
		case 0:
			if (mZone051TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 1:
			if (mZone051TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 2:
			if (mZone051TypePostTick < (120 * 60))
			{
				return;
			}
			break;
		case 3:
			if (mZone051TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 4:
			if (mZone051TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 5:
			if (mZone051TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);


		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 18;
		CopyMemory(&tBroadcastInfoData[0], &mZone051TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone051TypeState[mZone051TypeZoneIndex] = 0;
		mZone051TypePostTick = 0;
		mZone051TypeBattleState = 0;
		return;
	}
}
//PROCESS_ZONE_053_TYPE
void MyGame::Process_Zone_053_TYPE(void)
{
	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tGainExperience;
	int tGainMoney, tWinTribe = 0;
	BOOL tEnd = FALSE;
	int tMedalCnt = 0;
	int tRemainTime = 1800;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone053TypePostTick++;
	switch (mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex])
	{
	case 0:
		switch (mZone053TypeBattleState)
		{
		case 0:
			if ((mZone053TypeZoneIndex >= 2) && (mZone053TypeZoneIndex <= 9))
			{
				if (mWorldInfo.mTribeSymbolBattle == 1)
				{
					return;
				}
			}
			if (mZone053TypePostTick < (120 * 5))
			{
				return;
			}
			mZone053TypePostTick = 0;
			mZone053TypeBattleState = 1;
			mZone053TypeRemainTime = 10;
			return;
		case 1:
			if ((mZone053TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 19;
			CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone053TypeRemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone053TypeRemainTime--;
			if (mZone053TypeRemainTime == 0)
			{
				mZone053TypePostTick = 0;
				mZone053TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone053TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 20;
			CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 1;
			mZone053TypePostTick = 0;
			mZone053TypeBattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone053TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 21;
		CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 2;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		return;
	case 2:
		if (mZone053TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 22;
		CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tRemainTime, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 3;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimit();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 23;
			CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 5;
			mZone053TypePostTick = 0;
			mZone053TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
		if (mZone053TypePostTick == (120 * 30)) 
		{
			tEnd = TRUE;
		}
#if 0
		if (mZone053TypePostTick == (120 * 30))
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 24;
			CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 5;
			mZone053TypePostTick = 0;
			mZone053TypeBattleState = 0;
			//--------------//
			//DELETE_MONSTER//
			//--------------//
			mSUMMON.DeleteMonster();
			//--------------//
			//--------------//
			//--------------//
			return;
		}
#endif
		if (!tEnd) 
		{
			if ((mZone053TypePostTick % 10) == 0)
			{
				//mTRANSFER.B_053_TYPE_BATTLE_INFO(tRemainTime - (int)(mZone053TypePostTick * 0.5));
				mTRANSFER.B_053_TYPE_BATTLE_INFO(tRemainTime - (int)(mZone053TypePostTick));
				mUTIL.Broadcast(FALSE, NULL, 0, false);
			}
			if (mZone053TypePostAvatarIndex == -1)
			{
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
					if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
					{
						continue;
					}
					if (!mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mZone053TypeBattlePostLocation[0], mZone053TypeBattlePostRadius))
					{
						continue;
					}
					break;
				}
				if (index01 == mSERVER.mMAX_USER_NUM)
				{
					return;
				}
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 25;
				CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
				tWinTribe = static_cast<int> (mAVATAR_OBJECT[index01].mDATA.aTribe);
				//CopyMemory( &tBroadcastInfoData[4], &mAVATAR_OBJECT[index01].mDATA.aTribe, 4 );
				CopyMemory(&tBroadcastInfoData[4], &tWinTribe, 4);
				CopyMemory(&tBroadcastInfoData[8], &mAVATAR_OBJECT[index01].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mZone053TypeRemainTime = 5;
				mZone053TypePostAvatarIndex = index01;
				mZone053TypePostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
				mZone053TypeSaveTick = mZone053TypePostTick;
				return;
			}
			if ((!mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mUniqueNumber != mZone053TypePostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aLifeValue < 1) || (!mUTIL.CheckInRange(&mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aAction.aLocation[0], &mZone053TypeBattlePostLocation[0], mZone053TypeBattlePostRadius)) || (mUSER[mZone053TypePostAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aVisibleState == 0) || (mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aAction.aSort == 33))
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 26;
				CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mZone053TypePostAvatarIndex = -1;
				mZone053TypePostAvatarUniqueNumber = 0;
				return;
			}
			if (((mZone053TypePostTick - mZone053TypeSaveTick) % 120) != 20)
			{
				return;
			}
			if (mZone053TypeRemainTime > 0)
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 27;
				CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
				CopyMemory(&tBroadcastInfoData[4], &mZone053TypeRemainTime, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mZone053TypeRemainTime--;
				return;
			}
			tWinTribe = (int)mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aTribe;
		}
		else 
		{
			tWinTribe = -2;
		}

		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 28;
		CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
		//iTribe = static_cast<int> (mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aTribe);
		CopyMemory(&tBroadcastInfoData[4], &tWinTribe, 4);
		CopyMemory(&tBroadcastInfoData[8], &mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 4;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		//----------------//
		//BATTLE_WIN_BONUS//
		//----------------//
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
#if 0
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(mAVATAR_OBJECT[mZone053TypePostAvatarIndex].mDATA.aTribe)))
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			{
				continue;
			}
			GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney);
#endif
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(tWinTribe))) 
			{
				tMedalCnt = 3;
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, FALSE);
			}
			else 
			{
				tMedalCnt = 10;
				GetLevelBattleRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney, TRUE);
			}

			if (tGainExperience < 1)
			{
				continue;
			}
			if (!tEnd)
			{
				// Set Gain Money
				tGainMoney = 25000000;

				if (index01 == mZone053TypePostAvatarIndex)
				{
					tGainExperience *= 2;
					tGainMoney *= 2;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);
				if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
				{
					mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
					mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
			if ((mSERVER_INFO.mServerNumber >= 154) && (mSERVER_INFO.mServerNumber <= 164)) 
			{
				//mUTIL.ProcessForDropItem(8, 1328, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			else if ((mSERVER_INFO.mServerNumber >= 150) && (mSERVER_INFO.mServerNumber <= 153)) 
			{

				//mUTIL.ProcessForDropItem(8, 1329, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			else 
			{
				//mUTIL.ProcessForDropItem(8, 1330, tMedalCnt, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], mAVATAR_OBJECT[index01].mDATA.aTribe);
			}
			//-----//
			//QUEST//
			//-----//
			if ((mUSER[index01].mAvatarInfo.aQuestInfo[2] == 8) && (mUSER[index01].mAvatarInfo.aQuestInfo[3] == mSERVER_INFO.mServerNumber) && (mAVATAR_OBJECT[index01].ReturnQuestPresentState() == 2))
			{
				mUSER[index01].mAvatarInfo.aQuestInfo[4]++;
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 9, 0, 0, 0, 0);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			//-----//
			//-----//
			//-----//
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 4:
		if (mZone053TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 29;
		CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 5;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		//--------------//
		//DELETE_MONSTER//
		//--------------//
		mSUMMON.DeleteMonster();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 5:
		switch (mZone053TypeZoneIndex)
		{
		case 0:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 1:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 2:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 3:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 4:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 5:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 6:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 7:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 8:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		case 9:
			if (mZone053TypePostTick < (120 * 120))
			{
				return;
			}
			break;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++) 
		{
			mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 30;
		CopyMemory(&tBroadcastInfoData[0], &mZone053TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone053TypeState[mZone053TypeZoneIndex] = 0;
		mZone053TypePostTick = 0;
		mZone053TypeBattleState = 0;
		return;
	}
}
//GET_LEVEL_BATTLE_REWARD_INFO
void MyGame::GetLevelBattleRewardInfo(int tLevel1, int tLevel2, int* tGainExperience, int* tGainMoney, BOOL tWin)
{
	*tGainExperience = 0;
	*tGainMoney = 0;


	if (tLevel2 > 0)
	{
		switch (tLevel2)
		{
		case  1:
			*tGainExperience = 4810529;
			*tGainMoney = 10000000;
			break;
		case  2:
			*tGainExperience = 5002950;
			*tGainMoney = 10000000;
			break;
		case  3:
			*tGainExperience = 5203068;
			*tGainMoney = 10000000;
			break;
		case  4:
			*tGainExperience = 5411191;
			*tGainMoney = 10000000;
			break;
		case  5:
			*tGainExperience = 5627638;
			*tGainMoney = 15000000;
			break;
		case  6:
			*tGainExperience = 5852744;
			*tGainMoney = 15000000;
			break;
		case  7:
			*tGainExperience = 6086854;
			*tGainMoney = 15000000;
			break;
		case  8:
			*tGainExperience = 6330328;
			*tGainMoney = 15000000;
			break;
		case  9:
			*tGainExperience = 6583541;
			*tGainMoney = 20000000;
			break;
		case 10:
			*tGainExperience = 6846883;
			*tGainMoney = 20000000;
			break;
		case 11:
			*tGainExperience = 7120758;
			*tGainMoney = 20000000;
			break;
		case 12:
			*tGainExperience = 7405588;
			*tGainMoney = 20000000;
			break;
		}
		if (FALSE == tWin) {
			*tGainExperience /= 2;
			*tGainMoney /= 2;
		}
		return;
	}
	switch (tLevel1)
	{
	case  10:
		*tGainExperience = 140;
		*tGainMoney = 100000;
		break;
	case  11:
		*tGainExperience = 315;
		*tGainMoney = 100000;
		break;
	case  12:
		*tGainExperience = 499;
		*tGainMoney = 100000;
		break;
	case  13:
		*tGainExperience = 676;
		*tGainMoney = 100000;
		break;
	case  14:
		*tGainExperience = 847;
		*tGainMoney = 100000;
		break;
	case  15:
		*tGainExperience = 1015;
		*tGainMoney = 100000;
		break;
	case  16:
		*tGainExperience = 1180;
		*tGainMoney = 100000;
		break;
	case  17:
		*tGainExperience = 1342;
		*tGainMoney = 100000;
		break;
	case  18:
		*tGainExperience = 1502;
		*tGainMoney = 100000;
		break;
	case  19:
		*tGainExperience = 1660;
		*tGainMoney = 100000;
		break;
	case  20:
		*tGainExperience = 1817;
		*tGainMoney = 100000;
		break;
	case  21:
		*tGainExperience = 1972;
		*tGainMoney = 100000;
		break;
	case  22:
		*tGainExperience = 2126;
		*tGainMoney = 100000;
		break;
	case  23:
		*tGainExperience = 2278;
		*tGainMoney = 100000;
		break;
	case  24:
		*tGainExperience = 2429;
		*tGainMoney = 100000;
		break;
	case  25:
		*tGainExperience = 2580;
		*tGainMoney = 100000;
		break;
	case  26:
		*tGainExperience = 2729;
		*tGainMoney = 100000;
		break;
	case  27:
		*tGainExperience = 2877;
		*tGainMoney = 100000;
		break;
	case  28:
		*tGainExperience = 3025;
		*tGainMoney = 100000;
		break;
	case  29:
		*tGainExperience = 3172;
		*tGainMoney = 100000;
		break;
	case  30:
		*tGainExperience = 3318;
		*tGainMoney = 300000;
		break;
	case  31:
		*tGainExperience = 3463;
		*tGainMoney = 300000;
		break;
	case  32:
		*tGainExperience = 3608;
		*tGainMoney = 300000;
		break;
	case  33:
		*tGainExperience = 3752;
		*tGainMoney = 300000;
		break;
	case  34:
		*tGainExperience = 3895;
		*tGainMoney = 300000;
		break;
	case  35:
		*tGainExperience = 4038;
		*tGainMoney = 300000;
		break;
	case  36:
		*tGainExperience = 4180;
		*tGainMoney = 300000;
		break;
	case  37:
		*tGainExperience = 4322;
		*tGainMoney = 300000;
		break;
	case  38:
		*tGainExperience = 4463;
		*tGainMoney = 300000;
		break;
	case  39:
		*tGainExperience = 4604;
		*tGainMoney = 300000;
		break;
	case  40:
		*tGainExperience = 4744;
		*tGainMoney = 300000;
		break;
	case  41:
		*tGainExperience = 4884;
		*tGainMoney = 300000;
		break;
	case  42:
		*tGainExperience = 5023;
		*tGainMoney = 300000;
		break;
	case  43:
		*tGainExperience = 5162;
		*tGainMoney = 300000;
		break;
	case  44:
		*tGainExperience = 5300;
		*tGainMoney = 300000;
		break;
	case  45:
		*tGainExperience = 5438;
		*tGainMoney = 300000;
		break;
	case  46:
		*tGainExperience = 5576;
		*tGainMoney = 300000;
		break;
	case  47:
		*tGainExperience = 5713;
		*tGainMoney = 300000;
		break;
	case  48:
		*tGainExperience = 5850;
		*tGainMoney = 300000;
		break;
	case  49:
		*tGainExperience = 5987;
		*tGainMoney = 300000;
		break;
	case  50:
		*tGainExperience = 6123;
		*tGainMoney = 500000;
		break;
	case  51:
		*tGainExperience = 6259;
		*tGainMoney = 500000;
		break;
	case  52:
		*tGainExperience = 6395;
		*tGainMoney = 500000;
		break;
	case  53:
		*tGainExperience = 6530;
		*tGainMoney = 500000;
		break;
	case  54:
		*tGainExperience = 6665;
		*tGainMoney = 500000;
		break;
	case  55:
		*tGainExperience = 6799;
		*tGainMoney = 500000;
		break;
	case  56:
		*tGainExperience = 6934;
		*tGainMoney = 500000;
		break;
	case  57:
		*tGainExperience = 7068;
		*tGainMoney = 500000;
		break;
	case  58:
		*tGainExperience = 7202;
		*tGainMoney = 500000;
		break;
	case  59:
		*tGainExperience = 7335;
		*tGainMoney = 500000;
		break;
	case  60:
		*tGainExperience = 7468;
		*tGainMoney = 500000;
		break;
	case  61:
		*tGainExperience = 7601;
		*tGainMoney = 500000;
		break;
	case  62:
		*tGainExperience = 7734;
		*tGainMoney = 500000;
		break;
	case  63:
		*tGainExperience = 7866;
		*tGainMoney = 500000;
		break;
	case  64:
		*tGainExperience = 7999;
		*tGainMoney = 500000;
		break;
	case  65:
		*tGainExperience = 8131;
		*tGainMoney = 500000;
		break;
	case  66:
		*tGainExperience = 8262;
		*tGainMoney = 500000;
		break;
	case  67:
		*tGainExperience = 8394;
		*tGainMoney = 500000;
		break;
	case  68:
		*tGainExperience = 8525;
		*tGainMoney = 500000;
		break;
	case  69:
		*tGainExperience = 8656;
		*tGainMoney = 500000;
		break;
	case  70:
		*tGainExperience = 8787;
		*tGainMoney = 700000;
		break;
	case  71:
		*tGainExperience = 8918;
		*tGainMoney = 700000;
		break;
	case  72:
		*tGainExperience = 9048;
		*tGainMoney = 700000;
		break;
	case  73:
		*tGainExperience = 9178;
		*tGainMoney = 700000;
		break;
	case  74:
		*tGainExperience = 9308;
		*tGainMoney = 700000;
		break;
	case  75:
		*tGainExperience = 9438;
		*tGainMoney = 700000;
		break;
	case  76:
		*tGainExperience = 9568;
		*tGainMoney = 700000;
		break;
	case  77:
		*tGainExperience = 9697;
		*tGainMoney = 700000;
		break;
	case  78:
		*tGainExperience = 9826;
		*tGainMoney = 700000;
		break;
	case  79:
		*tGainExperience = 9955;
		*tGainMoney = 700000;
		break;
	case  80:
		*tGainExperience = 10084;
		*tGainMoney = 700000;
		break;
	case  81:
		*tGainExperience = 10213;
		*tGainMoney = 700000;
		break;
	case  82:
		*tGainExperience = 10341;
		*tGainMoney = 700000;
		break;
	case  83:
		*tGainExperience = 10469;
		*tGainMoney = 700000;
		break;
	case  84:
		*tGainExperience = 10598;
		*tGainMoney = 700000;
		break;
	case  85:
		*tGainExperience = 10725;
		*tGainMoney = 700000;
		break;
	case  86:
		*tGainExperience = 10853;
		*tGainMoney = 700000;
		break;
	case  87:
		*tGainExperience = 10981;
		*tGainMoney = 700000;
		break;
	case  88:
		*tGainExperience = 11108;
		*tGainMoney = 700000;
		break;
	case  89:
		*tGainExperience = 17585;
		*tGainMoney = 700000;
		break;
	case  90:
		*tGainExperience = 11408;
		*tGainMoney = 1000000;
		break;
	case  91:
		*tGainExperience = 12660;
		*tGainMoney = 1000000;
		break;
	case  92:
		*tGainExperience = 13548;
		*tGainMoney = 1000000;
		break;
	case  93:
		*tGainExperience = 14250;
		*tGainMoney = 1000000;
		break;
	case  94:
		*tGainExperience = 14835;
		*tGainMoney = 1000000;
		break;
	case  95:
		*tGainExperience = 15340;
		*tGainMoney = 1000000;
		break;
	case  96:
		*tGainExperience = 15786;
		*tGainMoney = 1000000;
		break;
	case  97:
		*tGainExperience = 16186;
		*tGainMoney = 1000000;
		break;
	case  98:
		*tGainExperience = 16551;
		*tGainMoney = 1000000;
		break;
	case  99:
		*tGainExperience = 19254;
		*tGainMoney = 1000000;
		break;
	case 100:
		*tGainExperience = 24979;
		*tGainMoney = 1000000;
		break;
	case 101:
		*tGainExperience = 27721;
		*tGainMoney = 1000000;
		break;
	case 102:
		*tGainExperience = 29667;
		*tGainMoney = 1000000;
		break;
	case 103:
		*tGainExperience = 31203;
		*tGainMoney = 1000000;
		break;
	case 104:
		*tGainExperience = 32484;
		*tGainMoney = 1000000;
		break;
	case 105:
		*tGainExperience = 33590;
		*tGainMoney = 1000000;
		break;
	case 106:
		*tGainExperience = 34566;
		*tGainMoney = 1000000;
		break;
	case 107:
		*tGainExperience = 35444;
		*tGainMoney = 1000000;
		break;
	case 108:
		*tGainExperience = 36241;
		*tGainMoney = 1000000;
		break;
	case 109:
		*tGainExperience = 36975;
		*tGainMoney = 1000000;
		break;
	case 110:
		*tGainExperience = 37654;
		*tGainMoney = 1000000;
		break;
	case 111:
		*tGainExperience = 38287;
		*tGainMoney = 1000000;
		break;
	case 112:
		*tGainExperience = 797423;
		*tGainMoney = 1000000;
		break;
	case 113:
		*tGainExperience = 206915;
		*tGainMoney = 3000000;
		break;
	case 114:
		*tGainExperience = 229625;
		*tGainMoney = 3000000;
		break;
	case 115:
		*tGainExperience = 245740;
		*tGainMoney = 3000000;
		break;
	case 116:
		*tGainExperience = 258464;
		*tGainMoney = 3000000;
		break;
	case 117:
		*tGainExperience = 269077;
		*tGainMoney = 3000000;
		break;
	case 118:
		*tGainExperience = 278236;
		*tGainMoney = 3000000;
		break;
	case 119:
		*tGainExperience = 286326;
		*tGainMoney = 3000000;
		break;
	case 120:
		*tGainExperience = 293592;
		*tGainMoney = 3000000;
		break;
	case 121:
		*tGainExperience = 300201;
		*tGainMoney = 3000000;
		break;
	case 122:
		*tGainExperience = 306275;
		*tGainMoney = 3000000;
		break;
	case 123:
		*tGainExperience = 311902;
		*tGainMoney = 3000000;
		break;
	case 124:
		*tGainExperience = 317149;
		*tGainMoney = 3000000;
		break;
	case 125:
		*tGainExperience = 322070;
		*tGainMoney = 3000000;
		break;
	case 126:
		*tGainExperience = 326708;
		*tGainMoney = 3000000;
		break;
	case 127:
		*tGainExperience = 331096;
		*tGainMoney = 3000000;
		break;
	case 128:
		*tGainExperience = 335263;
		*tGainMoney = 3000000;
		break;
	case 129:
		*tGainExperience = 339233;
		*tGainMoney = 3000000;
		break;
	case 130:
		*tGainExperience = 343025;
		*tGainMoney = 3000000;
		break;
	case 131:
		*tGainExperience = 346657;
		*tGainMoney = 3000000;
		break;
	case 132:
		*tGainExperience = 350142;
		*tGainMoney = 3000000;
		break;
	case 133:
		*tGainExperience = 353494;
		*tGainMoney = 3000000;
		break;
	case 134:
		*tGainExperience = 356723;
		*tGainMoney = 3000000;
		break;
	case 135:
		*tGainExperience = 359839;
		*tGainMoney = 3000000;
		break;
	case 136:
		*tGainExperience = 362851;
		*tGainMoney = 3000000;
		break;
	case 137:
		*tGainExperience = 365766;
		*tGainMoney = 5000000;
		break;
	case 138:
		*tGainExperience = 368592;
		*tGainMoney = 5000000;
		break;
	case 139:
		*tGainExperience = 371332;
		*tGainMoney = 5000000;
		break;
	case 140:
		*tGainExperience = 373996;
		*tGainMoney = 5000000;
		break;
	case 141:
		*tGainExperience = 376583;
		*tGainMoney = 5000000;
		break;
	case 142:
		*tGainExperience = 379103;
		*tGainMoney = 5000000;
		break;
	case 143:
		*tGainExperience = 381556;
		*tGainMoney = 5000000;
		break;
	case 144:
		*tGainExperience = 383950;
		*tGainMoney = 5000000;
		break;
	case 145:
		*tGainExperience = 4625509;
		*tGainMoney = 5000000;
		break;
	}
	if (FALSE == tWin) {
		*tGainExperience /= 2;
		*tGainMoney /= 2;
	}

}
//PROCESS_ZONE_038
void MyGame::Process_Zone_038(void)
{
	int index01, iTribe;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone038PostTick++;
	switch (mZone038BattleState)
	{
	case 0:
		if (mWorldInfo.mTribeSymbolBattle == 1)
		{
			return;
		}
		if (mZone038PostTick < (120 * 5))
		{
			return;
		}
		mZone038PostTick = 0;
		mZone038BattleState = 1;
		mZone038RemainTime = 10;
		return;
	case 1:
		if ((mZone038PostTick % (120 * 1)) != 0)
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 33;
		CopyMemory(&tBroadcastInfoData[0], &mZone038RemainTime, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mZone038RemainTime--;
		if (mZone038RemainTime == 0)
		{
			mZone038PostTick = 0;
			mZone038BattleState = 2;
		}
		return;
	case 2:
		if (mZone038PostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 34;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mZone038PostTick = 0;
		mZone038BattleState = 3;
		return;
	case 3:
		if (mZone038PostAvatarIndex == -1)
		{
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
				if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
				{
					continue;
				}
				if ((mAVATAR_OBJECT[index01].mDATA.aTribe == mWorldInfo.mZone038WinTribe) || (mAVATAR_OBJECT[index01].mDATA.aTribe == ReturnAllianceTribe(mWorldInfo.mZone038WinTribe)))
				{
					continue;
				}
				if (!mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mZone038BattlePostLocation[0], mZone038BattlePostRadius))
				{
					continue;
				}
				break;
			}
			if (index01 == mSERVER.mMAX_USER_NUM)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 35;
			iTribe = static_cast<int> (mAVATAR_OBJECT[index01].mDATA.aTribe);
			CopyMemory(&tBroadcastInfoData[0], &iTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[index01].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone038PostTick = 0;
			mZone038RemainTime = 5;
			mZone038PostAvatarIndex = index01;
			mZone038PostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
			return;
		}
		if ((!mAVATAR_OBJECT[mZone038PostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone038PostAvatarIndex].mUniqueNumber != mZone038PostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aLifeValue < 1) || (!mUTIL.CheckInRange(&mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aAction.aLocation[0], &mZone038BattlePostLocation[0], mZone038BattlePostRadius)) || (mUSER[mZone038PostAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aVisibleState == 0) || (mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aAction.aSort == 33))
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 36;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone038PostAvatarIndex = -1;
			mZone038PostAvatarUniqueNumber = 0;
			return;
		}
		if ((mZone038PostTick % 120) != 20)
		{
			return;
		}
		if (mZone038RemainTime > 0)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 37;
			CopyMemory(&tBroadcastInfoData[0], &mZone038RemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone038RemainTime--;
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 38;
		iTribe = static_cast<int> (mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aTribe);
		CopyMemory(&tBroadcastInfoData[0], &iTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone038WinTribe = mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aTribe;
		mZone038PostTick = 0;
		mZone038BattleState = 4;
		mSUMMON.SummonGuard(TRUE, TRUE);
		mPLAYUSER_COM.U_CHANGE_HERO_RANK_INFO_SEND(4, mUSER[mZone038PostAvatarIndex].mAvatarInfo.aName, 50, mUSER[mZone038PostAvatarIndex].mAvatarInfo.aTribe);
		//-----//
		//QUEST//
		//-----//
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
			if (mAVATAR_OBJECT[index01].mDATA.aTribe != mAVATAR_OBJECT[mZone038PostAvatarIndex].mDATA.aTribe)
			{
				continue;
			}
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			{
				continue;
			}
			if ((mUSER[index01].mAvatarInfo.aQuestInfo[2] == 8) && (mUSER[index01].mAvatarInfo.aQuestInfo[3] == mSERVER_INFO.mServerNumber) && (mAVATAR_OBJECT[index01].ReturnQuestPresentState() == 2))
			{
				mUSER[index01].mAvatarInfo.aQuestInfo[4]++;
				mTRANSFER.B_PROCESS_QUEST_RECV(0, 9, 0, 0, 0, 0);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		// Done Claim Reset State
		mZone038PostAvatarIndex = -1;
		mZone038PostAvatarUniqueNumber = 0;
		return;
	case 4:
		if (mZone038PostTick < (120 * 180))
		{
			return;
		}
		mZone038PostTick = 0;
		mZone038BattleState = 0;
		mZone038PostAvatarIndex = -1;
		mZone038PostAvatarUniqueNumber = 0;
		return;
	}
}
//PROCESS_ZONE_039_TYPE
void MyGame::Process_Zone_039_TYPE(void)
{
	int index01;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone039TypePostTick++;
	switch (mZone039TypeBattleState)
	{
	case 0:
		return;
	case 1:
		if (mZone039TypePostTick < (120 * 1))
		{
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mUSER[index01].mCheckValidState)
			{
				continue;
			}
			if ((mUSER[index01].mAvatarInfo.aTribe != mWorldInfo.mZone038WinTribe) && (mUSER[index01].mAvatarInfo.aTribe != ReturnAllianceTribe(mWorldInfo.mZone038WinTribe)))
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);


			}
		}
		mZone039TypeBattleState = 0;
		mZone039TypePostTick = 0;
		return;
	}
}
void MyGame::Process_Zone_175_TYPE(void)//Labyrint
{
	int index01;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tGainExperience;
	int tGainMoney;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone175TypePostTick++;
	switch (mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2])
	{
	case  0:
		switch (mZone175TypeBattleState)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}//In fiecare zi la ora:
			if ((tPresentTime->tm_hour != 16) || (tPresentTime->tm_min != 55))
			{
				return;
			}

			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 1;
			mZone175TypeRemainTime = 10;
			return;
		case 1:
			if ((mZone175TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			if (10 == mZone175TypeRemainTime)
			{
				mGAMELOG.GL_661_START_MISSION_LABYRINTH();
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 63;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			CopyMemory(&tBroadcastInfoData[8], &mZone175TypeRemainTime, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone175TypeRemainTime--;
			if (mZone175TypeRemainTime == 0)
			{
				mZone175TypePostTick = 0;
				mZone175TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone175TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 64;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 1;
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;
			return;
		}
		return;
	case  1:
		if (mZone175TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 65;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 2;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	case  2: //[1´Ü°è_ÀÔ±¸°³¹æ]
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 66;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 3;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	case  3: //[1´Ü°è_ÀÔ±¸Æó¼â]
		if (mZone175TypePostTick < (120 * 2))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 67;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 4;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	case  4: //[1´Ü°è_½ÃÀÛ]
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 68;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 5;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimitForZone175Type(1);
		//--------------//
		//--------------//
		//--------------//
		return;

	case 5:
		// Verificăm dacă toți jucătorii au părăsit zona
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState) continue;
			if (mUSER[index01].mMoveZoneResult == 1) continue;
			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0) continue;
			break;
		}

		// Dacă zona este goală, încheiem evenimentul
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			tBroadcastInfoSort = 69;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mSUMMON.DeleteMonster();
			return;
		}

		// Dacă timpul a expirat (ex: 60 minute)
		if (mZone175TypePostTick == (120 * 60))
		{
			tBroadcastInfoSort = 70;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mSUMMON.DeleteMonster();
			return;
		}

		// La fiecare 20 de tick-uri, invocăm monștri
		if ((mZone175TypePostTick % 20) == 0)
		{
			mSUMMON.SummonMonsterForZone175Type();
		}

		// Verificăm dacă mai există monștri speciali în viață
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState) continue;
			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType >= 40) && (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType <= 44))
			{
				break;
			}
		}

		// Dacă nu mai sunt monștri speciali, încheiem evenimentul
		if (index01 < MAX_MONSTER_OBJECT_NUM)
		{
			return;
		}

		// Broadcast: câștigarea bătăliei
		tBroadcastInfoSort = 71;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 6;
		mZone175TypePostTick = 0;
		mSUMMON.DeleteMonster();

		// Bonus pentru toți jucătorii activi
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (!mAVATAR_OBJECT[index01].mCheckValidState) continue;
			if (mUSER[index01].mMoveZoneResult == 1) continue;
			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0) continue;
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1) continue;

			// Dacă jucătorul este într-o stare de atac special, îl resetăm
			if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 11)
			{
				mAVATAR_OBJECT[index01].mDATA.aAction.aType = mAVATAR_OBJECT[index01].GetWeaponClass() * 2;
				mAVATAR_OBJECT[index01].mDATA.aAction.aSort = 1;
				mAVATAR_OBJECT[index01].mDATA.aAction.aFrame = 0.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aSkillValue = 0;

				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 1);
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 1, false, 1);
			}
#ifdef __GOD__
			// Dacă este definit simbolul __GOD__, se apelează această versiune a funcției GetZone175TypeRewardInfo,
			// care primește ca parametri nivelurile aLevel1 și aLevel2 și un parametru suplimentar 1, apoi returnează experiența și banii câștigați.
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, 1, &tGainExperience, &tGainMoney);
#else
			// Dacă simbolul __GOD__ nu este definit, se folosește o versiune mai simplă a funcției,
			// cu doar nivelul aLevel1 și parametrul 1, fără al doilea nivel.
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, 1, &tGainExperience, &tGainMoney);
#endif

			// Dacă experiența câștigată este mai mică decât 1, se trece la următorul ciclu (nu se acordă experiență)
			if (tGainExperience < 1)
			{
				continue;
			}

			// Se setează în pachetul de transfer tipul 1 și cantitatea de experiență câștigată
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);

			// Se trimite pachetul către utilizatorul curent
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			// Se procesează experiența câștigată pentru utilizator
			mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);

			// Se adaugă 250 la statistica "aKillOtherTribe" (număr de ucideri de membri din alte triburi) pentru avatar
			mUSER[index01].mAvatarInfo.aKillOtherTribe += 250;
			mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 250;

			// Se trimite pachetul de modificare pentru această statistică (tip 3)
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			// Dacă adăugarea banilor nu depășește limita maximă admisă
			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				// Se adaugă banii câștigați la utilizator
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;

				// Se trimite pachetul cu modificarea banilor (tip 23)
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}

			// Procesarea drop-ului de obiecte - etapa 1
			// Se încearcă să se dea obiecte cu VNUM-urile 1037, 1022 și 1024 utilizatorului curent
			mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1022, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1024, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);

		}

		// --- următoarele blocuri sunt în switch/case și tratează diverse stări ale zonei ---

		// Return la finalul unei etape
		return;

	case 6: //[º»¼º±ÍÈ¯_OR_2´Ü°è_ÀÔ±¸°³¹æ]
		// Dacă timpul post-tick este mai mic decât 120 unități (1 secundă x 120), ieșim
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		// Dacă indexul zonei 2 este invalid (< 1), se face un broadcast info și se resetează starea zonei
		if (mZone175TypeZoneIndex2 < 1)
		{
			// Se setează tipul broadcastului la 72
			tBroadcastInfoSort = 72;

			// Se copiază indexul zonei 1 și 2 în buffer-ul de broadcast
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);

			// Se cere serverului centru să trimită broadcast cu acest info
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			// Se setează starea zonei la 23 (posibil finalizată)
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;

			// Se resetează tick-ul și starea bătăliei
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;
			return;
		}
		// Se face un broadcast info de tip 73 pentru alte situații
		tBroadcastInfoSort = 73;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Se setează starea zonei la 7, apoi reset tick și stare bătălie
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 7;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;

	case 7: //[2´Ü°è_ÀÔ±¸Æó¼â]
		// Dacă timpul post-tick este mai mic decât 240 (2 sec x 120), ieșim
		if (mZone175TypePostTick < (120 * 2))
		{
			return;
		}
		// Se face broadcast info tip 74
		tBroadcastInfoSort = 74;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Se setează starea zonei la 8
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 8;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;

	case 8: //[2´Ü°è_½ÃÀÛ]
		// Dacă timpul post-tick este mai mic decât 120, ieșim
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		// Se face broadcast info tip 75
		tBroadcastInfoSort = 75;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Se setează starea zonei la 9
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 9;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		// Se cheamă funcția pentru a invoca monștri fără limită de timp în zona 175 tip 2
		mSUMMON.SummonMonsterWithoutTimeLimitForZone175Type(2);
		return;

	case 9: //[2´Ü°è_ÁøÇà]
		// Se începe un loop pentru toți utilizatorii serverului
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			// Se sare peste utilizatorii invalizi
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			// Se sare peste utilizatorii care sunt în mișcare către o zonă (mMoveZoneResult == 1)
			if (mUSER[index01].mMoveZoneResult == 1)
			{
				continue;
			}
			// Se sare peste utilizatorii invizibili (visibleState == 0)
			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
			{
				continue;
			}
			break; // Dacă se găsește un utilizator valid, se iese din loop
		}
		// Dacă nu s-a găsit niciun utilizator valid
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			// Se face broadcast info tip 76
			tBroadcastInfoSort = 76;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			// Se setează starea zonei la 23 (finalizată)
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;

			// Se șterg monștrii din zonă
			mSUMMON.DeleteMonster();
			return;
		}

		// Dacă timpul post-tick a ajuns la 60 secunde (120 * 60)
		if (mZone175TypePostTick == (120 * 60))
		{
			// Se face broadcast info tip 77
			tBroadcastInfoSort = 77;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			// Se setează starea zonei la 23 (finalizată)
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;

			// Se șterg monștrii din zonă
			mSUMMON.DeleteMonster();
			return;
		}

		// La fiecare 20 unități de timp (aprox. 1 secundă), se invocă monștri pentru zona 175 tip
		if ((mZone175TypePostTick % 20) == 0)
		{
			mSUMMON.SummonMonsterForZone175Type();
		}

		// Se parcurge lista de monștri pentru a verifica dacă există monștri speciali (tip 40-44)
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 40) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 41) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 42) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 43) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 44))
			{
				break;
			}
		}

		// Dacă s-au găsit monștri speciali, se iese fără a face nimic în continuare
		if (index01 < MAX_MONSTER_OBJECT_NUM)
		{
			return;
		}

		// Se face broadcast info tip 78
		tBroadcastInfoSort = 78;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Se setează starea zonei la 10 (posibil starea de final de bătălie)
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 10;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		// Se șterg monștrii din zonă
		mSUMMON.DeleteMonster();
		//----------------//
// BONUS LA VICTORIE ÎN LUPTĂ //
//----------------//
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			// Verific dacă avatarul este valid
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			// Sar peste utilizatorii care au rezultat mutare zonă = 1
			if (mUSER[index01].mMoveZoneResult == 1)
			{
				continue;
			}
			// Sar peste avatarurile invizibile
			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
			{
				continue;
			}
			// Sar peste avatarurile care sunt moarte (life < 1)
			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			{
				continue;
			}
			// Dacă avatarul este într-o stare specială (aSort == 11), o resetez la stare normală
			if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 11)
			{
				// Setez tipul acțiunii conform clasei armei înmulțită cu 2
				mAVATAR_OBJECT[index01].mDATA.aAction.aType = mAVATAR_OBJECT[index01].GetWeaponClass() * 2;
				// Resetez starea acțiunii la 1 (stare normală)
				mAVATAR_OBJECT[index01].mDATA.aAction.aSort = 1;
				// Resetez cadrul animației
				mAVATAR_OBJECT[index01].mDATA.aAction.aFrame = 0.0f;
				// Resetez valoarea skill-ului
				mAVATAR_OBJECT[index01].mDATA.aAction.aSkillValue = 0;
				// Trimit acțiunea modificată către client/server
				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 1);
				// Difuzez noua poziție a avatarului către toți ceilalți jucători
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 1, false, 1);
			}


#ifdef __GOD__
			// Dacă compilăm cu flag-ul __GOD__, apelăm funcția GetZone175TypeRewardInfo cu parametri suplimentari (nivel 1, nivel 2, tip 2)
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, 2, &tGainExperience, &tGainMoney);
#else
			// Altfel, apelăm funcția fără nivelul 2
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, 2, &tGainExperience, &tGainMoney);
#endif
			// Dacă experiența câștigată este mai mică decât 1, sărim peste restul codului pentru acest avatar
			if (tGainExperience < 1)
			{
				continue;
			}
			// Pregătim transferul informațiilor despre experiență
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
			// Trimitem datele către client
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			// Procesăm experiența câștigată de avatar
			mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);

			// Creștem punctele pentru "ucidere alte triburi" cu 250
			mUSER[index01].mAvatarInfo.aKillOtherTribe += 250;
			mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 250;
			// Trimitem modificarea la client
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			// Verificăm dacă suma banilor după adăugare nu depășește maximul permis
			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				// Adăugăm banii câștigați
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
				// Trimitem modificarea la client
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			// Etapa 2 - Generăm drop-uri de iteme în locația avatarului
			mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		}
		//----------------//
		//----------------//
		//----------------//
		return;
case 10: //[MESAJ_DE_VICTORIE_SAU_3_MINUTE_DE_CONTEST]
	// Dacă timpul post eveniment este mai mic decât 120 (1 minut în unități de tick), ieșim
	if (mZone175TypePostTick < (120 * 1))
	{
		return;
	}
	// Dacă indexul celei de-a doua zone este mai mic decât 2
	if (mZone175TypeZoneIndex2 < 2)
	{
		//----------------//
		// TRANSMITEM INFORMAȚII BROADCAST //
		//----------------//
		tBroadcastInfoSort = 79;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//----------------//
		//----------------//
		//----------------//
		// Setăm starea zonei la 23 (probabil stare de finalizare)
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
		// Resetăm contorul de post-tick și starea bătăliei
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	}
	//----------------//
	// TRANSMITEM INFORMAȚII BROADCAST //
	//----------------//
	tBroadcastInfoSort = 80;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
	//----------------//
	//----------------//
	//----------------//
	// Setăm starea zonei la 11 (probabil stare activă sau pregătire)
	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 11;
	// Resetăm contorul de post-tick și starea bătăliei
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;
	return;
case 11: // Faza 11: Așteaptă 2 minute înainte de a trece la etapa următoare
	if (mZone175TypePostTick < (120 * 2)) // Dacă timpul post tick este mai mic de 240 (2 minute)
	{
		return; // Nu face nimic până nu se împlinește timpul
	}
	// Trimite informații de broadcast către server cu codul 81 și indicii zonei
	tBroadcastInfoSort = 81;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	// Actualizează starea zonei la 12, resetează contorii de timp și stare
	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 12;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;
	return;

case 12: // Faza 12: Așteaptă 1 minut pentru pregătirea luptei
	if (mZone175TypePostTick < (120 * 1)) // Dacă timpul post tick este mai mic de 120 (1 minut)
	{
		return; // Așteaptă până expiră timpul
	}
	// Trimite informații de broadcast către server cu codul 82 și indicii zonei
	tBroadcastInfoSort = 82;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	// Setează starea zonei la 13 și resetează contorii
	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 13;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;

	// Apelează funcția pentru a invoca monștri fără limită de timp
	mSUMMON.SummonMonsterWithoutTimeLimitForZone175Type(3);
	return;

case 13: // Faza 13: Luptele sunt active în zonă
	// Caută un jucător valid în zonă
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState) // Dacă jucătorul nu este valid
		{
			continue; // Trece la următorul
		}
		if (mUSER[index01].mMoveZoneResult == 1) // Dacă jucătorul este în proces de mutare în altă zonă
		{
			continue; // Trece la următorul
		}
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0) // Dacă jucătorul este invizibil
		{
			continue; // Trece la următorul
		}
		break; // Găsit jucător valid
	}
	if (index01 == mSERVER.mMAX_USER_NUM) // Dacă nu există jucători valizi
	{
		// Trimite broadcast că lupta s-a terminat (cod 83)
		tBroadcastInfoSort = 83;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Setează starea zonei la 23 (lupta terminată), resetează timpi și stare
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		// Șterge monștrii din zonă
		mSUMMON.DeleteMonster();
		return;
	}
	if (mZone175TypePostTick == (120 * 60)) // Dacă a trecut o oră de luptă
	{
		// Trimite broadcast că lupta s-a terminat forțat (cod 84)
		tBroadcastInfoSort = 84;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Setează starea zonei la 23 și resetează timpii și starea
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		// Șterge monștrii
		mSUMMON.DeleteMonster();
		return;
	}
	if ((mZone175TypePostTick % 20) == 0) // La fiecare 20 de tick-uri
	{
		mSUMMON.SummonMonsterForZone175Type(); // Invocă monștri în zonă
	}
	// Caută monștri speciali (tip 40-44) în zonă
	for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState) // Dacă monstrul nu este valid
		{
			continue; // Trece la următorul
		}
		if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 40) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 41) ||
			(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 42) || (mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 43) ||
			(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 44)) // Dacă monstrul este special
		{
			break; // Ieși din loop
		}
	}
	if (index01 < MAX_MONSTER_OBJECT_NUM) // Dacă există monștri speciali
	{
		return; // Continuă lupta
	}
	// Nu mai sunt monștri speciali, trimite broadcast că lupta s-a terminat (cod 85)
	tBroadcastInfoSort = 85;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	// Setează starea zonei la 14 (luptă finalizată), resetează timpi și stare
	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 14;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;

	// Șterge monștrii
	mSUMMON.DeleteMonster();

	// Acordă bonusuri jucătorilor care au supraviețuit
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
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1) // Dacă jucătorul este mort
		{
			continue;
		}

		// Dacă jucătorul era într-o acțiune de atac (sort 11), resetează acțiunea
		if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 11)
		{
			mAVATAR_OBJECT[index01].mDATA.aAction.aType = mAVATAR_OBJECT[index01].GetWeaponClass() * 2;
			mAVATAR_OBJECT[index01].mDATA.aAction.aSort = 1;
			mAVATAR_OBJECT[index01].mDATA.aAction.aFrame = 0.0f;
			mAVATAR_OBJECT[index01].mDATA.aAction.aSkillValue = 0;

			mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 1);

			// Anunță ceilalți jucători despre schimbarea acțiunii
			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 1, false, 1);
		}
#ifdef __GOD__
		// Dacă este definită macro __GOD__, se folosește o versiune a funcției care primește și nivelul 2 al avatarului
		GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, 3, &tGainExperience, &tGainMoney);
#else
		// Altfel, se folosește versiunea care ia în considerare doar nivelul 1 și tipul 3 pentru recompense
		GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, 3, &tGainExperience, &tGainMoney);
#endif

		// Dacă experiența câștigată este mai mică decât 1, nu se continuă cu restul logicii pentru acest avatar
		if (tGainExperience < 1)
		{
			continue;
		}

		// Se actualizează informațiile avatarului cu experiența câștigată
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);

		// Se trimite clientului datele actualizate despre avatar
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Se procesează experiența câștigată pentru avatar
		mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);

		// Se adaugă puncte pentru uciderea altor triburi (250 puncte)
		mUSER[index01].mAvatarInfo.aKillOtherTribe += 250;
		mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 250;

		// Se actualizează și se trimite clientului noua valoare a punctelor pentru uciderea altor triburi
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Dacă adăugarea banilor nu depășește limita maximă, se adaugă banii câștigați avatarului
		if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
		{
			mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		// Se procesează dropul de iteme pentru etapa 3 (dropuri specifice zonei 1037 și 1023, 1025)
		mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
	}

	// Blocurile switch/case pentru diferite stări (14, 15, 16, 17) controlează logica fazelor din luptă

case 14: // Finalizare sau oprire luptă (OR 4 regiuni ocupate)
	if (mZone175TypePostTick < (120 * 1)) // Așteaptă 1 minut înainte de a continua
	{
		return;
	}
	if (mZone175TypeZoneIndex2 < 3)
	{
		// Se anunță prin broadcast schimbarea stării cu codul 86 și se resetează zona
		tBroadcastInfoSort = 86;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23; // stare finală
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	}

	// Altfel, se anunță stare diferită (cod 87) și se setează starea la 15 (altă fază)
	tBroadcastInfoSort = 87;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 15;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;
	return;

case 15: // Start faza 4 regiuni
	if (mZone175TypePostTick < (120 * 2)) // Așteaptă 2 minute
	{
		return;
	}

	tBroadcastInfoSort = 88; // Anunță startul fazei
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 16; // Setează starea
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;
	return;

case 16: // Faza de început de luptă pe 4 regiuni
	if (mZone175TypePostTick < (120 * 1)) // Așteaptă 1 minut
	{
		return;
	}

	tBroadcastInfoSort = 89; // Anunță începerea oficială a luptei
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 17;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;

	// Se summon-ează monștri fără limită de timp pentru zona curentă
	mSUMMON.SummonMonsterWithoutTimeLimitForZone175Type(4);
	return;

case 17:
	// Verifică dacă există vreun jucător activ și vizibil în zonă
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
			continue;
		if (mUSER[index01].mMoveZoneResult == 1)
			continue;
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
			continue;
		break;
	}

	// Dacă nu există jucători activi, încheie evenimentul și curăță monștrii
	if (index01 == mSERVER.mMAX_USER_NUM)
	{
		tBroadcastInfoSort = 90;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		mSUMMON.DeleteMonster();

		return;
	}

	// Dacă timpul evenimentului a expirat, finalizează evenimentul și curăță monștrii
	if (mZone175TypePostTick == (120 * 60))
	{
		tBroadcastInfoSort = 91;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		mSUMMON.DeleteMonster();

		return;
	}

	// La fiecare 20 de tick-uri, reapare monștri în zonă
	if ((mZone175TypePostTick % 20) == 0)
	{
		mSUMMON.SummonMonsterForZone175Type();
	}

	// Caută monștri speciali cu tipurile între 40 și 44
	for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
	{
		if (!mMONSTER_OBJECT[index01].mCheckValidState)
			continue;
		if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType >= 40) &&
			(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType <= 44))
		{
			break;
		}
	}

	// Dacă există încă astfel de monștri, oprește procesarea
	if (index01 < MAX_MONSTER_OBJECT_NUM)
	{
		return;
	}

	// Dacă nu mai există monștri speciali, trimite broadcast de finalizare și resetează starea
	tBroadcastInfoSort = 92;
	CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
	CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
	mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

	mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 18;
	mZone175TypePostTick = 0;
	mZone175TypeBattleState = 0;

	mSUMMON.DeleteMonster();

	// Acordă bonus jucătorilor care au câștigat lupta și sunt în viață
	for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
	{
		if (!mAVATAR_OBJECT[index01].mCheckValidState)
			continue;
		if (mUSER[index01].mMoveZoneResult == 1)
			continue;
		if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
			continue;
		if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
			continue;

		if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 11)
		{
			mAVATAR_OBJECT[index01].mDATA.aAction.aType = mAVATAR_OBJECT[index01].GetWeaponClass() * 2;
			mAVATAR_OBJECT[index01].mDATA.aAction.aSort = 1;
			mAVATAR_OBJECT[index01].mDATA.aAction.aFrame = 0.0f;
			mAVATAR_OBJECT[index01].mDATA.aAction.aSkillValue = 0;

			mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 1);

			mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 1, false, 1);
		}
#ifdef __GOD__
		// Dacă este activată versiunea GOD, folosește funcția cu doi parametri de level pentru recompense
		GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, 4, &tGainExperience, &tGainMoney);
#else
		// Altfel, folosește versiunea standard a funcției (fără al doilea parametru de level)
		GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, 4, &tGainExperience, &tGainMoney);
#endif

		// Dacă experiența obținută este mai mică decât 1, continuă fără a acorda nimic
		if (tGainExperience < 1)
		{
			continue;
		}

		// Trimite experiența obținută către jucător
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Procesează experiența în sistemul de utilizatori
		mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);

		// Acordă 250 puncte la statistica "KillOtherTribe"
		mUSER[index01].mAvatarInfo.aKillOtherTribe += 250;
		mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 250;

		// Trimite actualizarea către client
		mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
		mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

		// Verifică dacă suma de bani obținută nu depășește limita maximă
		if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
		{
			// Adaugă banii jucătorului
			mUSER[index01].mAvatarInfo.aMoney += tGainMoney;

			// Trimite actualizarea sumei de bani către client
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}

		// Generează iteme ca recompensă în locația jucătorului
		// (Se pare că e vorba de Stage 4 Drop - zona specială de recompense)
		mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		mUTIL.ProcessForDropItem(11, 1041, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 18:
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		if (mZone175TypeZoneIndex2 < 4)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 93;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 94;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 19;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	case 19:
		if (mZone175TypePostTick < (120 * 2))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 95;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 20;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		return;
	case 20: 
		if (mZone175TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 96;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 21;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimitForZone175Type(5);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 21:
		// Parcurgem toți utilizatorii conectați
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			// Dacă jucătorul nu este într-o stare validă, continuăm
			if (!mAVATAR_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			// Dacă jucătorul tocmai s-a mutat din zonă, continuăm
			if (mUSER[index01].mMoveZoneResult == 1)
			{
				continue;
			}
			// Dacă jucătorul este invizibil, continuăm
			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
			{
				continue;
			}
			// Dacă am găsit măcar un jucător valid și vizibil, ieșim din for
			break;
		}

		// Dacă nu am găsit niciun jucător valid în zonă
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			// Trimite informația de broadcast (tipul 97) către toți
			tBroadcastInfoSort = 97;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			// Setează starea zonei ca închisă (23)
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;

			// Resetează timerul și starea luptei
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;

			// Șterge toți monștrii invocați
			mSUMMON.DeleteMonster();
			return;
		}

		// Dacă timpul a ajuns la 120 de secunde * 60 de ticks (adică 2 minute în ticks)
		if (mZone175TypePostTick == (120 * 60))
		{
			// Trimite broadcast tip 98 - probabil semnal de încheiere eveniment forțat
			tBroadcastInfoSort = 98;
			CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

			// Închide zona
			mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;
			mZone175TypePostTick = 0;
			mZone175TypeBattleState = 0;

			// Șterge toți monștrii
			mSUMMON.DeleteMonster();
			return;
		}

		// La fiecare 20 de ticks, invocă un monstru
		if ((mZone175TypePostTick % 20) == 0)
		{
			mSUMMON.SummonMonsterForZone175Type();
		}

		// Verifică dacă există vreun monstru de tip special 40-44 în viață
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 40) ||
				(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 41) ||
				(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 42) ||
				(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 43) ||
				(mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 44))
			{
				// Dacă găsește un astfel de monstru, oprește verificarea
				break;
			}
		}

		// Dacă există încă monștri speciali în zonă, nu face nimic
		if (index01 < MAX_MONSTER_OBJECT_NUM)
		{
			return;
		}

		// Toți monștrii au fost eliminați - zona este câștigată
		// Trimite broadcast tip 99 - anunț de victorie
		tBroadcastInfoSort = 99;
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		// Marchează zona ca "cucerită"
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 22;
		mZone175TypePostTick = 0;
		mZone175TypeBattleState = 0;

		// Șterge monștrii rămași
		mSUMMON.DeleteMonster();

		// Bonus de victorie pentru jucători activi
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			// Verificări: jucător activ, neîn mișcare de zonă, vizibil, viu
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

			// Dacă jucătorul este în stare de acțiune "nemuritor" (sort 11), îl resetează la stare normală
			if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 11)
			{
				// Setează tipul de atac în funcție de clasa armei * 2
				mAVATAR_OBJECT[index01].mDATA.aAction.aType = mAVATAR_OBJECT[index01].GetWeaponClass() * 2;

				// Resetează starea de acțiune la atac normal
				mAVATAR_OBJECT[index01].mDATA.aAction.aSort = 1;
				mAVATAR_OBJECT[index01].mDATA.aAction.aFrame = 0.0f;
				mAVATAR_OBJECT[index01].mDATA.aAction.aSkillValue = 0;

				// Trimite acțiunea jucătorului către client
				mTRANSFER.B_AVATAR_ACTION_RECV(index01, mAVATAR_OBJECT[index01].mUniqueNumber, &mAVATAR_OBJECT[index01].mDATA, 1);

				// Transmite acțiunea și către ceilalți jucători din zonă
				mUTIL.Broadcast(TRUE, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], 1, false, 1);
			}
#ifdef __GOD__
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, 5, &tGainExperience, &tGainMoney);
#else
			GetZone175TypeRewardInfo(mAVATAR_OBJECT[index01].mDATA.aLevel1, 5, &tGainExperience, &tGainMoney);
#endif
			if (tGainExperience < 1)
			{
				continue;
			}
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);

			mUSER[index01].mAvatarInfo.aKillOtherTribe += 250;
			mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 250;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);

			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			// Stage 5 Drop
			mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1037, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1023, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1025, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1041, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1049, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(11, 1048, 0, 0, mUTIL.ReturnItemRecognitionNumber(0), &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mAVATAR_OBJECT[index01].mDATA.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 22:
		// Verifică dacă au trecut cel puțin 120 de secunde (2 minute) de la ultima actualizare.
		if (mZone175TypePostTick < (120 * 1))
		{
			// Dacă nu au trecut cele 120 de secunde, se oprește execuția acestui caz.
			return;
		}

		//--------------//
		//BROADCAST_INFO//
		//--------------//

		// Setează tipul de informație pentru broadcast la 100 (probabil cod predefinit pentru un tip specific de mesaj global).
		tBroadcastInfoSort = 100;

		// Copiază indexul zonei în bufferul de date pentru trimiterea broadcast-ului.
		// Se copiază 4 bytes (un `int`) de la `mZone175TypeZoneIndex1` în primele 4 bytes ai `tBroadcastInfoData`.
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);

		// Apoi se copiază al doilea index al zonei în următorii 4 bytes.
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);

		// Trimite mesajul broadcast către centru (toți jucătorii sau instanțele conectate),
		// cu tipul 100 și datele referitoare la zona 175.
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		//--------------//
		//--------------//
		//--------------//

		// Actualizează starea zonei 175 pentru această zonă specifică (identificată de index1 și index2) la valoarea 23,
		// indicând că urmează faza de "inițializare/resetare".
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 23;

		// Resetează contorul de timp pentru tick-ul post-eveniment.
		mZone175TypePostTick = 0;

		// Resetează starea luptei pentru zona respectivă.
		mZone175TypeBattleState = 0;

		// Iese din `switch` (sau din funcție) – cazul 22 s-a încheiat.
		return;

	case 23:
		// Verifică dacă au trecut cel puțin 120 * 60 secunde (adică 7200 secunde = 2 ore) de la ultima actualizare.
		if (mZone175TypePostTick < (120 * 60))
		{
			// Dacă nu au trecut cele 2 ore, iese fără a face nimic.
			return;
		}

		// Apelează funcția de log care notează finalizarea misiunii "Labyrinth" în fișierele de log ale serverului.
		mGAMELOG.GL_662_END_MISSION_LABYRINTH();

		// Parcurge toți jucătorii conectați pe server.
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			// Forțează deconectarea fiecărui jucător prin apelul `Quit`, oferind ca parametri fișierul, funcția și linia
			// pentru a putea fi logate sau debugate mai ușor în caz de erori.
			mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
		}

		//--------------//
		//BROADCAST_INFO//
		//--------------//

		// Setează codul de tip broadcast la 110 — acest tip este diferit față de cel din `case 22`,
		// probabil semnalând finalul complet al evenimentului.
		tBroadcastInfoSort = 110;

		// Copiază indexul zonei în bufferul de date pentru broadcast.
		CopyMemory(&tBroadcastInfoData[0], &mZone175TypeZoneIndex1, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone175TypeZoneIndex2, 4);

		// Trimite broadcast-ul de tip 110 către toți jucătorii/serverele,
		// anunțând încheierea misiunii și resetarea zonei.
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);

		//--------------//
		//--------------//
		//--------------//

		// Setează starea zonei la 0 — ceea ce probabil înseamnă că zona a fost complet resetată și este liberă pentru următorul eveniment.
		mWorldInfo.mZone175TypeState[mZone175TypeZoneIndex1][mZone175TypeZoneIndex2] = 0;

		// Resetează contorul de timp al evenimentului.
		mZone175TypePostTick = 0;

		// Resetează starea de luptă pentru zona respectivă.
		mZone175TypeBattleState = 0;

		// Iese din switch sau funcție — cazul 23 s-a încheiat.
		return;
	}
}
//GET_ZONE_175_TYPE_REWARD_INFO
#ifdef __GOD__
void MyGame::GetZone175TypeRewardInfo(int tLevel, int tLevel2, int tStep, int* tGainExperience, int* tGainMoney)
#else
void MyGame::GetZone175TypeRewardInfo(int tLevel, int tStep, int* tGainExperience, int* tGainMoney)
#endif
{
	*tGainExperience = 0;
	*tGainMoney = 0;
	if (tLevel2 > 0)
	{
		switch (tLevel2)
		{
		case  1:
			*tGainExperience = 4810529;
			break;
		case  2:
			*tGainExperience = 5002950;
			break;
		case  3:
			*tGainExperience = 5203068;
			break;
		case  4:
			*tGainExperience = 5411191;
			break;
		case  5:
			*tGainExperience = 2813819;
			break;
		case  6:
			*tGainExperience = 2926372;
			break;
		case  7:
			*tGainExperience = 3043427;
			break;
		case  8:
			*tGainExperience = 3165164;
			break;
		case  9:
			*tGainExperience = 2106733;
			break;
		case 10:
			*tGainExperience = 2191002;
			break;
		case 11:
			*tGainExperience = 2278642;
			break;
		case 12:
			*tGainExperience = 2369788;
			break;
		}
		switch (tStep)
		{
		case 1:
			*tGainMoney = 13000000;
			break;
		case 2:
			*tGainMoney = 14000000;
			break;
		case 3:
			*tGainMoney = 15000000;
			break;
		case 4:
			*tGainMoney = 16000000;
			break;
		case 5:
			*tGainMoney = 17000000;
			break;
		}
		return;
	}
	switch (tStep)
	{
	case 1:
		*tGainExperience = 4625509;
		*tGainMoney = 26000000;
		break;
	case 2:
		*tGainExperience = 4625509;
		*tGainMoney = 27000000;
		break;
	case 3:
		*tGainExperience = 4625509;
		*tGainMoney = 28000000;
		break;
	case 4:
		*tGainExperience = 4625509;
		*tGainMoney = 29000000;
		break;
	case 5:
		*tGainExperience = 4625509;
		*tGainMoney = 30000000;
		break;
	}

#if 0
	switch (tLevel)
	{
	case 100:
		*tGainExperience = 49959;
		*tGainMoney = 5000000;
		break;
	case 101:
		*tGainExperience = 55443;
		*tGainMoney = 5000000;
		break;
	case 102:
		*tGainExperience = 59333;
		*tGainMoney = 5000000;
		break;
	case 103:
		*tGainExperience = 62405;
		*tGainMoney = 5000000;
		break;
	case 104:
		*tGainExperience = 64968;
		*tGainMoney = 5000000;
		break;
	case 105:
		*tGainExperience = 67180;
		*tGainMoney = 5000000;
		break;
	case 106:
		*tGainExperience = 69133;
		*tGainMoney = 5000000;
		break;
	case 107:
		*tGainExperience = 70887;
		*tGainMoney = 5000000;
		break;
	case 108:
		*tGainExperience = 72483;
		*tGainMoney = 5000000;
		break;
	case 109:
		*tGainExperience = 73949;
		*tGainMoney = 5000000;
		break;
	case 110:
		*tGainExperience = 75308;
		*tGainMoney = 5000000;
		break;
	case 111:
		*tGainExperience = 76575;
		*tGainMoney = 5000000;
		break;
	case 112:
		*tGainExperience = 1594846;
		*tGainMoney = 5000000;
		break;
	case 113:
		*tGainExperience = 206915;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 114:
		*tGainExperience = 229625;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 115:
		*tGainExperience = 245740;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 116:
		*tGainExperience = 258464;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 117:
		*tGainExperience = 269077;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 118:
		*tGainExperience = 278236;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 119:
		*tGainExperience = 286326;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 120:
		*tGainExperience = 293592;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 121:
		*tGainExperience = 300201;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 122:
		*tGainExperience = 306275;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 6000000;
			break;
		case 2:
			*tGainMoney = 6500000;
			break;
		}
		break;
	case 123:
		*tGainExperience = 311902;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 124:
		*tGainExperience = 317149;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 125:
		*tGainExperience = 322070;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 126:
		*tGainExperience = 326708;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 127:
		*tGainExperience = 331096;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 128:
		*tGainExperience = 335263;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 129:
		*tGainExperience = 339233;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 130:
		*tGainExperience = 343025;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 131:
		*tGainExperience = 346657;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 132:
		*tGainExperience = 350142;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 7000000;
			break;
		case 2:
			*tGainMoney = 7500000;
			break;
		case 3:
			*tGainMoney = 8000000;
			break;
		}
		break;
	case 133:
		*tGainExperience = 353494;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 134:
		*tGainExperience = 356723;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 135:
		*tGainExperience = 359839;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 136:
		*tGainExperience = 362851;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 137:
		*tGainExperience = 365766;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 138:
		*tGainExperience = 368592;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 139:
		*tGainExperience = 371332;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 140:
		*tGainExperience = 373996;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 141:
		*tGainExperience = 376583;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 142:
		*tGainExperience = 379103;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 8500000;
			break;
		case 2:
			*tGainMoney = 9000000;
			break;
		case 3:
			*tGainMoney = 9500000;
			break;
		case 4:
			*tGainMoney = 10000000;
			break;
		}
		break;
	case 143:
		*tGainExperience = 381556;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 10500000;
			break;
		case 2:
			*tGainMoney = 11000000;
			break;
		case 3:
			*tGainMoney = 11500000;
			break;
		case 4:
			*tGainMoney = 12000000;
			break;
		case 5:
			*tGainMoney = 12500000;
			break;
		}
		break;
	case 144:
		*tGainExperience = 383950;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 10500000;
			break;
		case 2:
			*tGainMoney = 11000000;
			break;
		case 3:
			*tGainMoney = 11500000;
			break;
		case 4:
			*tGainMoney = 12000000;
			break;
		case 5:
			*tGainMoney = 12500000;
			break;
		}
		break;
	case 145:
		*tGainExperience = 4625509;
		switch (tStep)
		{
		case 1:
			*tGainMoney = 10500000;
			break;
		case 2:
			*tGainMoney = 11000000;
			break;
		case 3:
			*tGainMoney = 11500000;
			break;
		case 4:
			*tGainMoney = 12000000;
			break;
		case 5:
			*tGainMoney = 12500000;
			break;
		}
		break;
	}
#endif
}

void MyGame::CheckUpdateCashItemInfo()
{
	if ((mTickCount % 120) == 0)
	{
		if (mEXTRA_COM.U_UPDATE_CASH_ITEM_INFO_FOR_EXTRA_SEND() == TRUE)
		{
			mCENTER_COM.W_UPDATE_CASH_ITEM_INFO_FOR_CENTER(0);
		}
	}
}

int MyGame::CheckMoveZoneForMoveZoneItem(int tTribe, int tLevel, int tZoneNumber)
{
	if (mSERVER_INFO.mServerNumber == tZoneNumber) {
		return 3;
	}

	int tCheckTribe = -1;
	int tCheckLevelMin = 1;

	switch (tZoneNumber)
	{
	case   1:
	case   2:
	case   3:
	case   4:
		tCheckTribe = 0;
		tCheckLevelMin = 1;
		break;
	case   6:
	case   7:
	case   8:
	case   9:
		tCheckTribe = 1;
		tCheckLevelMin = 1;
		break;
	case  11:
	case  12:
	case  13:
	case  14:
		tCheckTribe = 2;
		tCheckLevelMin = 1;
		break;
	case 140:
	case 141:
	case 142:
	case 143:
		tCheckTribe = 3;
		tCheckLevelMin = 113;
		break;
	case  40:
	case  43:
	case  56:
		tCheckTribe = 0;
		tCheckLevelMin = 90;
		break;
	case  41:
	case  44:
	case  57:
		tCheckTribe = 1;
		tCheckLevelMin = 90;
		break;
	case  42:
	case  45:
	case  58:
		tCheckTribe = 2;
		tCheckLevelMin = 90;
		break;
	case  38:
	case  55:
	case  89:
		tCheckTribe = -1;
		tCheckLevelMin = 90;
		break;
	case  75:
		tCheckTribe = -1;
		tCheckLevelMin = 146;
		break;
	case  90:
		tCheckTribe = -1;
		tCheckLevelMin = 150;
		break;
	case 201:
		tCheckTribe = -1;
		tCheckLevelMin = 154;
		break;
	default:
		return 3; 
	}

	if (tCheckTribe != -1) 
	{
		if ((tTribe == tCheckTribe) || (tTribe == ReturnAlliance(tCheckTribe))) {
			if (tLevel >= tCheckLevelMin) {
				return 0;
			}
			else {
				return 1;
			}
		}
		return 2;
	}
	else 
	{
		if (tLevel >= tCheckLevelMin) 
		{
			return 0;
		}
		else 
		{
			return 1;
		}
	}
}

#ifdef __GOD__
//PROCESS_ZONE_194
void MyGame::Process_Zone_194(void)
{
	int index01;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeUserNum[4];
	int tWinTribe;
	int tGainMoney;
	int tEventSort;
	int tEventValue;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone194PostTick++;
	switch (mWorldInfo.mZone194State)
	{
	case 0:
		switch (mZone194BattleState)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}
			if ((tPresentTime->tm_hour != 23) || (tPresentTime->tm_min > 10))
			{
				return;
			}
			mZone194PostTick = 0;
			mZone194BattleState = 1;
			return;
		case 1:
			mZone194PostTick = 0;
			mZone194BattleState = 2;
			mZone194RemainTime1 = 10;
			return;
		case 2:
			if ((mZone194PostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 201;
			CopyMemory(&tBroadcastInfoData[0], &mZone194RemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone194RemainTime1--;
			if (mZone194RemainTime1 == 0)
			{
				mZone194PostTick = 0;
				mZone194BattleState = 3;
			}
			return;
		case 3:
			if (mZone194PostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 202;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone194State = 1;
			mZone194PostTick = 0;
			mZone194BattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone194PostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 203;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone194State = 2;
		mZone194PostTick = 0;
		mZone194BattleState = 0;
		return;
	case 2:
		if (mZone194PostTick < (120 * 1))
		{
			if ((mZone194PostTick % 2) == 1)
			{
				mTRANSFER.B_194_BATTLE_COUNTDOWN((60 - (mZone194PostTick / 2)));
				mUTIL.Broadcast(FALSE, NULL, 1);
			}
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 204;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone194State = 3;
		mZone194PostTick = 0;
		mZone194BattleState = 0;
		mZone194RemainTime2 = 1200;
		mZone194BattleResult[0] = 0;
		mZone194BattleResult[1] = 0;
		mZone194BattleResult[2] = 0;
		mZone194BattleResult[3] = 0;
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 205;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone194State = 5;
			mZone194PostTick = 0;
			mZone194BattleState = 0;
			return;
		}
		mZone194RemainTime2--;
		if ((mZone194RemainTime2 % 2) != 0)
		{
			return;
		}
		mTRANSFER.B_194_BATTLE_INFO(&mZone194BattleResult[0]);
		mUTIL.Broadcast(FALSE, NULL, 1);
		tTribeUserNum[0] = 0;
		tTribeUserNum[1] = 0;
		tTribeUserNum[2] = 0;
		tTribeUserNum[3] = 0;
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
			switch (mAVATAR_OBJECT[index01].mDATA.aTribe)
			{
			case 0: tTribeUserNum[0]++; break;
			case 1: tTribeUserNum[1]++; break;
			case 2: tTribeUserNum[2]++; break;
			case 3: tTribeUserNum[3]++; break;
			}
		}
		tWinTribe = -1;
		if (mZone194RemainTime2 == 0)
		{
			if (tWinTribe == -1)
			{
				if ((mZone194BattleResult[0] > 0) && (mZone194BattleResult[0] > mZone194BattleResult[1]) && (mZone194BattleResult[0] > mZone194BattleResult[2]) && (mZone194BattleResult[0] > mZone194BattleResult[3]))
				{
					tWinTribe = 0;
				}
			}
			if (tWinTribe == -1)
			{
				if ((mZone194BattleResult[1] > 0) && (mZone194BattleResult[1] > mZone194BattleResult[0]) && (mZone194BattleResult[1] > mZone194BattleResult[2]) && (mZone194BattleResult[1] > mZone194BattleResult[3]))
				{
					tWinTribe = 1;
				}
			}
			if (tWinTribe == -1)
			{
				if ((mZone194BattleResult[2] > 0) && (mZone194BattleResult[2] > mZone194BattleResult[0]) && (mZone194BattleResult[2] > mZone194BattleResult[1]) && (mZone194BattleResult[2] > mZone194BattleResult[3]))
				{
					tWinTribe = 2;
				}
			}
			if (tWinTribe == -1)
			{
				if ((mZone194BattleResult[3] > 0) && (mZone194BattleResult[3] > mZone194BattleResult[0]) && (mZone194BattleResult[3] > mZone194BattleResult[1]) && (mZone194BattleResult[3] > mZone194BattleResult[2]))
				{
					tWinTribe = 3;
				}
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 206;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone194State = 4;
			mZone194PostTick = 0;
			mZone194BattleState = 0;
			if (tWinTribe == -1)
			{
				return;
			}
		}
		else
		{
			if (tWinTribe == -1)
			{
				if ((tTribeUserNum[0] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
				{
					tWinTribe = 0;
				}
			}
			if (tWinTribe == -1)
			{
				if ((tTribeUserNum[1] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
				{
					tWinTribe = 1;
				}
			}
			if (tWinTribe == -1)
			{
				if ((tTribeUserNum[2] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[3] == 0))
				{
					tWinTribe = 2;
				}
			}
			if (tWinTribe == -1)
			{
				if ((tTribeUserNum[3] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0))
				{
					tWinTribe = 3;
				}
			}
			if (tWinTribe == -1)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 206;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone194State = 4;
			mZone194PostTick = 0;
			mZone194BattleState = 0;
		}
		//----------------//
		//BATTLE_WIN_BONUS//
		//----------------//
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
			/*if (mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe)
			{
				continue;
			}*/
			tGainMoney = 30000000;
			if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
			{
				mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
			if (mAVATAR_OBJECT[index01].mDATA.aTribe == tWinTribe)
			{
				mUSER[index01].mAvatarInfo.aKillOtherTribe += 300;
				mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 300;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.ProcessForDropItem(3, 1437, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			}
			else
			{
				mUSER[index01].mAvatarInfo.aKillOtherTribe += 100;
				mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 100;
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		//----------------//
		//----------------//
		//----------------//
#if 0
		switch ((rand() % 4))
		{
		case 0:
			switch (tWinTribe)
			{
			case 0: //[21]
				tEventSort = 21;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 1: //[22]
				tEventSort = 22;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 2: //[23]
				tEventSort = 23;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 3: //[24]
				tEventSort = 24;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			}
			break;
		case 1:
			switch (tWinTribe)
			{
			case 0: //[31]
				tEventSort = 31;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 1: //[32]
				tEventSort = 32;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 2: //[33]
				tEventSort = 33;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 3: //[34]
				tEventSort = 34;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			}
			break;
		case 2:
			switch (tWinTribe)
			{
			case 0: //[41]
				tEventSort = 41;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 1: //[42]
				tEventSort = 42;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 2: //[43]
				tEventSort = 43;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 3: //[44]
				tEventSort = 44;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			}
			break;
		case 3:
			switch (tWinTribe)
			{
			case 0: //[51]
				tEventSort = 51;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 1: //[52]
				tEventSort = 52;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 2: //[53]
				tEventSort = 53;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			case 3: //[54]
				tEventSort = 54;
				tEventValue = 1;
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 301;
				CopyMemory(&tBroadcastInfoData[0], &tEventSort, 4);
				CopyMemory(&tBroadcastInfoData[4], &tEventValue, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				break;
			}
			break;
		}
#endif
		return;
	case 4:
		if (mZone194PostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 207;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone194State = 5;
		mZone194PostTick = 0;
		mZone194BattleState = 0;
		return;
	case 5:
		if (mZone194PostTick < (120 * 1))
		{
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (mAVATAR_OBJECT[index01].mCheckValidState)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 208;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone194State = 0;
		mZone194PostTick = 0;
		mZone194BattleState = 0;
		return;
	}
}
//PROCESS_ZONE_195
void MyGame::Process_Zone_195(void)
{
	int index01, iTribe;
	int tZone;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone195PostTick++;
	switch (mZone195BattleState)
	{
	case 0:
		if (mZone195PostAvatarIndex == -1)
		{
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
				if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
				{
					continue;
				}
				if (((mAVATAR_OBJECT[index01].mDATA.aTribe + 1) == mWorldInfo.mProvingGroundsState[mZone195LevelState]) || ((mAVATAR_OBJECT[index01].mDATA.aTribe + 1) == ReturnAllianceTribe(mWorldInfo.mProvingGroundsState[mZone195LevelState])))
				{
					continue;
				}
				if (!mUTIL.CheckInRange(&mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mZone195BattlePostLocation[0], mZone195BattlePostRadius))
				{
					continue;
				}
				break;
			}
			if (index01 == mSERVER.mMAX_USER_NUM)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 771;
			iTribe = static_cast<int> (mAVATAR_OBJECT[index01].mDATA.aTribe);
			tZone = mSERVER_INFO.mServerNumber;
			CopyMemory(&tBroadcastInfoData[0], &iTribe, 4);
			CopyMemory(&tBroadcastInfoData[4], &tZone, 4);
			CopyMemory(&tBroadcastInfoData[8], &mAVATAR_OBJECT[index01].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone195PostTick = 0;
			mZone195RemainTime = 5;
			mZone195PostAvatarIndex = index01;
			mZone195PostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
			return;
		}
		if ((!mAVATAR_OBJECT[mZone195PostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone195PostAvatarIndex].mUniqueNumber != mZone195PostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aLifeValue < 1) || (!mUTIL.CheckInRange(&mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aAction.aLocation[0], &mZone195BattlePostLocation[0], mZone195BattlePostRadius)) || (mUSER[mZone195PostAvatarIndex].mMoveZoneResult == 1) || (mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aVisibleState == 0) || (mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aAction.aSort == 33))
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 772;
			tZone = mSERVER_INFO.mServerNumber;
			CopyMemory(&tBroadcastInfoData[0], &tZone, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone195PostAvatarIndex = -1;
			mZone195PostAvatarUniqueNumber = 0;
			return;
		}
		if ((mZone195PostTick % 120) != 20)
		{
			return;
		}
		if (mZone195RemainTime > 0)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 773;
			tZone = mSERVER_INFO.mServerNumber;
			CopyMemory(&tBroadcastInfoData[0], &mZone195RemainTime, 4);
			CopyMemory(&tBroadcastInfoData[4], &tZone, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone195RemainTime--;
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 774;
		iTribe = static_cast<int> (mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aTribe);
		tZone = mSERVER_INFO.mServerNumber;
		CopyMemory(&tBroadcastInfoData[0], &iTribe, 4);
		CopyMemory(&tBroadcastInfoData[4], &tZone, 4);
		CopyMemory(&tBroadcastInfoData[8], &mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&tBroadcastInfoData[8 + MAX_AVATAR_NAME_LENGTH], &mZone195LevelState, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mProvingGroundsState[mZone195LevelState] = (mAVATAR_OBJECT[mZone195PostAvatarIndex].mDATA.aTribe + 1);
		mWorldInfo.mProvingGroundsPoint[0] = mUTIL.CheckPVNumber(0);
		mWorldInfo.mProvingGroundsPoint[1] = mUTIL.CheckPVNumber(1);
		mWorldInfo.mProvingGroundsPoint[2] = mUTIL.CheckPVNumber(2);
		mWorldInfo.mProvingGroundsPoint[3] = mUTIL.CheckPVNumber(3);
		mZone195PostTick = 0;
		mZone195PostAvatarIndex = -1;
		mZone195PostAvatarUniqueNumber = 0;
		mZone195BattleState = 0;

		// Broadcast New Conquer Info
		CopyMemory(&tBroadcastInfoData[4], &iTribe, 4);
		CopyMemory(&tBroadcastInfoData[8], &tZone, 4);
		CopyMemory(&tBroadcastInfoData[12], &mWorldInfo.mProvingGroundsPoint, 16);
		CopyMemory(&tBroadcastInfoData[28], &mWorldInfo.mProvingGroundsState, 36);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(751, &tBroadcastInfoData[0]);
		return;
	}
}
//PROCESS_ZONE_200
void MyGame::Process_Zone_200(void)
{
	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeUserKillNum[4];
	int tWinTribe;
	int tGainExperience;
	int tGainMoney;
	time_t tCountSeconds;
	struct tm* tPresentTime;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone200PostTick++;
	switch (mGAME.mWorldInfo.mZone200TypeState)
	{
	case 0:
		time(&tCountSeconds);
		tPresentTime = localtime(&tCountSeconds);
		if (tPresentTime == NULL)
		{
			return;
		}
		if ((tPresentTime->tm_hour % 3 != 0) || (tPresentTime->tm_min > 10))
		{
			return;
		}
		// Reset any players that might still be inside
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (mAVATAR_OBJECT[index01].mCheckValidState)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
		mZone200PostTick = 0;
		mWorldInfo.mZone200TypeState = 1;
		mZone200RemainTime1 = 5;
		// Broadcasst
		CopyMemory(&tBroadcastInfoData[0], &mZone200RemainTime1, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(659, &tBroadcastInfoData[0]);
		return;

	case 1:
		if ((mZone200PostTick % (120 * 1)) != 0)
		{
			return;
		}
		mZone200RemainTime1--;
		if (mZone200RemainTime1 == 0)
		{
			mZone200PostTick = 0;
			mWorldInfo.mZone200TypeState = 2;
			mZone200RemainTime1 = 5;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(660, &tBroadcastInfoData[0]);
			return;
		}
		// Broadcast Info
		CopyMemory(&tBroadcastInfoData[0], &mZone200RemainTime1, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(659, &tBroadcastInfoData[0]);
		return;

	case 2:
		if (mZone200PostTick < (120 * 1))
		{
			return;
		}
		if (mZone200RemainTime1 == 0)
		{
			mZone200PostTick = 0;
			mWorldInfo.mZone200TypeState = 3;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 20;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(662, &tBroadcastInfoData[0]);
			return;
		}
		// Broadcast
		CopyMemory(&tBroadcastInfoData[0], &mZone200RemainTime1, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(661, &tBroadcastInfoData[0]);
		mZone200RemainTime1--;
		return;

	case 3:
		if ((mZone200PostTick % 2) == 0)
		{
			mTRANSFER.B_REMAIN_TIME_RECV(mZone200RemainTime2);
			mUTIL.Broadcast(FALSE, NULL, 0);
		}
		mZone200RemainTime2--;
		if (mZone200RemainTime2 == 0)
		{
			mZone200MonsterCount[0] = 170;
			mZone200MonsterCount[1] = 170;
			mZone200MonsterCount[2] = 170;
			mZone200MonsterCount[3] = 170;
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
			mSUMMON.SummonMonsterWithoutTimeLimit();
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			mWorldInfo.mZone200TypeState = 4;
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(663, &tBroadcastInfoData[0]);
			return;
		}
		return;

	case 4:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			// Broadcast
			mWorldInfo.mZone200TypeState = 0;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			mSUMMON.DeleteMonster();
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(669, &tBroadcastInfoData[0]);
			return;
		}
		// End VOD after 1 hour when it is still not finished
		if (mZone200PostTick == (120 * 60))
		{
			mWorldInfo.mZone200TypeState = 0;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			mSUMMON.DeleteMonster();
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(669, &tBroadcastInfoData[0]);
			return;
		}
		if ((mZone200PostTick % 5) == 0)
		{
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
		}
		if (mZone200MonsterCount[0] > 0 && mZone200MonsterCount[1] > 0 && mZone200MonsterCount[2] > 0 && mZone200MonsterCount[3] > 0)
		{
			return;
		}
		if (mZone200MonsterCount[0] == 0 && mZone200MonsterCount[1] > 0 && mZone200MonsterCount[2] > 0 && mZone200MonsterCount[3] > 0)
		{
			tWinTribe = 0;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(666, &tBroadcastInfoData[0]);
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
			mWorldInfo.mZone200TypeState = 5;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			return;
		}
		if (mZone200MonsterCount[0] > 0 && mZone200MonsterCount[1] == 0 && mZone200MonsterCount[2] > 0 && mZone200MonsterCount[3] > 0)
		{
			tWinTribe = 1;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(666, &tBroadcastInfoData[0]);
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
			mWorldInfo.mZone200TypeState = 5;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			return;
		}
		if (mZone200MonsterCount[0] > 0 && mZone200MonsterCount[1] > 0 && mZone200MonsterCount[2] == 0 && mZone200MonsterCount[3] > 0)
		{
			tWinTribe = 2;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(666, &tBroadcastInfoData[0]);
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
			mWorldInfo.mZone200TypeState = 5;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			return;
		}
		if (mZone200MonsterCount[0] > 0 && mZone200MonsterCount[1] > 0 && mZone200MonsterCount[2] > 0 && mZone200MonsterCount[3] == 0)
		{
			tWinTribe = 3;
			CopyMemory(&tBroadcastInfoData[0], &tWinTribe, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(666, &tBroadcastInfoData[0]);
			mTRANSFER.B_VOD_BATTLE_INFO(&mZone200MonsterCount[0]);
			mUTIL.Broadcast(FALSE, NULL, 0, false);
			mWorldInfo.mZone200TypeState = 5;
			mZone200PostTick = 0;
			mZone200RemainTime1 = 0;
			mZone200RemainTime2 = 0;
			return;
		}
		return;

	case 5:
		mZone200PostTick = 0;
		mZone200RemainTime1 = 0;
		mZone200RemainTime2 = 0;
		mWorldInfo.mZone200TypeState = 6;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(667, &tBroadcastInfoData[0]);
		return;

	case 6:
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 43))
			{
				break;
			}
		}
		if (index01 < MAX_MONSTER_OBJECT_NUM)
		{
			return;
		}
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
			// Rewards
			mUTIL.ProcessForDropItem(3, 531, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(3, 531, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(3, 531, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(3, 531, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(3, 531, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUTIL.ProcessForDropItem(3, 1072, 1, 0, 0, &mAVATAR_OBJECT[index01].mDATA.aAction.aLocation[0], &mUSER[index01].mAvatarInfo.aName[0], "", 0, mUSER[index01].mAvatarInfo.aTribe, 0);
			mUSER[index01].mAvatarInfo.aKillOtherTribe += 100;
			mAVATAR_OBJECT[index01].mDATA.aKillOtherTribe += 100;
			mTRANSFER.B_AVATAR_CHANGE_INFO_2(3, mUSER[index01].mAvatarInfo.aKillOtherTribe);
			mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
		}
		mZone200PostTick = 0;
		mZone200RemainTime1 = 0;
		mZone200RemainTime2 = 0;
		mWorldInfo.mZone200TypeState = 7;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(668, &tBroadcastInfoData[0]);
		return;

	case 7:
		if (mZone200PostTick < (60 * 1))
		{
			return;
		}
		mSUMMON.DeleteMonster();
		mZone200PostTick = 0;
		mZone200RemainTime1 = 0;
		mZone200RemainTime2 = 0;
		mWorldInfo.mZone200TypeState = 0;
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(669, &tBroadcastInfoData[0]);
		return;

	}
}
//PROCESS_ZONE_241
void MyGame::Process_Zone_241(void)
{
	int index01, iTribe;
	int tZone;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone241PostTick++;
	switch (mWorldInfo.mLifeOrDeathState[mZone241Type])
	{
	case 0:
		if (mZone241PostAvatarIndex == -1)
		{
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
				break;
			}
			if (index01 == mSERVER.mMAX_USER_NUM)
			{
				return;
			}
			mZone241PostTick = 0;
			mWorldInfo.mLifeOrDeathState[mZone241Type] = 1;
			mZone241RemainTime = 3600;
			mZone241PostAvatarIndex = index01;
			mZone241PostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
			mSUMMON.SummonMonsterWithoutTimeLimit();
			// Broadcast
			CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
			CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[index01].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(411, &tBroadcastInfoData[0]);
			return;
		}
		return;

	case 1:
		if ((!mAVATAR_OBJECT[mZone241PostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone241PostAvatarIndex].mUniqueNumber != mZone241PostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aVisibleState == 0) || (mUSER[mZone241PostAvatarIndex].mMoveZoneResult))
		{
			// Broadcast
			CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
			CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(413, &tBroadcastInfoData[0]);

			mSUMMON.DeleteMonster();
			mZone241PostAvatarIndex = -1;
			mZone241PostAvatarUniqueNumber = 0;
			mZone241PostTick = 0;
			mWorldInfo.mLifeOrDeathState[mZone241Type] = 2;
			
			return;
		}
		if (mZone241RemainTime > 0)
		{
			mZone241RemainTime--;
			if (mZone241RemainTime == 0)
			{
				mWorldInfo.mLifeOrDeathState[mZone241Type] = 2;
				mZone241PostTick = 0;
				mSUMMON.DeleteMonster();
				// Broadcast
				CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
				CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(413, &tBroadcastInfoData[0]);
				return;
			}
			if ((mZone241RemainTime % 10) == 0)
			{
				mTRANSFER.B_REMAIN_TIME_RECV(mZone241RemainTime);
				mUSER[mZone241PostAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
			}
		}
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 46))
			{
				break;
			}
		}
		if (index01 < MAX_MONSTER_OBJECT_NUM)
		{
			return;
		}
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 2;
		mZone241PostTick = 0;
		// Broadcast
		CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
		CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(414, &tBroadcastInfoData[0]);
		return;

	case 2:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			mZone241PostAvatarIndex = -1;
			mZone241PostAvatarUniqueNumber = 0;
			mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
			mZone241PostTick = 0;
			CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(415, &tBroadcastInfoData[0]);
			return;
		}
		if (mZone241PostTick < (120 * 1))
		{
			return;
		}
		mZone241PostAvatarIndex = -1;
		mZone241PostAvatarUniqueNumber = 0;
		mWorldInfo.mLifeOrDeathState[mZone241Type] = 0;
		mZone241PostTick = 0;
		CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(415, &tBroadcastInfoData[0]);
		return;
	}
}
//PROCESS_ZONE_241
//void MyGame::Process_Zone_241(void)
//{
//	int index01, iTribe;
//	int tZone;
//	int tBroadcastInfoSort;
//	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
//
//	if (!mCheckActiveBattleLogic)
//	{
//		return;
//	}
//	mZone241PostTick++;
//	switch (mWorldInfo.mLifeOrDeathState[mZone241Type])
//	{
//	case 0:
//		if (mZone241PostAvatarIndex == -1)
//		{
//			for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
//			{
//				if (!mAVATAR_OBJECT[index01].mCheckValidState)
//				{
//					continue;
//				}
//				if (mUSER[index01].mMoveZoneResult == 1)
//				{
//					continue;
//				}
//				if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
//				{
//					continue;
//				}
//				if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
//				{
//					continue;
//				}
//				if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
//				{
//					continue;
//				}
//				break;
//			}
//			if (index01 == mSERVER.mMAX_USER_NUM)
//			{
//				return;
//			}
//			//--------------//
//			//BROADCAST_INFO//
//			//--------------//
//			tBroadcastInfoSort = 411;
//			CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
//			CopyMemory(&tBroadcastInfoData[4], &mZone241Type, 4);
//			CopyMemory(&tBroadcastInfoData[8], &mAVATAR_OBJECT[index01].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
//			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//			//--------------//
//			//--------------//
//			//--------------//
//			mZone241PostTick = 0;
//			mZone241RemainTime = 3600;
//			mZone241PostAvatarIndex = index01;
//			mZone241PostAvatarUniqueNumber = mAVATAR_OBJECT[index01].mUniqueNumber;
//			mSUMMON.SummonMonsterWithoutTimeLimit();
//			return;
//		}
//		if ((!mAVATAR_OBJECT[mZone241PostAvatarIndex].mCheckValidState) || (mAVATAR_OBJECT[mZone241PostAvatarIndex].mUniqueNumber != mZone241PostAvatarUniqueNumber) || (mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aVisibleState == 0) || (mUSER[mZone241PostAvatarIndex].mMoveZoneResult))
//		{
//			//--------------//
//			//BROADCAST_INFO//
//			//--------------//
//			tBroadcastInfoSort = 413;
//			CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
//			CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
//			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//			//--------------//
//			//--------------//
//			//--------------//
//			mSUMMON.DeleteMonster();
//			mZone241PostAvatarIndex = -1;
//			mZone241PostAvatarUniqueNumber = 0;
//			mZone241PostTick = 0;
//			mZone241BattleState[mZone241Type] = 0;
//			return;
//		}
//		if (mZone241RemainTime > 0)
//		{
//			mZone241RemainTime--;
//			if (mZone241RemainTime == 0)
//			{
//				tBroadcastInfoSort = 413;
//				CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
//				CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
//				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//				mZone241BattleState[mZone241Type] = 1;
//				mZone241PostTick = 0;
//				mSUMMON.DeleteMonster();
//				return;
//			}
//			if ((mZone241RemainTime % 10) == 0)
//			{
//				mTRANSFER.B_REMAIN_TIME_RECV(mZone241RemainTime);
//				mUSER[mZone241PostAvatarIndex].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
//			}
//		}
//		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
//		{
//			if (!mMONSTER_OBJECT[index01].mCheckValidState)
//			{
//				continue;
//			}
//			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mSpecialType == 46))
//			{
//				break;
//			}
//		}
//		if (index01 < MAX_MONSTER_OBJECT_NUM)
//		{
//			return;
//		}
//		tBroadcastInfoSort = 414;
//		CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
//		CopyMemory(&tBroadcastInfoData[4], &mAVATAR_OBJECT[mZone241PostAvatarIndex].mDATA.aName[0], MAX_AVATAR_NAME_LENGTH);
//		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//		mWorldInfo.mLifeOrDeathState[mZone241Type] = 1;
//		mZone241PostTick = 0;
//		return;
//
//	case 1:
//		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
//		{
//			if (!mAVATAR_OBJECT[index01].mCheckValidState)
//			{
//				continue;
//			}
//			if (mUSER[index01].mMoveZoneResult == 1)
//			{
//				continue;
//			}
//			if (mAVATAR_OBJECT[index01].mDATA.aVisibleState == 0)
//			{
//				continue;
//			}
//			if (mAVATAR_OBJECT[index01].mDATA.aLifeValue < 1)
//			{
//				continue;
//			}
//			if (mAVATAR_OBJECT[index01].mDATA.aAction.aSort == 33)
//			{
//				continue;
//			}
//			break;
//		}
//		if (index01 == mSERVER.mMAX_USER_NUM)
//		{
//			mZone241PostAvatarIndex = -1;
//			mZone241PostAvatarUniqueNumber = 0;
//			mZone241BattleState[mZone241Type] = 0;
//			mZone241PostTick = 0;
//			return;
//		}
//		if (mZone241PostTick < (120 * 1))
//		{
//			return;
//		}
//		mZone241BattleState[mZone241Type] = 2;
//		return;
//
//	case 2:
//		//Returning Home
//		tBroadcastInfoSort = 415;
//		CopyMemory(&tBroadcastInfoData[0], &mZone241Type, 4);
//		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
//		mZone241PostAvatarIndex = -1;
//		mZone241PostAvatarUniqueNumber = 0;
//		mZone241BattleState[mZone241Type] = 0;
//		mZone241PostTick = 0;
//		return;
//	}
//}
//PROCESS_ZONE_267_TYPE
void MyGame::Process_Zone_267(void)
{
	int index01;
	time_t tCountSeconds;
	struct tm* tPresentTime;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeUserNum[4];
	int tWinTribe;
	int tGainExperience;
	int tGainMoney;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone267TypePostTick++;
	switch (mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex])
	{
	case 0:
		switch (mZone267TypeBattleState)
		{
		case 0:
			time(&tCountSeconds);
			tPresentTime = localtime(&tCountSeconds);
			if (tPresentTime == NULL)
			{
				return;
			}
			if ((tPresentTime->tm_hour != 20) || (tPresentTime->tm_min > 10))
			{
				return;
			}
			mZone267TypePostTick = 0;
			mZone267TypeBattleState = 1;
			mZone267TypeRemainTime1 = 10;
			return;
		case 1:
			if ((mZone267TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 402;
			CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone267TypeRemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone267TypeRemainTime1--;
			if (mZone267TypeRemainTime1 == 0)
			{
				mZone267TypePostTick = 0;
				mZone267TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone267TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 403;
			CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 1;
			mZone267TypePostTick = 0;
			mZone267TypeBattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone267TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 404;
		CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 2;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		return;
	case 2:
		if (mZone267TypePostTick < (120 * 1))
		{
			return;
		}
		mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 3;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		mZone267TypeRemainTime2 = 1800;
		mZone267TypeBattleResult[0] = 0;
		mZone267TypeBattleResult[1] = 0;
		mZone267TypeBattleResult[2] = 0;
		mZone267TypeBattleResult[3] = 0;
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 405;
		CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone267TypeRemainTime2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 406;
			CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 5;
			mZone267TypePostTick = 0;
			mZone267TypeBattleState = 0;
			return;
		}
		mZone267TypeRemainTime2--;
		if ((mZone267TypeRemainTime2 % 10) != 0)
		{
			return;
		}
		mTRANSFER.B_267_TYPE_BATTLE_INFO(&mZone267TypeBattleResult[0], mZone267TypeRemainTime2);
		mUTIL.Broadcast(FALSE, NULL, 1);
		tTribeUserNum[0] = 0;
		tTribeUserNum[1] = 0;
		tTribeUserNum[2] = 0;
		tTribeUserNum[3] = 0;
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
			switch (mAVATAR_OBJECT[index01].mDATA.aTribe)
			{
			case 0: tTribeUserNum[0]++; break;
			case 1: tTribeUserNum[1]++; break;
			case 2: tTribeUserNum[2]++; break;
			case 3: tTribeUserNum[3]++; break;
			}
		}
		tWinTribe = -1;
		if (mZone267TypeRemainTime2 == 0)
		{
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(0))
				{
				case 1:
					if ((mZone267TypeBattleResult[0] > mZone267TypeBattleResult[2]) && (mZone267TypeBattleResult[0] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 0;
					}
					break;
				case 2:
					if ((mZone267TypeBattleResult[0] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[0] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 0;
					}
					break;
				case 3:
					if ((mZone267TypeBattleResult[0] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[0] > mZone267TypeBattleResult[2]))
					{
						tWinTribe = 0;
					}
					break;
				default:
					if ((mZone267TypeBattleResult[0] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[0] > mZone267TypeBattleResult[2]) && (mZone267TypeBattleResult[0] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 0;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(1))
				{
				case 0:
					if ((mZone267TypeBattleResult[1] > mZone267TypeBattleResult[2]) && (mZone267TypeBattleResult[1] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 1;
					}
					break;
				case 2:
					if ((mZone267TypeBattleResult[1] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[1] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 1;
					}
					break;
				case 3:
					if ((mZone267TypeBattleResult[1] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[1] > mZone267TypeBattleResult[2]))
					{
						tWinTribe = 1;
					}
					break;
				default:
					if ((mZone267TypeBattleResult[1] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[1] > mZone267TypeBattleResult[2]) && (mZone267TypeBattleResult[1] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 1;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(2))
				{
				case 0:
					if ((mZone267TypeBattleResult[2] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[2] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 2;
					}
					break;
				case 1:
					if ((mZone267TypeBattleResult[2] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[2] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 2;
					}
					break;
				case 3:
					if ((mZone267TypeBattleResult[2] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[2] > mZone267TypeBattleResult[1]))
					{
						tWinTribe = 2;
					}
					break;
				default:
					if ((mZone267TypeBattleResult[2] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[2] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[2] > mZone267TypeBattleResult[3]))
					{
						tWinTribe = 2;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(3))
				{
				case 0:
					if ((mZone267TypeBattleResult[3] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[3] > mZone267TypeBattleResult[2]))
					{
						tWinTribe = 3;
					}
					break;
				case 1:
					if ((mZone267TypeBattleResult[3] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[3] > mZone267TypeBattleResult[2]))
					{
						tWinTribe = 3;
					}
					break;
				case 2:
					if ((mZone267TypeBattleResult[3] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[3] > mZone267TypeBattleResult[1]))
					{
						tWinTribe = 3;
					}
					break;
				default:
					if ((mZone267TypeBattleResult[3] > mZone267TypeBattleResult[0]) && (mZone267TypeBattleResult[3] > mZone267TypeBattleResult[1]) && (mZone267TypeBattleResult[3] > mZone267TypeBattleResult[2]))
					{
						tWinTribe = 3;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				//--------------//
				//BROADCAST_INFO//
				//--------------//
				tBroadcastInfoSort = 407;
				CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
				mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
				//--------------//
				//--------------//
				//--------------//
				mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 5;
				mZone267TypePostTick = 0;
				mZone267TypeBattleState = 0;
				return;
			}
		}
		else
		{
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(0))
				{
				case 1:
					if ((tTribeUserNum[0] > 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 0;
					}
					break;
				case 2:
					if ((tTribeUserNum[0] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 0;
					}
					break;
				case 3:
					if ((tTribeUserNum[0] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0))
					{
						tWinTribe = 0;
					}
					break;
				default:
					if ((tTribeUserNum[0] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 0;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(1))
				{
				case 0:
					if ((tTribeUserNum[1] > 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 1;
					}
					break;
				case 2:
					if ((tTribeUserNum[1] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 1;
					}
					break;
				case 3:
					if ((tTribeUserNum[1] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[2] == 0))
					{
						tWinTribe = 1;
					}
					break;
				default:
					if ((tTribeUserNum[1] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[2] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 1;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(2))
				{
				case 0:
					if ((tTribeUserNum[2] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 2;
					}
					break;
				case 1:
					if ((tTribeUserNum[2] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 2;
					}
					break;
				case 3:
					if ((tTribeUserNum[2] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0))
					{
						tWinTribe = 2;
					}
					break;
				default:
					if ((tTribeUserNum[2] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[3] == 0))
					{
						tWinTribe = 2;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				switch (ReturnAllianceTribe(3))
				{
				case 0:
					if ((tTribeUserNum[3] > 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0))
					{
						tWinTribe = 3;
					}
					break;
				case 1:
					if ((tTribeUserNum[3] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[2] == 0))
					{
						tWinTribe = 3;
					}
					break;
				case 2:
					if ((tTribeUserNum[3] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0))
					{
						tWinTribe = 3;
					}
					break;
				default:
					if ((tTribeUserNum[3] > 0) && (tTribeUserNum[0] == 0) && (tTribeUserNum[1] == 0) && (tTribeUserNum[2] == 0))
					{
						tWinTribe = 3;
					}
					break;
				}
			}
			if (tWinTribe == -1)
			{
				return;
			}
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 408;
		CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &tWinTribe, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 4;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		//----------------//
		//BATTLE_WIN_BONUS//
		//----------------//
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
			if ((mAVATAR_OBJECT[index01].mDATA.aTribe != tWinTribe) && (mAVATAR_OBJECT[index01].mDATA.aTribe != ReturnAllianceTribe(tWinTribe)))
			{
				ReturnLevelWarReward3(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney);
				tGainExperience /= 2;
				tGainMoney /= 2;
				if (tGainExperience < 1)
				{
					continue;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);
				if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
				{
					mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
					mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
			else
			{
				ReturnLevelWarReward3(mAVATAR_OBJECT[index01].mDATA.aLevel1, mAVATAR_OBJECT[index01].mDATA.aLevel2, &tGainExperience, &tGainMoney);
				if (tGainExperience < 1)
				{
					continue;
				}
				mTRANSFER.B_AVATAR_CHANGE_INFO_2(1, tGainExperience);
				mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				mUTIL.ProcessForExperience(index01, tGainExperience, 0, 0);
				if (!mUTIL.CheckOverMaximum(mUSER[index01].mAvatarInfo.aMoney, tGainMoney))
				{
					mUSER[index01].mAvatarInfo.aMoney += tGainMoney;
					mTRANSFER.B_AVATAR_CHANGE_INFO_2(23, tGainMoney);
					mUSER[index01].Send(TRUE, (char*)&mTRANSFER.mOriginal[0], mTRANSFER.mOriginalSize);
				}
			}
		}
		//----------------//
		//----------------//
		//----------------//
		return;
	case 4:
		if (mZone267TypePostTick < (120 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 409;
		CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 5;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		return;
	case 5:
		if (mZone267TypePostTick < (120 * 1))
		{
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 410;
		CopyMemory(&tBroadcastInfoData[0], &mZone267TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone267TypeState[mZone267TypeZoneIndex] = 0;
		mZone267TypePostTick = 0;
		mZone267TypeBattleState = 0;
		return;
	}
}
void MyGame::Process_Zone_319_TYPE(void)
{
	int index01;
	int tBroadcastInfoSort;
	BYTE tBroadcastInfoData[MAX_BROADCAST_INFO_SIZE];
	int tTribeUserNum[4];
	int tWinTribe;
	int tGainExperience;
	int tGainMoney;
	int tMedalCnt = 0;

	if (!mCheckActiveBattleLogic)
	{
		return;
	}
	mZone319TypePostTick++;
	switch (mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex])
	{
	case 0:
		switch (mZone319TypeBattleState)
		{
		case 0:
			if (mZone319TypePostTick < (120 * 5))
			{
				return;
			}
			mZone319TypePostTick = 0;
			mZone319TypeBattleState = 1;
			mZone319TypeRemainTime1 = 10;
			return;
		case 1:
			if ((mZone319TypePostTick % (120 * 1)) != 0)
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 755;
			CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
			CopyMemory(&tBroadcastInfoData[4], &mZone319TypeRemainTime1, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mZone319TypeRemainTime1--;
			if (mZone319TypeRemainTime1 == 0)
			{
				mZone319TypePostTick = 0;
				mZone319TypeBattleState = 2;
			}
			return;
		case 2:
			if (mZone319TypePostTick < (120 * 1))
			{
				return;
			}
			//--------------//
			//BROADCAST_INFO//
			//--------------//
			tBroadcastInfoSort = 756;
			CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			//--------------//
			//--------------//
			//--------------//
			mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 1;
			mZone319TypePostTick = 0;
			mZone319TypeBattleState = 0;
			return;
		}
		return;
	case 1:
		if (mZone319TypePostTick < (120 * 3))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 757;
		CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 2;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		return;
	case 2:
		if (mZone319TypePostTick < (120 * 1))
		{
			return;
		}
		mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 3;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime2 = 1800;
		//--------------//
		//SUMMON_MONSTER//
		//--------------//
		mSUMMON.SummonMonsterWithoutTimeLimit();
		//--------------//
		//--------------//
		//--------------//
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 758;
		CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
		CopyMemory(&tBroadcastInfoData[4], &mZone319TypeRemainTime2, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		return;
	case 3:
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
			break;
		}
		if (index01 == mSERVER.mMAX_USER_NUM)
		{
			mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 4;
			mZone319TypePostTick = 0;
			mZone319TypeBattleState = 0;
			tBroadcastInfoSort = 761;
			CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
			ZeroMemory(&tBroadcastInfoData[4], 4);
			ZeroMemory(&tBroadcastInfoData[8], 80);
			ZeroMemory(&tBroadcastInfoData[88], 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			return;
		}
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}
			if (mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == 287)
			{
				break;
			}
		}
		if (index01 == MAX_MONSTER_OBJECT_NUM)
		{
			mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 4;
			mZone319TypePostTick = 0;
			mZone319TypeBattleState = 0;
			mZone319TypeRemainTime2 = 0;
			tBroadcastInfoSort = 761;
			CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
			ZeroMemory(&tBroadcastInfoData[4], 4);
			ZeroMemory(&tBroadcastInfoData[8], 80);
			ZeroMemory(&tBroadcastInfoData[88], 4);
			mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
			return;
		}
		if ((mZone319TypePostTick % 10) == 0) 
		{
			mTRANSFER.B_REMAIN_TIME_RECV(mZone319TypeRemainTime2);
			mUTIL.Broadcast(FALSE, 0, 0);
		}
		mZone319TypeRemainTime2--;
		if (mZone319TypeRemainTime2 != 0)
		{
			return;
		}
		mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 4;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		mZone319TypeRemainTime2 = 0;
		tBroadcastInfoSort = 761;
		CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
		ZeroMemory(&tBroadcastInfoData[4], 4);
		ZeroMemory(&tBroadcastInfoData[8], 80);
		ZeroMemory(&tBroadcastInfoData[88], 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		return;
	case 4:
		if (mZone319TypePostTick < (60 * 1))
		{
			return;
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 762;
		CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 5;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		//--------------//
		//DELETE_MONSTER//
		//--------------//
		mSUMMON.DeleteMonster();
		//--------------//
		//--------------//
		//--------------//
		return;
	case 5:
		if (mZone319TypePostTick < (120 * 180)) // Cooldown
		{
			return;
		}
		for (index01 = 0; index01 < mSERVER.mMAX_USER_NUM; index01++)
		{
			if (mAVATAR_OBJECT[index01].mCheckValidState)
			{
				mUSER[index01].Quit(__FILE__, __FUNCTION__, __LINE__);
			}
		}
		//--------------//
		//BROADCAST_INFO//
		//--------------//
		tBroadcastInfoSort = 763;
		CopyMemory(&tBroadcastInfoData[0], &mZone319TypeZoneIndex, 4);
		mCENTER_COM.U_DEMAND_BROADCAST_INFO(tBroadcastInfoSort, &tBroadcastInfoData[0]);
		//--------------//
		//--------------//
		//--------------//
		mWorldInfo.mZone319TypeState[mZone319TypeZoneIndex] = 0;
		mZone319TypePostTick = 0;
		mZone319TypeBattleState = 0;
		return;
	}
}
//RETURN_LEVEL_WAR_REWARD_3
void MyGame::ReturnLevelWarReward3(int tLevel1, int tLevel2, int* tGainExperience, int* tGainMoney)
{
	*tGainExperience = 0;
	*tGainMoney = 0;
	switch (tLevel2)
	{
	case 1:
		*tGainExperience = 9621058;
		*tGainMoney = 15000000;
		return;
	case 2:
		*tGainExperience = 10005901;
		*tGainMoney = 15000000;
		return;
	case 3:
		*tGainExperience = 10406137;
		*tGainMoney = 15000000;
		return;
	case 4:
		*tGainExperience = 10822382;
		*tGainMoney = 15000000;
		return;
	case 5:
		*tGainExperience = 5627638;
		*tGainMoney = 20000000;
		return;
	case 6:
		*tGainExperience = 5852744;
		*tGainMoney = 20000000;
		return;
	case 7:
		*tGainExperience = 6086854;
		*tGainMoney = 20000000;
		return;
	case 8:
		*tGainExperience = 6330328;
		*tGainMoney = 20000000;
		return;
	case 9:
		*tGainExperience = 3291770;
		*tGainMoney = 25000000;
		return;
	case 10:
		*tGainExperience = 3423441;
		*tGainMoney = 25000000;
		return;
	case 11:
		*tGainExperience = 3560379;
		*tGainMoney = 25000000;
		return;
	case 12:
		*tGainExperience = 3702794;
		*tGainMoney = 25000000;
		return;
	}
	switch (tLevel1)
	{
	case  70:
		*tGainExperience = 43936;
		*tGainMoney = 500000;
		break;
	case  71:
		*tGainExperience = 44588;
		*tGainMoney = 500000;
		break;
	case  72:
		*tGainExperience = 45240;
		*tGainMoney = 500000;
		break;
	case  73:
		*tGainExperience = 45891;
		*tGainMoney = 500000;
		break;
	case  74:
		*tGainExperience = 46541;
		*tGainMoney = 500000;
		break;
	case  75:
		*tGainExperience = 47190;
		*tGainMoney = 500000;
		break;
	case  76:
		*tGainExperience = 47838;
		*tGainMoney = 500000;
		break;
	case  77:
		*tGainExperience = 48485;
		*tGainMoney = 500000;
		break;
	case  78:
		*tGainExperience = 49131;
		*tGainMoney = 500000;
		break;
	case  79:
		*tGainExperience = 49775;
		*tGainMoney = 500000;
		break;
	case  80:
		*tGainExperience = 50421;
		*tGainMoney = 500000;
		break;
	case  81:
		*tGainExperience = 51064;
		*tGainMoney = 500000;
		break;
	case  82:
		*tGainExperience = 51705;
		*tGainMoney = 500000;
		break;
	case  83:
		*tGainExperience = 52346;
		*tGainMoney = 500000;
		break;
	case  84:
		*tGainExperience = 52988;
		*tGainMoney = 500000;
		break;
	case  85:
		*tGainExperience = 53627;
		*tGainMoney = 500000;
		break;
	case  86:
		*tGainExperience = 54266;
		*tGainMoney = 500000;
		break;
	case  87:
		*tGainExperience = 54905;
		*tGainMoney = 500000;
		break;
	case  88:
		*tGainExperience = 55542;
		*tGainMoney = 500000;
		break;
	case  89:
		*tGainExperience = 87927;
		*tGainMoney = 500000;
		break;
	case  90:
		*tGainExperience = 114075;
		*tGainMoney = 500000;
		break;
	case  91:
		*tGainExperience = 50639;
		*tGainMoney = 2000000;
		break;
	case  92:
		*tGainExperience = 54193;
		*tGainMoney = 2000000;
		break;
	case  93:
		*tGainExperience = 56998;
		*tGainMoney = 2000000;
		break;
	case  94:
		*tGainExperience = 59339;
		*tGainMoney = 2000000;
		break;
	case  95:
		*tGainExperience = 61359;
		*tGainMoney = 2000000;
		break;
	case  96:
		*tGainExperience = 63143;
		*tGainMoney = 2000000;
		break;
	case  97:
		*tGainExperience = 64745;
		*tGainMoney = 2000000;
		break;
	case  98:
		*tGainExperience = 66203;
		*tGainMoney = 2000000;
		break;
	case  99:
		*tGainExperience = 77015;
		*tGainMoney = 2000000;
		break;
	case 100:
		*tGainExperience = 99918;
		*tGainMoney = 2000000;
		break;
	case 101:
		*tGainExperience = 110885;
		*tGainMoney = 2000000;
		break;
	case 102:
		*tGainExperience = 118666;
		*tGainMoney = 2000000;
		break;
	case 103:
		*tGainExperience = 124811;
		*tGainMoney = 2000000;
		break;
	case 104:
		*tGainExperience = 129936;
		*tGainMoney = 2000000;
		break;
	case 105:
		*tGainExperience = 134359;
		*tGainMoney = 2000000;
		break;
	case 106:
		*tGainExperience = 138265;
		*tGainMoney = 2000000;
		break;
	case 107:
		*tGainExperience = 141774;
		*tGainMoney = 2000000;
		break;
	case 108:
		*tGainExperience = 144966;
		*tGainMoney = 2000000;
		break;
	case 109:
		*tGainExperience = 147899;
		*tGainMoney = 2000000;
		break;
	case 110:
		*tGainExperience = 150616;
		*tGainMoney = 2000000;
		break;
	case 111:
		*tGainExperience = 153150;
		*tGainMoney = 2000000;
		break;
	case 112:
		*tGainExperience = 3189692;
		*tGainMoney = 2000000;
		break;
	case 113:
		*tGainExperience = 1034574;
		*tGainMoney = 5000000;
		break;
	case 114:
		*tGainExperience = 1148127;
		*tGainMoney = 5000000;
		break;
	case 115:
		*tGainExperience = 1228701;
		*tGainMoney = 5000000;
		break;
	case 116:
		*tGainExperience = 1292318;
		*tGainMoney = 5000000;
		break;
	case 117:
		*tGainExperience = 1345386;
		*tGainMoney = 5000000;
		break;
	case 118:
		*tGainExperience = 1391182;
		*tGainMoney = 5000000;
		break;
	case 119:
		*tGainExperience = 1431630;
		*tGainMoney = 5000000;
		break;
	case 120:
		*tGainExperience = 1467959;
		*tGainMoney = 5000000;
		break;
	case 121:
		*tGainExperience = 1501007;
		*tGainMoney = 5000000;
		break;
	case 122:
		*tGainExperience = 1531376;
		*tGainMoney = 5000000;
		break;
	case 123:
		*tGainExperience = 1559509;
		*tGainMoney = 5000000;
		break;
	case 124:
		*tGainExperience = 1585746;
		*tGainMoney = 5000000;
		break;
	case 125:
		*tGainExperience = 1610352;
		*tGainMoney = 5000000;
		break;
	case 126:
		*tGainExperience = 1633542;
		*tGainMoney = 5000000;
		break;
	case 127:
		*tGainExperience = 1655482;
		*tGainMoney = 5000000;
		break;
	case 128:
		*tGainExperience = 1676317;
		*tGainMoney = 5000000;
		break;
	case 129:
		*tGainExperience = 1696166;
		*tGainMoney = 5000000;
		break;
	case 130:
		*tGainExperience = 1715126;
		*tGainMoney = 5000000;
		break;
	case 131:
		*tGainExperience = 1733283;
		*tGainMoney = 5000000;
		break;
	case 132:
		*tGainExperience = 1750710;
		*tGainMoney = 5000000;
		break;
	case 133:
		*tGainExperience = 1767469;
		*tGainMoney = 5000000;
		break;
	case 134:
		*tGainExperience = 1783613;
		*tGainMoney = 5000000;
		break;
	case 135:
		*tGainExperience = 1799197;
		*tGainMoney = 5000000;
		break;
	case 136:
		*tGainExperience = 1814256;
		*tGainMoney = 5000000;
		break;
	case 137:
		*tGainExperience = 1097299;
		*tGainMoney = 7000000;
		break;
	case 138:
		*tGainExperience = 1105776;
		*tGainMoney = 7000000;
		break;
	case 139:
		*tGainExperience = 1113995;
		*tGainMoney = 7000000;
		break;
	case 140:
		*tGainExperience = 1121987;
		*tGainMoney = 7000000;
		break;
	case 141:
		*tGainExperience = 1129749;
		*tGainMoney = 7000000;
		break;
	case 142:
		*tGainExperience = 1137310;
		*tGainMoney = 7000000;
		break;
	case 143:
		*tGainExperience = 1144669;
		*tGainMoney = 7000000;
		break;
	case 144:
		*tGainExperience = 1151850;
		*tGainMoney = 7000000;
		break;
	case 145:
		*tGainExperience = 9251018;
		*tGainMoney = 8000000;
		break;
	}
}
#endif
//void MyGame::ProcesForTreasureHunterEvent()////Saigo monsters////
//{
//	int tTickCount = 0;
//	BYTE tData[MAX_BROADCAST_DATA_SIZE];
//	float tPossibleLocation[13][3];
//	int index01;
//	int index02;
//	tPossibleLocation[0][0] = -700.0f;
//	tPossibleLocation[0][1] = 0.0f;
//	tPossibleLocation[0][2] = -2111.0f;
//	tPossibleLocation[1][0] = -619.0f;
//	tPossibleLocation[1][1] = 0.0f;
//	tPossibleLocation[1][2] = -478.0f;
//	tPossibleLocation[2][0] = 837.0f;
//	tPossibleLocation[2][1] = 0.0f;
//	tPossibleLocation[2][2] = -655.0f;
//	tPossibleLocation[3][0] = 737.0f;
//	tPossibleLocation[3][1] = 0.0f;
//	tPossibleLocation[3][2] = -2136.0f;
//	tPossibleLocation[4][0] = 2.0f;
//	tPossibleLocation[4][1] = 62.0f;
//	tPossibleLocation[4][2] = -2830.0f;
//	tPossibleLocation[5][0] = 601.0f;
//	tPossibleLocation[5][1] = 62.0f;
//	tPossibleLocation[5][2] = -3243.0f;
//	tPossibleLocation[6][0] = -538.0f;
//	tPossibleLocation[6][1] = 62.0f;
//	tPossibleLocation[6][2] = -3086.0f;
//	tPossibleLocation[7][0] = 14.0f;
//	tPossibleLocation[7][1] = 97.0f;
//	tPossibleLocation[7][2] = -3246.0f;
//	tPossibleLocation[8][0] = -4.0f;
//	tPossibleLocation[8][1] = 0.0f;
//	tPossibleLocation[8][2] = -1356.0f;
//	tPossibleLocation[9][0] = 0.0f;
//	tPossibleLocation[9][1] = 0.0f;
//	tPossibleLocation[9][2] = -2096.0f;
//	tPossibleLocation[10][0] = -723.0f;
//	tPossibleLocation[10][1] = 0.0f;
//	tPossibleLocation[10][2] = -1352.0f;
//	tPossibleLocation[11][0] = -5.0f;
//	tPossibleLocation[11][1] = 0.0f;
//	tPossibleLocation[11][2] = -586.0f;
//	tPossibleLocation[12][0] = 741.0f;
//	tPossibleLocation[12][1] = 0.0f;
//	tPossibleLocation[12][2] = -1355.0f;
//
//	time_t tCountSeconds;
//	struct tm* tPresentTime;
//	time(&tCountSeconds);
//	tPresentTime = localtime(&tCountSeconds);
//	int tRandomLocation;
//
//	switch (mGAME.mTreasureHunterEventState)
//	{
//	case 0:
//		if (tPresentTime->tm_hour != 13 || tPresentTime->tm_min != 4
//			return;
//		}
//		mGAME.mTreasureHunterEventState = 1;
//		return;
//7) //This is the time of the respawn, you can modify it will different times or hours based on what you want.
//		{
//	case 1:
//		sprintf((char*)&tData[0], "Saigo Temple Treasure Hunter Event has begun!"); // Pop up so that the players will inform that the spawn is already added.
//		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
//		mSUMMON.SummonMonsterWithoutTimeLimit();
//		
//		for (index01 = 0; index01 < 1; index01++)
//		{
//			tRandomLocation = rand() % 13;
//			for (index02 = 0; index02 < 1; index02++)
//			{
//				mSUMMON.SummonMonsterForSpecial(705, &tPossibleLocation[tRandomLocation][0], FALSE); // This is the monster id
//			}
//		}
//
//		mGAME.mTreasureHunterEventState = 2;
//		return;
//
//	case 2:
//		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
//		{
//			if (!mMONSTER_OBJECT[index01].mCheckValidState)
//			{
//				continue;
//			}
//			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == 705))
//			{
//				break;
//			}
//		}
//		if (index01 == MAX_MONSTER_OBJECT_NUM)
//		{
//			sprintf((char*)&tData[0], "Saigo Temple Treasure Hunter Event has ended!");
//			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
//			mGAME.mTreasureHunterEventState = 0;
//		}
//		return;
//	}
//}


void MyGame::ProcessforYanggokBoss()////Yanggok monsters///
{
	int tTickCount = 0;
	BYTE tData[MAX_BROADCAST_DATA_SIZE];
	float tPossibleLocation[2][3]; // You can modify it here if you want to static respawning just change the variable name
	int index01;
	int index02;

	tPossibleLocation[0][0] = 1750.0;//Left Positioning   #------------------------#
	tPossibleLocation[0][1] = 0.0;// Ground Positioning  #   Mid Dragon side      #
	tPossibleLocation[0][2] = 6374.0;//Right Positioning #------------------------#
	tPossibleLocation[1][0] = 1813.0;//Left Positioning  #------------------------#
	tPossibleLocation[1][1] = 0.0;//round Positioning  #   Mid  side Tiger      #
	tPossibleLocation[1][2] = 8407.0;//Right Positioning #------------------------#

	time_t tCountSeconds;
	struct tm* tPresentTime;
	time(&tCountSeconds);
	tPresentTime = localtime(&tCountSeconds);
	int tRandomLocation;

	//sprintf((char*)&tData[0], mUSER[0].mAvatarInfo.aName); // Pop up so that the players will inform that the spawn is already added.
	// mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

	switch (mGAME.mYanggokEventState)
	{
	case 0:
		if (tPresentTime->tm_hour != 20 || tPresentTime->tm_min != 2) //This is the time of the respawn, you can modify it will different times or hours based on what you want.
		{
			return;
		}
		mGAME.mYanggokEventState = 1;
		return;

	case 1:
		sprintf((char*)&tData[0], "The first Ice King has appeared in Ghost Valley!!!"); // Pop up so that the players will inform that the spawn is already added.
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

		sprintf((char*)&tData[0], "The second Ice King has appeared in Ghost Valley!!!"); // Pop up so that the players will inform that the spawn is already added.
		mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);

		mSUMMON.SummonMonsterWithoutTimeLimit();

		mSUMMON.SummonMonsterForSpecial(705, &tPossibleLocation[0][0], FALSE); // Then change this value according the location
		mSUMMON.SummonMonsterForSpecial(702, &tPossibleLocation[1][0], FALSE); // Then change this value according the location

		mGAME.mYanggokEventState = 2;
		return;

	case 2:
		for (index01 = 0; index01 < MAX_MONSTER_OBJECT_NUM; index01++)
		{
			if (!mMONSTER_OBJECT[index01].mCheckValidState)
			{
				continue;
			}

			if ((mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == 705 || mMONSTER_OBJECT[index01].mMONSTER_INFO->mIndex == 702))
			{
				break;
			}
		}

		if (index01 == MAX_MONSTER_OBJECT_NUM)
		{
			sprintf((char*)&tData[0], "The monsters have been killed!!!"); // Pop up so that the players will inform that the spawn is already added.
			mRELAY_COM.U_DEMAND_BROADCAST_DATA(102, &tData[0]);
			mGAME.mYanggokEventState = 0;
		}
		return;
	}
}