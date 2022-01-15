#include "FName.h"
#include "..\mk10.h"

FName::FName(const char * Name, EFindName FindType, int formal)
{
	((void(__fastcall*)(FName*, const char*,EFindName, int))_addr(0x14150A6E0))(this, Name, FindType, formal);
}
