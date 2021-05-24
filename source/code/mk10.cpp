#include "..\pch.h"
#include "mk10.h"
#include "mk10utils.h"
#include "mk10menu.h"
#include <iostream>
#include "..\dxhook.h"
#include "eSettingsManager.h"
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
	return ((const char*(__fastcall*)())GetMKXAddr(0x14160AAB0))();
}

void MK10::SetCharacter(PLAYER_NUM plr, const char * character)
{
	__int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, int, const char*))GetMKXAddr(0x14049C400))(gameinfo, (int64)plr, character);
}

void MK10::SetStage(const char * stage)
{
	__int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);

	((void(__fastcall*)(int64, const char*))GetMKXAddr(0x14049C360))(gameinfo, stage);
}

void MK10::SlowGameTimeForXTicks(float speed, int ticks)
{
	((void(__fastcall*)(float, unsigned int))GetMKXAddr(0x140457000))(speed, ticks);
}

void MK10::ResetStageInteractables()
{
	int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);
	int64 bgndinfo = *(int64*)(gameinfo + 0x58);

	((void(__fastcall*)(int64))GetMKXAddr(0x1401851C0))(bgndinfo);
	((void(__fastcall*)(int64))GetMKXAddr(0x1401852B0))(bgndinfo);
	((void(__fastcall*)(int64))GetMKXAddr(0x140184EF0))(bgndinfo);

}

int64 MK10::GetCharacterObject(PLAYER_NUM plr)
{
	return ((int64(__fastcall*)(PLAYER_NUM))GetMKXAddr(0x1405BBF60))(plr);
}

int64 MK10::GetCharacterInfo(PLAYER_NUM plr)
{
	int64 gameinfo = *(__int64*)GetMKXAddr(GFG_GAME_INFO);

	return ((int64(__fastcall*)(int64,PLAYER_NUM))GetMKXAddr(0x140485F80))(gameinfo,plr);
}

void MK10::SetCharacterScale(PLAYER_NUM plr, FVector * scale)
{
	((void(__fastcall*)(int64, FVector*))GetMKXAddr(0x140CC1BD0))(MK10::GetCharacterObject(plr), scale);
}

void MK10::GetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr =*(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector* ))GetMKXAddr(0x140CAEF00))(ptr, vec);

}

void MK10::SetCharacterPosition(FVector * vec, PLAYER_NUM plr)
{
	int64 object = GetCharacterInfo(plr);
	int64 ptr = *(int64*)(object + 32);
	((int64(__fastcall*)(int64, FVector*))GetMKXAddr(0x140CBF720))(ptr, vec);
}

void MK10::SetCharacterLife(int64 obj, float life)
{
	((void(__fastcall*)(int64, float))GetMKXAddr(0x140200770))(obj, life);
}

void MK10::SetCharacterMeter(int64 obj, float meter)
{
	((void(__fastcall*)(int64, float))GetMKXAddr(0x14055EC40))(obj, meter);
}

void __fastcall MK10::CamSetPos(int64 ptr, FVector * pos)
{
	((void(__fastcall*)(int64, FVector*))GetMKXAddr(0x140870B50))(ptr, pos);
}

void __fastcall MK10::CamSetRot(int64 ptr, FRotator * rot)
{
	((void(__fastcall*)(int64, FRotator*))GetMKXAddr(0x140871820))(ptr, rot);
}

void __fastcall MK10::ActorCamSetPos(int64 ptr, FVector * pos)
{
	*(float*)(ptr + 0x414) = pos->X;
	*(float*)(ptr + 0x414 + 4) = pos->Y;
	*(float*)(ptr + 0x414 + 8) = pos->Z;
	((void(__fastcall*)(int64, FVector*))GetMKXAddr(0x1414631A0))(ptr, pos);
}

