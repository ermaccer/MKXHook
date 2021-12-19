#include "code/eSettingsManager.h"
#include "eDirectX11Hook.h"

#include "pch.h"
#include "utils/MemoryMgr.h"
#include "utils/Trampoline.h"
#include "code/mk10.h"
#include "code/mk10utils.h"
#include "code/mk10menu.h"
#include "code/eNotifManager.h"
#include "code/MKCamera.h"
#include "code/eGamepadManager.h"

#include <iostream>


using namespace Memory::VP;



int64 __fastcall GenericTrueReturn() { return 1; }
int64 __fastcall GenericFalseReturn() { return 0; }
void __fastcall  GenericDummy() {}


bool __fastcall SetFlagNull() 
{
	bool result = 0;

	if (((bool(__fastcall*)())_addr(0x1400100E0))())
		result = 0;
	else
	{
		Patch<int>(_addr(0x143212E54), 0);
		Patch<int>(_addr(0x143212E68), 0);
	}
	return result;

}


bool ValidateGameVersion()
{
	const char* gameName = GetGameName();

	if (strcmp(gameName, "MK10") == 0)
		return true;
	else
	{
		MessageBoxA(0, "Invalid game version!\nMKXHook only supports latest Steam executable.\n\n"
			"If you still cannot run the plugin and made sure that the game is updated, MKXHook needs to be updated.", 0, MB_ICONINFORMATION);
		return false;
	}
}


void OnInitializeHook()
{
	SettingsMgr->Init();

	if (SettingsMgr->bEnableConsoleWindow)
	{
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		freopen("CONIN$", "r", stdin);
	}

	if (SettingsMgr->bDisableAssetHashChecking)
		printf("NOTE: With disabled hash checking you won't be able to play online\n nor use Faction Wars (private rooms still work though)\n");

	printf("MKXHook::OnInitializeHook() | Begin!\n");
	printf("MKXHook::OnInitializeHook() | Game detected: %s\n", GetGameName());
	TheMenu->Initialize();
	Notifications->Init();
	Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
	InjectHook(_addr(0x1404A172D), tramp->Jump(MK10Hooks::HookProcessStuff));
	InjectHook(_addr(0x14049D139), tramp->Jump(MK10Hooks::HookStartupFightRecording));


	if (SettingsMgr->bEnable60FPSFrontend)
		InjectHook(_addr(0x14002B250), tramp->Jump(SetFlagNull), PATCH_JUMP);


	if (SettingsMgr->bDisableAssetHashChecking)
		InjectHook(_addr(0x14002BF69), tramp->Jump(GenericFalseReturn));

	if (SettingsMgr->bEnableNPCFatalities)
	{
		InjectHook(_addr(0x140058F03), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(_addr(0x1402A0977), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
		InjectHook(_addr(0x14045121A), tramp->Jump(MK10Hooks::HookCheckFatalityStatus));
	}

	if (SettingsMgr->bFixNPCGenderFatalityMessage)
	{
		InjectHook(_addr(0x14008C37E), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
		InjectHook(_addr(0x1401E7FEC), tramp->Jump(MK10Hooks::HookCheckIfCharacterFemale));
	}

	if (SettingsMgr->bDisableSweatEffects)
	{
		InjectHook(_addr(0x140085ABB), tramp->Jump(GenericDummy));
		InjectHook(_addr(0x140208230), tramp->Jump(GenericDummy), PATCH_JUMP);
		InjectHook(_addr(0x1402082B0), tramp->Jump(GenericDummy), PATCH_JUMP);
	}

	if (SettingsMgr->bDisableComboDamageScaling)
	{
		InjectHook(_addr(0x1400579EB), tramp->Jump(MK10Hooks::HookDamageMultiplier));
		InjectHook(_addr(0x1401C27DC), tramp->Jump(MK10Hooks::HookDamageMultiplier));
		InjectHook(_addr(0x14037791F), tramp->Jump(MK10Hooks::HookDamageMultiplier));
		InjectHook(_addr(0x14043E5D7), tramp->Jump(MK10Hooks::HookDamageMultiplier));
		InjectHook(_addr(0x14054B82B), tramp->Jump(MK10Hooks::HookDamageMultiplier));

		InjectHook(_addr(0x14005AD7B), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));
		InjectHook(_addr(0x1401E70C8), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));
		InjectHook(_addr(0x140203ADA), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));
		InjectHook(_addr(0x1402040BC), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));
		InjectHook(_addr(0x14043E5E7), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));
		InjectHook(_addr(0x140440BE3), tramp->Jump(MK10Hooks::HookDamageMultiplierTwo));

		InjectHook(_addr(0x1400561AB), tramp->Jump(MK10Hooks::HookDamageMultiplierThree));
		InjectHook(_addr(0x14043347F), tramp->Jump(MK10Hooks::HookDamageMultiplierThree));
		InjectHook(_addr(0x1404334FF), tramp->Jump(MK10Hooks::HookDamageMultiplierThree));

	}

	InjectHook(_addr(0x14135B5FB), tramp->Jump(&MKCamera::HookedSetPosition));
	InjectHook(_addr(0x14135B608), tramp->Jump(&MKCamera::HookedSetRotation));

	InjectHook(_addr(0x140029E7F), tramp->Jump(MK10Hooks::HookDispatch));

	if (SettingsMgr->bEnableNPCVictoryPoses)
		InjectHook(_addr(0x1405543B6), tramp->Jump(MK10Hooks::HookGetCharacterVictory));

	//gamepad
	if (SettingsMgr->bEnableGamepadSupport)
		InjectHook(_addr(0x14216922E), tramp->Jump(XInputGetState_Hook), PATCH_JUMP);
}



BOOL WINAPI DllMain(HMODULE hMod, DWORD dwReason, LPVOID lpReserved)
{
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:

		if (ValidateGameVersion())
		{
#ifdef _60_ONLY
			Trampoline* tramp = Trampoline::MakeTrampoline(GetModuleHandle(nullptr));
			InjectHook(_addr(0x14002B250), tramp->Jump(SetFlagNull), PATCH_JUMP);
#else
			SettingsMgr->Init();
			OnInitializeHook();
			eDirectX11Hook::Init();
			DisableThreadLibraryCalls(hMod);
			CreateThread(nullptr, 0, DirectXHookThread, hMod, 0, nullptr);

#endif	
		}

		break;
	case DLL_PROCESS_DETACH:
		kiero::shutdown();
		break;
	}
	return TRUE;
}