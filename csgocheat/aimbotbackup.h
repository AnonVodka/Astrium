//#pragma once
//#include "../../stdafx.h"
//#include "../Utils/Hitbox.h"
//#include "../Menu/Menu.h"
//#include "../Utils/Playerlist.h"
//#include "../Menu/SettingsManager.h"
//#include "../Utils/HitboxLists.h"
//
//
//#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)
//
//class Aimbot
//{
//private:
//	struct Target_t
//	{
//		Vector aimspot;
//		CBaseEntity* ent;
//	};
//
//	Vector GetBestPoint(PlayerList::CPlayer* Player)
//	{
//		for (auto Pos : Player->ShootPos)
//		{
//			if (Pos != Vector(0, 0, 0))
//			{
//				Vector New = Pos + Player->box->points[1];
//				Vector Aimangles;
//				Misc::CalcAngle(Hacks.LocalPlayer->GetEyePosition(), New, Aimangles);
//				//if (Misc::FovTo(Hacks.CurrentCmd->viewangles, Aimangles) > Menu::AimbotMenu::Selection::Fov.value) continue;
//				float damage = Autowall::GetDamage(New);
//				if (damage > Options.Ragebot.Accuracy.iMinDmg)
//				{
//					return New;
//				}
//			}
//		}
//		return Vector(0, 0, 0);
//	}
//
//	void HitboxScanning(PlayerList::CPlayer* Player)
//	{
//		Hitbox* box = Player->box;
//		CTraceFilter filter;
//		trace_t tr;
//		Ray_t ray;
//		int Dividens[3] = { (box->points[8].x - box->points[1].x) / 5 , (box->points[8].y - box->points[1].y) / 5, (box->points[8].z - box->points[1].z) / 5 };
//		int Old = Player->ScannedNumber + 5;
//		for (; Player->ScannedNumber < Old; Player->ScannedNumber++)
//		{
//			int x = Player->ScannedNumber;
//			int y = 0;
//			int z = 0;
//			while (x >= 5)
//			{
//				x -= 5;
//				y++;
//			}
//			while (y >= 5)
//			{
//				y -= 5;
//				z++;
//			}
//			if (z >= 5)
//			{
//				Player->ScannedNumber = 0;
//				break;
//			}
//
//			Vector Pos = Vector(box->points[1].x + (x * Dividens[0]), box->points[1].y + (y * Dividens[1]), box->points[1].z + (z * Dividens[2]));
//			ray.Init(Pos, Pos);
//			Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &tr);
//			if (tr.m_pEnt != Player->entity)
//				Player->ShootPos[Player->ScannedNumber] = Vector(0, 0, 0);
//		}
//	}
//
//	void GetTargets(std::vector< CBaseEntity* >& possibletargets)
//	{
//		for (auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
//		{
//			auto pEntity = static_cast< CBaseEntity* >(Interfaces.pEntList->GetClientEntity(i));
//			if (pEntity == nullptr)
//				continue;
//			if (pEntity == Hacks.LocalPlayer)
//				continue;
//			if (!pEntity->isAlive())
//				continue;
//			if (!(pEntity->GetHealth() > 0))
//				continue;
//			if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
//				continue;
//			if (pEntity->IsDormant())
//				continue;
//			PlayerList::CPlayer* Player = plist.FindPlayer(pEntity);
//			Player->entity = pEntity;
//			if (pEntity->HasGunGameImmunity())
//				continue;
//			player_info_t info;
//			if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
//				continue;
//			possibletargets.emplace_back(pEntity);
//		}
//	}
//
//	void GetAimSpots(std::vector< Vector >& Targets, std::vector< Target_t >& possibleaimspots, std::vector< CBaseEntity* >& possibletargets)
//	{
//		if ((int)possibletargets.size())
//		{
//			for (CBaseEntity* pEntity : possibletargets)
//			{
//				Targets.emplace_back(pEntity->GetVecOrigin() - Hacks.LocalPlayer->GetVecOrigin());
//
//				std::vector< int > iArray = { iBoxListDefault[Options.Ragebot.Aimbot.iHitbox] };
//
//				float flBestDamage = 0.f;
//
//				if (Options.Ragebot.Accuracy.bVelocityPrediction)
//				{
//					if (!(pEntity->GetFlags() & FL_ONGROUND))
//					{
//						iArray = { (int)CSGOHitboxID::Pelvis };
//						flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//						if (flBestDamage == 0)
//						{
//							if ((Options.Ragebot.HvH.iPreferBaim == 2 && pEntity->GetEyeAngles().x > 60) || Options.Ragebot.HvH.iPreferBaim == 3)
//							{
//								if (Options.Ragebot.Accuracy.iMultibox == 2)
//									iArray = iBoxListSmartBaim;
//								else if (Options.Ragebot.Accuracy.iMultibox == 3)
//									iArray = iBaim;
//								else
//									iArray = iBoxListBaim;
//							}
//							else
//							{
//								int iSwitch = Options.Ragebot.Accuracy.iMultibox;
//								int i;
//								switch (iSwitch)
//								{
//								case 0:
//								case 1:
//									iArray = { iBoxListDefault[Options.Ragebot.Aimbot.iHitbox] };
//									break;
//								case 2:
//									iArray = iBoxListSmart;
//									break;
//								case 3:
//									iArray = iBoxListMax;
//									break;
//								case 4:
//									iArray = iBaim;
//									break;
//								}
//							}
//							flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//						}
//					}
//					else if (pEntity->GetFlags() & FL_ONGROUND && pEntity->GetVecVelocity().Length2D() < 1.f)
//					{
//						iArray = iBoxListSmartBaim;
//						flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//						if (flBestDamage == 0)
//						{
//							if ((Options.Ragebot.HvH.iPreferBaim == 2 && pEntity->GetEyeAngles().x > 60) || Options.Ragebot.HvH.iPreferBaim == 3)
//							{
//								if (Options.Ragebot.Accuracy.iMultibox == 2)
//									iArray = iBoxListSmartBaim;
//								else if (Options.Ragebot.Accuracy.iMultibox == 3)
//									iArray = iBaim;
//								else
//									iArray = iBoxListBaim;
//							}
//							else
//							{
//								int iSwitch = Options.Ragebot.Accuracy.iMultibox;
//								int i;
//								switch (iSwitch)
//								{
//								case 0:
//								case 1:
//									iArray = { iBoxListDefault[Options.Ragebot.Aimbot.iHitbox] };
//									break;
//								case 2:
//									iArray = iBoxListSmart;
//									break;
//								case 3:
//									iArray = iBoxListMax;
//									break;
//								case 4:
//									iArray = iBaim;
//									break;
//								}
//							}
//							flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//						}
//					}
//					else
//					{
//						if ((Options.Ragebot.HvH.iPreferBaim == 2 && pEntity->GetEyeAngles().x > 60) || Options.Ragebot.HvH.iPreferBaim == 3)
//						{
//							if (Options.Ragebot.Accuracy.iMultibox == 2)
//								iArray = iBoxListSmartBaim;
//							else if (Options.Ragebot.Accuracy.iMultibox == 3)
//								iArray = iBaim;
//							else
//								iArray = iBoxListBaim;
//						}
//						else
//						{
//							int iSwitch = Options.Ragebot.Accuracy.iMultibox;
//							int i;
//							switch (iSwitch)
//							{
//							case 0:
//							case 1:
//								iArray = { iBoxListDefault[Options.Ragebot.Aimbot.iHitbox] };
//								break;
//							case 2:
//								iArray = iBoxListSmart;
//								break;
//							case 3:
//								iArray = iBoxListMax;
//								break;
//							case 4:
//								iArray = iBaim;
//								break;
//							}
//						}
//						flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//					}
//				}
//				else
//				{
//					if ((Options.Ragebot.HvH.iPreferBaim == 2 && pEntity->GetEyeAngles().x > 60) || Options.Ragebot.HvH.iPreferBaim == 3)
//						iArray = iBoxListBaim;
//					else
//					{
//						int iSwitch = Options.Ragebot.Accuracy.iMultibox;
//						int i;
//						switch (iSwitch)
//						{
//						case 0:
//						case 1:
//							iArray = { iBoxListDefault[Options.Ragebot.Aimbot.iHitbox] };
//							break;
//						case 2:
//							iArray = iBoxListSmart;
//							break;
//						case 3:
//							iArray = iBoxListMax;
//							break;
//						case 4:
//							iArray = iBaim;
//							break;
//						}
//					}
//					flBestDamage = ScanBoxList(pEntity, iArray, possibleaimspots);
//				}
//
//				if (flBestDamage == 0)
//				{
//					iArray = iBoxListSafety;
//					ScanBoxList(pEntity, iArray, possibleaimspots);
//				}
//			}
//		}
//	}
//
//	float ScanBoxList(CBaseEntity* pEntity, std::vector< int > iArray, std::vector< Target_t > &possibleaimspots)
//	{
//		float flBestDamage = 0.f;
//
//		if (iArray.size() > 0)
//		{
//			for (int i = 0; i < iArray.size(); i++)
//			{
//				Hitbox box;
//				if (!box.GetHitbox(pEntity, iArray[i]))
//					continue;
//
//				Vector Aimspot;
//				float flDamage = iArray[i] == (int)CSGOHitboxID::Head ? box.GetBestPoint(Aimspot) : box.ScanCenter(Aimspot);
//
//				if (flDamage > Options.Ragebot.Accuracy.iMinDmg || (flDamage > pEntity->GetHealth() && Options.Ragebot.Accuracy.bAcceptKillDmg))
//				{
//					if (flDamage > flBestDamage)
//					{
//						flBestDamage = flDamage;
//						if (Misc::GetNumberOfTicksChoked(pEntity) > 5 && Options.Ragebot.HvH.bPositionAdj)
//						{
//							Aimspot -= pEntity->GetAbsOrigin();
//							Aimspot += pEntity->GetNetworkOrigin();
//						}
//						Target_t target;
//						target.aimspot = Aimspot;
//						target.ent = pEntity;
//						possibleaimspots.emplace_back(target);
//
//					}
//				}
//			}
//		}
//
//		return flBestDamage;
//	}
//
//	void GetAtTargetsSpot(std::vector< Vector >& Targets)
//	{
//		if (!(int)Targets.size())
//			Target = Vector(0, 0, 0);
//		else
//		{
//			Target = Vector(8128, 8128, 8128);
//			for (Vector t : Targets)
//			{
//				if (t.Length() < Target.Length())
//					Target = t;
//			}
//		}
//	}
//
//	bool Fire(CInput::CUserCmd* cmd, Vector vecCurPos, std::vector< Target_t >& possibleaimspots)
//	{
//
//		//if (Options.Ragebot.Accuracy.bAutoStop)
//		//{
//		//	if (KEY_DOWN(Options.Ragebot.Accuracy.iAutoStopKey))
//		//	{
//		//		Hacks.CurrentCmd->forwardmove = 0;
//		//		Hacks.CurrentCmd->sidemove = 0;
//		//		Hacks.CurrentCmd->buttons = 0;
//		//	}
//		//}
//
//
//
//		int closest = 8129;
//		if ((!Options.Ragebot.Aimbot.bAutoShoot && !(cmd->buttons & IN_ATTACK)) || !Options.Ragebot.Aimbot.bAimbotEnable)
//			return true;
//		Vector Aimangles;
//		int originaltick = Hacks.CurrentCmd->tick_count;
//		int distance = -1;
//		static int Cycle = 0;
//		bool shot = false;
//		if (!Misc::bullettime())
//			return true;
//		int selection = Options.Ragebot.Aimbot.iSelection;
//		if (selection != 1)
//			for (int i = 0; i < possibleaimspots.size(); i++)
//			{
//				Target_t Aimspot = possibleaimspots[i];
//				Misc::CalcAngle(vecCurPos, Aimspot.aimspot, Aimangles);
//				distance = vecCurPos.DistTo(Aimspot.aimspot);
//				if (distance < closest)
//				{
//					int TempTick = originaltick;
//					if (Misc::GetNumberOfTicksChoked(Aimspot.ent) > 5 && Options.Ragebot.HvH.bPositionAdj)
//					{
//						float correct = Interfaces.pEngine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
//						TempTick = originaltick + Misc::GetNumberOfTicksChoked(Aimspot.ent) + Misc::TIME_TO_TICKS(fabs(correct));
//					}
//					Hacks.CurrentCmd->tick_count = TempTick;
//					cmd->viewangles = Aimangles;
//					pTarget = Aimspot.ent;
//					cmd->buttons |= IN_ATTACK;
//					Angles = cmd->viewangles;
//					shot = true;
//				}
//			}
//		else if (possibleaimspots.size() > 0)
//		{
//			Cycle++;
//			if (Cycle >= possibleaimspots.size())
//				Cycle = 0;
//			Target_t Aimspot = possibleaimspots[Cycle];
//			Misc::CalcAngle(vecCurPos, Aimspot.aimspot, Aimangles);
//			int TempTick = originaltick;
//			if (Misc::GetNumberOfTicksChoked(Aimspot.ent) > 5 && Options.Ragebot.HvH.bPositionAdj)
//			{
//				float correct = Interfaces.pEngine->GetNetChannelInfo()->GetLatency(FLOW_OUTGOING);
//				TempTick = originaltick + Misc::GetNumberOfTicksChoked(Aimspot.ent) + Misc::TIME_TO_TICKS(fabs(correct));
//			}
//			cmd->viewangles = Aimangles;
//			Angles = cmd->viewangles;
//			cmd->buttons |= IN_ATTACK;
//			shot = true;
//		}
//		return false;
//
//	}
//
//public:
//	Vector Target;
//	CBaseEntity* pTarget;
//	Vector Angles;
//
//	bool Aim(CInput::CUserCmd* cmd)
//	{
//		Angles = cmd->viewangles;
//		Vector vecCurPos = Hacks.LocalPlayer->GetEyePosition();
//		std::vector< Vector > Targets;
//		std::vector< Target_t > possibleaimspots;
//		std::vector< CBaseEntity* > possibletargets;
//		GetTargets(possibletargets);
//		GetAimSpots(Targets, possibleaimspots, possibletargets);
//		GetAtTargetsSpot(Targets);
//		if (Hacks.LocalWeapon->IsMiscWeapon())
//			return false;
//
//		if (Options.Ragebot.Aimbot.bAutoScope && Options.Ragebot.Aimbot.bAimbotEnable && Hacks.LocalWeapon->isSniper() && !Hacks.LocalPlayer->m_bIsScoped() && possibleaimspots.size() > 0)
//		{
//			Hacks.CurrentCmd->buttons |= IN_ATTACK2;
//			return false;
//		}
//		if (Hacks.LocalWeapon->hitchance() < Options.Ragebot.Accuracy.iHitchance)
//			return false;
//		return !Fire(cmd, vecCurPos, possibleaimspots);
//
//	}
//} Aimbot;
