#pragma once

#include "../../../Hooks.h"
#include "../../../stdafx.h"
#include "../../Utils/hitbox.h"
#include "../../Menu/Menu.h"
#include "../../Utils/Playerlist.h"
#include "../../Utils/HitboxLists.h"
#include "../../Utils/LocalInfo.h"
#include "../../../SDK/Math/Math.h"
#include <iostream>

class CTrigger
{
private:
	bool TargetMeetsTriggerRequirements(CBaseEntity* pEntity)
	{
		// Is a valid player
		if (pEntity && pEntity->IsDormant() == false && pEntity->isAlive() && pEntity->GetIndex() != Hacks.LocalPlayer->GetIndex() && pEntity->GetIndex() < 65)
		{
			// Team Check
			if (pEntity->GetTeam() != Hacks.LocalPlayer->GetTeam())
			{
				// Spawn Check
				if (!pEntity->HasGunGameImmunity())
				{
					return true;
				}
			}
		}

		// They must have failed a requirement
		return false;
	}
	
	void DoTriggerPistols()
	{
		if (!Hacks.LocalWeapon->isPistol())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Pistols.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Pistols.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			||	(Options.Legitbot.Trigger.Pistols.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST) 
			||	(Options.Legitbot.Trigger.Pistols.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH) 
			||	(Options.Legitbot.Trigger.Pistols.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			||	(Options.Legitbot.Trigger.Pistols.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			||  (Options.Legitbot.Trigger.Pistols.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD 
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG 
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			if (*Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver)
			{
				if (Options.Legitbot.Trigger.Pistols.bAutoRevolver)
				{

//					if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - Misc::GetServerTime() > 0.05)
						Hacks.CurrentCmd->buttons |= IN_ATTACK;
				}
				else if (Options.Legitbot.Trigger.Pistols.bRevolverSecondary)
				{
					// Revolver Secondary
					if (Hacks.CurrentCmd->buttons = IN_ATTACK2)
					{
						static bool WasFiring = false;
						WasFiring = !WasFiring;

						if (WasFiring)
						{
							Hacks.CurrentCmd->buttons &= ~IN_ATTACK2;
						}
					}
				}
			}
			else if(Options.Legitbot.Trigger.Pistols.bAutoPistol)
			{
				// Auto Pistol
				if (Hacks.CurrentCmd->buttons = IN_ATTACK)
				{
					static bool WasFiring = false;
					WasFiring = !WasFiring;

					if (WasFiring)
					{
						Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
					}
				}
			}
			else
			{
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
			}
		}

	}
	
	void DoTriggerRifles()
	{
		if (!Hacks.LocalWeapon->isRifle())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Rifles.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Rifles.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			|| (Options.Legitbot.Trigger.Rifles.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST)
			|| (Options.Legitbot.Trigger.Rifles.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH)
			|| (Options.Legitbot.Trigger.Rifles.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			|| (Options.Legitbot.Trigger.Rifles.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			|| (Options.Legitbot.Trigger.Rifles.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}

	}
	
	void DoTriggerSnipers()
	{
		if (!Hacks.LocalWeapon->isSniper())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Snipers.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Snipers.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			|| (Options.Legitbot.Trigger.Snipers.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST)
			|| (Options.Legitbot.Trigger.Snipers.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH)
			|| (Options.Legitbot.Trigger.Snipers.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			|| (Options.Legitbot.Trigger.Snipers.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			|| (Options.Legitbot.Trigger.Snipers.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			if (Options.Legitbot.Trigger.Snipers.bScoped && !Hacks.LocalWeapon->isScoped())
				return;
			else
			{
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
			}

		}

	}
	
	void DoTriggerShotguns()
	{
		if (!Hacks.LocalWeapon->isShotgun())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Shotguns.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Shotguns.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			|| (Options.Legitbot.Trigger.Shotguns.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST)
			|| (Options.Legitbot.Trigger.Shotguns.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH)
			|| (Options.Legitbot.Trigger.Shotguns.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			|| (Options.Legitbot.Trigger.Shotguns.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			|| (Options.Legitbot.Trigger.Shotguns.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}

	}
	
	void DoTriggerSmgs()
	{
		if (!Hacks.LocalWeapon->isSmgW())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Smgs.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Smgs.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			|| (Options.Legitbot.Trigger.Smgs.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST)
			|| (Options.Legitbot.Trigger.Smgs.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH)
			|| (Options.Legitbot.Trigger.Smgs.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			|| (Options.Legitbot.Trigger.Smgs.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			|| (Options.Legitbot.Trigger.Smgs.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}

	}

	void DoTriggerHeavy()
	{
		if (!Hacks.LocalWeapon->isMachineW())
			return;
		//===============================================================================
		auto LocalPlayerWeapon = (CBaseCombatWeapon*)Interfaces.pEntList->GetClientEntityFromHandle(Hacks.LocalPlayer->GetActiveBaseCombatWeapon());
		auto WeaponEntity = (IClientEntity*)LocalPlayerWeapon;

		//if (LocalPlayerWeapon) {
		//	if (LocalPlayerWeapon->ammo2() == 0)
		//		return;

		//	if (Hacks.LocalWeapon->IsGrenade() || Hacks.LocalWeapon->IsNade())
		//		return;
		//}
		//else
		//	return;
		//===============================================================================

		Vector ViewAngles = Hacks.CurrentCmd->viewangles;
		if (Options.Legitbot.Trigger.Heavy.bTriggerRecoil)
			Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (vec_t)2.f;

		Vector CrosshairForward;
		g_Math.angleVectors(ViewAngles, CrosshairForward);
		//CrosshairForward *= LocalPlayerWeaponData->m_flRange;
		CrosshairForward *= 8000.f;


		Vector TraceSource = Hacks.LocalPlayer->GetEyePosition();
		Vector TraceDestination = TraceSource + CrosshairForward;

		Ray_t Ray;
		trace_t Trace;
		CTraceFilter Filter;

		Filter.pSkip = Hacks.LocalPlayer;

		Ray.Init(TraceSource, TraceDestination);
		Interfaces.pTrace->TraceRay(Ray, MASK_SHOT, &Filter, &Trace);

		if (!Trace.m_pEnt)
			return;
		if (!Trace.m_pEnt->isAlive())
			return;
		if (Trace.m_pEnt->GetHealth() <= 0 || Trace.m_pEnt->GetHealth() > 100)
			return;

		if (Hacks.LocalPlayer->GetTeam() == Trace.m_pEnt->GetTeam())
			return;

		if ((Options.Legitbot.Trigger.Heavy.bTriggerHead && Trace.hitgroup == HITGROUP_HEAD)
			|| (Options.Legitbot.Trigger.Heavy.bTriggerChest && Trace.hitgroup == HITGROUP_CHEST)
			|| (Options.Legitbot.Trigger.Heavy.bTriggerStomach && Trace.hitgroup == HITGROUP_STOMACH)
			|| (Options.Legitbot.Trigger.Heavy.bTriggerArms && (Trace.hitgroup == HITGROUP_LEFTARM || Trace.hitgroup == HITGROUP_RIGHTARM))
			|| (Options.Legitbot.Trigger.Heavy.bTriggerLegs && (Trace.hitgroup == HITGROUP_LEFTLEG || Trace.hitgroup == HITGROUP_RIGHTLEG))
			|| (Options.Legitbot.Trigger.Heavy.bTriggerFullBody && (
				Trace.hitgroup == HITGROUP_HEAD
				|| Trace.hitgroup == HITGROUP_CHEST
				|| Trace.hitgroup == HITGROUP_STOMACH
				|| Trace.hitgroup == HITGROUP_LEFTARM
				|| Trace.hitgroup == HITGROUP_RIGHTARM
				|| Trace.hitgroup == HITGROUP_LEFTLEG
				|| Trace.hitgroup == HITGROUP_RIGHTLEG))
			)
		{
			Hacks.CurrentCmd->buttons |= IN_ATTACK;
		}

	}


public:
	void Run()
	{
		if (Options.Legitbot.Trigger.Pistols.bEnableTrigger && ((Options.Legitbot.Trigger.Pistols.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Pistols.iTriggerKey) || !Options.Legitbot.Trigger.Pistols.bTriggerOnKey)))
			DoTriggerPistols();
		if (Options.Legitbot.Trigger.Rifles.bEnableTrigger && ((Options.Legitbot.Trigger.Rifles.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Rifles.iTriggerKey) || !Options.Legitbot.Trigger.Rifles.bTriggerOnKey)))
			DoTriggerRifles();
		if (Options.Legitbot.Trigger.Snipers.bEnableTrigger && ((Options.Legitbot.Trigger.Snipers.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Snipers.iTriggerKey) || !Options.Legitbot.Trigger.Snipers.bTriggerOnKey)))
			DoTriggerSnipers();
		if (Options.Legitbot.Trigger.Shotguns.bEnableTrigger && ((Options.Legitbot.Trigger.Shotguns.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Shotguns.iTriggerKey) || !Options.Legitbot.Trigger.Shotguns.bTriggerOnKey)))
			DoTriggerShotguns();
		if (Options.Legitbot.Trigger.Smgs.bEnableTrigger && ((Options.Legitbot.Trigger.Smgs.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Smgs.iTriggerKey) || !Options.Legitbot.Trigger.Smgs.bTriggerOnKey)))
			DoTriggerSmgs();
		if (Options.Legitbot.Trigger.Heavy.bEnableTrigger && ((Options.Legitbot.Trigger.Heavy.bTriggerOnKey && KEY_DOWN(Options.Legitbot.Trigger.Heavy.iTriggerKey) || !Options.Legitbot.Trigger.Heavy.bTriggerOnKey)))
			DoTriggerHeavy();
	}
} Trigger;

class Legit {
	int GetBestPoint(Vector& aimspot, Hitbox box, float& fov) {

		if (Hacks.LocalWeapon->isMachineW()) {
			fov = Options.Legitbot.Aimbot.Heavy.iAimbotFov;
		}
		else if (Hacks.LocalWeapon->isShotgun()) {
			fov = Options.Legitbot.Aimbot.Shotguns.iAimbotFov;
		}
		else if (Hacks.LocalWeapon->isSmgW()) {
			fov = Options.Legitbot.Aimbot.Smgs.iAimbotFov;
		}
		else if (Hacks.LocalWeapon->isRifle()) {
			fov = Options.Legitbot.Aimbot.Rifles.iAimbotFov;
		}
		else if (Hacks.LocalWeapon->isSniper()) {
			fov = Options.Legitbot.Aimbot.Snipers.iAimbotFov;
		}
		else if (Hacks.LocalWeapon->isPistol()) {
			fov = Options.Legitbot.Aimbot.Pistols.iAimbotFov;
		}

		Vector Aimangles;
		Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), box.points[0], Aimangles);
		if (Misc::FovTo(Hacks.CurrentCmd->viewangles, Aimangles) > fov) return false;
		float bestdamage = 0;
		for (int index = 0; index < 27; ++index) {
			Vector Aimangles;
			Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), box.points[index], Aimangles);
			if (Misc::FovTo(Hacks.CurrentCmd->viewangles, Aimangles) > fov) continue;
			float damage = Autowall::GetDamage(box.points[index]);
			if (damage > bestdamage) {
				aimspot = box.points[index];
				bestdamage = damage;

			}
		}
		return bestdamage;
	}

	bool LegitAim(float fov, int hitbox) {
		if (!(Hacks.CurrentCmd->buttons & IN_ATTACK && Misc::bullettime() && LocalInfo.Choked < 13)) return false;
		std::vector<Vector> possibleaimspots;
		std::vector<CBaseEntity*> possibletargets;
		for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++) {
			auto pEntity = static_cast<CBaseEntity*> (Interfaces.pEntList->GetClientEntity(i));
			if (pEntity == nullptr) continue;
			if (pEntity == Hacks.LocalPlayer) continue;
			if (!pEntity->isAlive()) continue;
			if (!(pEntity->GetHealth() > 0)) continue;
			if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam()) continue;
			// 			if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() && !Settings.GetSetting(Tab_LegitBot, Legit_Team)) continue;
			if (pEntity->IsDormant()) continue;
			//if(GetChockedPackets(pEntity) == 0) continue;
			if (pEntity->HasGunGameImmunity()) continue;
			player_info_t info;
			if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info))) continue;
			possibletargets.emplace_back(pEntity);
		}
		if ((int)possibletargets.size()) {
			for (auto pEntity : possibletargets) {
				Hitbox box;
				if (!box.GetHitbox(pEntity, hitbox)) continue;
				Vector Aimspot;
				if (box.GetBestPoint(Aimspot)) {
					//FindActualHitbox(pEntity, Aimspot);

					plist.Update();
					PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
					Player->entity = pEntity;
					possibleaimspots.emplace_back(Aimspot);
				}
			}
		}
		for (auto Spot : possibleaimspots) {
			bool SilentAim = 0;

			if (Hacks.LocalWeapon->isMachineW()) {
				SilentAim = Options.Legitbot.Aimbot.Heavy.bSilentAim;
			}
			else if (Hacks.LocalWeapon->isShotgun()) {
				SilentAim = Options.Legitbot.Aimbot.Shotguns.bSilentAim;
			}
			else if (Hacks.LocalWeapon->isSmgW()) {
				SilentAim = Options.Legitbot.Aimbot.Smgs.bSilentAim;
			}
			else if (Hacks.LocalWeapon->isRifle()) {
				SilentAim = Options.Legitbot.Aimbot.Rifles.bSilentAim;
			}
			else if (Hacks.LocalWeapon->isSniper()) {
				SilentAim = Options.Legitbot.Aimbot.Snipers.bSilentAim;
			}
			else if (Hacks.LocalWeapon->isPistol()) {
				SilentAim = Options.Legitbot.Aimbot.Pistols.bSilentAim;
			}
			else if (!Hacks.LocalWeapon->IsWeapon())
				SilentAim = false;

			Vector vecCurPos = Hacks.LocalPlayer->GetEyePosition();
			Vector angs;
			Misc::CalcAngle(vecCurPos, Spot, angs);
			Vector localangs;
			Interfaces.pEngine->GetViewAngles(localangs);
			if (Misc::FovTo(localangs, angs) <= fov) {
				if (!SilentAim) Interfaces.pEngine->SetViewAngles(angs);
				Hacks.CurrentCmd->viewangles = angs;
				Hacks.CurrentCmd->buttons |= IN_ATTACK;
				Hacks.SendPacket = false;
				return true;
			}
		}
	}

	void GetSettings(float& fov, float& recoil, int& Hitbox) {
		if (Hacks.LocalWeapon->isMachineW()) {
			fov = Options.Legitbot.Aimbot.Heavy.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Heavy.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Heavy.iAimbotHitbox;;
		}
		else if (Hacks.LocalWeapon->isShotgun()) {
			fov = Options.Legitbot.Aimbot.Shotguns.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Shotguns.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Shotguns.iAimbotHitbox;;
		}
		else if (Hacks.LocalWeapon->isSmgW()) {
			fov = Options.Legitbot.Aimbot.Smgs.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Smgs.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Smgs.iAimbotHitbox;;
		}
		else if (Hacks.LocalWeapon->isRifle()) {
			fov = Options.Legitbot.Aimbot.Rifles.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Rifles.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Rifles.iAimbotHitbox;;
		}
		else if (Hacks.LocalWeapon->isSniper()) {
			fov = Options.Legitbot.Aimbot.Snipers.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Snipers.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Snipers.iAimbotHitbox;
		}
		else if (Hacks.LocalWeapon->isPistol()) {
			fov = Options.Legitbot.Aimbot.Pistols.iAimbotFov;
			recoil = Options.Legitbot.Aimbot.Pistols.flAimbotRecoil / 100;
			Hitbox = Options.Legitbot.Aimbot.Pistols.iAimbotHitbox;
		}
	}

	void AutoPistol()
	{
		// Auto Pistol
		if (Hacks.LocalWeapon->isPistol() && Options.Legitbot.Aimbot.Pistols.bAutoPistol)
		{
			if (Hacks.CurrentCmd->buttons & IN_ATTACK)
			{

				static bool WasFiring = false;
				WasFiring = !WasFiring;

				if (WasFiring)
				{
					Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				}
			}
		}
	}

