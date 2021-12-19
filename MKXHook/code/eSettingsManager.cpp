#include "eSettingsManager.h"
#include "..\IniReader.h"
#include <Windows.h>

eSettingsManager* SettingsMgr = new eSettingsManager();

void eSettingsManager::Init()
{
	CIniReader ini("");
	bEnableConsoleWindow = ini.ReadBoolean("Settings", "bEnableConsoleWindow", true);
	bDisableAssetHashChecking = ini.ReadBoolean("Settings", "bDisableAssetHashChecking", false);
	bEnableNPCFatalities =  ini.ReadBoolean("Settings", "bEnableNPCFatalities", false);
	bFixNPCGenderFatalityMessage = ini.ReadBoolean("Settings", "bFixNPCGenderFatalityMessage", false);
	bEnable60FPSFrontend = ini.ReadBoolean("Settings", "bEnable60FPSPatch", true);
	bDisableSweatEffects = ini.ReadBoolean("Settings", "bDisableSweatEffects", false);
	bEnableGamepadSupport = ini.ReadBoolean("Settings", "bEnableGamepadSupport", true);
	iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);


	iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);
	iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);


	iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);
	iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);
	iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);


	iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);
	iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);

	iFreeCameraKeyRollPlus = ini.ReadInteger("Settings", "iFreeCameraKeyRollPlus", 0);
	iFreeCameraKeyRollMinus = ini.ReadInteger("Settings", "iFreeCameraKeyRollMinus", 0);

	iFreeCameraKeyPitchPlus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchPlus", 0);
	iFreeCameraKeyPitchMinus = ini.ReadInteger("Settings", "iFreeCameraKeyPitchMinus", 0);

	iFreeCameraKeyFOVPlus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVPlus", 0);
	iFreeCameraKeyFOVMinus = ini.ReadInteger("Settings", "iFreeCameraKeyFOVMinus", 0);


	bDisableComboDamageScaling = ini.ReadBoolean("Settings", "bDisableComboDamageScaling", false);
	bEnableNPCVictoryPoses = ini.ReadBoolean("Settings", "bEnableNPCVictoryPoses", false);

	CIniReader user("mkxhook_user.ini");
	fMenuScale = user.ReadFloat("MenuSettings", "fMenuScale", 1.0f);

	if (fMenuScale < 1.0f)
		fMenuScale = 1.0f;

}

void eSettingsManager::SaveSettings()
{
	CIniReader user("mkxhook_user.ini");
	user.WriteFloat("MenuSettings", "fMenuScale", fMenuScale);

	CIniReader ini("");
	ini.WriteBoolean("Settings", "bEnableGamepadSupport", bEnableGamepadSupport);
	ini.WriteBoolean("Settings", "bEnableConsoleWindow", bEnableConsoleWindow);
	ini.WriteBoolean("Settings", "bDisableComboDamageScaling", bDisableComboDamageScaling);
	ini.WriteBoolean("Settings", "bDisableAssetHashChecking", bDisableAssetHashChecking);
	ini.WriteBoolean("Settings", "bDisableSweatEffects", bDisableSweatEffects);
	ini.WriteBoolean("Settings", "bEnable60FPSPatch", bEnable60FPSFrontend);
	ini.WriteBoolean("Settings", "bFixNPCGenderFatalityMessage", bFixNPCGenderFatalityMessage);
	ini.WriteBoolean("Settings", "bEnableNPCVictoryPoses", bEnableNPCVictoryPoses);
	ini.WriteBoolean("Settings", "bEnableNPCFatalities", bEnableNPCFatalities);

}
