#include "mk10.h"

enum eTabs {
	TAB_CHARACTER_MODIFIER,
	TAB_STAGE_MODIFIER,
	TAB_MISC,
	TAB_CHEATS,
	TAB_CAMERA


};

// as usual, based on mh2 debug menu

class MK10Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool bPlayer1ModifierEnabled;
	bool bPlayer1TraitEnabled;
	int  iPlayer1Trait;
	bool bPlayer2ModifierEnabled;
	bool bPlayer2TraitEnabled;
	int  iPlayer2Trait;
	bool bInfiniteEasyFatalities;
	bool bInfiniteSkipFights;

	bool bStopTimer;

	bool bInfiniteHealthPlayer1;
	bool bInfiniteSuperBarPlayer1;



	bool bCustomCamera;
	bool bCustomCameraRot;
	FVector camPos;
	FRotator camRot;
	bool bFreeCameraMovement;
	float fFreeCameraSpeed;
	int  iFreeCameraRotSpeed;
	bool bInfiniteHealthPlayer2;
	bool bInfiniteSuperBarPlayer2;
	
	bool bEnableRandomFights;

	char szPlayer1ModifierCharacter[128] = {};
	char szPlayer2ModifierCharacter[128] = {};
	int  iSlowMotionTicks;
	float fSlowMotionSpeed;
	void Initialize();
	void Process();
	void Draw();
	void UpdateControls();
	bool GetActiveState();
};



extern MK10Menu* TheMenu;

void PushErrorMessage(const char* message);