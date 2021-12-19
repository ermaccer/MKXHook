#include "MKCharacter.h"
#include "mk10utils.h"
#include "mk10.h"

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

bool MKCharacter::IsCrouching()
{
	return ((bool(__fastcall*)(MKCharacter*))_addr(0x1401BBDB0))(this);
}
