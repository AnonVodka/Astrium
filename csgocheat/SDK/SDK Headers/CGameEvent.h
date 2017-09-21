class IGameEvent
{
public:

	const char* GetName()
	{
		return getvfunc< const char*(__thiscall *)( void* ) >( this, 1 )( this );
	}

	int GetInt( const char* szKeyName, int nDefault = 0 )
	{
		return getvfunc< int(__thiscall *)( void*, const char*, int ) >( this, 6 )( this, szKeyName, nDefault );
	}

	const char* GetString( const char* szKeyName )
	{
		return getvfunc< const char*(__thiscall *)( void*, const char*, int ) >( this, 9 )( this, szKeyName, 0 );
	}

	void SetString( const char* szKeyName, const char* szValue )
	{
		return getvfunc< void(__thiscall *)( void*, const char*, const char* ) >( this, 16 )( this, szKeyName, szValue );
	}
};

class IGameEventListener2
{
public:
	virtual ~IGameEventListener2( void )
	{
	};

	// FireEvent is called by EventManager if pEvent just occured
	// KeyValue memory will be freed by manager if not needed anymore
	virtual void FireGameEvent( IGameEvent* pEvent ) = 0;
};

class IGameEventManager2
{
public:
	virtual ~IGameEventManager2( void )
	{
	};
	virtual int LoadEventsFromFile( const char* filename ) = 0;
	virtual void Reset() = 0;
	virtual bool AddListener( IGameEventListener2* listener, const char* name, bool bServerSide ) = 0;
	virtual bool FindListener( IGameEventListener2* listener, const char* name ) = 0;
	virtual void RemoveListener( IGameEventListener2* listener ) = 0;
	virtual void AddListenerGlobal( IGameEventListener2* listener, bool bIsServerSide ) = 0;
	virtual IGameEvent* zzz( const char* name, bool bForce = false, int* pCookie = nullptr ) = 0;
	virtual bool FireEvent( IGameEvent* pEvent, bool bDontBroadcast = false ) = 0;
	virtual bool FireEventClientSide( IGameEvent* pEvent ) = 0;
	virtual IGameEvent* DuplicateEvent( IGameEvent* pEvent ) = 0;
	virtual void FreeEvent( IGameEvent* pEvent ) = 0;
	virtual bool SerializeEvent( IGameEvent* pEvent, bf_write* buf ) = 0;
	virtual IGameEvent* UnserializeEvent( bf_read* buf ) = 0;
	virtual KeyValues* GetEventDataTypes( IGameEvent* pEvent ) = 0;
};
