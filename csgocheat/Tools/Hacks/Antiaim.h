#pragma once
#include "../../stdafx.h"
#include "../Menu/Menu.h"
#include "Misc.h"
#include "Aimbot.h"
#include "../Utils/LocalInfo.h"
#include "../Menu/SettingsManager.h"

#define KEY_DOWN(VK_NNM) ((GetAsyncKeyState(VK_NNM) & 0x8000) ? 1:0)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

class AntiAim
{
public:
	QAngle temp;
	bool start = false;
	bool jitter = false;
	bool flip = false;
	bool ShouldAA = true;
	int current = 0;
private:

	void MemeWalk()
	{
		if (Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER || Hacks.LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
			return;

		if (Hacks.CurrentCmd->forwardmove > 0)
		{
			Hacks.CurrentCmd->buttons |= IN_BACK;
			Hacks.CurrentCmd->buttons &= ~IN_FORWARD;
		}

		if (Hacks.CurrentCmd->forwardmove < 0)
		{
			Hacks.CurrentCmd->buttons |= IN_FORWARD;
			Hacks.CurrentCmd->buttons &= ~IN_BACK;
		}

		if (Hacks.CurrentCmd->sidemove < 0)
		{
			Hacks.CurrentCmd->buttons |= IN_MOVERIGHT;
			Hacks.CurrentCmd->buttons &= ~IN_MOVELEFT;
		}

		if (Hacks.CurrentCmd->sidemove > 0)
		{
			Hacks.CurrentCmd->buttons |= IN_MOVELEFT;
			Hacks.CurrentCmd->buttons &= ~IN_MOVERIGHT;
		}
	}

	void FakeWalk()
	{
		if (KEY_DOWN(Options.Ragebot.AntiAim.Misc.iFakeWalkKey) && Options.Ragebot.AntiAim.Misc.bFakeWalk)
		{
			static int iChoked = -1;
			iChoked++;

			if (iChoked < 3)
			{
				Hacks.SendPacket = false;
				Hacks.CurrentCmd->tick_count += 10;
				Hacks.CurrentCmd += 7 + Hacks.CurrentCmd->tick_count % 2 ? 0 : 1;
				Hacks.CurrentCmd->buttons |= Hacks.LocalPlayer->GetMoveType() == IN_BACK;
				Hacks.CurrentCmd->forwardmove = Hacks.CurrentCmd->sidemove = 0.f;
			}
			else
			{
				Hacks.SendPacket = true;
				iChoked = -1;
				Interfaces.pGlobalVars->frametime *= (Hacks.LocalPlayer->GetVecVelocity().Length2D()) / 1.f;
				Hacks.CurrentCmd->buttons |= Hacks.LocalPlayer->GetMoveType() == IN_FORWARD;
			}
		}
	}

	void Fakelag()
	{
		static int Ticks = 6;
		static int Ticks1 = 0;
		int ticksMax = 16;
		static Vector pos = Hacks.LocalPlayer->GetVecOrigin();
		int Factor = Options.Misc.Misc1.iFakeLagFactor;
		bool InAirOnly = Options.Misc.Misc1.bInAirOnly;
		int Mode = Options.Misc.Misc1.iFakeLag;
		switch (Mode)
		{
		case 0: // Off
			break;
		case 1: // Normal
			if (InAirOnly)
			{
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
					return;

				if (Factor > 0)
				{
					if (Ticks1 >= ticksMax)
					{
						Hacks.SendPacket = true;
						Ticks1 = 0;
					}
					else
					{
						int packetsToChoke;
						if (Hacks.LocalPlayer->GetVecVelocity().Length() > 0.f)
						{
							packetsToChoke = (int)((128.f / Interfaces.pGlobalVars->interval_per_tick) / Hacks.LocalPlayer->GetVecVelocity().Length()) + 1;
							if (packetsToChoke >= 15)
								packetsToChoke = 14;
							if (packetsToChoke < Factor)
								packetsToChoke = Factor;
						}
						else
							packetsToChoke = 0;

						Hacks.SendPacket = Ticks1 < 18 - packetsToChoke;;
					}
					Ticks1++;
				}
			}
			else
			{
				if (Factor > 0)
				{
					if (Ticks1 >= ticksMax)
					{
						Hacks.SendPacket = true;
						Ticks1 = 0;
					}
					else
					{
						int packetsToChoke;
						if (Hacks.LocalPlayer->GetVecVelocity().Length() > 0.f)
						{
							packetsToChoke = (int)((128.f / Interfaces.pGlobalVars->interval_per_tick) / Hacks.LocalPlayer->GetVecVelocity().Length()) + 1;
							if (packetsToChoke >= 15)
								packetsToChoke = 14;
							if (packetsToChoke < Factor)
								packetsToChoke = Factor;
						}
						else
							packetsToChoke = 0;

						Hacks.SendPacket = Ticks1 < 18 - packetsToChoke;;
					}
					Ticks1++;
				}
			}
			break;
		case 2: // Adaptive
			if (InAirOnly)
			{
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
					return;

				if (!(LocalInfo.Choked > 12))
					Hacks.SendPacket = false;

			}
			else
			{
				if (!(LocalInfo.Choked > 12))
					Hacks.SendPacket = false;
			}
			break;
		case 3: // Switch
			if (InAirOnly)
			{
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
					return;

				if (!((pos - LocalInfo.LastPos).Length2DSqr() > 4096.f) && !(LocalInfo.Choked > 12))
					Hacks.SendPacket = false;
			}
			else
			{
				if (!((pos - LocalInfo.LastPos).Length2DSqr() > 4096.f) && !(LocalInfo.Choked > 12))
					Hacks.SendPacket = false;
			}
			break;
		case 4: // Random
			if (InAirOnly)
			{
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
					return;

				if (LocalInfo.Choked > Ticks)
				{
					Ticks += ((rand() % 4) + 2) * ((rand() % 2) + 2);
					while (Ticks > 12)
						Ticks -= 7;
				}
				else
					Hacks.SendPacket = false;

			}
			else
			{
				if (LocalInfo.Choked > Ticks)
				{
					Ticks += ((rand() % 4) + 2) * ((rand() % 2) + 2);
					while (Ticks > 12)
						Ticks -= 7;
				}
				else
					Hacks.SendPacket = false;
			}
			break;
		case 5: // Fluctuate
			if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
			{
				Hacks.SendPacket = true;
			}
			else
			{
				Hacks.SendPacket = false;
			}
			break;
		}
		pos = Hacks.LocalPlayer->GetVecOrigin();
	}

	bool CanFireNext( CBaseEntity* pEntity)
	{
		CBaseCombatWeapon* pWeapon = pEntity->GetActiveBaseCombatWeapon();
		float flServerTime = pEntity->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
		float flNextShot = pWeapon->NextPrimaryAttack() - flServerTime;
		return flNextShot == 1;
	}

	void AtTarget(Vector& viewangles)
	{

		//if (Aimbot.Target != Vector(0, 0, 0))
		//{
		//	Misc::CalcAngle(Hacks.LocalPlayer->GetVecOrigin(), Aimbot.Target + Hacks.LocalPlayer->GetVecOrigin(), viewangles);
		//}

		QAngle angle = QAngle(0, 0, 0);
		float lowest = 99999999.f;
		Vector EyePos = Hacks.LocalPlayer->GetEyePosition() + Hacks.LocalPlayer->GetAbsOrigin();

		for (int i = 1; i < 65; i++) {
			if (i == Interfaces.pEngine->GetLocalPlayer()) continue;
			CBaseEntity* pEnt = Interfaces.pEntList->GetClientEntity(i);
			if (!pEnt) continue;
			if (pEnt->IsDormant()) continue;
			if (!pEnt->isAlive()) continue;
			if (pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam()) continue;

			Vector CurPos = pEnt->GetEyePosition() + pEnt->GetAbsOrigin();

			if (CurPos.DistToSqr(EyePos) < lowest) {
				lowest = CurPos.DistTo(EyePos);
				Misc::CalcAngle(EyePos, CurPos, angle);
			}
		}
	}
	
	void DoAA(int style, Vector& view)
	{
		long currentTime_ms = std::chrono::duration_cast< std::chrono::seconds >(std::chrono::system_clock::now().time_since_epoch()).count();
		static long timeStamp = currentTime_ms;

		timeStamp = currentTime_ms;

		int yaw = 0;
		int pitch = 0;
		int maxJitter;
		int random;
		float temp;
		double factor;
		static int SpinYaw = 0;
		static float StoredAng = 0;
		static bool fake;
		fake = !fake;

		//static int jitter = 0;
		static int last = 0;
		int help = {};
		int Fake = rand() % 3;
		static int Spin[2] = { 0, 0 };
		for (int& s : Spin)
			if (s > 180)
				s -= 360;
			else if (s < -180)
				s += 360;

		Hacks.SendPacket = true;

		// Stand Anti-Anon huehuehuehue
		if (style == 0)
		{
			int iFakeYawAdd = Options.Ragebot.AntiAim.Stand.iFakeYawAdd;
			int iYawAdd = Options.Ragebot.AntiAim.Stand.iYawAdd;

			if (fake)
			{
				Hacks.SendPacket = true;

				switch (Options.Ragebot.AntiAim.Stand.iFakeYaw)
				{
				case 0:
					break;
				case 1: // 180
					yaw = 180.f - Options.Ragebot.AntiAim.Stand.iFakeYawAdd;
					break;
				case 2: // Backwards Jitter
					yaw -= 180 - Options.Ragebot.AntiAim.Stand.iFakeYawAdd;
					random = rand() % 100;
					maxJitter = rand() % (85 - 70 + 1) + 70;
					temp = maxJitter - (rand() % maxJitter);
					if (random < 35 + (rand() % 15))
						yaw -= temp;
					else if (random < 85 + (rand() % 15))
						yaw += temp;
					break;
				case 3: // Sideways
					if (Options.Ragebot.AntiAim.Stand.iFakeYawAdd >= 35 && Options.Ragebot.AntiAim.Stand.iFakeYawAdd <= 95)
						yaw = 90;
					else if (Options.Ragebot.AntiAim.Stand.iFakeYawAdd <= -35 && Options.Ragebot.AntiAim.Stand.iFakeYawAdd >= -95)
						yaw = -90;
					break;
				case 4: // Random
					switch (timeStamp % 8)
					{
					case 1: yaw -= rand() % ((45 - 1) + 1) + 1;  break;
					case 2: yaw -= 10;  break;
					case 3: yaw -= rand() % ((135 - 45) + 1) + 1;  break;
					case 4: yaw -= 10;  break;
					case 5: yaw -= rand() % ((180 - 135) + 1) + 1;  break;
					case 6: yaw -= 10;  break;
					case 7: yaw -= rand() % ((270 - 270) + 1) + 1;  break;
					case 8: yaw -= 10;  break;
					}
					break;
				case 5: // Localview
					yaw = Hacks.CurrentCmd->viewangles.y;
					break;
				case 6: // Static
					yaw = Options.Ragebot.AntiAim.Stand.iFakeYawAdd;
					break;
				case 7: // Opposite
					if (Options.Ragebot.AntiAim.Stand.iYaw == 1)
					{
						yaw = 0 + Options.Ragebot.AntiAim.Stand.iYawAdd;
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 2)
					{
						yaw = 0 + iFakeYawAdd;
						random = rand() % 100;
						maxJitter = rand() % (85 - 70 + 1) + 70;
						temp = maxJitter - (rand() % maxJitter);
						if (random < 35 + (rand() % 15))
							yaw -= temp;
						else if (random < 85 + (rand() % 15))
							yaw += temp;
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 3)
					{
						if (flip)
							SpinYaw -= 90;
						else
							SpinYaw += 90;
						flip != flip;
						StoredAng = SpinYaw;
						yaw = SpinYaw;
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 4)
					{
						if (Options.Ragebot.AntiAim.Stand.iYawAdd >= 35 && Options.Ragebot.AntiAim.Stand.iYawAdd <= 95)
							yaw = -90;
						else if (Options.Ragebot.AntiAim.Stand.iYawAdd <= -35 && Options.Ragebot.AntiAim.Stand.iYawAdd >= -95)
							yaw = 90;
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 5)
					{
						yaw -= rand();
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 6)
					{
						yaw -= Options.Ragebot.AntiAim.Stand.iYawAdd;
					}
					else if (Options.Ragebot.AntiAim.Stand.iYaw == 7)
					{
						switch (timeStamp % 8)
						{
						case 1: yaw -= rand() % ((45 - 1) + 1) + 1;  break;
						case 2: yaw -= 10;  break;
						case 3: yaw -= rand() % ((135 - 45) + 1) + 1;  break;
						case 4: yaw -= 10;  break;
						case 5: yaw -= rand() % ((180 - 135) + 1) + 1;  break;
						case 6: yaw -= 10;  break;
						case 7: yaw -= rand() % ((270 - 270) + 1) + 1;  break;
						case 8: yaw -= 10;  break;
						}
					}
					break;
				}
			}
			else
			{
				Hacks.SendPacket = false;

				switch (Options.Ragebot.AntiAim.Stand.iYaw)
				{
				case 0:
					break;
				case 1: // Backwards
					yaw = 180.f - Options.Ragebot.AntiAim.Stand.iYawAdd;
					break;
				case 2: // Backwards Jitter
					yaw -= 180 - Options.Ragebot.AntiAim.Stand.iYawAdd;
					random = rand() % 100;
					maxJitter = rand() % (85 - 70 + 1) + 70;
					temp = maxJitter - (rand() % maxJitter);
					if (random < 35 + (rand() % 15))
						yaw -= temp;
					else if (random < 85 + (rand() % 15))
						yaw += temp;
					break;
				case 3: // Spin
					if (flip)
						SpinYaw -= 35;
					else
						SpinYaw += 35;
					flip != flip;
					StoredAng = SpinYaw;
					yaw = SpinYaw;
					break;
				case 4: // Sideways
					if (Options.Ragebot.AntiAim.Stand.iYawAdd >= 35 && Options.Ragebot.AntiAim.Stand.iYawAdd <= 95)
						yaw = 90;
					else if (Options.Ragebot.AntiAim.Stand.iYawAdd <= -35 && Options.Ragebot.AntiAim.Stand.iYawAdd >= -95)
						yaw = -90;
					break;
				case 5: // Random
					yaw = rand();
					break;
				case 6: // Static
					yaw = Options.Ragebot.AntiAim.Stand.iYawAdd;
					break;
				case 7: // Backwards Corruption
					switch (timeStamp % 8)
					{
					case 1: yaw = 170 + rand() % ((90 - 1) + 1) + 1;  break;
					case 2: yaw = 180;  break;
					case 3: yaw = 170 + rand() % ((180 - 90) + 1) + 1;  break;
					case 4: yaw = 180;  break;
					case 5: yaw = 170 + rand() % (((-90) - (-180)) + 1) + 1;  break;
					case 6: yaw = 180;  break;
					case 7: yaw = 170 + rand() % (((-1) - (-90)) + 1) + 1;  break;
					case 8: yaw = 180;  break;
					}
					break;
				}
			}

			switch (Options.Ragebot.AntiAim.Stand.iPitch)
			{
			case 0:
				break;
			case 1: //down
				pitch = 88.99f;
				break;
			case 2: //up
				pitch = -88.99f;
				break;
			case 3: // Minimal
				pitch = 89;
				if (Hacks.LocalWeapon->isSniper())
					pitch = 85;
				else if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW())
					pitch = 80;
				else if (Hacks.LocalWeapon->isPistol())
					pitch = 89;
				else if (Hacks.LocalWeapon->isMachineW())
					pitch = 78.50;
				else if (Hacks.LocalWeapon->isShotgun())
					pitch = 75.00;
				break;
			case 4:
				pitch = rand();
				break;
			case 5: // Fake Down
				pitch = -991;
				break;
			case 6: // Fake Up
				pitch = 991;
				break;
			case 7: // Fake Zero
				pitch = 1080;
				break;
			}


			if (Options.Ragebot.AntiAim.Stand.bAtTargets)
				AtTarget(view);
		}

		// Move Anti-Anon huehuehuehue
		else if (style == 1) 
		{
			int iFakeYawAdd = Options.Ragebot.AntiAim.Move.iFakeYawAdd;
			int iYawAdd = Options.Ragebot.AntiAim.Move.iYawAdd;
			if (fake)
			{
				Hacks.SendPacket = true;

				switch (Options.Ragebot.AntiAim.Move.iFakeYaw)
				{
				case 0:
					break;
				case 1: // 180
					yaw = 180.f - Options.Ragebot.AntiAim.Move.iFakeYawAdd;
					break;
				case 2: // Backwards Jitter
					yaw -= 180 - Options.Ragebot.AntiAim.Move.iFakeYawAdd;
					random = rand() % 100;
					maxJitter = rand() % (85 - 70 + 1) + 70;
					temp = maxJitter - (rand() % maxJitter);
					if (random < 35 + (rand() % 15))
						yaw -= temp;
					else if (random < 85 + (rand() % 15))
						yaw += temp;
					break;
				case 3: // Sideways
					if (Options.Ragebot.AntiAim.Move.iFakeYawAdd >= 35 && Options.Ragebot.AntiAim.Move.iFakeYawAdd <= 95)
						yaw = 90;
					else if (Options.Ragebot.AntiAim.Move.iFakeYawAdd <= -35 && Options.Ragebot.AntiAim.Move.iFakeYawAdd >= -95)
						yaw = -90;
					break;
				case 4: // Random
					switch (timeStamp % 8)
					{
					case 1: yaw -= rand() % ((45 - 1) + 1) + 1;  break;
					case 2: yaw -= 10;  break;
					case 3: yaw -= rand() % ((135 - 45) + 1) + 1;  break;
					case 4: yaw -= 10;  break;
					case 5: yaw -= rand() % ((180 - 135) + 1) + 1;  break;
					case 6: yaw -= 10;  break;
					case 7: yaw -= rand() % ((270 - 270) + 1) + 1;  break;
					case 8: yaw -= 10;  break;
					}
					break;
				case 5: // Localview
					yaw = Hacks.CurrentCmd->viewangles.y;
					break;
				case 6: // Static
					yaw = Options.Ragebot.AntiAim.Move.iFakeYawAdd;
					break;
				case 7: // Opposite
					if (Options.Ragebot.AntiAim.Move.iYaw == 1)
					{
						yaw = 0 + Options.Ragebot.AntiAim.Move.iFakeYawAdd;
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 2)
					{
						yaw = 0 + iFakeYawAdd;
						random = rand() % 100;
						maxJitter = rand() % (85 - 70 + 1) + 70;
						temp = maxJitter - (rand() % maxJitter);
						if (random < 35 + (rand() % 15))
							yaw -= temp;
						else if (random < 85 + (rand() % 15))
							yaw += temp;
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 3)
					{
						if (flip)
							SpinYaw -= 90;
						else
							SpinYaw += 90;
						flip != flip;
						StoredAng = SpinYaw;
						yaw = SpinYaw;
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 4)
					{
						if (Options.Ragebot.AntiAim.Move.iYawAdd >= 35 && Options.Ragebot.AntiAim.Move.iYawAdd <= 95)
							yaw = -90;
						else if (Options.Ragebot.AntiAim.Move.iYawAdd <= -35 && Options.Ragebot.AntiAim.Move.iYawAdd >= -95)
							yaw = 90;
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 5)
					{
						yaw -= rand();
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 6)
					{
						yaw -= Options.Ragebot.AntiAim.Move.iYawAdd;
					}
					else if (Options.Ragebot.AntiAim.Move.iYaw == 7)
					{
						switch (timeStamp / 2 % 8)
						{
						case 1: yaw -= 0 - rand() % ((90 - 1) + 1) + 1;  break;
						case 2: yaw -= 0;  break;
						case 3: yaw -= 0 - rand() % ((180 - 90) + 1) + 1;  break;
						case 4: yaw -= 0;  break;
						case 5: yaw -= 0 - rand() % (((-90) - (-180)) + 1) + 1;  break;
						case 6: yaw -= 0;  break;
						case 7: yaw -= 0 - rand() % (((-1) - (-90)) + 1) + 1;  break;
						case 8: yaw -= 0;  break;
						}
					}
					break;
				}
			}
			else
			{
				Hacks.SendPacket = false;

				switch (Options.Ragebot.AntiAim.Move.iYaw)
				{
				case 0:
					break;
				case 1: // Backwards
					yaw = 180.f - Options.Ragebot.AntiAim.Move.iYawAdd;
					break;
				case 2: // Backwards Jitter
					yaw -= 180 - Options.Ragebot.AntiAim.Move.iYawAdd;
					random = rand() % 100;
					maxJitter = rand() % (85 - 70 + 1) + 70;
					temp = maxJitter - (rand() % maxJitter);
					if (random < 35 + (rand() % 15))
						yaw -= temp;
					else if (random < 85 + (rand() % 15))
						yaw += temp;
				break;
				case 3: // Spin
					if (flip)
						SpinYaw -= 35;
					else
						SpinYaw += 35;
					flip != flip;
					StoredAng = SpinYaw;
					yaw = SpinYaw;
					break;
				case 4: // Sideways
					if (Options.Ragebot.AntiAim.Move.iFakeYawAdd >= 35 && Options.Ragebot.AntiAim.Move.iFakeYawAdd <= 95)
						yaw = 90;
					else if (Options.Ragebot.AntiAim.Move.iFakeYawAdd <= -35 && Options.Ragebot.AntiAim.Move.iFakeYawAdd >= -95)
						yaw = -90;
					break;
				case 5: // Random
					yaw = rand();
					break;
				case 6: // Static
					yaw = Options.Ragebot.AntiAim.Move.iYawAdd;
					break;
				case 7: // Backwards Corruption
					switch (timeStamp % 8)
					{
					case 1: yaw = 170 + rand() % ((90 - 1) + 1) + 1;  break;
					case 2: yaw = 180;  break;
					case 3: yaw = 170 + rand() % ((180 - 90) + 1) + 1;  break;
					case 4: yaw = 180;  break;
					case 5: yaw = 170 + rand() % (((-90) - (-180)) + 1) + 1;  break;
					case 6: yaw = 180;  break;
					case 7: yaw = 170 + rand() % (((-1) - (-90)) + 1) + 1;  break;
					case 8: yaw = 180;  break;
					}
					break;
				}
			}

			switch (Options.Ragebot.AntiAim.Move.iPitch)
			{
			case 0:
				break;
			case 1: //down
				pitch = 88.99f;
				break;
			case 2: //up
				pitch = -88.99f;
				break;
			case 3: // Minimal
				pitch = 89;
				if (Hacks.LocalWeapon->isSniper())
					pitch = 85;
				else if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW())
					pitch = 80;
				else if (Hacks.LocalWeapon->isPistol())
					pitch = 89;
				else if (Hacks.LocalWeapon->isMachineW())
					pitch = 78.50;
				else if (Hacks.LocalWeapon->isShotgun())
					pitch = 75.00;
				break;
			case 4:
				pitch = rand();
				break;
			case 5: // Fake Down
				pitch = -991;
				break;
			case 6: // Fake Up
				pitch = 991;
				break;
			case 7: // Fake Zero
				pitch = 1080;
				break;
			}
	
			if (Options.Ragebot.AntiAim.Move.bAtTargets)
				AtTarget(view);
		}
		
