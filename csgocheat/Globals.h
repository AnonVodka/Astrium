#pragma once

#include "Hooks.h"
#include "Options.h"
#include "ImGUI/imgui.h"
#include "ImGUI/DX9/imgui_impl_dx9.h"


namespace Global
{
	extern bool MenuInit;
	extern bool MenuOpen;
	extern int curLil;
	extern int curLilLegit;
	extern ImFont* fDefault;
	extern ImFont* fTabs;
	extern ImFont* fSubTabs;
	extern int MenuTab;
	extern int RageSubTab;
	extern int VisSubTab;
	extern int LegitSubTab;
	extern const char* configpath;
	extern std::vector<ColorP> ColorsForPicker;
	extern Vector LastAngle;
	extern bool lbyupdate;
	extern float curReal;
	extern float curFake;
	extern float hitmarkerAlpha;
}