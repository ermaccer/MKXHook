#include "mk10menu.h"
#include "mk10.h"
#include "mk10utils.h"
#include <iostream>
#include <Windows.h>
#include <imgui.h>
#include "eSettingsManager.h"
#include <vector>
#include <string>
#include "eNotifManager.h"
#include "..\eDirectX11Hook.h"
#include "helper\eMouse.h"
#include "MKCamera.h"

std::vector<std::string> P1Traits;
std::vector<std::string> P2Traits;
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

const char* szTraits[]{
	"TRAIT_Alien1",
	"TRAIT_Alien2",
	"TRAIT_Alien3",
	"TRAIT_Aztec1",
	"TRAIT_Aztec2",
	"TRAIT_Aztec3",
	"TRAIT_BoRaiChoDLC1",
	"TRAIT_BoRaiChoDLC2",
	"TRAIT_BoRaiChoDLC3",
	"TRAIT_CageJr1",
	"TRAIT_CageJr2",
	"TRAIT_CageJr3",
	"TRAIT_Ermac1",
	"TRAIT_Ermac2",
	"TRAIT_Ermac3",
	"TRAIT_Goro1",
	"TRAIT_Goro2",
	"TRAIT_Goro3",
	"TRAIT_Jason1",
	"TRAIT_Jason2",
	"TRAIT_Jason3",
	"TRAIT_Jax1",
	"TRAIT_Jax2",
	"TRAIT_Jax3",
	"TRAIT_JaxJr1",
	"TRAIT_JaxJr2",
	"TRAIT_JaxJr3",
	"TRAIT_JohnnyCage1",
	"TRAIT_JohnnyCage2",
	"TRAIT_JohnnyCage3",
	"TRAIT_Kano1",
	"TRAIT_Kano2",
	"TRAIT_Kano3",
	"TRAIT_Kenshi1",
	"TRAIT_Kenshi2",
	"TRAIT_Kenshi3",
	"TRAIT_KenshiJr1",
	"TRAIT_KenshiJr2",
	"TRAIT_KenshiJr3",
	"TRAIT_Kitana1",
	"TRAIT_Kitana2",
	"TRAIT_Kitana3",
	"TRAIT_Kunglao1",
	"TRAIT_Kunglao2",
	"TRAIT_Kunglao3",
	"TRAIT_KungLaoJr1",
	"TRAIT_KungLaoJr2",
	"TRAIT_KungLaoJr3",
	"TRAIT_LadyBug1",
	"TRAIT_LadyBug2",
	"TRAIT_LadyBug3",
	"TRAIT_LeatherFace1",
	"TRAIT_LeatherFace2",
	"TRAIT_LeatherFace3",
	"TRAIT_LiuKang1",
	"TRAIT_LiuKang2",
	"TRAIT_LiuKang3",
	"TRAIT_MasterMale1",
	"TRAIT_MasterMale2",
	"TRAIT_MasterMale3",
	"TRAIT_Mileena1",
	"TRAIT_Mileena2",
	"TRAIT_Mileena3",
	"TRAIT_Nomad1",
	"TRAIT_Nomad2",
	"TRAIT_Nomad3",
	"TRAIT_Predator1",
	"TRAIT_Predator2",
	"TRAIT_Predator3",
	"TRAIT_QuanChi1",
	"TRAIT_QuanChi2",
	"TRAIT_QuanChi3",
	"TRAIT_Raiden1",
	"TRAIT_Raiden2",
	"TRAIT_Raiden3",
	"TRAIT_Reptile1",
	"TRAIT_Reptile2",
	"TRAIT_Reptile3",
	"TRAIT_Scorpion1",
	"TRAIT_Scorpion2",
	"TRAIT_Scorpion3",
	"TRAIT_Shinnok1",
	"TRAIT_Shinnok2",
	"TRAIT_Shinnok3",
	"TRAIT_Sonya1",
	"TRAIT_Sonya2",
	"TRAIT_Sonya3",
	"TRAIT_Subzero1",
	"TRAIT_Subzero2",
	"TRAIT_Subzero3",
	"TRAIT_TanyaDLC1",
	"TRAIT_TanyaDLC2",
	"TRAIT_TanyaDLC3",
	"TRAIT_Tremor1",
	"TRAIT_Tremor2",
	"TRAIT_Tremor3",
	"TRAIT_Triborg1",
	"TRAIT_Triborg2",
	"TRAIT_Triborg3",
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

const char* szBones[] = {
	"Head",
	"Hips",
	"Jaw",
	"LeftArm",
	"LeftEye",
	"LeftFoot",
	"LeftForeArm",
	"LeftHand",
	"LeftLeg",
	"Neck",
	"Neck1",
	"Reference",
	"RightArm",
	"RightEye",
	"RightFoot",
	"RightHand",
	"RightLeg",
	"Spine",
	"Spine1",
	"Spine2",
	"Spine3",
};

const char* szCameraModes[TOTAL_CUSTOM_CAMERAS] = {
	"Third Person",
	"Third Person #2",
	"First Person",
	"First Person Mid",
	"Head Perspective"
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
	sprintf(szPlayer1ModifierCharacter, szCharacters[0]);
	sprintf(szPlayer2ModifierCharacter, szCharacters[0]);
	sprintf(szCurrentCameraOption, szCameraModes[0]);
	sprintf(szStageModifierStage, szStageNames[0]);
	sprintf(szPlayer1Trait, szTraits[0]);
	sprintf(szPlayer2Trait, szTraits[0]);
	sprintf(szPlayer1Bone, szBones[0]);
	sprintf(szPlayer2Bone, szBones[0]);
}

void MK10Menu::Process()
{
	UpdateControls();
}

void MK10Menu::Draw()
{
	ImGui::GetIO().MouseDrawCursor = true;
	ImGui::Begin(GetMKXHookVersion(),&m_bIsActive, ImGuiWindowFlags_MenuBar);

	if (ImGui::BeginMenuBar())
	{
		if (ImGui::BeginMenu("Settings"))
		{
			m_bSubmenuActive[SUBMENU_SETTINGS] = true;
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Help"))
		{
			if (ImGui::MenuItem("Script Reference"))
				m_bSubmenuActive[SUBMENU_SCRIPT] = true;
			ImGui::EndMenu();
		}
	}
	ImGui::EndMenuBar();

	if (ImGui::BeginTabBar("##tabs"))
	{
		if (ImGui::BeginTabItem("Character Modifier"))
		{
			DrawCharacterTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Variation Manager"))
		{
			DrawVariationsTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Stage Modifier"))
		{
			DrawStageTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Player Control"))
		{
			DrawPlayerTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Speed Modifier"))
		{
			DrawSpeedTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Camera Control"))
		{
			DrawCameraTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Cheats"))
		{
			DrawCheatsTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Script"))
		{
			DrawScriptTab();
			ImGui::EndTabItem();
		}
		if (ImGui::BeginTabItem("Misc."))
		{
			DrawMiscTab();
			ImGui::EndTabItem();
		}

	}
	ImGui::End();

	if (m_bSubmenuActive[SUBMENU_SETTINGS])
		DrawSettings();

	if (m_bSubmenuActive[SUBMENU_SCRIPT])
		DrawScriptReference();
}

void MK10Menu::UpdateControls()
{
	if (!m_bIsActive)
	{
		if (GetAsyncKeyState(SettingsMgr->iToggleCustomCamKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				m_bCustomCameras ^= 1;
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Custom cameras can only be activated in game!");
			}
		}
		if (GetAsyncKeyState(SettingsMgr->iResetStageInteractablesKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			if (GetObj(PLAYER1) && GetObj(PLAYER2))
				GetGameInfo()->ResetStageInteractables();
			else
			{
				Notifications->SetNotificationTime(2500);
				Notifications->PushNotification("Stage objects can only be reset in game!");
			}
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleSlowMoKey))
		{
			if (GetTickCount64() - timer <= 150) return;
			timer = GetTickCount64();
			TheMenu->m_bSlowMotion ^= 1;
		}

		if (GetAsyncKeyState(SettingsMgr->iToggleFreezeWorldKey))
		{
			if (m_bHookDispatch)
			{
				if (GetTickCount64() - timer <= 150) return;
				timer = GetTickCount64();
				m_bFreezeWorld ^= 1;
			}
		}
		ProcessScriptHotkeys();
	}

}

void MK10Menu::UpdateFreecam()
{
	if (TheMenu->m_bFreeCam)
	{
		if (TheCamera)
		{
			FVector fwd = TheCamera->GetMatrix().GetForward();
			FVector strafe = TheCamera->GetMatrix().GetRight();
			FVector up = TheCamera->GetMatrix().GetUp();

			// forward

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXPlus))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * 1;


			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyXMinus))
				TheMenu->camPos += fwd * TheMenu->m_fFreeCameraSpeed * -1;

			// strafe

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYPlus))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYMinus))
				TheMenu->camPos += strafe * TheMenu->m_fFreeCameraSpeed * -1;

			// up

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZPlus))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * 1;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyZMinus))
				TheMenu->camPos += up * TheMenu->m_fFreeCameraSpeed * -1;


			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawMinus))
				TheMenu->camRot.Yaw -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyYawPlus))
				TheMenu->camRot.Yaw += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollMinus))
				TheMenu->camRot.Roll -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyRollPlus))
				TheMenu->camRot.Roll += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchMinus))
				TheMenu->camRot.Pitch -= TheMenu->m_nFreeCameraRotationSpeed;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyPitchPlus))
				TheMenu->camRot.Pitch += TheMenu->m_nFreeCameraRotationSpeed;

			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVMinus))
				TheMenu->camFov -= 1.0f;
			if (GetAsyncKeyState(SettingsMgr->iFreeCameraKeyFOVPlus))
				TheMenu->camFov += 1.0f;


			// mouse
			{
				if (!TheMenu->m_bIsActive && TheMenu->m_bMouseControl)
				{
					TheMenu->camRot.Pitch += eMouse::GetDeltaY();
					TheMenu->camRot.Yaw += eMouse::GetDeltaX();
				}
			}
		}

	}
}

