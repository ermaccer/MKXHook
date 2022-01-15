#include "FMatrix.h"

FMatrix::FMatrix()
{
}

void FMatrix::Rotator(FRotator * dest)
{
	((void(__fastcall*)(FMatrix*, FRotator* ))_addr(0x1415E0640))(this, dest);
}
