#pragma once
#include "stdafx.h"
#include "Tools\Hacks\Misc.h"

void AutoBlocker(CInput::CUserCmd* cmd)
{
	float bestdist = 250.f;
	int index = -1;

	for (int i = 0; i < Interfaces.pGlobalVars->maxClients; i++)
	{
		CBaseEntity* entity = Interfaces.pEntList->GetClientEntity(i);
		if (!entity)
			continue;

		if (!entity->isAlive() || entity->IsDormant() || entity == Hacks.LocalPlayer)
			continue;
		
		float dist = Hacks.LocalPlayer->GetVecOrigin().DistTo(entity->GetVecOrigin());

		if (dist < bestdist)
		{
			bestdist = dist;
			index = i;
		}
	}

	if (index == -1)
		return;

	CBaseEntity* target = Interfaces.pEntList->GetClientEntity(index);

	if (!target)
		return;

	Vector angles;
	Misc::CalcAngle(Hacks.LocalPlayer->GetVecOrigin(), target->GetVecOrigin(), angles);

	angles.y -= Hacks.LocalPlayer->GetEyeAngles().y;
	angles.Normalized();

	if (angles.y < 0.0f)
		cmd->sidemove = 450.f;
	else if (angles.y > 0.0f)
		cmd->sidemove = -450.f;
} 