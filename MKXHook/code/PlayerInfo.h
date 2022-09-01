#pragma once
#include "unreal/FName.h"

class AIDrone {
public:
	void Set(const char* script);
};

class PlayerInfo {
public:
	void SetMeter(float value);
	void SetDamageMult(float value);
	void SetEnergy(float value);
	const char* GetName();

	AIDrone* GetDrone();
};