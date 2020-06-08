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
	bEnable60FPSFrontend = ini.ReadBoolean("Settings", "bEnable60FPSFrontend", false);

	iHookMenuOpenKey = ini.ReadInteger("Settings", "iHookMenuOpenKey", VK_F1);
}
