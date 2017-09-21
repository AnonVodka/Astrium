#pragma once
#include "../../../../stdafx.h"

inline bool IsKeyDown( DWORD key )
{
	if( INIT::Window == GetFocus() )
	{
		if( GetAsyncKeyState( key ) )
			return true;
	}
	return false;
}

struct Message
{
	bool Team;
	CBaseEntity* Player;
	string Text;

	Message( bool Team, int PlayerID, string Text ) : Team( Team ), Text( Text )
	{
		Player = Interfaces.pEntList->GetClientEntity( Interfaces.pEngine->GetPlayerForUserID( PlayerID ) );
	}
};

class ChatBox
{
	vector< Message > Msgs;
protected:
	bool ChatEnabled = false;
public:
	void AddMessage( Message Msg )
	{
		Msgs.emplace_back( Msg );
	}

	void Run();
	ChatBox();
	~ChatBox();
};