void MK10Menu::DrawCharacterTab()
{
	ImGui::Checkbox("Enable Player 1 Modifier", &m_bPlayer1Modifier);
	ImGui::SameLine(); ShowHelpMarker("It does not matter who you choose at character select screen, character will be changed upon match start. Works in all game modes");

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
	ImGui::Separator();
	ImGui::Checkbox("Enable Player 2 Modifier", &m_bPlayer2Modifier);
	ImGui::SameLine(); ShowHelpMarker("Do not replace Shinnok boss fight, game will crash.");

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
	ImGui::Separator();



}

void MK10Menu::DrawStageTab()
{
	ImGui::Checkbox("Enable Stage Modifier", &m_bStageModifier);

	if (ImGui::BeginCombo("Stage", szStageModifierStage))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szStageNames); n++)
		{
			bool is_selected = (szStageModifierStage == szStageNames[n]);
			if (ImGui::Selectable(szStageNames[n], is_selected))
				sprintf(szStageModifierStage, szStageNames[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Reset Stage Objects"))
		GetGameInfo()->ResetStageInteractables();

}

void MK10Menu::DrawVariationsTab()
{
	ImGui::TextWrapped("You can load non default variations for all characters. Multiple variations can be loaded for"
		" one character.");
	ImGui::TextWrapped("Cyber Sub-Zero is not a variation. There's a high chance of crashing the game so be aware!");
	ImGui::Separator();

	ImGui::Checkbox("Enable P1 Custom Variations", &m_bPlayer1CustomTrait);

	if (ImGui::BeginCombo("Variation (P1)", szPlayer1Trait))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szTraits); n++)
		{
			bool is_selected = (szPlayer1Trait == szTraits[n]);
			if (ImGui::Selectable(szTraits[n], is_selected))
				sprintf(szPlayer1Trait, szTraits[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Add (P1)"))
	{
		std::string str = szPlayer1Trait;
		P1Traits.push_back(str);
	}
	ImGui::SameLine();
	if (ImGui::Button("Clear (P1)"))
	{
		P1Traits.clear();
	}
	ImGui::Text("Traits to use:");
	for (int i = 0; i < P1Traits.size(); i++)
	{
		ImGui::Text("%d %s", i + 1, P1Traits[i].c_str());
	}

	ImGui::Separator();
	ImGui::Checkbox("Enable P2 Custom Variations", &m_bPlayer2CustomTrait);
	if (ImGui::BeginCombo("Variation (P2)", szPlayer2Trait))
	{
		for (int n = 0; n < IM_ARRAYSIZE(szTraits); n++)
		{
			bool is_selected = (szPlayer2Trait == szTraits[n]);
			if (ImGui::Selectable(szTraits[n], is_selected))
				sprintf(szPlayer2Trait, szTraits[n]);
			if (is_selected)
				ImGui::SetItemDefaultFocus();

		}
		ImGui::EndCombo();
	}

	if (ImGui::Button("Add (P2)"))
	{
		std::string str = szPlayer2Trait;
		P2Traits.push_back(str);
	}
	ImGui::SameLine();
	if (ImGui::Button("Clear (P2)"))
	{
		P2Traits.clear();
	}
	ImGui::Text("Traits to use:");
	for (int i = 0; i < P2Traits.size(); i++)
	{
		ImGui::Text("%d %s", i + 1, P2Traits[i].c_str());
	}

}

void MK10Menu::DrawPlayerTab()
{
	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{
		ImGui::Checkbox("Change Player Speed", &m_bChangePlayerSpeed);
		ImGui::SliderFloat("Player 1", &m_fP1Speed, 0.0, 10.0f);
		ImGui::SliderFloat("Player 2", &m_fP2Speed, 0.0, 10.0f);
		if (ImGui::Button("Reset Speed"))
		{
			m_fP1Speed = 1.0f;
			m_fP2Speed = 1.0f;
			if (GetObj(PLAYER1))
				GetObj(PLAYER1)->SetSpeed(m_fP1Speed);
			if (GetObj(PLAYER2))
				GetObj(PLAYER2)->SetSpeed(m_fP1Speed);
		}

		ImGui::Checkbox("Change Player Scale", &m_bChangePlayerScale);
		ImGui::InputFloat3("Player 1 ", &m_vP1Scale.X);
		ImGui::InputFloat3("Player 2 ", &m_vP2Scale.X);

		if (ImGui::Button("Reset Scale"))
		{
			m_vP1Scale = { 1.0f,1.0f,1.0f };
			m_vP2Scale = { 1.0f,1.0f,1.0f };
			if (GetObj(PLAYER1))
				GetObj(PLAYER1)->SetScale(&m_vP1Scale);
			if (GetObj(PLAYER2))
				GetObj(PLAYER2)->SetScale(&m_vP2Scale);
		}


		ImGui::Separator();
		ImGui::Text("Position");
		ImGui::SameLine(); ShowHelpMarker("Read only!");
		if (GetObj(PLAYER1))
		{
			GetCharacterPosition(&plrPos, PLAYER1);
			ImGui::InputFloat3("X | Y | Z", &plrPos.X);
		}
		if (GetObj(PLAYER2))
		{
			GetCharacterPosition(&plrPos2, PLAYER2);
			ImGui::InputFloat3("X | Y | Z", &plrPos2.X);
		}
	}
	else
		ImGui::Text("Player options are only available in-game!");
}

void MK10Menu::DrawSpeedTab()
{
	ImGui::Text("Gamespeed Control");
	ImGui::InputFloat("", &m_fSlowMotionSpeed, 0.1f);

	if (m_fSlowMotionSpeed > 2.0f) m_fSlowMotionSpeed = 2.0f;
	if (m_fSlowMotionSpeed < 0.0f) m_fSlowMotionSpeed = 0.0f;
	ImGui::Checkbox("Enable", &m_bSlowMotion);
	ImGui::SameLine(); ShowHelpMarker("Hotkey - F5.");


	ImGui::Separator();
	ImGui::TextWrapped("Tick this checkbox if you want to freeze game with a button, this might cause issues with pause menus and stuff so enable only when needed!");
	ImGui::Checkbox("Hook Freeze World", &m_bHookDispatch);

	if (m_bHookDispatch)
	{
		ImGui::Checkbox("Freeze World", &m_bFreezeWorld);
		ImGui::SameLine();
		ShowHelpMarker("Hotkey - F2");
	}

	ImGui::Separator();
}

void MK10Menu::DrawCameraTab()
{
	ImGui::Checkbox("Set Camera Position", &m_bCustomCameraPos);
	ImGui::InputFloat3("X | Y | Z", &camPos.X);
	ImGui::Checkbox("Set Camera Rotation", &m_bCustomCameraRot);
	ImGui::InputInt3("Pitch | Yaw | Roll", &camRot.Pitch);

	ImGui::Checkbox("Set FOV", &m_bCustomCameraFOV);
	ImGui::InputFloat("FOV", &camFov);

	ImGui::Separator();
	ImGui::Checkbox("Enable Freecam", &m_bFreeCam);
	ImGui::SameLine(); ShowHelpMarker("Allows to move camera with certain keys.\nRequires all toggles enabled!\nYou can configure keys in .ini file.");

	if (m_bFreeCam)
	{
		if (!m_bCustomCameraPos || !m_bCustomCameraRot || !m_bCustomCameraFOV)
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Check rest of the Set Camera options!");

		ImGui::InputFloat("Freecam Speed", &m_fFreeCameraSpeed);
		ImGui::InputInt("Freecam Rotation Speed", &m_nFreeCameraRotationSpeed);
		ImGui::Checkbox("Mouse Control", &m_bMouseControl);
	}




	ImGui::Separator();
	ImGui::Checkbox("Force Camera To Move", &m_bForceCameraUpdate);
	ImGui::SameLine(); ShowHelpMarker("Check this option if you can't move camera anymore in win poses and some cinematics.");


	ImGui::Separator();
	ImGui::Checkbox("Custom Cameras", &m_bCustomCameras);
	if (GetObj(PLAYER1) && GetObj(PLAYER2))
	{

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
		m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);

		m_nCurrentCustomCamera = GetCamMode(szCurrentCameraOption);
		if (m_nCurrentCustomCamera == CAMERA_1STPERSON || m_nCurrentCustomCamera == CAMERA_1STPERSON_MID)
		{
			ImGui::InputFloat("FPS Camera Offset", &m_fAdjustCam);
		}
		else if (m_nCurrentCustomCamera == CAMERA_HEAD_TRACKING)
		{
			ImGui::InputFloat("Up/Down Angle Offset", &m_fAdjustCustomHeadCameraY);
			ImGui::InputFloat("Up/Down Offset", &m_fAdjustCustomHeadCameraZ);
			ImGui::InputFloat("Left/Right Offset", &m_fAdjustCustomHeadCameraX);

			ImGui::Checkbox("Don't Flip Camera", &m_bDontFlipCamera);
			ImGui::SameLine(); ShowHelpMarker("Use this option for head tracked cinematics.");
			ImGui::Checkbox("Use Player Two As Source", &m_bUsePlayerTwoAsTracker);

			ImGui::TextWrapped("Toggle 'Disable Head Tracking' in Misc. section first to use this mode properly. Toggle it at select screen.");
			ImGui::TextWrapped("Recommended to set FOV value to at least 110 to make this mode look right!");
			ImGui::TextColored(ImVec4(1.f, 0.3f, 0.3f, 1.f), "Disable this mode before restarting or leaving match!");
		}
	}
	else
		ImGui::Text("Custom cameras will appear once in-game!");
}

void MK10Menu::DrawCheatsTab()
{
	ImGui::Separator();
	ImGui::Columns(2);
	ImGui::SetColumnWidth(0, 11.5f * ImGui::GetFontSize());

	ImGui::Text("Infinite Health");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##infhealth", &m_bInfiniteHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##infhealth", &m_bInfiniteHealthP2);
	ImGui::NextColumn();


	ImGui::Text("Zero Health\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##0health", &m_bNoHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##0health", &m_bNoHealthP2);
	ImGui::NextColumn();

	ImGui::Text("One Health\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##1health", &m_bOneHealthP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##1health", &m_bOneHealthP2);
	ImGui::NextColumn();


	ImGui::Text("Infinite Meter\n");
	ImGui::NextColumn();
	ImGui::Checkbox("P1##super", &m_bInfiniteMeterP1);
	ImGui::SameLine();
	ImGui::Checkbox("P2##super", &m_bInfiniteMeterP2);
	ImGui::NextColumn();

	ImGui::Text("Freeze Timer\n");
	ImGui::NextColumn();
	ImGui::Checkbox("Enable##time", &m_bStopTimer);
	ImGui::NextColumn();

	ImGui::Columns(1);

}

void MK10Menu::DrawMiscTab()
{
	if (ImGui::Button("Hide FightHUD"))
		HideHUD();
	ImGui::SameLine();
	if (ImGui::Button("Show FightHUD"))
		ShowHUD();
	ImGui::Checkbox("Hide FightHUD In Game", &m_bAutoHideHUD);
	ImGui::Checkbox("Disable Combo Scaling", &m_bDisableComboScaling);
	ImGui::Checkbox("Disable Head Tracking", &m_bDisableHeadTracking);
	ImGui::SameLine();
	ShowHelpMarker("NOTE: Enable this in select screen! Disables P1 head looking at P2. Automatically enabled with 'Head Perspective' custom camera.");

	bool unlock = ImGui::Button("Unlock Costumes");
	ImGui::SameLine(); ShowHelpMarker("Execute this option in the Crypt");
	if (unlock)
	{
		int64 gallery = ((int64(__fastcall*)())_addr(0x140483C00))();

		if (gallery)
		{
			((void(__fastcall*)(int64))_addr(0x1404A2150))(gallery);
			Notifications->SetNotificationTime(5500);
			Notifications->PushNotification("Costumes should be unlocked now, check costumes list in select screen.");
		}

	}

}

void MK10Menu::DrawScriptTab()
{
	ImGui::RadioButton("On Player1", &m_nScriptExecuteType, SCRIPT_P1); ImGui::SameLine();
	ImGui::RadioButton("On Player2", &m_nScriptExecuteType, SCRIPT_P2);

	static char szScriptSource[256] = {};
	ImGui::InputText("Script Source", szScriptSource, sizeof(szScriptSource));
	ImGui::Separator();

	m_pScript = GetScript(szScriptSource);
	if (m_pScript)
	{
		static int functionIndex = 0;
		static char szFunction[256] = {};

		static int hash = 0;
		ImGui::TextWrapped("Functions with params are not supported!");

		ImGui::InputText("Function Name", szFunction, sizeof(szFunction));
		ImGui::InputInt("Function Index", &functionIndex, 1, 100, ImGuiInputTextFlags_ReadOnly);
		ImGui::SameLine(); ShowHelpMarker("Read only.");

		static eScriptKeyBind bind;
		if (ImGui::Button("Add Hotkey"))
		{
			m_nHash = HashString(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			bind.functionHash = m_nHash;
			sprintf(bind.scriptName, "%s", szScriptSource);
			bind.type = (eScriptExecuteType)m_nScriptExecuteType;

			m_bPressingKey = true;
		}

		if (m_bPressingKey)
		{
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				bind.key = result;
				m_vKeyBinds.push_back(bind);
				m_bPressingKey = false;
			}

		}
		ImGui::SameLine();
		if (ImGui::Button("Run"))
		{
			m_nHash = HashString(szFunction);
			functionIndex = m_pScript->GetFunctionID(m_nHash);

			RunLastScript();
		}
	}
	else
	{
		if (strlen(szScriptSource) > 0)
			ImGui::TextWrapped("%s not available!", szScriptSource);
	}


	ImGui::Separator();
	ImGui::TextWrapped("Registered hotkeys:");
	for (unsigned int i = 0; i < m_vKeyBinds.size(); i++)
	{
		ImGui::TextWrapped("%s - Run [0x%X] from %s", eKeyboardMan::KeyToString(m_vKeyBinds[i].key), m_vKeyBinds[i].functionHash, m_vKeyBinds[i].scriptName);
	}

	if (ImGui::Button("Clear All"))
		m_vKeyBinds.clear();
}

void MK10Menu::DrawSettings()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Settings", &m_bSubmenuActive[SUBMENU_SETTINGS]);

	static int settingID = 0;
	static const char* settingNames[] = {
		"Menu",
		"INI",
		"Keys",
		"Mouse"
	};

	enum eSettings {
		MENU,
		INI,
		KEYS,
		MOUSE
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(settingNames); n++)
	{
		bool is_selected = (settingID == n);
		if (ImGui::Selectable(settingNames[n], is_selected))
			settingID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (settingID)
	{
	case MENU:
		ImGui::TextWrapped("All user settings are saved to mkxhook_user.ini.");
		ImGui::Text("Menu Scale");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::InputFloat("", &SettingsMgr->fMenuScale);
		ImGui::PopItemWidth();
		break;
	case INI:
		ImGui::TextWrapped("These settings control MKXHook.ini options. Any changes require game restart to take effect.");
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		ImGui::Checkbox("Debug Console", &SettingsMgr->bEnableConsoleWindow);
		ImGui::Checkbox("Gamepad Support", &SettingsMgr->bEnableGamepadSupport);
		ImGui::Checkbox("60 FPS Patch", &SettingsMgr->bEnable60FPSFrontend);

		ImGui::LabelText("", "Features");
		ImGui::Separator();
		ImGui::Checkbox("Disable Sweat Effects", &SettingsMgr->bDisableSweatEffects);
		ImGui::SameLine(); ShowHelpMarker("Disables sweat generation on fighters.");
		ImGui::Checkbox("Enable NPC Fatalities", &SettingsMgr->bEnableNPCFatalities);
		ImGui::SameLine(); ShowHelpMarker("Allows to perform fatalities on NPCs");
		ImGui::Checkbox("Enable NPC Victory Poses", &SettingsMgr->bEnableNPCVictoryPoses);
		ImGui::SameLine(); ShowHelpMarker("(currently) Assigns Kung Lao's victory animation to Rain.");
		ImGui::Checkbox("Fix NPC Gender Messages", &SettingsMgr->bFixNPCGenderFatalityMessage);
		ImGui::SameLine(); ShowHelpMarker("Rain, Baraka and Corrupted Shinnok will correctly use 'Finish Him'.");
		ImGui::Checkbox("Disable Asset Checking", &SettingsMgr->bDisableAssetHashChecking);
		ImGui::SameLine(); ShowHelpMarker("Allows to freely replace files without the need of updating toc data.");
		ImGui::Checkbox("Disable Cinematics Letterboxing", &SettingsMgr->bDisableCinematicLetterboxing);
		ImGui::SameLine(); ShowHelpMarker("Removes black bars from cutscenes.");

		break;
	case KEYS:
		if (m_bPressingKey)
			ImGui::TextColored(ImVec4(0.f, 1.f, 0.3f, 1.f), "Press a key!");

		if (ImGui::Button("Reset Keys", { -FLT_MIN, 0 }))
		{
			SettingsMgr->ResetKeys();
			Notifications->SetNotificationTime(2500);
			Notifications->PushNotification("Keys reset! Remember to save.");

		}
		ImGui::Separator();
		ImGui::LabelText("", "Core");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iHookMenuOpenKey, "Open/Close Menu", "menu");
		KeyBind(&SettingsMgr->iToggleSlowMoKey, "Toggle Gamespeed/Slow Motion", "slomo");
		KeyBind(&SettingsMgr->iToggleFreezeWorldKey, "Freeze World", "freeze");
		ImGui::Separator();
		ImGui::LabelText("", "Camera");
		ImGui::Separator();

		KeyBind(&SettingsMgr->iFreeCameraKeyFOVPlus, "FOV+", "fov_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyFOVMinus, "FOV-", "fov_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyYawPlus, "Yaw+", "ya_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYawMinus, "Yaw-", "ya_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchPlus, "Pitch+", "pi_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyPitchMinus, "Pitch-", "pi_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollPlus, "Roll+", "r_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyRollMinus, "Roll-", "r_minus");

		KeyBind(&SettingsMgr->iFreeCameraKeyXPlus, "Forward", "x_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyXMinus, "Back", "x_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYPlus, "Left", "y_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyYMinus, "Right", "y_minus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZPlus, "Up", "z_plus");
		KeyBind(&SettingsMgr->iFreeCameraKeyZMinus, "Down", "z_minus");


		ImGui::Separator();
		ImGui::LabelText("", "Misc");
		ImGui::Separator();
		KeyBind(&SettingsMgr->iToggleCustomCamKey, "Toggle Custom Cameras", "ccam");
		KeyBind(&SettingsMgr->iResetStageInteractablesKey, "Reset Stage Objects", "r_stage");
		ImGui::Separator();

		if (m_bPressingKey)
		{
			eVKKeyCode result = eKeyboardMan::GetLastKey();

			if (result >= VK_BACKSPACE && result < VK_KEY_NONE)
			{
				*m_pCurrentVarToChange = result;
				m_bPressingKey = false;
			}

		}
		break;
	case MOUSE:
		ImGui::TextWrapped("All user settings are saved to mkxhook_user.ini.");
		ImGui::Text("Sensitivity");
		ImGui::PushItemWidth(-FLT_MIN);
		ImGui::SliderInt("", &SettingsMgr->mouse.sens, 1, 50);
		ImGui::PopItemWidth();
		ImGui::Checkbox("Invert X", &SettingsMgr->mouse.invert_x);
		ImGui::Checkbox("Invert Y", &SettingsMgr->mouse.invert_y);
		break;
	default:
		break;
	}

	if (ImGui::Button("Save", { -FLT_MIN, 0 }))
	{
		Notifications->SetNotificationTime(2500);
		Notifications->PushNotification("Settings saved to MKXHook.ini and mkxhook_user.ini!");
		eDirectX11Hook::ms_bShouldReloadFonts = true;
		SettingsMgr->SaveSettings();
	}

	ImGui::EndChild();

	ImGui::End();
}

void MK10Menu::DrawScriptReference()
{
	ImGui::SetNextWindowPos({ ImGui::GetIO().DisplaySize.x / 2.0f, ImGui::GetIO().DisplaySize.y / 2.0f }, ImGuiCond_Once, { 0.5f, 0.5f });
	ImGui::SetNextWindowSize({ 54 * ImGui::GetFontSize(), 54 * ImGui::GetFontSize() }, ImGuiCond_Once);
	ImGui::Begin("Script Reference", &m_bSubmenuActive[SUBMENU_SCRIPT]);

	static int secID = 0;
	static const char* scriptSections[] = {
		"General",
		"Usage",
	};

	enum eScriptRef {
		GEN,
		USG,
	};

	ImGui::BeginChild("##settings", { 12 * ImGui::GetFontSize(), 0 }, true);

	for (int n = 0; n < IM_ARRAYSIZE(scriptSections); n++)
	{
		bool is_selected = (secID == n);
		if (ImGui::Selectable(scriptSections[n], is_selected))
			secID = n;
		if (is_selected)
			ImGui::SetItemDefaultFocus();
	}

	ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("##content", { 0, -ImGui::GetFrameHeightWithSpacing() });

	switch (secID)
	{
	case GEN:
		ImGui::TextWrapped("You can find script functions in the MKScript folder. Open .mko file of interest with notepad or"
			" any hex editor. To find functions that can be executed look for strings starting with 'Rx', 'pFunc','p'.");
		break;
	case USG:
		ImGui::BulletText("On Player1 - selected function will execute on Player 1 object.\nUse with character scripts or FightEngine");
		ImGui::BulletText("On Player2 - selected function will execute on Player 2 object.\nUse with character scripts or FightEngine");

		ImGui::TextWrapped("Some common player functions:");
		ImGui::BulletText("BrutalityVictory");
		ImGui::BulletText("RoundOverWinnerTaunt");
		ImGui::BulletText("RoundOverGetupAny");
		ImGui::BulletText("RoundOverWinnerWalkaway");
		break;
	default:
		break;
	}

	ImGui::EndChild();

	ImGui::End();
}

void MK10Menu::DrawKeyBind(char* name, int* var)
{
	ImGui::SameLine();

	static char butName[256] = {};
	sprintf(butName, "%s##key%s", eKeyboardMan::KeyToString(*var), name);
	if (ImGui::Button(butName))
	{
		m_bPressingKey = true;
		m_pCurrentVarToChange = var;
	}
}

void MK10Menu::KeyBind(int* var, char* bindName, char* name)
{
	ImGui::LabelText("", bindName);
	DrawKeyBind(name, var);
}

bool MK10Menu::GetActiveState()
{
	return m_bIsActive;
}

void MK10Menu::RunLastScript()
{
	if (m_pScript->GetFunctionID(m_nHash))
	{
		switch (m_nScriptExecuteType)
		{
		case SCRIPT_P1:
			GetObj(PLAYER1)->ExecuteScript(m_pScript, m_nHash);
			break;
		case SCRIPT_P2:
			GetObj(PLAYER2)->ExecuteScript(m_pScript, m_nHash);
			break;
		default:
			break;
		}
	}
	else
	{
		Notifications->SetNotificationTime(3500);
		Notifications->PushNotification("Function %x does not exist!", m_nHash);
	}
}

void MK10Menu::ProcessScriptHotkeys()
{
	for (int i = 0; i < m_vKeyBinds.size(); i++)
	{
		if (GetAsyncKeyState(m_vKeyBinds[i].key) & 0x1)
		{
			MKScript* script = GetScript(m_vKeyBinds[i].scriptName);
			if (script->GetFunctionID(m_vKeyBinds[i].functionHash))
			{
				switch (m_vKeyBinds[i].type)
				{
				case SCRIPT_P1:
					GetObj(PLAYER1)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				case SCRIPT_P2:
					GetObj(PLAYER2)->ExecuteScript(script, m_vKeyBinds[i].functionHash);
					break;
				default:
					break;
				}
			}
			else
			{
				Notifications->SetNotificationTime(3500);
				Notifications->PushNotification("Function %x does not exist!", m_vKeyBinds[i].functionHash);
			}
		}
	}
}

char * GetMKXHookVersion()
{
	static char buffer[512] = {};
	sprintf(buffer, "MKXHook by ermaccer (%s)", MKXHOOK_VERSION);
	return buffer;
}
