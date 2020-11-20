#pragma once
#include "mk10utils.h"

// in case it gets updated - defines
#define GFG_GAME_INFO 0x1430DBA00


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

struct FRotator {
	int Pitch;
	int Yaw;
	int Roll;
};

namespace MK10 {
	const char* GetGameName();
	void SetCharacter(PLAYER_NUM plr, const char* character);
	void SetStage(const char* stage);
	void SlowGameTimeForXTicks(float speed, int ticks);
	void ResetStageInteractables();

	int64 GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);

	void  GetCharacterPosition(FVector* vec, PLAYER_NUM plr);
	void  SetCharacterPosition(FVector* vec, PLAYER_NUM plr);

	void  SetCharacterLife(int64 obj, float life);
	void  SetCharacterMeter(int64 obj, float meter);
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
	void __fastcall HookCamSetPos(int64 ptr, FVector* pos);
	void __fastcall HookCamSetRot(int64 ptr, FRotator* rot);
	int64 __fastcall HookIsEasyFatalityAvailable(const char* name);

	void __fastcall  Hook30To60Swap(int64 game, int a2);

	void __fastcall  HookDamageMultiplier(int64 ptr, float mult);
	void __fastcall  HookDamageMultiplierTwo(int64 ptr, float mult);
	void __fastcall  HookDamageMultiplierThree(int64 ptr, float mult);
	int64 __fastcall HookGetCharacterVictory(const char* name, const char* packageID, char* packageName, int packageBuffer);
}


