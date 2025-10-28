#include "MainApp.h"

LEVELSYSTEM mLEVEL;

LEVELSYSTEM::LEVELSYSTEM(void)
{
	int index01;

	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		mGainExpInfoForKillOtherTribe[index01] = 0.0f;
	}
	mGainExpInfoForKillOtherTribe[0] = 40.0f;
	mGainExpInfoForKillOtherTribe[1] = 40.0f;
	mGainExpInfoForKillOtherTribe[2] = 40.0f;
	mGainExpInfoForKillOtherTribe[3] = 40.0f;
	mGainExpInfoForKillOtherTribe[4] = 40.0f;
	mGainExpInfoForKillOtherTribe[5] = 40.0f;
	mGainExpInfoForKillOtherTribe[6] = 40.0f;
	mGainExpInfoForKillOtherTribe[7] = 40.0f;
	mGainExpInfoForKillOtherTribe[8] = 40.0f;
	mGainExpInfoForKillOtherTribe[9] = 40.0f;
	mGainExpInfoForKillOtherTribe[10] = 40.0f;
	mGainExpInfoForKillOtherTribe[11] = 40.0f;
	mGainExpInfoForKillOtherTribe[12] = 40.0f;
	mGainExpInfoForKillOtherTribe[13] = 40.0f;
	mGainExpInfoForKillOtherTribe[14] = 40.0f;
	mGainExpInfoForKillOtherTribe[15] = 40.0f;
	mGainExpInfoForKillOtherTribe[16] = 40.0f;
	mGainExpInfoForKillOtherTribe[17] = 40.0f;
	mGainExpInfoForKillOtherTribe[18] = 40.0f;
	mGainExpInfoForKillOtherTribe[19] = 40.0f;
	mGainExpInfoForKillOtherTribe[20] = 40.0f;
	mGainExpInfoForKillOtherTribe[21] = 40.0f;
	mGainExpInfoForKillOtherTribe[22] = 40.0f;
	mGainExpInfoForKillOtherTribe[23] = 40.0f;
	mGainExpInfoForKillOtherTribe[24] = 40.0f;
	mGainExpInfoForKillOtherTribe[25] = 40.0f;
	mGainExpInfoForKillOtherTribe[26] = 40.0f;
	mGainExpInfoForKillOtherTribe[27] = 40.0f;
	mGainExpInfoForKillOtherTribe[28] = 40.0f;
	mGainExpInfoForKillOtherTribe[29] = 40.0f;
	mGainExpInfoForKillOtherTribe[30] = 40.0f;
	mGainExpInfoForKillOtherTribe[31] = 40.0f;
	mGainExpInfoForKillOtherTribe[32] = 40.0f;
	mGainExpInfoForKillOtherTribe[33] = 50.0f;
	mGainExpInfoForKillOtherTribe[34] = 50.0f;
	mGainExpInfoForKillOtherTribe[35] = 50.0f;
	mGainExpInfoForKillOtherTribe[36] = 50.0f;
	mGainExpInfoForKillOtherTribe[37] = 50.0f;
	mGainExpInfoForKillOtherTribe[38] = 50.0f;
	mGainExpInfoForKillOtherTribe[39] = 50.0f;
	mGainExpInfoForKillOtherTribe[40] = 50.0f;
	mGainExpInfoForKillOtherTribe[41] = 50.0f;
	mGainExpInfoForKillOtherTribe[42] = 50.0f;
	mGainExpInfoForKillOtherTribe[43] = 50.0f;
	mGainExpInfoForKillOtherTribe[44] = 50.0f;
	mGainExpInfoForKillOtherTribe[45] = 50.0f;
	mGainExpInfoForKillOtherTribe[46] = 50.0f;
	mGainExpInfoForKillOtherTribe[47] = 50.0f;
	mGainExpInfoForKillOtherTribe[48] = 50.0f;
	mGainExpInfoForKillOtherTribe[49] = 50.0f;
	mGainExpInfoForKillOtherTribe[50] = 50.0f;
	mGainExpInfoForKillOtherTribe[51] = 50.0f;
	mGainExpInfoForKillOtherTribe[52] = 50.0f;
	mGainExpInfoForKillOtherTribe[53] = 50.0f;
	mGainExpInfoForKillOtherTribe[54] = 50.0f;
	mGainExpInfoForKillOtherTribe[55] = 50.0f;
	mGainExpInfoForKillOtherTribe[56] = 50.0f;
	mGainExpInfoForKillOtherTribe[57] = 50.0f;
	mGainExpInfoForKillOtherTribe[58] = 50.0f;
	mGainExpInfoForKillOtherTribe[59] = 50.0f;
	mGainExpInfoForKillOtherTribe[60] = 50.0f;
	mGainExpInfoForKillOtherTribe[61] = 50.0f;
	mGainExpInfoForKillOtherTribe[62] = 50.0f;
	mGainExpInfoForKillOtherTribe[63] = 50.0f;
	mGainExpInfoForKillOtherTribe[64] = 50.0f;
	mGainExpInfoForKillOtherTribe[65] = 50.0f;
	mGainExpInfoForKillOtherTribe[66] = 60.0f;
	mGainExpInfoForKillOtherTribe[67] = 60.0f;
	mGainExpInfoForKillOtherTribe[68] = 60.0f;
	mGainExpInfoForKillOtherTribe[69] = 60.0f;
	mGainExpInfoForKillOtherTribe[70] = 60.0f;
	mGainExpInfoForKillOtherTribe[71] = 60.0f;
	mGainExpInfoForKillOtherTribe[72] = 60.0f;
	mGainExpInfoForKillOtherTribe[73] = 60.0f;
	mGainExpInfoForKillOtherTribe[74] = 60.0f;
	mGainExpInfoForKillOtherTribe[75] = 60.0f;
	mGainExpInfoForKillOtherTribe[76] = 60.0f;
	mGainExpInfoForKillOtherTribe[77] = 60.0f;
	mGainExpInfoForKillOtherTribe[78] = 60.0f;
	mGainExpInfoForKillOtherTribe[79] = 60.0f;
	mGainExpInfoForKillOtherTribe[80] = 60.0f;
	mGainExpInfoForKillOtherTribe[81] = 60.0f;
	mGainExpInfoForKillOtherTribe[82] = 60.0f;
	mGainExpInfoForKillOtherTribe[83] = 60.0f;
	mGainExpInfoForKillOtherTribe[84] = 60.0f;
	mGainExpInfoForKillOtherTribe[85] = 60.0f;
	mGainExpInfoForKillOtherTribe[86] = 60.0f;
	mGainExpInfoForKillOtherTribe[87] = 60.0f;
	mGainExpInfoForKillOtherTribe[88] = 60.0f;
	mGainExpInfoForKillOtherTribe[89] = 60.0f;
	mGainExpInfoForKillOtherTribe[90] = 60.0f;
	mGainExpInfoForKillOtherTribe[91] = 60.0f;
	mGainExpInfoForKillOtherTribe[92] = 60.0f;
	mGainExpInfoForKillOtherTribe[93] = 60.0f;
	mGainExpInfoForKillOtherTribe[94] = 60.0f;
	mGainExpInfoForKillOtherTribe[95] = 60.0f;
	mGainExpInfoForKillOtherTribe[96] = 60.0f;
	mGainExpInfoForKillOtherTribe[97] = 60.0f;
	mGainExpInfoForKillOtherTribe[98] = 60.0f;
	mGainExpInfoForKillOtherTribe[99] = 66.0f;
	mGainExpInfoForKillOtherTribe[100] = 66.0f;
	mGainExpInfoForKillOtherTribe[101] = 66.0f;
	mGainExpInfoForKillOtherTribe[102] = 66.0f;
	mGainExpInfoForKillOtherTribe[103] = 72.0f;
	mGainExpInfoForKillOtherTribe[104] = 72.0f;
	mGainExpInfoForKillOtherTribe[105] = 72.0f;
	mGainExpInfoForKillOtherTribe[106] = 78.0f;
	mGainExpInfoForKillOtherTribe[107] = 78.0f;
	mGainExpInfoForKillOtherTribe[108] = 78.0f;
	mGainExpInfoForKillOtherTribe[109] = 84.0f;
	mGainExpInfoForKillOtherTribe[110] = 84.0f;
	mGainExpInfoForKillOtherTribe[111] = 84.0f;
	mGainExpInfoForKillOtherTribe[112] = 90.0f;
	mGainExpInfoForKillOtherTribe[113] = 90.0f;
	mGainExpInfoForKillOtherTribe[114] = 90.0f;
	mGainExpInfoForKillOtherTribe[115] = 90.0f;
	mGainExpInfoForKillOtherTribe[116] = 90.0f;
	mGainExpInfoForKillOtherTribe[117] = 90.0f;
	mGainExpInfoForKillOtherTribe[118] = 90.0f;
	mGainExpInfoForKillOtherTribe[119] = 90.0f;
	mGainExpInfoForKillOtherTribe[120] = 90.0f;
	mGainExpInfoForKillOtherTribe[121] = 90.0f;
	mGainExpInfoForKillOtherTribe[122] = 90.0f;
	mGainExpInfoForKillOtherTribe[123] = 100.0f;
	mGainExpInfoForKillOtherTribe[124] = 100.0f;
	mGainExpInfoForKillOtherTribe[125] = 100.0f;
	mGainExpInfoForKillOtherTribe[126] = 100.0f;
	mGainExpInfoForKillOtherTribe[127] = 100.0f;
	mGainExpInfoForKillOtherTribe[128] = 100.0f;
	mGainExpInfoForKillOtherTribe[129] = 100.0f;
	mGainExpInfoForKillOtherTribe[130] = 100.0f;
	mGainExpInfoForKillOtherTribe[131] = 100.0f;
	mGainExpInfoForKillOtherTribe[132] = 100.0f;
	mGainExpInfoForKillOtherTribe[133] = 100.0f;
	mGainExpInfoForKillOtherTribe[134] = 110.0f;
	mGainExpInfoForKillOtherTribe[135] = 110.0f;
	mGainExpInfoForKillOtherTribe[136] = 110.0f;
	mGainExpInfoForKillOtherTribe[137] = 110.0f;
	mGainExpInfoForKillOtherTribe[138] = 110.0f;
	mGainExpInfoForKillOtherTribe[139] = 110.0f;
	mGainExpInfoForKillOtherTribe[140] = 110.0f;
	mGainExpInfoForKillOtherTribe[141] = 110.0f;
	mGainExpInfoForKillOtherTribe[142] = 110.0f;
	mGainExpInfoForKillOtherTribe[143] = 110.0f;
	mGainExpInfoForKillOtherTribe[144] = 110.0f;
#ifdef __GOD__
	mGainExpInfoForKillOtherTribe[145] = 330.0f;
	mGainExpInfoForKillOtherTribe[146] = 330.0f;
	mGainExpInfoForKillOtherTribe[147] = 330.0f;
	mGainExpInfoForKillOtherTribe[148] = 330.0f;
	mGainExpInfoForKillOtherTribe[149] = 360.0f;
	mGainExpInfoForKillOtherTribe[150] = 360.0f;
	mGainExpInfoForKillOtherTribe[151] = 360.0f;
	mGainExpInfoForKillOtherTribe[152] = 360.0f;
	mGainExpInfoForKillOtherTribe[153] = 390.0f;
	mGainExpInfoForKillOtherTribe[154] = 390.0f;
	mGainExpInfoForKillOtherTribe[155] = 390.0f;
	mGainExpInfoForKillOtherTribe[156] = 390.0f;
	mRangeForHigh[0] = 962105896;
	mRangeForHigh[1] = 1000590131;
	mRangeForHigh[2] = 1040613736;
	mRangeForHigh[3] = 1082238285;
	mRangeForHigh[4] = 1125527816;
	mRangeForHigh[5] = 1170548928;
	mRangeForHigh[6] = 1217370885;
	mRangeForHigh[7] = 1266065720;
	mRangeForHigh[8] = 1316708348;
	mRangeForHigh[9] = 1369376681;
	mRangeForHigh[10] = 1424151748;
	mRangeForHigh[11] = 1481117817;
#endif
}
//CHECK_VALID_ELEMENT
BOOL LEVELSYSTEM::CheckValidElement(int tArrayIndex)
{
	if ((mDATA[tArrayIndex].lIndex < 1) || (mDATA[tArrayIndex].lIndex > MAX_LIMIT_LEVEL_NUM))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].lIndex != (tArrayIndex + 1))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lRangeInfo[0] < 0) || (mDATA[tArrayIndex].lRangeInfo[0] > MAX_NUMBER_SIZE))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lRangeInfo[1] < 1) || (mDATA[tArrayIndex].lRangeInfo[1] > MAX_NUMBER_SIZE))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].lRangeInfo[0] >= mDATA[tArrayIndex].lRangeInfo[1])
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (tArrayIndex < 144)
	{
		if (mDATA[tArrayIndex].lRangeInfo[1] != (mDATA[(tArrayIndex + 1)].lRangeInfo[0] - 1))
		{
			__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].lRangeInfo[2] < 0) || (mDATA[tArrayIndex].lRangeInfo[2] > 100))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackPower < 0) || (mDATA[tArrayIndex].lAttackPower > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lDefensePower < 0) || (mDATA[tArrayIndex].lDefensePower > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackSuccess < 0) || (mDATA[tArrayIndex].lAttackSuccess > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lAttackBlock < 0) || (mDATA[tArrayIndex].lAttackBlock > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lElementAttack < 0) || (mDATA[tArrayIndex].lElementAttack > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lLife < 0) || (mDATA[tArrayIndex].lLife > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].lMana < 0) || (mDATA[tArrayIndex].lMana > 10000))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	return TRUE;
}
//INIT
BOOL LEVELSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;

	Free();

	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	if (tDataNum != MAX_LIMIT_LEVEL_NUM)
	{
		return FALSE;
	}
	CopyMemory(&mDATA[0], &tOriginal[4], (tDataNum * sizeof(LEVEL_INFO)));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);

	for (index01 = 0; index01 < tDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			__LogMgr()->Log("! [%s] %d", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void LEVELSYSTEM::Free(void)
{
}
//RETURN_LEVEL
int LEVELSYSTEM::ReturnLevel(int tGeneralExperience)
{
	int index01;

	if (tGeneralExperience < mDATA[0].lRangeInfo[0])
	{
		return 1;
	}
	for (index01 = 0; index01 < (MAX_LIMIT_LEVEL_NUM - 1); index01++)
	{
		if ((tGeneralExperience >= mDATA[index01].lRangeInfo[0]) && (tGeneralExperience <= mDATA[index01].lRangeInfo[1]))
		{
			return (index01 + 1);
		}
	}
	return MAX_LIMIT_LEVEL_NUM;
}
//RETURN_LEVEL_FACTOR_1
int LEVELSYSTEM::ReturnLevelFactor1(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}
	return mDATA[(tLevel - 1)].lRangeInfo[0];
}
//RETURN_LEVEL_FACTOR_2
int LEVELSYSTEM::ReturnLevelFactor2(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}
	return mDATA[(tLevel - 1)].lRangeInfo[1];
}
//RETURN_LEVEL_FACTOR_3
int LEVELSYSTEM::ReturnLevelFactor3(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
	{
		return 0;
	}
#if 0
	for (int i = 0; i < 145; i++) {
		__LogMgr()->Log("===> %d %d\n", i, mDATA[(i)].lRangeInfo[2]);
	}
#endif
	return mDATA[(tLevel - 1)].lRangeInfo[2];
}
//RETURN_LEVEL_FACTOR_ATTACK_POWER
int LEVELSYSTEM::ReturnLevelFactorAttackPower(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackPower;
}
//RETURN_LEVEL_FACTOR_DEFENSE_POWER
int LEVELSYSTEM::ReturnLevelFactorDefensePower(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lDefensePower;
}
//RETURN_LEVEL_FACTOR_ATTACK_SUCCESS
int LEVELSYSTEM::ReturnLevelFactorAttackSuccess(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackSuccess;
}
//RETURN_LEVEL_FACTOR_ATTACK_BLOCK
int LEVELSYSTEM::ReturnLevelFactorAttackBlock(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lAttackBlock;
}
//RETURN_LEVEL_FACTOR_ELEMENT_ATTACK
int LEVELSYSTEM::ReturnLevelFactorElementAttack(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lElementAttack;
}
//RETURN_LEVEL_FACTOR_LIFE
int LEVELSYSTEM::ReturnLevelFactorLife(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lLife;
}
//RETURN_LEVEL_FACTOR_MANA
int LEVELSYSTEM::ReturnLevelFactorMana(int tLevel)
{
#ifdef __GOD__
	if ((tLevel < 1) || (tLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)))
