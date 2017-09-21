#include "../../stdafx.h"
Createmove_Hacks CM_Hacks;
PaintTraverse_Hacks PT_Hacks;
Draw_Model_Exec_Hacks DMEHacks;

/*
NOTE:

TRY TO KEEP AMOUNT OF .CPP FILES TO A LOW AMOUND, OR IT TAKES A LONG TIME TO COMPILE

TO DO THIS, WE ARE KEEPING MOST FEATURES IN ONE .CPP SO WE DONT HAVE TO HAVE A .CPP
FOR EVERY FEATURE.

AIMBOTS HAVE THERE OWN CPP THOUGH.

*/

extern void dolegitshit();

#pragma region Create Move

bool bTeleportSwitch;
bool bTeleportZSwitch;
bool bTeleportInvertSwitch;
BYTE byteCorrupt[] = { 0xBE, 0x120 };
BYTE byteDeCorrupt[] = { 0xBE, 0x20 };
void Teleport()
{
	bool bTeleport = false;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleport = true;

	if (bTeleport && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		BYTE* nulldata;
		static DWORD dwAddr = Utils.PatternSearch("client.dll", (PBYTE)"\xBE\x00\x00\x00\x00\x2B\xF1\x3B\xF3\x7D\x1F\x8B\x55\x0C\x8B\xC3", "x????xxxxxxxxxxx", NULL, NULL);
		auto bByte = bTeleportSwitch ? byteCorrupt : byteDeCorrupt;
		DWORD virtualProtect;
		VirtualProtect((LPVOID)(dwAddr), 4, PAGE_READWRITE, &virtualProtect);
		memcpy((LPVOID)(dwAddr), bByte, sizeof(bByte));
		VirtualProtect(reinterpret_cast<void*>(dwAddr), 4, virtualProtect, &virtualProtect);
		bTeleportSwitch = !bTeleportSwitch;
	}
}

void TeleportZ(Vector &angle)
{
	bool bTeleportZ = false;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleportZ = true;

	if (bTeleportZ && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		angle.z = 99999999999999999999999.99999999999f;
		bTeleportZSwitch = !bTeleportZSwitch;
	}
}

void TeleportInvert(Vector &angle)
{
	Vector views = Hacks.CurrentCmd->viewangles;
	bool bTeleportInvert = false;
	static int invert = 9999999999999999999;
	if (GetAsyncKeyState(Settings.GetSetting(Tab_Misc, Misc_Teliport)))
		bTeleportInvert = true;

	if (bTeleportInvert && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
	{
		//angle.z = 99999999999999999999999.99999999999f;
		angle.y = -99999999999999999999999.99999999999f;
		angle.x = -99999999999999999999999.99999999999f;
		bTeleportInvertSwitch = !bTeleportInvertSwitch;
	}
}


void Createmove_Hacks::BunnyHop()
{
	if ((Hacks.CurrentCmd->buttons & IN_JUMP))
	{
		if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
			Hacks.CurrentCmd->buttons &= ~IN_JUMP;
		else
		{
			Hacks.CurrentCmd->buttons &= ~IN_DUCK;
			UnLagNextTick = true;
			Hacks.SendPacket = true;
		}
	}
}

void Createmove_Hacks::AutoStrafer()
{
	// basic silent autostrafer
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND) && (Hacks.CurrentCmd->buttons & IN_JUMP))
	{
		if (Hacks.LocalPlayer->GetVecVelocity().Length2D() == 0 && (Hacks.CurrentCmd->forwardmove == 0 && Hacks.CurrentCmd->sidemove == 0))
		{
			Hacks.CurrentCmd->forwardmove = 450.f;
		}
		else if (Hacks.CurrentCmd->forwardmove == 0 && Hacks.CurrentCmd->sidemove == 0)
		{
			if (Hacks.CurrentCmd->mousedx > 1 || Hacks.CurrentCmd->mousedx < -1) {
				Hacks.CurrentCmd->sidemove = Hacks.CurrentCmd->mousedx < 0.f ? -450.f : 450.f;
			}
			else
			{
				Hacks.CurrentCmd->forwardmove = 5850.f / Hacks.LocalPlayer->GetVecVelocity().Length2D();
				Hacks.CurrentCmd->sidemove = (Hacks.CurrentCmd->command_number % 2) == 0 ? -450.f : 450.f;
			}
		}
	}
}

bool Createmove_Hacks::CircleStrafer(Vector &angles)
{
	if (!GetAsyncKeyState((int)Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Key)))
		return false;

	Vector forward;
	g_Math.angleVectors(angles, forward);
	forward *= Hacks.LocalPlayer->GetVecVelocity().Length2D() * 2;
	/*
	Mathetmatics
	Fc = mV^2/r
	F=ma
	a = v^2/r

	Angular momentum
	w = v/r
	angular acceloration = dw/dt
	
	etc. Math it all out
	This is for a circle, however it should be triangles but its close enough
	r = (180 * sidemove)/change in viewangs*PI

	as we want max acceloration we want small r large v. Simple :) 
	Someone can do that maths and select the right side move etc. 
	*/
	CTraceWorldOnly filter;// Pretty sure this ray trace is useless but hey :)
	Ray_t ray;
	trace_t tr;
	ray.Init(Hacks.LocalPlayer->GetAbsOrigin(), forward);
	Interfaces.pTrace->TraceRay(ray, MASK_SHOT, (CTraceFilter*)&filter, &tr);
	static int add = 0;
	float value = 1000 / Hacks.LocalPlayer->GetVecVelocity().Length2D();
	float maxvalue = Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Max) / 2;
	float minvalue = Settings.GetSetting(Tab_Misc, Misc_CircleStrafe_Min) / 2;

	if (value > maxvalue)
		value = maxvalue;

	if (value < minvalue && minvalue != 0)
		value = minvalue;

	if (tr.DidHit())
		add += value * 2;
	else
		add += value;
	if (add > 180)
		add -= 360;
	angles.y += add;

	Hacks.CurrentCmd->sidemove = -(value * 132.35294)/2;//-(value * 132.35294);//-450;
	//Hacks.CurrentCmd->forwardmove = 450;
	return true;
}

