#pragma once
#include "../../stdafx.h"
#include "Hitbox.h"

class PlayerList
{
public:
	class CPlayer
	{
	public:
		Vector ShootPos[125];
		int index = -1;
		CBaseEntity* entity;
		Vector reset = Vector(0, 0, 0);
		float lastsim = 0;
		Vector lastorigin = Vector(0, 0, 0);
		std::vector< float > pastangles;
		int ScannedNumber = 0;
		int BestIndex = 0;
		float difference = 0.f;
		float Backtrack[360];
		float flLastPelvisAng = 0.f;
		float flEyeAng = 0.f;
		float resolved = 0.f;
		float posedifference = 0.f;
		Hitbox* box;

		char * aa = "Unkown";

		CPlayer(CBaseEntity* entity, int index, int lastsim) : entity(entity), index(index), lastsim(lastsim)
		{
		}
	};

private:
	std::vector< CPlayer > Players;
public:
	void Update()
	{
		for (int i = 0; i < Players.size(); i++)
		{
			if (Players[i].entity == nullptr)
			{
				Players.erase(Players.begin() + i);
				continue;
			}
			if (Players[i].entity == Hacks.LocalPlayer)
			{
				Players.erase(Players.begin() + i);
				continue;
			};
		}
	}

	void UpdateSim()
	{
		Update();
		for (int i = 0; i < Players.size(); i++)
		{
			Players[i].lastsim = Players[i].entity->GetSimulationTime();
		}
	}

	void AddPlayer(CBaseEntity* ent)
	{
		Players.emplace_back(CPlayer(ent, ent->GetIndex(), ent->GetSimulationTime()));
	}

	CPlayer* FindPlayer(CBaseEntity* ent)
	{
		for (int i = 0; i < Players.size(); i++)
			if (Players[i].index == ent->GetIndex())
				return &Players[i];
		AddPlayer(ent);
		return FindPlayer(ent);
	}
} plist;