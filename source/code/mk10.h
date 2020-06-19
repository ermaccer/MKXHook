#pragma once
#include "mk10utils.h"

// in case it gets updated - defines
#define GFG_GAME_INFO 0x1430D4950
#define GALLERY_INFO 0x14330A450

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = -1,
	PLAYER1,
	PLAYER2,
	PLAYER3,
	PLAYER4,
	MAX_PLAYERS,
	CPU_PLAYER,
	NOT_CPU_PLAYER,
	BACKGROUND_PLAYER
};

struct FVector
{
	float X;
	float Y;
	float Z;
};



namespace MK10 {
	const char* GetGameName();
	void SetCharacter(PLAYER_NUM plr, const char* character);
	void SlowGameTimeForXTicks(float speed, int ticks);
	void ResetStageInteractables();

	int64 GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);
}


namespace MK10Hooks {
	// util
	int64 IsNPCCharacter(const char* character);
	int64 IsNPCCharacterMale(const char* character);

	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording();
	int64 __fastcall HookCheckIfCharacterFemale(const char* character);
	int64 HookCheckFatalityStatus();
	void __fastcall HookDLCCellAmount(int64 ptr, int cells, int64 a3, int a4);
	int64 __fastcall HookIsEasyFatalityAvailable(const char* name);

	void __fastcall  Hook30To60Swap(int64 game, int a2);
}


