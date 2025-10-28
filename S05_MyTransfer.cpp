#include "MainApp.h"

//INSTANCE
MyTransfer mTRANSFER;
// CREATE
MyTransfer::MyTransfer(void)
{
}
// INIT
BOOL MyTransfer::Init(void)
{
	return TRUE;
}
// FREE
void MyTransfer::Free(void)
{
}
// B_CONNECT_OK
void MyTransfer::B_CONNECT_OK(int tRandomNumber)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 0;
	CopyMemory(&mOriginal[1], &tRandomNumber, 4);
	mOriginalSize = 5;
}
// B_TEMP_REGISTER_RECV
void MyTransfer::B_TEMP_REGISTER_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEMP_REGISTER_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TEMP_REGISTER_RECV;
}
// B_REGISTER_AVATAR_RECV
void MyTransfer::B_REGISTER_AVATAR_RECV(AVATAR_INFO* tAvatarInfo, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_REGISTER_AVATAR_RECV;
	CopyMemory(&mOriginal[1], tAvatarInfo, sizeof(AVATAR_INFO));
	CopyMemory(&mOriginal[(1 + sizeof(AVATAR_INFO))], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	mOriginalSize = S_REGISTER_AVATAR_RECV;
}
// B_BROADCAST_WORLD_INFO
void MyTransfer::B_BROADCAST_WORLD_INFO(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BROADCAST_WORLD_INFO;
	CopyMemory(&mOriginal[1], tWorldInfo, sizeof(WORLD_INFO));
	CopyMemory(&mOriginal[(1 + sizeof(WORLD_INFO))], tTribeInfo, sizeof(TRIBE_INFO));
	mOriginalSize = S_BROADCAST_WORLD_INFO;
}
void MyTransfer::B_BROADCAST_WORLD_INFO2(WORLD_INFO* tWorldInfo, TRIBE_INFO* tTribeInfo)
{
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_BROADCAST_WORLD_INFO;
	CopyMemory(&mOriginal_C[1], tWorldInfo, sizeof(WORLD_INFO));
	CopyMemory(&mOriginal_C[(1 + sizeof(WORLD_INFO))], tTribeInfo, sizeof(TRIBE_INFO));
	mOriginalSize_C = S_BROADCAST_WORLD_INFO;
}

// B_AUTO_CHECK_ASK_SEND
void MyTransfer::B_AUTO_CHECK_ASK_SEND(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AUTO_CHECK_ASK_SEND;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_AUTO_CHECK_ASK_SEND;
}
// B_AVATAR_ACTION_RECV
void MyTransfer::B_AVATAR_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mAVATAR_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal[0] = P_AVATAR_ACTION_RECV;
	CopyMemory(&mOriginal[1], &tServerIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], tAvatar, sizeof(OBJECT_FOR_AVATAR));
	CopyMemory(&mOriginal[(9 + sizeof(OBJECT_FOR_AVATAR))], &tCheckChangeActionState, 4);
	mOriginalSize = S_AVATAR_ACTION_RECV;
}
void MyTransfer::B_AVATAR_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_AVATAR* tAvatar, int tCheckChangeActionState)
{
	ZeroMemory(&mOriginal2, MAX_TRANSFER_BUFFER_SIZE);
	mAVATAR_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_AVATAR_ACTION_RECV;
	CopyMemory(&mOriginal2[1], &tServerIndex, 4);
	CopyMemory(&mOriginal2[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal2[9], tAvatar, sizeof(OBJECT_FOR_AVATAR));
	CopyMemory(&mOriginal2[(9 + sizeof(OBJECT_FOR_AVATAR))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_AVATAR_ACTION_RECV;
}

// B_AVATAR_EFFECT_VALUE_INFO
void MyTransfer::B_AVATAR_EFFECT_VALUE_INFO(int tServerIndex, DWORD tUniqueNumber, int tEffectValue[MAX_AVATAR_EFFECT_SORT_NUM][2], int tEffectValueState[MAX_AVATAR_EFFECT_SORT_NUM])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_EFFECT_VALUE_INFO;
	CopyMemory(&mOriginal[1], &tServerIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], tEffectValue, (MAX_AVATAR_EFFECT_SORT_NUM * 8));
	CopyMemory(&mOriginal[(9 + MAX_AVATAR_EFFECT_SORT_NUM * 8)], &tEffectValueState[0], (MAX_AVATAR_EFFECT_SORT_NUM * 4));
	mOriginalSize = S_AVATAR_EFFECT_VALUE_INFO;
}
// B_AVATAR_CHANGE_INFO_1
void MyTransfer::B_AVATAR_CHANGE_INFO_1(int tServerIndex, DWORD tUniqueNumber, int tSort, int tValue01, int tValue02, int tValue03)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_CHANGE_INFO_1;
	CopyMemory(&mOriginal[1], &tServerIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], &tSort, 4);
	CopyMemory(&mOriginal[13], &tValue01, 4);
	CopyMemory(&mOriginal[17], &tValue02, 4);
	CopyMemory(&mOriginal[21], &tValue03, 4);
	mOriginalSize = S_AVATAR_CHANGE_INFO_1;
}
// B_MONSTER_ACTION_RECV
void MyTransfer::B_MONSTER_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_MONSTER* tMonster, int tCheckChangeActionState)
{
	ZeroMemory(&mOriginal2, MAX_TRANSFER_BUFFER_SIZE);
	mMONSTER_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_MONSTER_ACTION_RECV;
	CopyMemory(&mOriginal2[1], &tServerIndex, 4);
	CopyMemory(&mOriginal2[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal2[9], tMonster, sizeof(OBJECT_FOR_MONSTER));
	CopyMemory(&mOriginal2[(9 + sizeof(OBJECT_FOR_MONSTER))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_MONSTER_ACTION_RECV;
}
// B_ITEM_ACTION_RECV
void MyTransfer::B_ITEM_ACTION_RECV(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mITEM_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal[0] = P_ITEM_ACTION_RECV;
	CopyMemory(&mOriginal[1], &tServerIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], tItem, sizeof(OBJECT_FOR_ITEM));
	CopyMemory(&mOriginal[(9 + sizeof(OBJECT_FOR_ITEM))], &tCheckChangeActionState, 4);
	mOriginalSize = S_ITEM_ACTION_RECV;
}
void MyTransfer::B_ITEM_ACTION_RECV2(int tServerIndex, DWORD tUniqueNumber, OBJECT_FOR_ITEM* tItem, int tCheckChangeActionState)
{
	ZeroMemory(&mOriginal2, MAX_TRANSFER_BUFFER_SIZE);
	mITEM_OBJECT[tServerIndex].mUpdateTimeForBroadcast = GetTickCount();
	mOriginal2[0] = P_ITEM_ACTION_RECV;
	CopyMemory(&mOriginal2[1], &tServerIndex, 4);
	CopyMemory(&mOriginal2[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal2[9], tItem, sizeof(OBJECT_FOR_ITEM));
	CopyMemory(&mOriginal2[(9 + sizeof(OBJECT_FOR_ITEM))], &tCheckChangeActionState, 4);
	mOriginalSize2 = S_ITEM_ACTION_RECV;
}

// B_GENERAL_NOTICE_RECV
void MyTransfer::B_GENERAL_NOTICE_RECV(char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 1)
	{
		mOriginal_C[0] = P_GENERAL_NOTICE_RECV;
		CopyMemory(&mOriginal_C[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GENERAL_NOTICE_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_GENERAL_NOTICE_RECV;
		CopyMemory(&mOriginal_R[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GENERAL_NOTICE_RECV;
	}
	else
	{
		mOriginal[0] = P_GENERAL_NOTICE_RECV;
		CopyMemory(&mOriginal[1], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GENERAL_NOTICE_RECV;
	}
}
// B_PROCESS_ATTACK_RECV
void MyTransfer::B_PROCESS_ATTACK_RECV(ATTACK_FOR_PROTOCOL* tAttackInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PROCESS_ATTACK_RECV;
	CopyMemory(&mOriginal[1], tAttackInfo, sizeof(ATTACK_FOR_PROTOCOL));
	mOriginalSize = S_PROCESS_ATTACK_RECV;
}
// B_AVATAR_CHANGE_INFO_2
void MyTransfer::B_AVATAR_CHANGE_INFO_2(int tSort, int tValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AVATAR_CHANGE_INFO_2;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tValue, 4);
	mOriginalSize = S_AVATAR_CHANGE_INFO_2;
}
// B_PROCESS_DATA_RECV
void MyTransfer::B_PROCESS_DATA_RECV(int tResult, int tSort, BYTE tData[MAX_BROADCAST_DATA_SIZE])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PROCESS_DATA_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tData[0], MAX_BROADCAST_DATA_SIZE);
	mOriginalSize = S_PROCESS_DATA_RECV;
}
// B_DEMAND_ZONE_SERVER_INFO_2_RESULT
void MyTransfer::B_DEMAND_ZONE_SERVER_INFO_2_RESULT(int tResult, char tIp[16], int tPort)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DEMAND_ZONE_SERVER_INFO_2_RESULT;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tIp[0], 16);
	CopyMemory(&mOriginal[21], &tPort, 4);
	mOriginalSize = S_DEMAND_ZONE_SERVER_INFO_2_RESULT;
}
// B_USE_HOTKEY_ITEM_RECV
void MyTransfer::B_USE_HOTKEY_ITEM_RECV(int tResult, int tPage, int tIndex)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_USE_HOTKEY_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tPage, 4);
	CopyMemory(&mOriginal[9], &tIndex, 4);
	mOriginalSize = S_USE_HOTKEY_ITEM_RECV;
}
// B_USE_INVENTORY_ITEM_RECV
void MyTransfer::B_USE_INVENTORY_ITEM_RECV(int tResult, int tPage, int tIndex, int tValue, int tValue2)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_USE_INVENTORY_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tPage, 4);
	CopyMemory(&mOriginal[9], &tIndex, 4);
	CopyMemory(&mOriginal[13], &tValue, 4);
	CopyMemory(&mOriginal[17], &tValue2, 4);
	mOriginalSize = S_USE_INVENTORY_ITEM_RECV;
}
// B_IMPROVE_ITEM_RECV
void MyTransfer::B_IMPROVE_ITEM_RECV(int tResult, int tCost, int iValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_IMPROVE_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &iValue, 4);
	mOriginalSize = S_IMPROVE_ITEM_RECV;
}
// B_REFINE_ITEM_RECV
void MyTransfer::B_REFINE_ITEM_RECV(int tResult, int tCPCost, int iValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_REFINE_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCPCost, 4);
	CopyMemory(&mOriginal[9], &iValue, 4);
	mOriginalSize = S_REFINE_ITEM_RECV;
}
// B_ADD_ITEM_RECV
void MyTransfer::B_ADD_ITEM_RECV(int tResult, int tCost)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ADD_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	mOriginalSize = S_ADD_ITEM_RECV;
}
// B_EXCHANGE_ITEM_RECV
void MyTransfer::B_EXCHANGE_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_EXCHANGE_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_EXCHANGE_ITEM_RECV;
}
// B_USE_INVENTORY_ITEM_RECV2
void MyTransfer::B_SEND_ITEM_NEW(int tResult, int tPage, int tIndex, int tValue1, int tValue2, int tValue3, int tValue4, int tValue5, int tValue6)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_SEND_ITEM_NEW;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tPage, 4);
	CopyMemory(&mOriginal[9], &tIndex, 4);
	CopyMemory(&mOriginal[13], &tValue1, 4);
	CopyMemory(&mOriginal[17], &tValue2, 4);

	CopyMemory(&mOriginal[21], &tValue3, 4);
	CopyMemory(&mOriginal[25], &tValue4, 4);
	CopyMemory(&mOriginal[29], &tValue5, 4);
	CopyMemory(&mOriginal[33], &tValue6, 4);
	mOriginalSize = S_SEND_ITEM_NEW;
}
// B_HIGH_ITEM_RECV
void MyTransfer::B_HIGH_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_HIGH_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_HIGH_ITEM_RECV;
}
// B_LOW_ITEM_RECV
void MyTransfer::B_LOW_ITEM_RECV(int tResult, int tCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_LOW_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_LOW_ITEM_RECV;
}
// B_MAKE_ITEM_RECV
void MyTransfer::B_MAKE_ITEM_RECV(int tResult, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_MAKE_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_MAKE_ITEM_RECV;
}
// B_MAKE_SKILL_RECV
void MyTransfer::B_MAKE_SKILL_RECV(int tResult, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_MAKE_SKILL_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_MAKE_SKILL_RECV;
}
// B_GEAR_BREAK_RECV
void MyTransfer::B_GEAR_BREAK_RECV(int tResult, int tMoney, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GEAR_BREAK_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tMoney, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_GEAR_BREAK_RECV;
}
// B_START_PSHOP_RECV
void MyTransfer::B_START_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_START_PSHOP_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], tPShopInfo, sizeof(PSHOP_INFO));
	mOriginalSize = S_START_PSHOP_RECV;
}
// B_END_PSHOP_RECV
void MyTransfer::B_END_PSHOP_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_END_PSHOP_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_END_PSHOP_RECV;
}
// B_DEMAND_PSHOP_RECV
void MyTransfer::B_DEMAND_PSHOP_RECV(int tResult, PSHOP_INFO* tPShopInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DEMAND_PSHOP_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], tPShopInfo, sizeof(PSHOP_INFO));
	mOriginalSize = S_DEMAND_PSHOP_RECV;
}
// B_PSHOP_ITEM_INFO_RECV
void MyTransfer::B_PSHOP_ITEM_INFO_RECV(DWORD tUniqueNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tPage, int tIndex, int tPShopItemInfo[9], int tSocket[MAX_SOCKETSYSTEM_ARRAY])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PSHOP_ITEM_INFO_RECV;
	CopyMemory(&mOriginal[1], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(5 + MAX_AVATAR_NAME_LENGTH)], &tPage, 4);
	CopyMemory(&mOriginal[(9 + MAX_AVATAR_NAME_LENGTH)], &tIndex, 4);
	CopyMemory(&mOriginal[(13 + MAX_AVATAR_NAME_LENGTH)], &tPShopItemInfo[0], 36);
	CopyMemory(&mOriginal[(13 + MAX_AVATAR_NAME_LENGTH + 36)], &tSocket[0], 20);
	memset(&mOriginal[(13 + MAX_AVATAR_NAME_LENGTH + 56)], 0, 4);
	mOriginalSize = S_PSHOP_ITEM_INFO_RECV;
}
// B_BUY_PSHOP_RECV
void MyTransfer::B_BUY_PSHOP_RECV(int tResult, int tCost, int tPage, int tIndex, int tValue[6], int tSocket[MAX_SOCKETSYSTEM_ARRAY])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BUY_PSHOP_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tValue[0], 24);
	CopyMemory(&mOriginal[41], &tSocket[0], 20);
	mOriginalSize = S_BUY_PSHOP_RECV;
}
// B_PROCESS_QUEST_RECV
void MyTransfer::B_PROCESS_QUEST_RECV(int tResult, int tSort, int tPage, int tIndex, int tXPost, int tYPost)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PROCESS_QUEST_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tXPost, 4);
	CopyMemory(&mOriginal[21], &tYPost, 4);
	mOriginalSize = S_PROCESS_QUEST_RECV;
}
// B_CHANGE_TO_TRIBE4_RECV
void MyTransfer::B_CHANGE_TO_TRIBE4_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CHANGE_TO_TRIBE4_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_CHANGE_TO_TRIBE4_RECV;
}
// B_GENERAL_CHAT_RECV
void MyTransfer::B_GENERAL_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GENERAL_CHAT_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_GENERAL_CHAT_RECV;
}
// B_SECRET_CHAT_RECV
void MyTransfer::B_SECRET_CHAT_RECV(int tResult, int tZoneNumber, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_SECRET_CHAT_RECV;
		CopyMemory(&mOriginal[1], &tResult, 4);
		CopyMemory(&mOriginal[5], &tZoneNumber, 4);
		CopyMemory(&mOriginal[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_SECRET_CHAT_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_SECRET_CHAT_RECV;
		CopyMemory(&mOriginal_C[1], &tResult, 4);
		CopyMemory(&mOriginal_C[5], &tZoneNumber, 4);
		CopyMemory(&mOriginal_C[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_SECRET_CHAT_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_SECRET_CHAT_RECV;
		CopyMemory(&mOriginal_R[1], &tResult, 4);
		CopyMemory(&mOriginal_R[5], &tZoneNumber, 4);
		CopyMemory(&mOriginal_R[9], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(9 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_SECRET_CHAT_RECV;
	}
}
// B_GENERAL_SHOUT_RECV
void MyTransfer::B_GENERAL_SHOUT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GENERAL_SHOUT_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_GENERAL_SHOUT_RECV;
}
// B_GET_CASH_SIZE_RECV
void MyTransfer::B_GET_CASH_SIZE_RECV(int tCashSize, int tBonusCashSize)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GET_CASH_SIZE_RECV;
	CopyMemory(&mOriginal[1], &tCashSize, 4);
	CopyMemory(&mOriginal[5], &tBonusCashSize, 4);
	mOriginalSize = S_GET_CASH_SIZE_RECV;
}
// B_BUY_CASH_ITEM_RECV
void MyTransfer::B_BUY_CASH_ITEM_RECV(int tResult, int tCashSize, int tPage, int tIndex, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BUY_CASH_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCashSize, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = S_BUY_CASH_ITEM_RECV;
}
// B_DUEL_ASK_RECV
void MyTransfer::B_DUEL_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tSort)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tSort, 4);
	mOriginalSize = S_DUEL_ASK_RECV;
}
// B_DUEL_CANCEL_RECV
void MyTransfer::B_DUEL_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_CANCEL_RECV;
	mOriginalSize = S_DUEL_CANCEL_RECV;
}
// B_DUEL_ANSWER_RECV
void MyTransfer::B_DUEL_ANSWER_RECV(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_DUEL_ANSWER_RECV;
}
// B_DUEL_START_RECV
void MyTransfer::B_DUEL_START_RECV(int tDuelState[3], int tRemainTime, int tIsPotionUsable)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_START_RECV;
	CopyMemory(&mOriginal[1], &tDuelState[0], 12);
	CopyMemory(&mOriginal[13], &tRemainTime, 4);
	CopyMemory(&mOriginal[17], &tIsPotionUsable, 4);
	mOriginalSize = S_DUEL_START_RECV;
}
// B_DUEL_TIME_INFO
void MyTransfer::B_DUEL_TIME_INFO(int tRemainTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_TIME_INFO;
	CopyMemory(&mOriginal[1], &tRemainTime, 4);
	mOriginalSize = S_DUEL_TIME_INFO;
}
// B_DUEL_END_RECV
void MyTransfer::B_DUEL_END_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DUEL_END_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_DUEL_END_RECV;
}
// B_TRADE_ASK_RECV
void MyTransfer::B_TRADE_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tLevel)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tLevel, 4);
	mOriginalSize = S_TRADE_ASK_RECV;
}
// B_TRADE_CANCEL_RECV
void MyTransfer::B_TRADE_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_CANCEL_RECV;
	mOriginalSize = S_TRADE_CANCEL_RECV;
}
// B_TRADE_ANSWER_RECV
void MyTransfer::B_TRADE_ANSWER_RECV(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_TRADE_ANSWER_RECV;
}
// B_TRADE_START_RECV
void MyTransfer::B_TRADE_START_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tTradeMoney2, int tTradeSocket[8][MAX_SOCKETSYSTEM_ARRAY])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_START_RECV;
	CopyMemory(&mOriginal[1], &tTradeMoney, 4);
	CopyMemory(&mOriginal[5], tTrade, (MAX_TRADE_SLOT_NUM * 16));
	CopyMemory(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16)], tTradeSocket, ((8 * 4) * MAX_SOCKETSYSTEM_ARRAY));
	CopyMemory(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16) + ((8 * 4) * MAX_SOCKETSYSTEM_ARRAY)], &tTradeMoney2, 4);
	mOriginalSize = S_TRADE_START_RECV;
}
// B_TRADE_STATE_RECV
void MyTransfer::B_TRADE_STATE_RECV(int tTradeMoney, int tTrade[MAX_TRADE_SLOT_NUM][4], int tTradeMoney2, int tTradeSocket[8][MAX_SOCKETSYSTEM_ARRAY])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_STATE_RECV;
	CopyMemory(&mOriginal[1], &tTradeMoney, 4);
	CopyMemory(&mOriginal[5], tTrade, (MAX_TRADE_SLOT_NUM * 16));
	CopyMemory(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16)], tTradeSocket, ((8 * 4) * MAX_SOCKETSYSTEM_ARRAY));
	CopyMemory(&mOriginal[5 + (MAX_TRADE_SLOT_NUM * 16) + ((8 * 4) * MAX_SOCKETSYSTEM_ARRAY)], &tTradeMoney2, 4);
	mOriginalSize = S_TRADE_STATE_RECV;
}
// B_TRADE_MENU_RECV
void MyTransfer::B_TRADE_MENU_RECV(int tCheckMe)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_MENU_RECV;
	CopyMemory(&mOriginal[1], &tCheckMe, 4);
	mOriginalSize = S_TRADE_MENU_RECV;
}
// B_TRADE_END_RECV
void MyTransfer::B_TRADE_END_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRADE_END_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TRADE_END_RECV;
}
// B_FRIEND_ASK_RECV
void MyTransfer::B_FRIEND_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_FRIEND_ASK_RECV;
}
// B_FRIEND_CANCEL_RECV
void MyTransfer::B_FRIEND_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_CANCEL_RECV;
	mOriginalSize = S_FRIEND_CANCEL_RECV;
}
// B_FRIEND_ANSWER_RECV
void MyTransfer::B_FRIEND_ANSWER_RECV(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_FRIEND_ANSWER_RECV;
}
// B_FRIEND_MAKE_RECV
void MyTransfer::B_FRIEND_MAKE_RECV(int tIndex, char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_MAKE_RECV;
	CopyMemory(&mOriginal[1], &tIndex, 4);
	CopyMemory(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_FRIEND_MAKE_RECV;
}
// B_FRIEND_FIND_RECV
void MyTransfer::B_FRIEND_FIND_RECV(int tIndex, int tZoneNumber)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_FIND_RECV;
	CopyMemory(&mOriginal[1], &tIndex, 4);
	CopyMemory(&mOriginal[5], &tZoneNumber, 4);
	mOriginalSize = S_FRIEND_FIND_RECV;
}
// B_FRIEND_DELETE_RECV
void MyTransfer::B_FRIEND_DELETE_RECV(int tIndex)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_FRIEND_DELETE_RECV;
	CopyMemory(&mOriginal[1], &tIndex, 4);
	mOriginalSize = S_FRIEND_DELETE_RECV;
}
// B_TEACHER_ASK_RECV
void MyTransfer::B_TEACHER_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_TEACHER_ASK_RECV;
}
// B_TEACHER_CANCEL_RECV
void MyTransfer::B_TEACHER_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_CANCEL_RECV;
	mOriginalSize = S_TEACHER_CANCEL_RECV;
}
// B_TEACHER_ANSWER_RECV
void MyTransfer::B_TEACHER_ANSWER_RECV(int tAnswer)
{
	mOriginal[0] = P_TEACHER_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_TEACHER_ANSWER_RECV;
}
// B_TEACHER_START_RECV
void MyTransfer::B_TEACHER_START_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_START_RECV;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_TEACHER_START_RECV;
}
// B_TEACHER_END_RECV
void MyTransfer::B_TEACHER_END_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_END_RECV;
	mOriginalSize = S_TEACHER_END_RECV;
}
// B_TEACHER_STATE_RECV
void MyTransfer::B_TEACHER_STATE_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TEACHER_STATE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_TEACHER_STATE_RECV;
}
// B_PARTY_ASK_RECV
void MyTransfer::B_PARTY_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_PARTY_ASK_RECV;
}
// B_PARTY_CANCEL_RECV
void MyTransfer::B_PARTY_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_CANCEL_RECV;
	mOriginalSize = S_PARTY_CANCEL_RECV;
}
// B_PARTY_ANSWER_RECV
void MyTransfer::B_PARTY_ANSWER_RECV(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_PARTY_ANSWER_RECV;
}
// B_PARTY_MAKE_RECV
void MyTransfer::B_PARTY_MAKE_RECV()
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PARTY_MAKE_RECV;
	mOriginalSize = S_PARTY_MAKE_RECV;
}
// B_PARTY_JOIN_RECV
void MyTransfer::B_PARTY_JOIN_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_JOIN_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_JOIN_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_JOIN_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_JOIN_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_JOIN_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_JOIN_RECV;
	}
}
// B_PARTY_INFO_RECV
void MyTransfer::B_PARTY_INFO_RECV(char tAvatarName1[MAX_AVATAR_NAME_LENGTH], char tAvatarName2[MAX_AVATAR_NAME_LENGTH], char tAvatarName3[MAX_AVATAR_NAME_LENGTH], char tAvatarName4[MAX_AVATAR_NAME_LENGTH], char tAvatarName5[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_INFO_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName1[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[1 + MAX_AVATAR_NAME_LENGTH], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName3[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName4[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName5[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_INFO_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_INFO_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName1[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[1 + MAX_AVATAR_NAME_LENGTH], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName3[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName4[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName5[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_INFO_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_INFO_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName1[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[1 + MAX_AVATAR_NAME_LENGTH], &tAvatarName2[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName3[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName4[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[1 + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH + MAX_AVATAR_NAME_LENGTH], &tAvatarName5[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_INFO_RECV;
	}
}
// B_PARTY_CHAT_RECV
void MyTransfer::B_PARTY_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_CHAT_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_PARTY_CHAT_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_CHAT_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_PARTY_CHAT_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_CHAT_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_PARTY_CHAT_RECV;
	}
}
// B_PARTY_LEAVE_RECV
void MyTransfer::B_PARTY_LEAVE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_LEAVE_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_LEAVE_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_LEAVE_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_LEAVE_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_LEAVE_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_LEAVE_RECV;
	}
}
// B_PARTY_EXILE_RECV
void MyTransfer::B_PARTY_EXILE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_EXILE_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_EXILE_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_EXILE_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_EXILE_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_EXILE_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_EXILE_RECV;
	}
}
// B_PARTY_BREAK_RECV
void MyTransfer::B_PARTY_BREAK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_PARTY_BREAK_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_PARTY_BREAK_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_PARTY_BREAK_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_PARTY_BREAK_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_PARTY_BREAK_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_PARTY_BREAK_RECV;
	}
}
// B_GUILD_ASK_RECV
void MyTransfer::B_GUILD_ASK_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_ASK_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	mOriginalSize = S_GUILD_ASK_RECV;
}
// B_GUILD_CANCEL_RECV
void MyTransfer::B_GUILD_CANCEL_RECV(void)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_CANCEL_RECV;
	mOriginalSize = S_GUILD_CANCEL_RECV;
}
// B_GUILD_ANSWER_RECV
void MyTransfer::B_GUILD_ANSWER_RECV(int tAnswer)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_ANSWER_RECV;
	CopyMemory(&mOriginal[1], &tAnswer, 4);
	mOriginalSize = S_GUILD_ANSWER_RECV;
}
// B_GUILD_WORK_RECV
void MyTransfer::B_GUILD_WORK_RECV(int tResult, int tSort, GUILD_INFO* tGuildInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_WORK_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], tGuildInfo, sizeof(GUILD_INFO));
	mOriginalSize = S_GUILD_WORK_RECV;
}
// B_GUILD_NOTICE_RECV
void MyTransfer::B_GUILD_NOTICE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_GUILD_NOTICE_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GUILD_NOTICE_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_GUILD_NOTICE_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GUILD_NOTICE_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_GUILD_NOTICE_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GUILD_NOTICE_RECV;
	}
}
// B_GUILD_CHAT_RECV
void MyTransfer::B_GUILD_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_GUILD_CHAT_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_GUILD_CHAT_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_GUILD_CHAT_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_GUILD_CHAT_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_GUILD_CHAT_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_GUILD_CHAT_RECV;
	}
}
// B_GUILD_FIND_RECV
void MyTransfer::B_GUILD_FIND_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GUILD_FIND_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	mOriginalSize = S_GUILD_FIND_RECV;
}
// B_GUILD_LOGIN_INFO
void MyTransfer::B_GUILD_LOGIN_INFO(char tAvatarName[MAX_AVATAR_NAME_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_GUILD_LOGIN_INFO;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize = S_GUILD_LOGIN_INFO;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_GUILD_LOGIN_INFO;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_C = S_GUILD_LOGIN_INFO;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_GUILD_LOGIN_INFO;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		mOriginalSize_R = S_GUILD_LOGIN_INFO;
	}
}
// B_TRIBE_WORK_RECV
void MyTransfer::B_TRIBE_WORK_RECV(int tResult, int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_WORK_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize = S_TRIBE_WORK_RECV;
}
// B_TRIBE_NOTICE_RECV
void MyTransfer::B_TRIBE_NOTICE_RECV(int tType, char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_TRIBE_NOTICE_RECV;
		CopyMemory(&mOriginal[1], &tType, 4);
		CopyMemory(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(5 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_TRIBE_NOTICE_RECV;
	}
	else if (type == 1)
	{
		mOriginal_C[0] = P_TRIBE_NOTICE_RECV;
		CopyMemory(&mOriginal_C[1], &tType, 4);
		CopyMemory(&mOriginal_C[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(5 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_TRIBE_NOTICE_RECV;
	}
	else if (type == 2)
	{
		mOriginal_R[0] = P_TRIBE_NOTICE_RECV;
		CopyMemory(&mOriginal_R[1], &tType, 4);
		CopyMemory(&mOriginal_R[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(5 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_TRIBE_NOTICE_RECV;
	}
}
// B_TRIBE_CHAT_RECV
void MyTransfer::B_TRIBE_CHAT_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_CHAT_RECV;
	CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize = S_TRIBE_CHAT_RECV;
}
void MyTransfer::B_TRIBE_CHAT_RECV2(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH])
{
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	BYTE tAuthType = 1;
	mOriginal_C[0] = P_TRIBE_CHAT_RECV;
	CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal_C[1 + MAX_AVATAR_NAME_LENGTH], &tAuthType, 1);
	CopyMemory(&mOriginal_C[(2 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
	mOriginalSize_C = S_TRIBE_CHAT_RECV;
}
// B_FACTION_NOTICE_RECV
void MyTransfer::B_FACTION_NOTICE_RECV(char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tContent[MAX_CHAT_CONTENT_LENGTH], int type)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	ZeroMemory(&mOriginal_R, MAX_TRANSFER_BUFFER_SIZE);
	if (type == 0)
	{
		mOriginal[0] = P_FACTION_NOTICE_RECV;
		CopyMemory(&mOriginal[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize = S_FACTION_NOTICE_RECV;
	}
	if (type == 1)
	{
		mOriginal_C[0] = P_FACTION_NOTICE_RECV;
		CopyMemory(&mOriginal_C[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_C[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_C = S_FACTION_NOTICE_RECV;
	}
	if (type == 2)
	{
		mOriginal_R[0] = P_FACTION_NOTICE_RECV;
		CopyMemory(&mOriginal_R[1], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
		CopyMemory(&mOriginal_R[(1 + MAX_AVATAR_NAME_LENGTH)], &tContent[0], MAX_CHAT_CONTENT_LENGTH);
		mOriginalSize_R = S_FACTION_NOTICE_RECV;
	}
}
// B_TRIBE_BANK_RECV
void MyTransfer::B_TRIBE_BANK_RECV(int tResult, int tSort, int tTribeBankInfo[MAX_TRIBE_BANK_SLOT_NUM], int tMoney)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_BANK_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tTribeBankInfo[0], (MAX_TRIBE_BANK_SLOT_NUM * 4));
	CopyMemory(&mOriginal[(9 + MAX_TRIBE_BANK_SLOT_NUM * 4)], &tMoney, 4);
	mOriginalSize = S_TRIBE_BANK_RECV;
}
// B_TRIBE_VOTE_RECV
void MyTransfer::B_TRIBE_VOTE_RECV(int tResult, int tSort, int tValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_VOTE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tValue, 4);
	mOriginalSize = S_TRIBE_VOTE_RECV;
}
// B_TRIBE_ALLIANCE_INFO
void MyTransfer::B_TRIBE_ALLIANCE_INFO(int tSort, int tValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TRIBE_ALLIANCE_INFO;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tValue, 4);
	mOriginalSize = S_TRIBE_ALLIANCE_INFO;
}
// B_BROADCAST_INFO_RECV
void MyTransfer::B_BROADCAST_INFO_RECV(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BROADCAST_INFO_RECV;
	CopyMemory(&mOriginal[1], &tInfoSort, 4);
	CopyMemory(&mOriginal[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mOriginalSize = S_BROADCAST_INFO_RECV;
}
void MyTransfer::B_BROADCAST_INFO_RECV2(int tInfoSort, BYTE tInfoData[MAX_BROADCAST_INFO_SIZE])
{
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_BROADCAST_INFO_RECV;
	CopyMemory(&mOriginal_C[1], &tInfoSort, 4);
	CopyMemory(&mOriginal_C[5], &tInfoData[0], MAX_BROADCAST_INFO_SIZE);
	mOriginalSize_C = S_BROADCAST_INFO_RECV;
}

// B_049_TYPE_BATTLE_INFO
void MyTransfer::B_049_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_049_TYPE_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tTribeUserNum[0], 16);
	CopyMemory(&mOriginal[17], &tRemainTime, 4);
	mOriginalSize = S_049_TYPE_BATTLE_INFO;
}
// B_051_TYPE_BATTLE_INFO
void MyTransfer::B_051_TYPE_BATTLE_INFO(int tExistStone[4])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_051_TYPE_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tExistStone[0], 16);
	mOriginalSize = S_051_TYPE_BATTLE_INFO;
}
// B_053_TYPE_BATTLE_INFO
void MyTransfer::B_053_TYPE_BATTLE_INFO(int tRemainTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_053_TYPE_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tRemainTime, 4);
	mOriginalSize = S_053_TYPE_BATTLE_INFO;
}
// B_VOD_BATTLE_INFO
void MyTransfer::B_VOD_BATTLE_INFO(int tTribeUserKillNum[4])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_VOD_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tTribeUserKillNum[0], 16);
	mOriginalSize = S_VOD_BATTLE_INFO;
}
// B_GM_COMMAND_INFO
void MyTransfer::B_GM_COMMAND_INFO(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GM_COMMAND_INFO;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize = S_GM_COMMAND_INFO;
}
void MyTransfer::B_GM_COMMAND_INFO2(int tSort, BYTE tData[MAX_TRIBE_WORK_SIZE])
{
	ZeroMemory(&mOriginal_C, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal_C[0] = P_GM_COMMAND_INFO;
	CopyMemory(&mOriginal_C[1], &tSort, 4);
	CopyMemory(&mOriginal_C[5], &tData[0], MAX_TRIBE_WORK_SIZE);
	mOriginalSize_C = S_GM_COMMAND_INFO;
}
// B_194_BATTLE_INFO
void MyTransfer::B_194_BATTLE_INFO(int tTribeUserNum[4])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_194_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tTribeUserNum[0], 16);
	mOriginalSize = S_194_BATTLE_INFO;
}

// B_194_BATTLE_COUNTDOWN
void MyTransfer::B_194_BATTLE_COUNTDOWN(int tTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_194_BATTLE_COUNTDOWN;
	CopyMemory(&mOriginal[1], &tTime, 4);
	mOriginalSize = S_194_BATTLE_COUNTDOWN;
}

// B_267_TYPE_BATTLE_INFO
void MyTransfer::B_267_TYPE_BATTLE_INFO(int tTribeUserNum[4], int tRemainTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_267_TYPE_BATTLE_INFO;
	CopyMemory(&mOriginal[1], &tTribeUserNum[0], 16);
	CopyMemory(&mOriginal[17], &tRemainTime, 4);
	mOriginalSize = S_267_TYPE_BATTLE_INFO;
}

void MyTransfer::B_ANIMAL_STATE_RECV(int tValue01, int tValue02)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ANIMAL_STATE_RECV;
	CopyMemory(&mOriginal[1], &tValue01, 4);
	CopyMemory(&mOriginal[5], &tValue02, 4);
	mOriginalSize = S_ANIMAL_STATE_RECV;
}

void MyTransfer::B_SOCKET_ITEM_RECV(int tResult, int tSort, int tSocket[MAX_SOCKETSYSTEM_ARRAY])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_SOCKET_ITEM_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tSocket[0], (MAX_SOCKETSYSTEM_ARRAY * 4));
	mOriginalSize = S_SOCKET_ITEM_RECV;
}

