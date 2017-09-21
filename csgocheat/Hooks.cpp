#include "stdafx.h"
//#include "Tools/Menu/Menu.h"
#include "Tools/Hacks/Misc.h"
#include "Tools/Utils/Playerlist.h"
//#include "CircleStrafer.h"
#include "Tools/Hacks/Esp.h"
#include "Tools/Hacks/Antiaim.h"
#include "Tools/Hacks/Aimbot.h"
#include "Tools/Hacks/CreateMoveETC.h"
//#include "Tools/Menu/SettingsManager.h"
#include "Tools/Hacks/KnifeBot.h"
#include "Tools/Hacks/Nightmode.h"
#include "Tools/Hacks/Asuswalls.h"
#include "Tools/Hacks/Legitbot/Legit.h"
//#include "Tools/Hacks/Resolver.h"
#include "BlockBot.h"
#include <d3d9types.h>
#include "Sounds.h"
#include "playsoundapi.h"
#include "Pred.h"

#pragma comment(lib, "Winmm.lib")

#define DEV

cOptions Options;

#define PI_2 PI/2
#define PI_4 PI/4

#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)
void Gui_Init(IDirect3DDevice9* pDevice);
extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);
bool vecPressedKeys[256] = {};
CHackManager Hacks;

VTHookManager VMTPanel;
VTHookManager VMTD3D;
VTHookManager VMTClient;
VTHookManager VMTEngine;
VTHookManager VMTModelRender;
VTHookManager VMTClientMode;
VTHookManager VMTGameEvent;
VTHookManager VMTSurface;

class Hitbox;

std::vector< int > AutoStraferConstants = {};
std::vector< const char* > smoke_materials =
{
	"particle/vistasmokev1/vistasmokev1_smokegrenade",
	"particle/vistasmokev1/vistasmokev1_emods",
	"particle/vistasmokev1/vistasmokev1_emods_impactdust",
	"particle/vistasmokev1/vistasmokev1_fire",
};

typedef void(*Fucntion)(IGameEvent* event);

void Hurt(IGameEvent* event)
{
	if (Options.Visuals.VisualsMisc.bHitMarker)
	{
		if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		{
			Global::hitmarkerAlpha = 1.f;
			switch (Options.Visuals.VisualsMisc.iHitsound)
			{
			case 0: break;
			case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break; // Default
			case 2:	PlaySoundA(pew, NULL, SND_ASYNC | SND_MEMORY); break; // Anime
			case 3:	PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break; // Roblox
			case 4:	PlaySoundA(hitler_wav, NULL, SND_ASYNC | SND_MEMORY); break; // German
			}

		}
	}
}

void HitSound(IGameEvent* event)
{
	if (Options.Visuals.VisualsMisc.bHitMarker)
	{
		if (Interfaces.pEngine->GetPlayerForUserID(event->GetInt("attacker")) == Interfaces.pEngine->GetLocalPlayer())
		{
			switch (Options.Visuals.VisualsMisc.iKillsound)
			{
			case 0: break;
			case 1: PlaySoundA(rawData, NULL, SND_ASYNC | SND_MEMORY); break; // Default
			case 2:	PlaySoundA(pew, NULL, SND_ASYNC | SND_MEMORY); break; // Anime
			case 3:	PlaySoundA(roblox, NULL, SND_ASYNC | SND_MEMORY); break; // Roblox
			case 4:	PlaySoundA(hitler_wav, NULL, SND_ASYNC | SND_MEMORY); break; // German
			}
		}
	}
}

class CGameEventListener : public IGameEventListener2
{
private:
	std::string eventName;
	Fucntion Call;
	bool server;

public:
	CGameEventListener() : eventName(""), Call(nullptr), server(false)
	{
	}

	CGameEventListener(const std::string& gameEventName, const Fucntion Func, bool Server) : eventName(gameEventName), Call(Func), server(Server)
	{
		this->RegListener();
	}

	virtual void FireGameEvent(IGameEvent* event)
	{
		this->Call(event);
	}

	virtual int IndicateEventHandling(void)
	{
		return 0x2A;
	}
	 
	void RegListener(void)
	{
		static bool first = true;
		if (!first)
			return;
		if (Interfaces.g_GameEventMgr->AddListener(this, this->eventName.c_str(), server))
			Hacks.listeners.push_back(this);
	}
};

