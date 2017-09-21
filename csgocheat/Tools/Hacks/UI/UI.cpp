#include "UI.h"
static RECT DynamicBox(mstudiobone_t* pBone, bool& PVS)
{
	Vector trans = pBone->pos;

	Vector min;
	Vector max;
	
	min = Vector(trans.x - 2.5, trans.y - 2.5, trans.z - 2.5);
	max = Vector(trans.x + 2.5, trans.y + 2.5, trans.z + 2.5);

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector Distance = pointList[0] - pointList[1];
	int dst = Distance.Length();
	dst /= 1.3f;
	Vector angs;
	Misc::CalcAngle(trans, Hacks.LocalPlayer->GetEyePosition(), angs);

	Vector all[8];
	angs.y += 45;
	for (int i = 0; i < 4; i++)
	{
		g_Math.angleVectors(angs, all[i]);
		all[i] *= dst;
		all[i + 4] = all[i];
		all[i].z = max.z;
		all[i + 4].z = min.z;
		VectorAdd(all[i], trans, all[i]);
		VectorAdd(all[i + 4], trans, all[i + 4]);
		angs.y += 90;
	}

	Vector flb, brt, blb, frt, frb, brb, blt, flt;
	PVS = true;

	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[3], flb))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[0], blb))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[2], frb))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[6], blt))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[5], brt))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[4], frt))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[1], brb))
		PVS = false;
	if (!Interfaces.g_pDebugOverlay->ScreenPosition(all[7], flt))
		PVS = false;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	float left = flb.x;
	float top = flb.y;
	float right = flb.x;
	float bottom = flb.y;

	for (int i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top > arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom < arr[i].y)
			bottom = arr[i].y;
	}
	RECT rect;
	rect.left = left;
	rect.bottom = bottom;
	rect.right = right;
	rect.top = top;
	return rect;
}

static void DrawCircle(RECT rect, CColor Color)
{
	int yMiddle = (rect.left + rect.right) / 2;
	int xMiddle = (rect.bottom + rect.top) / 2;
	float radius = (rect.bottom - rect.top) / 2;
	int r, g, b, a;
	Color.GetColor(r, g, b, a);
	Interfaces.pSurface->DrawColoredCircle(xMiddle, yMiddle, radius, r, g, b, a);
}


DeathInfo::DeathInfo( int id1, int id2, char* WeaponName, bool Headshot ) : WeaponName( WeaponName ), Headshot( Headshot )
{
	Timer = 700;
	CBaseEntity* Killer = Interfaces.pEntList->GetClientEntity( Interfaces.pEngine->GetPlayerForUserID( id1 ) );
	CBaseEntity* Target = Interfaces.pEntList->GetClientEntity( Interfaces.pEngine->GetPlayerForUserID( id2 ) );
	if( Killer == Hacks.LocalPlayer )
	{
		Timer = 1500;
		LocalIsKiller = true;
	}

	if( Killer && Target )
	{
		KillerName = Killer->GetName();
		TargetName = Target->GetName();
	}
}

void KillFeed::Run()
{
	int Bottom = 70;
	int W, H;
	Interfaces.pEngine->GetScreenSize( W, H );
	int Biggest = 0;
	for( size_t i = 0; i < Deaths.size(); i++ )
	{
		DeathInfo* Death = &Deaths[ i ];
		Death->Timer--;
		if( Death->Timer < 0 )
			Deaths.erase( Deaths.begin() + i );
		string FeedStr = std::string( Death->KillerName ) + " -> " + std::string( Death->WeaponName ) + " : " + std::string( Death->TargetName );
		RECT nameSize = GetTextSize( Hacks.Font_HUD, FeedStr.c_str() );
		if( nameSize.right > Biggest )
			Biggest = nameSize.right;
		Bottom += nameSize.bottom + ( i + 1 != Deaths.size() ? 3 : 0 );
	}
	Deaths.shrink_to_fit();
	if( Deaths.size() == 0 )
		return;
	RECT BoxRect;
	BoxRect.left = W - ( Biggest + 10 );
	BoxRect.right = W - 10;
	BoxRect.top = 70;
	BoxRect.bottom = Bottom;
	DrawRect( BoxRect.left - 5 - 2, BoxRect.top - 5 - 2, BoxRect.right + 5 + 2, BoxRect.bottom + 5 + 2, CColor( 5, 5, 5, 255 ) );
	DrawRect( BoxRect.left - 5 - 1, BoxRect.top - 5 - 1, BoxRect.right + 5 + 1, BoxRect.bottom + 5 + 1, CColor( 75, 75, 75, 255 ) );
	DrawRect( BoxRect.left - 5, BoxRect.top - 5, BoxRect.right + 5, BoxRect.bottom + 5, CColor( 22.5, 22.5, 22.5, 255 ) );
	Bottom = 70;
	for( size_t i = 0; i < Deaths.size(); i++ )
	{
		DeathInfo Death = Deaths[ i ];

		string FeedStr = std::string( Death.KillerName ) + " -> " + std::string( Death.WeaponName ) + " : " + std::string( Death.TargetName );
		RECT nameSize = GetTextSize( Hacks.Font_HUD, FeedStr.c_str() );
		CColor clr = Death.Headshot ? CColor( 255, 0, 0, 255 ) : CColor( 0, 200, 255, 255 );
		if( !Death.LocalIsKiller )
		{
			for( int i = 0; i < 3; i++ )
				clr._color[ i ] *= 0.58f;
		}
		Interfaces.pSurface->DrawT( W - nameSize.right - 10, Bottom, clr, Hacks.Font_HUD, false, ( char* )FeedStr.c_str() );

		Bottom += nameSize.bottom + 3;
	}
}

