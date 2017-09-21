#pragma once
#include "../../stdafx.h"
#include <chrono>
#include <ctime>
#include <time.h>

#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

class Misc
{
	typedef bool(__cdecl* ServerRankRevealAllFn)(float*);

public:

	static vec_t Normalize_y(vec_t ang)
	{
		while (ang < -180.0f)
			ang += 360.0f;
		while (ang > 180.0f)
			ang -= 360.0f;
		return ang;
	}

	static void setName(const char* name)
	{
		auto namevar = Interfaces.g_ICVars->FindVar("name");
		*reinterpret_cast<int*>(reinterpret_cast<DWORD>(&namevar->fnChangeCallback) + 0xC) = 0;
		namevar->SetValue(name);
	}

	static void ServerRankReveal()
	{
		if (!Interfaces.pEngine->IsInGame() || !Interfaces.pEngine->IsConnected())
			return;

		if (!Options.Visuals.VisualsMisc.bRankReveal)
			return;

		if (GetAsyncKeyState(VK_TAB) == 0)
			return;

		static float fArray[3] = { 0.f, 0.f, 0.f };

		static DWORD ServerRankReveal = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL);//Utils.PFindPattern( "client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? ");
		if (ServerRankReveal == 0)
			ServerRankReveal = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x55\x8B\xEC\x8B\x0D\x00\x00\x00\x00\x68\x00\x00\x00\x00", "xxxxx????x????", NULL, NULL);//Utils.PFindPattern( "client.dll", "55 8B EC 8B 0D ? ? ? ? 68 ? ? ? ? ");

