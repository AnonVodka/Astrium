#pragma once
#include "../../stdafx.h"
#include "../Utils/Hitbox.h"
#include "../Menu/Menu.h"
#include "../Utils/Playerlist.h"
#include "../Menu/SettingsManager.h"
#include "../Utils/HitboxLists.h"
#include "../../SDK/SDK.h"
#include "../../stdafx.h"
#include "../Menu/Menu.h"
#include "../Hacks/Misc.h"
#include "../Hacks/Esp.h"
#include "../Hacks/CreateMoveETC.h"
#include "../Menu/SettingsManager.h"
#include "../../SDK/SDK.h"

vector<Vector> PathingPos;

void LoadPathing()
{
	char path[MAX_PATH];
	char size[8];
	char vecstr[64];
	char itostr[8]; 
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (!Hacks.LocalPlayer)
		return;

	PathingPos.erase(PathingPos.begin(), PathingPos.end());
	sprintf_s(path, _CXR("%s%s_%d.ini"), PathingFile, Interfaces.pEngine->GetLevelName(), Hacks.LocalPlayer->team());
	GetPrivateProfileStringA(_CXR("Points"), _CXR("Size"), "0", size, 8, path);
	int numPoints = atoi(size);
	for (int i = 0; i < numPoints - 1; i++)
	{
		char vecstr[64];
		char itostr[8];
		sprintf_s(itostr, "%d", i);
		GetPrivateProfileStringA(_CXR("Pathing"), _CXR(itostr), _CXR("0.0 0.0 0.0"), vecstr, 64, path);
		std::string PosStr = vecstr;
		string buffer;
		stringstream ss(PosStr);
		vector<string> floats;
		while (ss >> buffer)
			floats.push_back(buffer);

		PathingPos.push_back(Vector(stof(floats[0]), stof(floats[1]), stof(floats[2])));
	}
}

void SavePathing()
{
	char path[MAX_PATH];
	char size[8];
	char vecstr[64];
	char itostr[8];

	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	if (!Hacks.LocalPlayer)
		return;

	sprintf_s(path, _CXR("%s%s_%d.ini"), PathingFile, Interfaces.pEngine->GetLevelName(), Hacks.LocalPlayer->GetTeam());
	sprintf_s(size, _CXR("%d"), PathingPos.size() + 1);
	WritePrivateProfileStringA(_CXR("Points"), _CXR("Size"), size, path);
	for (int i = 0; i < PathingPos.size(); i++)
	{
		sprintf_s(itostr, _CXR("%d"), i);
		sprintf_s(vecstr, _CXR("%f %f %f"), PathingPos[i].x, PathingPos[i].y, PathingPos[i].z);
		WritePrivateProfileStringA(_CXR("Pathing"), _CXR(itostr), vecstr, path);
	}
}

// Plot & Remove points.
if (Interfaces.InputSystem->IsButtonDown
(Interfaces.InputSystem->VirtualKeyToButtonCode
(GetMenuValue(_CreatePointKey))))
{
	PathingPos.push_back(pLocal->GetAbsOrigin());
}
else if (Interfaces.InputSystem->IsButtonDown
(Interfaces.InputSystem->VirtualKeyToButtonCode
(GetMenuValue(_RemovePointKey))))
{
	if (PathingPos.size() > 0)
		PathingPos.pop_back();
}

// Path to your points.
// Sorry this is shit. Just aimbots your next pos on yaw and sets forward move. Stole the idea from Inure in his thread.
void AutoPath(CBaseEntity* pLocal, CUserCmd* pCmd, QAngle &lastAngle)
{
	if (PathingPos.size() > 1)
	{
		QAngle CurAngles;
		Interfaces.Engine->GetViewAngles(CurAngles);

		QAngle newAngle, temp;
		calcAngles(pLocal->GetAbsOrigin(), PathingPos[PathingID], temp);
		NormalizeAngles(temp);
		temp.x = CurAngles.x;
		AimStep(lastAngle, temp, newAngle, pCmd, 12.0f);
		NormalizeAngles(newAngle);
		pCmd->viewangles = newAngle;
		lastAngle = newAngle;
		pCmd->forwardmove = 450;
	}

	if (flGetDistance(pLocal->GetAbsOrigin(), PathingPos[PathingID]) < 15)
	{
		PathingID++;
		if (PathingID > PathingPos.size() - 1)
			PathingID = 0;
	}
}

// in surface
if (GetMenuValue(_bDrawPathing))
{
	for (int i = 0; i < PathingPos.size(); i++)
	{
		// draw lines and points here,
	}
}