void MyTransfer::B_COSTUME_STATE_RECV(int tResult, int tValue01, int tValue02, int iPage, int iInvenSlot, int iInvenIndex, int pItemIndex)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_COSTUME_STATE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tValue01, 4);
	CopyMemory(&mOriginal[9], &tValue02, 4);
	CopyMemory(&mOriginal[13], &iPage, 4);
	CopyMemory(&mOriginal[17], &iInvenSlot, 4);
	CopyMemory(&mOriginal[21], &iInvenIndex, 4);
	CopyMemory(&mOriginal[25], &pItemIndex, 4);
	mOriginalSize = S_COSTUME_STATE_RECV;
}

void MyTransfer::B_AUTOHUNT_RECV(int tServerIndex, DWORD tUniqueNumber, int tAutoState)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_AUTOHUNT_RECV;
	CopyMemory(&mOriginal[1], &tServerIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], &tAutoState, 4);
	mOriginalSize = S_AUTOHUNT_RECV;
}

void MyTransfer::W_DAILY_MISSION_RECV(int tResult, int tSort, int tWars, int tPVPKills, int tPVMKills, int tOnlineTime, int tItem, int tPage, int tIndex, int tXPost, int tYPost)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DAILY_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tSort, 4);
	CopyMemory(&mOriginal[9], &tWars, 4);
	CopyMemory(&mOriginal[13], &tPVPKills, 4);
	CopyMemory(&mOriginal[17], &tPVMKills, 4);
	CopyMemory(&mOriginal[21], &tOnlineTime, 4);
	CopyMemory(&mOriginal[25], &tItem, 4);
	CopyMemory(&mOriginal[29], &tPage, 4);
	CopyMemory(&mOriginal[33], &tIndex, 4);
	CopyMemory(&mOriginal[37], &tXPost, 4);
	CopyMemory(&mOriginal[41], &tYPost, 4);
	mOriginalSize = S_DAILY_RECV;
}

