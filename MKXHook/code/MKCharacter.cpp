#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk10.h"
#include "unreal/FName.h"
#include "unreal/FMatrix.h"

void MKCharacter::SetLife(float life)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140200770))(this, life);
}

void MKCharacter::SetScale(FVector * scale)
{
	((void(__fastcall*)(MKCharacter*, FVector*))_addr(0x140CC1BD0))(this, scale);
}

void MKCharacter::SetSpeed(float speed)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x1401FD360))(this, speed);
}

void MKCharacter::SetMeter(float value)
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x14055EC40))(this, value);
}

void MKCharacter::ActivateHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140978DF0))(this, 0.5);
}

void MKCharacter::KillHeadTracking()
{
	((void(__fastcall*)(MKCharacter*, float))_addr(0x140978D80))(this, 0.5);
}

void MKCharacter::SetBoneSize(const char * name, float size)
{
	// 
	((void(__fastcall*)(MKCharacter*, const char*, float))_addr(0x14097a4b0))(this, name, size);
	((void(__fastcall*)(MKCharacter*, const char*, float))_addr(0x14097A520))(this, name, size);
}

void MKCharacter::GetBonePos(const char * name, FVector * pos)
{
	if (!(*(int64*)this + 568))
		return;
	FName fname(name, FNAME_Add, 1);
	((void(__fastcall*)(MKCharacter*, FName*, FVector*))_addr(0x1401DAC10))(this, &fname, pos);
}

void MKCharacter::GetBoneRot(const char * name, FRotator * rot)
{
	FName fname(name, FNAME_Add, 1);
	FMatrix mat;
	((void(__fastcall*)(MKCharacter*, FName*, FMatrix*))_addr(0x1401D9AF0))(this, &fname, &mat);
	mat.Rotator(rot);
}

void MKCharacter::ExecuteScript(MKScript* script, int function)
{
	((void(__thiscall*)(MKCharacter*, MKScript*, int, int))_addr(0x140206410))(this, script, function, 1);
}

