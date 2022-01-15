#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCamera.h"
#include <imgui.h>


const char * GetGameName()
{
	return ((const char*(__fastcall*)())_addr(0x14160AAB0))();
}

void SetCharacter(PLAYER_NUM plr, const char * character)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, int, const char*))_addr(0x14049C400))(gameinfo, (int64)plr, character);
}

void SetTrait(PLAYER_NUM plr, const char * name)
{
	((void(__fastcall*)(int64, const char*, const char*, int))_addr(0x1405493C0))(GetInfo(plr), name, name, 1);
}

void ClearTraits(PLAYER_NUM plr)
{
	((void(__fastcall*)(int64))_addr(0x14054CBF0))(GetInfo(plr));
}

void SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))_addr(0x14049C360))(gameinfo, stage);
}

void SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, unsigned int))_addr(0x140457000))(speed, ticks);
}

void ResetStageInteractables()
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);
	int64 bgndinfo = *(int64*)(gameinfo + 0x58);

	((void(__fastcall*)(int64))_addr(0x1401851C0))(bgndinfo);
	((void(__fastcall*)(int64))_addr(0x1401852B0))(bgndinfo);
	((void(__fastcall*)(int64))_addr(0x140184EF0))(bgndinfo);

}

MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1405BBF60))(plr);
}

int64 GetInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)_addr(GFG_GAME_INFO);

	return ((int64(__fastcall*)(int64, PLAYER_NUM))_addr(0x140485F80))(gameinfo, plr);
}


void GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_addr(0x140CAEF00))(ptr, vec);

}

void SetCharacterMeter(int64 obj, float meter)
{
	((void(__fastcall*)(int64, float))_addr(0x14055EC40))(obj, meter);
}

void HideHUD()
{
	((void(__fastcall*)(int, int))_addr(0x14047E990))(8, 8);
}

void ShowHUD()
{
	((void(__fastcall*)(int, int))_addr(0x14047ED30))(8, 8);
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

	if (TheMenu->m_bSlowMotion)
		SlowGameTimeForXTicks(TheMenu->m_fSlowMotionSpeed, 10);

	if (TheMenu->m_bChangePlayerScale)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetScale(&TheMenu->m_vP1Scale);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetScale(&TheMenu->m_vP2Scale);
	}


	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (GetObj(PLAYER1))
			GetObj(PLAYER1)->SetSpeed(TheMenu->m_fP1Speed);
		if (GetObj(PLAYER2))
			GetObj(PLAYER2)->SetSpeed(TheMenu->m_fP2Speed);
	}

	if (GetObj(PLAYER1))
	{
		if (TheMenu->m_bInfiniteHealthP1)
			GetObj(PLAYER1)->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)
			GetObj(PLAYER1)->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)
			GetObj(PLAYER1)->SetLife(0.01f);
		if (TheMenu->m_bInfiniteMeterP1)
			SetCharacterMeter(GetInfo(PLAYER1), 1.0f);

		if (TheMenu->m_bDisableHeadTracking)
		{
			GetObj(PLAYER1)->KillHeadTracking();
		}


		if (TheMenu->m_bAutoHideHUD)
			HideHUD();

		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING && TheMenu->m_bCustomCameras)
		{
			TheMenu->m_bDisableHeadTracking = true;
		}

	}
	if (GetObj(PLAYER2))
	{
		if (TheMenu->m_bInfiniteHealthP2)
			GetObj(PLAYER2)->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP2)
			GetObj(PLAYER2)->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP2)
			GetObj(PLAYER2)->SetLife(0.01f);
		if (TheMenu->m_bInfiniteMeterP2)
			SetCharacterMeter(GetInfo(PLAYER2), 1.0f);
	}



	if (TheMenu->m_bStopTimer)
	{
		*(int*)(_addr(0x143316850) + 0x1964) = 91;
	}

	if (TheMenu->m_bFreeCam)
	{
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
			TheMenu->camPos.X += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
			TheMenu->camPos.X -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
			TheMenu->camPos.Y += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
			TheMenu->camPos.Y -= TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
			TheMenu->camPos.Z += TheMenu->m_fFreeCameraSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
			TheMenu->camPos.Z -= TheMenu->m_fFreeCameraSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
			TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
			TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
			TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
			TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
			TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
			TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
			TheMenu->camFov -= 1.0f;
		if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
			TheMenu->camFov += 1.0f;
	}

	if (TheMenu->m_bForceCameraUpdate)
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
	TheMenu->m_bCustomCameraPos = false;
	TheMenu->m_bCustomCameraRot = false;
	TheMenu->m_bYObtained = false;
	TheMenu->m_bCustomCameras = false;

	// recording call
	((void(__fastcall*)())_addr(0x1403924C0))();

	if (TheMenu->m_bStageModifier)
		SetStage(TheMenu->szStageModifierStage);

	if (TheMenu->m_bPlayer1Modifier)
		SetCharacter(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
	if (TheMenu->m_bPlayer2Modifier)
		SetCharacter(PLAYER2, TheMenu->szPlayer2ModifierCharacter);


	if (TheMenu->m_bPlayer1CustomTrait)
	{
		ClearTraits(PLAYER1);
		for (int i = 0; i < P1Traits.size(); i++)
			SetTrait(PLAYER1, P1Traits[i].c_str());

	}
	if (TheMenu->m_bPlayer2CustomTrait)
	{
		ClearTraits(PLAYER2);
		for (int i = 0; i < P2Traits.size(); i++)
			SetTrait(PLAYER2, P2Traits[i].c_str());

	}

	printf("MKXHook::Info() | %s VS %s\n", ((const char*(__fastcall*)(int64))_addr(0x140553FF0))(GetInfo(PLAYER1)),
		((const char*(__fastcall*)(int64))_addr(0x140553FF0))(GetInfo(PLAYER2)));

}

int64 __fastcall MK10Hooks::HookCheckIfCharacterFemale(const char * character)
{
	if (IsNPCCharacter(character))
		return IsNPCCharacterMale(character);
	else
		return ((int64(__fastcall*)(const char*))_addr(0x140484480))(character);
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

	return ((int64(__fastcall*)(const char*, const char*, char*, int))_addr(0x140553850))(newName, packageID, packageName, packageBuffer);
}

void MK10Hooks::HookDispatch(int64 ptr, int a2)
{
	if (TheMenu->m_bHookDispatch)
	{
		int64 arg = *(int64*)(ptr);

		if (!TheMenu->m_bFreezeWorld)
			a2 = *(uint32_t*)(ptr + 0x18);

		if (*(uint32_t*)(ptr + 0x14) == a2)
			return;

		*(int*)(ptr + 0x14) = a2;
		((void(*)(int64, int))*(int64*)(arg + 0xD8))(ptr, a2);
	}
	else
		((int64(__fastcall*)(int64, int))_addr(0x140875590))(ptr, a2);
}