void MyTransfer::B_BEGINNER_REWARD_RECV(int tResult, int iPage, int iInvenSlot, int iInvenSlot2, int iInvenIndex, int iInvenIndex2, int tValue[8], int tImproveValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BEGINNER_REWARD_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4); // tResult % 1000 = No. of Loops
	CopyMemory(&mOriginal[5], &iPage, 4);
	CopyMemory(&mOriginal[9], &iInvenSlot, 4);	  // Use if No. of Loops < 4
	CopyMemory(&mOriginal[13], &iInvenSlot2, 4);  // Use if No. of Loops >= 4 but < 8
	CopyMemory(&mOriginal[17], &iInvenIndex, 4);  // Use if No. of Loops < 4
	CopyMemory(&mOriginal[21], &iInvenIndex2, 4); // Use if No. of Loops >= 4 but < 8
	CopyMemory(&mOriginal[25], &tValue[0], 32);
	CopyMemory(&mOriginal[57], &tImproveValue, 4);
	mOriginalSize = S_BEGINNER_REWARD_RECV;
}

void MyTransfer::B_WARLORD_V2_RECV(int tResult, int tCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_WARLORD_V2_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = S_WARLORD_V2_RECV;
}

void MyTransfer::B_REMAIN_TIME_RECV(int tRemainTime)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_REMAIN_TIME_RECV;
	CopyMemory(&mOriginal[1], &tRemainTime, 4);
	mOriginalSize = S_REMAIN_TIME_RECV;
}

