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
	bEnable60FPSFrontend = ini.ReadBoolean("Settings", "bEnable60FPSPatch", false);
	bDisableSweatEffects = ini.ReadBoolean("Settings", "bDisableSweatEffects", false);

	iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);
	iAvailableDLCCells = ini.ReadInteger("Settings", "iAvailableDLCCells", -1);

	iFreeCameraKeyXPlus = ini.ReadInteger("Settings", "iFreeCameraKeyXPlus", 0);
	iFreeCameraKeyXMinus = ini.ReadInteger("Settings", "iFreeCameraKeyXMinus", 0);


	iFreeCameraKeyYPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYPlus", 0);
	iFreeCameraKeyYMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYMinus", 0);

	iFreeCameraKeyZPlus = ini.ReadInteger("Settings", "iFreeCameraKeyZPlus", 0);
	iFreeCameraKeyZMinus = ini.ReadInteger("Settings", "iFreeCameraKeyZMinus", 0);


	iFreeCameraKeyYawPlus = ini.ReadInteger("Settings", "iFreeCameraKeyYawPlus", 0);
	iFreeCameraKeyYawMinus = ini.ReadInteger("Settings", "iFreeCameraKeyYawMinus", 0);
	bDisableComboDamageScaling = ini.ReadBoolean("Settings", "bDisableComboDamageScaling", false);
	bEnableNPCVictoryPoses = ini.ReadBoolean("Settings", "bEnableNPCVictoryPoses", false);
}
