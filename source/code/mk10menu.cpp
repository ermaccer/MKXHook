#include "mk10menu.h"
#include "mk10.h"
#include "mk10utils.h"
#include <iostream>
#include <Windows.h>
#include <imgui.h>
#include "eSettingsManager.h"

bool bShowMessageError = 0;

// TODO: replace with auto scan?
const char* szCharacters[] = {
	// place npcs first for easy access
	"Rain_A",
	"Baraka_A",
	"Sindel_A",
	"Tanya_A",
	"ShinnokBoss_A",
	// rest of the cast
	"CHAR_Alien_A",
	"char_aztec_a", "CHAR_Aztec_B", "CHAR_Aztec_E",
	"CHAR_BoRaiChoDLC_A",
	"char_cagejr_a", "CHAR_CageJr_B", "CHAR_CageJr_N", "CHAR_CageJr_O",
	"CHAR_Ermac_A", "CHAR_Ermac_B","CHAR_Ermac_H","CHAR_Ermac_N","CHAR_Ermac_V",
	"Char_Goro_A",
	"CHAR_Jason_A",
	"CHAR_JaxJr_A", "CHAR_JaxJr_B","CHAR_JaxJr_N","CHAR_JaxJr_O",
	"CHAR_Jax_A", "CHAR_Jax_B", "CHAR_Jax_C", "CHAR_Jax_M", "CHAR_Jax_P", "CHAR_Jax_Y",
	"CHAR_JohnnyCage_A", "CHAR_JohnnyCage_B","CHAR_JohnnyCage_C","CHAR_JohnnyCage_M", "CHAR_JohnnyCage_P","CHAR_JohnnyCage_Z",
	"CHAR_Kano_A","CHAR_Kano_B","CHAR_Kano_K","CHAR_Kano_T",
	"CHAR_KenshiJr_A","CHAR_KenshiJr_B","CHAR_KenshiJr_L",
	"CHAR_Kenshi_A","CHAR_Kenshi_B","CHAR_Kenshi_F",
	"CHAR_Kitana_A","CHAR_Kitana_B","CHAR_Kitana_C","CHAR_Kitana_E","CHAR_Kitana_F","CHAR_Kitana_M",
	"CHAR_KungLaoJr_A","CHAR_KungLaoJr_B","CHAR_KungLaoJr_E",
	"CHAR_KungLao_A","CHAR_KungLao_B","CHAR_KungLao_C","CHAR_KungLao_Y","CHAR_KungLao_Z",
	"char_ladybug_a","CHAR_LadyBug_B","char_ladybug_L",
	"CHAR_LeatherFace_A","CHAR_LeatherFace_B","CHAR_LeatherFace_C",
	"CHAR_LiuKang_A","CHAR_LiuKang_B","CHAR_LiuKang_C","CHAR_LiuKang_E","CHAR_LiuKang_T","CHAR_LiuKang_Z",
	"CHAR_MasterMale_A","CHAR_MasterMale_B","CHAR_MasterMale_E",
	"CHAR_Mileena_A","CHAR_Mileena_B","CHAR_Mileena_C","CHAR_Mileena_H","CHAR_Mileena_M",
	"CHAR_Nomad_A","CHAR_Nomad_B","CHAR_Nomad_L",
	"CHAR_Predator_A",
	"CHAR_QuanChi_A","CHAR_QuanChi_B","CHAR_QuanChi_Y",
	"CHAR_Raiden_A","CHAR_Raiden_B","CHAR_Raiden_C","CHAR_Raiden_I",
	"CHAR_Reptile_A","CHAR_Reptile_B","CHAR_Reptile_H","CHAR_Reptile_N",
	"char_scorpion_a","CHAR_Scorpion_B","CHAR_Scorpion_C","CHAR_Scorpion_J","CHAR_Scorpion_M","CHAR_Scorpion_N","CHAR_Scorpion_P","CHAR_Scorpion_V",
	"CHAR_Shinnok_A","CHAR_Shinnok_B","CHAR_Shinnok_F",
	"CHAR_Sonya_A","CHAR_Sonya_B","CHAR_Sonya_C","CHAR_Sonya_K","CHAR_Sonya_T",
	"char_subzero_a","CHAR_SubZero_B","CHAR_SubZero_C","CHAR_SubZero_K","CHAR_SubZero_N","CHAR_SubZero_V",
	"CHAR_TanyaDLC_A",
	"CHAR_Tremor_A",
	"Char_Triborg_A",

};



