#pragma once
#include "unreal/FName.h"

class PlayerInfo {
public:
	void SetMeter(float value);
	void SetDamageMult(float value);
	const char* GetName();
};