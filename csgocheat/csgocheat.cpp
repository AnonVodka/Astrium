#include "stdafx.h"
#include "Tools/Hacks/Misc.h"
 

bool Unhook_Cheat = false;
auto ExitCheat() -> bool;

void Unhook()
{
	Unhook_Cheat = true;
}

bool ExitCheat()
{
	if( !Unhook_Cheat )
		return false;

	Interfaces.pEngine->ClientCmd_Unrestricted( "clear", 0 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "echo Astrium has Exited", 0 );

	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_mouseenable 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 1", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
	Sleep( 100 );
	Interfaces.pEngine->ClientCmd_Unrestricted( "cl_drawhud 1", 0 );
	Sleep( 100 );

	if( Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected() )
	{
		Misc::SetClanTag( "", Hacks.LocalPlayer->GetName().c_str() );
		Sleep( 100 );
	}

	Hacks.UnHook();
	Sleep( 200 );

	SetWindowLongPtr( INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >( INIT::OldWindow ) );
	Sleep( 200 );

	FreeLibraryAndExitThread( INIT::Dll, 0 );
}

void WINAPI CheatMain()
{
	//AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);
	SetConsoleTitle("Astrium.cc Debug Console");
	Interfaces.InitialiseSDK();

	auto BuildNumber = Interfaces.pEngine->GetEngineBuildNumber();

	CNetvarManager::Instance()->CreateDatabase();
	Hacks.Hook();

	if (BuildNumber != 13604)
	{
		Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("crosshair 1", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("clear", 0);		

		
		
		Hacks.UnHook();
		Sleep(200);
		MessageBox(0, "Outdated version detected, please try again later", "Astrium.cc", MB_OK);
		SetWindowLongPtr(INIT::Window, GWL_WNDPROC, reinterpret_cast< LONG_PTR >(INIT::OldWindow));
		Sleep(200);

		FreeLibraryAndExitThread(INIT::Dll, 0);
	}
	else
	{
		Interfaces.pEngine->ClientCmd_Unrestricted("toggleconsole", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("net_graph 1", 0);
		Sleep(100);
		Interfaces.pEngine->ClientCmd_Unrestricted("clear", 0);
/*		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated:  30.08.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Quick-Stop", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Aimbot", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Hitchance", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 31.08.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Walkbot", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Airstuck", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 01.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Improved/Changed Anti Aims", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Semi-invis Model for Thirdperson", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Removed Jitter Range", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added PVS Fix", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Removed Skybox Changer", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Bug in Delta Resolver", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 02.09.17" , 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Cleaned Config.cpp", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 03.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Cleaned up visuals tab", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Delta resolver crashing", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Changed Health/Armor Bar Style", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 04.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Hitsound", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Killsound", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Changed Thirdperson Ghostmodel", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 06.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Changed Nightmode colors", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 07.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Thirdperson Key", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Thirdperson Modifier", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Made Thirdperson Ghostmodel more see through", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Made all thirdperson features disable on death", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 07.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Auto Revolver", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added New Resolver (Couldn't test them because cs updated and every server was outdated ,-,)", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Yaw and Pitch show option for box", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Bullettracer (Code commented out coz crashing)", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Changed the Menu a bit", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Removed Thirdperson Modifier coz not working", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Changed Asuswalls", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);*/
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo Astrium DEV-LOG | Updated: 011.09.17", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Patched issue with thirdperson updating", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Fixed Size/Spacing of healthbar lines", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Bound Autoscope to aimbot", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo + Added Backwards Jitter Fake Anti-Aim", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo - Removed build date from watermark", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo  ", 0);
		Interfaces.pEngine->ClientCmd_Unrestricted("echo -----------------------------------------------", 0);
		Sleep(100);
		Interfaces.pEngine->ClientCmd_Unrestricted("crosshair 1", 0);

		while (!Unhook_Cheat)
		{
			Misc::ServerRankReveal();
			Sleep(15);
		}

		ExitCheat();
	}
	return;
}