#else
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_LEVEL_NUM))
#endif
	{
		return 0;
	}
#ifdef __GOD__
	if (tLevel > MAX_LIMIT_LEVEL_NUM)
		tLevel = MAX_LIMIT_LEVEL_NUM;
#endif
	return mDATA[(tLevel - 1)].lMana;
}

#ifdef __GOD__
//RETURN_HIGH_EXP_VALUE
int LEVELSYSTEM::ReturnHighExpValue(int tLevel)
{
	if ((tLevel < 1) || (tLevel > MAX_LIMIT_HIGH_LEVEL_NUM))
	{
		return 0;
	}
	return mRangeForHigh[(tLevel - 1)];
}
#endif

//RETURN_GAIN_EXP_FOR_KILL_OTHER_TRIBE
int LEVELSYSTEM::ReturnGainExpForKillOtherTribe(int tAttackLevel, int tDefenseLevel)
{
#ifdef __GOD__
	if ((tAttackLevel < 1) || (tAttackLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tDefenseLevel < 1) || (tDefenseLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || ((tAttackLevel - tDefenseLevel) > 9))
#else
	if ((tAttackLevel < 1) || (tAttackLevel > MAX_LIMIT_LEVEL_NUM) || (tDefenseLevel < 1) || (tDefenseLevel > MAX_LIMIT_LEVEL_NUM) || ((tAttackLevel - tDefenseLevel) > 9))
#endif
	{
		return 0;
	}
	if (tAttackLevel < tDefenseLevel)
	{
		return (int)(mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] + (mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] * ((float)(tDefenseLevel - tAttackLevel) * 0.1f)));
	}
	else
	{
		return (int)(mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] - (mGainExpInfoForKillOtherTribe[(tDefenseLevel - 1)] * ((float)(tAttackLevel - tDefenseLevel) * 0.1f)));
	}
	return 0;
}




ITEMSYSTEM mITEM;

ITEMSYSTEM::ITEMSYSTEM(void)
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	mDATA = NULL;
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < 6; index02++)
		{
			for (index03 = 0; index03 < 22; index03++)
			{
				mPartNum[index01][index02][index03] = 0;
				mPART[index01][index02][index03] = NULL;
			}
		}
	}
	//mSharedMemMap = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL ITEMSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].iIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].iIndex < 1) || (mDATA[tArrayIndex].iIndex > 99999))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].iIndex != (tArrayIndex + 1))
	{
		mLog("! [%s] %d ", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].iName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].iDescription[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].iType < 1) || (mDATA[tArrayIndex].iType > MAX_ITEM_TYPE))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iSort < 1) || (mDATA[tArrayIndex].iSort > MAX_ITEM_SORT))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDataNumber2D < 1) || (mDATA[tArrayIndex].iDataNumber2D > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDataNumber3D < 0) || (mDATA[tArrayIndex].iDataNumber3D > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAddDataNumber3D < 0) || (mDATA[tArrayIndex].iAddDataNumber3D > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLevel < 1) || (mDATA[tArrayIndex].iLevel > MAX_LIMIT_LEVEL_NUM))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].iMartialLevel < 0) || (mDATA[tArrayIndex].iMartialLevel > 12)) // God
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].iEquipInfo[0] < 1) || (mDATA[tArrayIndex].iEquipInfo[0] > 4))
	{
		mLog("! [%s] %d", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iEquipInfo[1] < 1) || (mDATA[tArrayIndex].iEquipInfo[1] > 22))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iBuyCost < 1) || (mDATA[tArrayIndex].iBuyCost > MAX_NUMBER_SIZE))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iSellCost < 0) || (mDATA[tArrayIndex].iSellCost > MAX_NUMBER_SIZE))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iBuyCPCost < 0) || (mDATA[tArrayIndex].iBuyCPCost > MAX_NUMBER_SIZE))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLevelLimit < 1) || (mDATA[tArrayIndex].iLevelLimit > MAX_LIMIT_LEVEL_NUM))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].iMartialLevelLimit < 0) || (mDATA[tArrayIndex].iMartialLevelLimit > 12))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].iCheckMonsterDrop < 1) || (mDATA[tArrayIndex].iCheckMonsterDrop > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckNPCSell < 1) || (mDATA[tArrayIndex].iCheckNPCSell > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckNPCShop < 1) || (mDATA[tArrayIndex].iCheckNPCShop > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarDrop < 1) || (mDATA[tArrayIndex].iCheckAvatarDrop > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarTrade < 1) || (mDATA[tArrayIndex].iCheckAvatarTrade > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckAvatarShop < 1) || (mDATA[tArrayIndex].iCheckAvatarShop > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckImprove < 1) || (mDATA[tArrayIndex].iCheckImprove > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckHighImprove < 1) || (mDATA[tArrayIndex].iCheckHighImprove > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckHighItem < 1) || (mDATA[tArrayIndex].iCheckHighItem > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckLowItem < 1) || (mDATA[tArrayIndex].iCheckLowItem > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckExchange < 1) || (mDATA[tArrayIndex].iCheckExchange > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckItemSet < 1) || (mDATA[tArrayIndex].iCheckItemSet > 3))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCheckExpire < 0) || (mDATA[tArrayIndex].iCheckExpire > 365))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iStrength < 0) || (mDATA[tArrayIndex].iStrength > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iWisdom < 0) || (mDATA[tArrayIndex].iWisdom > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iVitality < 0) || (mDATA[tArrayIndex].iVitality > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iKi < 0) || (mDATA[tArrayIndex].iKi > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLuck < 0) || (mDATA[tArrayIndex].iLuck > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackPower < 0) || (mDATA[tArrayIndex].iAttackPower > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iDefensePower < 0) || (mDATA[tArrayIndex].iDefensePower > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackSucess < 0) || (mDATA[tArrayIndex].iAttackSucess > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iAttackBlock < 0) || (mDATA[tArrayIndex].iAttackBlock > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iElementAttackPower < 0) || (mDATA[tArrayIndex].iElementAttackPower > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iElementDefensePower < 0) || (mDATA[tArrayIndex].iElementDefensePower > 30000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCritical < 0) || (mDATA[tArrayIndex].iCritical > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iPotionType[0] < 0) || (mDATA[tArrayIndex].iPotionType[0] > 16))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iPotionType[1] < 0) || (mDATA[tArrayIndex].iPotionType[1] > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].iPotionType[0] == 9)
	{
		if ((mDATA[tArrayIndex].iPotionType[1] < 1) || (mDATA[tArrayIndex].iPotionType[1] > 3))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].iGainSkillNumber < 0) || (mDATA[tArrayIndex].iGainSkillNumber > 300))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLastAttackBonusInfo[0] < 0) || (mDATA[tArrayIndex].iLastAttackBonusInfo[0] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iLastAttackBonusInfo[1] < 0) || (mDATA[tArrayIndex].iLastAttackBonusInfo[1] > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[0] < 0) || (mDATA[tArrayIndex].iCapeInfo[0] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[1] < 0) || (mDATA[tArrayIndex].iCapeInfo[1] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].iCapeInfo[2] < 0) || (mDATA[tArrayIndex].iCapeInfo[2] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 8; index01++)
	{
		if ((mDATA[tArrayIndex].iBonusSkillInfo[index01][0] < 0) || (mDATA[tArrayIndex].iBonusSkillInfo[index01][0] > 300))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].iBonusSkillInfo[index01][1] < 0) || (mDATA[tArrayIndex].iBonusSkillInfo[index01][1] > 100))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL ITEMSYSTEM::Init(char* tFileName)
{
	int index01 = NULL;
	int index02;
	int index03;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	ITEM_INFO* tDATA;
	int tLevel;
	int tType;
	int tSort;
	BOOL tCheckFirstCreate;

	Free();

	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	if (tDataNum != 99999)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	tDATA = (ITEM_INFO*)calloc(1, (tDataNum * sizeof(ITEM_INFO)));
	if (tDATA == NULL)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[mSharedMemSize], (tDataNum * sizeof(ITEM_INFO))); //&tOriginal[x]. Change X according to TS2.c
	mSharedMemSize += (tDataNum * sizeof(ITEM_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;

	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			__LogMgr()->Log("! [%s] %d , index = %d \n", __FUNCTION__, __LINE__, index01);
			return FALSE;
		}
	}
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (mDATA[index01].iIndex == 0)
		{
			continue;
		}
		tLevel = mDATA[index01].iLevel - 1;
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPartNum[tLevel][tType][tSort]++;
	}
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < MAX_ITEM_TYPE; index02++)// Change to How many iType IMG Has
		{
			for (index03 = 0; index03 < MAX_ITEM_SORT; index03++)// Change to How many iSort IMG Has
			{
				mSharedMemSize += 4;
				if (mPartNum[index01][index02][index03] < 1)
				{
					continue;
				}
				mSharedMemSize += (mPartNum[index01][index02][index03] * 4);
				mPART[index01][index02][index03] = (int*)calloc(1, (mPartNum[index01][index02][index03] * 4));
				if (mPART[index01][index02][index03] == NULL)
				{
					__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
					return FALSE;
				}
				mPartNum[index01][index02][index03] = 0;
			}
		}
	}
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (mDATA[index01].iIndex == 0)
		{
			continue;
		}
		tLevel = mDATA[index01].iLevel - 1;
		tType = mDATA[index01].iType - 1;
		tSort = mDATA[index01].iSort - 1;
		mPART[tLevel][tType][tSort][mPartNum[tLevel][tType][tSort]] = index01;
		mPartNum[tLevel][tType][tSort]++;
	}

	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_ITEMSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	//mSharedPostMem = (BYTE *)shmat(mSharedMemMap, (char *)0, 0);
	if (mSharedPostMem == NULL)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}

	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedItemData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4; //Change to First mSharedMemSize to Correct the Check at the end.
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(ITEM_INFO)));
	}
	mSharedItemData.mDATA = (ITEM_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(ITEM_INFO));
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < MAX_ITEM_TYPE; index02++)// Change to How many iType IMG Has
		{
			for (index03 = 0; index03 < MAX_ITEM_SORT; index03++)// Change to How many iSort IMG Has
			{
				if (tCheckFirstCreate)
				{
					CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mPartNum[index01][index02][index03], 4);
				}
				CopyMemory(&mSharedItemData.mPartNum[index01][index02][index03], &mSharedPostMem[mSharedMemSizeForCheck], 4);
				mSharedMemSizeForCheck += 4;
			}
		}
	}
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < MAX_ITEM_TYPE; index02++)// Change to How many iType IMG Has
		{
			for (index03 = 0; index03 < MAX_ITEM_SORT; index03++)// Change to How many iSort IMG Has
			{
				if (mPartNum[index01][index02][index03] < 1)
				{
					continue;
				}
				if (tCheckFirstCreate)
				{
					CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mPART[index01][index02][index03], (mPartNum[index01][index02][index03] * 4));
				}
				mSharedItemData.mPART[index01][index02][index03] = (int*)&mSharedPostMem[mSharedMemSizeForCheck];
				mSharedMemSizeForCheck += (mPartNum[index01][index02][index03] * 4);
			}
		}
	}
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < MAX_ITEM_TYPE; index02++)// Change to How many iType IMG Has
		{
			for (index03 = 0; index03 < MAX_ITEM_SORT; index03++)// Change to How many iSort IMG Has
			{
				mPartNum[index01][index02][index03] = 0;
				if (mPART[index01][index02][index03])
				{
					free(mPART[index01][index02][index03]);
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}

	return TRUE;
}
//FREE
void ITEMSYSTEM::Free(void)
{
	int index01;
	int index02;
	int index03;

	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	for (index01 = 0; index01 < MAX_LIMIT_LEVEL_NUM; index01++)
	{
		for (index02 = 0; index02 < MAX_ITEM_TYPE; index02++)
		{
			for (index03 = 0; index03 < MAX_ITEM_SORT; index03++)
			{
				mPartNum[index01][index02][index03] = 0;
				if (mPART[index01][index02][index03])
				{
					GlobalFree(mPART[index01][index02][index03]);
					mPART[index01][index02][index03] = NULL;
				}
			}
		}
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = NULL;
	}
}
//SEARCH
ITEM_INFO* ITEMSYSTEM::Search(int iIndex)
{
	if ((iIndex < 1) || (iIndex > mSharedItemData.mDataNum))
	{
		return NULL;
	}
	if (mSharedItemData.mDATA[(iIndex - 1)].iIndex == 0)
	{
		return NULL;
	}
	return &mSharedItemData.mDATA[(iIndex - 1)];
}
// RETURN
ITEM_INFO* ITEMSYSTEM::Return(int iLevel, int iType, int iSort)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > MAX_ITEM_TYPE) || (iSort < 1) || (iSort > MAX_ITEM_SORT))
	{
		return NULL;
	}
	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];

	if (iLevel <= MAX_LIMIT_LEVEL_NUM)
	{
		if (mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)] < 1)
		{
			return NULL;
		}
		if (iLevel < MAX_LIMIT_LEVEL_NUM)
		{
			return &mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][(rand() % mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)])]];
		}
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iMartialLevel == 0)
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
	}
	else
	{
		if (mSharedItemData.mPartNum[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)] < 1)
		{
			return NULL;
		}
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01]].iMartialLevel == (iLevel - MAX_LIMIT_LEVEL_NUM))
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		unsigned int tRandom = 0;
		tRandom = rand();

		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
}
//RETURN
ITEM_INFO* ITEMSYSTEM::Return(int iLevel, int iType, int iSort, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (iType < 1) || (iType > MAX_ITEM_TYPE) || (iSort < 1) || (iSort > MAX_ITEM_SORT) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	if (iLevel <= MAX_LIMIT_LEVEL_NUM)
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(iType - 1)][(iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iMartialLevel == 0)
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
					{
						if (tTotalSearchItemNum < 1000)
						{
							tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(iType - 1)][(iSort - 1)][index01];
							tTotalSearchItemNum++;
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		return &mSharedItemData.mDATA[tSearchItemIndex[(rand() % tTotalSearchItemNum)]];
	}
	else
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01]].iMartialLevel == (iLevel - MAX_LIMIT_LEVEL_NUM))
				{
					if ((mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckItemSet == tITEM_INFO->iCheckItemSet))
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
						{
							if (tTotalSearchItemNum < 1000)
							{
								tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(iType - 1)][(iSort - 1)][index01];
								tTotalSearchItemNum++;
							}
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		tRandom = rand();
		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
}