void Airstuck()
{
	if (GetAsyncKeyState((int)Settings.GetSetting(Tab_Misc, Misc_Airstuck_Key)))
	{

		float ServerTime = Hacks.LocalPlayer->GetTickBase() * Interfaces.pGlobalVars->interval_per_tick;
		float NextPrimaryAttack = Hacks.LocalWeapon->NextPrimaryAttack();

		bool Shooting = false;
		if (NextPrimaryAttack > ServerTime)
			Shooting = true;


		if (!Shooting)
		{
			Hacks.CurrentCmd->tick_count = 99999999;
			//Hacks.CurrentCmd->tick_count = 0;

		}
	}
}
void Name_Stealer()
{
	if (Settings.GetBoolSetting(Tab_Misc, Misc_NameStealer))
	{
		stringstream NewName;
		int Index = Settings.GetSetting(Tab_Misc, Misc_NameStealer_Index);
		switch (Index)
		{
		case 0:
		case 1: NewName << "SOMEWARE"; break;
		case 2: NewName << "AIMJUNKIES.NET"; break;
		case 3: NewName << "VACWARE.NET"; break;
		case 4: NewName << "INTERWARE.CC"; break;
		case 5: NewName << "EZFRAGS.CO.UK"; break;
		case 6: NewName << " "; break;
		case 7: NewName << "Jewware"; break;
		}

		int ran = rand() % 3;
		for (int i = 0; i < ran; i++)
		{
			NewName << " ";
		}
		if (Settings.GetSetting(Tab_Misc, Misc_NameStealer_Invis)) {
			NewName << " \n";
		}
		ConVar* Name = Interfaces.g_ICVars->FindVar("name");
		if (Name)
		{
			*(int*)((DWORD)&Name->fnChangeCallback + 0xC) = 0;
			Name->SetValue(NewName.str().c_str());
		}
	}
}
void Createmove_Hacks::CorrectMovement(Vector vOldAngles, CInput::CUserCmd* pCmd, Vector Viewangs)
{
	Vector vMove(pCmd->forwardmove, pCmd->sidemove, pCmd->upmove);
	float flSpeed = sqrt(vMove.x * vMove.x + vMove.y * vMove.y), flYaw;
	Vector vMove2;
	g_Math.VectorAngles3D(vMove, vMove2);

	flYaw = DEG2RAD(Viewangs.y - vOldAngles.y + vMove2.y);
	pCmd->forwardmove = cos(flYaw) * flSpeed;
	pCmd->sidemove = sin(flYaw) * flSpeed;

	if (Viewangs.x < -90.f || Viewangs.x > 90.f)
		pCmd->forwardmove = -pCmd->forwardmove;
}
extern Vector GetHitboxPOS(CPlayer* Enemy, int HitboxID);

bool anyAlive()
{
	for (INT i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* pEntity = (CBaseEntity*)Interfaces.pEntList->GetClientEntity(i);
		if (pEntity == NULL)
			continue;
		if (!pEntity->isAlive())
			continue;
		if (pEntity == Hacks.LocalPlayer)
			continue;
		if (pEntity->IsDormant())
			continue;
		if (pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam())
			continue;
		player_info_t info;
		if (!(Interfaces.pEngine->GetPlayerInfo(pEntity->GetIndex(), &info)))
			continue;
		return true;
	}
	return false;
}

