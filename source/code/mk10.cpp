#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>
#include "..\dxhook.h"
#include "eSettingsManager.h"

const char * MK10::GetGameName()
{
	return ((const char*(__fastcall*)())GetMKXAddr(0x141606530))();
}

void MK10::SetCharacter(PLAYER_NUM plr, const char * character)
{
	__int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);
	printf("MKXHook::SetCharacter() | Setting side %d as %s\n", plr, character);

	((void(__fastcall*)(int64, int, const char*))GetMKXAddr(0x1404972B0))(gameinfo, (int64)plr, character);
}

void MK10::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, unsigned int))GetMKXAddr(0x140451EB0))(speed, ticks);
}

void MK10::ResetStageInteractables()
{
	int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);
	int64 bgndinfo = *(int64*)(gameinfo + 0x58);

	((void(__fastcall*)(int64))GetMKXAddr(0x140184FE0))(bgndinfo);
	((void(__fastcall*)(int64))GetMKXAddr(0x1401850D0))(bgndinfo);
	((void(__fastcall*)(int64))GetMKXAddr(0x140184D10))(bgndinfo);

}

int64 MK10::GetCharacterObject(PLAYER_NUM plr)
{
	return ((int64(__fastcall*)(PLAYER_NUM))GetMKXAddr(0x1405B6E10))(plr);
}

int64 MK10::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);

	return ((int64(__fastcall*)(int64,PLAYER_NUM))GetMKXAddr(0x140480E30))(gameinfo,plr);
}


int64 MK10Hooks::IsNPCCharacter(const char * character)
{
	int64 result = 0;

	if (strcmp(character, "rain_a") == 0)
		result = 1;
	if (strcmp(character, "tanya_a") == 0)
		result = 1;
	if (strcmp(character, "sindel_a") == 0)
		result = 1;
	if (strcmp(character, "baraka_a") == 0)
		result = 1;
	if (strcmp(character, "shinnokboss_a") == 0)
		result = 1;

	return result;
}

int64 MK10Hooks::IsNPCCharacterMale(const char * character)
{
	int64 isMale = 1;

	if (strcmp(character, "rain_a") == 0)
		isMale = 0;
	if (strcmp(character, "baraka_a") == 0)
		isMale = 0;
	if (strcmp(character, "shinnokboss_a") == 0)
		isMale = 0;
	return isMale;
}

void __fastcall MK10Hooks::HookProcessStuff()
{
	TheMenu->Process();

	if (TheMenu->bInfiniteHealthPlayer1)
	{
		if (MK10::GetCharacterObject(PLAYER1))
		 ((void(__fastcall*)(int64, float))GetMKXAddr(0x140200590))(MK10::GetCharacterObject(PLAYER1),1000.0f);
	}
	if (TheMenu->bInfiniteHealthPlayer2)
	{
		if (MK10::GetCharacterObject(PLAYER2))
			((void(__fastcall*)(int64, float))GetMKXAddr(0x140200590))(MK10::GetCharacterObject(PLAYER2), 1000.0f);
	}
	if (TheMenu->bInfiniteSuperBarPlayer1)
	{
		if (MK10::GetCharacterInfo(PLAYER1))
			((void(__fastcall*)(int64, float))GetMKXAddr(0x140559AF0))(MK10::GetCharacterInfo(PLAYER1), 1.0f);
	}


	((void(__fastcall*)())GetMKXAddr(0x140CAE620))();
}

void __fastcall MK10Hooks::HookStartupFightRecording()
{
	printf("MKXHook::Info() | Starting a new fight!\n");
	// recording call
	((void(__fastcall*)())GetMKXAddr(0x1403922B0))();
	if (TheMenu->bPlayer1ModifierEnabled)
	{
		MK10::SetCharacter(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
		// TODO: variations
		//__int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);
		//((void(__fastcall*)(int,int))GetMKXAddr(0x1405940B0))(PLAYER1, 1);
	}

	if (TheMenu->bPlayer2ModifierEnabled)
		MK10::SetCharacter(PLAYER2, TheMenu->szPlayer2ModifierCharacter);


}

int64 __fastcall MK10Hooks::HookCheckIfCharacterFemale(const char * character)
{
	printf("MKXHook::HookCheckCharacterFemale() | Checking for %s\n", character);

	if (IsNPCCharacter(character))
		return IsNPCCharacterMale(character);
	else
		return ((int64(__fastcall*)(const char*))GetMKXAddr(0x14047F330))(character);;



}

int64 MK10Hooks::HookCheckFatalityStatus()
{
	return 1;
}

void __fastcall MK10Hooks::HookDLCCellAmount(int64 ptr, int cells, int64 a3, int a4)
{
	cells = SettingsMgr->iAvailableDLCCells;
	printf("MKXHook::HookDLCCellAmount() | Requesting %d cells\n", cells, a4);
	((void(__fastcall*)(int64,int,int64,int))GetMKXAddr(0x14069A650))(ptr,cells,a3,a4);
}

int64 __fastcall MK10Hooks::HookIsEasyFatalityAvailable(const char * name)
{
	if (TheMenu->bInfiniteEasyFatalities)
		return 1;
	else 
    	return ((int64(__fastcall*)(const char*))GetMKXAddr(0x140505710))(name);
}

void __fastcall MK10Hooks::Hook30To60Swap(int64 game, int a2)
{
	((void(__fastcall*)(int,int))GetMKXAddr(0x140495110))(game,a2);
}