#define REG_EVENT_LISTENER(p, e, n, s) p = new CGameEventListener(n, e, s)
CGameEventListener* Hurts;
CGameEventListener* HitSounds;
void Init()
{
	REG_EVENT_LISTENER(Hurts, &Hurt, "player_hurt", false);
	REG_EVENT_LISTENER(HitSounds, &HitSound, "player_death", false);
}

LRESULT __stdcall Hooked_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//if (Menu::Menu.active) return true;
	switch (uMsg) {
	case WM_LBUTTONDOWN:
		vecPressedKeys[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		vecPressedKeys[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		vecPressedKeys[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		vecPressedKeys[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		vecPressedKeys[wParam] = true;
		break;
	case WM_KEYUP:
		vecPressedKeys[wParam] = false;
		break;
	default: break;
	}

	{
		static bool isDown = false;
		static bool isClicked = false;
		if (vecPressedKeys[VK_INSERT]) {
			isClicked = false;
			isDown = true;
		}
		else if (!vecPressedKeys[VK_INSERT] && isDown) {
			isClicked = true;
			isDown = false;
		}
		else {
			isClicked = false;
			isDown = false;
		}

		if (isClicked)
		{
			Global::MenuOpen = !Global::MenuOpen;
			
			static auto cl_mouseenable = Interfaces.g_ICVars->FindVar("cl_mouseenable");
			cl_mouseenable->SetValue(!Global::MenuOpen);
		}
	}

	if (Global::MenuInit && Global::MenuOpen && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;

	return CallWindowProc(INIT::OldWindow, hWnd, uMsg, wParam, lParam);
}

void __stdcall Hooked_PaintTraverse(unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	if (Options.Visuals.VisualsMisc.bScopeRemover && !strcmp("HudZoom", Interfaces.pPanel->GetName(vguiPanel)))
		return;

	Hacks.oPaintTraverse(Interfaces.pPanel, vguiPanel, forceRepaint, allowForce);

	if (strcmp("FocusOverlayPanel", Interfaces.pPanel->GetName(vguiPanel)))
	{
		return;
	}

	static bool bSpoofed = false;

	if (!bSpoofed)
	{
        ConVar* sv_cheats = Interfaces.g_ICVars->FindVar("sv_cheats");
        SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
        sv_cheats_spoofed->SetInt(1);
		bSpoofed = true;
	}

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
		Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
		
		DoAsusWalls();
		DoNightMode();
		if (Hacks.LocalPlayer)
		{
			Misc::DrawScope();
			Esp::DoEsp();
		}
	}
	Esp::Watermark();
}

void New_CreateMove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	CInput::CVerifiedUserCmd* VerifiedCmd;
	AA.ShouldAA = false;
	CreateMoveETC::GetCmds(sequence_number, Hacks.CurrentCmd, VerifiedCmd);
	Aimbot.Target = Vector(0, 0, 0);

	Misc::ServerRankReveal();

	if (Hacks.CurrentCmd && VerifiedCmd && Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && Hacks.LocalPlayer)
	{
		static bool enabled = false;
		static bool check = false;
		Misc::Chatspam();

		//plist.Update();
		MEMCHECK;
		Misc::ClantagChanger();
		Misc::NameSpam();
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
		Vector OrigAng = Hacks.CurrentCmd->viewangles;
		Misc::Normalize(OrigAng);
		//CircleStrafer(OrigAng);
		int airstuckmode = Options.Misc.Movement.iAirStuck;
		switch (airstuckmode)
		{
		case 0:
			break;
		case 1:
			if (GetAsyncKeyState(Options.Misc.Movement.iAirStuckKey))
			{
				if (!check) {
					enabled = !enabled;
					check = true;
				}
			}
			else {
				check = false;
			}
			if (enabled) {
				float ServerTime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
				float NextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

				bool Shooting = false;
				if (NextPrimaryAttack > ServerTime)
					Shooting = true;


				if (!Shooting) {
					Hacks.CurrentCmd->tick_count = 9999999;
				}
			}
			break;
		case 2:
			if (KEY_DOWN(Options.Misc.Movement.iAirStuckKey))
			{
				Hacks.CurrentCmd->tick_count = 9999999;
			}
			break;
		}
	

		if (KEY_DOWN(Options.Misc.Misc1.iFreeCamKey) && Options.Misc.Misc1.bFreeCam)
		{
			Hacks.CurrentCmd->forwardmove = 0;
			Hacks.CurrentCmd->sidemove = 0;
		}

		if (KEY_DOWN(Options.Misc.Movement.iSlowMotionKey) && Options.Misc.Movement.bSlowmotion)
		{
			static bool xd = true;

			if (Hacks.CurrentCmd->buttons & IN_ATTACK || Hacks.CurrentCmd->buttons & IN_ATTACK2)
				xd = false;
			
			if (xd)
			{
				Hacks.CurrentCmd->tick_count = INT_MAX;
				xd = false;
			}
			else
			{
				Hacks.CurrentCmd->tick_count = 0;
				xd = true;
			}
		}

		if (Options.Misc.Misc2.bBlockBot && GetAsyncKeyState(Options.Misc.Misc2.iBlockBotKey))
			AutoBlocker(Hacks.CurrentCmd);
		if (Options.Misc.Movement.bWalkBot)
			Misc::Walkbot(OrigAng);
		CreateMoveETC::BhopMovement(OrigAng);
		if (Hacks.LocalWeapon)
		{
			if (Hacks.LocalPlayer->isAlive())
			{
				//if (Options.Ragebot.HvH.bPred)
				//	Pred::StartPrediction();

				CreateMoveETC::LocalPrediction();
				LegitBot.Run();
				Trigger.Run();
				if (Options.Misc.Misc2.bKnifeBot)
					KnifeBot::Run();
				if (Hacks.LocalWeapon->HasAmmo())
				{
					Aimbot.Aim(Hacks.CurrentCmd);
					if (Misc::Shooting() && LocalInfo.Choked < 13)
					{
						if (!Options.Ragebot.Aimbot.bSilentAim && Options.Ragebot.Aimbot.bAimbotEnable)
							Interfaces.pEngine->SetViewAngles(Hacks.CurrentCmd->viewangles);//	Hacks.SendPacket = false;

						if (Options.Ragebot.Aimbot.bAimbotEnable || Options.Ragebot.Accuracy.bNoRecoil)
							Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;
					}
					else if (!Hacks.LocalWeapon->IsNade() && Options.Ragebot.Aimbot.bAutoPistol)
						Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					if (*Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver && (Options.Ragebot.Aimbot.bAimbotEnable && Options.Ragebot.Aimbot.bAutoRevolver))
					{
						//if (Hacks.CurrentCmd->buttons & IN_RELOAD)
						//	return;

						//if (!Hacks.LocalPlayer)
						//	return;

						//if (!Hacks.LocalWeapon->HasAmmo())
						//	return;

						//float postponeFireReady = Hacks.LocalWeapon->GetPostponeFireReadyTime();
						//float server_time = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

						//Hacks.CurrentCmd->buttons |= IN_ATTACK;

						//if (Hacks.CurrentCmd->buttons & IN_ATTACK2)
						//	Hacks.CurrentCmd->buttons |= IN_ATTACK;
						//else if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - server_time <= 0.05f)
						//	Hacks.CurrentCmd->buttons &= ~IN_ATTACK;

						if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - Misc::GetServerTime() > 0.05)
							Hacks.CurrentCmd->buttons |= IN_ATTACK;
					}
				}
				else
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					Hacks.CurrentCmd->buttons |= IN_RELOAD;
				}
				if (!Misc::Shooting())
					AA.Run();
			}

		}



		CreateMoveETC::CleanUp(OrigAng);
		if (!Hacks.SendPacket && Options.Visuals.VisualsMisc.iThirdPerson == 1 && Hacks.LocalPlayer->isAlive())
			Global::LastAngle = Hacks.CurrentCmd->viewangles;
		else if (Hacks.SendPacket && Options.Visuals.VisualsMisc.iThirdPerson == 2 &&  Hacks.LocalPlayer->isAlive())
			Global::LastAngle = Hacks.CurrentCmd->viewangles;




		LocalInfo.Choked = Hacks.SendPacket ? 0 : LocalInfo.Choked + 1;
		CreateMoveETC::VerifyCmd(VerifiedCmd);
		//plist.UpdateSim();
	}
}

