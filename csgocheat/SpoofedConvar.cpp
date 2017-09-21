#pragma once
#include "stdafx.h"

SpoofedConvar::SpoofedConvar()
{
}

SpoofedConvar::SpoofedConvar( const char* szCVar )
{
	m_pOriginalCVar = Interfaces.g_ICVars->FindVar( szCVar );
	Spoof();
}

SpoofedConvar::SpoofedConvar( ConVar* pCVar )
{
	m_pOriginalCVar = pCVar;
	Spoof();
}

SpoofedConvar::~SpoofedConvar()
{
	if( IsSpoofed() )
	{
		DWORD dwOld;

		SetFlags( m_iOriginalFlags );
		SetString( m_szOriginalValue );

		VirtualProtect( ( LPVOID )m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld );
		strcpy( ( char* )m_pOriginalCVar->pszName, m_szOriginalName );
		VirtualProtect( ( LPVOID )m_pOriginalCVar->pszName, 128, dwOld, &dwOld );

		//Unregister dummy cvar
		Interfaces.g_ICVars->UnRegisterConCommand( m_pDummyCVar );
		free( m_pDummyCVar );
		m_pDummyCVar = nullptr;
	}
}

bool SpoofedConvar::IsSpoofed()
{
	return m_pDummyCVar != nullptr;
}

void SpoofedConvar::Spoof()
{
	if( !IsSpoofed() && m_pOriginalCVar )
	{
		//Save old name value and flags so we can restore the cvar lates if needed
		m_iOriginalFlags = m_pOriginalCVar->nFlags;
		strcpy( m_szOriginalName, m_pOriginalCVar->pszName );
		strcpy( m_szOriginalValue, m_pOriginalCVar->pszDefaultValue );

		sprintf_s( m_szDummyName, 128, "d_%s", m_szOriginalName );

		//Create the dummy cvar
		m_pDummyCVar = ( ConVar* )malloc( sizeof( ConVar) );
		if( !m_pDummyCVar )
			return;
		memcpy( m_pDummyCVar, m_pOriginalCVar, sizeof( ConVar) );

		m_pDummyCVar->pNext = nullptr;
		//Register it
		Interfaces.g_ICVars->RegisterConCommand( m_pDummyCVar );

		//Fix "write access violation" bullshit
		DWORD dwOld;
		VirtualProtect( ( LPVOID )m_pOriginalCVar->pszName, 128, PAGE_READWRITE, &dwOld );

		//Rename the cvar
		strcpy( ( char* )m_pOriginalCVar->pszName, m_szDummyName );

		VirtualProtect( ( LPVOID )m_pOriginalCVar->pszName, 128, dwOld, &dwOld );

		SetFlags( FCVAR_NONE );
	}
}

void SpoofedConvar::SetFlags( int flags )
{
	if( IsSpoofed() )
	{
		m_pOriginalCVar->nFlags = flags;
	}
}

int SpoofedConvar::GetFlags()
{
	return m_pOriginalCVar->nFlags;
}

void SpoofedConvar::SetInt( int iValue )
{
	if( IsSpoofed() )
	{
		m_pOriginalCVar->SetValue( iValue );
	}
}

void SpoofedConvar::SetBool( bool bValue )
{
	if( IsSpoofed() )
	{
		m_pOriginalCVar->SetValue( bValue );
	}
}

void SpoofedConvar::SetFloat( float flValue )
{
	if( IsSpoofed() )
	{
		m_pOriginalCVar->SetValue( flValue );
	}
}

void SpoofedConvar::SetString( const char* szValue )
{
	if( IsSpoofed() )
	{
		m_pOriginalCVar->SetValue( szValue );
	}
}
