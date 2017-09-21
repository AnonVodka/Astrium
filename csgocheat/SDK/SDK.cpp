#include "../stdafx.h"
#include <unordered_map>
//------------------------------------------------------------
// Classes to help the parsing of the netvars
//------------------------------------------------------------
#pragma region Helper classes

typedef unordered_map< string, unique_ptr< NetvarTable > > TableMap;
typedef unordered_map< string, uint32_t > PropMap;

typedef unordered_map< string, unique_ptr< NetvarTable > >::iterator Iter;

struct NetvarTable
{
	TableMap m_ChildTables;
	PropMap m_ChildProps;
	uint32_t m_uOffset = 0;

	bool is_empty()
	{
		return m_ChildTables.size() == 0 && m_ChildProps.size() == 0;
	}

	void insert_table( string&& name, unique_ptr< NetvarTable >&& pTable )
	{
		m_ChildTables.emplace( name, std::move( pTable ) );
	}

	void insert_prop( string&& name, uint32_t offset )
	{
		m_ChildProps.emplace( name, offset );
	}
};

class NetvarDatabase
{
public:
	TableMap m_Tables;

	void insert( string&& name, unique_ptr< NetvarTable >&& pTable )
	{
		m_Tables.emplace( name, std::move( pTable ) );
	}

	Iter find( const string& key )
	{
		return m_Tables.find( key );
	}

	Iter begin()
	{
		return m_Tables.begin();
	}

	Iter end()
	{
		return m_Tables.end();
	}
};

#pragma endregion

//------------------------------------------------------------
// Netvar Manager
//------------------------------------------------------------
CNetvarManager* CNetvarManager::instance = nullptr;

CNetvarManager::CNetvarManager()
{
}

CNetvarManager::~CNetvarManager()
{
}

void CNetvarManager::CreateDatabase()
{
	m_pDatabase = make_unique< NetvarDatabase >();
	auto pClient = Interfaces.pClient;

	if( pClient )
	{
		for( auto pClass = pClient->GetAllClasses(); pClass; pClass = pClass->m_pNext )
		{
			if( pClass->m_pRecvTable )
			{
				//Insert new entry on the database
				m_pDatabase->insert(
					pClass->m_pRecvTable->m_pNetTableName,
					InternalLoadTable( pClass->m_pRecvTable, 0 ) );
				m_tableCount++;
			}
		}
	}
}

void CNetvarManager::Dump( std::ostream& output )
{
	for( auto& entry : *m_pDatabase )
	{
		auto& pTable = entry.second;
		if( pTable->is_empty() )
			continue;
		output << entry.first << std::endl;
		Dump( output, *pTable, 1 );
		output << "==============================================================" << std::endl;
	}
}

void CNetvarManager::Dump( const std::string& file )
{
	std::ofstream output( file );
	Dump( output );
}

//------------------------------------------------------------
// Internal methods below. This is where the real work is done
//------------------------------------------------------------
unique_ptr< NetvarTable > CNetvarManager::InternalLoadTable( RecvTable* pRecvTable, uint32_t offset )
{
	auto pTable = make_unique< NetvarTable >();
	pTable->m_uOffset = offset;

	for( auto i = 0; i < pRecvTable->m_nProps; ++i )
	{
		auto pProp = &pRecvTable->m_pProps[ i ];

		//Skip trash array items
		if( !pProp || isdigit( pProp->m_pVarName[ 0 ] ) )
			continue;
		//We dont care about the base class
		if( strcmp( pProp->m_pVarName, "baseclass" ) == 0 )
			continue;

		//If this prop is a table
		if( pProp->m_RecvType == SendPropType::DPT_DataTable && //If it is a table AND
			pProp->m_pDataTable != nullptr && //The DataTable isnt null AND
			pProp->m_pDataTable->m_pNetTableName[ 0 ] == 'D' )
		{ //The Table name starts with D (this is because there are some shitty nested 
			//tables that we want to skip, and those dont start with D)

			//Load the table pointed by pProp->m_pDataTable and insert it
			pTable->insert_table( pProp->m_pVarName, InternalLoadTable( pProp->m_pDataTable, pProp->m_Offset ) );
		}
		else
		{
			pTable->insert_prop( pProp->m_pVarName, pProp->m_Offset );
		}
		m_netvarCount++;
	}
	return pTable;
}

