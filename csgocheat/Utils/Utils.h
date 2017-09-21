#pragma once
#include "../stdafx.h"

#define INRANGE(x, a, b)	(x >= a && x <= b)
#define GETBITS(x)			(INRANGE((x&(~0x20)),'A','F') ? ((x&(~0x20)) - 'A' + 0xa) : (INRANGE(x,'0','9') ? x - '0' : 0))
#define GETBYTE(x)			(GETBITS(x[0]) << 4 | GETBITS(x[1]))

class CUtils
{
public:
	DWORD PFindPattern( std::string moduleName, std::string pattern )
	{
		const char* pat = pattern.c_str();
		DWORD firstMatch = 0;
		DWORD rangeStart = ( DWORD )GetModuleHandleA( moduleName.c_str() );
		MODULEINFO miModInfo;
		GetModuleInformation( GetCurrentProcess(), ( HMODULE )rangeStart, &miModInfo, sizeof(MODULEINFO) );
		DWORD rangeEnd = rangeStart + miModInfo.SizeOfImage;
		for( DWORD pCur = rangeStart; pCur < rangeEnd; pCur++ )
		{
			if( !*pat )
				return firstMatch;
			if( *( PBYTE )pat == '\?' || *( BYTE* )pCur == GETBYTE(pat) )
			{
				if( !firstMatch )
					firstMatch = pCur;
				if( !pat[ 2 ] )
					return firstMatch;
				if( *( PWORD )pat == '\?\ ? ' || *(PBYTE)pat != '\ ? ')
					                            pat += 3;
					else
						pat += 2;
			}
			else
			{
				pat = pattern.c_str();
				firstMatch = 0;
			}
		}
		return NULL;
	}

	ULONG PatternSearch( std::string sModuleName, PBYTE pbPattern, std::string sMask, ULONG uCodeBase, ULONG uSizeOfCode )
	{
		BOOL bPatternDidMatch = FALSE;
		HMODULE hModule = GetModuleHandle( sModuleName.c_str() );

		if( !hModule )
			return 0x0;

		PIMAGE_DOS_HEADER pDsHeader = PIMAGE_DOS_HEADER( hModule );
		PIMAGE_NT_HEADERS pPeHeader = PIMAGE_NT_HEADERS( LONG( hModule ) + pDsHeader->e_lfanew );
		PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pPeHeader->OptionalHeader;

		if( uCodeBase == 0x0 )
			uCodeBase = ( ULONG )hModule + pOptionalHeader->BaseOfCode;

		if( uSizeOfCode == 0x0 )
			uSizeOfCode = pOptionalHeader->SizeOfCode;

		ULONG uArraySize = sMask.length();

		if( !uCodeBase || !uSizeOfCode || !uArraySize )
			return 0x0;

		for( size_t i = uCodeBase; i <= uCodeBase + uSizeOfCode; i++ )
		{
			for( size_t t = 0; t < uArraySize; t++ )
			{
				if( *( ( PBYTE )i + t ) == pbPattern[ t ] || sMask.c_str()[ t ] == '?' )
					bPatternDidMatch = TRUE;

				else
				{
					bPatternDidMatch = FALSE;
					break;
				}
			}

			if( bPatternDidMatch )
				return i;
		}

		return 0x0;
	}

	std::uint8_t* PatternScan(void* module, const char* signature)
	{
		static auto pattern_to_byte = [](const char* pattern) {
			auto bytes = std::vector<int>{};
			auto start = const_cast<char*>(pattern);
			auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current) {
				if (*current == '?') {
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else {
					bytes.push_back(strtoul(current, &current, 16));
				}
			}
			return bytes;
		};

		auto dosHeader = (PIMAGE_DOS_HEADER)module;
		auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)module + dosHeader->e_lfanew);

		auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto patternBytes = pattern_to_byte(signature);
		auto scanBytes = reinterpret_cast<std::uint8_t*>(module);

		auto s = patternBytes.size();
		auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i) {
			bool found = true;
			for (auto j = 0ul; j < s; ++j) {
				if (scanBytes[i + j] != d[j] && d[j] != -1) {
					found = false;
					break;
				}
			}
			if (found) {
				return &scanBytes[i];
			}
		}
		return nullptr;
	}

	static uint64_t FindPatternIDA(const char* szModule, const char* szSignature)
	{

#define INRANGE(x,a,b)  (x >= a && x <= b) 
#define getBits( x )    (INRANGE((x&(~0x20)),((char)(0x1116+2506-0x1a9f)),((char)(0xab+9102-0x23f3))) ? ((x&(~0x20)) - ((char)(0xd2a+2075-0x1504)) + 0xa) : (INRANGE(x,((char)(0x1186+4058-0x2130)),((char)(0x848+343-0x966))) ? x - ((char)(0x13c2+2199-0x1c29)) : 0))
#define getByte( x )    (getBits(x[0]) << 4 | getBits(x[1]))

		MODULEINFO modInfo;
		GetModuleInformation(GetCurrentProcess(), GetModuleHandleA(szModule), &modInfo, sizeof(MODULEINFO));
		DWORD startAddress = (DWORD)modInfo.lpBaseOfDll;
		DWORD endAddress = startAddress + modInfo.SizeOfImage;
		const char* pat = szSignature;
		DWORD firstMatch = 0;
		for (DWORD pCur = startAddress; pCur < endAddress; pCur++) {
			if (!*pat) return firstMatch;
			if (*(PBYTE)pat == '\?' || *(BYTE*)pCur == getByte(pat)) {
				if (!firstMatch) firstMatch = pCur;
				if (!pat[2]) return firstMatch;
				if (*(PWORD)pat == '\?\?' || *(PBYTE)pat != '\?') pat += 3;
				else pat += 2;
			}
			else {
				pat = szSignature;
				firstMatch = 0;
			}
		}
		return NULL;
	}

	HMODULE GetModuleHandleSafe( const char* pszModuleName )
	{
		HMODULE hmModuleHandle = nullptr;

		do
		{
			hmModuleHandle = GetModuleHandle( pszModuleName );
			Sleep( 1 );
		}
		while( hmModuleHandle == nullptr );

		return hmModuleHandle;
	}
};

extern CUtils Utils;