void __declspec(naked) __fastcall Hooked_Createmove(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	Hacks.SendPacket = true;
	__asm
	{
		MOV Hacks.SendPacket, BL
		PUSH EBP
		MOV EBP, ESP
		SUB ESP, 8
		PUSHAD
		PUSH active
		PUSH input_sample_frametime
		PUSH sequence_number
		CALL Hacks.oCreateMove
	}
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	New_CreateMove(thisptr, _EAX, sequence_number, input_sample_frametime, active);
	__asm
	{
		POPAD
		MOV BL, Hacks.SendPacket
		MOV ESP, EBP
		POP EBP
		RETN 0x0C
	}
}

float __stdcall Hooked_ViewmodelFOV()
{
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if (Options.Misc.Misc2.bEnableFov)
		{
			float value = Options.Misc.Misc2.flViewModelValue;
			return value;
		}
		else
		{
			return 68.f;
		}
	}
	return 68.f;
}

void __stdcall Hooked_OverrideView(CViewSetup* pSetup)
{
	static Vector newOrigin;

	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if (Options.Misc.Misc2.bEnableFov)
			pSetup->fov = Options.Misc.Misc2.flFovValue;

		if (Options.Misc.Misc1.bFreeCam)
		{
			int freecamkey = Options.Misc.Misc1.iFreeCamKey;
			
			float freecamspeed = Options.Misc.Misc1.flFreeCamSpeed;

			if (!KEY_DOWN(freecamkey))
			{
				newOrigin = pSetup->origin;
			}
			if (KEY_DOWN(freecamkey))
			{

				unsigned int fSpeed = freecamspeed; //5.f;
				if (KEY_DOWN(VK_CONTROL))
					fSpeed = fSpeed * 0.45;
				if (KEY_DOWN(VK_SHIFT))
					fSpeed = fSpeed * 1.65;
				if (KEY_DOWN(0x57)) // W		
				{
					newOrigin += pSetup->angles.Forward() * fSpeed;
				}
				if (KEY_DOWN(0x41)) // A		
				{
					newOrigin += pSetup->angles.Right() * fSpeed;
				}
				if (KEY_DOWN(0x44)) // D		
				{
					newOrigin -= pSetup->angles.Right() * fSpeed;
				}
				if (KEY_DOWN(0x53)) // S		
				{
					newOrigin -= pSetup->angles.Forward() * fSpeed;

				}
				if (KEY_DOWN(VK_SPACE)) // Space		
				{
					newOrigin += pSetup->angles.Up() * fSpeed;
				}
				pSetup->origin = newOrigin;
			}
		}

		CHECKMEM;
		//pSetup->angles = Aimbot.Angles;
	}
	Hacks.FOV = pSetup->fov;
	Hacks.oOverrideView(pSetup);
}