void MyTransfer::B_BOOZE_DRINK_RECV(int tResult, int tDrinkIndex)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BOOZE_DRINK_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tDrinkIndex, 4);
	mOriginalSize = S_BOOZE_DRINK_RECV;
}

void MyTransfer::PC_CAFE_PETTOBAG_RECV(int tResult, int tItemIndex, int iPage, int iInvenSlot, int iInvenIndex, int tItemModifier)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_PC_CAFE_PETTOBAG_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tItemIndex, 4);
	CopyMemory(&mOriginal[9], &iPage, 4);
	CopyMemory(&mOriginal[13], &iInvenSlot, 4);
	CopyMemory(&mOriginal[17], &iInvenIndex, 4);
	CopyMemory(&mOriginal[21], &tItemModifier, 4);
	mOriginalSize = S_PC_CAFE_PETTOBAG_RECV;
}

void MyTransfer::REFRESH_BAG_ITEM(int tResult, int tItemIndex, int iPage, int iIndex, int iInvenSlot)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_REFRESH_BAG_ITEM;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tItemIndex, 4);
	CopyMemory(&mOriginal[9], &iPage, 4);
	CopyMemory(&mOriginal[13], &iIndex, 4);
	CopyMemory(&mOriginal[17], &iInvenSlot, 4);
	mOriginalSize = S_REFRESH_BAG_ITEM;
}

