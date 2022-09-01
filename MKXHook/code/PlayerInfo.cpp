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

void PlayerInfo::SetEnergy(float value)
{
	((void(__fastcall*)(PlayerInfo*, float))_addr(0x14055DC50))(this, value);
}

const char* PlayerInfo::GetName()
{
	return ((const char* (__fastcall*)(PlayerInfo*))_addr(0x140553FF0))(this);
}

AIDrone* PlayerInfo::GetDrone()
{
	return	((AIDrone * (__fastcall*)(PlayerInfo*))_addr(0x140552530))(this);
}

void AIDrone::Set(const char* script)
{
	((void(__fastcall*)(AIDrone*, const char*))_addr(0x140140430))(this, script);
}