int __stdcall Hooked_DoPostScreenEffects(int a1)
{
	if(Hacks.LocalPlayer && Options.Visuals.Glow.bEnabled)


	return Hacks.oDoPostScreenEffects(Interfaces.pClientMode, a1);
}

void AutoResolver(Vector* & Angle, PlayerList::CPlayer* Player)
{
	static int iLastUpdatedTick = 0;

	Player->reset.y = Angle->y;

	static Vector orginalview = Vector(0, 0, 0);
	if (orginalview.x != Angle->x)
		orginalview.x = Angle->x;
	if (Angle->y != Player->resolved)
	{
		orginalview.y = Angle->y;

		float flResolve = 0.f;
		float flLowerBodyYaw = Player->entity->pelvisangs();

		int difference = orginalview.y - flLowerBodyYaw;

		iLastUpdatedTick++;

		if (flLowerBodyYaw != Player->flLastPelvisAng)
		{
			if (Player->entity->GetVecVelocity().Length2D() == 0)
			{
				int temp = static_cast<int>(floor(Player->flEyeAng - Player->flLastPelvisAng));
				while (temp < 0)
					temp += 360;
				while (temp > 360)
					temp -= 360;
				Player->Backtrack[temp] = flLowerBodyYaw - Player->flEyeAng;
			}

			iLastUpdatedTick = 0;
			Player->flLastPelvisAng = flLowerBodyYaw;
			Player->flEyeAng = orginalview.y;
		}

		if (Player->entity->GetVecVelocity().Length2D() >= 1)
		{
			flResolve = flLowerBodyYaw;
		}
		else
		{
			int temp = static_cast<int>(floor(orginalview.y - flLowerBodyYaw));
			while (temp < 0)
				temp += 360;
			while (temp > 360)
				temp -= 360;
			flResolve = Player->Backtrack[temp] + orginalview.y;
		}
		Angle->y = flResolve;
		Player->resolved = Angle->y;
	}
}