void MyTransfer::B_COSTUME_HIDE_RECV(int tResult)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_COSTUME_HIDE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	memset(&mOriginal[5], 0, 8);
	mOriginalSize = S_COSTUME_HIDE_RECV;
}

void MyTransfer::B_ENGRAVE_WEAPON_RECV(int tResult, int tMoney, int tCP, int tProtectionCharm, int tImproveState)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ENGRAVE_WEAPON_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tMoney, 4);
	CopyMemory(&mOriginal[9], &tCP, 4);
	CopyMemory(&mOriginal[13], &tProtectionCharm, 4);
	CopyMemory(&mOriginal[17], &tImproveState, 4);
	mOriginalSize = S_ENGRAVE_WEAPON_RECV;
}

void MyTransfer::B_UPGRADE_TO_LEGENDARY_RECV(int tResult, int tMode, int tCost, int tCPCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 171;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tMode, 4);
	CopyMemory(&mOriginal[9], &tCost, 4);
	CopyMemory(&mOriginal[13], &tCPCost, 4);
	CopyMemory(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = 41;
}

void MyTransfer::B_TOWER_INFO_RECV(TOWER_INFO* tTowerInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TOWER_INFO_RECV;
	CopyMemory(&mOriginal[1], tTowerInfo, 48);
	memset(&mOriginal[49], -1, 48);
	mOriginalSize = S_TOWER_INFO_RECV;
}

