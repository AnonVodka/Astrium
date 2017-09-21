#include "../../stdafx.h"
#include "Tools/Menu/Menu.h"
#include "Tools/Hacks/Misc.h"
#include "Tools/Utils/Playerlist.h"
#include "Tools/Hacks/Esp.h"
#include "Tools/Hacks/CreateMoveETC.h"
#include "Tools/Menu/SettingsManager.h"

void PaintTraverse()
{
	if (!Settings.GetSetting(Tab_Visuals, Visuals_Enable) || !Settings.GetSetting(Tab_Visuals, Visuals_GrenadePrediction))
		return;

	auto pLocal = Hacks.LocalPlayer();
	auto pWeapon = pLocal->GetActiveWeapon();

	if (pLocal && pWeapon && pWeapon->GetCSWpnData()->iWeaponType == WEAPONTYPE_GRENADE)
		PredictGrenade(pLocal);
}

void PredictGrenade(C_CSPlayer* pLocal)
{
	const float TIMEALIVE = 5.f;
	const float GRENADE_COEFFICIENT_OF_RESTITUTION = 0.4f;

	float fStep = 0.1f;
	float fGravity = 800.0f / 8.f;

	Vector vPos, vThrow, vThrow2;
	Vector vStart;

	int iCollisions = 0;

	Vector vViewAngles;
	Interfaces::Engine()->GetViewAngles(vViewAngles);

	vThrow[0] = vViewAngles[0];
	vThrow[1] = vViewAngles[1];
	vThrow[2] = vViewAngles[2];

	if (vThrow[0] < 0)
		vThrow[0] = -10 + vThrow[0] * ((90 - 10) / 90.0);
	else
		vThrow[0] = -10 + vThrow[0] * ((90 + 10) / 90.0);

	float fVel = (90 - vThrow[0]) * 4;
	if (fVel > 500)
		fVel = 500;

	Utils::AngleVectors(vThrow, vThrow2);

	Vector vEye = pLocal->GetEyePos();
	vStart[0] = vEye[0] + vThrow2[0] * 16;
	vStart[1] = vEye[1] + vThrow2[1] * 16;
	vStart[2] = vEye[2] + vThrow2[2] * 16;

	vThrow2[0] = (vThrow2[0] * fVel) + pLocal->GetVelocity()[0];
	vThrow2[1] = (vThrow2[1] * fVel) + pLocal->GetVelocity()[1];
	vThrow2[2] = (vThrow2[2] * fVel) + pLocal->GetVelocity()[2];	// casualhacker for da magic calc help

	for (float fTime = 0.0f; fTime < TIMEALIVE; fTime += fStep)
	{
		vPos = vStart + vThrow2 * fStep;

		Ray_t ray;
		trace_t tr;
		CTraceFilter loc;
		loc.pSkip = pLocal;

		ray.Init(vStart, vPos);
		Interfaces::EngineTrace()->TraceRay(ray, MASK_SOLID, &loc, &tr);

		if (tr.DidHit())
		{
			float anglez = Utils::DotProduct(Vector(0, 0, 1), tr.plane.normal);
			float invanglez = Utils::DotProduct(Vector(0, 0, -1), tr.plane.normal);
			float angley = Utils::DotProduct(Vector(0, 1, 0), tr.plane.normal);
			float invangley = Utils::DotProduct(Vector(0, -1, 0), tr.plane.normal);
			float anglex = Utils::DotProduct(Vector(1, 0, 0), tr.plane.normal);
			float invanglex = Utils::DotProduct(Vector(-1, 0, 0), tr.plane.normal);
			float scale = tr.endpos.DistTo(pLocal->GetOrigin()) / 60;
			Color color = Color(0, 0, 255);
			if (anglez > 0.5)
			{
				tr.endpos.z += 1;
				Vector startPos = tr.endpos + Vector(-scale, 0, 0);
				Vector endPos = tr.endpos + Vector(scale, 0, 0);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(0, -scale, 0);
				endPos = tr.endpos + Vector(0, scale, 0);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}
			else if (invanglez > 0.5)
			{
				tr.endpos.z += 1;
				Vector startPos = tr.endpos + Vector(-scale, 0, 0);
				Vector endPos = tr.endpos + Vector(scale, 0, 0);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(0, -scale, 0);
				endPos = tr.endpos + Vector(0, scale, 0);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}
			else if (angley > 0.5)
			{
				tr.endpos.y += 1;
				Vector startPos = tr.endpos + Vector(0, 0, -scale);
				Vector endPos = tr.endpos + Vector(0, 0, scale);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(-scale, 0, 0);
				endPos = tr.endpos + Vector(scale, 0, 0);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}
			else if (invangley > 0.5)
			{
				tr.endpos.y += 1;
				Vector startPos = tr.endpos + Vector(0, 0, -scale);
				Vector endPos = tr.endpos + Vector(0, 0, scale);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(-scale, 0, 0);
				endPos = tr.endpos + Vector(scale, 0, 0);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}
			else if (anglex > 0.5)
			{
				tr.endpos.x += 1;
				Vector startPos = tr.endpos + Vector(0, -scale, 0);
				Vector endPos = tr.endpos + Vector(0, scale, 0);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(0, 0, -scale);
				endPos = tr.endpos + Vector(0, 0, scale);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}
			else if (invanglex > 0.5)
			{
				tr.endpos.x += 1;
				Vector startPos = tr.endpos + Vector(0, -scale, 0);
				Vector endPos = tr.endpos + Vector(0, scale, 0);
				Vector outStart, outEnd;
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);

				startPos = tr.endpos + Vector(0, 0, -scale);
				endPos = tr.endpos + Vector(0, 0, scale);
				if (Draw::WorldToScreen(startPos, outStart) && Draw::WorldToScreen(endPos, outEnd))
					Draw::Line(outStart.x, outStart.y, outEnd.x, outEnd.y, color);
			}

			vThrow2 = tr.plane.normal * -2.0f * Utils::DotProduct(vThrow2, tr.plane.normal) + vThrow2;
			vThrow2 *= GRENADE_COEFFICIENT_OF_RESTITUTION;

			iCollisions++;
			if (iCollisions > 2)
				break;

			vPos = vStart + vThrow2 * tr.fraction * fStep;
			fTime += (fStep * (1 - tr.fraction));
		}

		Vector vOutStart, vOutEnd;

		if (Draw::WorldToScreen(vStart, vOutStart), Draw::WorldToScreen(vPos, vOutEnd))
			Draw::Line(vOutStart.x, vOutStart.y, vOutEnd.x, vOutEnd.y, Color(0, 255, 0));

		vStart = vPos;
		vThrow2.z -= fGravity * tr.fraction * fStep;
	}
}
