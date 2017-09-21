#pragma once
#include "../../../stdafx.h"
#include "../Misc.h"
#include "ChatBox/ChatBox.h"

class DeathInfo
{
public:
	std::string KillerName, TargetName, WeaponName;
	int Timer;
	bool LocalIsKiller = false, Headshot = false;;
	DeathInfo( int id1, int id2, char* WeaponName, bool Headshot );
};

class KillFeed
{
	std::vector< DeathInfo > Deaths;
public:
	void AddDeath( DeathInfo Death )
	{
		if( Settings.GetMenuSetting( Tab_Misc, Misc_UI ) )
			Deaths.emplace_back( Death );
	}

	KillFeed()
	{
	}

	void Run();
};

class UI
{
public:
	KillFeed Feed;
	ChatBox ChatBox;

	UI()
	{
	};

	~UI()
	{
	};
	void DrawInfoBox( int size, string text );

	void DrawRadar();

	void DrawWeapons();

	void DrawHealth();

	void Draw();
};

extern UI GUI;
