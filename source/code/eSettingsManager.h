#pragma once


// as usual, pluginmh/mugenhook

class eSettingsManager {
public:
	void Init();

	bool bEnable60FPSFrontend;
	bool bFixNPCGenderFatalityMessage;
	bool bEnableNPCFatalities;
	bool bDisableAssetHashChecking;
	bool bEnableConsoleWindow;

	int iHookMenuOpenKey;

};

extern eSettingsManager* SettingsMgr;