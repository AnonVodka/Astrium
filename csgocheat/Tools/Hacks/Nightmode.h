#include "../../SDK/SDK.h"
#include "../../stdafx.h"
#include "../Menu/Menu.h"
#include "../Hacks/Misc.h"
#include "../Hacks/Esp.h"
#include "../Hacks/CreateMoveETC.h"
#include "../Menu/SettingsManager.h"

void DoNightMode()
{
	static bool bPerformed = false , bLastSetting;

	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	ConVar* r_drawspecificstaticprop = Interfaces.g_ICVars->FindVar("r_drawspecificstaticprop");
	SpoofedConvar* r_drawspecificstaticprop_s = new SpoofedConvar(r_drawspecificstaticprop);
	r_drawspecificstaticprop_s->SetInt(0);

	ConVar* fog_override = Interfaces.g_ICVars->FindVar("fog_override");
	SpoofedConvar* fog_override_spoofed = new SpoofedConvar(fog_override);
	fog_override_spoofed->SetInt(1);

	ConVar* fog_enable = Interfaces.g_ICVars->FindVar("fog_enable");
	SpoofedConvar* fog_enable_spoofed = new SpoofedConvar(fog_enable);
	fog_enable_spoofed->SetInt(0);

	static ConVar* sv_skyname = Interfaces.g_ICVars	->FindVar("sv_skyname");
	*(float*)((DWORD)&sv_skyname->fnChangeCallback + 0xC) = NULL;
	sv_skyname->nFlags &= ~FCVAR_CHEAT; // something something dont force convars

	if (!Hacks.LocalPlayer || !Interfaces.pEngine->IsConnected() || !Interfaces.pEngine->IsInGame())
		return;

	if (!bPerformed)
	{
		for (auto i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial* pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			if (bLastSetting)
			{
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(0.60, 0.60, 0.60);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "World"))
				{
					//pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					sv_skyname->SetValue("sky_csgo_night02");
					pMaterial->ColorModulate(0.1, 0.1, 0.1);
				}

				if (strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					pMaterial->ColorModulate(0.3, 0.3, 0.3);
				}
			}
			else
			{
				if (strstr(pMaterial->GetTextureGroupName(), "Model")) {
					pMaterial->ColorModulate(1, 1, 1);
				}
				if ((strstr(pMaterial->GetTextureGroupName(), "World")) || strstr(pMaterial->GetTextureGroupName(), "StaticProp"))
				{
					sv_skyname->SetValue("vertigoblue_hdr"); // braucht fix für default value vonner skybox
					//pMaterial->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, false);
					pMaterial->ColorModulate(1, 1, 1);
				}
			}

		}
		bPerformed = true;
	}
	if (bLastSetting != Options.Visuals.VisualsWorlds.bNightMode)
	{
		bLastSetting = Options.Visuals.VisualsWorlds.bNightMode;
		bPerformed = false;
	}
}