#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCamera.h"
#include <imgui.h>



const char* szCharactersRandom[] = {
	// random array = - costumes
	"Rain_A",
	"Baraka_A",
	"Sindel_A",
	"Tanya_A",
	"ShinnokBoss_A",

	"CHAR_Alien_A",
	"char_aztec_a",
	"CHAR_BoRaiChoDLC_A",
	"char_cagejr_a",
	"CHAR_Ermac_A",
	"Char_Goro_A",
	"CHAR_Jason_A",
	"CHAR_JaxJr_A",
	"CHAR_Jax_A",
	"CHAR_JohnnyCage_A",
	"CHAR_Kano_A",
	"CHAR_KenshiJr_A",
	"CHAR_Kenshi_A",
	"CHAR_Kitana_A",
	"CHAR_KungLaoJr_A",
	"CHAR_KungLao_A",
	"char_ladybug_a",
	"CHAR_LeatherFace_A",
	"CHAR_LiuKang_A",
	"CHAR_MasterMale_A",
	"CHAR_Mileena_A",
	"CHAR_Nomad_A",
	"CHAR_Predator_A",
	"CHAR_QuanChi_A",
	"CHAR_Raiden_A",
	"CHAR_Reptile_A",
	"char_scorpion_a",
	"CHAR_Shinnok_A",
	"CHAR_Sonya_A",
	"char_subzero_a",
	"CHAR_TanyaDLC_A",
	"CHAR_Tremor_A",
	"Char_Triborg_A",

};

const char * MK10::GetGameName()
{
	return ((const char*(__fastcall*)())_addr(0x14160AAB0))();
}

void MK10::SetCharacter(PLAYER_NUM plr, const char * character)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, int, const char*))_addr(0x14049C400))(gameinfo, (int64)plr, character);
}

void MK10::SetTrait(PLAYER_NUM plr, const char * name)
{
	((void(__fastcall*)(int64, const char*, const char*, int))_addr(0x1405493C0))(GetCharacterInfo(plr), name, name, 1);
}

void MK10::ClearTraits(PLAYER_NUM plr)
{
	((void(__fastcall*)(int64))_addr(0x14054CBF0))(GetCharacterInfo(plr));
}

void MK10::SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))_addr(0x14049C360))(gameinfo, stage);
}

void MK10::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, unsigned int))_addr(0x140457000))(speed, ticks);
}

void MK10::ResetStageInteractables()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	int64 bgndinfo = *(int64*)(gameinfo + 0x58);

	((void(__fastcall*)(int64))_addr(0x1401851C0))(bgndinfo);
	((void(__fastcall*)(int64))_addr(0x1401852B0))(bgndinfo);
	((void(__fastcall*)(int64))_addr(0x140184EF0))(bgndinfo);

}

MKCharacter* MK10::GetCharacterObject(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1405BBF60))(plr);
}

int64 MK10::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	return ((int64(__fastcall*)(int64,PLAYER_NUM))_addr(0x140485F80))(gameinfo,plr);
}


void MK10::GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr =*(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector* ))_addr(0x140CAEF00))(ptr, vec);

}

void MK10::SetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_addr(0x140CBF720))(ptr, vec);
}

void MK10::SetCharacterMeter(int64 obj, float meter)
{
	((void(__fastcall*)(int64, float))_addr(0x14055EC40))(obj, meter);
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
	Notifications->Update();

	if (TheMenu->bSlowMotionEnabled)
		MK10::SlowGameTimeForXTicks(TheMenu->fSlowMotionSpeed, 10);


	if (TheMenu->bChangePlayerScale)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			MK10::GetCharacterObject(PLAYER1)->SetScale(&TheMenu->fPlayer1Scale);
		if (MK10::GetCharacterObject(PLAYER2))
			MK10::GetCharacterObject(PLAYER2)->SetScale(&TheMenu->fPlayer2Scale);
	}


	if (TheMenu->bChangePlayerSpeed)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			MK10::GetCharacterObject(PLAYER1)->SetSpeed(TheMenu->fPlayer1Speed);
		if (MK10::GetCharacterObject(PLAYER2))
			MK10::GetCharacterObject(PLAYER2)->SetSpeed(TheMenu->fPlayer2Speed);
	}

	if (MK10::GetCharacterObject(PLAYER1))
	{
		if (TheMenu->bInfiniteHealthPlayer1)
			MK10::GetCharacterObject(PLAYER1)->SetLife(1000.0f);
		if (TheMenu->b0HealthPlayer1)
			MK10::GetCharacterObject(PLAYER1)->SetLife(0.0f);
		if (TheMenu->b1HealthPlayer1)
			MK10::GetCharacterObject(PLAYER1)->SetLife(0.01f);
		if (TheMenu->bInfiniteSuperBarPlayer1)
			MK10::SetCharacterMeter(MK10::GetCharacterInfo(PLAYER1), 1.0f);
	}
	if (MK10::GetCharacterObject(PLAYER2))
	{
		if (TheMenu->bInfiniteHealthPlayer2)
			MK10::GetCharacterObject(PLAYER2)->SetLife(1000.0f);
		if (TheMenu->b0HealthPlayer2)
			MK10::GetCharacterObject(PLAYER2)->SetLife(0.0f);
		if (TheMenu->b1HealthPlayer2)
			MK10::GetCharacterObject(PLAYER2)->SetLife(0.01f);
		if (TheMenu->bInfiniteSuperBarPlayer2)
			MK10::SetCharacterMeter(MK10::GetCharacterInfo(PLAYER2), 1.0f);
	}



	if (TheMenu->bStopTimer)
	{
		*(int*)(_addr(0x143316850) + 0x1964) = 91;
	}

	if (TheMenu->bFreeCameraMovement)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->iFreeCameraRotSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->iFreeCameraRotSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}

	if (TheMenu->bFreezePosition)
	{
		MK10::SetCharacterPosition(&TheMenu->plrPos, PLAYER1);
		MK10::SetCharacterPosition(&TheMenu->plrPos, PLAYER2);
	}

	if (TheMenu->bForceMoveCamera)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	

	((void(__fastcall*)())_addr(0x140CB2BA0))();
}

