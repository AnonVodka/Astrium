#include "Hooks.h"
#include "newMenu.h"
#include "Tools/Hacks/Misc.h"


bool rage;
bool legit;
bool visuals;
bool misc;
bool skins;
bool colors;
//cOptions Options;
void Unhook();
void Gui_Init(IDirect3DDevice9* pDevice);
extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);

void Gui_Init(IDirect3DDevice9* pDevice)
{
	ImGuiIO& io = ImGui::GetIO();
	io.DeltaTime = 1.f / 60.f;
	D3DDEVICE_CREATION_PARAMETERS d3dcp{ 0 };
	pDevice->GetCreationParameters(&d3dcp);

	auto& style = ImGui::GetStyle();

	Global::fDefault = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Verdana.ttf", 15.0f);

	Global::fTabs = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\auifont.ttf", 62.0f);

	Global::fSubTabs = io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\AstriumWep.ttf", 25.0f);
	static int hue = 140;

	ImVec4 col_text = ImColor::HSV(hue / 255.f, 20.f / 255.f, 235.f / 255.f);
	ImVec4 col_main = ImColor(9, 82, 128);
	ImVec4 col_back = ImColor(31, 44, 54);
	ImVec4 col_area = ImColor(4, 32, 41);

	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.30f, 0.30f, 0.30f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.11f, 0.11f, 0.11f, 0.95f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.09f, .09f, .09f, 1.f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.13, 0.13, 0.13, 1.f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.11, 0.11, 0.11, 1.f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(.52f, 0.f, 0.52f, .7f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(.52f, 0.f, 0.52f, .7);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(.52f, 0.f, 0.52f, .7f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(.52f, 0.f, 0.52f, .7f);;
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); //main half
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.50f, 0.50f, 0.50f, 0.70f); //main half
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(.52f, 0.f, 0.52f, 1.f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.15, 0.15, 0.15, 1.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(.52f, 0.f, 0.52f, 1.f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); //main half
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(.52f, 0.f, 0.52f, 1.f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.12, 0.12, 0.12, 1.f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.12, 0.12, 0.12, 1.f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.12, 0.12, 0.12, 1.f);
	style.Colors[ImGuiCol_Header] = ImVec4(.52f, 0.f, 0.52f, .7f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(.50f, 0.50f, 0.50f, .3f); // combobox hover
	style.Colors[ImGuiCol_ComboSelectedText] = ImVec4(.52f, 0.f, 0.52f, .87f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(.52f, 0.f, 0.52f, .87f);
	style.Colors[ImGuiCol_Column] = ImVec4(col_text.x, col_text.y, col_text.z, 0.32f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(col_text.x, col_text.y, col_text.z, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(col_main.x, col_main.y, col_main.z, 0.20f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 0.78f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(col_text.x, col_text.y, col_text.z, 0.f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(col_text.x, col_text.y, col_text.z, 0);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(col_text.x, col_text.y, col_text.z, 0.63f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(col_main.x, col_main.y, col_main.z, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.43f);
	style.Colors[ImGuiCol_PopupBg] = ImVec4(col_main.x, col_main.y, col_main.z, 0.92f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
		
	style.Alpha = .0f;
	style.WindowPadding = ImVec2(8, 8);
	style.WindowMinSize = ImVec2(32, 32);
	style.WindowRounding = 4.0f; //4.0
	style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
	style.ChildWindowRounding = 0.0f;
	style.FramePadding = ImVec2(4, 2);
	style.FrameRounding = 0.0f; //2.0
	style.ItemSpacing = ImVec2(8, 4);
	style.ItemInnerSpacing = ImVec2(4, 4);
	style.TouchExtraPadding = ImVec2(0, 0);
	style.IndentSpacing = 21.0f;
	style.ColumnsMinSpacing = 3.0f;
	style.ScrollbarSize = 12.0f;
	style.ScrollbarRounding = 16.0f; //16.0
	style.GrabMinSize = 0.1f;
	style.GrabRounding = 16.0f; //16.0
	style.ButtonTextAlign = ImVec2(0.5f, 0.5f);
	style.DisplayWindowPadding = ImVec2(22, 22);
	style.DisplaySafeAreaPadding = ImVec2(4, 4);
	style.AntiAliasedLines = true;
	style.AntiAliasedShapes = true;
	style.CurveTessellationTol = 1.25f;

	ImGui_ImplDX9_Init(INIT::Window, pDevice);

	Global::MenuInit = true;
}

void TextColor(bool active)
{
	auto& style = ImGui::GetStyle();

	if (active)
	{
		style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);
	}
	else
		style.Colors[ImGuiCol_Text] = ImVec4(0.39f, 0.39f, 0.39f, 1.f);
}

void DefineTab()
{
	if (Global::MenuTab == 0)
	{
		rage = true;
		legit = false;
		visuals = false;
		misc = false;
		skins = false;
		colors = false;
	}
	else if (Global::MenuTab == 1)
	{
		rage = false;
		legit = true;
		visuals = false;
		misc = false;
		skins = false;
		colors = false;
	}
	else if (Global::MenuTab == 2)
	{
		rage = false;
		legit = false;
		visuals = true;
		misc = false;
		skins = false;
		colors = false;
	}
	else if (Global::MenuTab == 3)
	{
		rage = false;
		legit = false;
		visuals = false;
		misc = true;
		skins = false;
		colors = false;
	}
	else if (Global::MenuTab == 4)
	{
		rage = false;
		legit = false;
		visuals = false;
		misc = false;
		skins = true;
		colors = false;
	}
	else if (Global::MenuTab == 5)
	{
		rage = false;
		legit = false;
		visuals = false;
		misc = false;
		skins = false;
		colors = true;
	}
}

void BtnNormal()
{
	auto& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImVec4(0.10, 0.10, 0.10, .98f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.13f, 0.13f, 0.13f, 1.f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.f);
}

void BtnActive()
{
	auto& style = ImGui::GetStyle();

	style.Colors[ImGuiCol_Button] = ImVec4(0.15f, 0.15f, 0.15f, .98f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.15f, 0.15f, 0.15f, 1.f);
}

void DrawRageTab()
{
	auto& style = ImGui::GetStyle();
	BtnNormal();

	style.ItemSpacing = ImVec2(0, 4);

	// Sub-Tabs ghetto
	if (Global::RageSubTab == 0)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);

	if (ImGui::Button("Aimbot", ImVec2(386, 32))) Global::RageSubTab = 0;
	ImGui::SameLine();

	if (Global::RageSubTab == 1)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);
	if (ImGui::Button("Anti-Aim", ImVec2(386, 32))) Global::RageSubTab = 1;

	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);

	style.WindowPadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(4, 4);

	if (Global::RageSubTab == 0)
	{
		ImGui::BeginChild("Aimbot - General", ImVec2(190, 398), true);
		{
			ImGui::Text("Aimbot - General");
			ImGui::Separator();

			ImGui::Checkbox("Enable Aimbot", &Options.Ragebot.Aimbot.bAimbotEnable);
			ImGui::Checkbox("Automatically Shoot", &Options.Ragebot.Aimbot.bAutoShoot);
			ImGui::Checkbox("Automatically Scope", &Options.Ragebot.Aimbot.bAutoScope);
			ImGui::Checkbox("Auto Pistol", &Options.Ragebot.Aimbot.bAutoPistol);
			ImGui::Checkbox("Auto Revolver", &Options.Ragebot.Aimbot.bAutoRevolver);
			ImGui::Checkbox("Silent Aim", &Options.Ragebot.Aimbot.bSilentAim);

			ImGui::Text("Prefered Hitbox:");
			ImGui::Combo("##hitbox", &Options.Ragebot.Aimbot.iHitbox, iHitbox, ARRAYSIZE(iHitbox));

			ImGui::Text("Select Target by:");
			ImGui::Combo("##tgtslt", &Options.Ragebot.Aimbot.iSelection, iSelection, ARRAYSIZE(iSelection));
		}ImGui::EndChild();

		ImGui::SameLine();

		ImGui::BeginChild("Aimbot - Accuracy", ImVec2(190, 398), true);
		{
			ImGui::Text("Aimbot - Accuracy");
			ImGui::Separator();
			ImGui::Checkbox("Velocity Prediction", &Options.Ragebot.Accuracy.bVelocityPrediction);
			ImGui::Text("Multibox");
			ImGui::Combo("##multibox", &Options.Ragebot.Accuracy.iMultibox, iMultibox, ARRAYSIZE(iMultibox));
			ImGui::Checkbox("Multipoint", &Options.Ragebot.Accuracy.bMultipoint);
			ImGui::SliderInt("Pointscale", &Options.Ragebot.Accuracy.iPointscale, 0.f, 100.f, "%.f");
			ImGui::SliderInt("Hitchance ", &Options.Ragebot.Accuracy.iHitchance, 0.f, 100.f, "%.f");
			ImGui::SliderInt("Min Dmg", &Options.Ragebot.Accuracy.iMinDmg, 0.f, 125.f, "%.f DMG");
			ImGui::Checkbox("Adaptive Min Damage", &Options.Ragebot.Accuracy.bAcceptKillDmg);
			ImGui::Checkbox("Remove Recoil", &Options.Ragebot.Accuracy.bNoRecoil);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Hack vs Hack", ImVec2(190, 398), true);
		{
			ImGui::Text("Hack vs Hack");
			ImGui::Separator();
			//ImGui::Text("Resolver");
			//ImGui::Combo("##resolver", &Options.Ragebot.HvH.iAntiAimResolver, iResolver, ARRAYSIZE(iResolver));
			ImGui::Checkbox("Position Adjustment", &Options.Ragebot.HvH.bPositionAdj);
			ImGui::Checkbox("Resolver", &Options.Ragebot.HvH.bResolver);
			ImGui::Text("Prefer Bodyaim:");		
			ImGui::Combo("##prf", &Options.Ragebot.HvH.iPreferBaim, iPreferBaim, ARRAYSIZE(iPreferBaim));

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Work in Progress", ImVec2(190, 398), true);
		{
			ImGui::Text("Work in Progress");
			ImGui::Separator();
		}ImGui::EndChild();
	}
	else if (Global::RageSubTab == 1)
	{
		ImGui::BeginChild("##aastand", ImVec2(190, 398), true);
		{		
			ImGui::Text("Anti Aim Stand");
			ImGui::Separator();
			ImGui::Checkbox("Enable Anti Aim", &Options.Ragebot.AntiAim.Stand.bEnableAntiAim);
			ImGui::Checkbox("At Targets", &Options.Ragebot.AntiAim.Stand.bAtTargets);
			ImGui::Separator();
			ImGui::Text("Pitch");
			if(Options.Misc.Misc2.bAntiUntrusted)
				ImGui::Combo("##sfgjwftj", &Options.Ragebot.AntiAim.Stand.iPitch, iPitch_Spread, ARRAYSIZE(iPitch_Spread));
			else
				ImGui::Combo("##fsghjdtzjudghj", &Options.Ragebot.AntiAim.Stand.iPitch, iPitch_Nospread, ARRAYSIZE(iPitch_Nospread));
			ImGui::Text("Yaw");
			ImGui::Combo("##dghkfgh", &Options.Ragebot.AntiAim.Stand.iYaw, iYaw, ARRAYSIZE(iYaw));
			ImGui::SliderInt(" 		       Add##standreal", &Options.Ragebot.AntiAim.Stand.iYawAdd, -180, 180, "%.0f");
			ImGui::Text("Fake Yaw");
			ImGui::Combo("##35673j", &Options.Ragebot.AntiAim.Stand.iFakeYaw, iFakeYaw, ARRAYSIZE(iFakeYaw));
			ImGui::SliderInt(" 		       Add##standfake", &Options.Ragebot.AntiAim.Stand.iFakeYawAdd, -180, 180, "%.0f");

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("##aamove", ImVec2(190, 398), true);
		{
			ImGui::Text("Anti Aim Move");
			ImGui::Separator();
			ImGui::Checkbox("Enable Anti Aim", &Options.Ragebot.AntiAim.Move.bEnableAntiAim);
			ImGui::Checkbox("Memewalk", &Options.Ragebot.AntiAim.Move.bMemeWalk);
			ImGui::Checkbox("At Targets", &Options.Ragebot.AntiAim.Move.bAtTargets);
			ImGui::Separator();
			ImGui::Text("Pitch");
			if (Options.Misc.Misc2.bAntiUntrusted)
				ImGui::Combo("##etzjdghj", &Options.Ragebot.AntiAim.Move.iPitch, iPitch_Spread, ARRAYSIZE(iPitch_Spread));
			else
				ImGui::Combo("##bhfnkfhujku", &Options.Ragebot.AntiAim.Move.iPitch, iPitch_Nospread, ARRAYSIZE(iPitch_Nospread));
			ImGui::Text("Yaw");
			ImGui::Combo("##sfgjsdzkjsdtjsfgh", &Options.Ragebot.AntiAim.Move.iYaw, iYaw, ARRAYSIZE(iYaw));
			ImGui::SliderInt(" 		       Add##movereal", &Options.Ragebot.AntiAim.Move.iYawAdd, -180, 180, "%.0f");
			ImGui::Text("Fake Yaw");
			ImGui::Combo("##fhjkdtrhfdgsj", &Options.Ragebot.AntiAim.Move.iFakeYaw, iFakeYaw, ARRAYSIZE(iFakeYaw));
			ImGui::SliderInt(" 		       Add##movefake", &Options.Ragebot.AntiAim.Move.iFakeYawAdd, -180, 180, "%.0f");

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("##edge", ImVec2(190, 398), true);
		{
			ImGui::Text("Edge Detection");
			ImGui::Separator();
			ImGui::Checkbox("Enable Edge Detection", &Options.Ragebot.AntiAim.Edge.bEnableEdge);
			ImGui::Separator();
			ImGui::Text("Pitch");
			if (Options.Misc.Misc2.bAntiUntrusted)
				ImGui::Combo("##etzkgrh", &Options.Ragebot.AntiAim.Edge.iPitch, iPitch_Spread, ARRAYSIZE(iPitch_Spread));
			else
				ImGui::Combo("##gzhk367i", &Options.Ragebot.AntiAim.Edge.iPitch, iPitch_Nospread, ARRAYSIZE(iPitch_Nospread));
			ImGui::Text("Yaw");
			ImGui::Combo("##fhjlkzuo", &Options.Ragebot.AntiAim.Edge.iYaw, iEdgeReal, ARRAYSIZE(iEdgeReal));
			ImGui::SliderInt(" 		       Add##edgereal", &Options.Ragebot.AntiAim.Edge.iYawAdd, -180, 180, "%.0f");
			ImGui::Text("Fake Yaw");
			ImGui::Combo("##ghkmtzk", &Options.Ragebot.AntiAim.Edge.iFakeYaw, iEdgeFake, ARRAYSIZE(iEdgeFake));
			ImGui::SliderInt(" 		       Add##edgefake", &Options.Ragebot.AntiAim.Edge.iFakeYawAdd, -180, 180, "%.0f");
		
		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("##aamisc", ImVec2(190, 398), true);
		{
			ImGui::Text("Anti Aim Misc");
			ImGui::Separator();
			ImGui::Checkbox("Fakewalk", &Options.Ragebot.AntiAim.Misc.bFakeWalk);
			ImGui::Hotkey("Key##fakewalkkey", &Options.Ragebot.AntiAim.Misc.iFakeWalkKey, ImVec2(150, 20));

		}ImGui::EndChild();
	}
}

void DrawLegitTab()
{
	auto& style = ImGui::GetStyle();
	BtnNormal();
	ImGui::PushFont(Global::fSubTabs);
	style.ItemSpacing = ImVec2(0, 4);

	if (Global::LegitSubTab == 0)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);

	if (ImGui::Button("G", ImVec2(128.5, 32))) Global::LegitSubTab = 0;
	ImGui::SameLine();
	
	if (Global::LegitSubTab == 1)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);
	if (ImGui::Button("P", ImVec2(128.5, 32))) Global::LegitSubTab = 1;
	ImGui::SameLine();

	if (Global::LegitSubTab == 2)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);
	if (ImGui::Button("W", ImVec2(128.5, 32))) Global::LegitSubTab = 2;
	ImGui::SameLine();

	if (Global::LegitSubTab == 3)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);
	if (ImGui::Button("d", ImVec2(128.5, 32))) Global::LegitSubTab = 3;
	ImGui::SameLine();

	if (Global::LegitSubTab == 4)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);

	if (ImGui::Button("f", ImVec2(128.5, 32))) Global::LegitSubTab = 4;
	ImGui::SameLine();

	if (Global::LegitSubTab == 5)
		style.Colors[ImGuiCol_Text] = ImVec4(1.f, 1.f, 1.f, 1.f);
	else
		style.Colors[ImGuiCol_Text] = ImVec4(.3f, .3f, .3f, 1.f);
	if (ImGui::Button("a", ImVec2(128.5, 32))) Global::LegitSubTab = 5;


	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);

	style.WindowPadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(4, 4);

	ImGui::PushFont(Global::fDefault);
	if (Global::LegitSubTab == 0)
	{
		ImGui::BeginChild("Pistols##aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot - Pistols");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Pistols.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Pistols.bOnKey);
			if (Options.Legitbot.Aimbot.Pistols.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Pistols.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Pistols.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Pistols.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Pistols.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Pistols.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Pistols##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Pistols");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Pistols.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Pistols.bTriggerOnKey);
			if(Options.Legitbot.Trigger.Pistols.bTriggerOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Trigger.Pistols.iTriggerKey, ImVec2(150, 20));
			/*ImGui::Text("Delay in");
			ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Pistols.iTriggerDelay, 10, 250, "%0.f");*/
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Pistols.bTriggerRecoil);
			ImGui::Separator();
			ImGui::Checkbox("Auto Revolver", &Options.Legitbot.Trigger.Pistols.bAutoRevolver);
			ImGui::Checkbox("Revolver Secondary Fire", &Options.Legitbot.Trigger.Pistols.bRevolverSecondary);
			ImGui::Checkbox("Auto Pistol", &Options.Legitbot.Trigger.Pistols.bAutoPistol);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Pistols.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Pistols.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Pistols.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Pistols.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Pistols.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Pistols.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

	if (Global::LegitSubTab == 1)
	{
		ImGui::BeginChild("Smgs##aimbot", ImVec2(200, 398), true);
		{

			ImGui::Text("Aimbot - Smgs");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Smgs.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Smgs.bOnKey);
			if (Options.Legitbot.Aimbot.Smgs.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Smgs.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Smgs.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Smgs.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Smgs.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Smgs.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Smgs##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Smgs");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Smgs.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Smgs.bTriggerOnKey);
			if (Options.Legitbot.Trigger.Smgs.bTriggerOnKey)
				ImGui::Hotkey("##smgskey", &Options.Legitbot.Trigger.Smgs.iTriggerKey, ImVec2(150, 20));
			//ImGui::Text("Delay in");
			//ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Smgs.iTriggerDelay, 10, 250, "%0.f");
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Smgs.bTriggerRecoil);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Smgs.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Smgs.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Smgs.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Smgs.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Smgs.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Smgs.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

	if (Global::LegitSubTab == 2)
	{
		ImGui::BeginChild("Rifles##aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot - Rifles");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Rifles.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Rifles.bOnKey);
			if (Options.Legitbot.Aimbot.Rifles.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Rifles.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Rifles.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Rifles.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Rifles.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Rifles.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Rifles##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Rifles");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Rifles.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Rifles.bTriggerOnKey);
			if (Options.Legitbot.Trigger.Rifles.bTriggerOnKey)
				ImGui::Hotkey("##rifleskey", &Options.Legitbot.Trigger.Rifles.iTriggerKey, ImVec2(150, 20));
			//ImGui::Text("Delay in");
			//ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Rifles.iTriggerDelay, 10, 250, "%0.f");
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Rifles.bTriggerRecoil);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Rifles.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Rifles.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Rifles.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Rifles.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Rifles.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Rifles.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

	if (Global::LegitSubTab == 3)
	{
		ImGui::BeginChild("Shotguns##aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot - Shotguns");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Shotguns.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Shotguns.bOnKey);
			if (Options.Legitbot.Aimbot.Shotguns.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Shotguns.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Shotguns.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Shotguns.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Shotguns.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Shotguns.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Shotguns##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Shotguns");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Shotguns.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Shotguns.bTriggerOnKey);
			if (Options.Legitbot.Trigger.Shotguns.bTriggerOnKey)
				ImGui::Hotkey("##Shotgunskey", &Options.Legitbot.Trigger.Shotguns.iTriggerKey, ImVec2(150, 20));
			//ImGui::Text("Delay in");
			//ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Shotguns.iTriggerDelay, 10, 250, "%0.f");
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Shotguns.bTriggerRecoil);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Shotguns.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Shotguns.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Shotguns.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Shotguns.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Shotguns.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Shotguns.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

	if (Global::LegitSubTab == 4)
	{
		ImGui::BeginChild("Heavy##aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot - Heavy");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Heavy.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Heavy.bOnKey);
			if (Options.Legitbot.Aimbot.Heavy.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Heavy.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Heavy.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Heavy.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Heavy.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Heavy.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Heavy##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Heavy");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Heavy.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Heavy.bTriggerOnKey);
			if (Options.Legitbot.Trigger.Heavy.bTriggerOnKey)
				ImGui::Hotkey("##Heavykey", &Options.Legitbot.Trigger.Heavy.iTriggerKey, ImVec2(150, 20));
			//ImGui::Text("Delay in");
			//ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Heavy.iTriggerDelay, 10, 250, "%0.f");
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Heavy.bTriggerRecoil);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Heavy.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Heavy.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Heavy.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Heavy.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Heavy.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Heavy.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

	if (Global::LegitSubTab == 5)
	{
		ImGui::BeginChild("Snipers##aimbot", ImVec2(200, 398), true);
		{
			ImGui::Text("Aimbot - Snipers");
			ImGui::Separator();
			ImGui::Checkbox("Enable Aimbot", &Options.Legitbot.Aimbot.Snipers.bEnableAimbot);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Aimbot.Snipers.bOnKey);
			if (Options.Legitbot.Aimbot.Snipers.bOnKey)
				ImGui::Hotkey("##pistolkey", &Options.Legitbot.Aimbot.Snipers.iKey, ImVec2(150, 20));
			ImGui::Separator();
			ImGui::Text("Hitbox");
			ImGui::Combo("##hitbox", &Options.Legitbot.Aimbot.Snipers.iAimbotHitbox, iHitboxLegit, ARRAYSIZE(iHitboxLegit));
			ImGui::Checkbox("Silent Aim", &Options.Legitbot.Aimbot.Snipers.bSilentAim);
			ImGui::Text("Aimbot Fov");
			ImGui::SliderFloat("Degrees##fov", &Options.Legitbot.Aimbot.Snipers.iAimbotFov, 0.0, 20, "%.1f");
			ImGui::Text("Aimbot Rcs");
			ImGui::SliderFloat("%##rcs", &Options.Legitbot.Aimbot.Snipers.flAimbotRecoil, 0, 100, "%.0f", 1.0f);

		}ImGui::EndChild();
		ImGui::SameLine();
		ImGui::BeginChild("Snipers##trigger", ImVec2(200, 398), true);
		{
			ImGui::Text("Trigger - Snipers");
			ImGui::Separator();
			ImGui::Checkbox("Enable", &Options.Legitbot.Trigger.Snipers.bEnableTrigger);
			ImGui::SameLine();
			ImGui::Checkbox("On Key", &Options.Legitbot.Trigger.Snipers.bTriggerOnKey);
			if (Options.Legitbot.Trigger.Snipers.bTriggerOnKey)
				ImGui::Hotkey("##sniperskey", &Options.Legitbot.Trigger.Snipers.iTriggerKey, ImVec2(150, 20));
			//ImGui::Text("Delay in");
			//ImGui::SliderInt("ms", &Options.Legitbot.Trigger.Snipers.iTriggerDelay, 10, 250, "%0.f");
			ImGui::Checkbox("Rcs", &Options.Legitbot.Trigger.Snipers.bTriggerRecoil);
			ImGui::Checkbox("Scoped Check", &Options.Legitbot.Trigger.Snipers.bScoped);
			ImGui::Separator();
			ImGui::Text("Trigger - Filter");
			ImGui::Separator();
			ImGui::Checkbox("Full Body", &Options.Legitbot.Trigger.Snipers.bTriggerFullBody);
			ImGui::Checkbox("Head", &Options.Legitbot.Trigger.Snipers.bTriggerHead);
			ImGui::Checkbox("Chest", &Options.Legitbot.Trigger.Snipers.bTriggerChest);
			ImGui::Checkbox("Stomach", &Options.Legitbot.Trigger.Snipers.bTriggerStomach);
			ImGui::Checkbox("Arms", &Options.Legitbot.Trigger.Snipers.bTriggerArms);
			ImGui::Checkbox("Legs", &Options.Legitbot.Trigger.Snipers.bTriggerLegs);
		}ImGui::EndChild();
		ImGui::SameLine();
	}

}

void DrawVisualsTab()
{
	auto& style = ImGui::GetStyle();
	BtnNormal();

	style.ItemSpacing = ImVec2(0, 4);
	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);

	style.WindowPadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(4, 4);

	ImGui::BeginChild("ESP - General", ImVec2(190, 398), true);
	{
		ImGui::Text("ESP - Main");
		ImGui::Separator();
		ImGui::Checkbox("Box", &Options.Visuals.Esp.EspBox.bBox);
		ImGui::Checkbox("Name", &Options.Visuals.Esp.EspMisc.bName);
		ImGui::Checkbox("Health", &Options.Visuals.Esp.EspBox.bHealthbar);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("HP Text", &Options.Visuals.Esp.EspBox.bHealthText);
		ImGui::Checkbox("Armor", &Options.Visuals.Esp.EspBox.bArmorBar);
		ImGui::Checkbox("Player Weapon", &Options.Visuals.Esp.EspMisc.bWeapons);
		ImGui::Checkbox("Player Ammo", &Options.Visuals.Esp.EspMisc.bAmmo);
		ImGui::Checkbox("Skeleton", &Options.Visuals.Esp.EspBox.bSkeleton);
		ImGui::Checkbox("Snaplines", &Options.Visuals.Esp.EspBox.bAimlines);
		//ImGui::Checkbox("Visible Only", &Options.Visuals.Esp.EspFilter.bXQZ);  // DOES NOT WORK
		ImGui::Checkbox("Enemy Only", &Options.Visuals.Esp.EspFilter.bEnemyOnly);
		ImGui::Checkbox("Planted C4", &Options.Visuals.Esp.EspFilter.bC4);
		ImGui::Checkbox("Hostages", &Options.Visuals.Esp.EspFilter.bHostage);
		ImGui::Checkbox("Is Scoped", &Options.Visuals.Esp.EspMisc.bIsScoped);
		ImGui::Checkbox("Is Flashed", &Options.Visuals.Esp.EspMisc.bIsFlashed);
		ImGui::Checkbox("Dropped Weapons", &Options.Visuals.Esp.EspFilter.bDroppedWeapons);
		ImGui::Checkbox("Pitch", &Options.Visuals.Esp.EspBox.bPitch);
		ImGui::Checkbox("Yaw", &Options.Visuals.Esp.EspBox.bYaw);
	}ImGui::EndChild();

	ImGui::SameLine();

	ImGui::BeginChild("ESP - Misc", ImVec2(190, 398), true);
	{
		ImGui::Text("ESP - Extra");
		ImGui::Separator();
		ImGui::Text("Thirperson");
		ImGui::Combo("##tp", &Options.Visuals.VisualsMisc.iThirdPerson, iThirdperson, ARRAYSIZE(iThirdperson));
		ImGui::Hotkey("##dfgedrtes", &Options.Visuals.VisualsMisc.iThirdPersonKey, ImVec2(150, 20));
		//ImGui::SliderFloat("Thirdperson Modifier:", &Options.Visuals.VisualsMisc.flThirdPersonRange, 0.f, 800.f, "%.0f", 1.0f);
		ImGui::Separator();
		ImGui::Checkbox("Hitmarker", &Options.Visuals.VisualsMisc.bHitMarker);
		ImGui::Text("Hitsound");
		ImGui::Combo("##hitsound", &Options.Visuals.VisualsMisc.iHitsound, iHitSound, ARRAYSIZE(iHitSound));
		ImGui::Text("Killsound");
		ImGui::Combo("##killsound", &Options.Visuals.VisualsMisc.iKillsound, iKillSound, ARRAYSIZE(iKillSound));
		ImGui::Checkbox("Remove Scope", &Options.Visuals.VisualsMisc.bScopeRemover);
		ImGui::Checkbox("Remove Flashes", &Options.Visuals.VisualsWorlds.bNoFlash);
		ImGui::Checkbox("Remove Smokes", &Options.Visuals.VisualsWorlds.bNoSmoke);
		ImGui::Checkbox("Remove Visual Recoil", &Options.Visuals.VisualsMisc.bNoVisualRecoil);
		ImGui::Separator();
		ImGui::Text("Infobox");
		ImGui::Separator();
		ImGui::Checkbox("Show Infobox", &Options.Visuals.Infobox.bInfoBox);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Add LBY Status", &Options.Visuals.Infobox.bInfoLby);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Add Velocity", &Options.Visuals.Infobox.bInfoVelocity);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Add Viewangles", &Options.Visuals.Infobox.bInfoAngles);
		ImGui::NewLine();
		ImGui::SameLine(28);
	}ImGui::EndChild();

	ImGui::SameLine();
	ImGui::BeginChild("Visuals - Misc", ImVec2(190, 398), true);
	{
		ImGui::Text("Visuals - Misc");
		ImGui::Separator();
		ImGui::Checkbox("Enable Crosshairs", &Options.Visuals.VisualsMisc.bCrosshair);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Normal", &Options.Visuals.VisualsMisc.bNormalCrosshair);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Recoil", &Options.Visuals.VisualsMisc.bRecoilCrosshair);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Spread", &Options.Visuals.VisualsMisc.bSpreadCrosshair);
		ImGui::Checkbox("Force Enable Radar", &Options.Visuals.VisualsMisc.bEngineRadar);
		ImGui::Checkbox("Watermark", &Options.Visuals.VisualsMisc.bWatermark);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Local Time", &Options.Visuals.VisualsMisc.bTime);
		ImGui::Checkbox("Rank Reveal", &Options.Visuals.VisualsMisc.bRankReveal);
		ImGui::Checkbox("Spectator List", &Options.Visuals.VisualsMisc.bSpecList);
		ImGui::Checkbox("Nightmode", &Options.Visuals.VisualsWorlds.bNightMode);
		ImGui::Checkbox("Asus Walls", &Options.Visuals.VisualsWorlds.bAsusWalls);
	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("Chams", ImVec2(190, 398), true);
	{
		ImGui::Text("Chams");
		ImGui::Separator();
		ImGui::Text("	Models");
		ImGui::Separator();
		ImGui::Checkbox("Enable", &Options.Visuals.Chams.bPlayers);
		{
			ImGui::Separator();
			ImGui::Selectable("Flat", &Options.Visuals.Chams.bFlat);
			ImGui::Selectable("Transparent", &Options.Visuals.Chams.bTransparent);
			ImGui::Selectable("Through Walls", &Options.Visuals.Chams.bThroughWalls);
			ImGui::Selectable("Wireframe", &Options.Visuals.Chams.bWireframe);
			ImGui::Selectable("Enemy Only", &Options.Visuals.Chams.bEnemyOnly);
		}
		ImGui::Separator();
		ImGui::Text("	Hands");
		ImGui::Separator();
		ImGui::Checkbox("Enable ", &Options.Visuals.Chams.bArms);
		{
			ImGui::Separator();
			ImGui::Selectable("Flat ", &Options.Visuals.Chams.bArmsFlat);
			ImGui::Selectable("Transparent ", &Options.Visuals.Chams.bArmsTransparent);
			ImGui::Selectable("Through Walls ", &Options.Visuals.Chams.bArmsThroughWalls);
			ImGui::Selectable("Wireframe ", &Options.Visuals.Chams.bArmsWireframe);
			ImGui::Separator();
		}
	}ImGui::EndChild();

}

void DrawMiscTab()
{
	auto& style = ImGui::GetStyle();
	BtnNormal();

	style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);

	style.WindowPadding = ImVec2(8, 8);
	style.ItemSpacing = ImVec2(4, 4);

	ImGui::BeginChild("Misc I", ImVec2(190, 398), true);
	{
		ImGui::Text("Misc I");
		ImGui::Separator();
		ImGui::Text("Fakelag");
		ImGui::Combo("##faglag", &Options.Misc.Misc1.iFakeLag, iFakeLag, ARRAYSIZE(iFakeLag));
		ImGui::Checkbox("In Air Only", &Options.Misc.Misc1.bInAirOnly);
		if(Options.Misc.Misc1.iFakeLag == 1)
			ImGui::SliderInt("Factor", &Options.Misc.Misc1.iFakeLagFactor, 0, 20, "%.0f");
		ImGui::Separator();
		ImGui::Checkbox("Change Clantag", &Options.Misc.Misc1.bClanTag);
		if (Options.Misc.Misc1.bClanTag)
		{
			ImGui::Combo("##clntag", &Options.Misc.Misc1.iClanTagSelection, iClanTag, ARRAYSIZE(iClanTag));
			ImGui::NewLine();
			ImGui::SameLine(28);
			ImGui::Checkbox("Animate Clantag", &Options.Misc.Misc1.bClanTagAnimation);
			ImGui::NewLine();
			ImGui::SameLine(28);
			ImGui::Checkbox("Corruption", &Options.Misc.Misc1.bCorruption);
		}
		ImGui::Separator();
		ImGui::Checkbox("Freecam", &Options.Misc.Misc1.bFreeCam);
		ImGui::SliderFloat("Speed", &Options.Misc.Misc1.flFreeCamSpeed, 5, 25, "%.1f", (1.0F));
		ImGui::Hotkey("Key##freecamkey", &Options.Misc.Misc1.iFreeCamKey, ImVec2(150, 20));

	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("Misc II", ImVec2(190, 398), true);
	{
		ImGui::Text("Misc II");
		ImGui::Separator();
		ImGui::Checkbox("Anti-Untrusted", &Options.Misc.Misc2.bAntiUntrusted);
		ImGui::Checkbox("Chatspam", &Options.Misc.Misc2.bChatSpam);
		ImGui::Text("Name Spam");
		ImGui::Combo("##nmespam", &Options.Misc.Misc2.iNameSpam, iNameSpam, ARRAYSIZE(iNameSpam));
		ImGui::Checkbox("KnifeBot", &Options.Misc.Misc2.bKnifeBot);
		ImGui::Checkbox("Blockbot", &Options.Misc.Misc2.bBlockBot);
		ImGui::Hotkey("##blockbotkey", &Options.Misc.Misc2.iBlockBotKey, ImVec2(150, 20));
		ImGui::Checkbox("Override FOV", &Options.Misc.Misc2.bEnableFov);
		ImGui::SliderFloat("FOV Value", &Options.Misc.Misc2.flFovValue, 30.f, 190.f, "%.f", 1.f);
		ImGui::SliderFloat("viewmodelFOV Value", &Options.Misc.Misc2.flViewModelValue, 30.f, 190.f, "%.f", 1.f);
	}ImGui::EndChild();	
	ImGui::SameLine();
	ImGui::BeginChild("Movements", ImVec2(190, 398), true);
	{
		ImGui::Text("Movement");
		ImGui::Separator();
		ImGui::Checkbox("Bunnyhop", &Options.Misc.Movement.bAutoJump);
		ImGui::Checkbox("Auto Strafe", &Options.Misc.Movement.bAutoStrafe);
		if (Options.Misc.Movement.bAutoStrafe)
		{
			ImGui::Separator();
			ImGui::Text("Strafe Mode");
			ImGui::Combo("##strmd", &Options.Misc.Movement.iAutoStrafeMode, iAutostrafer, ARRAYSIZE(iAutostrafer));
			ImGui::Checkbox("Z-Axis Strafe", &Options.Misc.Movement.bZStrafe);
			ImGui::Hotkey("Key##zstrafekey", &Options.Misc.Movement.iZStrafeKey, ImVec2(150, 20));
			ImGui::Text("Circle Strafer");
			ImGui::Combo("Circle Strafer", &Options.Misc.Movement.iCircleStraferMode, iCircleStrafer, ARRAYSIZE(iCircleStrafer));
			ImGui::Hotkey("Key##cskey", &Options.Misc.Movement.iCircleStraferKey, ImVec2(150, 20));
			ImGui::Separator();
		}
		ImGui::Separator();
		ImGui::Checkbox("Slowmotion", &Options.Misc.Movement.bSlowmotion);
		ImGui::Hotkey("Key##slowmotionkey", &Options.Misc.Movement.iSlowMotionKey, ImVec2(150, 20));
		ImGui::Text("Airstuck");
		ImGui::Combo("##airstuck", &Options.Misc.Movement.iAirStuck, iAirstuck, ARRAYSIZE(iAirstuck));
		ImGui::Hotkey("##key", &Options.Misc.Movement.iAirStuckKey, ImVec2(150, 20));
		ImGui::Checkbox("Walkbot", &Options.Misc.Movement.bWalkBot);
		ImGui::NewLine();
		ImGui::SameLine(28);
		ImGui::Checkbox("Bunnyhop", &Options.Misc.Movement.bBunnyhop);
		ImGui::Text("Distance to Wall");
		ImGui::SliderFloat("%##float", &Options.Misc.Movement.flDistance, 0, 500, "%.1f", (1.0f));
		ImGui::Text("Degrees Turn");
		ImGui::SliderInt("%##int", &Options.Misc.Movement.iTurn, -180, 180, "%.1f");
		ImGui::Separator();
	}ImGui::EndChild();
	ImGui::SameLine();
	ImGui::BeginChild("cfg", ImVec2(190, 398), true);
	{
		ImGui::Text("Config");
		ImGui::Separator();
		if (ImGui::Button("Save"))
			Config->Save();
		ImGui::SameLine();
		if (ImGui::Button("Load"))
			Config->Load();
		ImGui::SameLine();
		if (ImGui::Button("Unload"))
			Unhook();		
	}ImGui::EndChild();
}

void DrawColorsTab()
{
	ImGui::BeginChild("##visualscolors", ImVec2(772, 434), true);
	{
		static int selectedItem = 0;

		ImVec2 lastCursor = ImGui::GetCursorPos();

		auto& style = ImGui::GetStyle();
		BtnNormal();

		style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);

		style.WindowPadding = ImVec2(8, 8);
		style.ItemSpacing = ImVec2(4, 4);

		ImGui::ListBoxHeader("##Colors - Visuals", ImVec2(320, 418));

		for (int i = 0; i < Global::ColorsForPicker.size(); i++)
		{
			bool selected = i == selectedItem;

			if (ImGui::Selectable(Global::ColorsForPicker[i].Name, selected))
				selectedItem = i;
		}
		ImGui::ListBoxFooter();


		float nc = lastCursor.x + 260;
		ImGui::SetCursorPos(ImVec2(nc, lastCursor.y));

		ColorP col = Global::ColorsForPicker[selectedItem];
		int r = (col.Ccolor[0] * 255.f);
		int g = (col.Ccolor[1] * 255.f);
		int b = (col.Ccolor[2] * 255.f);

		bool wip;

		style.Colors[ImGuiCol_Text] = ImVec4(0.98f, 0.98f, 0.98f, 1.f);
		ImGui::SetCursorPosX(nc);
		

		col.Ccolor[0] = r / 255.f;
		col.Ccolor[1] = g / 255.f;
		col.Ccolor[2] = b / 255.f;

		ImGui::SameLine();

		ImVec2 curPos = ImGui::GetCursorPos();
		ImVec2 curWindowPos = ImGui::GetWindowPos();
		curPos.x += curWindowPos.x;
		curPos.y += curWindowPos.y;

		ImGui::PushItemWidth(372);
		ImGui::ColorPicker3("##clr", col.Ccolor);

	}ImGui::EndChild();


}


HRESULT __stdcall Hooked_EndScene(IDirect3DDevice9* pDevice)
{
	static ConVar* convar;
	//VMTD3D.ReHook();

	if (!Global::MenuInit)
	{
		Gui_Init(pDevice);
		convar = Interfaces.g_ICVars->FindVar("cl_mouseenable");
	}
	ImGui::GetIO().MouseDrawCursor = Global::MenuOpen;

	ImGui_ImplDX9_NewFrame();
	auto& style = ImGui::GetStyle();
	int W, H;
	Interfaces.pEngine->GetScreenSize(W, H);

	DefineTab();

	if (Global::MenuOpen)
	{
		if (style.Alpha > 1.f)
			style.Alpha = 1.f;
		else if (style.Alpha != 1.f)
			style.Alpha += 0.01f;

		style.WindowMinSize = ImVec2(0, 0);
		ImGui::PushFont(Global::fDefault);
		int w;
		int h;
		style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 1.00f);
		ImVec2 mainWindowPos; // wir brauchen die main window pos um nen vernünftigen border zu drawen

		Interfaces.pEngine->GetScreenSize(w, h);

		//Erstmal drawen wir das main menu
		ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiSetCond_Appearing);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1, 0.1f, 1.f);
		ImGui::Begin("##bg", &Global::MenuOpen, ImVec2(W, H), .5f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar);
		{

		}ImGui::End();



		style.WindowPadding = ImVec2(1, 1);
		style.Colors[ImGuiCol_Button] = ImVec4(0.54, 0., 0.54, 1.f);
		style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.54, 0., 0.54, 1.f);
		style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.54, 0., 0.54, 1.f);
		ImGui::SetNextWindowSize(ImVec2(800, 20));
		ImGui::Begin("Astrium.cc", &Global::MenuOpen, ImVec2(800, 0), 1.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse |  ImGuiWindowFlags_ShowBorders);
		{
			mainWindowPos = ImGui::GetWindowPos();
			//ImGui::Button("Astrium.cc", ImVec2(798, 8));
		}ImGui::End();

		// Als Border machen wir ein 3-lagigen: farbe-grau
		style.WindowPadding = ImVec2(8, 8);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
		ImGui::SetNextWindowPosCenter(ImGuiSetCond_Appearing);
		ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x + 6, mainWindowPos.y + 80));
		BtnNormal();
		//style.WindowPadding = ImVec2(0, 0);


		ImGui::Begin("Hurensohn Visual Studio", &Global::MenuOpen, ImVec2(788, 450), 0.98f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_ShowBorders);
		{
			//mainWindowPos = ImGui::GetWindowPos();

			if (Global::MenuTab == 0)
				DrawRageTab();
			if (Global::MenuTab == 1)
				DrawLegitTab();
			if (Global::MenuTab == 2)
				DrawVisualsTab();
			if (Global::MenuTab == 3)
				DrawMiscTab();
			if (Global::MenuTab == 4)
				DrawMiscTab();
			if (Global::MenuTab == 5)
			DrawColorsTab();
		}ImGui::End();

		ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x, mainWindowPos.y + 26));
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.20f, 0.20f, 0.20f, 1.f);
		ImGui::Begin("##border2", &Global::MenuOpen, ImVec2(800, 510), 0.98f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoInputs | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_ShowBorders);
		{

		}ImGui::End();

		// So jetzt die tabs



		ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x + 6, mainWindowPos.y + 32));
		style.Colors[ImGuiCol_WindowBg] = ImVec4(1.f, 1.f, 1.f, 0.f);
		style.WindowPadding = ImVec2(0, 0);
		style.ItemSpacing = ImVec2(4, 0);
		ImGui::SetNextWindowSize(ImVec2(788, 42));
		ImGui::Begin("##tabarea", &Global::MenuOpen, ImVec2(788, 42), 0.f, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_ShowBorders);
		{
			if (Global::MenuTab == 0) BtnActive(); else BtnNormal();
			if (ImGui::Button("RAGEBOT", ImVec2(128, 42))) Global::MenuTab = 0;
			ImGui::SameLine();
			if (Global::MenuTab == 1) BtnActive(); else BtnNormal();
			if (ImGui::Button("LEGITBOT", ImVec2(128, 42))) Global::MenuTab = 1;
			ImGui::SameLine();
			if (Global::MenuTab == 2) BtnActive(); else BtnNormal();
			if (ImGui::Button("VISUALS", ImVec2(128, 42))) Global::MenuTab = 2;
			ImGui::SameLine();
			if (Global::MenuTab == 3) BtnActive(); else BtnNormal();
			if (ImGui::Button("MISC", ImVec2(128, 42))) Global::MenuTab = 3;
			ImGui::SameLine();
			if (Global::MenuTab == 4) BtnActive(); else BtnNormal();
			if (ImGui::Button("SKINS", ImVec2(128, 42))) Global::MenuTab = 4;
			ImGui::SameLine();
			if (Global::MenuTab == 5) BtnActive(); else BtnNormal();
			if (ImGui::Button("COLORS", ImVec2(128, 42))) Global::MenuTab = 5;
			// lila


		}ImGui::End();

		if (Global::MenuTab == 0)
		{
			if (Global::curLil > 0)
				Global::curLil -= 2;
		}
		else if (Global::MenuTab == 1)
		{
			if (Global::curLil > 132)
				Global::curLil -= 2;
			else if (Global::curLil < 132)
				Global::curLil += 2;
		}
		else if (Global::MenuTab == 2)
		{
			if (Global::curLil > 264)
				Global::curLil -= 2;
			else if (Global::curLil < 264)
				Global::curLil += 2;
		}
		else if (Global::MenuTab == 3)
		{
			if (Global::curLil > 396)
				Global::curLil -= 2;
			else if (Global::curLil < 396)
				Global::curLil += 2;
		}
		else if (Global::MenuTab == 4)
		{
			if (Global::curLil > 528)
				Global::curLil -= 2;
			else if (Global::curLil < 528)
				Global::curLil += 2;
		}
		else if (Global::MenuTab == 5)
		{
			if (Global::curLil > 660)
				Global::curLil -= 2;
			else if (Global::curLil < 660)
				Global::curLil += 2;
		}

		ImGui::SetNextWindowPos(ImVec2(mainWindowPos.x + 6 + Global::curLil, mainWindowPos.y + 72), ImGuiSetCond_Always);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(1.f, 1.f, 1.f, 0.f);
		style.Colors[ImGuiCol_Border] = ImVec4(0.27f, 0.27f, .27f, 0.00f);
		style.WindowPadding = ImVec2(0, 0);
		style.ItemSpacing = ImVec2(0, 0);
		ImGui::Begin("##tabarea", &Global::MenuOpen, ImVec2(500, 7), 0.f, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoTitleBar);
		{
			// lila

			style.Colors[ImGuiCol_Button] = ImVec4(0.54, 0., 0.54, 1.f);
			style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.54, 0., 0.54, 1.f);
			style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.54, 0., 0.54, 1.f);

			ImGui::Button("##ggffghgf", ImVec2(Global::curLil + 128, 6));

		}ImGui::End();

		//background

	}
	else
	{
		if (style.Alpha < 0.f)
			style.Alpha = 0.f;
		else if (style.Alpha != 0.f)
			style.Alpha -= 0.01f;
	}

	if (Options.Visuals.Infobox.bInfoBox)
	{
		style.Alpha = 1.f;
		ImGui::PushFont(Global::fDefault);
		int lbyred = 0;
		int lbygreen = 0;
		style.WindowMinSize = ImVec2(210, 40);
		style.WindowPadding = ImVec2(8, 8);
		style.ItemSpacing = ImVec2(4, 4);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
		ImGui::Begin("Infobox", &Options.Visuals.Infobox.bInfoBox, ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
		{
			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Hacks.LocalPlayer->isAlive())
			{
				if (!(Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() >= -35 && Hacks.CurrentCmd->viewangles.y - Hacks.LocalPlayer->pelvisangs() <= 35))
				{
					lbygreen = 1;
					lbyred = 0;
				}
				else
				{
					lbyred = 1;
					lbygreen = 0;
				}

				if (Options.Visuals.Infobox.bInfoLby)
				{
					ImGui::Text("LBY Status:");
					ImGui::SameLine();
					ImGui::TextColored(ImVec4(lbyred, lbygreen, 0, 1.f), "[BROKEN]");
				}

				if (Options.Visuals.Infobox.bInfoVelocity)
				{
					int velocity = Hacks.LocalPlayer->GetVecVelocity().Length2D();
					ImGui::TextColored(ImVec4(0.97, 0.97, 0, 1), "Velocity: %i", velocity);
				}

				if (Options.Visuals.Infobox.bInfoAngles)
				{
					int anglereal = Global::curReal;
					int anglefake = Global::curFake;
					int lby = Hacks.LocalPlayer->pelvisangs();
					int pitch = Hacks.LocalPlayer->GetEyeAngles().x;
					bool sendpacket = Hacks.SendPacket;

					ImGui::Text("LBY:"); ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.97, 0, 1), "%i", lby);
					ImGui::SameLine();

					ImGui::Text("Real:"); ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.97, 0, 1), "%i", anglereal);
					ImGui::SameLine();

					ImGui::Text("Fake:"); ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.97, 0, 1), "%i", anglefake);

					ImGui::Text("Pitch:"); ImGui::SameLine();
					ImGui::TextColored(ImVec4(0, 0.97, 0, 1), "%i", pitch);

					ImGui::Text("Packet Status: ");
					ImGui::SameLine();
					if (sendpacket)
						ImGui::TextColored(ImVec4(0.97, 0, 0, 1.f), "Sending");
					else
						ImGui::TextColored(ImVec4(0, 0.97, 0, 1.f), "Choking");

				}

			}
		}ImGui::End();
	}

	/*if (Options.Visuals.VisualsMisc.bSpecList)
	{
		int specs = 0;
		std::string spect = "";
		ImGui::PushFont(Global::fDefault);
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
		{
			int localindex = Interfaces.pEngine->GetLocalPlayer();
			if (Hacks.LocalPlayer)
			{
				for (int i = 0; i < Interfaces.pEngine->GetMaxClients(); i++)
				{
					CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity(i);
					if (!pEntity)
						continue;
					if (pEntity->GetHealth() > 0)
						continue;
					if (pEntity == Hacks.LocalPlayer)
						continue;
					if (pEntity->IsDormant())
						continue;
					if (pEntity->GetObserverTarget() != Hacks.LocalPlayer)
						continue;

					player_info_t pInfo;
					Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &pInfo);
					if (pInfo.ishltv)
						continue;

					spect += pInfo.name;
					spect += "\n";
					specs++;

				}

				style.WindowMinSize = ImVec2(210, 40);
				style.WindowPadding = ImVec2(8, 8);
				style.ItemSpacing = ImVec2(4, 4);
				style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
				ImGui::Begin("Spectator List", &Options.Visuals.Infobox.bInfoBox, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_ShowBorders);
				{
					if (specs > 0) spect += "Noone spectates NoNames";
					ImVec2 siz = ImGui::CalcTextSize(spect.c_str());
					ImGui::SetWindowSize(ImVec2(200, 20 + siz.y));
					ImGui::Text(spect.c_str());
				}ImGui::End();
			}
		}
	}*/

	/*if (Options.Visuals.Infobox.bPlayerBox)
	{
		style.Alpha = 1.f;
		ImGui::PushFont(Global::fDefault);
		int lbyred = 0;
		int lbygreen = 0;
		style.WindowMinSize = ImVec2(210, 40);
		style.WindowPadding = ImVec2(8, 8);
		style.ItemSpacing = ImVec2(4, 4);
		style.Colors[ImGuiCol_WindowBg] = ImVec4(0.1f, 0.1f, 0.1f, 0.95f);
		if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() && Hacks.LocalPlayer->isAlive())
			if (ImGui::Begin("Playerbox", &Options.Visuals.Infobox.bPlayerBox, ImVec2(200, 250), 1.0f, ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_ShowBorders | ImGuiWindowFlags_NoResize))
			{
				ImDrawList* windowDrawList = ImGui::GetWindowDrawList();

				ImVec2 siz = ImGui::GetWindowSize();
				ImVec2 pos = ImGui::GetWindowPos();
				CBaseCombatWeapon* LocalWeapon;

				float accuracy = Hacks.LocalPlayer->GetActiveBaseCombatWeapon->UpdateAccuracyPenalty() * 3000.f;
				if (accuracy > 179)
					accuracy = 179;

				int iSpeed = 0;
				Vector vSpeed = Hacks.LocalPlayer->GetVecVelocity();
				iSpeed = (int)vSpeed.Length2D();

				int iSpeed2 = 0;
				Vector vSpeed2 = Hacks.LocalPlayer->GetVecVelocity();
				iSpeed2 = (int)vSpeed2.Length2D() - 300;

				float flPunch = 0.0f;
				Vector vRecoil = Hacks.LocalPlayer->GetPunchAngle();
				flPunch = (float)vRecoil.Length2D();

				if (iSpeed < 300)
					windowDrawList->AddText(ImVec2(pos.x + 25, pos.y + 1 + 217), Color(255, 255, 255, 255).GetU32(), "Speed");
				if (iSpeed > 300)
					windowDrawList->AddText(ImVec2(pos.x + 25, pos.y + 1 + 217), Color(255, 0, 0, 255).GetU32(), "Boost");
				windowDrawList->AddText(ImVec2(pos.x + 85, pos.y + 1 + 217), Color(255, 255, 255, 255).GetU32(), "Recoil");
				windowDrawList->AddText(ImVec2(pos.x + 145, pos.y + 1 + 217), Color(255, 255, 255, 255).GetU32(), "Spread");

				windowDrawList->AddRect(ImVec2(pos.x + 147, pos.y + 35), ImVec2(pos.x + 147 + 25, pos.y + 35 + 180), Color(0, 0, 0, 255).GetU32());
				windowDrawList->AddRect(ImVec2(pos.x + 87, pos.y + 35), ImVec2(pos.x + 87 + 25, pos.y + 35 + 180), Color(0, 0, 0, 255).GetU32());
				windowDrawList->AddRect(ImVec2(pos.x + 28, pos.y + 35), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), Color(0, 0, 0, 255).GetU32());

				if (iSpeed < 300)
					windowDrawList->AddRectFilled(ImVec2(pos.x + 28, pos.y + 35 + 180 - (iSpeed * 0.6)), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), Color(255, 255, 255, 255).GetU32());

				if (iSpeed > 300)
					windowDrawList->AddRectFilled(ImVec2(pos.x + 28, pos.y + 35 + 180 - (iSpeed2 * 0.2)), ImVec2(pos.x + 28 + 25, pos.y + 35 + 180), Color(255, 0, 0, 255).GetU32());

				windowDrawList->AddRectFilled(ImVec2(pos.x + 147, pos.y + 35 + 180 - accuracy), ImVec2(pos.x + 147 + 25, pos.y + 35 + 180), Color(255, 255, 255, 255).GetU32());
				windowDrawList->AddRectFilled(ImVec2(pos.x + 87, pos.y + 35 + 180 - flPunch * 30), ImVec2(pos.x + 87 + 25, pos.y + 35 + 180), Color(255, 255, 255, 255).GetU32());
				ImGui::End();
			}
	}*/

	ImGui::Render();
	return Hacks.oEndScene(pDevice);
}

HRESULT __stdcall Hooked_Reset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam)
{
	if (!Global::MenuInit)
		return Hacks.oResetScene(pDevice, pPresParam);

	ImGui_ImplDX9_InvalidateDeviceObjects();

	return Hacks.oResetScene(pDevice, pPresParam);

	ImGui_ImplDX9_CreateDeviceObjects();

	return Hacks.oResetScene(pDevice, pPresParam);
}