const char* szStageNames[]{
   "BGND_AztecCourtyard",
   "BGND_CharacterTest",
   "BGND_CharacterViewer",
   "BGND_Cove",
   "BGND_Crossroads",
   "BGND_DestroyedCity",
   "BGND_DestroyedCityPast",
   "BGND_JinseiChamber",
   "BGND_JinseiChamberRed",
   "BGND_Jungle",
   "BGND_KR_IL_Tunnel",
   "BGND_KR_KahnTomb",
   "BGND_KR_SnowForest",
   "BGND_LinKueiTemple",
   "BGND_OWMarketplace",
   "BGND_Pit",
   "BGND_QuanChiFortress",
   "BGND_RefugeeCamp",
   "BGND_SkyTemple",
   "BGND_SkyTempleRed",
   "BGND_SnowForest",
   "BGND_SnowForestRed",
   "BGND_TYM_BlaDrag",
   "BGND_TYM_BroShad",
   "BGND_TYM_LinKuei",
   "BGND_TYM_SF",
   "BGND_TYM_SpeForc",
   "BGND_TYM_WhiLotu",
   "BGND_TrainingRoom",

};


const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid"
};

int GetCamMode(const char* mode)
{
	for (int i = 0; i < TOTAL_CUSTOM_CAMERAS; i++)
	{
		if (strcmp(mode, szCameraModes[i]) == 0)
		{
			return i;
			break;
		}
	}
	return -1;
}



static int64 timer = GetTickCount64();

MK10Menu* TheMenu = new MK10Menu();

static void ShowHelpMarker(const char* desc)
{
	ImGui::TextDisabled("(?)");
	if (ImGui::IsItemHovered())
	{
		ImGui::BeginTooltip();
		ImGui::PushTextWrapPos(ImGui::GetFontSize() * 35.0f);
		ImGui::TextUnformatted(desc);
		ImGui::PopTextWrapPos();
		ImGui::EndTooltip();
	}
}


void MK10Menu::Initialize()
{
	bIsActive = false;
	bPlayer1ModifierEnabled = false;
	bPlayer2ModifierEnabled = false;
	bInfiniteEasyFatalities = false;
	bInfiniteSkipFights = false;
	bInfiniteHealthPlayer1 = false;
	bInfiniteHealthPlayer2 = false;
	b0HealthPlayer1 = false;
	b0HealthPlayer2 = false;
	bInfiniteSuperBarPlayer1 = false;
	bInfiniteSuperBarPlayer2 = false;
	bPlayer1TraitEnabled = false;
	bPlayer2TraitEnabled = false;
	bEnableRandomFights = false;
	bFreezePosition = false;
	bEnableCustomCameras = false;
	iCurrentCustomCamera = -1;
	iPlayer1Trait = 1;
	iPlayer2Trait = 1;
	fFreeCameraSpeed = 5.25f;
	iFreeCameraRotSpeed = 120;
	bStopTimer = false;
	bYObtained = false;
	iCurrentTab = 0;
	bStageModifier = false;
	bChangePlayerSpeed = false;
	fPlayer1Speed = 1.0f;
	fPlayer2Speed = 1.0f;
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	iSlowMotionTicks = 0;
	fSlowMotionSpeed = 0.0f;
	fAdjustCam = 30.0f;
	bChangePlayerScale = false;
	fPlayer1Scale = { 1.0f,1.0f,1.0f };
	fPlayer2Scale = { 1.0f,1.0f,1.0f };
	bFreezeWorld = false;
	camFov = 0;
	bCustomFOV = false;
	printf("MKXHook::Initialize() | Menu initialize\n");
}

