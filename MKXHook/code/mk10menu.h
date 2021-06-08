#include "mk10.h"
#include <vector>
#include <string>

enum eTabs {
	TAB_CHARACTER_MODIFIER,
	TAB_STAGE_MODIFIER,
	TAB_CAMERA,
	TAB_PLAYER_CONTROL,
	TAB_MISC,
	TAB_CHEATS
};

enum eCustomCameras {
	CAMERA_3RDPERSON,
	CAMERA_3RDPERSON2,
	CAMERA_1STPERSON,
	CAMERA_1STPERSON_MID,
	TOTAL_CUSTOM_CAMERAS
};


// as usual, based on mh2 debug menu

class MK10Menu {
private:
	int  iCurrentTab;
public:
	bool bIsActive;

	bool	 bSlowMotionEnabled;
	float	 fSlowMotionSpeed;

	bool bFocused;
	// characters
	bool bPlayer1ModifierEnabled;
	bool bPlayer1TraitEnabled;
	int  iPlayer1Trait;
	bool bPlayer2ModifierEnabled;
	bool bPlayer2TraitEnabled;
	int  iPlayer2Trait;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};

	char szPlayer1Trait[128] = {};
	char szPlayer2Trait[128] = {};

	bool bCustomTraitsP1;
	bool bCustomTraitsP2;

	bool bCustomTraitAppendP1;
	bool bCustomTraitAppendP2;

	bool bChangePlayerSpeed;
	float fPlayer1Speed;
	float fPlayer2Speed;


	// cheats
	bool bStopTimer;
	bool bInfiniteHealthPlayer1;
	bool bInfiniteSuperBarPlayer1;
	bool b0HealthPlayer1;
	bool b1HealthPlayer1;

	bool bInfiniteHealthPlayer2;
	bool bInfiniteSuperBarPlayer2;
	bool b0HealthPlayer2;
	bool b1HealthPlayer2;


	// camera
	bool bCustomCamera;
	bool bCustomFOV;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	float camFov;


	bool bFreeCameraMovement;
	float fFreeCameraSpeed;
	int  iFreeCameraRotSpeed;
	bool bEnableCustomCameras;
	int  iCurrentCustomCamera;
	char szCurrentCameraOption[128];
	bool bYObtained;

	float fAdjustCam;

	// player 
	bool bFreezePosition;
	FVector plrPos;
	FVector plrPos2;


	bool bChangePlayerScale;
	FVector fPlayer1Scale;
	FVector fPlayer2Scale;

	// stage
	bool bStageModifier;
	char szStageModifierStage[128] = {};

	
	bool bEnableRandomFights;
	bool bFreezeWorld;


	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();
	bool GetActiveState();
};

char* GetMKXHookVersion();
extern MK10Menu* TheMenu;
extern std::vector<std::string> P1Traits;
extern std::vector<std::string> P2Traits;