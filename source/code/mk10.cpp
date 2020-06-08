#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>

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
	((void(__fastcall*)())GetMKXAddr(0x140CAE620))();
}

void __fastcall MK10Hooks::HookStartupFightRecording()
{
	printf("MKXHook::Info() | Starting a new fight!\n");
	// recording call
	((void(__fastcall*)())GetMKXAddr(0x1403922B0))();
	if (TheMenu->bPlayer1ModifierEnabled)
	    MK10::SetCharacter(PLAYER1,TheMenu->szPlayer1ModifierCharacter);
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
