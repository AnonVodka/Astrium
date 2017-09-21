#pragma once
#include "Tools/Hacks/Antiaim.h"
class adfg {
public:
	QAngle temp;
	bool start = false;
	bool jitter = false;
	bool flip = false;
	bool ShouldAA = true;
	int current = 0;
private:

	void Axis(Vector& View)
	{
	int Add = 0;
	static int SpinYaw = 0;
	float JitterAng = 0;
	static float StoredAng = 0;

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

	int W, H;
	Interfaces.pEngine->GetScreenSize(W, H);

	int RealYaw = 1;
	bool mmsafe = true;
	bool fakehitbox = true;

	/*
	Hacks.Sendpacket = false // Real
	Hacks.Sendpacket = true // Fake
	*/

	switch (RealYaw)
	{
	case 1: // Backwards
		static bool a;
		static bool ab;
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (a)
				{
					Hacks.SendPacket = false;
					Add = 180;
					a = false;

				}
				else
				{
					Hacks.SendPacket = true;
					Add = -90;
					a = true;
				}
			}
			else
			{
				Add = 180;
			}
		}
		else
		{
			if (fakehitbox)
			{
				if (ab)
				{
					Hacks.SendPacket = false;
					Add = 180;
					ab = false;
				}
				else
				{
					Hacks.SendPacket = true;
					switch (Hacks.CurrentCmd->tick_count % 2)
					{
					case 0:
						Add = 90;
						break;
					case 1:
						Add = -90;
						break;
					}
					ab = true;
				}
			}
			else
			{
				switch (Hacks.CurrentCmd->tick_count % 2)
				{
				case 0:
					Add = 175;
					break;
				case 1:
					Add = -175;
					break;
				}
			}
		}
		break;
	case 2: // Fake Spin
		static bool b;
		static bool bc;
		static bool bbc;
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (b)
				{
					Hacks.SendPacket = false;
					Add = 180;
					b = false;
				}
				else
				{
					Hacks.SendPacket = true;
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 1)
					{
						if (bbc)
						{
							Hacks.SendPacket = false;
							Add = Hacks.LocalPlayer->pelvisangs() + 90;
							bbc = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = Hacks.LocalPlayer->pelvisangs() - 90;
							bbc = true;
						}
					}
					else
					{
						if (bbc)
						{
							Hacks.SendPacket = false;
							Add = 90;
							bbc = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = -90;
							bbc = true;
						}
					}
					b = false;
				}
			}
			else
			{
				Add = 180;
			}
		}
		else
		{
			if (fakehitbox)
			{
				if (bc)
				{
					Hacks.SendPacket = false;
					Add = 180;
					bc = false;
				}
				else
				{
					Hacks.SendPacket = true;
					if (flip)
						SpinYaw += 35;
					else
						SpinYaw -= 35;
					StoredAng = SpinYaw;
					View.y = SpinYaw;
					bc = true;
				}
			}
			else
			{
				if (flip)
					SpinYaw += 35;
				else
					SpinYaw -= 35;
				flip != flip;
				StoredAng = SpinYaw;
				View.y = SpinYaw;
			}
		}
		break;

	case 3: // Fake Jitter
		static bool c;
		static bool cd;
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (c)
				{
					Hacks.SendPacket = false;
					if (jitter)
					{
						Add = -155;
					}
					else
					{
						Add = 155;
					}
					c = false;
				}
				else
				{
					Hacks.SendPacket = true;
					switch (Hacks.CurrentCmd->tick_count % 2)
					{
					case 0:
						Add = 90;
						break;
					case 1:
						Add = -90;
						break;
					}
					c = true;
				}
			}
			else
			{
				Hacks.SendPacket = true;
				Add = 180;
			}
		}
		else
		{
			if (fakehitbox)
			{
				if (cd)
				{
					Hacks.SendPacket = false;
					if (jitter)
					{
						Add = -155;
					}
					else
					{
						Add = 155;
					}
					cd = false;
				}
				else
				{
					Hacks.SendPacket = true;
					switch (Hacks.CurrentCmd->tick_count % 4)
					{
					case 0:
						Add = Hacks.LocalPlayer->pelvisangs() - 90;
						break;
					case 1:
						Add = Hacks.LocalPlayer->pelvisangs() - 45;
						break;
					case 2:
						Add = Hacks.LocalPlayer->pelvisangs() + 45;
						break;
					case 3:
						Add = Hacks.LocalPlayer->pelvisangs() + 90;
						break;
					}
					cd = true;
				}
			}
			else
			{
				Hacks.SendPacket = true;
				if (jitter)
				{
					Add = -135;
				}
				else
				{
					Add = 135;
				}
				cd = false;
			}
		}
		break;

	case 4: // Fake Jitter 2
		static bool d;
		static bool de;
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (d)
				{
					Hacks.SendPacket = false;
					if (jitter)
					{
						Add = -155;
					}
					else
					{
						Add = 155;
					}
					d = false;
				}
				else
				{
					Hacks.SendPacket = true;
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() >= 30)
					{
						Add = 90;
					}
					else
					{
						Add = -90;
					}
					d = true;
				}
			}
			else
			{
				Hacks.SendPacket = true;
				if (jitter)
				{
					Add = -155;
				}
				else
				{
					Add = 155;
				}
			}
		}
		else
		{
			if (fakehitbox)
			{
				if (de)
				{
					Hacks.SendPacket = false;
					if ((Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						Hacks.SendPacket = true;
						if (jitter)
						{
							Hacks.SendPacket = false;
							Add = Hacks.LocalPlayer->pelvisangs() - 155;
							jitter = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = Hacks.LocalPlayer->pelvisangs() + 155;
							jitter = true;
						}
					}
					else if ((Hacks.LocalPlayer->GetFlags() & FL_DUCKING))
					{
						Hacks.SendPacket = false;
						if (jitter)
						{
							Hacks.SendPacket = false;
							Add = Hacks.LocalPlayer->pelvisangs() - 175;
							jitter = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = Hacks.LocalPlayer->pelvisangs() + 175;
							jitter = true;
						}
					}
					else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
					{
						Hacks.SendPacket = true;
						if (jitter)
						{
							Hacks.SendPacket = false;
							Add = Hacks.LocalPlayer->pelvisangs() - 90;
							jitter = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = Hacks.LocalPlayer->pelvisangs() + 90;
							jitter = true;
						}
					}
					de = false;
				}
				else
				{
					Hacks.SendPacket = true;
					if (Hacks.SendPacket)
					{
						Hacks.SendPacket = false;
						if (jitter)
						{
							Add = -90;
						}
						else
						{
							Add = 90;
						}
					}
					else if (!(Hacks.SendPacket))
					{
						Hacks.SendPacket = true;
						if (jitter)
						{
							Add = -45;
						}
						else
						{
							Add = 45;
						}
					}
					else if (Hacks.SendPacket)
					{
						Hacks.SendPacket = false;
						if (jitter)
						{
							Add = -155;
						}
						else
						{
							Add = 155;
						}
					}
					else
					{
						if (jitter)
						{
							Add = -180;
						}
						else
						{
							Add = 180;
						}
					}
					de = true;
				}

			}
			else
			{
				Hacks.SendPacket = true;
				if (jitter)
				{
					Add = -155;
					jitter = false;
				}
				else
				{
					Add = 155;
					jitter = true;
				}
			}
		}
		break;

	case 5: // Luddy on Speed
		static bool luddy;
		static bool luddy2;
		static bool luddy3;
		if (mmsafe)
		{
			if (fakehitbox)
			{

			}
			else
			{

			}
		}
		else
		{
			if (fakehitbox)
			{
				Hacks.SendPacket = false;
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() >= 150)
					{
						if (luddy2)
						{
							Hacks.SendPacket = false;
							Add = 180.f;
							luddy2 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							if (luddy3)
							{
								Hacks.SendPacket = false;
								Add = Hacks.LocalPlayer->pelvisangs() + Hacks.LocalPlayer->pelvisangs() + 90;
								luddy3 = false;
							}
							else
							{
								Hacks.SendPacket = true;
								Add = Hacks.LocalPlayer->pelvisangs() - Hacks.LocalPlayer->pelvisangs() - 90;
								luddy3 = true;
							}
							luddy2 = true;
						}
					}
					else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() <= 30)
					{
						if (luddy2)
						{
							Hacks.SendPacket = false;
							if (luddy3)
							{
								Hacks.SendPacket = false;
								Add = Hacks.LocalPlayer->pelvisangs() + Hacks.LocalPlayer->pelvisangs() + 90;
								luddy3 = false;
							}
							else
							{
								Hacks.SendPacket = true;
								Add = Hacks.LocalPlayer->pelvisangs() - Hacks.LocalPlayer->pelvisangs() - 90;
								luddy3 = true;
							}
							luddy2 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							switch (Hacks.CurrentCmd->tick_count % 3)
							{
							case 0:
								Add = -170.f;
								break;
							case 1:
								Add = 180.f;
								break;
							case 2:
								Add = 170.f;
								break;
							}
							luddy2 = true;
						}
					}
					else
					{
						if (luddy2)
						{
							Hacks.SendPacket = false;
							Add = 180.f;
							luddy2 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							float flRandom = rand() % 5 + 1.f;
							switch (Hacks.CurrentCmd->tick_count % 4)
							{
							case 0:
								Hacks.SendPacket = false;
								Add = -170.f - flRandom;
								break;
							case 3:
							case 1:
								Hacks.SendPacket = true;
								Add = 180.f;
								break;
							case 2:
								Add = 170.f + flRandom;
								break;
							}
							luddy2 = true;
						}
					}
				}
				else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() >= 260)
					{
						if (luddy2)
						{
							Hacks.SendPacket = false;
							switch (Hacks.CurrentCmd->tick_count % 3)
							{
							case 0:
								Add = -170.f;
								break;
							case 1:
								Add = 180.f;
								break;
							case 2:
								Add = 170.f;
								break;
							}
							luddy2 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							if (jitter)
							{
								Add = 90;
							}
							else
							{
								Add = -90;
							}
							luddy2 = true;
						}
					}
					else
					{
						if (luddy2)
						{
							Hacks.SendPacket = false;
							if (jitter)
							{
								Add = -175;
							}
							else
							{
								Add = 175;
							}
							luddy2 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							int spinspeed = 3;
							if (flip)
							{
								SpinYaw -= spinspeed / 5;
								flip != flip;
								StoredAng = SpinYaw;
								View.y = SpinYaw;
							}
							else
							{
								SpinYaw -= spinspeed * 5;
								flip != flip;
								StoredAng = SpinYaw;
								View.y = SpinYaw;
							}
							flip != flip;
							luddy2 = true;
						}
					}
				}
			}
			else
			{
				if (Hacks.LocalPlayer->GetFlags() & FL_ONGROUND)
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() >= 150)
					{
						Hacks.SendPacket = false;
						Add = 180.f;
						luddy2 = false;

					}
					else if (Hacks.LocalPlayer->GetVecVelocity().Length2D() <= 30)
					{
						Hacks.SendPacket = false;
						if (luddy3)
						{
							Hacks.SendPacket = false;
							Add = Hacks.LocalPlayer->pelvisangs() + Hacks.LocalPlayer->pelvisangs() + 90;
							luddy3 = false;
						}
						else
						{
							Hacks.SendPacket = true;
							Add = Hacks.LocalPlayer->pelvisangs() - Hacks.LocalPlayer->pelvisangs() - 90;
							luddy3 = true;
						}

					}
					else
					{

						Hacks.SendPacket = false;
						Add = 180.f;
						luddy2 = false;
					}
				}
				else if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
				{
					if (Hacks.LocalPlayer->GetVecVelocity().Length2D() >= 260)
					{

						Hacks.SendPacket = true;
						if (jitter)
						{
							Add = 90;
						}
						else
						{
							Add = -90;
						}

					}
					else
					{

						Hacks.SendPacket = false;
						if (jitter)
						{
							Add = -175;
						}
						else
						{
							Add = 175;
						}
						luddy2 = false;

					}
				}
			}
		}
		break;

	case 6: // Spinbot
		if (fakehitbox)
		{
			int spinspeed = 2;
			if (flip)
			{
				Hacks.SendPacket = false;
				Add = 180.f;
				SpinYaw += spinspeed * 2.5;
			}

			else
			{
				Hacks.SendPacket = true;
				Add = 90.f;
				SpinYaw -= spinspeed * 5;
			}
			flip != flip;
			StoredAng = SpinYaw;
			View.y = SpinYaw;
		}
		else
		{
			int spinspeed = 2;
			if (flip)
				SpinYaw += spinspeed;
			else
				SpinYaw -= spinspeed;
			flip != flip;
			StoredAng = SpinYaw;
			View.y = SpinYaw;
		}

		break;

	case 7:
		static bool legit;
		static bool legittroll;
		if (legit)
		{
			Hacks.SendPacket = false;
			/*if (legittroll)
			{
			Add = 90;
			legittroll = false;
			}
			else
			{
			Add = -90;
			legittroll = true;
			}*/
			if (flip)
				Add = -90;
			else
				Add = 90;
			legit = false;

		}
		else
		{
			Hacks.SendPacket = true;
			Add = 0;
			legit = true;
		}
		break;

	case 8: // Lowerbody Rand
		static bool bdy;
		static int lbyyaw = Hacks.LocalPlayer->pelvisangs();
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (bdy)
				{
					Hacks.SendPacket = true;
					Add = lbyyaw += rand() % 45;
					bdy != bdy;
				}
				else
				{
					Hacks.SendPacket = false;
					Add = lbyyaw -= rand() % 45;
					bdy != bdy;
				}
			}

			else
			{
				Add = lbyyaw += rand() % 45;
			}
		}
		break;

	case 9: // Lowerbody simple
		static bool bdyuff;
		if (mmsafe)
		{
			if (fakehitbox)
			{
				if (bdyuff)
				{
					Hacks.SendPacket = false;
					Add = (Hacks.LocalPlayer->pelvisangs() + Hacks.LocalPlayer->pelvisangs()) + 90;
					bdyuff = false;
				}
				else
				{
					Hacks.SendPacket = true;
					Add = (Hacks.LocalPlayer->pelvisangs() - Hacks.LocalPlayer->pelvisangs()) - 90;
					bdyuff = true;
				}
			}

			else
			{
				Add = (Hacks.LocalPlayer->pelvisangs() + Hacks.LocalPlayer->pelvisangs()) + rand() % 45;
			}
		}
		break;
	}

	/*switch (RealYaw)
	{
	//Sideways Distortion
	case 2: //Sideways Distortion
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Settings.GetSetting(Tab_Misc, Misc_AntiUntrusted))
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (Hacks.SendPacket)
	{
	if (jitter)
	Add = -90;
	else
	Add = 90;
	}
	else
	{
	float flRandom = rand() % 5 + 1.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -170.f - flRandom;
	break;
	case 3:
	case 1:
	Add = 180.f;
	break;
	case 2:
	Add = 170.f + flRandom;
	break;
	}
	}
	}
	else
	{
	if (Hacks.SendPacket)
	{
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -100.f;
	break;
	case 1:
	Add = 100.f;
	break;
	case 2:
	Add = 100.f;
	break;
	case 3:
	Add = -100.f;
	break;
	}
	}
	else
	{
	float flRandom = rand() % 32 + 28.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -100.f - flRandom;
	break;
	case 1:
	Add = 100.f + flRandom;
	break;
	case 2:
	Add = -100.f - flRandom;
	break;
	case 3:
	Add = 100.f + flRandom;
	break;
	}
	}
	}
	}
	else
	{
	//Nospread
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (Hacks.SendPacket)
	{
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -100.f;
	break;
	case 3:
	case 1:
	Add = 180.f;
	break;
	case 2:
	Add = 100.f;
	break;
	}
	}
	else
	{
	if (!LocalInfo.Flags & FL_ONGROUND)
	{
	float flRandom = rand() % 32 + 28.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -100.f + flRandom;
	break;
	case 3:
	case 1:
	Add = 180.f;
	break;
	case 2:
	Add = 100.f + flRandom;
	break;
	break;
	}
	}
	}
	}
	else
	{
	return;
	}
	}
	}
	else
	{
	if (jitter)
	Add = -135;
	else
	Add = 135;
	}
	Hacks.SendPacket = false;
	break;

	//180 or back
	case 3: //180 or back
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Settings.GetSetting(Tab_Misc, Misc_AntiUntrusted))
	{
	//Matchmaking
	if (Hacks.SendPacket)
	{
	Add = -90;
	}
	else
	{
	Add = 180;
	}
	}
	else
	{
	//Nospread
	if (LocalInfo.Flags & FL_ONGROUND)
	{
	if (Hacks.SendPacket)
	{
	if (flip)
	Add = -90;
	else
	Add = 90;
	}
	else
	{
	Add = 180;
	}
	}
	else
	{
	if (Hacks.SendPacket)
	{
	Add = -90;
	}
	else
	{
	Add = 90;
	}
	}
	}
	}
	else
	{
	Add = 180;
	}
	Hacks.SendPacket = true;
	break;

	//Crooked Distortion
	case 4: //Crooked Distortion
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.SendPacket)
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = 90;
	}
	else
	{
	Add = -90;
	}
	}
	else
	{
	Add = 170;
	}
	}
	else
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = -45;
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	Add = -161;
	}
	else
	{
	Add = -20;
	}
	}
	}
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (jitter)
	Add = 161;
	else
	Add = -161;
	}
	else
	{
	Add = 180;
	}
	}
	Hacks.SendPacket = true;
	break;

	//Spin
	case 5: //Spin
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (Hacks.SendPacket)
	{
	if (flip)
	SpinYaw += 35;
	else
	SpinYaw -= 35;
	View.y = SpinYaw;
	}
	else
	{
	float flRandom = rand() % 10 + 5.f;
	flRandom *= rand() % 2 == 0 ? -1.f : 1.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	JitterAng = -170.f;
	break;
	case 1:
	JitterAng = 180.f;
	break;
	case 2:
	JitterAng = 170.f;
	break;
	case 3:
	JitterAng = 180.f;
	break;
	}
	Add = JitterAng + flRandom;
	}
	}
	else
	{
	if (Hacks.SendPacket)
	{
	if (flip)
	SpinYaw += 35;
	else
	SpinYaw -= 35;
	StoredAng = SpinYaw;
	View.y = SpinYaw;
	}
	else
	{
	float flFake = rand() % 32 + 19.f;
	if ((StoredAng) < 0)
	StoredAng += flFake;
	else if ((StoredAng) > 0)
	StoredAng -= flFake;
	Add = StoredAng;
	}
	}
	}
	else
	{
	SpinYaw += 90;
	View.y = SpinYaw;
	}
	//Hacks.CurrentCmd->viewangles.y = SpinYaw;
	Hacks.SendPacket = true;
	break;

	//180 Distortion
	case 6: //180 Distortion
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Settings.GetSetting(Tab_Misc, Misc_AntiUntrusted))
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (Hacks.SendPacket)
	{
	if (jitter)
	Add = -120;
	else
	Add = 120;
	}
	else
	{
	float flRandom = rand() % 5 + 1.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -170.f - flRandom;
	break;
	case 3:
	case 1:
	Add = 180.f;
	break;
	case 2:
	Add = 170.f + flRandom;
	break;
	}
	}
	}
	else
	{
	if (Hacks.SendPacket)
	{
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -125.f;
	break;
	case 1:
	Add = -179.f;
	break;
	case 2:
	Add = 125.f;
	break;
	case 3:
	Add = 179.f;
	break;
	case 4:
	Add = -125.f;
	break;
	}
	}
	else
	{
	float flRandom = rand() % 33 + 30.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -125.f - flRandom;
	break;
	case 1:
	Add = -179.f - flRandom;
	break;
	case 2:
	Add = 125.f + flRandom;
	break;
	case 3:
	Add = 179.f - flRandom;
	break;
	case 4:
	Add = -125.f - flRandom;
	break;

	}
	}
	}
	}
	else
	{
	//Nospread
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (Hacks.SendPacket)
	{
	SpinYaw += 45;
	View.y = SpinYaw;
	}
	else
	{
	if (!LocalInfo.Flags & FL_ONGROUND)
	{
	float flRandom = rand() % 32 + 28.f;
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = -125.f;
	break;
	case 1:
	Add = -179.f;
	break;
	case 2:
	Add = 125.f;
	break;
	case 3:
	Add = 179.f;
	break;
	case 4:
	Add = -125.f;
	break;
	}
	}
	}
	}
	else
	{
	return;
	}
	}
	}
	else
	{
	if (jitter)
	Add = -135;
	else
	Add = 135;
	}
	Hacks.SendPacket = true;
	break;

	case 7:
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	static int base = 0;
	if (!(rand() % 40))
	base = rand() % 360;
	if (!Hacks.SendPacket)
	{
	View.y = base;
	if (LocalInfo.Flags & FL_ONGROUND)
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = 45;
	break;
	case 1:
	Add = 180;
	break;
	}
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = 165;
	break;
	case 1:
	Add = -90;
	break;
	}
	}
	else
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = -165;
	break;
	case 1:
	Add = 90;
	break;
	}
	}
	}
	}
	else
	{
	View.y = base;
	Add = 0;
	}
	}
	else
	{
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = 90.f;
	break;
	case 3: case 1:
	Add = 160;
	break;
	case 2:
	Add = -170;
	break;
	}
	}
	Hacks.SendPacket = true;
	break;

	case 8: //Offset Jitter
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.SendPacket)
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = 90;
	}
	else
	{
	Add = -90;
	}
	}
	else
	{
	Add = 170;
	}
	}
	else
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = -45;
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	Add = -161;
	}
	else
	{
	Add = -20;
	}
	}
	}
	}
	else
	{
	static bool left;
	if (left)
	{
	View.y += rand() % 60 - 90;
	}
	else
	{
	View.y -= rand() % 60 + 90;
	}
	left != left;
	}
	Hacks.SendPacket = true;
	break;

	case 9: // Reverse Offset Jitter
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.SendPacket)
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = 90;
	}
	else
	{
	Add = -90;
	}
	}
	else
	{
	Add = 170;
	}
	}
	else
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = -45;
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	Add = -161;
	}
	else
	{
	Add = -20;
	}
	}
	}
	}
	else
	{
	static bool right;
	if (right)
	{
	View.y += rand() % 60 - 180;
	}
	else
	{
	View.y -= rand() % 60 + 180;
	}
	right != right;
	}
	Hacks.SendPacket = true;
	break;

	case 10: // Back Jitter
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.SendPacket)
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = 90;
	}
	else
	{
	Add = -90;
	}
	}
	else
	{
	Add = 180;
	}
	}
	else
	{
	if (!(Hacks.LocalPlayer->GetFlags() & FL_ONGROUND))
	{
	Add = 180;
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	Add = 90;
	}
	else
	{
	Add = -90;
	}
	}
	}
	}
	else
	{
	switch (Hacks.CurrentCmd->tick_count % 6)
	{
	case 0:
	Add += 180.f;
	break;
	case 1:
	Add -= 135.f;
	break;
	case 2:
	Add += 135.f;
	break;
	case 3:
	Add -= 180.f;
	break;
	case 4:
	Add += 135.f;
	break;
	case 5:
	Add -= 135.f;
	break;
	}
	}
	Hacks.SendPacket = true;
	break;

	case 11: //UserCmdOverFlow
	Add = 0x90;
	Hacks.SendPacket = true;
	break;

	case 12:
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	static int base = 0;
	if (!(rand() % 40))
	base = rand() % 360;
	if (!Hacks.SendPacket)
	{
	View.y = base;
	if (LocalInfo.Flags & FL_ONGROUND)
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = 90;
	break;
	case 1:
	Add = 180;
	break;
	}
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() > 1)
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = 180;
	break;
	case 1:
	Add = -90;
	break;
	}
	}
	else
	{
	switch (Hacks.CurrentCmd->tick_count % 2)
	{
	case 0:
	Add = 180;
	break;
	case 1:
	Add = 90;
	break;
	}
	}
	}
	}
	else
	{
	View.y = base;
	Add = 0;
	}
	}
	else
	{
	switch (Hacks.CurrentCmd->tick_count % 4)
	{
	case 0:
	Add = 180.f;
	break;
	case 3: case 1:
	Add = 90;
	break;
	case 2:
	Add = -90;
	break;
	}
	}
	Hacks.SendPacket = true;
	break;

	case 13: //Fake Spin 2
	static float spin2;
	if (Hacks.SendPacket)
	{
	Add = spin2;
	}
	else
	{
	Add = 180;
	}
	spin2 += 1.777777777777777;
	//	Hacks.SendPacket = true;
	break;

	case 14:
	static bool kek, kack;
	static float spin3;
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (kek)
	{
	Hacks.SendPacket = true;
	Add = 180;
	}
	else
	{
	if (kack)
	{
	Add -= 90;
	}
	else
	{
	Add = 90;
	}
	kack = !kack;
	Hacks.SendPacket = false;
	}
	kek = !kek;
	}
	else
	{
	if (kek)
	{
	Hacks.SendPacket = true;
	Add = 180;
	}
	else
	{
	if (kack)
	{
	Add = spin3;
	spin3 += 50;
	}
	else
	{
	Add -= spin3;
	spin3 += 25;
	}
	kack = !kack;
	Hacks.SendPacket = false;
	}
	kek = !kek;
	}
	Hacks.SendPacket = true;
	break;

	case 15:
	static bool LUL;
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (LUL)
	{
	LUL = false;
	Add += 155.0f;
	Hacks.SendPacket = true;
	}
	else
	{
	LUL = true;
	Add -= 115.0f;
	Hacks.SendPacket = false;
	}
	}
	else
	{
	if (LUL)
	{
	LUL = false;
	Add -= 155.0f;
	Hacks.SendPacket = true;
	}
	else
	{
	LUL = true;
	Add += 115.0f;
	Hacks.SendPacket = false;
	}
	}
	Hacks.SendPacket = true;
	break;

	case 16:
	static bool lby1, aaswitch, abc;
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 1)
	{
	if (lby1)
	{
	Add += Hacks.LocalPlayer->pelvisangs() - 90.00f;
	Hacks.SendPacket = true;
	}
	else
	{
	Add -= Hacks.LocalPlayer->pelvisangs() + 90.00f;
	Hacks.SendPacket = false;
	}
	lby1 = !lby1;
	}
	else
	{
	if (aaswitch || !Hacks.SendPacket)
	{
	Add = 90.00f;
	Hacks.SendPacket = true;
	}
	else
	{
	Add -= 90.00f;
	Hacks.SendPacket = false;
	}
	aaswitch = !aaswitch;
	}
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 1)
	{
	if (lby1)
	{
	Add += Hacks.LocalPlayer->pelvisangs() - 45.f;
	Hacks.SendPacket = true;
	}
	else
	{
	Add -= Hacks.LocalPlayer->pelvisangs() + 45.f;
	Hacks.SendPacket = false;
	}
	lby1 = !lby1;
	}
	else
	{
	if (Hacks.SendPacket)
	{
	if (abc)
	{
	Add = 135.00f;
	}
	else
	{
	Add -= 135.00f;
	}
	abc = !abc;
	Hacks.SendPacket = false;
	}
	else
	{
	Add = 180.f;
	}
	Hacks.SendPacket = true;
	}
	}
	Hacks.SendPacket = true;
	break;

	case 17:
	static bool lby2;
	if (Settings.GetSetting(Tab_Ragebot, AntiAim_FakeHitbox))
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 1)
	{
	if (lby2)
	{
	Add += Hacks.LocalPlayer->pelvisangs() - 90.f;
	Hacks.SendPacket = true;
	}
	else
	{
	Add -= Hacks.LocalPlayer->pelvisangs() + 90.f;
	Hacks.SendPacket = false;
	}
	lby2 = !lby2;
	}
	else
	{
	Add = 180.f;
	}
	}
	else
	{
	if (Hacks.LocalPlayer->GetVecVelocity().Length2D() < 1)
	{
	if (lby2)
	{
	Add += Hacks.LocalPlayer->pelvisangs() - 155.f;
	Hacks.SendPacket = true;
	}
	else
	{
	Add -= Hacks.LocalPlayer->pelvisangs() + 155.f;
	Hacks.SendPacket = false;
	}
	lby2 = !lby2;
	}
	else
	{
	Add = rand() % 60 + 180;
	}
	}
	Hacks.SendPacket = true;
	break;
	}*/


	Hacks.CurrentCmd->viewangles.y = View.y + Add;


	int pitch = 2;
	switch (pitch)
	{
	case 1:
		Hacks.CurrentCmd->viewangles.x = 88.99f;
		break;
	case 2:
		Hacks.CurrentCmd->viewangles.x = -88.99f;
		break;
	case 3:
		if (Hacks.SendPacket)
			Hacks.CurrentCmd->viewangles.x = 0;
		else
			Hacks.CurrentCmd->viewangles.x = 89;
		break;
	case 4:
		if (Hacks.SendPacket)
			Hacks.CurrentCmd->viewangles.x = -45;
		else
			Hacks.CurrentCmd->viewangles.x = 89;
		break;
	case 5:
		Hacks.CurrentCmd->viewangles.x = 89;
		if (Hacks.LocalWeapon->isSniper())
			Hacks.CurrentCmd->viewangles.x = 85;
		else if (Hacks.LocalWeapon->isRifle() || Hacks.LocalWeapon->isSmgW())
			Hacks.CurrentCmd->viewangles.x = 80;
		else if (Hacks.LocalWeapon->isPistol())
			Hacks.CurrentCmd->viewangles.x = 89;
		else if (Hacks.LocalWeapon->isMachineW())
			Hacks.CurrentCmd->viewangles.x = 78.50;
		else if (Hacks.LocalWeapon->isShotgun())
			Hacks.CurrentCmd->viewangles.x = 75.00;
		break;
	case 6:
		Hacks.CurrentCmd->viewangles.x = -180.f;
		break;
	case 7:
		Hacks.CurrentCmd->viewangles.x = 272.911758f;
		if (!Hacks.SendPacket)
			Hacks.CurrentCmd->viewangles.x = 89;
		break;
	case 8:

		static bool knecht;
		if (knecht)
		{
			Hacks.CurrentCmd->viewangles.x = 1080;
			Hacks.SendPacket = true;
		}
		else
		{
			Hacks.CurrentCmd->viewangles.x = -1080;
			Hacks.SendPacket = false;
		}
		knecht = !knecht;

		break;
	case 9:
		static int abc = Interfaces.pGlobalVars->tickcount;
		switch (abc % 3)
		{
		case 0:
			Hacks.CurrentCmd->viewangles.x = 420;
			break;
		case 1:
			Hacks.CurrentCmd->viewangles.x = 666;
			break;
		case 2:
			Hacks.CurrentCmd->viewangles.x = 4200;
			break;
		}
		break;
	case 10:
		Hacks.CurrentCmd->viewangles.x = 420;
		break;
	case 11:
		Hacks.CurrentCmd->viewangles.x = 666;
		break;
	case 12:
		Hacks.CurrentCmd->viewangles.x = 4200;
		break;
	case 13:
		Hacks.CurrentCmd->viewangles.x = 8475735;
		break;
		break;
	}
}
};