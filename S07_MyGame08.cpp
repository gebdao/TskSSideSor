#include "MainApp.h"

PROXY_SHOP_OBJECT mPROXY_OBJECT[500];

void PROXY_SHOP_OBJECT::Free()
{
	mCheckValidState = FALSE;
	mUniqueNumber = -1;
	mProxyUserIndex = -1;
	strncpy(mProxyShopAvatarName, "", MAX_AVATAR_NAME_LENGTH);
	strncpy(mProxyShopName, "", MAX_AVATAR_NAME_LENGTH);
	strncpy(mID, "", MAX_AVATAR_NAME_LENGTH);
	mProxyShopLocation[0] = 0;
	mProxyShopLocation[1] = 0;
	mProxyShopLocation[2] = 0;
}
int PROXY_SHOP_OBJECT::GetProxyIndex(char* tAvatarName)
{
	int index01;

	for (index01 = 0; index01 < 500; index01++)
	{
		if (strcmp(mPROXY_OBJECT[index01].mProxyShopAvatarName, tAvatarName) == 0)
		{
			return index01;
		}
	}
	return -1;
}
int PROXY_SHOP_OBJECT::GetProxyIndex2(char* tID, char* tAvatarName)
{
	int index01;
	for (index01 = 0; index01 < 500; index01++)
	{
		if ((strcmp(mPROXY_OBJECT[index01].mID, tID) == 0) && (strcmp(mPROXY_OBJECT[index01].mProxyShopAvatarName, tAvatarName) == 0))
		{
			return index01;
		}
	}
	return -1;
}
BOOL PROXY_SHOP_OBJECT::CheckIfProxyActive(char* tID, char* tAvatarName)
{
	int index01;
	for (index01 = 0; index01 < 500; index01++)
	{
		if ((strcmp(mPROXY_OBJECT[index01].mID, tID) == 0) && (strcmp(mPROXY_OBJECT[index01].mProxyShopAvatarName, tAvatarName) == 0))
		{
			return TRUE;
		}
	}
	return FALSE;
}
int PROXY_SHOP_OBJECT::GetFreeProxyIndexForStart()
{
	int index01;
	for (index01 = 0; index01 < 500; index01++)
	{
		if (!mPROXY_OBJECT[index01].mCheckValidState)
		{
			return index01;
		}
	}
	if (index01 == MAX_AVATAR_OBJECT_NUM)
	{
		return -1;
	}
}