#pragma once
#include "mk10.h"
#include "unreal/FMatrix.h"
// generic layer for other plugins too
class MKCamera {
public:
	void SetPosition(FVector* pos);
	void SetRotation(FRotator* rot);
	void SetFOV(float FOV);
	float GetFOV();

	void HookedSetPosition(FVector* pos);
	void HookedSetRotation(FRotator* rot);

	FMatrix GetMatrix();
};

extern MKCamera* TheCamera;