#ifdef __GOD__
//RETURN_1
ITEM_INFO* ITEMSYSTEM::Return_1(int iLevel, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	if (iLevel <= MAX_LIMIT_LEVEL_NUM)
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iMartialLevel == 0)
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckItemSet == tITEM_INFO->iCheckItemSet)
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
						{
							if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
							{
								if (tTotalSearchItemNum < 1000)
								{
									tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
									tTotalSearchItemNum++;
								}
							}
							else
							{
								if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[1][0] == tITEM_INFO->iBonusSkillInfo[0][0])
								{
									if (tTotalSearchItemNum < 1000)
									{
										tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
										tTotalSearchItemNum++;
									}
								}
							}
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		tRandom = rand();
		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
	else
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iMartialLevel == (iLevel - MAX_LIMIT_LEVEL_NUM))
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckItemSet == tITEM_INFO->iCheckItemSet)
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
						{
							if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
							{
								if (tTotalSearchItemNum < 1000)
								{
									tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
									tTotalSearchItemNum++;
								}
							}
							else
							{
								if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[1][0] == tITEM_INFO->iBonusSkillInfo[0][0])
								{
									if (tTotalSearchItemNum < 1000)
									{
										tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
										tTotalSearchItemNum++;
									}
								}
							}
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		tRandom = rand();
		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
}
#endif

#ifdef __GOD__
//RETURN_2
ITEM_INFO* ITEMSYSTEM::Return_2(int iLevel, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > (MAX_LIMIT_LEVEL_NUM + MAX_LIMIT_HIGH_LEVEL_NUM)) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	unsigned int tRandom = 0;
	int tSearchItemIndex[1000];

	if (iLevel <= MAX_LIMIT_LEVEL_NUM)
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iMartialLevel == 0)
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckItemSet == tITEM_INFO->iCheckItemSet)
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
						{
							if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
							{
								if (tTotalSearchItemNum < 1000)
								{
									tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
									tTotalSearchItemNum++;
								}
							}
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		tRandom = rand();
		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
	else
	{
		tTotalSearchItemNum = 0;
		for (index01 = 0; index01 < mSharedItemData.mPartNum[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
			{
				if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iMartialLevel == (iLevel - MAX_LIMIT_LEVEL_NUM))
				{
					if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckItemSet == tITEM_INFO->iCheckItemSet)
					{
						if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
						{
							if (mSharedItemData.mDATA[mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
							{
								if (tTotalSearchItemNum < 1000)
								{
									tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(MAX_LIMIT_LEVEL_NUM - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
									tTotalSearchItemNum++;
								}
							}
						}
					}
				}
			}
		}
		if (tTotalSearchItemNum == 0)
		{
			return NULL;
		}
		tRandom = rand();
		return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
	}
}
#else
// RETURN
ITEM_INFO* ITEMSYSTEM::Return(int iLevel, ITEM_INFO* tITEM_INFO)
{
	if ((iLevel < 1) || (iLevel > MAX_LIMIT_LEVEL_NUM) || (tITEM_INFO == NULL))
	{
		return NULL;
	}

	int index01;
	int tTotalSearchItemNum;
	int tSearchItemIndex[1000];
	unsigned int tRandom = 0;

	tTotalSearchItemNum = 0;
	for (index01 = 0; index01 < mSharedItemData.mPartNum[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)]; index01++)
	{
		if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iEquipInfo[0] == tITEM_INFO->iEquipInfo[0])
		{
			if (mSharedItemData.mDATA[mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01]].iBonusSkillInfo[0][0] == tITEM_INFO->iBonusSkillInfo[0][0])
			{
				if (tTotalSearchItemNum < 1000)
				{
					tSearchItemIndex[tTotalSearchItemNum] = mSharedItemData.mPART[(iLevel - 1)][(tITEM_INFO->iType - 1)][(tITEM_INFO->iSort - 1)][index01];
					tTotalSearchItemNum++;
				}
			}
		}
	}
	if (tTotalSearchItemNum == 0)
	{
		return NULL;
	}
	tRandom = rand();
	return &mSharedItemData.mDATA[tSearchItemIndex[(tRandom % tTotalSearchItemNum)]];
}
#endif
ITEM_INFO* ITEMSYSTEM::ReturnRareItem(int iTribe, int iLevel)
{
	int iSortNum = 0;
	int iSort[9] = { 0, };
	unsigned int tRandom = 0;
	ITEM_INFO* pItemInfoPtr = NULL;

	iSort[0] = 7;   // ....
	iSort[1] = 9;   // ...
	iSort[2] = 10;  // ...
	iSort[3] = 11;  // ...
	iSort[4] = 12;  // ...

	switch (iTribe) {
	case 0: // ...
		iSort[5] = 13;  // ..
		iSort[6] = 14;  // ..
		iSort[7] = 15;  // ...
		break;
	case 1: // ...
		iSort[5] = 16;  // ...
		iSort[6] = 17;  // ...
		iSort[7] = 18;  // ...
		break;
	case 2: // ...
		iSort[5] = 19;  // ...
		iSort[6] = 20;  // ...
		iSort[7] = 21;  // ....
		break;
	default: // .. ...
		return NULL;
	}

	tRandom = rand();
	iSortNum = iSort[tRandom % 8];

	while (true) {
		pItemInfoPtr = Return(iLevel, 3, iSortNum);
		if (pItemInfoPtr != NULL) {
			if ((pItemInfoPtr->iEquipInfo[0] == 1) || ((pItemInfoPtr->iEquipInfo[0] - 2) == iTribe))
				break;

			pItemInfoPtr = NULL;
		}
	}

	return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::ReturnRareItem(int iTribe, int iType, int iLevel)
{
	int iSortNum = 0;
	int iSort[9] = { 0, };
	unsigned int tRandom = 0;
	ITEM_INFO* pItemInfoPtr = NULL;

	iSort[0] = 7;   // ....
	iSort[1] = 9;   // ...
	iSort[2] = 10;  // ...
	iSort[3] = 11;  // ...
	iSort[4] = 12;  // ...

	switch (iTribe) {
	case 0: // ...
		iSort[5] = 13;  // ..
		iSort[6] = 14;  // ..
		iSort[7] = 15;  // ...
		break;
	case 1: // ...
		iSort[5] = 16;  // ...
		iSort[6] = 17;  // ...
		iSort[7] = 18;  // ...
		break;
	case 2: // ...
		iSort[5] = 19;  // ...
		iSort[6] = 20;  // ...
		iSort[7] = 21;  // ....
		break;
	default: // .. ...
		return NULL;
	}

	tRandom = rand();
	iSortNum = iSort[tRandom % 8];

	while (true) {
		pItemInfoPtr = Return(iLevel, iType, iSortNum);
		if (pItemInfoPtr != NULL) {
			if ((pItemInfoPtr->iEquipInfo[0] == 1) || ((pItemInfoPtr->iEquipInfo[0] - 2) == iTribe))
				break;

			pItemInfoPtr = NULL;
		}
	}

	return pItemInfoPtr;
}

ITEM_INFO* ITEMSYSTEM::GetResultItemPtrByGigabyteItem(void)
{
	int iRandom = 0, iResultItemIndex = 0;
	iRandom = rand() % 1000;
	if (iRandom < 450) // 45.00%
		iResultItemIndex = 3;
	else if (iRandom < 700) // 25.00%
		iResultItemIndex = 4;
	else if (iRandom < 800) // 10.00%
		iResultItemIndex = 27;
	else if (iRandom < 860) // 6.00%
		iResultItemIndex = 28;
	else if (iRandom < 900) // 4.00%
		iResultItemIndex = 23;
	else if (iRandom < 930) // 3.00%
		iResultItemIndex = 29;
	else if (iRandom < 955) // 2.50%
		iResultItemIndex = 24;
	else if (iRandom < 975) // 2.00%
		iResultItemIndex = 30;
	else if (iRandom < 990) // 1.50%
		iResultItemIndex = 32;
	else
		iResultItemIndex = 33;

	return Search(iResultItemIndex);
}

ITEM_INFO* ITEMSYSTEM::GetMoneyBy1WonLuckyBag(void)
{
	int iRandom = 0;
	int tItemIndex = 0;
	iRandom = rand() % 10000;
	if (iRandom < 3000) {
		tItemIndex = 1308;
	}
	else if (iRandom < 3350) {
		tItemIndex = 1310;
	}
	else if (iRandom < 5350) {
		tItemIndex = 1019;
	}
	else if (iRandom < 6350) {
		tItemIndex = 1045;
	}
	else if (iRandom < 8150) {
		tItemIndex = 1020;
	}
	else if (iRandom < 8950) {
		tItemIndex = 1036;
	}
	else if (iRandom < 9950) {
		tItemIndex = 1021;
	}
	else if (iRandom < 9999) {
		tItemIndex = 1035;
	}
	else {
		tItemIndex = 1103;
	}
	return Search(tItemIndex); // ....
}

ITEM_INFO* ITEMSYSTEM::GetPresentItemPtrByGoodwillAmbassador(int& iCounts)
{
	int iRandom = 0;

	iCounts = 0;
	iRandom = rand() % 1000;

	return Search(322);
	//if (iRandom < 400) {
	//	return Search(1036);     // ... (.).
	//}
	//else if (iRandom < 700) {
	//	return Search(1037);     // ... (.)
	//}
	//else if (iRandom < 900) {
	//	return Search(1022);   // ... (9%)
	//}
	//else if (iRandom < 990) {
	//	return Search(1047);   // 1. ....
	//}
	//else {
	//	return Search(1108);   // . ...
	//}
	return NULL;
}

int ITEMSYSTEM::ReturnItemForTransfer(int tItemIndex, int tNewWeaponType, int tNewTribe, int tOldTribe)
{
	ITEM_INFO* tITEM_INFO;
	int index01;

	tITEM_INFO = Search(tItemIndex);
	if (tITEM_INFO == NULL)
	{
		return 0;
	}
	for (index01 = 0; index01 < 100000; index01++)
	{
		if (mSharedItemData.mDATA[index01].iType == tITEM_INFO->iType && mSharedItemData.mDATA[index01].iSort == tNewWeaponType && mSharedItemData.mDATA[index01].iEquipInfo[0] == tNewTribe &&
			mSharedItemData.mDATA[index01].iLevel == tITEM_INFO->iLevel && mSharedItemData.mDATA[index01].iMartialLevel == tITEM_INFO->iMartialLevel &&
			mSharedItemData.mDATA[index01].iLevelLimit == tITEM_INFO->iLevelLimit && mSharedItemData.mDATA[index01].iMartialLevelLimit == tITEM_INFO->iMartialLevelLimit &&
			mSharedItemData.mDATA[index01].iCheckItemSet == tITEM_INFO->iCheckItemSet && mSharedItemData.mDATA[index01].iCheckAvatarTrade == tITEM_INFO->iCheckAvatarTrade)
		{
			return mSharedItemData.mDATA[index01].iIndex;
		}
	}
}
int ITEMSYSTEM::ReturnItemForTransfer2(int tItemIndex, int tNewTribe, int tOldTribe, int tSort)
{
	ITEM_INFO* tITEM_INFO;
	int index01;

	tITEM_INFO = Search(tItemIndex);
	if (tITEM_INFO == NULL)
	{
		return 0;
	}
	if (tSort == 1)
	{
		switch (tOldTribe)
		{
		case 0:
			if (tNewTribe == 1)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex + 4;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex + 3;
				}
				else
				{
					return tITEM_INFO->iIndex + 1;
				}
			}
			if (tNewTribe == 2)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex + 8;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex + 6;
				}
				else
				{
					return tITEM_INFO->iIndex + 2;
				}
			}
			break;
		case 1:
			if (tNewTribe == 0)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex - 4;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex - 3;
				}
				else
				{
					return tITEM_INFO->iIndex - 1;
				}
			}
			if (tNewTribe == 2)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex + 4;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex - 6;
				}
				else
				{
					return tITEM_INFO->iIndex + 1;
				}
			}
			break;
		case 2:
			if (tNewTribe == 0)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex - 8;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex - 6;
				}
				else
				{
					return tITEM_INFO->iIndex - 2;
				}
			}
			if (tNewTribe == 1)
			{
				if (tITEM_INFO->iIndex >= 1385 && tITEM_INFO->iIndex <= 1396)
				{
					return tITEM_INFO->iIndex - 4;
				}
				else if (tITEM_INFO->iIndex >= 125 && tITEM_INFO->iIndex <= 142)
				{
					return tITEM_INFO->iIndex - 3;
				}
				else
				{
					return tITEM_INFO->iIndex - 1;
				}
			}
			break;
		}
	}
	else if (tSort == 2)
	{
		switch (tOldTribe)
		{
		case 0:
			if (tNewTribe == 1)
			{
				return tITEM_INFO->iIndex + 4;
			}
			if (tNewTribe == 2)
			{
				return tITEM_INFO->iIndex + 8;
			}
			break;
		case 1:
			if (tNewTribe == 0)
			{
				return tITEM_INFO->iIndex - 4;
			}
			if (tNewTribe == 2)
			{
				return tITEM_INFO->iIndex + 4;
			}
			break;
		case 2:
			if (tNewTribe == 0)
			{
				return tITEM_INFO->iIndex - 8;
			}
			if (tNewTribe == 1)
			{
				return tITEM_INFO->iIndex - 4;
			}
			break;
		}
	}
}
int ITEMSYSTEM::ReturnLegendDecoStats(int tMode, int tEquipImproveValue)
{
	int tISValue = 0;
	int tIUValue = 0;
	int tRFValue = 0;
	int t4thValue = 0;
	int tAddValue = 0;

	if (!tEquipImproveValue)
	{
		return 0;
	}

	tISValue = mUTIL.ReturnISValue(tEquipImproveValue);
	tIUValue = mUTIL.ReturnIUValue(tEquipImproveValue);
	tRFValue = mUTIL.ReturnRFValue(tEquipImproveValue);
	t4thValue = mUTIL.Return4thValue(tEquipImproveValue);

	tAddValue = ReturnDecoUpStat(1, tMode, tISValue);
	tAddValue += ReturnDecoUpStat(1, tMode, tIUValue);
	tAddValue += ReturnDecoUpStat(1, tMode, tRFValue);
	tAddValue += ReturnDecoUpStat(2, tMode, t4thValue);
	return tAddValue;
}
int ITEMSYSTEM::ReturnDecoUpStat(int tSort, int tMode, int tImproveValue)
{
	if (tSort == 1)
	{
		switch (tMode)
		{
		case 1:
			if (tImproveValue >= 41 && tImproveValue <= 60)
			{
				return 100 * (tImproveValue - 40);
			}
			break;
		case 2:
			if (tImproveValue >= 61 && tImproveValue <= 80)
			{
				return 125 * (tImproveValue - 60);
			}
			break;
		case 4:
			if (tImproveValue >= 1 && tImproveValue <= 20)
			{
				return 50 * tImproveValue;
			}
			break;
		case 8:
			if (tImproveValue >= 81 && tImproveValue <= 100)
			{
				return 50 * (tImproveValue - 80);
			}
			break;
		default:
			break;
		}
		return 0;
	}
	else if (tSort == 2)
	{
		switch (tMode)
		{
		case 1:
			if ((tImproveValue >= 1 && tImproveValue <= 5) || (tImproveValue >= 26 && tImproveValue <= 30))
			{
				return 400;
			}
			else if ((tImproveValue >= 6 && tImproveValue <= 10) || (tImproveValue >= 31 && tImproveValue <= 35))
			{
				return 800;
			}
			else if ((tImproveValue >= 11 && tImproveValue <= 15) || (tImproveValue >= 36 && tImproveValue <= 40))
			{
				return 1200;
			}
			else if ((tImproveValue >= 16 && tImproveValue <= 20) || (tImproveValue >= 41 && tImproveValue <= 45))
			{
				return 1600;
			}
			else if ((tImproveValue >= 21 && tImproveValue <= 25) || (tImproveValue >= 46 && tImproveValue <= 50))
			{
				return 200;
			}
			break;
		case 2:
			return 0;
		case 4:
			if (tImproveValue >= 1 && tImproveValue <= 25)
			{
				switch (tImproveValue % 5)
				{
				case 1: return 200;
				case 2: return 400;
				case 3: return 600;
				case 4: return 800;
				default:
					if ((tImproveValue % 5) == 0)
					{
						return 1000;
					}
					break;
				}
			}
			break;
		case 6:
			return 0;
		case 8:
			if (tImproveValue >= 26 && tImproveValue <= 50)
			{
				switch (tImproveValue % 5)
				{
				case 1: return 200;
				case 2: return 400;
				case 3: return 600;
				case 4: return 800;
				default:
					if ((tImproveValue % 5) == 0)
					{
						return 1000;
					}
					break;
				}
			}
			break;
		}
		return 0;
	}
}