void CNetvarManager::Dump( std::ostream& output, NetvarTable& table, int level )
{
	char line[512] = "";
	char fmt[512] = "";

	sprintf( fmt, "%%-%ds: 0x%%08X\n", 50 - level * 4 );

	for( auto& prop : table.m_ChildProps )
	{
		for( int i = 0; i < level; i++ )
		{
			if( i != level - 1 )
			{
				output << "    ";
			}
			else
			{
				output << "|___";
			}
		}
		sprintf( line, fmt, prop.first.c_str(), prop.second + table.m_uOffset );
		output << line;
	}
	for( auto& child : table.m_ChildTables )
	{
		for( int i = 0; i < level; i++ )
		{
			if( i != level - 1 )
			{
				output << "    ";
			}
			else
			{
				output << "|___";
			}
		}
		sprintf( line, fmt, child.first.c_str(), child.second->m_uOffset );
		output << line;
		Dump( output, *child.second, level + 1 );
	}
}

uint32_t CNetvarManager::GetOffset( const std::string& szTableName, const std::initializer_list< std::string >& props )
{
	auto table = m_pDatabase->find( szTableName );
	if( table == m_pDatabase->end() )
		return -1;

	int tableOffset = table->second->m_uOffset;
	if( props.size() == 0 )
		return tableOffset;

	int totalOffset = tableOffset;

	NetvarTable* curTable = table->second.get();

	for( auto i = 0; i < props.size(); i++ )
	{
		std::string propName = *( props.begin() + i );

		if( i + 1 < props.size() )
		{//This index is not the last one
			auto childTable = curTable->m_ChildTables.find( propName );
			if( childTable == curTable->m_ChildTables.end() )
			{
				throw std::runtime_error( "Prop not found" );
			}
			totalOffset += childTable->second->m_uOffset;

			curTable = childTable->second.get();
		}
		else
		{ //Last index, retrieve prop instead of table
			auto childProp = curTable->m_ChildProps.find( propName );
			if( childProp == curTable->m_ChildProps.end() )
			{
				throw std::runtime_error( "Prop not found" );
			}

			totalOffset += childProp->second;
		}
	}

	return totalOffset;
}

void UTIL_TraceLine( Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, const IHandleEntity* ignore, int collisionGroup, trace_t* ptr )
{
	Ray_t ray;
	ray.Init( vecAbsStart, vecAbsEnd );
	CTraceFilter traceFilter;
	traceFilter.pSkip = ( void* )ignore;
	Interfaces.pTrace->TraceRay( ray, mask, &traceFilter, ptr );
}

float DistanceToRay( const Vector& pos, const Vector& rayStart, const Vector& rayEnd, float* along = nullptr, Vector* pointOnRay = nullptr )
{
	Vector to = pos - rayStart;
	Vector dir = rayEnd - rayStart;
	float length = dir.NormalizeInPlace();

	float rangeAlong = g_Math.DotProduct( dir, to );
	if( along )
	{
		*along = rangeAlong;
	}

	float range;

	if( rangeAlong < 0.0f )
	{
		// off start point
		range = -( pos - rayStart ).Length();

		if( pointOnRay )
		{
			*pointOnRay = rayStart;
		}
	}
	else if( rangeAlong > length )
	{
		// off end point
		range = -( pos - rayEnd ).Length();

		if( pointOnRay )
		{
			*pointOnRay = rayEnd;
		}
	}
	else // within ray bounds
	{
		Vector onRay = rayStart + ( dir.operator*( rangeAlong ) );
		range = ( pos - onRay ).Length();

		if( pointOnRay )
		{
			*pointOnRay = onRay;
		}
	}

	return range;
}