void __fastcall MK10::ActorCamSetRot(int64 ptr, FRotator * rot)
{
	*(int*)(ptr + 0x414 + 12) = rot->Pitch;
	*(int*)(ptr + 0x414 + 12 + 4) = rot->Yaw;
	*(int*)(ptr + 0x414 + 12 + 8) = rot->Roll;
	((void(__fastcall*)(int64, FRotator*))GetMKXAddr(0x141463BE0))(ptr, rot);
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

	// hot keys

	if (MK10::GetCharacterObject(PLAYER1) && MK10::GetCharacterObject(PLAYER2))
	{
		if (GetAsyncKeyState(VK_CONTROL))
		{
			if (GetAsyncKeyState(VK_F2))
				((void(__fastcall*)())GetMKXAddr(0x14055FE90))();
			if (GetAsyncKeyState(VK_F3))
				MK10::SlowGameTimeForXTicks(TheMenu->fSlowMotionSpeed, TheMenu->iSlowMotionTicks);
		}

	}


	if (TheMenu->bChangePlayerScale)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			MK10::SetCharacterScale(PLAYER1, &TheMenu->fPlayer1Scale);
		if (MK10::GetCharacterObject(PLAYER2))
			MK10::SetCharacterScale(PLAYER2, &TheMenu->fPlayer2Scale);
	}

	if (TheMenu->bInfiniteHealthPlayer1)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			MK10::SetCharacterLife(MK10::GetCharacterObject(PLAYER1), 1000.0f);
	}
	if (TheMenu->bInfiniteHealthPlayer2)
	{
		if (MK10::GetCharacterObject(PLAYER2))
			MK10::SetCharacterLife(MK10::GetCharacterObject(PLAYER2), 1000.0f);
	}
	if (TheMenu->b0HealthPlayer1)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			MK10::SetCharacterLife(MK10::GetCharacterObject(PLAYER1), 0.0f);
	}
	if (TheMenu->b0HealthPlayer2)
	{
		if (MK10::GetCharacterObject(PLAYER2))
			MK10::SetCharacterLife(MK10::GetCharacterObject(PLAYER2), 0.0f);
	}
	if (TheMenu->bInfiniteSuperBarPlayer1)
	{
		if (MK10::GetCharacterInfo(PLAYER1))
			MK10::SetCharacterMeter(MK10::GetCharacterInfo(PLAYER1), 1.0f);
	}

	if (TheMenu->bInfiniteSuperBarPlayer2)
	{
		if (MK10::GetCharacterInfo(PLAYER2))
			MK10::SetCharacterMeter(MK10::GetCharacterInfo(PLAYER2), 1.0f);
	}

	if (TheMenu->bChangePlayerSpeed)
	{
		if (MK10::GetCharacterObject(PLAYER1))
			((void(__fastcall*)(int64, float))GetMKXAddr(0x1401FD360))(MK10::GetCharacterObject(PLAYER1), TheMenu->fPlayer1Speed);
		if (MK10::GetCharacterObject(PLAYER2))
			((void(__fastcall*)(int64, float))GetMKXAddr(0x1401FD360))(MK10::GetCharacterObject(PLAYER2), TheMenu->fPlayer2Speed);
	}

	if (TheMenu->bStopTimer)
	{
		*(int*)(GetMKXAddr(0x143316850) + 0x1964) = 91;
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



	

	((void(__fastcall*)())GetMKXAddr(0x140CB2BA0))();
}

void __fastcall MK10Hooks::HookStartupFightRecording()
{
	printf("MKXHook::Info() | Starting a new fight!\n");
	TheMenu->bEnableCustomCameras = false;
	TheMenu->bYObtained = false;
	// recording call
	((void(__fastcall*)())GetMKXAddr(0x1403924C0))();

	if (TheMenu->bStageModifier)
		MK10::SetStage(TheMenu->szStageModifierStage);

	if (!TheMenu->bEnableRandomFights)
	{
		if (TheMenu->bPlayer1ModifierEnabled)
			MK10::SetCharacter(PLAYER1, TheMenu->szPlayer1ModifierCharacter);
		if (TheMenu->bPlayer2ModifierEnabled)
			MK10::SetCharacter(PLAYER2, TheMenu->szPlayer2ModifierCharacter);

		if (TheMenu->bPlayer1TraitEnabled)
			((void(__fastcall*)(int64, int))GetMKXAddr(0x140599200))(PLAYER1, TheMenu->iPlayer1Trait);

		if (TheMenu->bPlayer2TraitEnabled)
			((void(__fastcall*)(int64, int))GetMKXAddr(0x140599200))(PLAYER2, TheMenu->iPlayer2Trait);
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
			((void(__fastcall*)(int64, int))GetMKXAddr(0x140599200))(PLAYER1, var);
		}
	}

	printf("MKXHook::Info() | %s VS %s\n", ((const char*(__fastcall*)(int64))GetMKXAddr(0x140553FF0))(MK10::GetCharacterInfo(PLAYER1)),
		((const char*(__fastcall*)(int64))GetMKXAddr(0x140553FF0))(MK10::GetCharacterInfo(PLAYER2)));

}