void MyTransfer::B_TOWER_UPGRADE_RECV(int tResult, int tPage, int tIndex)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_TOWER_UPGRADE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tPage, 4);
	CopyMemory(&mOriginal[9], &tIndex, 4);
	mOriginalSize = S_TOWER_UPGRADE_RECV;
}

void MyTransfer::B_ADD_AMULET_ABILITY(int tResult, int tMemory, int tValue1, int tValue2, int tValue3)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 169;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tMemory, 4);
	CopyMemory(&mOriginal[9], &tValue1, 4);
	CopyMemory(&mOriginal[13], &tValue2, 4);
	CopyMemory(&mOriginal[17], &tValue3, 4);
	mOriginalSize = 21;
}

void MyTransfer::B_DEMAND_BLOODSTAINED_SHOP_INFO_RECV(int tPages, BLOODSTAINEDSHOP_INFO* tInfo)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_DEMAND_BLOODSTAINED_SHOP_INFO_RECV;
	CopyMemory(&mOriginal[1], &tPages, 4);
	CopyMemory(&mOriginal[5], tInfo, sizeof(BLOODSTAINEDSHOP_INFO));
	mOriginalSize = S_DEMAND_BLOODSTAINED_SHOP_INFO_RECV;
}

void MyTransfer::B_BUY_BLOODSTAINED_SHOP_RECV(int tResult, int tRemainPoints, int tPage, int tIndex, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_BUY_BLOODSTAINED_SHOP_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tRemainPoints, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tValue[0], 24);
	mOriginalSize = S_BUY_BLOODSTAINED_SHOP_RECV;
}

