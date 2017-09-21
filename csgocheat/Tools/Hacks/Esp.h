#pragma once
#include "../../stdafx.h"
#include "CreateMoveETC.h"
#include "../../SDK/Math/Math.h"

class Esp
{
public:

	static std::string GetTimeString()
	{
		time_t current_time;
		struct tm *time_info;
		static char timeString[10];
		time(&current_time);
		time_info = localtime(&current_time);
		strftime(timeString, sizeof(timeString), "%X", time_info);
		return timeString;
	}

	static void Watermark()
	{
		int W, H, cW, cH;
		Interfaces.pEngine->GetScreenSize(W, H);

		long currentTime_ms = std::chrono::duration_cast< std::chrono::seconds >(std::chrono::system_clock::now().time_since_epoch()).count();
		static long timeStamp = currentTime_ms;

		timeStamp = currentTime_ms;

		std::string change;

		cW = W / 2;
		cH = H / 2;
		if (Options.Visuals.VisualsMisc.bWatermark)
		{
			switch (timeStamp % 12)
			{
			case 0:change = (""); break;
			case 1:change = (""); break;
			case 2:change = ("A"); break;
			case 3:change = ("As"); break;
			case 4:change = ("Ast"); break;
			case 5:change = ("Astr"); break;
			case 6:change = ("Astri"); break;
			case 7:change = ("Astriu"); break;
			case 8:change = ("Astrium"); break;
			case 9:change = ("Astrium."); break;
			case 10:change = ("Astrium.c"); break;
			case 11:change = ("Astrium.cc"); break;
			}

			Interfaces.pEngine->GetScreenSize(W, H);
			Interfaces.pSurface->DrawT(cW - 955, cH, CColor(147, 0, 147, 255), Hacks.Font_Watermark, false, "| %s", change.c_str());
		//	Interfaces.pSurface->DrawT(cW - 955, cH + 13, CColor(147, 0, 147, 255), Hacks.Font_Watermark, false, "| Updated: " __DATE__);
			if (Options.Visuals.VisualsMisc.bTime)
				Interfaces.pSurface->DrawT(cW - 955, cH + 13, CColor(147, 0, 147, 255), Hacks.Font_Watermark, false, "| Local Time: %s", GetTimeString().c_str());
			
		}
	}

	static void ThirdPerson()
	{
		static bool bSpoofed = false;
		static bool bThirdperson = false;
		static bool bKeyFix = false;
		MEMCHECK;

		if( !bSpoofed )
		{
			ConVar* sv_cheats = Interfaces.g_ICVars->FindVar("sv_cheats");
			SpoofedConvar* sv_cheats_spoofed = new SpoofedConvar(sv_cheats);
			sv_cheats_spoofed->SetInt(1);
			bSpoofed = true;
		}
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

		if(bSpoofed)
		{
			if( !bThirdperson && Options.Visuals.VisualsMisc.iThirdPerson && enabledtp && Hacks.LocalPlayer->GetHealth() > 0 )
			{
					Interfaces.pEngine->ClientCmd_Unrestricted("thirdperson", 0);
					bThirdperson = true;

					CBaseEntity* ThirdPerson = Hacks.LocalPlayer;
					Vector *ViewAngles = ThirdPerson->GetEyeAnglesPointer();
					Vector BufferViewAngles = Hacks.CurrentCmd->viewangles;
					if (BufferViewAngles.x > 89)
						BufferViewAngles.x = 89;
					if (BufferViewAngles.x < -89)
						BufferViewAngles.x = -89;
					*ViewAngles = BufferViewAngles;


			}
			else if( bThirdperson && !Options.Visuals.VisualsMisc.iThirdPerson)
			{
				Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
				bThirdperson = false;
			}
			if( Hacks.LocalPlayer->GetHealth() <= 0 )
			{
				Interfaces.pEngine->ClientCmd_Unrestricted( "firstperson", 0 );
				bThirdperson = false;
			}
		}
	}