int64 __fastcall MK10Hooks::HookCheckIfCharacterFemale(const char * character)
{
	printf("MKXHook::HookCheckCharacterFemale() | Checking for %s\n", character);

	if (IsNPCCharacter(character))
		return IsNPCCharacterMale(character);
	else
		return ((int64(__fastcall*)(const char*))GetMKXAddr(0x140484480))(character);;



}

int64 MK10Hooks::HookCheckFatalityStatus()
{
	return 1;
}

void __fastcall MK10Hooks::HookDLCCellAmount(int64 ptr, int cells, int64 a3, int a4)
{
	cells = SettingsMgr->iAvailableDLCCells;
	printf("MKXHook::HookDLCCellAmount() | Requesting %d cells\n", cells, a4);
	((void(__fastcall*)(int64,int,int64,int))GetMKXAddr(0x14069F8F0))(ptr,cells,a3,a4);
}

void __fastcall MK10Hooks::HookCamSetPos(int64 ptr, FVector* pos)
{
	float oneTime = 0.0f;
	if (!TheMenu->bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->bYObtained = true;
	}
	if (TheMenu->bEnableCustomCameras)
	{
		FVector plrPos;
		FVector p2;
		MK10::GetCharacterPosition(&plrPos, PLAYER1);
		MK10::GetCharacterPosition(&p2, PLAYER2);
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			pos->X = 5;
			pos->Y = oneTime - 330.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 210.0f + plrPos.Z;

		if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 210.0f;
				
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_3RDPERSON2:
			pos->X = 5;
			pos->Y = oneTime - 230.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 260.0f + plrPos.Z;;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 260.0f;
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON:
			pos->X = -10.0f;
			pos->Y = -230;
		    pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += TheMenu->fAdjustCam * -1;
			else
		     	pos->Y += TheMenu->fAdjustCam;
			pos->Z = 160.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON_MID:
			pos->X = 16.0f;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += 23.0f * -1;
			else
				pos->Y += 23.0f;
			pos->Z = 134.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		}
		MK10::CamSetPos(ptr, pos);
	}
	else
	{
		if (!TheMenu->bCustomCamera)
		{
			TheMenu->camPos = *pos;
			MK10::CamSetPos(ptr, pos);
		}
		else
			MK10::CamSetPos(ptr, &TheMenu->camPos);
	}

}

void __fastcall MK10Hooks::HookCamSetRot(int64 ptr, FRotator* rot)
{
	if (TheMenu->bEnableCustomCameras)
	{
		FVector p1, p2;
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			rot->Pitch = -900;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -900;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_3RDPERSON2:
			rot->Pitch = -4000;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -4000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON_MID:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		}

		MK10::CamSetRot(ptr, rot);
	}
	else
	{
		if (!TheMenu->bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			MK10::CamSetRot(ptr, rot);
		}
		else
			MK10::CamSetRot(ptr, &TheMenu->camRot);
	}

}