void Createmove_Hacks::MovePacket(CInput* thisptr, void* _EAX, int sequence_number, float input_sample_frametime, bool active)
{
	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame())
	{
#pragma region Get User Cmd
		CInput::CUserCmd* cmdlist = *(CInput::CUserCmd**)((DWORD)Interfaces.pInput + 0xEC);
		CInput::CUserCmd* cmd = &cmdlist[sequence_number % 150];
		CInput::CVerifiedUserCmd* verifiedCmdList = *(CInput::CVerifiedUserCmd**)((DWORD)Interfaces.pInput + 0xF0);
		CInput::CVerifiedUserCmd* VerifiedCmd = &verifiedCmdList[sequence_number % 150];
#pragma endregion

#pragma region Sort Out Hack Manger
		Hacks.CurrentCmd = cmd;
		Vector oldAngles = Hacks.CurrentCmd->viewangles;
		if (!Hacks.LocalPlayer)return;
		Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
		if (!Hacks.LocalWeapon) return;
#pragma endregion
		Vector OrigAng = Hacks.CurrentCmd->viewangles;
#pragma region Do Hacks
		if (Hacks.LocalPlayer)
		{
			if (Hacks.LocalPlayer->isAlive())
			{
				Name_Stealer();

				Settings.weaponconfigs();

				if (!CircleStrafer(OrigAng))
					if (Settings.GetBoolSetting(Tab_Misc, Misc_Auto_Strafer))
						AutoStrafer();

				if (Settings.GetBoolSetting(Tab_Misc, Misc_Bunny_Hop))
					BunnyHop();

				if (Settings.GetBoolSetting(Tab_Misc, Misc_Teleport_Enable) && !Settings.GetBoolSetting(Tab_Misc, Misc_Anti_Untrust))
				{
					int telval = Settings.GetSetting(Tab_Misc, Misc_Teliport_Type);
					switch (telval) {
					case 1:
						Teleport();
						break;
					case 2:
						TeleportZ(Hacks.CurrentCmd->viewangles);
						break;
					case 3:
						TeleportInvert(Hacks.CurrentCmd->viewangles);
						break;
					}
				}
				bool alive = anyAlive();
				if (Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
					alive = true;

				if (alive)
				{
#pragma region Prediction
					// Can Do Prediction Because We Have The Move Helper, If Not Pattern Search It And Try Again Next Packet
					if (Interfaces.g_pMoveHelper)
					{
						int TickBase = Hacks.LocalPlayer->GetTickBase(); // Get The Tick Base
						int Old_Time = Interfaces.pGlobalVars->curtime; // Get Current Time (Client Not Server)
						int Old_Frame_Time = Interfaces.pGlobalVars->frametime; // Get Frame Time (Client)

						Interfaces.pGlobalVars->curtime = TickBase * Interfaces.pGlobalVars->interval_per_tick; // Set Time To Server Time
						Interfaces.pGlobalVars->frametime = Interfaces.pGlobalVars->interval_per_tick; // Set Framerate To Tick Rate

						CMoveData Move_Data; // Make A Move Data
						memset(&Move_Data, 0, sizeof(Move_Data));
						bool Ducked = false;
						if (Hacks.CurrentCmd->buttons & IN_DUCK)
							Ducked = true;
						int duvkval = Settings.GetSetting(Tab_Ragebot, Ragebot_Duck);
						switch (duvkval) {
						case 2:
							Hacks.CurrentCmd->buttons &= ~IN_DUCK;
							break;
						}
						Interfaces.g_pMoveHelper->SetHost(Hacks.LocalPlayer); // Set Myself To Get Predicted
						Interfaces.g_pPred->SetupMove(Hacks.LocalPlayer, Hacks.CurrentCmd, Interfaces.g_pMoveHelper, &Move_Data); // Setup Prediction
						Interfaces.g_pGameMovement->ProcessMovement(Hacks.LocalPlayer, &Move_Data); // Process Prediction
						Interfaces.g_pPred->FinishMove(Hacks.LocalPlayer, Hacks.CurrentCmd, &Move_Data); // Finish Prediction
						Interfaces.g_pGameMovement->DecayPunchAngles();
						Interfaces.g_pMoveHelper->SetHost(NULL); // Remove Self From Move Helper
						if (Ducked)
							Hacks.CurrentCmd->buttons |= IN_DUCK;

						Interfaces.pGlobalVars->curtime = Old_Time;  // Reset Times To Correct Time
						Interfaces.pGlobalVars->frametime = Old_Frame_Time; // Reset Frame Time To Correct Time

						CBaseCombatWeapon* pWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();
						if (pWeapon)
							pWeapon->UpdateAccuracyPenalty();
					}
					else
					{
						// if we dont have a pointer to Move Helper, Find One.
						Interfaces.g_pMoveHelper = **(IMoveHelper***)(Utils.PatternSearch("client.dll", (PBYTE)"\x8B\x0D\x00\x00\x00\x00\x8B\x45\x00\x51\x8B\xD4\x89\x02\x8B\x01", "xx????xx?xxxxxxx", NULL, NULL) + 2);
					}
#pragma endregion Player And Others Prediction


					if (Settings.GetBoolSetting(Tab_Ragebot, Ragebot_Enable))
						Ragebot.Move();

					int duvkval = Settings.GetSetting(Tab_Ragebot, Ragebot_Duck);
					switch (duvkval) {
					case 2:
						if (Hacks.CurrentCmd->buttons & IN_ATTACK)
							Hacks.CurrentCmd->buttons &= ~IN_DUCK;
						break;
					}
				}
				if (Settings.GetBoolSetting(Tab_LegitBot, Legit_Activate))
					//Legitbot.Move();
					dolegitshit();

				Airstuck();

				/* AutoPistol */
				if (Settings.GetSetting(Tab_Misc, Misc_Apistol)) {
					if ((Hacks.CurrentCmd->buttons & IN_ATTACK) && (Hacks.LocalWeapon->NextPrimaryAttack()
						- ((float)Hacks.LocalPlayer->GetTickBase()
							* Interfaces.pGlobalVars->interval_per_tick) > 0) && Hacks.LocalWeapon->isPistoleW()) Hacks.CurrentCmd->buttons &= ~IN_ATTACK;
				}

			}

		}
#pragma endregion

#pragma region AntiUntrust
		if (Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
		{
			Ragebot.FastLargeNormalise(Hacks.CurrentCmd->viewangles);
			while (Hacks.CurrentCmd->viewangles.y < -180.0f) Hacks.CurrentCmd->viewangles.y += 360.0f;
			while (Hacks.CurrentCmd->viewangles.y > 180.0f) Hacks.CurrentCmd->viewangles.y -= 360.0f;
			if (Hacks.CurrentCmd->viewangles.x > 89.0f) Hacks.CurrentCmd->viewangles.x = 89.0f;
			if (Hacks.CurrentCmd->viewangles.x < -89.0f) Hacks.CurrentCmd->viewangles.x = -89.0f;
			Hacks.CurrentCmd->viewangles.z = 0;
		}
#pragma endregion 
		Vector simplifiedang = Hacks.CurrentCmd->viewangles;
		Vector simplifiedorg = OrigAng;
		if (!Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust) && false)
		{
			
			Ragebot.FastLargeNormalise(simplifiedang);
			while (simplifiedang.y < -180.0f) simplifiedang.y += 360.0f;
			while (simplifiedang.y > 180.0f) simplifiedang.y -= 360.0f;

			Ragebot.FastLargeNormalise(simplifiedorg);
			while (simplifiedorg.y < -180.0f) simplifiedorg.y += 360.0f;
			while (simplifiedorg.y > 180.0f) simplifiedorg.y -= 360.0f;
			
		}
		CorrectMovement(simplifiedorg, Hacks.CurrentCmd, simplifiedang);
		if (Settings.GetBoolSetting(Tab_Ragebot, AntiAim_Enable)&& !Settings.GetSetting(Tab_Misc, Misc_Anti_Untrust))
		{
			if (Settings.GetSetting(Tab_Ragebot, AntiAim_LispAnglesX))
				Hacks.CurrentCmd->viewangles.x += 36000000;//18000000;//The perfect lisp value || JAKE MOVING THE 0's does not change the lisp Makes teh number bigger tho!!!
			if (Settings.GetSetting(Tab_Ragebot, AntiAim_LispAnglesY))
				Hacks.CurrentCmd->viewangles.y += 36000000;//The perfect lisp value || plisp found by inure w/ help from skeltal
		}
		Hacks.LastAngles = Hacks.CurrentCmd->viewangles;

#pragma region Set Cmds
		VerifiedCmd->m_cmd = *Hacks.CurrentCmd;
		VerifiedCmd->m_crc = Hacks.CurrentCmd->GetChecksum();
#pragma endregion
	}
}
#pragma endregion Movement Related Hacks