static inline bool IsNearEqual(float v1, float v2, float Tolerance)
{
	return std::abs(v1 - v2) <= std::abs(Tolerance);
}

float GetLatency()
{
	INetChannelInfo *nci = Interfaces.pEngine->GetNetChannelInfo();
	if (nci)
	{
		float Latency = nci->GetAvgLatency(FLOW_OUTGOING) + nci->GetAvgLatency(FLOW_INCOMING);
		return Latency;
	}
	else
	{
		return 0.0f;
	}
}
float GetOutgoingLatency()
{
	INetChannelInfo *nci = Interfaces.pEngine->GetNetChannelInfo();
	if (nci)
	{
		float OutgoingLatency = nci->GetAvgLatency(FLOW_OUTGOING);
		return OutgoingLatency;
	}
	else
	{
		return 0.0f;
	}
}
float GetIncomingLatency()
{
	INetChannelInfo *nci = Interfaces.pEngine->GetNetChannelInfo();
	if (nci)
	{
		float IncomingLatency = nci->GetAvgLatency(FLOW_INCOMING);
		return IncomingLatency;
	}
	else
	{
		return 0.0f;
	}
}

void __stdcall Hooked_Frame_Stage_Notify(ClientFrameStage_t curStage)
{
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (Hacks.LocalPlayer)
	{
		LocalInfo.PunchAns = *Hacks.LocalPlayer->GetPunchAnglePtr();
		LocalInfo.Flags = Hacks.LocalPlayer->GetFlags();
	}

	ConVar* gitgud2 = Interfaces.g_ICVars->FindVar("mat_postprocess_enable");
	if (gitgud2)
	{
		if (Options.Visuals.VisualsMisc.bScopeRemover)
			gitgud2->SetValue(0);

		if (!Options.Visuals.VisualsMisc.bScopeRemover)
			gitgud2->SetValue(1);
	}

	Vector*pPunchAngle = nullptr, *pViewPunchAngle = nullptr, vPunchAngle, vViewPunchAngle;
	if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
	{
		if (Hacks.LocalPlayer)
		{
			Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
			if (curStage == FRAME_RENDER_START)
			{
				MEMCHECK;
				if (Options.Visuals.VisualsMisc.bNoVisualRecoil)
				{
					pPunchAngle = Hacks.LocalPlayer->GetPunchAnglePtr();
					pViewPunchAngle = Hacks.LocalPlayer->GetViewPunchAnglePtr();

					if (pPunchAngle && pViewPunchAngle)
					{
						vPunchAngle = *pPunchAngle;
						pPunchAngle->Init();
						vViewPunchAngle = *pViewPunchAngle;
						pViewPunchAngle->Init();
					}
				}

				//DWORD deadflag = Netvar("DT_BasePlayer", "deadflag");

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

				if (Options.Visuals.VisualsMisc.iThirdPerson >= 1 && enabledtp && Hacks.LocalPlayer->isAlive())
				{
					float flThirdPersonRange = 141; //Options.Visuals.VisualsMisc.flThirdPersonRange;

					*(bool*)((DWORD)Interfaces.pInput + 0xA5) = true;
					*(float*)((DWORD)Interfaces.pInput + 0xA8 + 0x8) = flThirdPersonRange;
				}
				else
				{
					*(bool*)((DWORD)Interfaces.pInput + 0xA5) = false;
					*(float*)((DWORD)Interfaces.pInput + 0xA8 + 0x8);
				}

				/*CInput::CUserCmd* cmd;
				static Vector vecAngles;
				Interfaces.pEngine->GetViewAngles(vecAngles);
				if (Options.Visuals.VisualsMisc.iThirdPerson >= 1)
				{
					if (!cmd->m_fCameraInThirdPerson)
					{
						cmd->m_fCameraInThirdPerson = true;
						cmd->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, Options.Visuals.VisualsMisc.flThirdPersonRange);
					}
				}
				else
				{
					cmd->m_fCameraInThirdPerson = false;
					cmd->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, 0);
				}*/


				//if (Options.Visuals.VisualsMisc.bNoFlash)
				//	*(Vector*)((DWORD)Hacks.LocalPlayer + Netvar("DT_BasePlayer", "deadflag") + 0x4) = Global::LastAngle;

				// PVS Fix

				for (int i = 1; i <= Interfaces.pGlobalVars->maxClients; i++)
				{
					if (i == Interfaces.pEngine->GetLocalPlayer()) continue;

					CBaseEntity* pMemeEnt = Interfaces.pEntList->GetClientEntity(i);
					if (!pMemeEnt) continue;

					*(int*)((uintptr_t)pMemeEnt + 0xA30) = Interfaces.pGlobalVars->framecount; //we'll skip occlusion checks now
					*(int*)((uintptr_t)pMemeEnt + 0xA28) = 0;//clear occlusion flags
				}
				for (auto matName : smoke_materials)
				{
					IMaterial* mat = Interfaces.pMaterialSystem->FindMaterial(matName, "Other textures");
					mat->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, Options.Visuals.VisualsWorlds.bNoSmoke);
				}


			}
		}
		if (*reinterpret_cast<bool*>(reinterpret_cast<DWORD>(Interfaces.pInput) + 0xA5))
			*reinterpret_cast<Vector*>(reinterpret_cast<DWORD>(Hacks.LocalPlayer) + 0x31C8) = Hacks.LastAngles;
	
	}

	Hacks.oFrameStageNotify(curStage);

	if (pPunchAngle && pViewPunchAngle)
	{
		*pPunchAngle = vPunchAngle;
		*pViewPunchAngle = vViewPunchAngle;
	}

	if (Options.Ragebot.HvH.bResolver)
	{
		//spin += 120;
		//if( spin > 180 )
		//	spin -= 360;
		plist.Update();
		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			{
				for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
				{
					auto pEntity = static_cast< CBaseEntity* >(Interfaces.pEntList->GetClientEntity(i));
					if (pEntity == nullptr)
						continue;
					if (pEntity == Hacks.LocalPlayer)
						continue;
					if (!Hacks.LocalPlayer->isAlive())
						continue;
					if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
						continue;
					if (!pEntity->isAlive())
						continue;
					if (!(pEntity->GetHealth() > 0))
						continue;
					if (pEntity->IsDormant())
						continue;
					player_info_t info;
					if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
						continue;
					PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
					Player->entity = pEntity;

					Vector* angs = Player->entity->GetEyeAnglesPointer();
					if (!Options.Misc.Misc2.bAntiUntrusted)
					{
						if (angs->x > 90.0f && angs->x < 270.f)
						{
							if (angs->x > 180.f)
								angs->x = -89.f;
							else
								angs->x = 89.0f;
						}
						//angs->y = spin;
					}
					AutoResolver(angs, Player);
					/*Vector AimAngles;
					CalcAngle(Player->entity->GetEyePosition(), Hacks.LocalPlayer->GetVecOrigin(), AimAngles);
					if (AimAngles.IsValid ())
					{
					if (Player->entity->GetFlags() & FL_ONGROUND)
					Player->LastDifference = Player->entity->pelvisangs() - AimAngles.y;
					angs->y = Player->LastDifference + AimAngles.y;
					}*/
				}
			}
		}
	}

	/*if (Options.Ragebot.HvH.iAntiAimResolver > 0)
	{
		if (!Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			return;

		static auto spin = 0;
		static float TimedYaw;
		static float OldYaw;
		static float CurYaw;
		static float curlwer;
		static float curlwerr;

		//spin += 120;
		//if( spin > 180 )
		//	spin -= 360;
		plist.Update();
		if (curStage == FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if (Interfaces.pEngine->IsInGame() && Interfaces.pEngine->IsConnected())
			{
				for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
				{
					auto pEntity = static_cast< CBaseEntity* >(Interfaces.pEntList->GetClientEntity(i));
					if (pEntity == nullptr)
						continue;
					if (pEntity == Hacks.LocalPlayer)
						continue;
					if (!Hacks.LocalPlayer->isAlive())
						continue;
					if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
						continue;
					if (!pEntity->isAlive())
						continue;
					if (!(pEntity->GetHealth() > 0))
						continue;
					if (pEntity->IsDormant())
						continue;

					player_info_t info;
					if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
						continue;
					PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
					Player->entity = pEntity;

					Vector* angs = Player->entity->GetEyeAnglesPointer();

					if (!Options.Misc.Misc2.bAntiUntrusted)
					{
						if (angs->x > 90.0f || angs->x < 270.f || angs->x > 1080.f)
						{
							if (angs->x >= 180.f || angs->x >= 90.f || angs->x >= 1080.f || angs->x >= 991.f)
								angs->x = 89.f;
							else if (angs->x <= -180.f || angs->x <= -90.f || angs->x <= -1080.f || angs->x <= -991.f)
								angs->x = -89.f;
							else
								angs->x = 89.0f;
						}
						//angs->y = spin;
					}
					else
					{
						if (angs->x > 89.f || angs->x < -89.f)
						{
							if (angs->x >= -89.f || angs->x <= -89.f)
								angs->x = -89.f;
							else if (angs->x >= 89.f || angs->x <= 89.f)
								angs->x = 89.f;
							else
								angs->x = 0;
						}
						//angs->y = spin;
					}

					if (Options.Ragebot.HvH.iAntiAimResolver == 1)
					{
						int tick = Hacks.LocalPlayer->GetTickBase();
						float flServerTime = (tick * Interfaces.pGlobalVars->interval_per_tick);
						float LastLBYUpdateTime = flServerTime - GetOutgoingLatency();
						if (((LastLBYUpdateTime + 1.125 - GetOutgoingLatency()) <= flServerTime) && (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
						{
							LastLBYUpdateTime += 1.125;
							Global::lbyupdate = true;
						}
						Global::lbyupdate = false;

						Vector* eYaw = pEntity->GetEyeAnglesPointer();
						float flResolveyaw;

						float lastLBY[64];
						float lbyDif[64];

						float curLbyYaw = pEntity->pelvisangs();

						if (pEntity->GetVecVelocity().Length2D() > 0)
							eYaw->y = pEntity->pelvisangs();
						else
						{
							if (!IsNearEqual(lastLBY[pEntity->GetIndex()], curLbyYaw, 15.f))
							{
								lbyDif[pEntity->GetIndex()] = curLbyYaw - eYaw->y;
								lastLBY[pEntity->GetIndex()] = curLbyYaw;
								eYaw->y += pEntity->pelvisangs();
							}
							else
							{
								eYaw->y += lbyDif[pEntity->GetIndex()];
							}
						}

						PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);

						Player->resolved = eYaw->y;
						AutoResolver(angs, Player);

					}

					else if (Options.Ragebot.HvH.iAntiAimResolver == 2)
					{
						AutoResolver(angs, Player);
					}

					else if (Options.Ragebot.HvH.iAntiAimResolver == 3)
					{
						if (pEntity->pelvisangs() != OldYaw)
						{
							CurYaw = OldYaw;
							OldYaw = pEntity->pelvisangs();
						}
						AutoResolver(angs, Player);
					}
					
					else if (Options.Ragebot.HvH.iAntiAimResolver == 4)
					{
						TimedYaw = pEntity->GetEyeAngles().y - pEntity->pelvisangs();
						CurYaw = abs(TimedYaw);

						AutoResolver(angs, Player);
					}
					
					else if (Options.Ragebot.HvH.iAntiAimResolver == 5)
					{
						static float lowerDelta[64];
						static float lastYaw[64];
						curlwer = pEntity->pelvisangs();
						curlwerr = pEntity->GetEyeAngles().y;
						//curlwerr = pEnt->GetEyeAngles().y; 
						float curLower = OldYaw;
						float curYaw = curlwerr;

						lowerDelta[i] = curYaw - curLower;
						//U::Normalize(lowerDelta[i]); //wat? normalize float

						if (fabs(lowerDelta[i]) > 15.f)
						{
							if (pEntity->GetVecVelocity().Length2D() > 0)
							{
								pEntity->GetEyeAngles().y - pEntity->pelvisangs();
							}
							else
							{
								if (curYaw != lastYaw[i])
								{
									curlwerr += lowerDelta[i];
									lastYaw[i] = curYaw;
								}
							}

						}
						AutoResolver(angs, Player);
					}
					
					else if (Options.Ragebot.HvH.iAntiAimResolver == 6)
					{
				
					}

					//*(float*)((DWORD)pEntity + Netvar("DT_CSPlayer", "m_angEyeAngles[]") + 0x4) = CurYaw;
				}
			}
		}
	}*/

	/*if (Options.Ragebot.HvH.bBruteforce)
	{
		for (int i = 1; i < Interfaces.pEngine->GetMaxClients(); ++i)
		{
			CBaseEntity* entity = Interfaces.pEntList->GetClientEntity(i);
			if (entity->isValidPlayer())
			{
				if (GetAsyncKeyState(MOUSE_5))
				{
					if (!entity->GetVecVelocity().Length() > 1.0f)
					{
						int angle = rand() % 5;
						switch (angle)
						{
						case 0:entity->pelvisangs() += 135; break;
						case 2:entity->pelvisangs() += 155; break;
						case 3:entity->pelvisangs() += 165; break;
						case 4:entity->pelvisangs() += 175; break;
						case 5:entity->pelvisangs() += 185; break;
						}
					}
					else
					{
						entity->pelvisangs() += 180;
					}
				}
			}
		}
	}*/

}

void InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx", NULL, NULL);
	dwFunction += 7;
	dwFunction = dwFunction + *reinterpret_cast< PDWORD_PTR >(dwFunction + 1) + 5;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void LoadFromBuffer(KeyValues* keyValues, char const* resourceName, const char* pBuffer)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x80\x7D\xF8\x00\x00\x00\x85\xDB", "x????xxxx??xx", NULL, NULL);
	dwFunction = dwFunction + *reinterpret_cast< PDWORD_PTR >(dwFunction + 1) + 5;
	__asm
	{
		push 0
		push 0
		push 0
		push pBuffer
		push resourceName
		mov ecx, keyValues
		call dwFunction
	}
}

IMaterial* Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\"  \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\"  \"0\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	};
	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created);
	++created;
	KeyValues* keyValues = static_cast< KeyValues* >(malloc(sizeof(KeyValues)));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial* createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}

void __fastcall Hooked_DrawModelExecute(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t& pInfo, matrix3x4_t* pCustomBoneToWorld)
{
	Chams::Get().OnDrawModelExecute(ctx, state, pInfo, pCustomBoneToWorld);
	//if (!Do_Chams(thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld))
	Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
	Interfaces.g_pModelRender->ForcedMaterialOverride(nullptr);
}

void __stdcall Hooked_ClientCmdUnrestricted(const char* szCmdString, char flag)
{
	string str(szCmdString);
	std::string prefix;
	if (!str.compare(0, string("Clantag ").size(), "Clantag "))
	{
		str.replace(0, string("Clantag ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::SetClanTag(str.c_str(), "");
	}
	else if (!str.compare(0, string("ReleaseName").size(), "ReleaseName"))
	{
		Misc::setName("\n\xAD\xAD\xAD­­­");
	}
	else if (!str.compare(0, string("Name ").size(), "Name "))
	{
		str.replace(0, string("Name ").size(), "");
		prefix = string("\\n");
		std::size_t found = str.find(prefix);
		if (found != std::string::npos)
			str.replace(found, found + prefix.size(), "\n");
		Misc::setName(str.c_str());
	}
	/*
	else if (!str.compare(0, string("Save ").size(), "Save ")) {
	str.replace(0, string("Save ").size(), "");
	std::ofstream output(str);
	Menu::Menu.Save(output);
	}
	else if (!str.compare(0, string("Load ").size(), "Load ")) {
	str.replace(0, string("Load ").size(), "");
	std::ifstream input(str);
	if (input.good()) Menu::Menu.Load(input);
	}
	else if (!str.compare(0, string("Delete ").size(), "Delete ")) {
	str.replace(0, string("Delete ").size(), "");
	std::ofstream output(str);
	if (output.good()) {
	output.close();
	std::remove(str.c_str());
	}
	}
	*/
	else
		Hacks.oClientCmdUnresticted(szCmdString, flag);
}