		if (ServerRankReveal != 0)
		{
			Hacks.ServerRankRevealEx = (ServerRankRevealAllFn)(ServerRankReveal);
			Hacks.ServerRankRevealEx(fArray);
		}
	}

	static void SetClanTag(const char* tag, const char* name)
	{
		static auto pSetClanTag = reinterpret_cast<void(__fastcall*)(const char*, const char*)>((DWORD)(Utils.PFindPattern("engine.dll", "53 56 57 8B DA 8B F9 FF 15")));
		pSetClanTag(tag, name);
	}

	static int TIME_TO_TICKS(int dt)
	{
		return (int)(0.5f + (float)(dt) / Interfaces.pGlobalVars->interval_per_tick);
	}

	static float GetNetworkLatency()
	{
		INetChannelInfo* nci = Interfaces.pEngine->GetNetChannelInfo();
		if (nci)
		{
			return nci->GetAvgLatency(FLOW_OUTGOING);
		}
		return 0.0f;
	}

	static void ClantagChanger()
	{
		if (!Interfaces.pEngine->IsConnected() || !Interfaces.pEngine->IsInGame())
			return;
		if (Options.Misc.Misc1.bClanTag && Options.Misc.Misc1.bCorruption)
		{
			static int counter = 0;
			static int motion = 0;
			int ServerTime = (float)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

			if (counter % 48 == 0)
				motion++;
			int value = ServerTime % 21;
			// !<>-_\\/[]{}$#________$$$$
			switch (value) {
			case 0: SetClanTag("Astrium.cc", "Astrium.cc"); break;
			case 1: SetClanTag("=s&r/u}.cc", "=s&r/u}.cc"); break;
			case 2: SetClanTag("As_(i&m.cc", "As_(i&m.cc"); break;
			case 3: SetClanTag("?s=riu}.cc", "?s=riu}.cc"); break;
			case 4: SetClanTag("Astrium.cc", "Astrium.cc"); break;
			case 5: SetClanTag("$´ri?m.cc", "$´ri?m.cc"); break;
			case 6: SetClanTag(".s&ri%m.cc", ".s&ri%m.cc"); break;
			case 7: SetClanTag("A§t!]u,.cc", "A§t!]u,.cc"); break;
			case 8: SetClanTag("Astrium.cc", "Astrium.cc"); break;
			case 9: SetClanTag("A/t~[u}m.cc", "A/t~[u}m.cc"); break;
			case 10:SetClanTag("#s*ri§&.cc", "#s*ri§&.cc"); break;
			case 11:SetClanTag("A+/ri)m.cc", "A+/ri)m.cc"); break;
			case 12:SetClanTag("Astrium.cc", "Astrium.cc"); break;
			case 13:SetClanTag("A&t§=um.cc", "A&t§=um.cc"); break;
			case 14:SetClanTag("A!t&i%m.cc", "A!t&i%m.cc"); break;
			case 15:SetClanTag("As[r}[m.cc", "As[r}[m.cc"); break;
			case 16:SetClanTag("Astrium.cc", "Astrium.cc"); break;
			case 17:SetClanTag("Ast}i?\.cc", "Ast}i?\.cc"); break;
			case 18:SetClanTag("A]t³i\m.cc", "A]t³i\m.cc"); break;
			case 19:SetClanTag("A(%ri/m.cc", "A(%ri/m.cc"); break;
			case 20:SetClanTag("Astrium.cc", "Astrium.cc"); break;
			}
			counter++;
		}

		long currentTime_ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
		static long timeStamp = currentTime_ms;
		if (currentTime_ms - timeStamp < 350)
			return;


		timeStamp = currentTime_ms;
		if (Options.Misc.Misc1.bClanTag && !Options.Misc.Misc1.bCorruption)
		{
			static int Cycle = 0;
			std::vector< string > Strings =
			{
				string("Astrium"),
				string("Astrium.cc"),
				string("\n"),
				string("\t\t\t\t"),
				string(":)\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t\t")
			};

			int iSwitch = Options.Misc.Misc1.iClanTagSelection;

			string String = Strings[iSwitch];

			if (Options.Misc.Misc1.bClanTagAnimation)
			{
				int iMinor = Strings[iSwitch].size();
				int iMajor = iMinor + 1;

				Cycle++;
				if (Cycle > iMinor)
					Cycle = -iMajor;
				String = string(iMinor, ' ');
				for (int i = 0; i < Strings[iSwitch].size(); i++)
				{
					int New = i + Cycle;
					if (New >= 0 && New < iMinor)
						String[New] = Strings[iSwitch][i];
				}
			}
			SetClanTag(String.c_str(), Hacks.LocalPlayer->GetName().c_str());
		}
	}

	static void NameSpam()
	{
		if (!(Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame()))
			return;
		int NameSpam = Options.Misc.Misc2.iNameSpam;
		switch (NameSpam)
		{
			static bool Spam;

		case 0:
			return;
			break;
		case 1:
			if (Spam)
			{
				setName("\x01\x0B\x0D""A""\x0D""S""\x0D""T""\x0D""R""\x0D""I""\x0D""U""\x0D""M""\x0D"".""\x0D""C""\x0D""C""\x0D ");
				Spam = false;
			}
			else
			{
				setName(" \x01\x0B\x0D""A""\x0D""S""\x0D""T""\x0D""R""\x0D""I""\x0D""U""\x0D""M""\x0D"".""\x0D""C""\x0D""C""\x0D");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 2:
			if (Spam)
			{
				setName(" Astrium.cc");
				Spam = false;
			}
			else
			{
				setName("Astrium.cc ");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 3:
			if (Spam)
			{
				setName("\nA\nS\nT\nR\nI\nU\nM\n™ ");
				Spam = false;
			}
			else
			{
				setName(" ™\nA\nS\nT\nR\nI\nU\nM\n");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 4:
			if (Spam)
			{
				setName("\n\xAD\xAD\xAD ");
				Spam = false;
			}
			else
			{
				setName(" \n\xAD\xAD\xAD");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 5:
			if (Spam)
			{
				setName(" ™\n™\n™\n™\n™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™ ");
				Spam = false;
			}
			else
			{
				setName("™\n™\n™\n™\n™\n™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™™ ");
				Spam = true;
			}
			Spam != Spam;
			break;
		case 6:
			stringstream ss;

			for (auto i = 0; i <= 150; i++)
			{
				ss << static_cast<char>(-1);
			}

			auto cv = Interfaces.g_ICVars->FindVar("name");
			*reinterpret_cast<int*>(reinterpret_cast<DWORD>(&cv->fnChangeCallback) + 0xC) = NULL;
			cv->SetValue(ss.str().c_str());
			break;

		}
	}

	static void Chatspam()
	{
		static DWORD lastspammed = 0;

		if (!Options.Misc.Misc2.bChatSpam)
			return;

		std::vector<std::string> chatspam2 =
		{
			"get good - get Astrium.cc",
			"Astrium.cc",
			"Join us now. Astrium.cc",
			"It's actually cringe to work for this cheat and write this message c:"
		};


		if (GetTickCount() - lastspammed > 800)
		{
			lastspammed = GetTickCount();
			auto say = "say ";
			std::string p = say + chatspam2[rand() % chatspam2.size()];
			Interfaces.pEngine->ClientCmd_Unrestricted(p.c_str(), 0);
		}
	}

	static double GetNumberOfTicksChoked(CBaseEntity* pEntity)
	{
		double flSimulationTime = pEntity->GetSimulationTime();
		double flSimDiff = ((double)Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick) - flSimulationTime;
		return TIME_TO_TICKS(max(0.0f, flSimDiff));
	}

	static bool Shooting()
	{
		if (Hacks.LocalWeapon->IsKnife())
		{
			if (Hacks.CurrentCmd->buttons & IN_ATTACK || Hacks.CurrentCmd->buttons & IN_ATTACK2)
				return true;
		}
		else if (Hacks.LocalWeapon->IsNade())
		{
			CBaseCSGrenade* csGrenade = (CBaseCSGrenade*)Hacks.LocalWeapon;
			if (csGrenade->GetThrowTime() > 0.f)
			{
				return true;
			}
		}
		else if (Hacks.CurrentCmd->buttons & IN_ATTACK && bullettime())
		{
			if (*Hacks.LocalWeapon->GetItemDefinitionIndex() == weapon_revolver && (Options.Ragebot.Aimbot.bAimbotEnable && Options.Ragebot.Aimbot.bAutoRevolver))
			{
				if (Hacks.CurrentCmd->buttons & IN_RELOAD)
					return false;

				if (!Hacks.LocalPlayer)
					return false;

				if (!Hacks.LocalWeapon->HasAmmo())
					return false;

				float postponeFireReady = Hacks.LocalWeapon->GetPostponeFireReadyTime();
				float server_time = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;

				if (Hacks.LocalWeapon->GetPostponeFireReadyTime() - server_time <= 0.05f)
					return true;

			}
			else
				return true;
		}
		return false;
	}

	static void DrawScope()
	{
		if (Options.Visuals.VisualsMisc.bScopeRemover && Hacks.LocalWeapon)
			if (Hacks.LocalWeapon->isSniper())
				if (Hacks.LocalPlayer->m_bIsScoped())
				{
					int width = 0;
					int height = 0;
					Interfaces.pEngine->GetScreenSize(width, height);
					DrawRect((width / 2), 0, (width / 2) + 1, height, CColor(0, 0, 0, 255));
					DrawRect(0, (height / 2), width, (height / 2) + 1, CColor(0, 0, 0, 255));
				}
	}

	static void CircleStrafer(float& OldAngle)
	{
		int Mode = Options.Misc.Movement.iCircleStraferMode;
		switch (Mode)
		{
		case 0:
			break;
		case 1: // Adaptive
		{
			static int Angle = 0;
			if (OldAngle - Angle > 360)
				Angle -= 360;
			static bool shouldspin = false;
			static bool enabled = false;
			static bool check = false;
			if (GetAsyncKeyState(Options.Misc.Movement.iCircleStraferKey))
			{
				if (!check)
					enabled = !enabled;
				check = true;
			}
			else
				check = false;
			if (enabled)
			{
				shouldspin = true;
				Hacks.CurrentCmd->buttons |= IN_JUMP;
			}
			if (shouldspin) {
				Vector Dir;
				g_Math.angleVectors(Vector(0, Angle, 0), Dir);
				Dir *= 8218;
				Ray_t ray;
				CTraceWorldOnly filter;
				trace_t trace;
				ray.Init(Hacks.LocalPlayer->GetEyePosition(), Hacks.LocalPlayer->GetVecOrigin() + Dir);
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&filter, &trace);
				auto temp = 3.4f / ((trace.endpos - Hacks.LocalPlayer->GetVecOrigin()).Length() / 100.f);
				if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 415) {
					if (temp < 3.4f)
						temp = 3.4f;
				}
				else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 200) {
					if (temp < 6.8f)
						temp = 6.8f;
				}
				else {
					if (temp < 10.2f)
						temp = 10.2f;
				}
				if (enabled) {
					Angle += temp;
					Hacks.CurrentCmd->sidemove = -450;
				}
				else {
					if (OldAngle - Angle < temp) {
						Angle = OldAngle;
						shouldspin = false;
					}
					else
						Angle += temp;
				}
				OldAngle = Angle;
			}
			else {
				Angle = OldAngle;
				return;
			}
		}
		break;
		case 2: // Non Adaptive
		{
			static int Angle = 0;
			if (OldAngle - Angle > 360)
				Angle -= 360;
			static bool shouldspin = false;
			static bool enabled = false;
			static bool check = false;
			if (GetAsyncKeyState(Options.Misc.Movement.iCircleStraferKey))
			{
				if (!check)
					enabled = !enabled;
				check = true;
			}
			else
				check = false;
			if (enabled)
			{
				shouldspin = true;
				Hacks.CurrentCmd->buttons |= IN_JUMP;
				Hacks.CurrentCmd->buttons |= IN_DUCK;
			}
			if (shouldspin)
			{
				Vector Dir;
				g_Math.angleVectors(Vector(0, Angle, 0), Dir);
				Dir *= 8218;
				Ray_t ray;
				CTraceWorldOnly filter;
				trace_t trace;
				ray.Init(Hacks.LocalPlayer->GetEyePosition(), Hacks.LocalPlayer->GetVecOrigin() + Dir);
				Interfaces.pTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
				auto temp = 3.4f / ((trace.endpos - Hacks.LocalPlayer->GetVecOrigin()).Length() / 100.f);
				if (temp < 3.4f)
					temp = 3.4f;
				if (enabled)
				{
					Angle += temp;
					Hacks.CurrentCmd->sidemove = -450;
				}
				else
				{
					if (OldAngle - Angle < temp)
					{
						Angle = OldAngle;
						shouldspin = false;
					}
					else
						Angle += temp;
				}
				OldAngle = Angle;
			}
			else
				Angle = OldAngle;
		}
		break;
		}

	}

	static void Walkbot(Vector& OrigAng)
	{

		bool walkbotBefore = false;

		Vector viewangles;
		Interfaces.pEngine->GetViewAngles(viewangles);

		static int OldMouseX = OrigAng.y;
		int mousedx = OldMouseX - OrigAng.y;

		auto fDistanceToWall = [&](Vector diff = Vector(0, 0, 0))->float {
			auto tmpviewangles = viewangles + diff;
			trace_t tr;
			Ray_t ray;
			CTraceFilter filter;
			filter.pSkip = Hacks.LocalPlayer;
			Vector begin = Hacks.LocalPlayer->GetEyePosition(), t, end;
			AngleVectors2(tmpviewangles, t);
			NormalizeInOut(t, end);
			end *= 8192.0f;
			end += begin;
			ray.Init(begin, end);
			Interfaces.pTrace->TraceRay(ray, 0x4600400B, &filter, &tr);
			return (begin - tr.endpos).Size();
		};

		static float old1, old2, old3;
		if (Hacks.LocalPlayer->GetVecVelocity().Length() < 3)
		{
			viewangles.y += 2.0f;
		}
		float Distances = Options.Misc.Movement.flDistance;
		if (fDistanceToWall() < Distances) // we are near to some wall
		{
			int turn = Options.Misc.Movement.iTurn;
			float negativeDist = fDistanceToWall(Vector(0, -1, 0)), positiveDist = fDistanceToWall(Vector(0, 1, 0));
			if (abs(negativeDist - positiveDist) < 1.0f)
			{
				viewangles.y += turn;
			}
			else
			{
				viewangles.y += positiveDist < negativeDist ? -1 : 1;
			}
		}
		if (Options.Misc.Movement.bBunnyhop)
		{
			if ((Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
				Hacks.CurrentCmd->buttons |= IN_JUMP;
			else
			{
				Hacks.CurrentCmd->buttons |= IN_DUCK;
				Hacks.CurrentCmd->buttons &= ~IN_FORWARD;
			}

		}


		if (abs(viewangles.x) > 0)
			viewangles.x = 1;

		while (viewangles.y > 180.0f)
			viewangles.y -= 360.0f;
		while (viewangles.y < -180.0f)
			viewangles.y += 360.0f;

		Interfaces.pEngine->SetViewAngles(viewangles);

		if (!walkbotBefore)
		{
			Hacks.CurrentCmd->forwardmove = 450.f;
			walkbotBefore = true;
		}

		else if (walkbotBefore)
		{
			walkbotBefore = false;
			Hacks.CurrentCmd->forwardmove = 450.f;
		}
	}

	static Vector Normalize( Vector& angs )
	{
		while( angs.y < -180.0f )
			angs.y += 360.0f;
		while( angs.y > 180.0f )
			angs.y -= 360.0f;
		if( angs.x > 89.0f )
			angs.x = 89.0f;
		if( angs.x < -89.0f )
			angs.x = -89.0f;
		angs.z = 0;
		return angs;
	}

	static bool AimStep( Vector angSource, Vector& angDestination )
	{
		Vector angDelta = Normalize( angDestination - angSource );
		if( angDelta.Abs() > 40.f )
		{
			angDestination = Normalize( angSource + angDelta / angDelta.Abs() * 40.f );
			return false;
		}
		return true;
	}

	static float GetServerTime()
	{
		return ( float )Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
	}

	static bool bullettime()
	{
		if( !Hacks.LocalWeapon )
			return false;
		float flNextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

		return flNextPrimaryAttack <= GetServerTime();
	}

	static void MoveFix( CInput::CUserCmd* cmd, Vector& realvec )
	{
		Vector vMove( cmd->forwardmove, cmd->sidemove, cmd->upmove );
		float flSpeed = sqrt( vMove.x * vMove.x + vMove.y * vMove.y ), flYaw;
		Vector vMove2;
		g_Math.vectorAnglesVec( vMove, vMove2 );
		Normalize( vMove2 );
		flYaw = DEG2RAD(cmd->viewangles.y - realvec.y + vMove2.y);
		cmd->forwardmove = cos( flYaw ) * flSpeed;
		cmd->sidemove = sin( flYaw ) * flSpeed;
		if( 90 < abs( cmd->viewangles.x ) && 180 > abs( cmd->viewangles.x ) )
			cmd->forwardmove *= -1;
	}

	static void CalcAngle( Vector src, Vector dst, Vector& angles )
	{
		Vector delta = src - dst;
		double hyp = delta.Length2D();
		angles.y = atan( delta.y / delta.x ) * 57.295779513082f;
		angles.x = atan( delta.z / hyp ) * 57.295779513082f;
		if( delta.x >= 0.0 )
			angles.y += 180.0f;
		angles.z = 0;
	}

	static int FovTo(Vector From, Vector To)
	{
		From -= To;
		Normalize(From);
		return (abs(From.y) + abs(From.x));
	}

	static bool isVisible(CBaseEntity* entity, int bone)
	{
		Ray_t ray;
		trace_t tr;

		ray.Init(Hacks.LocalPlayer->GetEyePosition(), entity->GetBonePos(bone));

		CTraceFilter filter;
		filter.pSkip = Hacks.LocalPlayer;

		Interfaces.pTrace->TraceRay(ray, (0x1 | 0x4000 | 0x2000000 | 0x2 | 0x4000000 | 0x40000000), &filter, &tr);
	
		if (tr.m_pEnt == entity)
		{
			return true;
		}

		return false;
	}

	static void NormalizeVector(Vector& vec)
	{
		for (int i = 0; i < 3; ++i)
		{
			while (vec[i] > 180.f)
				vec[i] -= 360.f;

			while (vec[i] < -180.f)
				vec[i] += 360.f;
		}
		vec[2] = 0.f;
	}

	static void NormalizeInOut(Vector &vIn, Vector &vOut)
	{
		float flLen = vIn.Length();
		if (flLen == 0) {
			vOut.Init(0, 0, 1);
			return;
		}
		flLen = 1 / flLen;
		vOut.Init(vIn.x * flLen, vIn.y * flLen, vIn.z * flLen);
	}

	static void SinCos(float a, float* s, float*c)
	{
		*s = sin(a);
		*c = cos(a);
	}

	static void AngleVectors(const Vector &angles, Vector *forward)
	{
		Assert(s_bMathlibInitialized);
		Assert(forward);

		float	sp, sy, cp, cy;

		sy = sin(DEG2RAD(angles[1]));
		cy = cos(DEG2RAD(angles[1]));

		sp = sin(DEG2RAD(angles[0]));
		cp = cos(DEG2RAD(angles[0]));

		forward->x = cp*cy;
		forward->y = cp*sy;
		forward->z = -sp;
	}

	static void AngleVectors2(const Vector& qAngles, Vector& vecForward)
	{
		float sp, sy, cp, cy;
		SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
		SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

		vecForward[0] = cp*cy;
		vecForward[1] = cp*sy;
		vecForward[2] = -sp;
	}

	static void VectorAngles2(const Vector &vecForward, Vector &vecAngles)
	{
		Vector vecView;
		if (vecForward[1] == 0.f && vecForward[0] == 0.f)
		{
			vecView[0] = 0.f;
			vecView[1] = 0.f;
		}
		else
		{
			vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

			if (vecView[1] < 0.f)
				vecView[1] += 360.f;

			vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

			vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
		}

		vecAngles[0] = -vecView[0];
		vecAngles[1] = vecView[1];
		vecAngles[2] = 0.f;
	}

	static void AngleVectors3(const Vector& qAngles, Vector& vecForward)
	{
		float sp, sy, cp, cy;
		SinCos((float)(qAngles[1] * (M_PI / 180.f)), &sy, &cy);
		SinCos((float)(qAngles[0] * (M_PI / 180.f)), &sp, &cp);

		vecForward[0] = cp*cy;
		vecForward[1] = cp*sy;
		vecForward[2] = -sp;
	}

	static void VectorAngles3(const Vector &vecForward, Vector &vecAngles)
	{
		Vector vecView;
		if (vecForward[1] == 0.f && vecForward[0] == 0.f)
		{
			vecView[0] = 0.f;
			vecView[1] = 0.f;
		}
		else
		{
			vecView[1] = atan2(vecForward[1], vecForward[0]) * 180.f / M_PI;

			if (vecView[1] < 0.f)
				vecView[1] += 360.f;

			vecView[2] = sqrt(vecForward[0] * vecForward[0] + vecForward[1] * vecForward[1]);

			vecView[0] = atan2(vecForward[2], vecView[2]) * 180.f / M_PI;
		}

		vecAngles[0] = -vecView[0];
		vecAngles[1] = vecView[1];
		vecAngles[2] = 0.f;
	}
};