#pragma region Paint Traverse



bool PaintTraverse_Hacks::PaintTraverse_IsGoodPlayer_ESP(CBaseEntity* Target)
{
	if (!Target)
		return false;

	if (Target == Hacks.LocalPlayer)
		return false;

	if (Target->IsDormant())
		return false;

	if (!Target->IsPlayer())
		return false;

	if (Target->GetHealth() == 0)
		return false;

	if (!Target->isAlive())
		return false;


	return true;
}
void CrossBoxEsp(ESP_Box Box)
{
	int Line_Size = (Box.y - Box.h) / 10;

	// Top Left
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.w - Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.w, Box.h - Line_Size);

	// Top Right
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.x + Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.x, Box.h - Line_Size);
	// Bottom Left
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.w - Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.w, Box.y + Line_Size);

	// Bottom Right
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.x + Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.x, Box.y + Line_Size);
}

void Draw_Corner_Box_Faster(ESP_Box Box)
{
	int Line_Size = (Box.y - Box.h) / 10;

	// Top Left
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x + Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x, Box.y + Line_Size);

	// Top Right
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w - Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w, Box.y + Line_Size);
	// Bottom Left
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x + Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x, Box.h - Line_Size);
	// Bottom Right

	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w - Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w, Box.h - Line_Size);
}
void Cornerbox(ESP_Box Box)
{
	int Line_Size = (Box.y - Box.h) / 10;

	// Top Left
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x - Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.x, Box.y, Box.x, Box.y - Line_Size);

	// Top Right
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w + Line_Size, Box.y);
	Interfaces.pSurface->DrawLine(Box.w, Box.y, Box.w, Box.y - Line_Size);
	// Bottom Left
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x - Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.x, Box.h, Box.x, Box.h + Line_Size);
	// Bottom Right

	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w + Line_Size, Box.h);
	Interfaces.pSurface->DrawLine(Box.w, Box.h, Box.w, Box.h + Line_Size);
}
ESP_Box PaintTraverse_Hacks::Get_Box(CBaseEntity* Entity)
{
	ESP_Box result;
	Vector vEye = Entity->GetEyePosition();
	Vector vPelvis = GetHitboxPOS_Ent(Entity, (int)CSGOHitboxID::Pelvis);
	vPelvis.z -= 50;
	//Vector vFoot = vEye + Vector(0, 0, -70);
	vEye += Vector(0, 0, 10);
	Vector ScreenTop, ScreenBottom;
	Interfaces.g_pDebugOverlay->ScreenPosition(vEye, ScreenTop);
	Interfaces.g_pDebugOverlay->ScreenPosition(vPelvis, ScreenBottom);

	int Width = ((ScreenTop.y - ScreenBottom.y) / 2);
	ScreenTop.x += Width / 2;
	ScreenBottom.x -= Width / 2;
	result.x = ScreenTop.x;
	result.y = ScreenTop.y;
	result.w = ScreenBottom.x;
	result.h = ScreenBottom.y;
	return result;
}

bool PaintTraverse_Hacks::IsVisable(CBaseEntity* Target, int boneID)
{
	CBaseEntity* copy = Target;
	trace_t Trace;
	Vector start = Hacks.LocalPlayer->GetEyePosition();
	Vector end = GetHitboxPOS_Ent(Target, boneID);
	UTIL_TraceLine(start, end, MASK_SOLID, Hacks.LocalPlayer, 0, &Trace);
	if (Trace.m_pEnt == copy) return true;
	if (Trace.fraction == 1.0f) return true;
	return false;
}
player_info_t* Info = new player_info_t;

