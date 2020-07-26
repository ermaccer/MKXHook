// mkxhook
// 08-06-2020 | Updated to latest Steam patch
#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "utils/Patterns.h"
#include "code/mk10.h"
#include "code/mk10utils.h"
#include "code/mk10menu.h"
#include "code/eSettingsManager.h"
#include <iostream>


using namespace Memory::VP;
using namespace hook;


int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}


const char* __fastcall SwapGameName()
{
	return "MK10 | MKXHook";
}


void OnInitializeHook()
{

	if (SettingsMgr->bEnable60FPSFrontend)
	{
		Patch<char>(GetMKXAddr(0x1404950E6 + 1), 0);
		Patch<char>(GetMKXAddr(0x1404950F7 + 1), 0);
		Patch<char>(GetMKXAddr(0x142639FE4), '6');
		Patch<char>(GetMKXAddr(0x1428C6580), '6');
		Patch<char>(GetMKXAddr(0x140E8F4CB + 2), 1);
		Patch<char>(GetMKXAddr(0x140F7DE89 + 2), 1);
	}

	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(GetMKXAddr(0x14049C5DD), tramp->Jump(MK10Hooks::HookProcessStuff));
	InjectHook(GetMKXAddr(0x1413708D8), tramp->Jump(SwapGameName));
	InjectHook(GetMKXAddr(0x140497FE9), tramp->Jump(MK10Hooks::HookStartupFightRecording));

	if (!(SettingsMgr->iAvailableDLCCells == -1))
	{
		InjectHook(GetMKXAddr(0x14004BAB9), tramp->Jump(MK10Hooks::HookDLCCellAmount));
		Patch<int>(GetMKXAddr(0x14069A662 + 1), SettingsMgr->iAvailableDLCCells);
	}

	if (SettingsMgr->bDisableAssetHashChecking)
		InjectHook(GetMKXAddr(0x14002BF69), tramp->Jump(GenericFalseReturn));
	
	if (SettingsMgr->bEnableNPCFatalities)
	{
		InjectHook(GetMKXAddr(0x14004E303), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(GetMKXAddr(0x1402A0767), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(GetMKXAddr(0x14044C0CA), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
	}

	if (SettingsMgr->bFixNPCGenderFatalityMessage)
	{
		InjectHook(GetMKXAddr(0x14008194E), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
		InjectHook(GetMKXAddr(0x1401E7E0C), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
	}
	InjectHook(GetMKXAddr(0x14018ED48), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14018ED3C), tramp->Jump(MK10Hooks::HookCamSetRot));
	//Nop(GetMKXAddr(0x140862E61), 5);

}