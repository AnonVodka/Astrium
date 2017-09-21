class VTHookManager
{
public:
	VTHookManager()
	{
		DWORD oProtection;
		VirtualProtect( reinterpret_cast< void* >( this ), 4, PAGE_READWRITE, &oProtection );
		memset( this, 0, sizeof(VTHookManager) );
		VirtualProtect( reinterpret_cast< void* >( this ), 4, oProtection, &oProtection );
	}

	explicit VTHookManager( PDWORD* ppdwClassBase )
	{
		bInitialize( ppdwClassBase );
	}

	~VTHookManager()
	{
		UnHook();
	}

	bool bInitialize( PDWORD* ppdwClassBase )
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount( *ppdwClassBase );
		m_pdwNewVMT = new DWORD[m_dwVMTSize];
		DWORD oProtection;
		VirtualProtect( reinterpret_cast< void* >( m_pdwNewVMT ), 4, PAGE_READWRITE, &oProtection );
		memcpy( m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD) * m_dwVMTSize );
		VirtualProtect( reinterpret_cast< void* >( m_pdwNewVMT ), 4, oProtection, &oProtection );
		*ppdwClassBase = m_pdwNewVMT;
		return true;
	}

	bool bInitialize( PDWORD** pppdwClassBase )
	{
		return bInitialize( *pppdwClassBase );
	}

	void UnHook() const
	{
		if( m_ppdwClassBase )
		{
			*m_ppdwClassBase = m_pdwOldVMT;
		}
	}

	void ReHook() const
	{
		if( m_ppdwClassBase )
		{
			*m_ppdwClassBase = m_pdwNewVMT;
		}
	}

	int iGetFuncCount() const
	{
		return static_cast< int >( m_dwVMTSize );
	}

	DWORD dwGetMethodAddress( int Index ) const
	{
		if( Index >= 0 && Index <= static_cast< int >( m_dwVMTSize ) && m_pdwOldVMT != nullptr )
		{
			return m_pdwOldVMT[ Index ];
		}
		return NULL;
	}

	PDWORD pdwGetOldVMT() const
	{
		return m_pdwOldVMT;
	}

	DWORD dwHookMethod( DWORD dwNewFunc, unsigned int iIndex ) const
	{
		if( m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0 )
		{
			m_pdwNewVMT[ iIndex ] = dwNewFunc;
			return m_pdwOldVMT[ iIndex ];
		}

		return 0;
	}

	DWORD dwUnHookMethod( unsigned int iIndex ) const
	{
		if( m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0 )
		{
			m_pdwNewVMT[ iIndex ] = m_pdwOldVMT[ iIndex ];
			return m_pdwOldVMT[ iIndex ];
		}

		return NULL;
	}

private:
	static DWORD dwGetVMTCount( PDWORD pdwVMT )
	{
		DWORD dwIndex = 0;

		for( dwIndex = 0; pdwVMT[ dwIndex ]; dwIndex++ )
		{

			if( IsBadCodePtr( reinterpret_cast< FARPROC >( pdwVMT[ dwIndex ] ) ) )
			{
				break;
			}
		}
		return dwIndex;
	}

	PDWORD* m_ppdwClassBase;
	PDWORD m_pdwNewVMT, m_pdwOldVMT;
	DWORD m_dwVMTSize;
};