float sepssub(Vector source, Vector pos) {
	Vector dist;
	dist.x = abs(source.x - pos.x);
	dist.y = abs(source.y - pos.y);
	float xx = dist.x*dist.x + dist.y*dist.y;
	float distance = sqrt(xx);
	return distance;
}
int newlength;
bool shouldbeep = true;
void Beeeep() {
	if (shouldbeep) {
		newlength /= 10;
		shouldbeep = false;
		Beep(Settings.GetSetting(Tab_Visuals, ESP_Sonar_Pitch), 80);
		Sleep(newlength);
		shouldbeep = true;
	}
}
void SoundEsp() {

	CBaseEntity* me = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	int maxdistance = Settings.GetSetting(Tab_Visuals, ESP_Sonar_Dist);
	int a = Interfaces.pEntList->GetHighestEntityIndex();
	CBaseEntity* Target = me;
	CBaseEntity* Player;
	int bestdist = Settings.GetSetting(Tab_Visuals, ESP_Sonar_Dist);
	bool whichRvis[128];
	for (int i = 0; i < a; i++)
	{
		Player = Interfaces.pEntList->GetClientEntity(i);

		if (!Player)
			continue;

		if (Player->IsDormant()
			|| (Player->GetHealth() == 0)
			|| !Player->isAlive()
			|| (Player == me)
			|| (Player->GetTeam() == me->GetTeam())
			|| Player->HasGunGameImmunity())
			continue; // IS PLAYER A PLAYER /

					  // Loop Though Main Bones /

		Vector out;
		Vector source = me->GetEyePosition();// ->GetPredictedEyePos();
		Vector pos = GetHitboxPOS_Ent(Player, 0);

		float length = sepssub(source, pos);
		//float length = VectorLength(out);


		if (length < bestdist && length < maxdistance)
		{
			bestdist = length;
			Target = Player;

		}

	}

	if (Target == me || bestdist > maxdistance)
	{
		if (Target == me) {
			return;
		}
		if (bestdist < Settings.GetSetting(Tab_Visuals, ESP_Prox_Dist)) {
			Interfaces.pSurface->DrawSetColor(255, 255, 255, 255);
			Interfaces.pSurface->DrawFilledRect(20, 400, 120, 600);

			Interfaces.pEngine->GetPlayerInfo(Target->GetIndex(), Info);
			Interfaces.pSurface->DrawT(25, 410, CColor(0, 255, 0, 255), Hacks.Font_Tahoma, false, Info->name);
			int number = bestdist;
			char numberstring[(((sizeof number) * CHAR_BIT) + 2) / 3 + 2];
			sprintf(numberstring, "%d", number);

			Interfaces.pSurface->DrawT(25, 430, CColor(255, 0, 0, 255), Hacks.Font_Tahoma, false, numberstring);


		}
	}
	else {
		newlength = bestdist;
		if (bestdist < Settings.GetSetting(Tab_Visuals, ESP_Prox_Dist)) {
			Interfaces.pSurface->DrawSetColor(255, 255, 255, 255);
			Interfaces.pSurface->DrawFilledRect(20, 400, 120, 450);

			Interfaces.pEngine->GetPlayerInfo(Target->GetIndex(), Info);
			Interfaces.pSurface->DrawT(25, 410, CColor(0, 255, 0, 255), Hacks.Font_Tahoma, false, Info->name);
			int number = bestdist;
			char numberstring[(((sizeof number) * CHAR_BIT) + 2) / 3 + 2];
			sprintf(numberstring, "%d", number);

			Interfaces.pSurface->DrawT(25, 430, CColor(255, 0, 0, 255), Hacks.Font_Tahoma, false, numberstring);


		}
		if (shouldbeep) {

			CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Beeeep, 0, 0, 0);
		}
	}
}




