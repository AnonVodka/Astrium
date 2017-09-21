#include "../../SDK/SDK.h"
#include "../../stdafx.h"
#include "../Menu/Menu.h"
#include "../Hacks/Misc.h"
#include "../Hacks/Esp.h"
#include "../Hacks/CreateMoveETC.h"
#include "../Menu/SettingsManager.h"
 
void DoAsusWalls()
{
	static bool bPerformed = false, bLastSetting;

	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());

	if (!Hacks.LocalPlayer || !Interfaces.pEngine->IsConnected() || !Interfaces.pEngine->IsInGame())
		return;

	if (!bPerformed)
	{
		for (auto i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial* pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

			if (!pMaterial || pMaterial->IsErrorMaterial())
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World") || (strstr(pMaterial->GetTextureGroupName(), "StaticProp")))
			{
				if (bLastSetting)
				{
					pMaterial->AlphaModulate(0.6);
				}
				else
				{
					pMaterial->AlphaModulate(1.00);
				}
			}		
		}
		bPerformed = true;
	}
	if (bLastSetting != Options.Visuals.VisualsWorlds.bAsusWalls)
	{
		bLastSetting = Options.Visuals.VisualsWorlds.bAsusWalls;
		bPerformed = false;
	}

	//for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
	//{
	//	IMaterial* pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);

	//	if (!pMaterial)
	//		continue;

	//	if (strstr(pMaterial->GetTextureGroupName(), "World"))
	//	{
	//		if (Options.Visuals.VisualsWorlds.flAsusFactor < 99)
	//		{
	//			pMaterial->AlphaModulate(Options.Visuals.VisualsWorlds.flAsusFactor / 100);
	//			pMaterial->SetMaterialVarFlag(MATERIAL_VAR_OPAQUETEXTURE, true);
	//			pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, true);
	//		}
	//		else
	//		{
	//			pMaterial->AlphaModulate(1.0f);
	//			pMaterial->SetMaterialVarFlag(MATERIAL_VAR_OPAQUETEXTURE, false);
	//			pMaterial->SetMaterialVarFlag(MATERIAL_VAR_IGNOREZ, false);
	//		}
	//	}
	//}
}
