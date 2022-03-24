#include "GameInfo.h"
#include "mk10.h"
int MKScript::GetFunctionID(int hash)
{
	return ((int(__thiscall*)(MKScript*, int, int))_addr(0x140CAB310))(this, hash, 0);
}

void FGGameInfo::SetStage(const char* stage)
{
	((void(__thiscall*)(FGGameInfo*, const char*))_addr(0x14049C360))(this, stage);
}

void FGGameInfo::ResetStageInteractables()
{
	int64 bgnd_info = *(int64*)(this + 0x58);

	((void(__fastcall*)(int64))_addr(0x1401851C0))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x1401852B0))(bgnd_info);
	((void(__fastcall*)(int64))_addr(0x140184EF0))(bgnd_info);
}

PlayerInfo* FGGameInfo::GetInfo(PLAYER_NUM plr)
{
	return ((PlayerInfo * (__fastcall*)(FGGameInfo*, PLAYER_NUM))_addr(0x140485F80))(this, plr);
}

MKScript* GetScript(const char* name)
{
	int64 package = ((int64(__fastcall*)(const char*))_addr(0x14033FE90))("MainlineManaged.SystemPackages.FightingArt");
	if (package)
	{
		MKScript* script = ((MKScript * (__fastcall*)(int64, const char*, int))_addr(0x14094EA10))(package, name, 1);
		return script;
	}
	return nullptr;
}

void RunScriptFunction(const char* name, unsigned int funcID)
{
	((void(__fastcall*)(const char*, unsigned int))_addr(0x14047DB80))(name, funcID);
}

FGGameInfo* GetGameInfo()
{
	return *(FGGameInfo**)_addr(GFG_GAME_INFO);
}
