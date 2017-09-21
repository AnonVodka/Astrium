#include "ChatBox.h"

void ChatBox::Run()
{
	int W, H;
	Interfaces.pEngine->GetScreenSize( W, H );
	DrawRect( 30, H - 200 - 80, 376, H - 80, CColor( 5, 5, 5, 255 ) );
	DrawRect( 31, H - 200 - 79, 375, H - 81, CColor( 75, 75, 75, 255 ) );
	DrawRect( 32, H - 200 - 78, 374, H - 82, CColor( 22.5, 22.5, 22.5, 255 ) );

	DrawRect( 35, H - 85 - 22, 371, H - 85, CColor( 5, 5, 5, 255 ) );
	DrawRect( 36, H - 86 - 20, 370, H - 86, ChatEnabled ? CColor( 100, 100, 100, 255 ) : CColor( 75, 75, 75, 255 ) );

	DrawRect( 36, H - 86 - 24, 370, H - 86 - 23, CColor( 75, 75, 75, 255 ) );

	int Bottom = H - 86 - 27;
	int LimitY = H - 200 - 75;
	int LimitX = 370;

	int Top = 1;
	std::vector< string > text;
	for( int i = Msgs.size() - 1; i >= 0; i-- )
	{
		auto Message = Msgs[ i ];
		string raw = ( Message.Team ? "(TEAM) " : "" ) + Message.Player->GetName() + ": " + Message.Text;

		RECT nameSize = GetTextSize( Hacks.Font_Controls, raw.c_str() );

		if( nameSize.right + 36 <= LimitX )
		{
			if( Bottom - ( Top + nameSize.bottom + 2 ) < LimitY )
				break;
			Top += nameSize.bottom + 2;
			Interfaces.pSurface->DrawT( 36, Bottom - Top, CColor( 255, 255, 255, 255 ), Hacks.Font_Controls, false, ( char* )raw.c_str() );
		}
	}
	if( IsKeyDown( 0x59 ) )
		ChatEnabled = true;
	else if( IsKeyDown( 0x1B ) )
		ChatEnabled = false;
}

ChatBox::ChatBox()
{
}


ChatBox::~ChatBox()
{
}