void MyTransfer::B_BUY_CAPSULE_SHOP_RECV(int tResultQuantity, int tPage, int tIndex1, int tIndex2, int tInvenSlot1, int tInvenSlot2, int tCapsuleType, int tCost, int tValue[8])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 141;
	CopyMemory(&mOriginal[1], &tResultQuantity, 4);
	CopyMemory(&mOriginal[5], &tPage, 4);
	CopyMemory(&mOriginal[9], &tIndex1, 4);
	CopyMemory(&mOriginal[13], &tIndex2, 4);
	CopyMemory(&mOriginal[17], &tInvenSlot1, 4);
	CopyMemory(&mOriginal[21], &tInvenSlot2, 4);
	CopyMemory(&mOriginal[25], &tCapsuleType, 4);
	CopyMemory(&mOriginal[29], &tCost, 4);
	CopyMemory(&mOriginal[33], &tValue[0], 32);
	mOriginalSize = 65;
}
void MyTransfer::B_ULTIMATE_ENCHANT_RECV(int tResult, int tCost, int tImproveValue, int tValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_ULTIMATE_ENCHANT_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tImproveValue, 4);
	CopyMemory(&mOriginal[13], &tValue, 4);
	mOriginalSize = S_ULTIMATE_ENCHANT_RECV;
}
void MyTransfer::B_GET_CURRENT_HERO_RANKING_RECV(int tResult, HERO_RANKING_INFO* hRank)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 148;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], hRank, sizeof(HERO_RANKING_INFO));
	mOriginalSize = 685;
}
void MyTransfer::B_CLAIM_HERO_RANK_REWARD_RECV(int tResult, int tRewardValue)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 149;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tRewardValue, 4);
	mOriginalSize = 9;
}
void MyTransfer::B_GET_OLD_HERO_RANKING_RECV(int tResult, HERO_RANKING_INFO* hRank)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 150;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], hRank, sizeof(HERO_RANKING_INFO));
	mOriginalSize = 685;
}
void MyTransfer::B_GET_CASH_ITEM_INFO_RECV(int tResult, int tVersion, int tCashItemInfo[4][14][10][4])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_GET_CASH_ITEM_INFO_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tVersion, 4);
	CopyMemory(&mOriginal[9], tCashItemInfo, 8960);
	mOriginalSize = S_GET_CASH_ITEM_INFO_RECV;
}
void MyTransfer::B_PROXY_SHOP(int tUserIndex, DWORD tUniqueNumber, float tUserLocation[3], char tAvatarName[MAX_AVATAR_NAME_LENGTH], char tShopName[MAX_PSHOP_NAME_LENGTH], int tMode)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 134;
	CopyMemory(&mOriginal[1], &tUserIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], &tUserLocation[0], 12);
	CopyMemory(&mOriginal[21], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[34], &tShopName[0], 27);
	CopyMemory(&mOriginal[61], &tMode, 4);
	mOriginalSize = 65;
}
void MyTransfer::B_DEMAND_PROXY_INFO(int a, int b, PROXYSHOP_INFO* mProxy)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 135;
	CopyMemory(&mOriginal[1], &a, 4);
	CopyMemory(&mOriginal[5], &b, 4);
	CopyMemory(&mOriginal[9], mProxy, sizeof(PROXYSHOP_INFO));
	mOriginalSize = 1033;
}
void MyTransfer::B_BUY_PROXY_SHOP_ITEM(int tResult, PROXYSHOP_INFO* tProxyInfo, int tPage, int tIndex, int tValue[12])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 136;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], tProxyInfo, sizeof(PROXYSHOP_INFO));
	CopyMemory(&mOriginal[1029], &tPage, 4);
	CopyMemory(&mOriginal[1033], &tIndex, 4);
	CopyMemory(&mOriginal[1037], &tValue[0], 48);
	mOriginalSize = 1085;
}
void MyTransfer::B_CLAIM_MONEY_PROXY_SHOP(int tResult, int aMoney, int aMoney2)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 137;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &aMoney, 4);
	CopyMemory(&mOriginal[9], &aMoney2, 4);
	mOriginalSize = 13;
}
void MyTransfer::B_FISHING_STATE_RECV(int tUserIndex, DWORD tUniqueNumber, int tFishingMode, int tFishingState, int tFishingStep)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 127;
	CopyMemory(&mOriginal[1], &tUserIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], &tFishingMode, 4);
	CopyMemory(&mOriginal[13], &tFishingState, 4);
	CopyMemory(&mOriginal[17], &tFishingStep, 4);
	mOriginalSize = 21;
}
void MyTransfer::B_FISHING_RESULT_RECV(int tUserIndex, DWORD tUniqueNumber, int tFishingMode, int tFishingState, int tFishingStep)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 128;
	CopyMemory(&mOriginal[1], &tUserIndex, 4);
	CopyMemory(&mOriginal[5], &tUniqueNumber, 4);
	CopyMemory(&mOriginal[9], &tFishingMode, 4);
	CopyMemory(&mOriginal[13], &tFishingState, 4);
	CopyMemory(&mOriginal[17], &tFishingStep, 4);
	mOriginalSize = 21;
}
void MyTransfer::B_FISHING_SUCCESS_RECV(int tResult, int tItemIndex, int tPage, int tIndex, int tInvenSlot)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 129;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tItemIndex, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tInvenSlot, 4);
	mOriginalSize = 21;
}
void MyTransfer::B_FACTION_TRAP_RECV(FACTION_TRAP* tFactionTrap)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 130;
	CopyMemory(&mOriginal[1], tFactionTrap, sizeof(FACTION_TRAP));
	mOriginalSize = 61;
}
void MyTransfer::B_ZONE_88_INFO_RECV(int tSort, int tState)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 125;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tState, 4);
	mOriginalSize = 9;
}
void MyTransfer::B_ZONE_88_INFO2_RECV(int tSort, char tAvatarName[MAX_AVATAR_NAME_LENGTH], int tTribe)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 126;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tAvatarName[0], MAX_AVATAR_NAME_LENGTH);
	CopyMemory(&mOriginal[5 + MAX_AVATAR_NAME_LENGTH], &tTribe, 4);
	mOriginalSize = 22;
}
void MyTransfer::B_CLAIM_LOGIN_REWARD_RECV(int tSort, int tItemIndex, int tPage, int tIndex, int tInvenIndex, int tLoginClaimState, int tLoginEventMallPoint)
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 174;
	CopyMemory(&mOriginal[1], &tSort, 4);
	CopyMemory(&mOriginal[5], &tItemIndex, 4);
	CopyMemory(&mOriginal[9], &tPage, 4);
	CopyMemory(&mOriginal[13], &tIndex, 4);
	CopyMemory(&mOriginal[17], &tInvenIndex, 4);
	CopyMemory(&mOriginal[21], &tLoginClaimState, 4);
	CopyMemory(&mOriginal[25], &tLoginEventMallPoint, 4);
	mOriginalSize = 29;
}
void MyTransfer::B_RETURN_TO_TOWN_RECV()
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 143;
	mOriginalSize = 1;
}
void MyTransfer::B_CLOAK_UPGRADE_RECV(int tResult, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = P_CLOAK_UPGRADE_RECV;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tValue[0], 24);
	mOriginalSize = S_CLOAK_UPGRADE_RECV;
}
void MyTransfer::B_UNSEAL_LEGENDARY_RECV(int tResult, int tCost, int tValue[6])
{
	ZeroMemory(&mOriginal, MAX_TRANSFER_BUFFER_SIZE);
	mOriginal[0] = 173;
	CopyMemory(&mOriginal[1], &tResult, 4);
	CopyMemory(&mOriginal[5], &tCost, 4);
	CopyMemory(&mOriginal[9], &tValue[0], 24);
	mOriginalSize = 33;
}