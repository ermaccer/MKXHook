#pragma once
#include "MKStructs.h"

// wrapper for old functions
class MKCharacter {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetMeter(float value);

	bool IsCrouching();
};