	static void Crosshair()
	{
		int W, H, cW, cH;
		Interfaces.pEngine->GetScreenSize(W, H);

		cW = W / 2;
		cH = H / 2;

		int dX = W / Hacks.FOV;
		int dY = H / Hacks.FOV;
		int drX, drY;

		if (Options.Visuals.VisualsMisc.bRecoilCrosshair)
		{
			if (Options.Visuals.VisualsMisc.bNoVisualRecoil)
			{
				drX = cW - (int)(dX * (Hacks.LocalPlayer->GetPunchAngle().y * 2));
				drY = cH + (int)(dY * (Hacks.LocalPlayer->GetPunchAngle().x * 2));
			}
			else
			{
				drX = cW - (int)(dX * (((Hacks.LocalPlayer->GetPunchAngle().y * 2.f))/* + Hacks.LocalPlayer->GetPunchAngle().y*/));
				drY = cH + (int)(dY * (((Hacks.LocalPlayer->GetPunchAngle().x * 2.f))/* + Hacks.LocalPlayer->GetPunchAngle().x*/));
			}
		}
		else
		{
			drX = cW;
			drY = cH;
		}

		if ((Options.Visuals.VisualsMisc.bRecoilCrosshair) && (!Options.Visuals.VisualsMisc.bNormalCrosshair))
		{
			Interfaces.pSurface->DrawSetColor(244, 244, 244, 255);
			Interfaces.pSurface->DrawFilledRect(drX - 6, drY - 1, drX - 3 + 9, drY - 1 + 2);
			Interfaces.pSurface->DrawFilledRect(drX - 1, drY - 6, drX - 1 + 2, drY - 3 + 9);
		}
		if (Options.Visuals.VisualsMisc.bSpreadCrosshair)
		{
			Interfaces.pSurface->DrawSetColor(244, 244, 244, 255);
			float radius = ((Hacks.LocalPlayer->GetActiveBaseCombatWeapon()->GetSpread()) + (Hacks.LocalPlayer->GetActiveBaseCombatWeapon()->GetInaccuracy())) * 500;
			Interfaces.pSurface->DrawOutlinedCircle(drX, drY, radius, 255);
		}
		if (Options.Visuals.VisualsMisc.bCrosshair && (Options.Visuals.VisualsMisc.bNormalCrosshair))
		{
			Interfaces.pSurface->DrawSetColor(244, 244, 244, 255);
			Interfaces.pSurface->DrawFilledRect(drX - 6, drY - 1, drX - 3 + 9, drY - 1 + 2);
			Interfaces.pSurface->DrawFilledRect(drX - 1, drY - 6, drX - 1 + 2, drY - 3 + 9);
		}
	}
	
	static void Hitmarker()
	{
		if (Global::hitmarkerAlpha < 0.f)
			Global::hitmarkerAlpha = 0.f;
		else if (Global::hitmarkerAlpha > 0.f)
			Global::hitmarkerAlpha -= 0.01f;

		int W, H;
		Interfaces.pEngine->GetScreenSize(W, H);

		if (Global::hitmarkerAlpha > 0.f)
		{
			DrawLine(W / 2 - 10, H / 2 - 10, W / 2 - 5, H / 2 - 5, CColor(240, 240, 240, (Global::hitmarkerAlpha * 255.f)));
			DrawLine(W / 2 - 10, H / 2 + 10, W / 2 - 5, H / 2 + 5, CColor(240, 240, 240, (Global::hitmarkerAlpha * 255.f)));
			DrawLine(W / 2 + 10, H / 2 - 10, W / 2 + 5, H / 2 - 5, CColor(240, 240, 240, (Global::hitmarkerAlpha * 255.f)));
			DrawLine(W / 2 + 10, H / 2 + 10, W / 2 + 5, H / 2 + 5, CColor(240, 240, 240, (Global::hitmarkerAlpha * 255.f)));

		}
	}

