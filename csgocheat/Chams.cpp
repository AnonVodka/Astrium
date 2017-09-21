#include "Chams.h"
#include <fstream>
//#include "SDK\SDK Headers\Entitys.h"

#include "Globals.h"
#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)

//#include "SDK\SDK Headers\CInput.h"

Chams::Chams()
{
	std::ofstream("csgo\\materials\\simple_regular.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_ignorez.vmt") << R"#("VertexLitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_flat.vmt") << R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "0"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";
	std::ofstream("csgo\\materials\\simple_flat_ignorez.vmt") << R"#("UnlitGeneric"
{
  "$basetexture" "vgui/white_additive"
  "$ignorez"      "1"
  "$envmap"       ""
  "$nofog"        "1"
  "$model"        "1"
  "$nocull"       "0"
  "$selfillum"    "1"
  "$halflambert"  "1"
  "$znearer"      "0"
  "$flat"         "1"
}
)#";

	materialRegular = Interfaces.pMaterialSystem->FindMaterial("simple_regular", TEXTURE_GROUP_MODEL);
	materialRegularIgnoreZ = Interfaces.pMaterialSystem->FindMaterial("simple_ignorez", TEXTURE_GROUP_MODEL);
	materialFlatIgnoreZ = Interfaces.pMaterialSystem->FindMaterial("simple_flat_ignorez", TEXTURE_GROUP_MODEL);
	materialFlat = Interfaces.pMaterialSystem->FindMaterial("simple_flat", TEXTURE_GROUP_MODEL);
}

Chams::~Chams()
{
	std::remove("csgo\\materials\\simple_regular.vmt");
	std::remove("csgo\\materials\\simple_ignorez.vmt");
	std::remove("csgo\\materials\\simple_flat.vmt");
	std::remove("csgo\\materials\\simple_flat_ignorez.vmt");
}

void Chams::OverrideMaterial(bool ignoreZ, bool flat, bool wireframe, bool glass, const Color& rgba)
{
	IMaterial* material = nullptr;

	if (flat) {
		if (ignoreZ)
			material = materialFlatIgnoreZ;
		else
			material = materialFlat;
	}
	else {
		if (ignoreZ)
			material = materialRegularIgnoreZ;
		else
			material = materialRegular;
	}


	if (glass) {
		material = materialFlat;
		material->AlphaModulate(0.45f);
	}
	else {
		material->AlphaModulate(
			rgba.a() / 255.0f);
	}

	material->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wireframe);
	material->ColorModulate(
		rgba.r() / 255.0f,
		rgba.g() / 255.0f,
		rgba.b() / 255.0f);

	Interfaces.g_pModelRender->ForcedMaterialOverride(material);
}