void UTIL_ClipTraceToPlayers( Vector& vecAbsStart, Vector& vecAbsEnd, unsigned int mask, ITraceFilter* filter, trace_t* tr )
{
	trace_t playerTrace;
	Ray_t ray;
	float smallestFraction = tr->fraction;
	const float maxRange = 60.0f;

	ray.Init( vecAbsStart, vecAbsEnd );

	for( int k = 1; k <= Interfaces.pGlobalVars->maxClients; ++k )
	{
		CBaseEntity* player = Interfaces.pEntList->GetClientEntity( k );

		if( !player || !player->isAlive() )
			continue;

		if( player->IsDormant() )
			continue;

		if( filter && filter->ShouldHitEntity( player, mask ) == false )
			continue;

		float range = DistanceToRay( player->WorldSpaceCenter(), vecAbsStart, vecAbsEnd );
		if( range < 0.0f || range > maxRange )
			continue;

		Interfaces.pTrace->ClipRayToEntity( ray, mask | CONTENTS_HITBOX, player, &playerTrace );
		if( playerTrace.fraction < smallestFraction )
		{
			// we shortened the ray - save off the trace
			*tr = playerTrace;
			smallestFraction = playerTrace.fraction;
		}
	}
}

bool TraceToExit(Vector& end, trace_t& tr, Vector start, Vector vEnd, trace_t* trace)
{
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static DWORD TraceToExit = Utils.PatternSearch("client.dll", (BYTE*)"\x55\x8B\xEC\x83\xEC\x30\xF3\x0F\x10\x75", "xxxxxxxxxx", NULL, NULL);

	if (!TraceToExit)
		return false;

	float start_y = start.y, start_z = start.z, start_x = start.x, dir_y = vEnd.y, dir_x = vEnd.x, dir_z = vEnd.z;

	_asm
	{
		push trace
		push dir_z
		push dir_y
		push dir_x
		push start_z
		push start_y
		push start_x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}

}

CBaseCombatWeapon* CBaseEntity::GetActiveBaseCombatWeapon()
{
	static int iOffset = Netvar("DT_BaseCombatCharacter", "m_hActiveWeapon");
	ULONG pWeepEhandle = *( PULONG )( ( DWORD )this + iOffset );
	return ( CBaseCombatWeapon* )( Interfaces.pEntList->GetClientEntityFromHandle( ( HANDLE )pWeepEhandle ) );
}

std::vector< CBaseCombatWeapon* > CBaseEntity::GetWeapons()
{
	int* m_hMyWeapons = reinterpret_cast< int* >( ( DWORD )this + 0x2DE8 );
	std::vector< CBaseCombatWeapon* > list = {};
	for( auto i = 0; i < 64; ++i )
	{
		auto Weapon = Interfaces.pEntList->GetClientEntityFromHandle( ( HANDLE )m_hMyWeapons[ i ] );
		if( Weapon )
		{
			list.push_back( ( CBaseCombatWeapon* )Weapon );
		}
	}
	return list;
}

const char* ConVar::GetName()
{
	typedef char*(__thiscall* GetNameFn)( void* );
	return getvfunc< GetNameFn >( this, ConVar_GetName )( this );
}

const char* ConVar::GetBaseName()
{
	typedef char*(__thiscall* GetNameFn)( void* );
	return getvfunc< GetNameFn >( this, ConVar_GetBaseName )( this );
}

float ConVar::GetFloat()
{
	typedef float (__thiscall* SetValueFn)( void* );
	return getvfunc< SetValueFn >( this, ConVar_GetFloat )( this );
}

void ConVar::SetValue( const char* value )
{
	typedef void (__thiscall* SetValueFn)( void*, const char* );
	return getvfunc< SetValueFn >( this, ConVar_SetString )( this, value );
}

void ConVar::SetValue( float value )
{
	typedef void (__thiscall* SetValueFn)( void*, float );
	return getvfunc< SetValueFn >( this, ConVar_SetFloat )( this, value );
}

void ConVar::SetValue( int value )
{
	typedef void (__thiscall* SetValueFn)( void*, int );
	return getvfunc< SetValueFn >( this, ConVar_SetInt )( this, value );
}