void PaintTraverse_Hacks::DrawBox(CBaseEntity* Target, int r, int g, int b, int a)
{
	ESP_Box	BOX = Get_Box(Target);
	if (Settings.GetSetting(Tab_Visuals, Vis_Box) != 0 || Settings.GetSetting(Tab_Visuals, Vis_Box) != 1)
	{
		Interfaces.pSurface->DrawSetColor(r, g, b, a);
		int swi = Settings.GetSetting(Tab_Visuals, Vis_Box);
		switch (swi) {
		case 2:
			Interfaces.pSurface->DrawOutlinedRect(BOX.x, BOX.y, BOX.w, BOX.h);
			Interfaces.pSurface->DrawSetColor(0, 0, 0, 255);
			Interfaces.pSurface->DrawOutlinedRect(BOX.x - 1, BOX.y - 1, BOX.w + 1, BOX.h + 1);
			Interfaces.pSurface->DrawSetColor(r, g, b, a);
			break;
		case 3:
			Draw_Corner_Box_Faster(BOX);
			break;

		case 4:
			CrossBoxEsp(BOX);
			break;

		case 5:
			Cornerbox(BOX);
			break;

		}
	}

	int aTextRed = Settings.GetSetting(Tab_Other, Other_TextRed);
	int aTextGreen = Settings.GetSetting(Tab_Other, Other_TextGreen);
	int aTextBlue = Settings.GetSetting(Tab_Other, Other_TextBlue);
	int aTextAlpha = Settings.GetSetting(Tab_Other, Other_TextAlpha);
	if (Settings.GetSetting(Tab_Visuals, Vis_Background))
	{
		Interfaces.pSurface->DrawSetColor(0, 0, 0, 255);
		Interfaces.pSurface->DrawFilledRect(BOX.w + 5, BOX.y + 10, BOX.w + 95, BOX.y + 40);

	}
	if (Settings.GetSetting(Tab_Visuals, Vis_Name))
	{
		Interfaces.pEngine->GetPlayerInfo(Target->GetIndex(), Info);
		if (Settings.GetBoolSetting(Tab_Visuals, Vis_Weapon)) {
			Interfaces.pSurface->DrawT(BOX.x, BOX.y - 25, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, Info->name);
		}
		else {
			Interfaces.pSurface->DrawT(BOX.x, BOX.y - 15, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, Info->name);
		}
	}

	if (Settings.GetBoolSetting(Tab_Visuals, Vis_Weapon))
	{

		CBaseCombatWeapon* Weapon = Target->GetActiveBaseCombatWeapon();
		Interfaces.pSurface->DrawT(BOX.x, BOX.y - 15, CColor(255, 255, 255, 255), Hacks.Font_ESP, false, Weapon->GetPName());

	}

	if (Settings.GetSetting(Tab_Visuals, Vis_Health))
	{
		Interfaces.pSurface->DrawSetColor(0, 0, 0, 255);
		Interfaces.pSurface->DrawLine(BOX.x - 7, BOX.y - 1, BOX.x - 7, BOX.h + 1);
		Interfaces.pSurface->DrawLine(BOX.x - 4, BOX.y - 1, BOX.x - 4, BOX.h + 1);
		Interfaces.pSurface->DrawLine(BOX.x - 7, BOX.y - 1, BOX.x - 4, BOX.y - 1);
		Interfaces.pSurface->DrawLine(BOX.x - 7, BOX.h + 1, BOX.x - 4, BOX.h + 1);
		//end test
		Interfaces.pSurface->DrawSetColor(255, 0, 0, 255);
		Interfaces.pSurface->DrawFilledRect(BOX.x - 6, BOX.y, BOX.x - 4, BOX.h);
		Interfaces.pSurface->DrawSetColor(0, 255, 0, 255);
		int Health = Target->GetHealth();
		double Filler = BOX.y - BOX.h;
		Filler /= 100;
		Filler *= Health;
		int pos = Filler + BOX.h;
		Interfaces.pSurface->DrawFilledRect(BOX.x - 6, pos, BOX.x - 4, BOX.h);
	}
}
extern Vector ImageCalculateBezierPoint();
void PaintTraverse_Hacks::DrawESP()
{
	if (!Hacks.LocalPlayer) return;

	CBaseEntity* Target;
	int Max_Entitys = Interfaces.pEntList->GetHighestEntityIndex();

	/* Paint Shit */
	if(Settings.GetSetting(Tab_Visuals, Vis_Active))
		ImageCalculateBezierPoint();

	for (int i = 0; i < Max_Entitys; i++)
	{
		Target = Interfaces.pEntList->GetClientEntity(i);

		if (!Target)
			continue;

		ClientClass* cClass = (ClientClass*)Target->GetClientClass();

		if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
		{
			if (!PaintTraverse_IsGoodPlayer_ESP(Target))
				continue;

			int Red;
			int Blue;
			int Green;
			int Alpha;
			bool seeable = IsVisable(Target, 0);
			if (Target->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
				if (Settings.GetSetting(Tab_Visuals, Vis_Box_Team)) {
					if (seeable) {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_Team_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_Team_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_Team_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_Team_Visible_Alpha);
						DrawBox(Target, Red, Green, Blue, Alpha);

					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Esp_Team_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Esp_Team_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Esp_Team_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Esp_Team_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis))
							DrawBox(Target, Red, Green, Blue, Alpha);
					}
				}
			}
			else {
				if (seeable) {

					Red = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Visible_Red);
					Green = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Visible_Green);
					Blue = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Visible_Blue);
					Alpha = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_Visible_Alpha);
					DrawBox(Target, Red, Green, Blue, Alpha);

				}
				else {
					Red = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_inVisible_Red);
					Green = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_inVisible_Green);
					Blue = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_inVisible_Blue);
					Alpha = Settings.GetSetting(Tab_Other, Other_Esp_Enemy_inVisible_Alpha);
					if (!Settings.GetSetting(Tab_Visuals, Vis_Box_Vis))
						DrawBox(Target, Red, Green, Blue, Alpha);

				}
			}



		}
		else if (cClass->m_ClassID == (int)CSGOClassID::CPlantedC4)
		{


		}
	}

	/* Glow Shit */
	CGlowObjectManager* GlowObjectManager = (CGlowObjectManager*)Interfaces.g_pGlowObjectManager;
	CGlowObjectManager::GlowObjectDefinition_t* glowEntity;
	if (Settings.GetSetting(Tab_Visuals, Vis_Glow)) {
		for (int i = 0; i < GlowObjectManager->size; i++)
		{
			glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
			CBaseEntity* Entity = glowEntity->getEntity();

			if (!Entity) continue;

			ClientClass* cClass = (ClientClass*)Entity->GetClientClass();

			if (cClass->m_ClassID == (int)CSGOClassID::CCSPlayer)
			{
				if (!PaintTraverse_IsGoodPlayer_ESP(Entity))
					continue;

				int Red;
				int Blue;
				int Green;
				int Alpha;
				bool seeable = IsVisable(Entity, 0);

				if (Entity->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
					if (!seeable) {

						Red = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Glow_Vis) && Settings.GetBoolSetting(Tab_Visuals, Vis_Glow_Team)) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}

					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Alpha);
						if (Settings.GetBoolSetting(Tab_Visuals, Vis_Glow_Team))
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}
				else {
					if (!seeable) {

						Red = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_inVisible_Alpha);
						if (!Settings.GetSetting(Tab_Visuals, Vis_Glow_Vis)) {
							glowEntity->set(CColor(Red, Green, Blue, Alpha));

						}
					}
					else {
						Red = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Red);
						Green = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Green);
						Blue = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Blue);
						Alpha = Settings.GetSetting(Tab_Other, Other_Glow_Visible_Alpha);
						glowEntity->set(CColor(Red, Green, Blue, Alpha));

					}

				}

			}
		}
	}

}

