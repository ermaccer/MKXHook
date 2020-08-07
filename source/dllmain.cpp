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

bool __fastcall SetFlagNull() 
{
	bool result = 0;

	if (((bool(__fastcall*)())GetMKXAddr(0x1400100E0))())
		result = 0;
	else
	{
		Patch<int>(GetMKXAddr(0x14320BDD4), 0);
		Patch<int>(GetMKXAddr(0x14320BDE8), 0);
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
	InjectHook(GetMKXAddr(0x14049C5DD), tramp->Jump(MK10Hooks::HookProcessStuff));
	InjectHook(GetMKXAddr(0x1413708D8), tramp->Jump(SwapGameName));
	InjectHook(GetMKXAddr(0x140497FE9), tramp->Jump(MK10Hooks::HookStartupFightRecording));

	if (SettingsMgr->bEnable60FPSFrontend)
	{
		Patch<char>(GetMKXAddr(0x1404950E6 + 1), 0);
		Patch<char>(GetMKXAddr(0x1404950F7 + 1), 0);
		Patch<char>(GetMKXAddr(0x142639FE4), '6');
		Patch<char>(GetMKXAddr(0x1428C6580), '6');
		Patch<char>(GetMKXAddr(0x140E8F4CB + 2), 1);
		Patch<char>(GetMKXAddr(0x140F7DE89 + 2), 1);

		InjectHook(GetMKXAddr(0x14002B250), tramp->Jump(SetFlagNull),PATCH_JUMP);

	}


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

	InjectHook(GetMKXAddr(0x14017C630), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14009523A), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017C6A0), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017D141), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14017D1C5), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14018EC67), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x1402D6774), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x1402EB446), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030778F), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030805F), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030ABE3), tramp->Jump(MK10Hooks::HookCamSetPos));
	InjectHook(GetMKXAddr(0x14030ABE3), tramp->Jump(MK10Hooks::HookCamSetPos));

	InjectHook(GetMKXAddr(0x140096C0A), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14016F399), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017C63D), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017C6AD), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017D150), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14017D1D4), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14018EC72), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1401911A2), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1402D6783), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x1402EB453), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14030779B), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14030806B), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x14030ABAA), tramp->Jump(MK10Hooks::HookCamSetRot));
	InjectHook(GetMKXAddr(0x140588020), tramp->Jump(MK10Hooks::HookCamSetRot));


}