SKILLSYSTEM mSKILL;

SKILLSYSTEM::SKILLSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
}
//CHECK_VALID_ELEMENT
BOOL SKILLSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].sIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].sIndex < 1) || (mDATA[tArrayIndex].sIndex > 312))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].sIndex != (tArrayIndex + 1))
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].sName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 10; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].sDescription[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].sType < 1) || (mDATA[tArrayIndex].sType > 4))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sAttackType < 1) || (mDATA[tArrayIndex].sAttackType > 5))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sDataNumber2D < 1) || (mDATA[tArrayIndex].sDataNumber2D > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTribeInfo[0] < 1) || (mDATA[tArrayIndex].sTribeInfo[0] > 4))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTribeInfo[1] < 1) || (mDATA[tArrayIndex].sTribeInfo[1] > 10))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sLearnSkillPoint < 1) || (mDATA[tArrayIndex].sLearnSkillPoint > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sMaxUpgradePoint < 1) || (mDATA[tArrayIndex].sMaxUpgradePoint > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sTotalHitNumber < 0) || (mDATA[tArrayIndex].sTotalHitNumber > 10))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].sValidRadius < 0) || (mDATA[tArrayIndex].sValidRadius > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sManaUse < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sManaUse > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[0] > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRecoverInfo[1] > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunAttack > 100))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunDefense > 100))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sFastRunSpeed > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[0] > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[1] > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackInfo[2] > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRunTime < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRunTime > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sChargingDamageUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackPowerUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sDefensePowerUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackSuccessUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackBlockUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sElementAttackUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sElementDefenseUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sAttackSpeedUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sRunSpeedUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sShieldLifeUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sLuckUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sCriticalUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sReturnSuccessUp > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sStunDefenseUp > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp < 0) || (mDATA[tArrayIndex].sGradeInfo[index01].sDestroySuccessUp > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL SKILLSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	SKILL_INFO* tDATA;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}

	CopyMemory(&tDataNum, &tOriginal[0], 4);
	if (tDataNum != 300)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	tDATA = (SKILL_INFO*)calloc(1, (tDataNum * sizeof(SKILL_INFO)));
	if (tDATA == NULL)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[4], (tDataNum * sizeof(SKILL_INFO)));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);

	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//FREE
void SKILLSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
}
//SEARCH
SKILL_INFO* SKILLSYSTEM::Search(int sIndex)
{
	if ((sIndex < 1) || (sIndex > mDataNum))
	{
		return NULL;
	}
	if (mDATA[(sIndex - 1)].sIndex == 0)
	{
		return NULL;
	}
	return &mDATA[(sIndex - 1)];
}
//RETURN_ATTACK_TYPE
int SKILLSYSTEM::ReturnAttackType(int sIndex)
{
	SKILL_INFO* tSKILL_INFO;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0;
	}
	return tSKILL_INFO->sAttackType;
}
//RETURN_TOTAL_HIT_NUMBER
int SKILLSYSTEM::ReturnTotalHitNumber(int sIndex)
{
	SKILL_INFO* tSKILL_INFO;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0;
	}
	return tSKILL_INFO->sTotalHitNumber;
}
//RETURN_SKILL_VALUE
float SKILLSYSTEM::ReturnSkillValue(int sIndex, int sPoint, int sFactor)
{
	SKILL_INFO* tSKILL_INFO;
	int tMinValue;
	int tMaxValue;
	float tValue;

	tSKILL_INFO = Search(sIndex);
	if (tSKILL_INFO == NULL)
	{
		return 0.0f;
	}
	if (sPoint < 1)
	{
		return 0.0f;
	}
	switch (sFactor)
	{
	case  1:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sManaUse;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sManaUse;
		break;
	case  2:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[0];
		break;
	case  3:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRecoverInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRecoverInfo[1];
		break;
	case  4:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunAttack;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunAttack;
		break;
	case  5:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefense;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefense;
		break;
	case  6:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sFastRunSpeed;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sFastRunSpeed;
		break;
	case  7:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[0];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[0];
		break;
	case  8:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[1];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[1];
		break;
	case  9:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackInfo[2];
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackInfo[2];
		break;
	case 10:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunTime;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunTime;
		break;
	case 11:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sChargingDamageUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sChargingDamageUp;
		break;
	case 12:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackPowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackPowerUp;
		break;
	case 13:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDefensePowerUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDefensePowerUp;
		break;
	case 14:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSuccessUp;
		break;
	case 15:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackBlockUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackBlockUp;
		break;
	case 16:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementAttackUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementAttackUp;
		break;
	case 17:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sElementDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sElementDefenseUp;
		break;
	case 18:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sAttackSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sAttackSpeedUp;
		break;
	case 19:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sRunSpeedUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sRunSpeedUp;
		break;
	case 20:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sShieldLifeUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sShieldLifeUp;
		break;
	case 21:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sLuckUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sLuckUp;
		break;
	case 22:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sCriticalUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sCriticalUp;
		break;
	case 23:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sReturnSuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sReturnSuccessUp;
		break;
	case 24:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sStunDefenseUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sStunDefenseUp;
		break;
	case 25:
		tMinValue = tSKILL_INFO->sGradeInfo[0].sDestroySuccessUp;
		tMaxValue = tSKILL_INFO->sGradeInfo[1].sDestroySuccessUp;
		break;
	default:
		return 0.0f;
	}
	tValue = (float)tMinValue + (float)((tMaxValue - tMinValue) * sPoint) / (float)tSKILL_INFO->sMaxUpgradePoint;
	if (tValue <= 0.0f)
	{
		return 0.0f;
	}
	if (tValue < 1.0f)
	{
		return 1.0f;
	}
	return tValue;
}
void SKILLSYSTEM::ChangeSkillForTransfer(int tUserIndex, int tNewTribe)
{
	int index01;
	int index02;
	int HR = 0;
	int HB = 0;
	int GP = 0;
	int HF = 0;
	int HS = 0;
	int HI = 0;
	int NineSkill = 0;
	int TenSkill = 0;

	for (index01 = 0; index01 < 40; index01++)
	{
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 82)
		{
			HS = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 83)
		{
			HB = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 84)
		{
			GP = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 103)
		{
			HR = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 104)
		{
			HF = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 105)
		{
			HI = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 123 ||
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 127 ||
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 135)
		{
			NineSkill = 1;
		}
		if (mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 124 ||
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 128 ||
			mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] == 136)
		{
			TenSkill = 1;
		}
	}
	for (index01 = 0; index01 < 40; index01++)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][0] = 0;
		mUSER[tUserIndex].mAvatarInfo.aSkill[index01][1] = 0;
	}
	if (HS == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[10][0] = 82;
		mUSER[tUserIndex].mAvatarInfo.aSkill[10][1] = 1;
	}
	if (HB == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[11][0] = 83;
		mUSER[tUserIndex].mAvatarInfo.aSkill[11][1] = 1;
	}
	if (GP == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[12][0] = 84;
		mUSER[tUserIndex].mAvatarInfo.aSkill[12][1] = 1;
	}
	if (HR == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[13][0] = 103;
		mUSER[tUserIndex].mAvatarInfo.aSkill[13][1] = 50;
	}
	if (HF == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[14][0] = 104;
		mUSER[tUserIndex].mAvatarInfo.aSkill[14][1] = 50;
	}
	if (HI == 1)
	{
		mUSER[tUserIndex].mAvatarInfo.aSkill[15][0] = 105;
		mUSER[tUserIndex].mAvatarInfo.aSkill[15][1] = 50;
	}
	switch (tNewTribe)
	{
	case 0:
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][0] = 1;
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][1] = 1;
		if (NineSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][0] = 123;
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][1] = 1;
		}
		if (TenSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][0] = 124;
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][1] = 1;
		}
		break;
	case 1:
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][0] = 20;
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][1] = 1;
		if (NineSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][0] = 127;
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][1] = 1;
		}
		if (TenSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][0] = 128;
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][1] = 1;
		}
		break;
	case 2:
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][0] = 39;
		mUSER[tUserIndex].mAvatarInfo.aSkill[0][1] = 1;
		if (NineSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][0] = 135;
			mUSER[tUserIndex].mAvatarInfo.aSkill[20][1] = 1;
		}
		if (TenSkill == 1)
		{
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][0] = 136;
			mUSER[tUserIndex].mAvatarInfo.aSkill[21][1] = 1;
		}
		break;
	}
	mUSER[tUserIndex].mAvatarInfo.aSkillPoint = 1050;
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < MAX_HOT_KEY_NUM; index02++)
		{
			if (mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] != 3)
			{
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][0] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][1] = 0;
				mUSER[tUserIndex].mAvatarInfo.aHotKey[index01][index02][2] = 0;
			}
		}
	}
}






MONSTERSYSTEM mMONSTER;

