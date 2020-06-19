
enum eTabs {
	TAB_CHARACTER_MODIFIER,
	TAB_STAGE_MODIFIER,
	TAB_MISC,
	// TODO: infinite health, powerbar etc
	TAB_CHEATS

};

// as usual, based on mh2 debug menu

class MK10Menu {
private:
	bool bIsActive;
	int  iCurrentTab;
public:
	bool bPlayer1ModifierEnabled;
	bool bPlayer2ModifierEnabled;
	bool bInfiniteEasyFatalities;
	bool bInfiniteSkipFights;
	bool bInfiniteHealthPlayer1;
	bool bInfiniteHealthPlayer2;
	bool bInfiniteSuperBarPlayer1;
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