void UI::DrawRadar()
{
	int W, H;
	Interfaces.pEngine->GetScreenSize( W, H );
	Vector TL( 30, 30, 0 );
	Vector TR( TL.x + 200, TL.y, 0 );
	Vector BL( TL.x, TL.y + 200, 0 );
	Vector BR( TL.x + 200, TL.y + 200, 0 );

	DrawRect( TL.x, TL.y, TL.x + 200, TL.y + 200, CColor( 5, 5, 5, 255 ) );
	DrawRect( TL.x + 1, TL.y + 1, TL.x + 199, TL.y + 199, CColor( 75, 75, 75, 255 ) );
	Interfaces.pSurface->DrawSetColor( 22, 22, 22, 255 );
	Interfaces.pSurface->DrawFilledRect( TL.x + 2, TL.y + 2, TL.x + 198, TL.y + 198 );

	Interfaces.pSurface->DrawSetColor( 75, 75, 75, 255 );

	Interfaces.pSurface->DrawLine( TL.x + 50, TL.y + 50, TL.x + 100, TL.y + 100 );
	Interfaces.pSurface->DrawLine( TR.x - 50, TL.y + 50, TL.x + 100, TL.y + 100 );

	Interfaces.pSurface->DrawLine( TL.x + 100, TL.y, TL.x + 100, TL.y + 200 );
	Interfaces.pSurface->DrawLine( TL.x, TL.y + 100, TL.x + 200, TL.y + 100 );

	Vector center = Vector( ( TL.x + TR.x ) / 2, ( TL.y + BL.y ) / 2, 0.f );

	for( int i = 0; i < Interfaces.pEntList->GetHighestEntityIndex(); i++ )
	{
		CBaseEntity* pEntity = Interfaces.pEntList->GetClientEntity( i );
		if( pEntity )
		{
			if( !pEntity->isValidPlayer() || Hacks.LocalPlayer->GetIndex() == pEntity->GetIndex() )
				continue;
			CColor c = pEntity->GetTeam() == Hacks.LocalPlayer->GetTeam() ? CColor( 50, 150, 255, 255 ) : CColor( 255, 255, 255, 255 );
			Vector relPos = ( pEntity->GetAbsOrigin() - Hacks.LocalPlayer->GetAbsOrigin() ) * 0.05f;
			relPos.y *= -1.f;
			Vector drawAt = Vector( relPos.x + center.x, relPos.y + center.y, 0 );
			Vector localAng;
			Interfaces.pEngine->GetViewAngles( localAng );

			drawAt = g_Math.RotatePoint( drawAt, center, localAng.y - 90 );
			if( drawAt.x < TR.x && drawAt.x > TL.x && drawAt.y < BL.y && drawAt.y > TL.y )
				DrawRect( drawAt.x - 1, drawAt.y - 1, drawAt.x + 2, drawAt.y + 2, c );
		}
	}
}

void UI::DrawWeapons()
{
	CBaseEntity *LocalGun = Hacks.LocalWeapon;
	if (!LocalGun)
		return;
	studiohdr_t* pStudioHdr = (studiohdr_t*)Interfaces.g_pModelInfo->FindModel("weapon");
	if (pStudioHdr == nullptr)
		return;
	mstudiobone_t* pBone = nullptr;
	for (int i = 0; i != pStudioHdr->numbones; i++)
	{
		pBone = pStudioHdr->GetBone(i);
		if (pBone->GetName() == "weapon_mag")
			break;
	};
	if (pBone == nullptr)
		return;
	//matrix3x4 *BonePos = (matrix3x4*)Bone->poseToBone;
	//Vector BoneEndPos = Vector(*BonePos[2][1], *BonePos[2][2], *BonePos[2][3]);
	Vector vChild,sChild;
	vChild = pBone->pos;
	Interfaces.g_pDebugOverlay->ScreenPosition(vChild, sChild);
	
	//Interfaces.pSurface->DrawSetColor(0, 200, 255, 255);
	//bool PVS = false;
	//DynamicBox(Bone, PVS);
	//DrawCircle(DynamicBox(Bone, PVS), CColor(0, 200, 255, 255));
	Interfaces.pSurface->DrawColoredCircle(sChild.x, sChild.y, 10, 0, 200, 255, 255);
}