MONSTERSYSTEM::MONSTERSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL MONSTERSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (mDATA[tArrayIndex].mIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].mIndex < 1) || (mDATA[tArrayIndex].mIndex > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mIndex != (tArrayIndex + 1))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 25; index01++)
	{
		if (mDATA[tArrayIndex].mName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 2; index01++)
	{
		for (index02 = 0; index02 < 101; index02++)
		{
			if (mDATA[tArrayIndex].mChatInfo[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 101)
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mType < 1) || (mDATA[tArrayIndex].mType > 15))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSpecialType < 1) || (mDATA[tArrayIndex].mSpecialType > 51))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDamageType < 1) || (mDATA[tArrayIndex].mDamageType > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDataSortNumber3D < 1) || (mDATA[tArrayIndex].mDataSortNumber3D > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mSize[index01] < 1) || (mDATA[tArrayIndex].mSize[index01] > 1000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mSize[3] < 0) || (mDATA[tArrayIndex].mSize[3] > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSizeCategory < 1) || (mDATA[tArrayIndex].mSizeCategory > 4))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mCheckCollision < 1) || (mDATA[tArrayIndex].mCheckCollision > 2))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 6; index01++)
	{
		if ((mDATA[tArrayIndex].mFrameInfo[index01] < 1) || (mDATA[tArrayIndex].mFrameInfo[index01] > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mTotalHitNum < 0) || (mDATA[tArrayIndex].mTotalHitNum > 3))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mHitFrame[index01] < 0) || (mDATA[tArrayIndex].mHitFrame[index01] > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mTotalSkillHitNum < 0) || (mDATA[tArrayIndex].mTotalSkillHitNum > 3))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].mSkillHitFrame[index01] < 0) || (mDATA[tArrayIndex].mSkillHitFrame[index01] > 10000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mBulletInfo[0] < 1) || (mDATA[tArrayIndex].mBulletInfo[0] > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mBulletInfo[1] < 1) || (mDATA[tArrayIndex].mBulletInfo[1] > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSummonTime[0] < 1) || (mDATA[tArrayIndex].mSummonTime[0] > 1000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mSummonTime[1] < 1) || (mDATA[tArrayIndex].mSummonTime[1] > 1000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mSummonTime[0] > mDATA[tArrayIndex].mSummonTime[1])
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mItemLevel < 1) || (mDATA[tArrayIndex].mItemLevel > MAX_LIMIT_LEVEL_NUM))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].mMartialItemLevel < 0) || (mDATA[tArrayIndex].mMartialItemLevel > 12))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].mRealLevel < 1) || (mDATA[tArrayIndex].mRealLevel > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#ifdef __GOD__
	if ((mDATA[tArrayIndex].mMartialRealLevel < 0) || (mDATA[tArrayIndex].mMartialRealLevel > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
#endif
	if ((mDATA[tArrayIndex].mGeneralExperience < 0) || (mDATA[tArrayIndex].mGeneralExperience > 100000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mPatExperience < 0) || (mDATA[tArrayIndex].mPatExperience > 100000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mLife < 1) || (mDATA[tArrayIndex].mLife > MAX_NUMBER_SIZE))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackType < 1) || (mDATA[tArrayIndex].mAttackType > 6))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRadiusInfo[0] < 0) || (mDATA[tArrayIndex].mRadiusInfo[0] > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRadiusInfo[1] < 0) || (mDATA[tArrayIndex].mRadiusInfo[1] > 10000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mRadiusInfo[0] > mDATA[tArrayIndex].mRadiusInfo[1])
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mWalkSpeed < 0) || (mDATA[tArrayIndex].mWalkSpeed > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mRunSpeed < 0) || (mDATA[tArrayIndex].mRunSpeed > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDeathSpeed < 0) || (mDATA[tArrayIndex].mDeathSpeed > 1000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackPower < 0) || (mDATA[tArrayIndex].mAttackPower > 300000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDefensePower < 0) || (mDATA[tArrayIndex].mDefensePower > 300000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackSuccess < 0) || (mDATA[tArrayIndex].mAttackSuccess > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mAttackBlock < 0) || (mDATA[tArrayIndex].mAttackBlock > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mElementAttackPower < 0) || (mDATA[tArrayIndex].mElementAttackPower > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mElementDefensePower < 0) || (mDATA[tArrayIndex].mElementDefensePower > 100000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mCritical < 0) || (mDATA[tArrayIndex].mCritical > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mFollowInfo[0] < 0) || (mDATA[tArrayIndex].mFollowInfo[0] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mFollowInfo[1] < 0) || (mDATA[tArrayIndex].mFollowInfo[1] > 100))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mFollowInfo[0] > mDATA[tArrayIndex].mFollowInfo[1])
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mNewKRInfo < 0)
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mNewKRInfo / 100) != 2 &&
		(mDATA[tArrayIndex].mNewKRInfo / 100) != 3 &&
		(mDATA[tArrayIndex].mNewKRInfo / 100) != 4 &&
		(mDATA[tArrayIndex].mNewKRInfo / 100) != 5 &&
		(mDATA[tArrayIndex].mNewKRInfo))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[0] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[0] > 1000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[1] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[1] > 100000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropMoneyInfo[2] < 0) || (mDATA[tArrayIndex].mDropMoneyInfo[2] > 100000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if (mDATA[tArrayIndex].mDropMoneyInfo[1] > mDATA[tArrayIndex].mDropMoneyInfo[2])
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		if ((mDATA[tArrayIndex].mDropPotionInfo[index01][0] < 0) || (mDATA[tArrayIndex].mDropPotionInfo[index01][0] > 1000000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].mDropPotionInfo[index01][1] < 0) || (mDATA[tArrayIndex].mDropPotionInfo[index01][1] > 99999))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 12; index01++)
	{
		if ((mDATA[tArrayIndex].mDropItemInfo[index01] < 0) || (mDATA[tArrayIndex].mDropItemInfo[index01] > 1000000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].mDropQuestItemInfo[0] < 0) || (mDATA[tArrayIndex].mDropQuestItemInfo[0] > 1000000))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	if ((mDATA[tArrayIndex].mDropQuestItemInfo[1] < 0) || (mDATA[tArrayIndex].mDropQuestItemInfo[1] > 99999))
	{
		mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	for (index01 = 0; index01 < 50; index01++)
	{
		if ((mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] < 0) || (mDATA[tArrayIndex].mDropExtraItemInfo[index01][0] > 1000000))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
		if ((mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] < 0) || (mDATA[tArrayIndex].mDropExtraItemInfo[index01][1] > 99999))
		{
			mLog("! [%s] %d\n", __FUNCTION__, __LINE__);
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL MONSTERSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	MONSTER_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize = 4;
	if (tDataNum != 10000)
	{
		return FALSE;
	}
	tDATA = (MONSTER_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(MONSTER_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[mSharedMemSize], (tDataNum * sizeof(MONSTER_INFO)));
	mSharedMemSize += (tDataNum * sizeof(MONSTER_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_MONSTERSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedMonsterData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4; //+= mSharedMemSize
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(MONSTER_INFO)));
	}
	mSharedMonsterData.mDATA = (MONSTER_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(MONSTER_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void MONSTERSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		//shmdt( mSharedPostMem );
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		//shmctl(mSharedMemMap, IPC_RMID, 0);
		mSharedMemMap = 0;
	}
}
//SEARCH
MONSTER_INFO* MONSTERSYSTEM::Search(int mIndex)
{
	if ((mIndex < 1) || (mIndex > mSharedMonsterData.mDataNum))
	{
		return NULL;
	}
	if (mSharedMonsterData.mDATA[(mIndex - 1)].mIndex == 0)
	{
		return NULL;
	}
	return &mSharedMonsterData.mDATA[(mIndex - 1)];
}
//SEARCH
MONSTER_INFO* MONSTERSYSTEM::Search(int tMonsterType, int tMonsterSpecialType)
{
	int index01;

	for (index01 = 0; index01 < mSharedMonsterData.mDataNum; index01++)
	{
		if (mSharedMonsterData.mDATA[index01].mIndex == 0)
		{
			continue;
		}
		if ((mSharedMonsterData.mDATA[index01].mType == tMonsterType) && (mSharedMonsterData.mDATA[index01].mSpecialType == tMonsterSpecialType))
		{
			return &mSharedMonsterData.mDATA[index01];
		}
	}
	//SVR_TRACE();
	return NULL;
}




NPCSYSTEM mNPC;

NPCSYSTEM::NPCSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL NPCSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;
	int index03;
	int index04;

	if (mDATA[tArrayIndex].nIndex == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].nIndex < 1) || (mDATA[tArrayIndex].nIndex > 500))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].nIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 28; index01++)
	{
		if (mDATA[tArrayIndex].nName[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 25)
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nSpeechNum < 1) || (mDATA[tArrayIndex].nSpeechNum > 5))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		for (index02 = 0; index02 < 5; index02++)
		{
			for (index03 = 0; index03 < 51; index03++)
			{
				if (mDATA[tArrayIndex].nSpeech[index01][index02][index03] == '\0')
				{
					break;
				}
			}
			if (index03 == 51)
			{
				return FALSE;
			}
		}
	}
	if ((mDATA[tArrayIndex].nTribe < 1) || (mDATA[tArrayIndex].nTribe > 5))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nType < 1) || (mDATA[tArrayIndex].nType > 17))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nDataSortNumber2D < 1) || (mDATA[tArrayIndex].nDataSortNumber2D > 10000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].nDataSortNumber3D < 1) || (mDATA[tArrayIndex].nDataSortNumber3D > 10000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].nSize[index01] < 1) || (mDATA[tArrayIndex].nSize[index01] > 1000))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 50; index01++)
	{
		if ((mDATA[tArrayIndex].nMenu[index01] < 1) || (mDATA[tArrayIndex].nMenu[index01] > 2))
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 28; index02++)
		{
			if ((mDATA[tArrayIndex].nShopInfo[index01][index02] < 0) || (mDATA[tArrayIndex].nShopInfo[index01][index02] > 99999))
			{
				return FALSE;
			}
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 8; index02++)
		{
			if ((mDATA[tArrayIndex].nSkillInfo1[index01][index02] < 0) || (mDATA[tArrayIndex].nSkillInfo1[index01][index02] > 300))
			{
				return FALSE;
			}
		}
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		for (index02 = 0; index02 < 3; index02++)
		{
			for (index03 = 0; index03 < 3; index03++)
			{
				for (index04 = 0; index04 < 8; index04++)
				{
					if ((mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] < 0) || (mDATA[tArrayIndex].nSkillInfo2[index01][index02][index03][index04] > 300))
					{
						return FALSE;
					}
				}
			}
		}
	}
	for (index01 = 0; index01 < 145; index01++)
	{
		for (index02 = 0; index02 < 15; index02++)
		{
			if ((mDATA[tArrayIndex].nGambleCostInfo[index01][index02] < 0) || (mDATA[tArrayIndex].nGambleCostInfo[index01][index02] > 100000000))
			{
				return FALSE;
			}
		}
	}
	return TRUE;
}
//INIT
BOOL NPCSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	NPC_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize = 4;
	if (tDataNum != 500)
	{
		return FALSE;
	}
	tDATA = (NPC_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(NPC_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[mSharedMemSize], (tDataNum * sizeof(NPC_INFO)));
	mSharedMemSize += (tDataNum * sizeof(NPC_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_NPCSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedNPCData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4; // += mSharedMemSize
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(NPC_INFO)));
	}
	mSharedNPCData.mDATA = (NPC_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(NPC_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		GlobalFree(mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void NPCSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = 0;
	}
}
//SEARCH
NPC_INFO* NPCSYSTEM::Search(int nIndex)
{
	if ((nIndex < 1) || (nIndex > mSharedNPCData.mDataNum))
	{
		return NULL;
	}
	if (mSharedNPCData.mDATA[(nIndex - 1)].nIndex == 0)
	{
		return NULL;
	}
	return &mSharedNPCData.mDATA[(nIndex - 1)];
}




QUESTSYSTEM mQUEST;

QUESTSYSTEM::QUESTSYSTEM(void)
{
	mDataNum = 0;
	mDATA = NULL;
	mSharedMemMap = 0;
	mSharedPostMem = NULL;
}
//CHECK_VALID_ELEMENT
BOOL QUESTSYSTEM::CheckValidElement(int tArrayIndex)
{
	int index01;
	int index02;

	if (strcmp(mDATA[tArrayIndex].qSubject, "") == 0)
	{
		return TRUE;
	}
	if ((mDATA[tArrayIndex].qIndex < 1) || (mDATA[tArrayIndex].qIndex > 1000))
	{
		return FALSE;
	}
	if (mDATA[tArrayIndex].qIndex != (tArrayIndex + 1))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 51; index01++)
	{
		if (mDATA[tArrayIndex].qSubject[index01] == '\0')
		{
			break;
		}
	}
	if (index01 == 51)
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qCategory < 1) || (mDATA[tArrayIndex].qCategory > 4))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qStep < 1) || (mDATA[tArrayIndex].qStep > 1000))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qLevel < 1) || (mDATA[tArrayIndex].qLevel > 145))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qType < 1) || (mDATA[tArrayIndex].qType > 2))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qSort < 1) || (mDATA[tArrayIndex].qSort > 8))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qSummonInfo[0] < 0) || (mDATA[tArrayIndex].qSummonInfo[0] > 200))
	{
		return FALSE;
	}
	if ((mDATA[tArrayIndex].qStartNPCNumber < 1) || (mDATA[tArrayIndex].qStartNPCNumber > 500))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 5; index01++)
	{
		if ((mDATA[tArrayIndex].qKeyNPCNumber[index01] < 0) || (mDATA[tArrayIndex].qKeyNPCNumber[index01] > 500))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].qEndNPCNumber < 1) || (mDATA[tArrayIndex].qEndNPCNumber > 500))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 3; index01++)
	{
		if ((mDATA[tArrayIndex].qReward[index01][0] < 1) || (mDATA[tArrayIndex].qReward[index01][0] > 6))
		{
			return FALSE;
		}
		if ((mDATA[tArrayIndex].qReward[index01][1] < 0) || (mDATA[tArrayIndex].qReward[index01][1] > 100000000))
		{
			return FALSE;
		}
	}
	if ((mDATA[tArrayIndex].qNextIndex < 0) || (mDATA[tArrayIndex].qNextIndex > 1000))
	{
		return FALSE;
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qStartSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qHurrySpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech1[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech2[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech3[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech4[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qProcessSpeech5[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qSuccessSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qFailureSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	for (index01 = 0; index01 < 15; index01++)
	{
		for (index02 = 0; index02 < 51; index02++)
		{
			if (mDATA[tArrayIndex].qCallSpeech[index01][index02] == '\0')
			{
				break;
			}
		}
		if (index02 == 51)
		{
			return FALSE;
		}
	}
	return TRUE;
}
//INIT
BOOL QUESTSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	QUEST_INFO* tDATA;
	BOOL tCheckFirstCreate;

	Free();
	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	mSharedMemSize = 0;
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	mSharedMemSize += 4;
	if (tDataNum != 1000)
	{
		return FALSE;
	}
	tDATA = (QUEST_INFO*)GlobalAlloc(GMEM_FIXED, (tDataNum * sizeof(QUEST_INFO)));
	if (tDATA == NULL)
	{
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[4], (tDataNum * sizeof(QUEST_INFO)));
	mSharedMemSize += (tDataNum * sizeof(QUEST_INFO));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDataNum = tDataNum;
	mDATA = tDATA;
	for (index01 = 0; index01 < mDataNum; index01++)
	{
		if (!CheckValidElement(index01))
		{
			return FALSE;
		}
	}
	mSharedMemMap = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, mSharedMemSize, "SHAREMEM_QUESTSYSTEM");
	if (mSharedMemMap == NULL)
	{
		return FALSE;
	}
	if (GetLastError() != ERROR_ALREADY_EXISTS)
	{
		tCheckFirstCreate = TRUE;
	}
	else
	{
		tCheckFirstCreate = FALSE;
	}
	mSharedPostMem = (BYTE*)MapViewOfFile(mSharedMemMap, FILE_MAP_ALL_ACCESS, 0, 0, mSharedMemSize);
	if (mSharedPostMem == NULL)
	{
		return FALSE;
	}
	mSharedMemSizeForCheck = 0;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], &mDataNum, 4);
	}
	CopyMemory(&mSharedQuestData.mDataNum, &mSharedPostMem[mSharedMemSizeForCheck], 4);
	mSharedMemSizeForCheck += 4;
	if (tCheckFirstCreate)
	{
		CopyMemory(&mSharedPostMem[mSharedMemSizeForCheck], mDATA, (mDataNum * sizeof(QUEST_INFO)));
	}
	mSharedQuestData.mDATA = (QUEST_INFO*)&mSharedPostMem[mSharedMemSizeForCheck];
	mSharedMemSizeForCheck += (mDataNum * sizeof(QUEST_INFO));
	if (mSharedMemSize != mSharedMemSizeForCheck)
	{
		return FALSE;
	}
	mDataNum = 0;
	if (mDATA)
	{
		HeapFree(GetProcessHeap(), 0, mDATA);
		mDATA = NULL;
	}
	return TRUE;
}
//FREE
void QUESTSYSTEM::Free(void)
{
	mDataNum = 0;
	if (mDATA)
	{
		free(mDATA);
		mDATA = NULL;
	}
	if (mSharedPostMem != NULL)
	{
		UnmapViewOfFile(mSharedPostMem);
		mSharedPostMem = NULL;
	}
	if (mSharedMemMap != 0)
	{
		CloseHandle(mSharedMemMap);
		mSharedMemMap = 0;
	}
}
//SEARCH
QUEST_INFO* QUESTSYSTEM::Search(int qTribe, int qStep)
{
	int index01;

	for (index01 = 0; index01 < mSharedQuestData.mDataNum; index01++)
	{
		if (strcmp(mSharedQuestData.mDATA[index01].qSubject, "") == 0)
		{
			continue;
		}
		if ((mSharedQuestData.mDATA[index01].qCategory == (qTribe + 1)) && (mSharedQuestData.mDATA[index01].qStep == qStep))
		{
			return &mSharedQuestData.mDATA[index01];
		}
	}
	return NULL;
}




