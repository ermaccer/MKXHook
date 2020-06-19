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
	bool bDisableComboDamageScaling;

	int iHookMenuOpenKey;
	int iAvailableDLCCells;

};

extern eSettingsManager* SettingsMgr;