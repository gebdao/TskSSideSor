#include "MainApp.h"
#include "MyWork.h"
#include "MyUser.h"

#include <windows.h>
#include <stdio.h>
#include <stdarg.h>


extern USER mUSER[MAX_USER]; // dacă e global definit în alt fișier

void Log(const char* fmt, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, fmt);
	vsprintf(buffer, fmt, args);
	va_end(args);

	CreateDirectoryA("C:\\TS2Logs", NULL);
	FILE* f = fopen("C:\\TS2Logs\\debug_log.txt", "a");
	if (f)
	{
		fprintf(f, "%s", buffer);
		fclose(f);
	}
}

int MyWork::ReturnEffectState(int tUserIndex, int tSkillNumber)
{
	Log("ReturnEffectState: Skill %d de la jucator %d verificat.\n", tSkillNumber, tUserIndex);

	switch (tSkillNumber)
	{
	case 7:
	case 26:
	case 45:
		Log("Skill long-range %d permis pentru jucatorul %d (bypass efect).\n", tSkillNumber, tUserIndex);
		return 1;

	case 11:
	case 34:
	case 49:
		if (mUSER[tUserIndex].mEffectValue[1][0] == 0) return 1;
		break;

	case 15:
	case 30:
	case 53:
		if (mUSER[tUserIndex].mEffectValue[0][0] == 0) return 1;
		break;

	case 19:
	case 38:
	case 57:
		if ((mUSER[tUserIndex].mEffectValue[3][0] == 0) || (mUSER[tUserIndex].mEffectValue[7][0] == 0)) return 1;
		break;

	case 82:
		if (mUSER[tUserIndex].mEffectValue[9][0] == 0) return 1;
		break;

	case 83:
		if (mUSER[tUserIndex].mEffectValue[10][0] == 0) return 1;
		break;

	case 84:
		if (mUSER[tUserIndex].mEffectValue[11][0] == 0) return 1;
		break;

	case 103:
		if (mUSER[tUserIndex].mEffectValue[12][0] == 0) return 1;
		break;

	case 104:
		if (mUSER[tUserIndex].mEffectValue[13][0] == 0) return 1;
		break;

	case 105:
		if (mUSER[tUserIndex].mEffectValue[14][0] == 0) return 1;
		break;
	}

	Log("Skill %d blocat pentru jucatorul %d\n", tSkillNumber, tUserIndex);
	return 0;
}#define MAX_USER 1000

struct USER {
	int mEffectValue[20][5]; // sau cum este în codul tău
	// alte variabile...
};

extern USER mUSER[MAX_USER];
