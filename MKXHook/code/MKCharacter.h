#pragma once
#include "MKStructs.h"
#include "unreal/FVector.h"

// wrapper for old functions
class MKCharacter {
public:
	void SetLife(float life);
	void SetScale(FVector* scale);
	void SetSpeed(float speed);
	void SetMeter(float value);

	void ActivateHeadTracking();
	void KillHeadTracking();

	void SetBoneSize(const char* name, float size);

	void GetBonePos(const char* name, FVector* pos);
	void GetBoneRot(const char* name, FRotator* rot);
};