void PaintTraverse_Hacks::DrawPaintTraverseHacks()
{
	Hacks.LocalPlayer = Interfaces.pEntList->GetClientEntity(Interfaces.pEngine->GetLocalPlayer());
	if (!Hacks.LocalPlayer) return;
	Hacks.LocalWeapon = Hacks.LocalPlayer->GetActiveBaseCombatWeapon();

	// Draw Cheats Here
	if (Settings.GetSetting(Tab_Visuals, Vis_Active)) {
		DrawESP();
		if (Settings.GetSetting(Tab_Visuals, ESP_Sonar_Dist) != 0)
			SoundEsp();
		//	if(Settings.GetSetting(Tab_Visuals, Cham_Asus) == 2)
		//		AsusWalls();
	}

}
#pragma endregion All Drawing Related Hacks

#pragma region Draw Model Execute

void Draw_Model_Exec_Hacks::InitKeyValues(KeyValues* keyValues, char* name)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\x68\x00\x00\x00\x00\x8B\xC8\xE8\x00\x00\x00\x00\x89\x45\xFC\xEB\x07\xC7\x45\x00\x00\x00\x00\x00\x8B\x03\x56", "x????xxx????xxxxxxx?????xxx", NULL, NULL); dwFunction += 7; dwFunction = dwFunction + *reinterpret_cast<PDWORD_PTR>(dwFunction + 1) + 5;
	__asm
	{
		push name
		mov ecx, keyValues
		call dwFunction
	}
}

