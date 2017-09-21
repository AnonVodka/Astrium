#pragma once

#define WIN32_LEAN_AND_MEAN

#include "targetver.h"
#include <windows.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <sstream>
#include <string>
#include <psapi.h>
#include <time.h>
#include <process.h>
#include <vector>
#include <map>
#include <ostream>
#include <Shlobj.h>
#include <stdint.h>
#include <string>
#include <string.h>
#include <cmath>
#include <float.h>
#include <codecvt>
using namespace std;
#include <atlbase.h>
#include <atlcom.h>
#include <sapi.h>
#include <algorithm>
#include <iterator>

#include "SDK/SDK Headers/IEffects.h"

/* Some other shit */
#include "ConsoleColours.h"
#include "Tools/Menu/SettingsManager.h"

void WINAPI CheatMain();

#include "VMTManager.h"
extern VTHookManager VMTPanel;
extern VTHookManager VMTD3D;
extern VTHookManager VMTClient;
extern VTHookManager VMTEngine;
extern VTHookManager VMTModelRender;
extern VTHookManager VMTGameEventManager;
extern VTHookManager VMTSurface;

/*SDK*/
#include "SDK/Math/Vectors.h"
#include "SDK/Math/Math.h"
#include "Utils/Utils.h"
#include "SDK/SDK.h"

/* Cheat And Hooks */
class CHackManager;
extern CHackManager Hacks;

namespace INIT
{
	extern HMODULE Dll;
	extern HWND Window;
	extern WNDPROC OldWindow;
}

#include "Tools/Menu/Controls.h"
#include "Hooks.h"