void __fastcall MK10Hooks::HookStartupFightRecording()
{
	printf("MKXHook::Info() | Starting a new fight!\n");
	TheMenu->bEnableCustomCameras = false;
	TheMenu->bYObtained = false;
	// recording call
	((void(__fastcall*)())_addr(0x1403924C0))();

	if (TheMenu->bStageModifier)
		MK10::SetStage(TheMenu->szStageModifierStage);

	if (!TheMenu->bEnableRandomFights)
	{
		if (TheMenu->bPlayer1ModifierEnabled)
			MK10::SetCharacter(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
		if (TheMenu->bPlayer2ModifierEnabled)
			MK10::SetCharacter(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

		if (!TheMenu->bCustomTraitsP1)
			if (TheMenu->bPlayer1TraitEnabled)
				((void(__fastcall*)(int64, int))_addr(0x140599200))(PLAYER1, TheMenu->iPlayer1Trait);
		if (!TheMenu->bCustomTraitsP2)
			if (TheMenu->bPlayer2TraitEnabled)
				((void(__fastcall*)(int64, int))_addr(0x140599200))(PLAYER2, TheMenu->iPlayer2Trait);
	}


	if (TheMenu->bEnableRandomFights)
	{
		int totalSize = sizeof(szCharactersRandom) / sizeof(szCharactersRandom[0]);
		int chr = rand() % totalSize;
		printf("MKXHook::RandomFight() | Got: %s\n", szCharactersRandom[chr]);
		MK10::SetCharacter(PLAYER1, szCharactersRandom[chr]);
		if (!IsNPCCharacter(szCharactersRandom[chr]))
		{
			int var = rand() % 3;
			if (var == 0) var = 1;
			((void(__fastcall*)(int64, int))_addr(0x140599200))(PLAYER1, var);
		}
	}
	if (TheMenu->bCustomTraitsP1)
	{
		if (!TheMenu->bCustomTraitAppendP1)
			MK10::ClearTraits(PLAYER1);
		for (int i = 0; i < P1Traits.size(); i++)
			MK10::SetTrait(PLAYER1, P1Traits[i].c_str());

	}
	if (TheMenu->bCustomTraitsP2)
	{
		if (!TheMenu->bCustomTraitAppendP2)
			MK10::ClearTraits(PLAYER2);
		for (int i = 0; i < P2Traits.size(); i++)
			MK10::SetTrait(PLAYER2, P2Traits[i].c_str());

	}

	printf("MKXHook::Info() | %s VS %s\n", ((const char*(__fastcall*)(int64))_addr(0x140553FF0))(MK10::GetCharacterInfo(PLAYER1)),
		((const char*(__fastcall*)(int64))_addr(0x140553FF0))(MK10::GetCharacterInfo(PLAYER2)));

}

int64 __fastcall MK10Hooks::HookCheckIfCharacterFemale(const char * character)
{
	printf("MKXHook::HookCheckCharacterFemale() | Checking for %s\n", character);

	if (IsNPCCharacter(character))
		return IsNPCCharacterMale(character);
	else
		return ((int64(__fastcall*)(const char*))_addr(0x140484480))(character);;



}

int64 MK10Hooks::HookCheckFatalityStatus()
{
	return 1;
}



void __fastcall MK10Hooks::HookDamageMultiplier(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;

	((void(__fastcall*)(int64, float))_addr(0x14055D7E0))(ptr, mult);
}

void __fastcall MK10Hooks::HookDamageMultiplierTwo(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;

	((void(__fastcall*)(int64, float))_addr(0x14055D3B0))(ptr, mult);
}

void __fastcall MK10Hooks::HookDamageMultiplierThree(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;
	((void(__fastcall*)(int64, float))_addr(0x140549CE0))(ptr, mult);
}

int64 __fastcall MK10Hooks::HookGetCharacterVictory(const char * name, const char * packageID, char * packageName, int packageBuffer)
{
	const char* newName = name;

	if (strcmp(name, "rain_a") == 0)
	{
		newName = "char_kunglao_a";
	}

	return ((int64(__fastcall*)(const char*, const char*, char*, int))_addr(0x140553850))(newName,packageID,packageName,packageBuffer);
}

void MK10Hooks::HookDispatch(int64 ptr, int a2)
{
	if (TheMenu->bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int))*(int64*)(arg + 0xD8))(ptr, a2);
	}
	else
		((int64(__fastcall*)(int64, int))_addr(0x140875590))(ptr, a2);
}