/*
void UI::DrawWeapons()
{
	int W, H;
	Interfaces.pEngine->GetScreenSize( W, H );
	int Longest = 0;
	int Top = 0;
	auto weapons = Hacks.LocalPlayer->GetWeapons();
	for( int i = 0; i < weapons.size(); i++ )
	{
		auto weapon = weapons[ i ];
		RECT nameSize = GetTextSize( Hacks.Font_HUD, weapon->GetGunName() );
		if( nameSize.right > Longest )
			Longest = nameSize.right;
		Top += nameSize.bottom + 3;
	}

	DrawRect( W - Longest - 12, H - Top - 3 - 54, W, H, CColor( 5, 5, 5, 255 ) );
	DrawRect( W - Longest - 11, H - Top - 3 - 53, W, H, CColor( 75, 75, 75, 255 ) );
	DrawRect( W - Longest - 10, H - Top - 3 - 52, W, H, CColor( 22.5, 22.5, 22.5, 255 ) );


	Top = 0;
	for( int i = 0; i < weapons.size(); i++ )
	{
		auto weapon = weapons[ i ];
		RECT nameSize = GetTextSize( Hacks.Font_HUD, weapon->GetGunName() );
		Top += nameSize.bottom + 3;
		Interfaces.pSurface->DrawT( W - 5 - nameSize.right, H - Top - 3 - 52, weapon == Hacks.LocalWeapon ? CColor( 0, 200, 255, 255 ) : CColor( 150, 150, 150, 255 ), Hacks.Font_HUD, false, weapon->GetGunName() );
	}

	DrawRect( W - 202, H - 52, W, H, CColor( 5, 5, 5, 255 ) );
	DrawRect( W - 201, H - 51, W, H, CColor( 75, 75, 75, 255 ) );
	DrawRect( W - 200, H - 50, W, H, CColor( 22.5, 22.5, 22.5, 255 ) );

	if( Hacks.LocalWeapon )
	{
		int iAmmo = Hacks.LocalWeapon->ammo();
		string Clip = iAmmo >= 0 ? to_string( iAmmo ) : "--";

		RECT nameSize = GetTextSize( Hacks.Font_HUD_Big, Clip.c_str() );
		Interfaces.pSurface->DrawT( W - 100 - nameSize.right / 2, ( H - 25 ) - ( nameSize.bottom / 2.f ), CColor( 255, 255, 255, 255 ), Hacks.Font_HUD_Big, false, ( char* )Clip.c_str() );
	}
}*/

void UI::DrawHealth()
{
	int W, H;
	Interfaces.pEngine->GetScreenSize( W, H );
	DrawRect( 0, H - 52, 406, H, CColor( 5, 5, 5, 255 ) );
	DrawRect( 0, H - 50, 404, H, CColor( 22.5, 22.5, 22.5, 255 ) );
	DrawOutlinedRect( 0, H - 51, 202, H, CColor( 75, 75, 75, 255 ) );
	DrawOutlinedRect( 203, H - 51, 405, H, CColor( 75, 75, 75, 255 ) );

	string Health = to_string( Hacks.LocalPlayer->GetHealth() );
	RECT nameSize = GetTextSize( Hacks.Font_HUD_Big, Health.c_str() );
	Interfaces.pSurface->DrawT( 100 - nameSize.right / 2 - 35, ( H - 33 ) - ( nameSize.bottom / 2.f ), CColor( 255, 255, 255, 255 ), 0xA2, false, "b" );
	Interfaces.pSurface->DrawT( 100 - nameSize.right / 2, ( H - 25 ) - ( nameSize.bottom / 2.f ), CColor( 255, 255, 255, 255 ), Hacks.Font_HUD_Big, false, ( char* )Health.c_str() );

	string Armor = to_string( Hacks.LocalPlayer->GetArmorValue() );
	nameSize = GetTextSize( Hacks.Font_HUD_Big, Armor.c_str() );
	Interfaces.pSurface->DrawT( 300 - nameSize.right / 2 - 35, ( H - 33 ) - ( nameSize.bottom / 2.f ), CColor( 255, 255, 255, 255 ), 0xA2, false, Hacks.LocalPlayer->HasHelmet() ? "l" : "a" );
	Interfaces.pSurface->DrawT( 300 - nameSize.right / 2, ( H - 25 ) - ( nameSize.bottom / 2.f ), CColor( 255, 255, 255, 255 ), Hacks.Font_HUD_Big, false, ( char* )Armor.c_str() );
}

void UI::Draw()
{
	ConVar* m_pHudDraw = Interfaces.g_ICVars->FindVar( "cl_drawhud" );
	bool bDraw = Settings.GetMenuSetting( Tab_Misc, Misc_UI );

	m_pHudDraw->SetValue( !bDraw );
	if( bDraw )
	{
		DrawHealth();
		DrawWeapons();
		DrawRadar();
		Feed.Run();
		ChatBox.Run();
	}
}

UI GUI;
