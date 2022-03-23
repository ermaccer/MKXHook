#include "PlayerInfo.h"
#include "mk10utils.h"

void PlayerInfo::SetMeter(float value)
{
	((void(__fastcall*)(PlayerInfo*, float))_addr(0x14055EC40))(this, value);
}

void PlayerInfo::SetDamageMult(float value)
{
	*(float*)(this + 656) = value;
	*(float*)(this + 660) = value;
}

const char* PlayerInfo::GetName()
{
	return ((const char* (__fastcall*)(PlayerInfo*))_addr(0x140553FF0))(this);
}