void __fastcall MK10Hooks::HookActorCamSetPos(int64 ptr, FVector * pos)
{
	if (TheMenu->bCustomFOV)
		*(float*)(ptr + 0x42C) = TheMenu->camFov;

	float oneTime = 0.0f;
	if (!TheMenu->bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->bYObtained = true;
	}
	if (TheMenu->bEnableCustomCameras)
	{
		FVector plrPos;
		FVector p2;
		MK10::GetCharacterPosition(&plrPos, PLAYER1);
		MK10::GetCharacterPosition(&p2, PLAYER2);
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			pos->X = 5;
			pos->Y = oneTime - 330.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 210.0f + plrPos.Z;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 210.0f;

			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_3RDPERSON2:
			pos->X = 5;
			pos->Y = oneTime - 230.0f;
			pos->Y += plrPos.Y * 0.85f;
			pos->Z = 260.0f + plrPos.Z;;

			if (p2.Y < plrPos.Y)
			{
				pos->Y += 600.0f;
				pos->Z = 260.0f;
			}


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON:
			pos->X = -10.0f;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += TheMenu->fAdjustCam * -1;
			else
				pos->Y += TheMenu->fAdjustCam;
			pos->Z = 160.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		case CAMERA_1STPERSON_MID:
			pos->X = 16.0f;
			pos->Y = -230;
			pos->Y += plrPos.Y - pos->Y;
			if (p2.Y < plrPos.Y)
				pos->Y += 23.0f * -1;
			else
				pos->Y += 23.0f;
			pos->Z = 134.0f + plrPos.Z;


			TheMenu->camPos = *pos;
			break;
		}
		MK10::ActorCamSetPos(ptr, pos);
	}
	else
	{
		if (!TheMenu->bCustomCamera)
		{
			TheMenu->camPos = *pos;
			MK10::ActorCamSetPos(ptr, pos);
		}
		else
			MK10::ActorCamSetPos(ptr, &TheMenu->camPos);
	}
}

void __fastcall MK10Hooks::HookActorCamSetRot(int64 ptr, FRotator * rot)
{
	if (TheMenu->bEnableCustomCameras)
	{
		FVector p1, p2;
		switch (TheMenu->iCurrentCustomCamera)
		{
		case CAMERA_3RDPERSON:
			rot->Pitch = -900;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -900;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_3RDPERSON2:
			rot->Pitch = -4000;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
				rot->Pitch = -4000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		case CAMERA_1STPERSON_MID:
			rot->Pitch = 0;
			rot->Yaw = 16000;
			rot->Roll = 0;
			TheMenu->camRot = *rot;
			MK10::GetCharacterPosition(&p1, PLAYER1);
			MK10::GetCharacterPosition(&p2, PLAYER2);

			if (p2.Y < p1.Y)
			{
				rot->Yaw = -16000;
			}

			TheMenu->camRot = *rot;
			break;
		}

		MK10::ActorCamSetRot(ptr, rot);
	}
	else
	{
		if (!TheMenu->bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			MK10::ActorCamSetRot(ptr, rot);
		}
		else
			MK10::ActorCamSetRot(ptr, &TheMenu->camRot);
	}

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

void __fastcall MK10Hooks::HookDamageMultiplier(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;

	((void(__fastcall*)(int64, float))GetMKXAddr(0x14055D7E0))(ptr, mult);
}

void __fastcall MK10Hooks::HookDamageMultiplierTwo(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;

	((void(__fastcall*)(int64, float))GetMKXAddr(0x14055D3B0))(ptr, mult);
}

void __fastcall MK10Hooks::HookDamageMultiplierThree(int64 ptr, float mult)
{
	if (SettingsMgr->bDisableComboDamageScaling)
		mult = 1.0f;
	((void(__fastcall*)(int64, float))GetMKXAddr(0x140549CE0))(ptr, mult);
}

int64 __fastcall MK10Hooks::HookGetCharacterVictory(const char * name, const char * packageID, char * packageName, int packageBuffer)
{
	const char* newName = name;

	if (strcmp(name, "rain_a") == 0)
	{
		newName = "char_kunglao_a";
	}

	return ((int64(__fastcall*)(const char*, const char*, char*, int))GetMKXAddr(0x140553850))(newName,packageID,packageName,packageBuffer);
}
