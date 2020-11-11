// mkxhook
// 08-06-2020 | Updated to latest Steam patch
// 10-08-2020 | Updated to latest Steam patch
// 11-11-2020 | Updated to latest Steam patch
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

bool __fastcall SetFlagNull() 
{
	bool result = 0;

	if (((bool(__fastcall*)())GetMKXAddr(0x1400100E0))())
		result = 0;
	else
	{
		Patch<int>(GetMKXAddr(0x143212E54), 0);
		Patch<int>(GetMKXAddr(0x143212E68), 0);
	}
	return result;

}


const char* __fastcall SwapGameName()
{
	return "MK10 | MKXHook";
}



void OnInitializeHook()
{
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(GetMKXAddr(0x1404A172D), tramp->Jump(MK10Hooks::HookProcessStuff));
	InjectHook(GetMKXAddr(0x141374E58), tramp->Jump(SwapGameName));
	InjectHook(GetMKXAddr(0x14049D139), tramp->Jump(MK10Hooks::HookStartupFightRecording));
	//Patch<int>(GetMKXAddr(0x14047CD30 + 6), 0);
	//Patch<int>(GetMKXAddr(0x14047CDE0 + 6), 0);
	if (SettingsMgr->bEnable60FPSFrontend)
	{
		InjectHook(GetMKXAddr(0x14002B250), tramp->Jump(SetFlagNull),PATCH_JUMP);

	}


	if (!(SettingsMgr->iAvailableDLCCells == -1))
	{
		InjectHook(GetMKXAddr(0x1400579A9), tramp->Jump(MK10Hooks::HookDLCCellAmount));
		Patch<int>(GetMKXAddr(0x14069F902 + 1), SettingsMgr->iAvailableDLCCells);
	}

	if (SettingsMgr->bDisableAssetHashChecking)
		InjectHook(GetMKXAddr(0x14002BF69), tramp->Jump(GenericFalseReturn));
	
	if (SettingsMgr->bEnableNPCFatalities)
	{
		InjectHook(GetMKXAddr(0x140058F03), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(GetMKXAddr(0x1402A0977), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(GetMKXAddr(0x14045121A), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
	}

	if (SettingsMgr->bFixNPCGenderFatalityMessage)
	{
		InjectHook(GetMKXAddr(0x14008C37E), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
		InjectHook(GetMKXAddr(0x1401E7FEC), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
	}

	if (SettingsMgr->bDisableSweatEffects)
	{
		InjectHook(GetMKXAddr(0x140085ABB), tramp->Jump(GenericDummy));
		InjectHook(GetMKXAddr(0x140208230), tramp->Jump(GenericDummy), PATCH_JUMP);
		InjectHook(GetMKXAddr(0x1402082B0), tramp->Jump(GenericDummy), PATCH_JUMP);
	}

	InjectHook(GetMKXAddr(0x1400A171A), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14016F579), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017C81D), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017C88D), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017D330), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017D3B4), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14018EE52), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14018EF1C), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x140191382), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1402D6993), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1402EB663), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1403079AB), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14030827B), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14030ADBA), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14058D170), tramp->Jump(MK10Hooks::HookCamSetRot));


	InjectHook(GetMKXAddr(0x14009FB7A), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017C810), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017C880), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017D321), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017D3A5), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14018EE47), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14018EF28), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x1402D6984), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x1402EB656), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030799F), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030826F), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030ADF3), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14058D161), tramp->Jump(MK10Hooks::HookCamSetPos));


}