	static void DrawInfo(RECT rect, CBaseEntity* pPlayer)
	{
		float bar = 0;
		float top = 1.4;
		float bot = 0.8;
		float right = 0;
		float left = 0;
		player_info_t info;
		static class Text
		{
		public:
			string text;
			int side;
			int Font;

			Text(string text, int side, int Font) : text(text), side(side), Font(Font)
			{
			}
		};
		std::vector< Text > texts;
		int middle = ((rect.right - rect.left) / 2) + rect.left;

		if (pPlayer->IsHostage())
		{
			if (Options.Visuals.Esp.EspFilter.bHostage)
				Interfaces.pSurface->DrawT(middle, rect.top - top++ * 9, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "Hostage");
		}
		else if (Interfaces.pEngine->GetPlayerInfo(pPlayer->GetIndex(), &info))
		{
			
			if (Options.Visuals.Esp.EspBox.bHealthbar)
			{
				bar++;
				float HealthValue = pPlayer->GetHealth();
				int iHealthValue = HealthValue;
				int Red = 255 - (HealthValue * 2.00);
				int Green = HealthValue * 2.00;
				float flBoxes = std::ceil(pPlayer->GetHealth() / 10.f);

				float height = (rect.bottom - rect.top) * (HealthValue / 100);
				float height2 = (rect.bottom - rect.top) * (100 / 100); // used for the styles like healthbar lines
				float flHeight = height2 / 10.f;

				DrawRect(rect.left - 5, rect.top - 1, rect.left - 1, rect.bottom + 1, CColor(0, 0, 0, 150));
				DrawRect(rect.left - 4, rect.bottom - height, rect.left - 2, rect.bottom, CColor(Red, Green, 0, 255));

				for (int i = 0; i < 10; i++)
					DrawLine(rect.left - 5, rect.top + i * flHeight, rect.left - 2, rect.top + i * flHeight, CColor(0, 0, 0, 255));

				if (Options.Visuals.Esp.EspBox.bHealthText)
				{
					int Health = pPlayer->GetHealth();
					if (Health > 0)
						Interfaces.pSurface->DrawT(rect.left - 30, rect.bottom - height - 2, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%i HP", Health);
				}
			}

			if (Options.Visuals.Esp.EspBox.bArmorBar)
			{
				float ArmorValue = pPlayer->GetArmorValue();
				int iArmorValue = ArmorValue;
				int red = 255 - (ArmorValue * 2.0);
				int blue = ArmorValue * 2.0;

				float height = (rect.right - rect.left) * (ArmorValue / 100);
					
				
				DrawRect(rect.left - 1, rect.bottom + 1, rect.right + 1, rect.bottom + 5, CColor(10, 10, 10, 165));
				DrawRect(rect.left, rect.bottom + 2, rect.left + height, rect.bottom + 4, CColor(red, blue, blue, 255));

				int Armor = pPlayer->GetArmorValue();
//				if (Armor > 0)
//					Interfaces.pSurface->DrawT(rect.left + height, rect.bottom + 2, CColor(255, 255, 255, 255), Hacks.Font_ESP, true, "%i AP", Armor);
			}

			if (Options.Visuals.Esp.EspMisc.bName)
				Interfaces.pSurface->DrawT(middle, rect.top - top++ * 9, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "%s", pPlayer->GetName().c_str());

			if (Options.Visuals.Esp.EspMisc.bIsScoped && pPlayer->m_bIsScoped())
				Interfaces.pSurface->DrawT(middle, rect.top - top++ * 9, CColor(255, 215, 0, 255), Hacks.Font_ESP, true, "*Scoped*");

			if (Options.Visuals.Esp.EspMisc.bIsFlashed && pPlayer->IsFlashed())
				Interfaces.pSurface->DrawT(middle, rect.top + top++ * 9, CColor(255, 0, 0, 255), Hacks.Font_ESP, true, "*Flashed*");

			if(Options.Visuals.Esp.EspBox.bPitch)
			{
				float Pitch = pPlayer->GetEyeAngles().x;
				Interfaces.pSurface->DrawT(middle, rect.bottom + bot++ * 9, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "Pitch: %.1f", Pitch);
			}
			if (Options.Visuals.Esp.EspBox.bYaw)
			{
				float Yaw = pPlayer->GetEyeAngles().y;
				Interfaces.pSurface->DrawT(middle, rect.bottom + bot++ * 9, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "Yaw: %.1f", Yaw);
			}
			CBaseCombatWeapon* weapon = pPlayer->GetActiveBaseCombatWeapon();
			if (weapon)
			{
				if (Options.Visuals.Esp.EspMisc.bWeapons && weapon)
				{
					//char* weaponchar = weapon->GetGunName();
					std::string weaponname = weapon->GetGunName();
					std::string ammo = std::to_string(weapon->ammo());

					CCSWeaponInfo* data = weapon->GetCSWpnData();

					std::string str = "";

					str += weaponname.c_str();

					if (Options.Visuals.Esp.EspMisc.bAmmo)
					{
						if (weapon->ammo() == 0)
							ammo = "EMPTY";
						str += " [";
						str += ammo.c_str();
						str += "]";

						Interfaces.pSurface->DrawT(middle, rect.bottom + bot++ * 9 + 1, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "%s", str.c_str());
					}
					else
						Interfaces.pSurface->DrawT(middle, rect.bottom + bot++ * 9 + 1, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "%s", str.c_str());

					//texts.push_back(Text(weapon->GetGunIcon(), 2, Hacks.Font_ESP));
				}
			}
			//delete[]weapon;
		}

	}

	static void DoEsp()
	{
		CBaseEntity* pEntity;
		static bool bCrosshair;
		//Playerbox();
		if(Options.Visuals.VisualsMisc.bCrosshair)
			Crosshair();

		if (Options.Visuals.VisualsMisc.bHitMarker)
			Hitmarker();

		//Esp::WeaponSkeleton();
		if(Options.Visuals.VisualsMisc.bNormalCrosshair)
		{

			if( !bCrosshair )
			{
				Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 0", 0 );
				bCrosshair = true;
			}
		}
		else
		{
			if( bCrosshair )
			{
				Interfaces.pEngine->ClientCmd_Unrestricted( "crosshair 1", 0 );
				bCrosshair = false;
			}
		}

		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize( width, height );
		for( auto i = 0; i <= Interfaces.pEntList->GetHighestEntityIndex(); i++ )
		{
			CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity( i );
			if( pEntity == nullptr )
				continue;
			if( pEntity == Hacks.LocalPlayer )
				continue;
			if( pEntity->IsDormant() )
				continue;

			player_info_t info;
			const ModelRenderInfo_t pInfo;
			if( Interfaces.pEngine->GetPlayerInfo( pEntity->GetIndex(), &info ) )
			{
				CColor clr = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? CColor( 50, 150, 255, 255 ) : CColor( 255, 0, 0, 255 );
				if( pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() && Options.Visuals.Esp.EspFilter.bEnemyOnly)
					continue;
				if( !pEntity->isAlive() )
					continue;
				
				if(Options.Visuals.Esp.EspFilter.bXQZ && Misc::isVisible(pEntity, 6))
				pEntity->IsSpotted();
				bool PVS = false;
				RECT rect = DynamicBox( pEntity, PVS );
				
				DrawInfo( rect, pEntity );
				
				bool EspBox = (Options.Visuals.Esp.EspBox.bBox);
				if(EspBox)
					DrawBox(rect, pEntity);
				
				if( Options.Visuals.Esp.EspBox.bAimlines )
					DrawSnapLine( Vector( rect.left + ( ( rect.right - rect.left ) / 2 ), rect.bottom, 0 ), clr );
				
				if(Options.Visuals.Esp.EspBox.bSkeleton)
					Skeleton( pEntity );	
				
				int x, y, height;
				
				if(Options.Visuals.VisualsMisc.bEngineRadar)
					*pEntity->IsSpottedPtr() = true;
				
			}

			ClientClass* cClass = (ClientClass*)pEntity->GetClientClass();

			if (Options.Visuals.Esp.EspFilter.bDroppedWeapons && cClass->m_ClassID != (int)CSGOClassID::CBaseWeaponWorldModel && ((strstr(cClass->m_pNetworkName, "Weapon") || cClass->m_ClassID == (int)CSGOClassID::CDEagle || cClass->m_ClassID == (int)CSGOClassID::CAK47)))
			{
				bool d = false;
				RECT rect = DynamicBox(pEntity, d);

				Vector vOrig3D = pEntity->GetAbsOrigin();
				Vector vOrig;
				CBaseCombatWeapon* wep = (CBaseCombatWeapon*)pEntity;
				//IClientEntity* plyr = Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)wep->GetOwnerHandle());
				auto plr = Interfaces.pEntList->GetClientEntityFromHandle((HANDLE)wep->GetOwnerHandle());

				if (!plr && !(vOrig3D.y >= -5 && vOrig3D.y <= 5 && vOrig3D.x >= -5 && vOrig3D.x <= 5))
				{
					std::string name = wep->GetGunName();
					Interfaces.pSurface->DrawT(rect.left, rect.top, CColor(244, 244, 244, 255), Hacks.Font_ESP, true, "%s", name.c_str());
				}
			}
			if(Options.Visuals.Esp.EspFilter.bHostage, pEntity->IsHostage() )
			{
				CColor clr = CColor( 255, 255, 255, 255 );
				bool t;
				RECT rect = DynamicBox( pEntity, t );
				DrawInfo( rect, pEntity );
			}
			if(Options.Visuals.Esp.EspFilter.bC4 && strstr( pEntity->GetClientClass()->m_pNetworkName, "CPlantedC4" ) )
			{
				if (!pEntity->BombDefused())
				{
					float flTime = pEntity->BombTimer() - Interfaces.pGlobalVars->curtime;
					if (flTime > 0.f)
					{
						Vector vPos3D = pEntity->GetAbsOrigin();
						Vector vPos;
						Interfaces.g_pDebugOverlay->ScreenPosition(vPos3D, vPos);

						if (flTime > 0.f)
						{
							bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
							if (flTime < 5.f)
								Interfaces.pSurface->DrawT(vPos.x + 25, vPos.y, bCanDefuse ? CColor(255, 0, 0, 255) : CColor(255, 0, 0, 255), Hacks.Font_Watermark, false, "[C4]: %.1f (Run!)", flTime); // 3 - red
						}

						if (flTime > 5.f)
						{
							bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
							if (flTime < 10.f)
								Interfaces.pSurface->DrawT(vPos.x + 25, vPos.y, bCanDefuse ? CColor(0, 212, 255, 255) : CColor(0, 212, 255, 255), Hacks.Font_Watermark, false, "[C4]: %.1f (Need Kit)", flTime); // 2 - blue
						}

						if (flTime > 10.f)
						{
							bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
							Interfaces.pSurface->DrawT(vPos.x + 25, vPos.y, bCanDefuse ? CColor(255, 255, 255, 255) : CColor(255, 255, 255, 255), Hacks.Font_Watermark, false, "[C4]: %.1f", flTime); // 1 - White
						}
						if (Hacks.LocalPlayer->GetHealth() > 0)
						{
							float flArmor = Hacks.LocalPlayer->GetArmor();
							float flDistance = Hacks.LocalPlayer->GetAbsOrigin().DistTo(pEntity->GetAbsOrigin());
							float a = 450.7f;
							float b = 75.68f;
							float c = 789.2f;
							float d = ((flDistance - b) / c);

							float flDmg = a * exp(-d * d);
							float flDamage = flDmg;

							if (flArmor > 0)
							{
								float flNew = flDmg * 0.5f;
								float flArmor = (flDmg - flNew) * 0.5f;

								if (flArmor > static_cast<float>(flArmor))
								{
									flArmor = static_cast<float>(flArmor) * (1.f / 0.5f);
									flNew = flDmg - flArmor;
								}

								flDamage = flNew;
							}

							int x, y;
							Interfaces.pEngine->GetScreenSize(x, y);

							if (flTime > 0.f)
							{
								bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
								if (flTime < 5.f)
									Interfaces.pSurface->DrawT(80, 20, flDamage >= Hacks.LocalPlayer->GetHealth() ? CColor(255, 0, 0, 255) : CColor(255, 0, 0, 255), Hacks.Font_Bomb, true, "Bomb Timer: %.1f ", flTime); // red
							}

							if (flTime > 5.f)
							{
								bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
								if (flTime < 10.f)
									Interfaces.pSurface->DrawT(80, 20, flDamage >= Hacks.LocalPlayer->GetHealth() ? CColor(0, 212, 255, 255) : CColor(0, 212, 255, 255), Hacks.Font_Bomb, true, "Bomb Timer: %.1f ", flTime); // blue
							}

							if (flTime > 10.f)
							{
								bool bCanDefuse = (Hacks.LocalPlayer->HasKit() && flTime > 5.5f) || flTime > 10.5f;
								Interfaces.pSurface->DrawT(80, 20, flDamage >= Hacks.LocalPlayer->GetHealth() ? CColor(255, 255, 255, 255) : CColor(255, 255, 255, 255), Hacks.Font_Bomb, true, "Bomb Timer: %.1f ", flTime); // white
							}
						}
					}
				}
			}
			//delete[]pEntity;
		}
	}

	static RECT DynamicBox( CBaseEntity* pPlayer, bool& PVS )
	{
		Vector trans = pPlayer->GetVecOrigin();

		Vector min;
		Vector max;

		min = pPlayer->BBMin();
		max = pPlayer->BBMax();

		Vector pointList[] = {
			Vector( min.x, min.y, min.z ),
			Vector( min.x, max.y, min.z ),
			Vector( max.x, max.y, min.z ),
			Vector( max.x, min.y, min.z ),
			Vector( max.x, max.y, max.z ),
			Vector( min.x, max.y, max.z ),
			Vector( min.x, min.y, max.z ),
			Vector( max.x, min.y, max.z )
		};

		Vector Distance = pointList[ 0 ] - pointList[ 1 ];
		int dst = Distance.Length();
		dst /= 1.3f;
		Vector angs;
		Misc::CalcAngle( trans, Hacks.LocalPlayer->GetEyePosition(), angs );

		Vector all[8];
		angs.y += 45;
		for( int i = 0; i < 4; i++ )
		{
			g_Math.angleVectors( angs, all[ i ] );
			all[ i ] *= dst;
			all[ i + 4 ] = all[ i ];
			all[ i ].z = max.z;
			all[ i + 4 ].z = min.z;
			VectorAdd( all[ i ], trans, all[ i ] );
			VectorAdd( all[ i + 4 ], trans, all[ i + 4 ] );
			angs.y += 90;
		}

		Vector flb, brt, blb, frt, frb, brb, blt, flt;
		PVS = true;

		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 3 ], flb ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 0 ], blb ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 2 ], frb ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 6 ], blt ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 5 ], brt ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 4 ], frt ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 1 ], brb ) )
			PVS = false;
		if( !Interfaces.g_pDebugOverlay->ScreenPosition( all[ 7 ], flt ) )
			PVS = false;

		Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

		float left = flb.x;
		float top = flb.y;
		float right = flb.x;
		float bottom = flb.y;

		for( int i = 0; i < 8; i++ )
		{
			if( left > arr[ i ].x )
				left = arr[ i ].x;
			if( top > arr[ i ].y )
				top = arr[ i ].y;
			if( right < arr[ i ].x )
				right = arr[ i ].x;
			if( bottom < arr[ i ].y )
				bottom = arr[ i ].y;
		}
		RECT rect;
		rect.left = left;
		rect.bottom = bottom;
		rect.right = right;
		rect.top = top;
		return rect;
	}

	static void Skeleton(CBaseEntity* pEntity)
	{
		CColor col = CColor(255, 255, 255, 255);


		studiohdr_t* pStudioHdr = Interfaces.g_pModelInfo->GetStudioModel(pEntity->GetModel());

		if (!pStudioHdr)
			return;

		Vector vParent, vChild, sParent, sChild;

		for (int j = 0; j < pStudioHdr->numbones; j++)
		{
			mstudiobone_t* pBone = pStudioHdr->GetBone(j);

			if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
			{
				vChild = pEntity->GetBonePos(j);
				vParent = pEntity->GetBonePos(pBone->parent);
				Interfaces.g_pDebugOverlay->ScreenPosition(vParent, sParent);
				Interfaces.g_pDebugOverlay->ScreenPosition(vChild, sChild);
				int red = 0;
				int green = 0;
				int blue = 0;
				int alpha = 0;
				col.GetColor(red, green, blue, alpha);
				Interfaces.pSurface->DrawSetColor(red, green, blue, alpha);
				Interfaces.pSurface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
			}
			//delete[]pBone;
		}

	}

	static void DrawSnapLine( Vector to, CColor clr )
	{
		int width = 0;
		int height = 0;
		Interfaces.pEngine->GetScreenSize( width, height );
		Vector From( ( width / 2 ), height - 1, 0 );
		DrawLine( From.x, From.y, to.x, to.y, clr );
	}

	static void DrawBox( RECT rect, CBaseEntity* pEntity)
	{
		float red;
		float green;
		float blue;
		if (pEntity->GetTeam() == 2)
		{
			if (Misc::isVisible(pEntity, 6))
			{
				red = Options.Col.espVisT[0];
				green = Options.Col.espVisT[1];
				blue = Options.Col.espVisT[2];
			}
			else
			{
				red = Options.Col.espInvisT[0];
				green = Options.Col.espInvisT[1];
				blue = Options.Col.espInvisT[2];
			}
		}
		else
		{
			if (Misc::isVisible(pEntity, 6))
			{
				red = Options.Col.espVisCT[0];
				green = Options.Col.espVisCT[1];
				blue = Options.Col.espVisCT[2];
			}
			else
			{
				red = Options.Col.espInvisCT[0];
				green = Options.Col.espInvisCT[1];
				blue = Options.Col.espInvisCT[2];
			}
		}

		float newR = red * 255;
		float newG = green * 255;
		float newB = blue * 255;


		DrawOutlinedRect(rect.left - 1, rect.top - 1, rect.right + 1, rect.bottom + 1, CColor(0, 0, 0, 220));
		DrawOutlinedRect(rect.left + 1, rect.top + 1, rect.right - 1, rect.bottom - 1, CColor(0, 0, 0, 220));
		DrawOutlinedRect(rect.left, rect.top, rect.right, rect.bottom, CColor(newR, newG, newB, 220));
	}

	/*
	static void DrawHealthBar(CBaseEntity* pEntity, int x, int y, int height)
	{
		float flBoxes = std::ceil(pEntity->GetHealth() / 10.f);
		float flX = x - 7 - height / 4.f;
		float flY = y - 1;
		float flHeight = height / 10.f;
		float flMultiplier = 12 / 360.f;

		flMultiplier *= flBoxes - 1;
		int Red = 255 - (flBoxes * 2.55);
		int Green = flBoxes * 2.55;
		//CColor ColHealth = CColor::FromHSB(flMultiplier, 1, 1);

		DrawRect(flX, flY, 4, height + 2, CColor(80, 80, 80, 125));
		DrawOutlinedRect(flX, flY, 4, height + 2, CColor(0, 0, 0, 255));
		DrawRect(flX + 1, flY, 2, flHeight * flBoxes + 1, CColor(Red, Green, 0, 255));

		for (int i = 0; i < 10; i++)
			DrawLine(flX, flY + i * flHeight, flX + 4, flY + i * flHeight, CColor(0, 0, 0, 255));
	}
	*/
};