void Draw_Model_Exec_Hacks::LoadFromBuffer(KeyValues* keyValues, char const *resourceName, const char *pBuffer)
{
	DWORD dwFunction = (DWORD)Utils.PatternSearch("client.dll", (PBYTE)"\xE8\x00\x00\x00\x00\x8A\xD8\xFF\x15\x00\x00\x00\x00\x84\xDB", "x????xxxx????xx", NULL, NULL); dwFunction = dwFunction + *reinterpret_cast<PDWORD_PTR>(dwFunction + 1) + 5;
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

IMaterial *Draw_Model_Exec_Hacks::Create_Material(bool Ignore, bool Lit, bool Wireframe)
{
	static int created = 0;
	static const char tmp[] =
	{
		"\"%s\"\
		\n{\
		\n\t\"$basetexture\" \"vgui/white_additive\"\
		\n\t\"$envmap\" \"\"\
		\n\t\"$model\" \"1\"\
		\n\t\"$flat\" \"1\"\
		\n\t\"$nocull\" \"0\"\
		\n\t\"$selfillum\" \"1\"\
		\n\t\"$halflambert\" \"1\"\
		\n\t\"$nofog\" \"0\"\
		\n\t\"$ignorez\" \"%i\"\
		\n\t\"$znearer\" \"0\"\
		\n\t\"$wireframe\" \"%i\"\
        \n}\n"
	}; // SHHH I DIDENT PASTE THIS .___.// Looks like you did

	char* baseType = (Lit == true ? "VertexLitGeneric" : "UnlitGeneric");
	char material[512];
	char name[512];
	sprintf_s(material, sizeof(material), tmp, baseType, (Ignore) ? 1 : 0, (Wireframe) ? 1 : 0);
	sprintf_s(name, sizeof(name), "#Aimpulse_Chams_%i.vmt", created); ++created;
	KeyValues* keyValues = (KeyValues*)malloc(sizeof(KeyValues));
	InitKeyValues(keyValues, baseType);
	LoadFromBuffer(keyValues, name, material);
	IMaterial *createdMaterial = Interfaces.pMaterialSystem->CreateMaterial(name, keyValues);
	createdMaterial->IncrementReferenceCount();
	return createdMaterial;
}
void Draw_Model_Exec_Hacks::AsusWalls()
{
	if (!Hacks.LocalPlayer)return;
	static bool go = true;
	static int lastasus = 1.f;
	static int lastgrey = 1.f;

	if (Interfaces.pEngine->IsConnected() && Interfaces.pEngine->IsInGame() && go)
	{
		for (MaterialHandle_t i = Interfaces.pMaterialSystem->FirstMaterial(); i != Interfaces.pMaterialSystem->InvalidMaterial(); i = Interfaces.pMaterialSystem->NextMaterial(i))
		{
			IMaterial *pMaterial = Interfaces.pMaterialSystem->GetMaterial(i);
			//cout << red << pMaterial->GetTextureGroupName() << endl;

			if (pMaterial->IsErrorMaterial())
				continue;
			if (!pMaterial)
				continue;

			if (strstr(pMaterial->GetTextureGroupName(), "World") && Settings.GetSetting(Tab_Visuals, Cham_Asus) !=0 || strstr(pMaterial->GetTextureGroupName(), "World") && Settings.GetSetting(Tab_Visuals, Vis_GreySacle) != 0)
			{
				pMaterial->AlphaModulate(Settings.GetSetting(Tab_Visuals, Cham_Asus)); // Scale 0-1
				float intensity = Settings.GetSetting(Tab_Visuals, Vis_GreySacle);
				pMaterial->ColorModulate(
					intensity,
					intensity,
					intensity);
				lastgrey = intensity;
				lastasus = Settings.GetSetting(Tab_Visuals, Cham_Asus);
			}
			if (strstr(pMaterial->GetTextureGroupName(), "Sky"))
			{
				pMaterial->ColorModulate(0, 0, 0);
				pMaterial->AlphaModulate(1.f);
			}
		}
		go = false;
	}
	go = lastasus != Settings.GetSetting(Tab_Visuals, Cham_Asus) || lastgrey != Settings.GetSetting(Tab_Visuals, Vis_GreySacle);
}

bool Draw_Model_Exec_Hacks::Do_Chams(void* thisptr, int edx, void* ctx, void* state, const ModelRenderInfo_t &pInfo, matrix3x4 *pCustomBoneToWorld)
{
	if (Settings.GetSetting(Tab_Visuals, Vis_Active) && Settings.GetSetting(Tab_Visuals, Cham_Asus)!=1)
		AsusWalls();//thisptr, edx, ctx, state, pInfo, pCustomBoneToWorld);

					/* Making Materials Is Slow, So Make Sure They Are Defined As Static */
	static IMaterial* Covered_Lit = Create_Material(true, true, false);
	static IMaterial* Visable_Lit = Create_Material(false, true, false);
	bool flat = Settings.GetSetting(Tab_Visuals, Cham_Flat);
	Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, flat);
	Visable_Lit->SetMaterialVarFlag(MATERIAL_VAR_TRANSLUCENT, flat);

	bool flame = Settings.GetSetting(Tab_Visuals, Cham_Flame);
	Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_OPAQUETEXTURE, flame);
	Visable_Lit->SetMaterialVarFlag(MATERIAL_VAR_OPAQUETEXTURE, flame);

	bool wire = Settings.GetSetting(Tab_Visuals, Cham_Wire);
	Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wire);
	Visable_Lit->SetMaterialVarFlag(MATERIAL_VAR_WIREFRAME, wire);

	if (Settings.GetSetting(Tab_Visuals, Cham_Active)) {
		CBaseEntity* Model_Entity = Interfaces.pEntList->GetClientEntity(pInfo.entity_index);
		const char* Model_Name = Interfaces.g_pModelInfo->GetModelName((model_t*)pInfo.pModel);

		if (!Model_Entity)
			return false;

		if (Model_Entity->IsPlayer() && Model_Entity != Hacks.LocalPlayer && strstr(Model_Name, "models/player") && true /*  */)
		{
			if (Model_Entity->GetTeam() != Hacks.LocalPlayer->GetTeam())
			{
				Covered_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Blue) / 255);
				Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Enemy_inVisible_Alpha) / 255);

				Visable_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Blue) / 255);
				Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Enemy_Visible_Alpha) / 255);

			}
			else
			{
				Covered_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Blue) / 255);
				Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Team_inVisible_Alpha) / 255);

				Visable_Lit->ColorModulate(
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Red) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Green) / 255,
					Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Blue) / 255);
				Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Team_Visible_Alpha) / 255);

			}


			if (!Model_Entity->isAlive())
			{
				Covered_Lit->ColorModulate(0.75f, 0.75f, 0.75f);
				Visable_Lit->ColorModulate(1.f, 1.f, 1.f);
			}

			if (Model_Entity->HasGunGameImmunity())
			{
				Covered_Lit->AlphaModulate(0.75f);
			}
			else
			{
				Covered_Lit->AlphaModulate(1.f);
			}

			if (Settings.GetSetting(Tab_Visuals, Cham_OnlyVis)) {
				Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, true);
			}
			else {
				Covered_Lit->SetMaterialVarFlag(MATERIAL_VAR_NO_DRAW, false);

			}
			if (Model_Entity->GetTeam() == Hacks.LocalPlayer->GetTeam()) {
				if (Settings.GetSetting(Tab_Visuals, Cham_ShowTeam)) {
					Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
					Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				}
				else {
					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

					Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

				}
			}
			else {
				Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);
				Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
				Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			}

			return true;
		}

		else if (strstr(Model_Name, "weapon") && Settings.GetSetting(Tab_Visuals, Cham_Weapon) /*  */)
		{

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Blue) / 255);

			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Weapon_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
		}

		else if (strstr(Model_Name, "ct_arms") && Settings.GetSetting(Tab_Visuals, Cham_Hands))
		{
			Covered_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);
			Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);



			return true;

		}
		else if (strstr(Model_Name, "t_arms") && Settings.GetSetting(Tab_Visuals, Cham_Hands))
		{
			Covered_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Hands_Blue) / 255);

			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);
			Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Hands_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);



			return true;

		}

		else if (strstr(Model_Name, "chicken") && Settings.GetSetting(Tab_Visuals, Cham_Chicken))
		{
			Covered_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Blue) / 255);

			Visable_Lit->ColorModulate(Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Visible_Red) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Visible_Green) / 255,
				Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Visible_Blue) / 255);

			Covered_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Chicken_inVisible_Alpha) / 255);
			Visable_Lit->AlphaModulate(Settings.GetSetting(Tab_Other, Other_Cham_Chicken_Visible_Alpha) / 255);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Covered_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			Interfaces.g_pModelRender->ForcedMaterialOverride(Visable_Lit, OVERRIDE_NORMAL);
			Hacks.oDrawModelExecute(thisptr, ctx, state, pInfo, pCustomBoneToWorld);

			return true;
		}

	}
	return false;

}

#pragma endregion