PATSYSTEM mPAT;

PATSYSTEM::PATSYSTEM(void)
{
	mMaxRangeValue[0] = 40000000;
	mMaxRangeValue[1] = 80000000;
	mMaxRangeValue[2] = 160000000;
	mMaxRangeValue[3] = 320000000;
	mMaxRangeValue[4] = 80000000;
	mMaxRangeValue[5] = 160000000;
	mMaxRangeValue[6] = 320000000;
	mMaxRangeValue[7] = 640000000;
}
//INIT
BOOL PATSYSTEM::Init(void)
{
	return TRUE;
}
//FREE
void PATSYSTEM::Free(void)
{
}
//RETURN_GROW_STEP
float PATSYSTEM::ReturnGrowStep(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;
	float tDegree;

	if (pIndex < 1)
	{
		return 0.0f;
	}
	switch (pIndex)
	{
	case 541:
	case 547:
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		tMaxRangeValueIndex = 0;
		break;
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		tMaxRangeValueIndex = 1;
		break;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		tMaxRangeValueIndex = 2;
		break;
	case 1016:
	case 1310:
	case 1311:
	case 1312:
	case 1990: // Seasonal M33 Custom Pet
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
		tMaxRangeValueIndex = 3;
		break;
	default:
		return 0.0f;
	}
	if (pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex])
	{
		return 4.0f;
	}
	tDegree = ((float)pGrowUpValue * 100.0f) / (float)mMaxRangeValue[tMaxRangeValueIndex];
	if (tDegree < 25.0f)
	{
		return 0.0f;
	}
	else if (tDegree < 50.0f)
	{
		return 1.0f;
	}
	else if (tDegree < 75.0f)
	{
		return 2.0f;
	}
	else if (tDegree < 100.0f)
	{
		return 3.0f;
	}
	else
	{
		return 4.0f;
	}
	return 0.0f;
}
float PATSYSTEM::ReturnGrowPercent(int pIndex, int pGrowUpValue)
{
	int tMaxRangeValueIndex;

	if (pGrowUpValue < 1)
	{
		return 0.0f;
	}
	switch (pIndex)
	{
	case 547:
	case 541:
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		tMaxRangeValueIndex = 0;
		break;
	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		tMaxRangeValueIndex = 1;
		break;
	case 1012:
	case 1013:
	case 1014:
	case 1015:
		tMaxRangeValueIndex = 2;
		break;
	case 1016:
	case 1310:
	case 1311:
	case 1312:
	case 1990:// Seasonal M33 Custom Pet
	case 2133:
	case 2144:
	case 2160:
	case 1980: // Seasonal M33 Custom Pet
	case 1982: // Seasonal M33 Custom Pet
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
		tMaxRangeValueIndex = 3;
		break;
	default:
		return 0.0f;
	}
	if (pGrowUpValue >= mMaxRangeValue[tMaxRangeValueIndex])
	{
		return 100.0f;
	}
	return (((float)pGrowUpValue * 100.0f) / (float)mMaxRangeValue[tMaxRangeValueIndex]);
}
float PATSYSTEM::ReturnAttackPower(int pIndex, int pGrowUpValue, int pActivityValue)
{
	if (pIndex < 1)
		return 0.0;

	if (pGrowUpValue < 1 || pActivityValue < 1)
		return 0.0;

	switch (pIndex)
	{
	case 541:
	case 1002:
		if (pGrowUpValue < mMaxRangeValue[0])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[0];
		else
			return 1100.0f;

	case 1006:
	case 1007:
	case 1008:
		if (pGrowUpValue < mMaxRangeValue[1])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[1];
		else
			return 1100.0f;

	case 1012:
	case 1013:
	case 1014:
		if (pGrowUpValue < mMaxRangeValue[2])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[2];
		else
			return 1100.0f;

	case 1016:
	case 1310:
	case 1311:
	case 2133:
	case 2144:
	case 2160:
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[3];
		else
			return 1100.0f;

	case 1312:
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;


	case 1990:// Seasonal M33 Custom Pet
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;


	case 1980: // Moon Rabbit
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[3];
		else
			return 1750.0f;

	case 1982: // Rudolf Santa
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 1000.0f / mMaxRangeValue[3];
		else
			return 1100.0f;

	default:
		return 0.0f;
	}
}
float PATSYSTEM::ReturnDefensePower(int pIndex, int pGrowUpValue, int pActivityValue)
{
	if (pIndex < 1)
		return 0.0;

	if (pGrowUpValue < 1 || pActivityValue < 1)
		return 0.0;

	switch (pIndex)
	{
	case 547:
	case 1003:
		if (pGrowUpValue < mMaxRangeValue[0])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[0];
		else
			return 2200.0f;

	case 1006:
	case 1009:
	case 1010:
		if (pGrowUpValue < mMaxRangeValue[1])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[1];
		else
			return 2200.0f;

	case 1012:
	case 1013:
	case 1015:
		if (pGrowUpValue < mMaxRangeValue[2])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[2];
		else
			return 2200.0f;

	case 1016:
	case 1310:
	case 1312:
	case 1990:// Seasonal M33 Custom Pet
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	case 1311:
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 4000.0f / mMaxRangeValue[3];
		else
			return 4400.0f;

	case 1980: // Moon Rabbit
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	case 1982: // Rudolf Santa
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 3500.0f;

	default:
		return 0.0f;
	}
}
float PATSYSTEM::ReturnLifeValue(int pIndex, int pGrowUpValue)
{
	if (pIndex < 1)
		return 0.0;

	if (pGrowUpValue < 1)
		return 0.0;

	switch (pIndex)
	{
	case 547:
	case 541:
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		if (pGrowUpValue < mMaxRangeValue[0])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[0];
		else
			return 2200.0f;

	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		if (pGrowUpValue < mMaxRangeValue[1])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[1];
		else
			return 2200.0f;

	case 1012:
	case 1013:
	case 1014:
	case 1015:
		if (pGrowUpValue < mMaxRangeValue[2])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[2];
		else
			return 2200.0f;

	case 1016:
	case 1311:
	case 1312:
	case 1990:// Seasonal M33 Custom Pet
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	case 1310:
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 4000.0f / mMaxRangeValue[3];
		else
			return 4400.0f;

	case 1980: // Moon Rabbit
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	case 1982: // Rudolf Santa
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	default:
		return 0.0f;
	}
}
float PATSYSTEM::ReturnManaValue(int pIndex, int pGrowUpValue)
{
	if (pIndex < 1)
		return 0.0;

	if (pGrowUpValue < 1)
		return 0.0;

	switch (pIndex)
	{
	case 1005:
		if (pGrowUpValue < mMaxRangeValue[0])
			return pGrowUpValue * 1800.0f / mMaxRangeValue[0];
		else
			return 2000.0f;

	case 1008:
	case 1010:
	case 1011:
		if (pGrowUpValue < mMaxRangeValue[1])
			return pGrowUpValue * 1800.0f / mMaxRangeValue[1];
		else
			return 2000.0f;

	case 1013:
	case 1014:
	case 1015:
		if (pGrowUpValue < mMaxRangeValue[2])
			return pGrowUpValue * 1800.0f / mMaxRangeValue[2];
		else
			return 2000.0f;

	case 1016:
	case 1311:
	case 1312:
	case 1990:// Seasonal M33 Custom Pet
	case 1983: // Seasonal M33 Custom Pet
	case 1984: // Seasonal M33 Custom Pet
	case 1985: // Seasonal M33 Custom Pet
	case 1986: // Seasonal M33 Custom Pet
	case 1987: // Seasonal M33 Custom Pet
	case 1988: // Seasonal M33 Custom Pet
	case 1989: // Seasonal M33 Custom Pet
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 1800.0f / mMaxRangeValue[3];
		else
			return 2000.0f;

	case 1310:
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 3600.0f / mMaxRangeValue[3];
		else
			return 4000.0f;

	case 1980: // Moon Rabbit
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;


	case 1982: // Rudolf Santa
		if (pGrowUpValue < mMaxRangeValue[3])
			return pGrowUpValue * 2000.0f / mMaxRangeValue[3];
		else
			return 2200.0f;

	default:
		return 0.0f;
	}
}
int PATSYSTEM::ReturnAdditionalDamagePower(int pIndex, int pGrowUpValue, int pActivityValue)
{
	int tIsAdd = 0;
	int tRangeValue = 0;
	double tDegree;

	if (pIndex < 1)
		return 0;

	if (pActivityValue < 1)
		return 0;

	switch (pIndex)
	{
	case 1002:
	case 1003:
	case 1004:
	case 1005:
		tIsAdd = 1;
		tRangeValue = 0;
		break;

	case 1006:
	case 1007:
	case 1008:
	case 1009:
	case 1010:
	case 1011:
		tIsAdd = 1;
		tRangeValue = 1;
		break;

	case 1012:
	case 1013:
	case 1014:
	case 1015:
		tIsAdd = 1;
		tRangeValue = 2;
		break;

	case 1016:
	case 1310:
	case 1311:
	case 1312:
	case 1990:// Seasonal M33 Custom Pet
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
		tIsAdd = 1;
		tRangeValue = 3;
		break;

	default:
		return 0;
	}

	tDegree = (pGrowUpValue / (mMaxRangeValue[tRangeValue] / 100000)) / 1000.0;
	if (tDegree < 101.0)
		return 0;
	if (tDegree < 125.0)
		return 50;
	if (tDegree < 150.0)
		return 100;
	if (tDegree < 175.0)
		return 150;
	if (tDegree >= 200.0)
	{
		if (pIndex == 1980 || pIndex == 1981 || pIndex == 1982 || pIndex == 1016 || pIndex == 1310 || pIndex == 1311 || pIndex == 1312 || pIndex == 1990)
		{
			return 500;
		}
		return 250;
	}
	return 200;
}
float PATSYSTEM::ReturnAmuletHP(int tPetIndex)
{
	ITEM_INFO* v2;

	v2 = mITEM.Search(tPetIndex);
	if (!v2)
	{
		return 0.0f;
	}
	if (v2->iSort != 28)
	{
		return 0.0f;
	}
	switch (tPetIndex)
	{
	case 2151:
		return 4000.0f;
	case 2152:
		return 3500.0f;
	case 2153:
		return 3000.0f;
	case 2154:
		return 3500.0f;
	case 2174:
		return 3800.0f;
	case 2175:
		return 3600.0f;
	case 2176:
		return 3400.0f;
	case 2177:
		return 3200.0f;
	case 2178:
		return 3400.0f;
	case 2179:
		return 3300.0f;
	case 2180:
		return 3200.0f;
	case 2181:
		return 3100.0f;
	case 2182:
		return 3000.0f;
	case 2183:
		return 3000.0f;
	case 2184:
		return 3000.0f;
	case 2185:
		return 3000.0f;
	case 2186:
		return 3400.0f;
	case 2187:
		return 3300.0f;
	case 2188:
		return 3200.0f;
	case 2189:
		return 3100.0f;
	case 2195:
		return 7000.0f;
	case 2196:
		return 6800.0f;
	case 2197:
		return 6600.0f;
	case 2198:
		return 6000.0f;
	case 2199:
		return 6000.0f;
	case 2200:
		return 6000.0f;
	case 2201:
		return 6500.0f;
	case 2202:
		return 6400.0f;
	case 2203:
		return 6300.0f;
	case 2204:
		return 6500.0f;
	case 2205:
		return 6400.0f;
	case 2206:
		return 6300.0f;
	case 2253:
		return 2000.0f;
	case 2254:
		return 4000.0f;
	case 2261:
		return 2000.0f;
	case 2262:
		return 4000.0f;
	case 2300:
		return 2000.0f;
	case 2301:
		return 4000.0f;
	case 2302:
		return 3500.0f;
	case 2410:
		return 4000.0f;
	case 2411:
		return 3800.0f;
	case 2412:
		return 3600.0f;
	case 2413:
		return 3000.0f;
	case 2414:
		return 3000.0f;
	case 2415:
		return 3000.0f;
	case 2416:
		return 3500.0f;
	case 2417:
		return 3400.0f;
	case 2418:
		return 3300.0f;
	case 2419:
		return 3500.0f;
	case 2420:
		return 3400.0f;
	case 2421:
		return 3300.0f;
	default:
		return 0.0f;
	}
}
float PATSYSTEM::ReturnAmuletPetMP(int tPetIndex)
{
	ITEM_INFO* v2;

	v2 = mITEM.Search(tPetIndex);
	if (!v2)
	{
		return 0.0f;
	}
	if (v2->iSort != 28)
	{
		return 0.0f;
	}
	switch (tPetIndex)
	{
	case 2151:
		return 3500.0f;
	case 2152:
		return 4000.0f;
	case 2153:
		return 3500.0f;
	case 2154:
		return 3000.0f;
	case 2174:
		return 3400.0f;
	case 2175:
		return 3300.0f;
	case 2176:
		return 3200.0f;
	case 2177:
		return 3100.0f;
	case 2178:
		return 3800.0f;
	case 2179:
		return 3600.0f;
	case 2180:
		return 3400.0f;
	case 2181:
		return 3200.0f;
	case 2182:
		return 3400.0f;
	case 2183:
		return 3300.0f;
	case 2184:
		return 3200.0f;
	case 2185:
		return 3100.0f;
	case 2186:
		return 3000.0f;
	case 2187:
		return 3000.0f;
	case 2188:
		return 3000.0f;
	case 2189:
		return 3000.0f;
	case 2195:
		return 4500.0f;
	case 2196:
		return 4400.0f;
	case 2197:
		return 4300.0f;
	case 2198:
		return 4500.0f;
	case 2199:
		return 4400.0f;
	case 2200:
		return 4300.0f;
	case 2201:
		return 5000.0f;
	case 2202:
		return 4800.0f;
	case 2203:
		return 4600.0f;
	case 2204:
		return 4000.0f;
	case 2205:
		return 4000.0f;
	case 2206:
		return 4000.0f;
	case 2253:
		return 2000.0f;
	case 2254:
		return 4000.0f;
	case 2261:
		return 2000.0f;
	case 2262:
		return 4000.0f;
	case 2300:
		return 2000.0f;
	case 2301:
		return 4000.0f;
	case 2302:
		return 3500.0f;
	case 2410:
		return 3500.0f;
	case 2411:
		return 3400.0f;
	case 2412:
		return 3300.0f;
	case 2413:
		return 3500.0f;
	case 2414:
		return 3400.0f;
	case 2415:
		return 3300.0f;
	case 2416:
		return 4000.0f;
	case 2417:
		return 3800.0f;
	case 2418:
		return 3600.0f;
	case 2419:
		return 3000.0f;
	case 2420:
		return 3000.0f;
	case 2421:
		return 3000.0f;
	}
}
int PATSYSTEM::ReturnAmuletPetability1(int tAmuletIndex, int tAmuletExp, int tMode)
{
	int result;
	ITEM_INFO* v4;
	int v5;
	int v6;

	if (tAmuletIndex == -1 || !tAmuletIndex)
		return 0;
	if (!tAmuletExp)
		return 0;
	v4 = mITEM.Search(tAmuletIndex);
	if (!v4)
		return 0;
	if (v4->iSort != 28)
		return 0;
	if (v4->iIndex == 2253 || v4->iIndex == 2254)
		return 0;
	if (v4->iIndex == 2261 || v4->iIndex == 2262 || v4->iIndex == 2300 || v4->iIndex == 2301)
		return 0;
	v5 = mUTIL.ReturnISValue(tAmuletExp);
	if (v5 < 10)
		return 0;
	v6 = v5 % 10;
	if (v5 / 10 != tMode)
		return 0;
	switch (tMode)
	{
	case 1:
		switch (v6)
		{
		case 0:
			result = 30;
			break;
		case 1:
			result = 60;
			break;
		case 2:
			result = 90;
			break;
		case 3:
			result = 120;
			break;
		case 4:
			result = 150;
			break;
		case 5:
			result = 180;
			break;
		case 6:
			result = 210;
			break;
		case 7:
			result = 240;
			break;
		case 8:
			result = 270;
			break;
		case 9:
			result = 300;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 2:
		switch (v6)
		{
		case 0:
			result = 200;
			break;
		case 1:
			result = 400;
			break;
		case 2:
			result = 600;
			break;
		case 3:
			result = 800;
			break;
		case 4:
			result = 1000;
			break;
		case 5:
			result = 1200;
			break;
		case 6:
			result = 1400;
			break;
		case 7:
			result = 1600;
			break;
		case 8:
			result = 1800;
			break;
		case 9:
			result = 2000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 3:
		switch (v6)
		{
		case 0:
			result = 20;
			break;
		case 1:
			result = 40;
			break;
		case 2:
			result = 60;
			break;
		case 3:
			result = 80;
			break;
		case 4:
			result = 100;
			break;
		case 5:
			result = 120;
			break;
		case 6:
			result = 140;
			break;
		case 7:
			result = 160;
			break;
		case 8:
			result = 180;
			break;
		case 9:
			result = 200;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 4:
		switch (v6)
		{
		case 0:
			result = 250;
			break;
		case 1:
			result = 500;
			break;
		case 2:
			result = 750;
			break;
		case 3:
			result = 1000;
			break;
		case 4:
			result = 1250;
			break;
		case 5:
			result = 1500;
			break;
		case 6:
			result = 1750;
			break;
		case 7:
			result = 2000;
			break;
		case 8:
			result = 2250;
			break;
		case 9:
			result = 2500;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 5:
		switch (v6)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	case 6:
		switch (v6)
		{
		case 0:
			result = 100;
			break;
		case 1:
			result = 200;
			break;
		case 2:
			result = 300;
			break;
		case 3:
			result = 400;
			break;
		case 4:
			result = 500;
			break;
		case 5:
			result = 600;
			break;
		case 6:
			result = 700;
			break;
		case 7:
			result = 800;
			break;
		case 8:
			result = 900;
			break;
		case 9:
			result = 1000;
			break;
		default:
			result = 0;
			break;
		}
		break;
	default:
		result = 0;
		break;
	}
	return result;
}
float PATSYSTEM::ReturnAmuletPetability3(int tAmuletIndex, int tAmuletExp, int tMode)
{
	float result;
	ITEM_INFO* v4;
	int v5;
	int v6;

	if (tAmuletIndex == -1 || !tAmuletIndex)
		return 0.0f;
	if (!tAmuletExp)
		return 0.0f;
	v4 = mITEM.Search(tAmuletIndex);
	if (!v4)
		return 0.0f;
	if (v4->iSort != 28)
		return 0.0f;
	if (v4->iIndex == 2253 || v4->iIndex == 2254)
		return 0.0f;
	if (v4->iIndex == 2261 || v4->iIndex == 2262 || v4->iIndex == 2300 || v4->iIndex == 2301)
		return 0.0f;
	v5 = mUTIL.ReturnRFValue(tAmuletExp);
	if (v5 < 10)
		return 0.0f;
	v6 = v5 % 10;
	if (v5 / 10 != tMode)
		return 0.0f;
	switch (tMode)
	{
	case 1:
		switch (v6)
		{
		case 0:
			result = 30.0f;
			break;
		case 1:
			result = 60.0f;
			break;
		case 2:
			result = 90.0f;
			break;
		case 3:
			result = 120.0f;
			break;
		case 4:
			result = 150.0f;
			break;
		case 5:
			result = 180.0f;
			break;
		case 6:
			result = 210.0f;
			break;
		case 7:
			result = 240.0f;
			break;
		case 8:
			result = 270.0f;
			break;
		case 9:
			result = 300.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		break;
	case 2:
		switch (v6)
		{
		case 0:
			result = 200.0f;
			break;
		case 1:
			result = 400.0f;
			break;
		case 2:
			result = 600.0f;
			break;
		case 3:
			result = 800.0f;
			break;
		case 4:
			result = 1000.0f;
			break;
		case 5:
			result = 1200.0f;
			break;
		case 6:
			result = 1400.0f;
			break;
		case 7:
			result = 1600.0f;
			break;
		case 8:
			result = 1800.0f;
			break;
		case 9:
			result = 2000.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		break;
	case 3:
		switch (v6)
		{
		case 0:
			result = 100.0f;
			break;
		case 1:
			result = 200.0f;
			break;
		case 2:
			result = 300.0f;
			break;
		case 3:
			result = 400.0f;
			break;
		case 4:
			result = 500.0f;
			break;
		case 5:
			result = 600.0f;
			break;
		case 6:
			result = 700.0f;
			break;
		case 7:
			result = 800.0f;
			break;
		case 8:
			result = 900.0f;
			break;
		case 9:
			result = 1000.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		break;
	case 4:
		switch (v6)
		{
		case 0:
			result = 100.0f;
			break;
		case 1:
			result = 200.0f;
			break;
		case 2:
			result = 300.0f;
			break;
		case 3:
			result = 400.0f;
			break;
		case 4:
			result = 500.0f;
			break;
		case 5:
			result = 600.0f;
			break;
		case 6:
			result = 700.0f;
			break;
		case 7:
			result = 800.0f;
			break;
		case 8:
			result = 900.0f;
			break;
		case 9:
			result = 1000.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		break;
	case 5:
		switch (v6)
		{
		case 0:
			result = 0.30f;
			break;
		case 1:
			result = 0.30f;
			break;
		case 2:
			result = 0.90f;
			break;
		case 3:
			result = 1.2f;
			break;
		case 4:
			result = 1.5f;
			break;
		case 5:
			result = 1.8f;
			break;
		case 6:
			result = 2.10f;
			break;
		case 7:
			result = 2.40f;
			break;
		case 8:
			result = 2.7f;
			break;
		case 9:
			result = 3.0f;
			break;
		default:
			result = 0.0f;
			break;
		}
		break;
	default:
		result = 0.0f;
		break;
	}
	return result;
}
float PATSYSTEM::ReturnLegendPetHPStat(int tPetIndex)
{
	ITEM_INFO* t;

	t = mITEM.Search(tPetIndex);
	if (!t)
	{
		return 0.0f;
	}
	if (t->iSort != 31 && t->iSort != 32 && t->iSort != 33)
	{
		return 0.0f;
	}
	switch (tPetIndex)
	{
	case 1838:
	case 1840:
	case 1841:
	case 1842:
	case 1887:
	case 1889:
	case 17202:
	case 17203:
	case 17204:
		return 8000.0f;

	case 17335:
	case 17337:
	case 17338:
	case 17340:
	case 17341:
	case 17342:
	case 17343:
	case 17345:
	case 17346:
		return 10000.0f;

	case 19101:
	case 19102:
		return 11000.0f;

	case 19103:
		return 11000.0f;

	case 19104:
		return 11000.0f;

	case 19105:
		return 12000.0f;

	case 19106:
		return 12000.0f;

	case 19107:
		return 12000.0f;

	case 19108:
		return 12000.0f;

	case 19109:
		return 13000.0f;

	case 19110:
		return 13000.0f;

	case 19111:
		return 13000.0f;

	case 19112:
		return 13000.0f;

	case 19113:
		return 13000.0f;

	case 19127:
		return 11000.0f;

	case 19128:
		return 11000.0f;

	case 19129:
		return 11000.0f;

	case 19130:
		return 11000.0f;

	case 19131:
		return 12000.0f;

	case 19132:
		return 12000.0f;

	case 19133:
		return 12000.0f;

	case 19134:
		return 12000.0f;

	case 19135:
		return 13000.0f;

	case 19136:
		return 13000.0f;

	case 19137:
		return 13000.0f;

	case 19138:
		return 13000.0f;

	case 19139:
		return 13000.0f;

	case 19140:
		return 11000.0f;

	case 19141:
		return 11000.0f;

	case 19142:
		return 11000.0f;

	case 19143:
		return 11000.0f;

	case 19144:
		return 12000.0f;

	case 19145:
		return 12000.0f;

	case 19146:
		return 12000.0f;

	case 19147:
		return 12000.0f;

	case 19148:
		return 13000.0f;

	case 19149:
		return 13000.0f;

	case 19150:
		return 13000.0f;

	case 19151:
		return 13000.0f;

	case 19152:
		return 13000.0f;

	case 19166:
		return 11000.0f;

	case 19167:
		return 11000.0f;

	case 19168:
		return 11000.0f;

	case 19169:
		return 11000.0f;

	case 19170:
		return 12000.0f;

	case 19171:
		return 12000.0f;

	case 19172:
		return 12000.0f;

	case 19173:
		return 12000.0f;

	case 19174:
		return 13000.0f;

	case 19175:
		return 13000.0f;

	case 19176:
		return 13000.0f;

	case 19177:
		return 13000.0f;

	case 19178:
		return 13000.0f;

	case 19179:
		return 11000.0f;

	case 19180:
		return 11000.0f;

	case 19181:
		return 11000.0f;

	case 19182:
		return 11000.0f;

	case 19183:
		return 12000.0f;

	case 19184:
		return 12000.0f;

	case 19185:
		return 12000.0f;

	case 19186:
		return 12000.0f;

	case 19187:
		return 13000.0f;

	case 19188:
		return 13000.0f;

	case 19189:
		return 13000.0f;

	case 19190:
		return 13000.0f;

	case 19191:
		return 13000.0f;

	case 19192:
		return 11000.0f;

	case 19193:
		return 11000.0f;

	case 19194:
		return 11000.0f;

	case 19195:
		return 11000.0f;

	case 19196:
		return 12000.0f;

	case 19197:
		return 12000.0f;

	case 19198:
		return 12000.0f;

	case 19199:
		return 12000.0f;

	case 19200:
		return 13000.0f;

	case 19201:
		return 13000.0f;

	case 19202:
		return 13000.0f;

	case 19203:
		return 13000.0f;

	case 19204:
		return 13000.0f;

	case 19205:
		return 11000.0f;

	case 19206:
		return 11000.0f;

	case 19207:
		return 11000.0f;

	case 19208:
		return 11000.0f;

	case 19209:
		return 12000.0f;

	case 19210:
		return 12000.0f;

	case 19211:
		return 12000.0f;

	case 19212:
		return 12000.0f;

	case 19213:
		return 13000.0f;

	case 19214:
		return 13000.0f;

	case 19215:
		return 13000.0f;

	case 19216:
		return 13000.0f;

	case 19217:
		return 13000.0f;

	case 19231:
		return 11000.0f;

	case 19232:
		return 11000.0f;

	case 19233:
		return 11000.0f;

	case 19234:
		return 11000.0f;

	case 19235:
		return 12000.0f;

	case 19236:
		return 12000.0f;

	case 19237:
		return 12000.0f;

	case 19238:
		return 12000.0f;

	case 19239:
		return 13000.0f;

	case 19240:
		return 13000.0f;

	case 19241:
		return 13000.0f;

	case 19242:
		return 13000.0f;

	case 19243:
		return 13000.0f;

	case 19244:
		return 11000.0f;

	case 19245:
		return 11000.0f;

	case 19246:
		return 11000.0f;

	case 19247:
		return 11000.0f;

	case 19248:
		return 12000.0f;

	case 19249:
		return 12000.0f;

	case 19250:
		return 12000.0f;

	case 19251:
		return 12000.0f;

	case 19252:
		return 13000.0f;

	case 19253:
		return 13000.0f;

	case 19254:
		return 13000.0f;

	case 19255:
		return 13000.0f;

	case 19256:
		return 13000.0f;

	default:
		return 0.0f;
	}
}
float PATSYSTEM::ReturnLegendPetMPStat(int tPetIndex)
{
	ITEM_INFO* t;

	t = mITEM.Search(tPetIndex);
	if (!t)
	{
		return 0.0f;
	}
	if (t->iSort != 31 && t->iSort != 32 && t->iSort != 33)
	{
		return 0.0f;
	}
	switch (tPetIndex)
	{
	case 17204:
	case 1839:
	case 1840:
	case 1841:
	case 1842:
	case 1889:
	case 1890:
		return 8000.0;

	case 17336:
	case 17339:
	case 17340:
	case 17341:
	case 17342:
	case 17345:
	case 17346:
		return 10000.0f;

	case 19114:
	case 19115:
		return  11000.0f;

	case 19116:
		return  11000.0f;

	case 19117:
		return  11000.0f;

	case 19118:
		return  12000.0f;

	case 19119:
		return  12000.0f;

	case 19120:
		return  12000.0f;

	case 19121:
		return  12000.0f;

	case 19122:
		return  13000.0f;

	case 19123:
		return  13000.0f;

	case 19124:
		return  13000.0f;

	case 19125:
		return  13000.0f;

	case 19126:
		return  13000.0f;

	case 19153:
		return  11000.0f;

	case 19154:
		return  11000.0f;

	case 19155:
		return  11000.0f;

	case 19156:
		return  11000.0f;

	case 19157:
		return  12000.0f;

	case 19158:
		return  12000.0f;

	case 19159:
		return  12000.0f;

	case 19160:
		return  12000.0f;

	case 19161:
		return  13000.0f;

	case 19162:
		return  13000.0f;

	case 19163:
		return  13000.0f;

	case 19164:
		return  13000.0f;

	case 19165:
		return  13000.0f;

	case 19166:
		return  10000.0f;

	case 19167:
		return  11000.0f;

	case 19168:
		return  11000.0f;

	case 19169:
		return  11000.0f;

	case 19170:
		return  11000.0f;

	case 19171:
		return  12000.0f;

	case 19172:
		return  12000.0f;

	case 19173:
		return  12000.0f;

	case 19174:
		return  12000.0f;

	case 19175:
		return  13000.0f;

	case 19176:
		return  13000.0f;

	case 19177:
		return  13000.0f;

	case 19178:
		return  13000.0f;

	case 19179:
		return  10000.0f;

	case 19180:
		return  11000.0f;

	case 19181:
		return  11000.0f;

	case 19182:
		return  11000.0f;

	case 19183:
		return  11000.0f;

	case 19184:
		return  12000.0f;

	case 19185:
		return  12000.0f;

	case 19186:
		return  12000.0f;

	case 19187:
		return  12000.0f;

	case 19188:
		return  13000.0f;

	case 19189:
		return  13000.0f;

	case 19190:
		return  13000.0f;

	case 19191:
		return  13000.0f;

	case 19192:
		return  10000.0f;

	case 19193:
		return  11000.0f;

	case 19194:
		return  11000.0f;

	case 19195:
		return  11000.0f;

	case 19196:
		return  11000.0f;

	case 19197:
		return  12000.0f;

	case 19198:
		return  12000.0f;

	case 19199:
		return  12000.0f;

	case 19200:
		return  12000.0f;

	case 19201:
		return  13000.0f;

	case 19202:
		return  13000.0f;

	case 19203:
		return  13000.0f;

	case 19204:
		return  13000.0f;

	case 19231:
		return  10000.0f;

	case 19232:
		return  11000.0f;

	case 19233:
		return  11000.0f;

	case 19234:
		return  11000.0f;

	case 19235:
		return  11000.0f;

	case 19236:
		return  12000.0f;

	case 19237:
		return  12000.0f;

	case 19238:
		return  12000.0f;

	case 19239:
		return  12000.0f;

	case 19240:
		return  13000.0f;

	case 19241:
		return  13000.0f;

	case 19242:
		return  13000.0f;

	case 19243:
		return  13000.0f;

	case 19244:
		return  10000.0f;

	case 19245:
		return  11000.0f;

	case 19246:
		return  11000.0f;

	case 19247:
		return  11000.0f;

	case 19248:
		return  11000.0f;

	case 19249:
		return  12000.0f;

	case 19250:
		return  12000.0f;

	case 19251:
		return  12000.0f;

	case 19252:
		return  12000.0f;

	case 19253:
		return  13000.0f;

	case 19254:
		return  13000.0f;

	case 19255:
		return  13000.0f;

	case 19256:
		return  13000.0f;

	default:
		return 0.0f;
	}
}
int PATSYSTEM::ReturnPetAddSkillPoint(int tPetIndex, int tGrowUpValue, int tSkillMode)
{
	ITEM_INFO* tItem;
	int v5;

	if (tPetIndex == -1 || !tPetIndex)
	{
		return 0;
	}
	if (!tGrowUpValue)
	{
		return 0;
	}
	tItem = mITEM.Search(tPetIndex);
	if (!tItem)
	{
		return 0;
	}
	if (tItem->iSort != 28)
	{
		return 0;
	}
	if (tItem->iIndex == 2253 || tItem->iIndex == 2254)
	{
		return 0;
	}
	if (tItem->iIndex == 2261 || tItem->iIndex == 2262 || tItem->iIndex == 2300 || tItem->iIndex == 2301)
	{
		return 0;
	}
	v5 = mUTIL.ReturnIUValue(tGrowUpValue);
	if (v5 < 10)
	{
		return 0;
	}
	if (v5 / 10 == tSkillMode)
	{
		return v5 % 10;
	}
	return 0;
}

float PATSYSTEM::ReturnPetAddSkillPoint2(int tSort1, int tSort2, int tPetIndex, int tPetGrowState)
{
	int tItemSort = 0;
	int tISValue = 0;

	tItemSort = mUTIL.ReturnItemSort(tPetIndex);
	if (tItemSort != 5 && tItemSort != 6)
	{
		return 0.0f;
	}

	switch (tSort1)
	{
	case 1:
		tISValue = mUTIL.ReturnISValue(tPetGrowState);
		if (tSort2 != 1)
		{
			return 0.0f;
		}
		switch (tISValue)
		{
		case 1:
			return 1.0;
		case 2:
			return 2.0;
		case 3:
			return 3.0;
		}
		break;
	case 2:
		tISValue = mUTIL.ReturnIUValue(tPetGrowState);
		if (tSort2 != 2)
		{
			return 0.0;
		}
		switch (tISValue)
		{
		case 11:
			return 1.0f;
		case 12:
			return 2.0f;
		case 13:
			return 3.0f;
		}
		break;
	case 3:
		tISValue = mUTIL.ReturnRFValue(tPetGrowState);
		if (tSort2 != 3)
		{
			return 0.0f;
		}
		switch (tISValue)
		{
		case 21:
			return 1.0f;
		case 22:
			return 2.0f;
		case 23:
			return 3.0f;
		}
		break;
	case 4:
		tISValue = mUTIL.Return4thValue(tPetGrowState);
		if (tSort2 != 3)
		{
			return 0.0f;
		}
		switch (tISValue)
		{
		case 31:
			return 2.0f;
		case 32:
			return 4.0f;
		case 33:
			return 6.0f;
		}
		break;

	default:
		break;
	}
	return 0.0f;
}






// CLASS OF SOCKETSYSTEM
SOCKETSYSTEM mSOCKET;

BOOL SOCKETSYSTEM::Init(char* tFileName)
{
	int index01;
	DWORD nReadByte;
	DWORD tOriginalSize;
	BYTE* tOriginal;
	DWORD tCompressSize;
	BYTE* tCompress;
	int tDataNum;
	SOCKET_INFO* tDATA;
	int i = 0;

	HANDLE hFile;
	hFile = CreateFile(tFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		return FALSE;
	}
	if (!ReadFile(hFile, &tOriginalSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tOriginal = (BYTE*)GlobalAlloc(GMEM_FIXED, tOriginalSize);
	if (tOriginal == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, &tCompressSize, 4, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != 4)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	tCompress = (BYTE*)GlobalAlloc(GMEM_FIXED, tCompressSize);
	if (tCompress == NULL)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!ReadFile(hFile, tCompress, tCompressSize, &nReadByte, NULL))
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (nReadByte != tCompressSize)
	{
		CloseHandle(hFile);
		return FALSE;
	}
	if (!CloseHandle(hFile))
	{
		return FALSE;
	}
	if (!mGAME.Decompress(tCompressSize, tCompress, tOriginalSize, tOriginal))
	{
		return FALSE;
	}
	CopyMemory(&tDataNum, &tOriginal[0], 4);
	if (tDataNum != 3031)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	tDATA = (SOCKET_INFO*)calloc(1, (tDataNum * sizeof(SOCKET_INFO)));
	if (tDATA == NULL)
	{
		__LogMgr()->Log("! [%s] %d\n", __FUNCTION__, __LINE__);
		return FALSE;
	}
	CopyMemory(&tDATA[0], &tOriginal[4], (tDataNum * sizeof(SOCKET_INFO)));
	GlobalFree(tCompress);
	GlobalFree(tOriginal);
	mDATA = tDATA;

	return TRUE;
}

int SOCKETSYSTEM::GetSocketInfo(int tSort, int tSocket1, int tSocket2, int tSocket3)
{
	BYTE tS1[4];
	BYTE tS2[4];
	BYTE tS3[4];
	int i = 0;
	int tSocketValue[10] = { 0 };
	int tSocketNum = 0;
	int tAddValue = 0;

	CopyMemory(&tS1, &tSocket1, 4);
	CopyMemory(&tS2, &tSocket2, 4);
	CopyMemory(&tS3, &tSocket3, 4);

	tSocketNum = tS1[1];
	if (!tSocketNum)
	{
		return 0;
	}
	tSocketValue[0] = tS1[2];
	tSocketValue[1] = tS1[3];
	tSocketValue[2] = tS2[0];
	tSocketValue[3] = tS2[1];
	tSocketValue[4] = tS2[2];
	tSocketValue[5] = tS2[3];
	tSocketValue[6] = tS3[0];
	tSocketValue[7] = tS3[1];
	tSocketValue[8] = tS3[2];
	tSocketValue[9] = tS3[3];
	for (i = 0; i < tSocketNum; ++i)
	{
		if (tSocketValue[2 * i])
		{
			tAddValue += SetSocketNum(tSort, tSocketValue[2 * i], tSocketValue[2 * i + 1]);
		}
	}
	return tAddValue;
}
int SOCKETSYSTEM::SetSocketNum(int tSort, int tSocketType, int tSocketValue)
{
	SOCKET_INFO* tDATA;
	int v4 = 0;

	switch (tSort)
	{
	case 1:
		if (tSocketType == 1)
		{
			if (tSocketValue == 1 || tSocketValue == 6 || tSocketValue == 11)
			{
				v4 = 1;
				break;
			}
		}
		if (tSocketType == 2 || tSocketType == 3 || tSocketType == 4 || tSocketType == 5 || tSocketType == 6 || tSocketType == 7 || tSocketType == 8)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 2:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 2 || tSocketValue == 7 || tSocketValue == 12)
			{
				v4 = 1;
			}
			break;
		case 9:
		case 10:
		case 11:
		case 12:
		case 13:
		case 14:
			v4 = 1;
			break;
		case 2:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;

	case 3:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 3 || tSocketValue == 8 || tSocketValue == 13)
			{
				v4 = 1;
			}
			break;
		case 15:
		case 16:
		case 17:
		case 18:
		case 19:
			v4 = 1;
			break;
		case 3:
		case 9:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;
	case 4:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 3 || tSocketValue == 8 || tSocketValue == 13)
			{
				v4 = 2;
			}
			break;
		case 20:
		case 21:
		case 22:
		case 23:
			v4 = 1;
			break;
		case 4:
		case 10:
		case 15:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;
	case 5:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 5 || tSocketValue == 10 || tSocketValue == 15)
			{
				v4 = 1;
			}
			break;
		case 24:
		case 25:
		case 26:
			v4 = 1;
			break;
		case 5:
		case 11:
		case 16:
		case 20:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;
	case 6:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 5 || tSocketValue == 10 || tSocketValue == 15)
			{
				v4 = 2;
			}
			break;
		case 27:
		case 28:
			v4 = 1;
			break;
		case 6:
		case 12:
		case 17:
		case 21:
		case 24:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;
	case 7:
		switch (tSocketType)
		{
		case 1:
			if (tSocketValue == 4 || tSocketValue == 9 || tSocketValue == 14)
			{
				v4 = 1;
			}
			break;
		case 29:
			v4 = 1;
			break;
		case 7:
		case 13:
		case 18:
		case 22:
		case 25:
		case 27:
			v4 = 2;
			break;
		default:
			return 0;
		}
		break;
	case 8:
		if (tSocketType == 1)
		{
			if (tSocketValue == 4 || tSocketValue == 9 || tSocketValue == 14)
			{
				v4 = 2;
			}
			break;
		}
		if (tSocketType == 8 || tSocketType == 14 || tSocketType == 19 || tSocketType == 23 || tSocketType == 26 || tSocketType == 28 || tSocketType == 29)
		{
			v4 = 2;
			break;
		}
		return 0;
	case 11:
		if (tSocketType == 1)
		{
			if (tSocketValue == 16 || tSocketValue == 25)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 30)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 12:
		if (tSocketType == 1)
		{
			if (tSocketValue == 17 || tSocketValue == 26)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 31)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 13:
		if (tSocketType == 1)
		{
			if (tSocketValue == 18 || tSocketValue == 27)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 32)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 14:
		if (tSocketType == 1)
		{
			if (tSocketValue == 19 || tSocketValue == 28)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 33)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 15:
		if (tSocketType == 1)
		{
			if (tSocketValue == 20 || tSocketValue == 29)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 34)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 16:
		if (tSocketType == 1)
		{
			if (tSocketValue == 21 || tSocketValue == 30)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 35)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 17:
		if (tSocketType == 1)
		{
			if (tSocketValue == 22 || tSocketValue == 31)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 36)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 18:
		if (tSocketType == 1)
		{
			if (tSocketValue == 23 || tSocketValue == 32)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 37)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 19:
		if (tSocketType == 1)
		{
			if (tSocketValue == 24 || tSocketValue == 33)
			{
				v4 = 1;
			}
			break;
		}
		if (tSocketType == 38)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 20:
		if (tSocketType == 39)
		{
			v4 = 1;
			break;
		}
		if (tSocketType == 43)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 21:
		if (tSocketType == 40)
		{
			v4 = 1;
			break;
		}
		if (tSocketType == 44)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 22:
		if (tSocketType == 41)
		{
			v4 = 1;
			break;
		}
		if (tSocketType == 45)
		{
			v4 = 1;
			break;
		}
		return 0;
	case 23:
		if (tSocketType == 42)
		{
			v4 = 1;
			break;
		}
		if (tSocketType == 46)
		{
			v4 = 1;
			break;
		}
		return 0;

	default:
		return 0;
	}

	//
	tDATA = mSOCKET.Return(tSocketType, tSocketValue);
	if (tSocketType)
	{
		if (v4 == 1)
		{
			return tDATA->sAdd;
		}
		else if (v4 == 2)
		{
			return tDATA->sAdd2;
		}
	}
	return 0;
}
SOCKET_INFO* SOCKETSYSTEM::Return(int sGemMode, int sGemLevel)
{
	int i;

	if (sGemMode < 1 || sGemLevel < 1)
	{
		return 0;
	}
	for (i = 0; i < 3500; ++i)
	{
		if (mDATA[i].sGemMode == sGemMode && mDATA[i].sGemLevel == sGemLevel)
		{
			return &mDATA[i];
		}
	}
	return 0;
}
