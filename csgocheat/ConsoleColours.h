/*
ConsoleColours.h
By NeverT

Functon:
Applys A Color To Text In Consoles
Usefull In Outputting Text To Stand Out
Usage:
cout << (color) << "text" << endl;
Colors With 'i' at the front are using FOREGROUND_INTENSITY (0x0080)
*/
#pragma once
#include <iostream>
#include <windows.h>

/*
Text Color Attributes flags (from wincon.h):
They Are Placed Here For Easy Viewing
FOREGROUND_BLUE      0x0001 // text color contains blue.
FOREGROUND_GREEN     0x0002 // text color contains green.
FOREGROUND_RED       0x0004 // text color contains red.
FOREGROUND_INTENSITY 0x0008 // text color is intensified.
BACKGROUND_BLUE      0x0010 // background color contains blue.
BACKGROUND_GREEN     0x0020 // background color contains green.
BACKGROUND_RED       0x0040 // background color contains red.
BACKGROUND_INTENSITY 0x0080 // background color is intensified.
*/
inline std::ostream& TITLE( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_GREEN );
	return s;
}

inline std::ostream& iblue( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_BLUE | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& ired( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& igreen( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& iyellow( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& iaqua( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& ipurple( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_INTENSITY );
	return s;
}

inline std::ostream& blue( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_BLUE );
	return s;
}

inline std::ostream& red( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED );
	return s;
}

inline std::ostream& green( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN );
	return s;
}

inline std::ostream& yellow( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN | FOREGROUND_RED );
	return s;
}

inline std::ostream& aqua( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_GREEN | FOREGROUND_BLUE );
	return s;
}

inline std::ostream& purple( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_BLUE );
	return s;
}

inline std::ostream& white( std::ostream& s )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE );
	return s;
}

struct ooocolor
{
	ooocolor( WORD attribute ) : m_color( attribute )
	{
	};

	WORD m_color;
};

template< class _Elem, class _Traits >
std::basic_ostream< _Elem, _Traits >& operator<<( std::basic_ostream< _Elem, _Traits >& i, ooocolor& c )
{
	HANDLE hStdout = GetStdHandle( STD_OUTPUT_HANDLE );
	SetConsoleTextAttribute( hStdout, c.m_color );
	return i;
}
