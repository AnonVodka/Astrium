// dllmain.cpp : Defines the entry point for the DLL application.
#include "stdafx.h"
//#include "Config.h"
#include "Globals.h"

void SetupColors()
{
	Global::ColorsForPicker.push_back(ColorP("Terrorist - Box Visible", Options.Col.espVisT));
	Global::ColorsForPicker.push_back(ColorP("Terrorist - Box Invisible", Options.Col.espInvisT));
	Global::ColorsForPicker.push_back(ColorP("Counter - Terrorist - Box Visible", Options.Col.espVisCT));
	Global::ColorsForPicker.push_back(ColorP("Counter - Terrorist - Box Invisible", Options.Col.espInvisCT));

	Global::ColorsForPicker.push_back(ColorP("Terrorists - Chams_Visible", Options.Col.chamsPlyrTVis));
	Global::ColorsForPicker.push_back(ColorP("Terrorists - Chams_Invisible", Options.Col.chamsPlyrTInvis));
	Global::ColorsForPicker.push_back(ColorP("Counter_Terrorists - Chams_Visible", Options.Col.chamsPlyrCTVis));
	Global::ColorsForPicker.push_back(ColorP("Counter_Terrorists - Chams_Invisible", Options.Col.chamsPlyrCTInvis));

	Global::ColorsForPicker.push_back(ColorP("Chams - Hands_Visible", Options.Col.chamsHandsVis));
	Global::ColorsForPicker.push_back(ColorP("Chams - Hands_Invisible", Options.Col.chamsHandsInvis));

	Global::ColorsForPicker.push_back(ColorP("Bullet Tracer", Options.Col.bullettracer));
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved )
{
	if( ul_reason_for_call == DLL_PROCESS_ATTACH )
	{
		//CfgManager::SetupPath();

		SetupColors();
		

		while (!(INIT::Window = FindWindowA("Valve001", NULL)))
			Sleep(200);

		INIT::OldWindow = (WNDPROC)SetWindowLongPtr(INIT::Window, GWL_WNDPROC, (LONG_PTR)Hooked_WndProc);

		CreateThread( nullptr, 0, (LPTHREAD_START_ROUTINE)(CheatMain ), nullptr, 0, nullptr );

		INIT::Dll = hModule;

		return TRUE;
	}
	return FALSE;
}