		//Hacks.CurrentCmd->viewangles.y = view.y + yaw;
		Hacks.CurrentCmd->viewangles.y = view.y + yaw;
		Hacks.CurrentCmd->viewangles.x = pitch;

	}

	bool isEdging(CBaseEntity* pLocalBaseEntity, CInput::CUserCmd* cmd, float flWall, float flCornor, bool& bSendPacket, Vector& view)
	{
		Ray_t ray;
		trace_t tr;

		bool isEdging;

		CTraceFilter traceFilter;
		traceFilter.pSkip = pLocalBaseEntity;

		auto bRetVal = false;
		auto vecCurPos = pLocalBaseEntity->GetEyePosition();
		Vector meme = cmd->viewangles;
		Misc::NormalizeVector(meme);
		int iPitch = Options.Ragebot.AntiAim.Edge.iPitch;
		int iYaw = Options.Ragebot.AntiAim.Edge.iYaw;
		int iFakeYaw = Options.Ragebot.AntiAim.Edge.iFakeYaw;
		int random;
		float setyaw = 0;
		float setpitch = 0;
		bool switchb = cmd->command_number % 2;

		for (float i = 0; i < 360; i += 2)
		{
			Vector vecDummy(10.f, meme.y, 0.f);
			vecDummy.y += i;

			Misc::NormalizeVector(vecDummy);

			Vector vecForward;
			Misc::AngleVectors3(vecDummy, vecForward);

			auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
			vecForward *= flLength;

			ray.Init(vecCurPos, (vecCurPos + vecForward));
			Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter *)&traceFilter, &tr);

			if (tr.fraction != 1.0f)
			{
				Vector qAngles;
				auto vecNegate = tr.plane.normal;

				vecNegate *= -1.f;
				Misc::VectorAngles3(vecNegate, qAngles);

				vecDummy.y = qAngles.y;

				Misc::NormalizeVector(vecDummy);
				trace_t leftTrace, rightTrace;

				Vector vecLeft;
				Misc::AngleVectors3(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);

				Vector vecRight;
				Misc::AngleVectors3(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);

				vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
				vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

				ray.Init(vecCurPos, (vecCurPos + vecLeft));
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &leftTrace);

				ray.Init(vecCurPos, (vecCurPos + vecRight));
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &rightTrace);

				if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
					vecDummy.y -= flCornor; // left
				else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
					vecDummy.y += flCornor; // right			
				cmd->viewangles.x = setpitch;
				cmd->viewangles.y = vecDummy.y + setyaw;
				bRetVal = true;
			}
		}
		return bRetVal;

		isEdging = true;
	}

	bool Edge(CBaseEntity* pLocalBaseEntity, CInput::CUserCmd* cmd, float flWall, float flCornor, bool& bSendPacket, Vector& view)
	{
		long currentTime_ms = std::chrono::duration_cast< std::chrono::seconds >(std::chrono::system_clock::now().time_since_epoch()).count();
		static long timeStamp = currentTime_ms;

		timeStamp = currentTime_ms;

		static int SpinYaw = 0;
		static float StoredAng = 0;
		static bool fake;
		fake = !fake;

		//static int jitter = 0;
		static int last = 0;
		int help = {};
		int Fake = rand() % 3;
		static int Spin[2] = { 0, 0 };
		for (int& s : Spin)
			if (s > 180)
				s -= 360;
			else if (s < -180)
				s += 360;

		Hacks.SendPacket = true;

		Ray_t ray;
		trace_t tr;

		CTraceFilter traceFilter;
		traceFilter.pSkip = pLocalBaseEntity;

		auto bRetVal = false;
		auto vecCurPos = pLocalBaseEntity->GetEyePosition();
		Vector meme = cmd->viewangles;
		Misc::NormalizeVector(meme);
		int iPitch = Options.Ragebot.AntiAim.Edge.iPitch;
		int iYaw = Options.Ragebot.AntiAim.Edge.iYaw;
		int iFakeYaw = Options.Ragebot.AntiAim.Edge.iFakeYaw;
		int maxJitter;
		int random;
		float temp;
		double factor;
		float setyaw = 0;
		float setpitch = 0;
		bool switchb = cmd->command_number % 2;

		int iFakeYawAdd = Options.Ragebot.AntiAim.Edge.iFakeYawAdd;
		int iYawAdd = Options.Ragebot.AntiAim.Edge.iYawAdd;
		if (fake)
		{
			Hacks.SendPacket = true;

			switch (Options.Ragebot.AntiAim.Edge.iFakeYaw)
			{
			case 0:
				break;
			case 1: // Forwards
				setyaw = 0 - Options.Ragebot.AntiAim.Edge.iFakeYawAdd;
				break;
			case 2: // Backwards
				setyaw = 180 - Options.Ragebot.AntiAim.Edge.iFakeYawAdd;
				break;
			case 3: // Backwards Jitter
				setyaw -= 180 - Options.Ragebot.AntiAim.Edge.iFakeYawAdd;
				random = rand() % 100;
				maxJitter = rand() % (85 - 70 + 1) + 70;
				temp = maxJitter - (rand() % maxJitter);
				if (random < 35 + (rand() % 15))
					setyaw -= temp;
				else if (random < 85 + (rand() % 15))
					setyaw += temp;
				break;
			case 4: // Sideways
				if (Options.Ragebot.AntiAim.Edge.iFakeYawAdd >= 35 && Options.Ragebot.AntiAim.Edge.iFakeYawAdd <= 95)
					setyaw = 90;
				else if (Options.Ragebot.AntiAim.Edge.iFakeYawAdd <= -35 && Options.Ragebot.AntiAim.Edge.iFakeYawAdd >= -95)
					setyaw = -90;
				break;
			case 5: // Random
				setyaw = rand();
				break;
			case 6: // Localview
				setyaw = Hacks.CurrentCmd->viewangles.y;
				break;
			case 7: // Static
				setyaw = Options.Ragebot.AntiAim.Edge.iFakeYaw;
				break;
			case 8:
				if (Options.Ragebot.AntiAim.Edge.iYaw == 1)
				{
					setyaw = 180 - Options.Ragebot.AntiAim.Edge.iYawAdd;
				}
				if (Options.Ragebot.AntiAim.Edge.iYaw == 2)
				{
					setyaw = 0 - Options.Ragebot.AntiAim.Edge.iYawAdd;
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 3)
				{
					setyaw = 0 - iFakeYawAdd;
					random = rand() % 100;
					maxJitter = rand() % (85 - 70 + 1) + 70;
					temp = maxJitter - (rand() % maxJitter);
					if (random < 35 + (rand() % 15))
						setyaw -= temp;
					else if (random < 85 + (rand() % 15))
						setyaw += temp;
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 5)
				{
					if (flip)
						SpinYaw -= 90;
					else
						SpinYaw += 90;
					flip != flip;
					StoredAng = SpinYaw;
					setyaw = SpinYaw;
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 6)
				{
					if (Options.Ragebot.AntiAim.Edge.iYawAdd >= 35 && Options.Ragebot.AntiAim.Edge.iYawAdd <= 95)
						setyaw = -90;
					else if (Options.Ragebot.AntiAim.Edge.iYawAdd <= -35 && Options.Ragebot.AntiAim.Edge.iYawAdd >= -95)
						setyaw = 90;
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 7)
				{
					setyaw -= rand();
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 8)
				{
					setyaw -= Options.Ragebot.AntiAim.Edge.iYawAdd;
				}
				else if (Options.Ragebot.AntiAim.Edge.iYaw == 9)
				{
					switch (timeStamp % 8)
					{
					case 1: setyaw -= 0 - rand() % ((90 - 1) + 1) + 1;  break;
					case 2: setyaw -= 0;  break;
					case 3: setyaw -= 0 - rand() % ((180 - 90) + 1) + 1;  break;
					case 4: setyaw -= 0;  break;
					case 5: setyaw -= 0 - rand() % (((-90) - (-180)) + 1) + 1;  break;
					case 6: setyaw -= 0;  break;
					case 7: setyaw -= 0 - rand() % (((-1) - (-90)) + 1) + 1;  break;
					case 8: setyaw -= 0;  break;
					}
				}
				break;
			}
		}
		else
		{
			Hacks.SendPacket = false;

			switch (Options.Ragebot.AntiAim.Edge.iYaw)
			{
			case 0:
				break;
			case 1: // Forward
				setyaw = 0 - Options.Ragebot.AntiAim.Edge.iYawAdd;
				break;
			case 2: // Backwards
				setyaw = 180 - Options.Ragebot.AntiAim.Edge.iYawAdd;
				break;
			case 3: // Backwards Jitter
			{
				setyaw = 180 + iFakeYawAdd;
				random = rand() % 100;
				maxJitter = rand() % (85 - 70 + 1) + 70;
				temp = maxJitter - (rand() % maxJitter);
				if (random < 35 + (rand() % 15))
					setyaw -= temp;
				else if (random < 85 + (rand() % 15))
					setyaw += temp;
			}
			break;
			case 4: // Spin
				if (flip)
					SpinYaw -= 35;
				else
					SpinYaw += 35;
				flip != flip;
				StoredAng = SpinYaw;
				setyaw = SpinYaw;
				break;
			case 5: // Sideways
				if (Options.Ragebot.AntiAim.Edge.iFakeYawAdd >= 35 && Options.Ragebot.AntiAim.Edge.iFakeYawAdd <= 95)
					setyaw = 90;
				else if (Options.Ragebot.AntiAim.Edge.iFakeYawAdd <= -35 && Options.Ragebot.AntiAim.Edge.iFakeYawAdd >= -95)
					setyaw = -90;
				break;
			case 6: // Random
				setyaw = rand();
				break;
			case 7: // Static
				setyaw = Options.Ragebot.AntiAim.Edge.iYawAdd;
				break;
			case 8: // Backwards Corruption
				switch (timeStamp % 8)
				{
				case 1: setyaw = 170 + rand() % ((90 - 1) + 1) + 1;  break;
				case 2: setyaw = 180;  break;
				case 3: setyaw = 170 + rand() % ((180 - 90) + 1) + 1;  break;
				case 4: setyaw = 180;  break;
				case 5: setyaw = 170 + rand() % (((-90) - (-180)) + 1) + 1;  break;
				case 6: setyaw = 180;  break;
				case 7: setyaw = 170 + rand() % (((-1) - (-90)) + 1) + 1;  break;
				case 8: setyaw = 180;  break;
				}
				break;
			}
		}

		switch (Options.Ragebot.AntiAim.Edge.iPitch)
		{
		case 0:
			break;
		case 1: //down
			setpitch = 88.99f;
			break;
		case 2: //up
			setpitch = -88.99f;
			break;
		case 3: // Minimal
			setpitch = 89;
			if (Hacks.LocalWeapon->isSniper())
				setpitch = 85;
			else if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW())
				setpitch = 80;
			else if (Hacks.LocalWeapon->isPistol())
				setpitch = 89;
			else if (Hacks.LocalWeapon->isMachineW())
				setpitch = 78.50;
			else if (Hacks.LocalWeapon->isShotgun())
				setpitch = 75.00;
			break;
		case 4:
			setpitch = rand();
			break;
		case 5: // Fake Down
			setpitch = -991;
			break;
		case 6: // Fake Up
			setpitch = 991;
			break;
		case 7: // Fake Zero
			setpitch = 1080;
			break;
		}

		Hacks.CurrentCmd->viewangles.y = view.y + setyaw;
		Hacks.CurrentCmd->viewangles.x = setpitch;

		for (float i = 0; i < 360; i += 2)
		{
			Vector vecDummy(10.f, meme.y, 0.f);
			vecDummy.y += i;

			Misc::NormalizeVector(vecDummy);

			Vector vecForward;
			Misc::AngleVectors3(vecDummy, vecForward);

			auto flLength = ((16.f + 3.f) + ((16.f + 3.f) * sin(DEG2RAD(10.f)))) + 7.f;
			vecForward *= flLength;

			ray.Init(vecCurPos, (vecCurPos + vecForward));
			Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter *)&traceFilter, &tr);

			if (tr.fraction != 1.0f)
			{
				Vector qAngles;
				auto vecNegate = tr.plane.normal;

				vecNegate *= -1.f;
				Misc::VectorAngles3(vecNegate, qAngles);

				vecDummy.y = qAngles.y;

				Misc::NormalizeVector(vecDummy);
				trace_t leftTrace, rightTrace;

				Vector vecLeft;
				Misc::AngleVectors3(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);

				Vector vecRight;
				Misc::AngleVectors3(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);

				vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
				vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

				ray.Init(vecCurPos, (vecCurPos + vecLeft));
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &leftTrace);

				ray.Init(vecCurPos, (vecCurPos + vecRight));
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&traceFilter, &rightTrace);

				if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
					vecDummy.y -= flCornor; // left
				else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
					vecDummy.y += flCornor; // right			
				cmd->viewangles.x = setpitch;
				cmd->viewangles.y = vecDummy.y + setyaw;
				bRetVal = true;
			}
		}
		return bRetVal;
	}
	
