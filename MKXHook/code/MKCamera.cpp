#include "mkcamera.h"
#include "mk10menu.h"
#include <iostream>
#include "MKCharacter.h"
MKCamera* TheCamera;

void MKCamera::SetPosition(FVector * pos)
{
	TheCamera = this;
	*(float*)(this + 0x414) = pos->X;
	*(float*)(this + 0x414 + 4) = pos->Y;
	*(float*)(this + 0x414 + 8) = pos->Z;
	((void(__fastcall*)(MKCamera*, FVector*))_addr(0x1414631A0))(this, pos);
}

void MKCamera::SetRotation(FRotator * rot)
{
	TheCamera = this;
	*(int*)(this + 0x414 + 12) = rot->Pitch;
	*(int*)(this + 0x414 + 12 + 4) = rot->Yaw;
	*(int*)(this + 0x414 + 12 + 8) = rot->Roll;

	((void(__fastcall*)(MKCamera*, FRotator*))_addr(0x141463BE0))(this, rot);
}

void MKCamera::SetFOV(float FOV)
{
	*(float*)(this + 0x42C) = FOV;
}

float MKCamera::GetFOV()
{
	return *(float*)(this + 0x42C);
}

void MKCamera::HookedSetPosition(FVector * pos)
{
	if (TheMenu->m_bCustomCameraFOV)
		SetFOV(TheMenu->camFov);
	else
		TheMenu->camFov = GetFOV();

	float oneTime = 0.0f;
	if (!TheMenu->m_bYObtained)
	{
		oneTime = pos->Y;
		TheMenu->m_bYObtained = true;
	}

	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector plrPos;
			FVector p2;
			FVector eyePos[2];
			FVector middle;
			if (GetObj(PLAYER1))
				GetCharacterPosition(&plrPos, PLAYER1);
			if (GetObj(PLAYER2))
				GetCharacterPosition(&p2, PLAYER2);
			switch (TheMenu->m_nCurrentCustomCamera)
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
					pos->Y += TheMenu->m_fAdjustCam * -1;
				else
					pos->Y += TheMenu->m_fAdjustCam;
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
			case CAMERA_HEAD_TRACKING:
				if (TheMenu->m_bUsePlayerTwoAsTracker)
				{
					if (GetObj(PLAYER2))
					{
						GetObj(PLAYER2)->GetBonePos("LeftEye", &eyePos[0]);
						GetObj(PLAYER2)->GetBonePos("RightEye", &eyePos[1]);
					}
				}

				else
				{
					if (GetObj(PLAYER1))
					{
						GetObj(PLAYER1)->GetBonePos("LeftEye", &eyePos[0]);
						GetObj(PLAYER1)->GetBonePos("RightEye", &eyePos[1]);
					}
				}

				middle = (eyePos[0] + eyePos[1]) / 2.0;
				

				pos->X = middle.X + TheMenu->m_fAdjustCustomHeadCameraX;
				pos->Y = middle.Y;
				pos->Z = middle.Z + TheMenu->m_fAdjustCustomHeadCameraZ;


				TheMenu->camPos = *pos;
				break;
			}
		}
		SetPosition(pos);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraPos)
		{
			TheMenu->camPos = *pos;
			SetPosition(pos);
		}
		else
			SetPosition(&TheMenu->camPos);
	}

}

void MKCamera::HookedSetRotation(FRotator * rot)
{

	if (TheMenu->m_bCustomCameras)
	{
		if (GetObj(PLAYER1) && GetObj(PLAYER2))
		{
			FVector p1, p2;
			FRotator headRot;
			if (GetObj(PLAYER1))
				GetCharacterPosition(&p1,PLAYER1);
			if (GetObj(PLAYER2))
				GetCharacterPosition(&p2, PLAYER2);

			switch (TheMenu->m_nCurrentCustomCamera)
			{
			case CAMERA_3RDPERSON:
				rot->Pitch = -900;
				rot->Yaw = 16000;
				rot->Roll = 0;
				TheMenu->camRot = *rot;

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

				if (p2.Y < p1.Y)
				{
					rot->Yaw = -16000;
				}

				TheMenu->camRot = *rot;
				break;
			case CAMERA_HEAD_TRACKING:
				if (TheMenu->m_bUsePlayerTwoAsTracker)
				{
					if (GetObj(PLAYER2))
						GetObj(PLAYER2)->GetBoneRot("Head", &headRot);
				}
				else
				{
					if (GetObj(PLAYER1))
						GetObj(PLAYER1)->GetBoneRot("Head", &headRot);
				}

				rot->Pitch = headRot.Pitch + TheMenu->m_fAdjustCustomHeadCameraY;
				rot->Yaw = 16000 + headRot.Yaw;
				rot->Roll = headRot.Roll / 100;
				TheMenu->camRot = *rot;

				if (TheMenu->m_bUsePlayerTwoAsTracker)
				{
					if (GetObj(PLAYER1))
						GetCharacterPosition(&p2, PLAYER1);
					if (GetObj(PLAYER2))
						GetCharacterPosition(&p1, PLAYER2);
				}
				else
				{
					if (GetObj(PLAYER1))
						GetCharacterPosition(&p1, PLAYER1);
					if (GetObj(PLAYER2))
						GetCharacterPosition(&p2, PLAYER2);
				}

				if (p2.Y < p1.Y && !TheMenu->m_bDontFlipCamera)
				{
					rot->Yaw = -16000 - headRot.Yaw;
				}
				TheMenu->camRot = *rot;
				break;
			}
		}
		SetRotation(rot);
	}
	else
	{
		if (!TheMenu->m_bCustomCameraRot)
		{
			TheMenu->camRot = *rot;
			SetRotation(rot);
		}
		else
			SetRotation(&TheMenu->camRot);
	}
}

FMatrix MKCamera::GetMatrix()
{
	FRotator rot = *(FRotator*)(this + 0x420);
	FMatrix mat(&rot);
	return mat;
}

