#include "mk10.h"
#include <vector>
#include <string>

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	TOTAL_CUSTOM_CAMERAS
};

enum eMenuSubMenus {
	SUBMENU_SETTINGS,
	TOTAL_SUBMENUS
};


// as usual, based on mh2 debug menu

class MK10Menu {
public:
	bool	 m_bIsActive;
	bool	 m_bSubmenuActive[TOTAL_SUBMENUS] = {};
	bool	 m_bSlowMotion;
	bool     m_bFreezeWorld;
	bool	 m_bIsFocused;
	bool	 m_bHookDispatch;
	bool	 m_bForceCameraUpdate;
	bool	 m_bCustomCameraPos;
	bool	 m_bCustomCameraRot;
	bool	 m_bCustomCameraFOV;
	bool	 m_bFreeCam;
	bool	 m_bCustomCameras;
	bool	 m_bYObtained;
	bool	 m_bStageModifier;
	bool	 m_bAutoHideHUD;
	// cheats
	bool m_bStopTimer;
	bool m_bInfiniteHealthP1;
	bool m_bInfiniteHealthP2;
	bool m_bInfiniteMeterP1;
	bool m_bInfiniteMeterP2;
	bool m_bNoHealthP1;
	bool m_bNoHealthP2;
	bool m_bOneHealthP1;
	bool m_bOneHealthP2;


	bool	m_bChangePlayerSpeed;
	bool	m_bChangePlayerScale;
	bool	m_bPlayer1Modifier;
	bool	m_bPlayer2Modifier;
	bool	m_bPlayer1CustomTrait;
	bool	m_bPlayer2CustomTrait;

	float	 m_fSlowMotionSpeed;
	float	 m_fP1Speed;
	float	 m_fP2Speed;
	float	 m_fAdjustCam;
	float	 m_fFreeCameraSpeed;

	int  m_nFreeCameraRotationSpeed;
	int  m_nCurrentCustomCamera;
	int  m_nCurrentCharModifier;


	FVector	 m_vP1Scale;
	FVector	 m_vP2Scale;

	// camera
	FVector camPos;
	FRotator camRot;
	float camFov;

	FVector plrPos;
	FVector plrPos2;

	char szStageModifierStage[128] = {};
	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	char szCurrentCameraOption[128] = {};
	char szPlayer1Trait[128] = {};
	char szPlayer2Trait[128] = {};

	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();


	void DrawSettings();

	bool GetActiveState();
};

char* GetMKXHookVersion();
extern MK10Menu* TheMenu;
extern std::vector<std::string> P1Traits;
extern std::vector<std::string> P2Traits;