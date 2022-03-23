#pragma once
#include "GameInfo.h"
#include "mk10utils.h"
#include "MKCharacter.h"
#include "unreal/FVector.h"


#define GFG_GAME_INFO 0x1430DBA00

#define MKXHOOK_VERSION "0.5.9"

const char* GetGameName();
void SetCharacter(PLAYER_NUM plr, const char* character);
void SetTrait(PLAYER_NUM plr, const char* name);
void ClearTraits(PLAYER_NUM plr);
void SlowGameTimeForXTicks(float speed, int ticks);

MKCharacter* GetObj(PLAYER_NUM plr);
PlayerInfo* GetInfo(PLAYER_NUM plr);



void  GetCharacterPosition(FVector* vec, PLAYER_NUM plr);

void HideHUD();
void ShowHUD();

unsigned int HashString(const char* input);

namespace MK10Hooks {
	// util
	int64 IsNPCCharacter(const char* character);
	int64 IsNPCCharacterMale(const char* character);

	// hooks
	void __fastcall HookProcessStuff();
	void __fastcall HookStartupFightRecording();
	int64 __fastcall HookCheckIfCharacterFemale(const char* character);
	int64 HookCheckFatalityStatus();

	int64 __fastcall HookGetCharacterVictory(const char* name, const char* packageID, char* packageName, int packageBuffer);

	void   HookDispatch(int64 ptr, int a2);
}


