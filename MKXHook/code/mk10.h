#pragma once
#include "mk10utils.h"
#include "MKCharacter.h"

#define GFG_GAME_INFO 0x1430DBA00


#define MKXHOOK_VERSION "0.5.5"

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


namespace MK10 {
	const char* GetGameName();
	void SetCharacter(PLAYER_NUM plr, const char* character);
	void SetTrait(PLAYER_NUM plr, const char* name);
	void ClearTraits(PLAYER_NUM plr);
	void SetStage(const char* stage);
	void SlowGameTimeForXTicks(float speed, int ticks);
	void ResetStageInteractables();

	MKCharacter* GetCharacterObject(PLAYER_NUM plr);
	int64 GetCharacterInfo(PLAYER_NUM plr);



	void  GetCharacterPosition(FVector* vec, PLAYER_NUM plr);
	void  SetCharacterPosition(FVector* vec, PLAYER_NUM plr);


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

	void __fastcall  HookDamageMultiplier(int64 ptr, float mult);
	void __fastcall  HookDamageMultiplierTwo(int64 ptr, float mult);
	void __fastcall  HookDamageMultiplierThree(int64 ptr, float mult);
	int64 __fastcall HookGetCharacterVictory(const char* name, const char* packageID, char* packageName, int packageBuffer);

}


