#pragma once
#include "..\mk10.h"

struct FMatrix
{
	float M[4][4];

	FMatrix();
	void Rotator(FRotator* dest);
};
