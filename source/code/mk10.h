#pragma once
#include "mk10utils.h"

// in case it gets updated
#define GFG_GAME_INFO 0x1430D4950

enum  PLAYER_NUM
{
	INVALID_PLAYER_NUM = 0xFFFFFFFF,
	PLAYER1 = 0x0,
	PLAYER2 = 0x1,
	PLAYER3 = 0x2,
	PLAYER4 = 0x3,
	MAX_PLAYERS = 0x4,
	CPU_PLAYER = 0x5,
	NOT_CPU_PLAYER = 0x6,
	BACKGROUND_PLAYER = 0x7,
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
}