public:
	void Run()
	{
		if (Options.Ragebot.AntiAim.Move.bMemeWalk)
			MemeWalk();
		if (Options.Ragebot.AntiAim.Misc.bFakeWalk)
			FakeWalk();
		if (Options.Misc.Misc2.bBlockBot && GetAsyncKeyState(Options.Misc.Misc2.iBlockBotKey))
			return;
		if( Hacks.LocalPlayer->GetMoveType() == MOVETYPE_LADDER || Hacks.LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP)
			return;
		if (Hacks.CurrentCmd->buttons & IN_USE)
			return;
		ShouldAA = true;
		Vector view = Hacks.CurrentCmd->viewangles;
		isEdging(Hacks.LocalPlayer, Hacks.CurrentCmd, 0.f, 90.f, Hacks.SendPacket, view);
		if (ShouldAA)
		{
			if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 80 && Options.Ragebot.AntiAim.Stand.bEnableAntiAim)
				DoAA(0, view);
			else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 80 && Options.Ragebot.AntiAim.Move.bEnableAntiAim)
				DoAA(1, view);
			if(isEdging(Hacks.LocalPlayer, Hacks.CurrentCmd, 0.f, 90.f, Hacks.SendPacket, view))
				if (Options.Ragebot.AntiAim.Edge.bEnableEdge)
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 300 && (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						bool bEdge = Edge(Hacks.LocalPlayer, Hacks.CurrentCmd, 0.f, 90.f, Hacks.SendPacket, view);
						if (bEdge)
							return;
					}
				}
		}
		Fakelag();
	}
} AA;
