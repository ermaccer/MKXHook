#include "mk10.h"
#include <vector>
#include <string>
#include "GameInfo.h"
#include "helper/eKeyboardMan.h"

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	CAMERA_HEAD_TRACKING,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	SUBMENU_SCRIPT,
	TOTAL_SUBMENUS
};

enum eScriptExecuteType {
	SCRIPT_P1,
	SCRIPT_P2,
	SCRIPT_GLOBAL
};

struct eScriptKeyBind {
	eScriptExecuteType type;
	eVKKeyCode key;
	char scriptName[128] = {};
	unsigned int functionHash;
};


class MK10Menu {
public:
	bool	 m_bIsActive = false;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool     m_bPressingKey = false;
	bool	 m_bSlowMotion = false;
	bool     m_bFreezeWorld = false;
	bool	 m_bIsFocused = true;
	bool	 m_bHookDispatch = false;
	bool	 m_bForceCameraUpdate = false;
	bool	 m_bCustomCameraPos = false;
	bool	 m_bCustomCameraRot = false;
	bool	 m_bCustomCameraFOV = false;
	bool	 m_bFreeCam = false;
	bool	 m_bCustomCameras = false;
	bool	 m_bYObtained = false;
	bool	 m_bStageModifier = false;
	bool	 m_bAutoHideHUD = false;
	bool	 m_bDontFlipCamera = false;
	bool	 m_bDisableHeadTracking = false;
	bool	 m_bUsePlayerTwoAsTracker = false;
	bool	 m_bMouseControl = false;

	// cheats
	bool m_bStopTimer = false;
	bool m_bInfiniteHealthP1 = false;
	bool m_bInfiniteHealthP2 = false;
	bool m_bInfiniteMeterP1 = false;
	bool m_bInfiniteMeterP2 = false;
	bool m_bNoHealthP1 = false;
	bool m_bNoHealthP2 = false;
	bool m_bOneHealthP1 = false;
	bool m_bOneHealthP2 = false;


	bool	m_bChangePlayerSpeed = false;
	bool	m_bChangePlayerScale = false;
	bool	m_bPlayer1Modifier = false;
	bool	m_bPlayer2Modifier = false;
	bool	m_bPlayer1CustomTrait = false;
	bool	m_bPlayer2CustomTrait = false;

	bool    m_bDisableComboScaling = false;

	float	 m_fSlowMotionSpeed = 0.5f;
	float	 m_fP1Speed = 1.0f;
	float	 m_fP2Speed = 1.0f;
	float	 m_fAdjustCam = 30.0f;
	float	 m_fFreeCameraSpeed = 5.25f;
	float	 m_fAdjustCustomHeadCameraX = 0.0f;
	float	 m_fAdjustCustomHeadCameraY = 800.0f;
	float	 m_fAdjustCustomHeadCameraZ = 0.0f;

	int  m_nFreeCameraRotationSpeed = 120;
	int  m_nCurrentCustomCamera = CAMERA_3RDPERSON;
	int  m_nCurrentCharModifier = 0;

	int* m_pCurrentVarToChange = nullptr;

	int  m_nScriptExecuteType = 0;
	unsigned int m_nHash = 0;
	MKScript* m_pScript;

	FVector	 m_vP1Scale = { 1.0f, 1.0f, 1.0f };
	FVector	 m_vP2Scale = { 1.0f, 1.0f, 1.0f };

	// camera
	FVector camPos;
	FRotator camRot;
	float camFov;

	FVector plrPos;
	FVector plrPos2;

	std::vector<eScriptKeyBind> m_vKeyBinds;

	char szStageModifierStage[128] = {};
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[128] = {};
	char szPlayer1Trait[128] = {};
	char szPlayer2Trait[128] = {};
	char szPlayer1Bone[128] = {};
	char szPlayer2Bone[128] = {};

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();
	void UpdateFreecam();

	void DrawCharacterTab();
	void DrawStageTab();
	void DrawVariationsTab();
	void DrawPlayerTab();
	void DrawSpeedTab();
	void DrawCameraTab();
	void DrawCheatsTab();
	void DrawMiscTab();
	void DrawScriptTab();


	void DrawSettings();

	void DrawScriptReference();

	void DrawKeyBind(char* name, int* var);
	void KeyBind(int* var, char* bindName, char* name);

	bool GetActiveState();

	void RunLastScript();

	void ProcessScriptHotkeys();
};

char* GetMKXHookVersion();
extern MK10Menu* TheMenu;
extern std::vector<std::string> P1Traits;
extern std::vector<std::string> P2Traits;