void Chams::OnDrawModelExecute(void* ctx, void* state, const ModelRenderInfo_t& info, matrix3x4_t* matrix)
{
	if (Interfaces.pEngine->IsInGame() && Hacks.LocalPlayer && info.pModel)
	{
		std::string mN = Interfaces.g_pModelInfo->GetModelName(info.pModel);

		const auto mdl = info.pModel;
		//pNPTR check uff $$$$ Anon ist ne schwuchtel ;))))
		bool isArm = strstr(mdl->szName, "arms") != nullptr;
		bool isPlayer = strstr(mdl->szName, "models/player") != nullptr;
		bool isSleeve = strstr(mdl->szName, "sleeve") != nullptr;

		if (isPlayer && Options.Visuals.Chams.bPlayers)
		{
			//nigga chams

			auto ent = Interfaces.pEntList->GetClientEntity(info.entity_index);

			if (ent && Hacks.LocalPlayer)
			{
				const auto enemy = ent->GetTeam() != Hacks.LocalPlayer->GetTeam();
				bool terror = ent->GetTeam() == 2;
				bool ct = ent->GetTeam() == 3;
				Color col_vis;
				Color col_invis;

				if (!enemy && Options.Visuals.Chams.bEnemyOnly)
					return;

				if (terror)
					col_vis = Color(Options.Col.chamsPlyrTVis[0] * 255, Options.Col.chamsPlyrTVis[1] * 255, Options.Col.chamsPlyrTVis[2] * 255);
				else
					col_vis = Color(Options.Col.chamsPlyrCTVis[0] * 255, Options.Col.chamsPlyrCTVis[1] * 255, Options.Col.chamsPlyrCTVis[2] * 255);

				if (terror)
					col_invis = Color(Options.Col.chamsPlyrTInvis[0] * 255, Options.Col.chamsPlyrTInvis[1] * 255, Options.Col.chamsPlyrTInvis[2] * 255);
				else
					col_invis = Color(Options.Col.chamsPlyrCTInvis[0] * 255, Options.Col.chamsPlyrCTInvis[1] * 255, Options.Col.chamsPlyrCTInvis[2] * 255);


				if (Options.Visuals.Chams.bThroughWalls)
				{
					OverrideMaterial(
						true,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						false,
						col_invis);
					Hacks.oDrawModelExecute(Interfaces.g_pModelRender, ctx, state, info, matrix);
					OverrideMaterial(
						false,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						false,
						col_vis);
				}
				else
				{
					OverrideMaterial(
						false,
						Options.Visuals.Chams.bFlat,
						Options.Visuals.Chams.bWireframe,
						Options.Visuals.Chams.bTransparent,
						col_vis);
				}

			}
		}
		else if (isSleeve && Options.Visuals.Chams.bArms)
		{
			auto material = Interfaces.pMaterialSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
			if (!material)
				return;

			material->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			Interfaces.g_pModelRender->ForcedMaterialOverride(material);
		}
		else if (isArm && Options.Visuals.Chams.bArms)
		{
			auto material = Interfaces.pMaterialSystem->FindMaterial(mdl->szName, TEXTURE_GROUP_MODEL);
			if (!material)
				return;
			Color col_vis = Color(Options.Col.chamsHandsVis[0] * 255, Options.Col.chamsHandsVis[1] * 255, Options.Col.chamsHandsVis[2] * 255);
			Color col_invis = Color(Options.Col.chamsHandsInvis[0] * 255, Options.Col.chamsHandsInvis[1] * 255, Options.Col.chamsHandsInvis[2] * 255);

			if (Options.Visuals.Chams.bArmsThroughWalls)
			{
				OverrideMaterial(
					true,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_invis
				);
				Hacks.oDrawModelExecute(Interfaces.g_pModelRender, ctx, state, info, matrix);
				OverrideMaterial(
					false,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_vis
				);
			}
			else
			{
				OverrideMaterial(
					false,
					Options.Visuals.Chams.bArmsFlat,
					Options.Visuals.Chams.bArmsWireframe,
					Options.Visuals.Chams.bArmsTransparent,
					col_vis
				);
			}
		}

		static bool enabledtp = false;
		static bool check = false;
		if (GetAsyncKeyState(Options.Visuals.VisualsMisc.iThirdPersonKey))
		{
			if (!check)
				enabledtp = !enabledtp;
			check = true;
		}
		else
			check = false;

		if (isPlayer && Options.Visuals.VisualsMisc.iThirdPerson >= 1 && enabledtp && Hacks.LocalPlayer->GetHealth() > 0)
		{
			auto ent = Interfaces.pEntList->GetClientEntity(info.entity_index);

			if (ent == Hacks.LocalPlayer)
				if (Hacks.LocalWeapon->isSniper())
					if (Hacks.LocalPlayer->m_bIsScoped())
				OverrideMaterialTP(false, false, false, true);
		}

	}
}

void Chams::OverrideMaterialTP(bool ignoreZ, bool flat, bool wireframe, bool glass)
{
	IMaterial* material = nullptr;

	if (flat) {
		if (ignoreZ)
			material = materialFlatIgnoreZ;
		else
			material = materialFlat;
	}
	else {
		if (ignoreZ)
			material = materialRegularIgnoreZ;
		else
			material = materialRegular;
	}


	if (glass) {
		material = materialFlat;
		material->AlphaModulate(0.20f);
	}

	Interfaces.g_pModelRender->ForcedMaterialOverride(material);
}