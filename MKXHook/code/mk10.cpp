#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>
#include "eSettingsManager.h"
#include "eNotifManager.h"
#include "MKCamera.h"
#include <imgui.h>
#include "helper/eMouse.h"

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
	((void(__fastcall*)(int64, const char*, const char*, int))_addr(0x1405493C0))((int64)GetInfo(plr), name, name, 1);
}

void ClearTraits(PLAYER_NUM plr)
{
	((void(__fastcall*)(int64))_addr(0x14054CBF0))((int64)GetInfo(plr));
}

void SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, unsigned int))_addr(0x140457000))(speed, ticks);
}

void ExecuteScriptFunction(const char* source, unsigned int hash)
{
	((void(__fastcall*)(const char*, unsigned int))_addr(0x14047DB80))(source, hash);
}


MKCharacter* GetObj(PLAYER_NUM plr)
{
	return ((MKCharacter*(__fastcall*)(PLAYER_NUM))_addr(0x1405BBF60))(plr);
}

PlayerInfo* GetInfo(PLAYER_NUM plr)
{
	return GetGameInfo()->GetInfo(plr);
}


void GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = (int64)GetInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))_addr(0x140CAEF00))(ptr, vec);

}

void HideHUD()
{
	((void(__fastcall*)(int, int))_addr(0x14047E990))(8, 8);
}

void ShowHUD()
{
	((void(__fastcall*)(int, int))_addr(0x14047ED30))(8, 8);
}

unsigned int HashString(const char* input)
{
	unsigned int result;
	int stringLength;
	int character;

	if (!input)
		return 0;
	stringLength = -1;

	do
		++stringLength;
	while (input[stringLength]);

	for (result = 0x811C9DC5; stringLength; --stringLength)
	{
		character = *(unsigned char*)input++;
		result = character ^ (unsigned int)(0x1000193 * result);
	}
	return result;
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
	eMouse::UpdateMouse();

	MKCharacter* p1 = GetObj(PLAYER1);
	MKCharacter* p2 = GetObj(PLAYER2);
	PlayerInfo* p1_info = GetInfo(PLAYER1);
	PlayerInfo* p2_info = GetInfo(PLAYER2);

	if (TheMenu->m_bSlowMotion)
		SlowGameTimeForXTicks(TheMenu->m_fSlowMotionSpeed, 10);

	if (TheMenu->m_bChangePlayerScale)
	{
		if (p1)	p1->SetScale(&TheMenu->m_vP1Scale);
		if (p2)	p2->SetScale(&TheMenu->m_vP2Scale);
	}


	if (TheMenu->m_bChangePlayerSpeed)
	{
		if (p1)	p1->SetSpeed(TheMenu->m_fP1Speed);
		if (p2)	p2->SetSpeed(TheMenu->m_fP2Speed);
	}

	if (p1)
	{
		if (TheMenu->m_bInfiniteHealthP1)	p1->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP1)		p1->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP1)	p1->SetLife(0.01f);
		if (TheMenu->m_bInfiniteMeterP1) p1_info->SetMeter(1.0f);
		if (TheMenu->m_bZeroMeterP1) p1_info->SetMeter(0.0f);
		if (TheMenu->m_bDisableHeadTracking) p1->KillHeadTracking();
		if (TheMenu->m_bInfiniteRunP1) p1_info->SetEnergy(100.0f);
		if (TheMenu->m_bNoRunP1) p1_info->SetEnergy(0.0f);


		if (TheMenu->m_bAIDroneModifierP1)
		{
			if (AIDrone* drone = p1_info->GetDrone())
				drone->Set(TheMenu->szPlayer1AI);
		}

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p1_info)
				p1_info->SetDamageMult(1.0f);
		}

		if (TheMenu->m_bAutoHideHUD)
			HideHUD();

		if (TheMenu->m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING && TheMenu->m_bCustomCameras)
		{
			TheMenu->m_bDisableHeadTracking = true;
		}

	}
	if (p2)
	{
		if (TheMenu->m_bInfiniteHealthP2)	p2->SetLife(1000.0f);
		if (TheMenu->m_bNoHealthP2)	p2->SetLife(0.0f);
		if (TheMenu->m_bOneHealthP2)	p2->SetLife(0.01f);
		if (TheMenu->m_bInfiniteMeterP2) p2_info->SetMeter(1.0f);
		if (TheMenu->m_bDisableHeadTracking) p2->KillHeadTracking();
		if (TheMenu->m_bInfiniteRunP2) p2_info->SetEnergy(100.0f);
		if (TheMenu->m_bNoRunP2) p2_info->SetEnergy(0.0f);

		if (TheMenu->m_bAIDroneModifierP2)
		{
			if (AIDrone* drone = p2_info->GetDrone())
				drone->Set(TheMenu->szPlayer2AI);
		}

		if (TheMenu->m_bDisableComboScaling)
		{
			if (p2_info)
				p2_info->SetDamageMult(1.0f);
		}
	}



	if (TheMenu->m_bStopTimer)
	{
		*(int*)(_addr(0x143316850) + 0x1964) = 91;
	}

	
	TheMenu->UpdateFreecam();

	if (TheMenu->m_bForceCameraUpdate)
	{
		if (TheCamera)
		{
			TheCamera->HookedSetPosition(&TheMenu->camPos);
			TheCamera->HookedSetRotation(&TheMenu->camRot);
			TheCamera->SetFOV(TheMenu->camFov);
		}

	}

	if (SettingsMgr->bDisableCinematicLetterboxing)
	{
		ExecuteScriptFunction("fg_utils.mko", HashString("SnapLetterBoxOff"));
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
		GetGameInfo()->SetStage(TheMenu->szStageModifierStage);

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

	printf("MKXHook::Info() | %s VS %s\n", GetInfo(PLAYER1)->GetName(), GetInfo(PLAYER2)->GetName());

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

void MK10Hooks::HookDisableLetterBox()
{
	RunScriptFunction("fg_utils.mko", HashString("SnapLetterBoxOff"));
}