void MK10Menu::Process()
{
	UpdateControls();

	//if (bIsActive)
	////	ImGui::GetIO().MouseDrawCursor = true;
	//else
	//	ImGui::GetIO().MouseDrawCursor = false;
}

void MK10Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin("MKXHook by ermaccer (0.5.3)");
	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			ImGui::Checkbox("Enable Player 1 Modifier", &bPlayer1ModifierEnabled);
			ImGui::SameLine(); ShowHelpMarker("It does not matter who you choose at character select screen, character will be changed upon match start. Works in all game modes");
			ImGui::Checkbox("Enable Player 1 Variation Modifier", &bPlayer1TraitEnabled);


			if (ImGui::BeginCombo("Player 1 Character", szPlayer1ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer1ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer1ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::SliderInt("Variation", &iPlayer1Trait, 1, 3);
			ImGui::Separator();
			ImGui::Checkbox("Enable Player 2 Modifier", &bPlayer2ModifierEnabled);
			ImGui::SameLine(); ShowHelpMarker("NB: Make sure you do not replace Shinnok boss fight, it'll crash.");
			ImGui::Checkbox("Enable Player 2 Variation Modifier", &bPlayer2TraitEnabled);



			if (ImGui::BeginCombo("Player 2 Character", szPlayer2ModifierCharacter))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCharacters); n++)
				{
					bool is_selected = (szPlayer2ModifierCharacter == szCharacters[n]);
					if (ImGui::Selectable(szCharacters[n], is_selected))
						sprintf(szPlayer2ModifierCharacter, szCharacters[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();
				}
				ImGui::EndCombo();
			}
			ImGui::SliderInt("Variation ", &iPlayer2Trait, 1, 3);
			ImGui::Separator();
			ImGui::Checkbox("Enable Random Fights", &bEnableRandomFights);
			ImGui::SameLine(); ShowHelpMarker("This will randomize P1 character each fight, Costumes are not available as they would pad list too much");


			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{
			bool reset = ImGui::Button("Reset Stage Objects");
			if (reset)
				MK10::ResetStageInteractables();

			ImGui::Checkbox("Enable Stage Modifier", &bStageModifier);

			if (ImGui::BeginCombo("Stage", szStageModifierStage))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
				{
					bool is_selected = (szStageModifierStage == szCameraModes[n]);
					if (ImGui::Selectable(szStageNames[n], is_selected))
						sprintf(szStageModifierStage, szStageNames[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			ImGui::Checkbox("Custom Camera Position", &bCustomCamera);
			ImGui::InputFloat3("X | Y | Z", &camPos.X);
			ImGui::Checkbox("Custom Camera Rotation", &bCustomCameraRot);
			ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);


			if (SettingsMgr->bGlobalCameraHook)
			{
				ImGui::Checkbox("Custom FOV", &bCustomFOV);
				ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
				ImGui::InputFloat("FOV", &camFov);
			}


			ImGui::Checkbox("Enable Freecam", &bFreeCameraMovement);
			ImGui::SameLine(); ShowHelpMarker("Requires both toggles enabled!\n You can configure keys in .ini file.");
			ImGui::InputFloat("Freecam Speed", &fFreeCameraSpeed);
			ImGui::InputInt("Freecam Rotation Speed", &iFreeCameraRotSpeed);


			ImGui::Separator();

			ImGui::Checkbox("Custom Cameras", &bEnableCustomCameras);

			if (ImGui::BeginCombo("Mode", szCurrentCameraOption))
			{
				for (int n = 0; n < IM_ARRAYSIZE(szCameraModes); n++)
				{
					bool is_selected = (szCurrentCameraOption == szCameraModes[n]);
					if (ImGui::Selectable(szCameraModes[n], is_selected))
						sprintf(szCurrentCameraOption, szCameraModes[n]);
					if (is_selected)
						ImGui::SetItemDefaultFocus();

				}
				ImGui::EndCombo();
			}
			iCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
			ImGui::InputFloat("FPS Camera Offset", &fAdjustCam);

			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
		{
			ImGui::Checkbox("Change Player Speed", &bChangePlayerSpeed);
			ImGui::SliderFloat("Player 1", &fPlayer1Speed, 0.0, 10.0f);
			ImGui::SliderFloat("Player 2", &fPlayer2Speed, 0.0, 10.0f);

			bool reset = ImGui::Button("Reset Speed");
			if (reset)
			{
				fPlayer1Speed = 1.0f;
				fPlayer2Speed = 1.0f;
			}
			ImGui::Separator();
			ImGui::Checkbox("Change Player Scale", &bChangePlayerScale);
			ImGui::InputFloat3("Player 1 ", &fPlayer1Scale.X);
			ImGui::InputFloat3("Player 2 ", &fPlayer2Scale.X);

			bool scale_reset = ImGui::Button("Reset Scale");
			if (scale_reset)
			{
				fPlayer1Scale = { 1.0f,1.0f,1.0f };
				fPlayer2Scale = { 1.0f,1.0f,1.0f };
			}

			ImGui::Separator();
			ImGui::Text("Position");
			ImGui::SameLine(); ShowHelpMarker("Preview only!");
			if (MK10::GetCharacterObject(PLAYER1))
			{
				MK10::GetCharacterPosition(&plrPos, PLAYER1);
				ImGui::InputFloat3("X | Y | Z", &plrPos.X);
			}
			if (MK10::GetCharacterObject(PLAYER2))
			{
				MK10::GetCharacterPosition(&plrPos2, PLAYER2);
				ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
			}
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			ImGui::Text("Player 1");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health", &bInfiniteHealthPlayer1);
			ImGui::Checkbox("Infinite Super Meter", &bInfiniteSuperBarPlayer1);
			ImGui::Separator();

			ImGui::Text("Player 2");
			ImGui::Separator();
			ImGui::Checkbox("Infinite Health ", &bInfiniteHealthPlayer2);
			ImGui::Checkbox("Infinite Super Meter ", &bInfiniteSuperBarPlayer2);
			ImGui::Separator();
			ImGui::Checkbox("Infinite Timer", &bStopTimer);
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			bool swap = ImGui::Button("Swap Player Positions");
			ImGui::SameLine(); ShowHelpMarker("Shortcut - CTRL+F2");
			if (swap)
				((void(__fastcall*)())GetMKXAddr(0x14055FE90))();

			bool unlock = ImGui::Button("Unlock Costumes");
			ImGui::SameLine(); ShowHelpMarker("Execute this option in the Crypt");
			if (unlock)
			{
				int64 gallery = ((int64(__fastcall*)())GetMKXAddr(0x140483C00))();

				if (gallery)
					((void(__fastcall*)(int64))GetMKXAddr(0x1404A2150))(gallery);
			}


			ImGui::Separator();
			ImGui::Text("Gamespeed Control");
			ImGui::SameLine();
			bool slowmo = ImGui::Button("Apply");
			ImGui::SameLine(); ShowHelpMarker("Shortcut - CTRL+F3");
			if (slowmo)
				MK10::SlowGameTimeForXTicks(fSlowMotionSpeed, iSlowMotionTicks);

			ImGui::SliderFloat("Speed", &fSlowMotionSpeed, 0.0f, 2.0f);
			ImGui::InputInt("Ticks", &iSlowMotionTicks, 1000, 10000);


			ImGui::Checkbox("Disable Combo Damage Scaling", &SettingsMgr->bDisableComboDamageScaling);

		}
	}

	ImGui::End();
}

void MK10Menu::UpdateControls()
{
	if (GetAsyncKeyState(SettingsMgr->iHookMenuOpenKey))
	{
		if (GetTickCount64() - timer <= 150) return;
		timer = GetTickCount64();
		bIsActive ^= 1;
	}
}

bool MK10Menu::GetActiveState()
{
	return bIsActive;
}

void PushErrorMessage(const char * message)
{
	if (!bShowMessageError)
	{
		bShowMessageError = true;
		ImGui::Begin("ERROR", &bShowMessageError);
		ImGui::Text(message);
		if (ImGui::Button("OK"))
			bShowMessageError = false;
		ImGui::End();
	}

}
