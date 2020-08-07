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
	// free camera keys
	int iFreeCameraKeyXPlus;
	int iFreeCameraKeyXMinus;
	int iFreeCameraKeyYPlus;
	int iFreeCameraKeyYMinus;
	int iFreeCameraKeyYawPlus;
	int iFreeCameraKeyYawMinus;
	int iFreeCameraKeyZPlus;
	int iFreeCameraKeyZMinus;
	int iAvailableDLCCells;


};

extern eSettingsManager* SettingsMgr;