#pragma once
#include "../../stdafx.h"
#include "../Utils/Hitbox.h"
#include "../Menu/Menu.h"
#include "../Utils/Playerlist.h"
#include "../Menu/SettingsManager.h"
#include "../Utils/HitboxLists.h"

class KnifeBot {
	static float GetDamage(Vector Angle)
	{
		FireBulletData Bullet_Data = FireBulletData(Hacks.LocalPlayer->GetEyePosition());
		Bullet_Data.filter.pSkip = Hacks.LocalPlayer;
		g_Math.angleVectors(Angle, Bullet_Data.direction);

		if (Autowall::FireSimulatedBullet(Bullet_Data, Hacks.LocalPlayer, Hacks.LocalWeapon))
			return Bullet_Data.current_damage;
		return 0;
	}
public:
	static void Run() {
			if (!Hacks.LocalWeapon)
				return;
			if (!Hacks.LocalWeapon->IsKnife())
				return;
			for (int y = 0; y <= 360; y += 360.f / 6.f) {
				for (int x = -89; x <= 89; x += 179.f / 6.f) {
					Vector ang = Vector(x, y, 0);
					Vector dir;
					g_Math.angleVectors(ang, dir);
					trace_t trace;
					UTIL_TraceLine(Hacks.LocalPlayer->GetEyePosition(), Hacks.LocalPlayer->GetEyePosition() + (dir * 64), MASK_SHOT, Hacks.LocalPlayer, 0, &trace);

					if (trace.m_pEnt == nullptr)
						continue;
					if (trace.m_pEnt == Hacks.LocalPlayer)
						continue;
					if (!trace.m_pEnt->isAlive())
						continue;
					if (!(trace.m_pEnt->GetHealth() > 0))
						continue;
					if (trace.m_pEnt->GetTeam() == Hacks.LocalPlayer->GetTeam())
						continue;
					if (trace.m_pEnt->IsDormant())
						continue;
					if (trace.m_pEnt->HasGunGameImmunity())
						continue;
					player_info_t info;
					if (!(Interfaces.pEngine->GetPlayerInfo(trace.m_pEnt->GetIndex(), &info)))
						continue;
					Hacks.CurrentCmd->viewangles = Vector(x, y, 0);
					Hacks.CurrentCmd->buttons |= IN_ATTACK2;
					return;
			}
		}
	}
};