public:
	void Run() 
	{
		bool enable = 0;

		if (Options.Legitbot.Aimbot.Pistols.bAutoPistol)
			AutoPistol();

		if (Hacks.LocalWeapon->isMachineW() && ((Options.Legitbot.Aimbot.Heavy.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Heavy.iKey) || !Options.Legitbot.Aimbot.Heavy.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Heavy.bEnableAimbot;
		}
		else if (Hacks.LocalWeapon->isShotgun() && ((Options.Legitbot.Aimbot.Shotguns.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Shotguns.iKey) || !Options.Legitbot.Aimbot.Shotguns.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Shotguns.bEnableAimbot;
		}
		else if (Hacks.LocalWeapon->isSmgW() && ((Options.Legitbot.Aimbot.Smgs.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Smgs.iKey) || !Options.Legitbot.Aimbot.Smgs.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Smgs.bEnableAimbot;
		}
		else if (Hacks.LocalWeapon->isRifle() && ((Options.Legitbot.Aimbot.Rifles.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Rifles.iKey) || !Options.Legitbot.Aimbot.Rifles.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Rifles.bEnableAimbot;
		}
		else if (Hacks.LocalWeapon->isSniper() && ((Options.Legitbot.Aimbot.Snipers.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Snipers.iKey) || !Options.Legitbot.Aimbot.Snipers.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Snipers.bEnableAimbot;
		}
		else if (Hacks.LocalWeapon->isPistol() && ((Options.Legitbot.Aimbot.Pistols.bOnKey && KEY_DOWN(Options.Legitbot.Aimbot.Pistols.iKey) || !Options.Legitbot.Aimbot.Pistols.bOnKey))) {
			enable = Options.Legitbot.Aimbot.Pistols.bEnableAimbot;
		}
		else if (!Hacks.LocalWeapon->IsWeapon())
			enable = false;
		if (!enable) 
			return;
		//		if (!LocalInfo.Flags & FL_ONGROUND && Hacks.LocalPlayer->GetFlags() & FL_ONGROUND && Hacks.CurrentCmd->buttons & IN_JUMP && Menu::LegitMenu::Bhop.active) Hacks.CurrentCmd->buttons &= ~IN_JUMP;
		float fov = 0, recoil = 0;
		int hitbox = 0;
		GetSettings(fov, recoil, hitbox);
		LegitAim(fov, hitbox);
		Hacks.CurrentCmd->viewangles -= LocalInfo.PunchAns * (recoil * 2);
	}
} LegitBot;