#pragma once
#include "../../stdafx.h"
#define IsNullPtr( ptr )( ptr == nullptr )

typedef struct
{
	unsigned __int64 unknown;
	unsigned __int64 xuid;
	char name[32];

	char unknown01[96];

	char m_szPlayerName[128];
	int m_nUserID;
	char m_szSteamID[33];
	UINT m_nSteam3ID;

	int userID;
	char guid[32 + 1];
	__int32 friendsID;
	char friendsName[32];
	bool fakeplayer;
	bool ishltv;
	unsigned long customFiles[4];
	unsigned char filesDownloaded;
	char pad[304];
} player_info_t;

typedef struct con_nprint_s
{
	int index;
	float time_to_live;
	float color[3];
	bool fixed_width_font;
} con_nprint_t;

class CEngineClient
{
public:
	virtual void vfunc00() = 0;

	virtual void vfunc01() = 0;

	virtual void vfunc02() = 0;

	virtual void vfunc03() = 0;

	virtual void vfunc04() = 0;

	virtual void vfunc05() = 0;

	virtual void vfunc06() = 0;

	virtual void vfunc07() = 0;

	virtual void vfunc08() = 0;

	virtual void vfunc10() = 0;

	virtual void vfunc11() = 0;

	virtual void vfunc12() = 0;

	virtual void vfunc13() = 0;

	virtual void vfunc14() = 0;

	virtual void vfunc15() = 0;

	virtual void vfunc16() = 0;

	virtual void vfunc17() = 0;

	virtual void vfunc18() = 0;

	virtual void vfunc19() = 0;

	virtual void vfunc20() = 0;

	virtual void vfunc21() = 0;

	virtual void vfunc22() = 0;

	virtual void vfunc23() = 0;

	virtual void vfunc24() = 0;

	virtual void vfunc25() = 0;

	virtual void vfunc26() = 0;

	virtual void vfunc27() = 0;

	virtual void vfunc28() = 0;

	virtual void vfunc29() = 0;

	virtual void vfunc30() = 0;

	virtual void Con_NXPrintf(const struct con_nprint_s* info, const char* fmt, ...) = 0;

	int GetPlayerForUserID(int userID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID, int);
		return getvfunc< OriginalFn >(this, 9)(this, userID);
	}

	void CEngineClient::GetScreenSize(int& width, int& height)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int&, int&);
		getvfunc< OriginalFn >(this, 5)(this, width, height);
	}

	INetChannelInfo* GetNetChannelInfo(void)
	{
		typedef INetChannelInfo*(__thiscall* OriginalFn)(PVOID);
		return getvfunc< OriginalFn >(this, 78)(this);
	}

	bool CEngineClient::GetPlayerInfo(int iIndex, player_info_t* pInfo)
	{
		typedef bool(__thiscall* OriginalFn)(PVOID, int, player_info_t*);
		return getvfunc< OriginalFn >(this, 8)(this, iIndex, pInfo);
	}

	void CEngineClient::ClientCmd_Unrestricted(const char* szCmdString, char flag)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const char*, char);
		getvfunc< OriginalFn >(this, 114)(this, szCmdString, flag);
	}

	int CEngineClient::GetLocalPlayer(VOID)
	{
		typedef int(__thiscall* OriginalFn)(PVOID);
		return getvfunc< OriginalFn >(this, 12)(this);
	}

	VMatrix& CEngineClient::WorldToScreenMatrix(void)
	{
		typedef VMatrix& (__thiscall* OriginalFn)(PVOID);
		return getvfunc< OriginalFn >(this, 37)(this);
	}

	void CEngineClient::ExecuteClientCmd(char const* szCommand)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, char const* szCommand);
		getvfunc< OriginalFn >(this, 105)(this, szCommand);
	}

	void CEngineClient::GetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, Vector&);
		return getvfunc< OriginalFn >(this, 18)(this, vAngles);
	}

	void CEngineClient::SetViewAngles(Vector& vAngles)
	{
		typedef void(__thiscall* oSetViewAngles)(PVOID, Vector&);
		return getvfunc< oSetViewAngles >(this, 19)(this, vAngles);
	}

	bool CEngineClient::IsConnected()
	{
		typedef bool(__thiscall* oGetScreenSize)(PVOID);
		return getvfunc< oGetScreenSize >(this, 27)(this);
	}

	bool CEngineClient::IsInGame()
	{
		typedef bool(__thiscall* oLocal)(PVOID);
		return getvfunc< oLocal >(this, 26)(this);
	}

	int CEngineClient::GetMaxClients()
	{
		typedef bool(__thiscall* oGetMaxClients)(PVOID);
		return getvfunc< oGetMaxClients >(this, 20)(this);
	}

	float CEngineClient::Time()
	{
		typedef float(__thiscall* oTime)(PVOID);
		return getvfunc< oTime >(this, 14)(this);
	}

	unsigned int GetEngineBuildNumber()
	{
		typedef unsigned int(__thiscall* OriginalFn)(PVOID);
		return getvfunc< OriginalFn >(this, 104)(this);
	}
};
