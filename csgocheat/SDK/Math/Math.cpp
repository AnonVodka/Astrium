#include "../../stdafx.h"
#define M_PI	3.14159265358979323846f
CMath g_Math;

VOID CMath::sinCos( float radians, PFLOAT sine, PFLOAT cosine )
{
	__asm
	{
		fld dword ptr[radians]
		fsincos
		mov edx, dword ptr[cosine]
		mov eax, dword ptr[sine]
		fstp dword ptr[edx]
		fstp dword ptr[eax]
	}
}

void CMath::angleVectors( const Vector& angles, Vector& forward )
{
	Assert(s_bMathlibInitialized);
	Assert(forward);

	float sp, sy, cp, cy;

	sy = sin( DEG2RAD(angles[1]) );
	cy = cos( DEG2RAD(angles[1]) );

	sp = sin( DEG2RAD(angles[0]) );
	cp = cos( DEG2RAD(angles[0]) );

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

float CMath::sseSqrt( float x )
{
	float root = 0.0f;

	__asm
	{
		sqrtss xmm0, x
		movss root, xmm0
	}

	return root;
}

Vector CMath::RotatePoint( Vector p, Vector c, float ang )
{
	float angleInRadians = ang * ( M_PI / 180.f );
	float cosTheta = cos( angleInRadians );
	float sinTheta = sin( angleInRadians );
	return Vector(
		( cosTheta * ( p.x - c.x ) -
			sinTheta * ( p.y - c.y ) + c.x ),
		( sinTheta * ( p.x - c.x ) +
			cosTheta * ( p.y - c.y ) + c.y ),
		0 );
}


void CMath::vectorAngles( float* forward, float* angles )
{
	if( forward[ 1 ] == 0.0f && forward[ 0 ] == 0.0f )
	{
		angles[ 0 ] = ( forward[ 2 ] > 0.0f ) ? 270.0f : 90.0f;
		angles[ 1 ] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt( square(forward[0]) + square(forward[1]) );

		angles[ 0 ] = RAD2DEG(atan2f(-forward[2], len2d));
		angles[ 1 ] = RAD2DEG(atan2f(forward[1], forward[0]));

		if( angles[ 0 ] < 0.0f )
			angles[ 0 ] += 360.0f;
		if( angles[ 1 ] < 0.0f )
			angles[ 1 ] += 360.0f;
	}
}

void CMath::vectorAnglesVec( Vector forward, Vector& angles )
{
	if( forward[ 1 ] == 0.0f && forward[ 0 ] == 0.0f )
	{
		angles[ 0 ] = ( forward[ 2 ] > 0.0f ) ? 270.0f : 90.0f;
		angles[ 1 ] = 0.0f;
	}
	else
	{
		float len2d = sseSqrt( square(forward[0]) + square(forward[1]) );

		angles[ 0 ] = RAD2DEG(atan2f(-forward[2], len2d));
		angles[ 1 ] = RAD2DEG(atan2f(forward[1], forward[0]));

		if( angles[ 0 ] < 0.0f )
			angles[ 0 ] += 360.0f;
		if( angles[ 1 ] < 0.0f )
			angles[ 1 ] += 360.0f;
	}
}

void CMath::VectorAngles3D( Vector& vecForward, Vector& vecAngles )
{
	Vector vecView;
	if( vecForward[ 1 ] == 0.f && vecForward[ 0 ] == 0.f )
	{
		vecView[ 0 ] = 0.f;
		vecView[ 1 ] = 0.f;
	}
	else
	{
		vecView[ 1 ] = atan2( vecForward[ 1 ], vecForward[ 0 ] ) * 180.f / M_PI;

		if( vecView[ 1 ] < 0.f )
			vecView[ 1 ] += 360;

		vecView[ 2 ] = sqrt( vecForward[ 0 ] * vecForward[ 0 ] + vecForward[ 1 ] * vecForward[ 1 ] );

		vecView[ 0 ] = atan2( vecForward[ 2 ], vecView[ 2 ] ) * 180.f / M_PI;
	}

	vecAngles[ 0 ] = -vecView[ 0 ];
	vecAngles[ 1 ] = vecView[ 1 ];
}

float deg2rad( float deg )
{
	return ( deg * M_PI / 180 );
}

FORCEINLINE float CMath::DotProduct( const Vector& a, const Vector& b )
{
	return ( a.x * b.x + a.y * b.y + a.z * b.z );
}

void CMath::AngleMatrix( Vector& angles, matrix3x4_t& matrix )
{
	float angle;
	float sr, sp, sy, cr, cp, cy;

	angle = angles.x * ( 6.283185f / 360 );
	sp = sin( angle );
	cp = cos( angle );

	angle = angles.y * ( 6.283185f / 360 );
	sy = sin( angle );
	cy = cos( angle );

	angle = angles.z * ( 6.283185f / 360 );
	sr = sin( angle );
	cr = cos( angle );

	// matrix = (YAW * PITCH) * ROLL
	matrix[ 0 ][ 0 ] = cp * cy;
	matrix[ 1 ][ 0 ] = cp * sy;

	matrix[ 2 ][ 0 ] = -sp;
	matrix[ 0 ][ 1 ] = sr * sp * cy + cr * -sy;

	matrix[ 1 ][ 1 ] = sr * sp * sy + cr * cy;
	matrix[ 2 ][ 1 ] = sr * cp;

	matrix[ 0 ][ 2 ] = ( cr * sp * cy + -sr * -sy );
	matrix[ 1 ][ 2 ] = ( cr * sp * sy + -sr * cy );

	matrix[ 2 ][ 2 ] = cr * cp;

	matrix[ 0 ][ 3 ] = 0.0;
	matrix[ 1 ][ 3 ] = 0.0;
	matrix[ 2 ][ 3 ] = 0.0;
}

void CMath::VectorTransform( const Vector in1, matrix3x4_t in2, Vector& out )
{
	out[ 0 ] = DotProduct( in1, Vector( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, Vector( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, Vector( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

void CMath::VectorTransform2( const Vector in1, float in2[3][4], Vector& out )
{
	out[ 0 ] = DotProduct( in1, Vector( in2[ 0 ][ 0 ], in2[ 0 ][ 1 ], in2[ 0 ][ 2 ] ) ) + in2[ 0 ][ 3 ];
	out[ 1 ] = DotProduct( in1, Vector( in2[ 1 ][ 0 ], in2[ 1 ][ 1 ], in2[ 1 ][ 2 ] ) ) + in2[ 1 ][ 3 ];
	out[ 2 ] = DotProduct( in1, Vector( in2[ 2 ][ 0 ], in2[ 2 ][ 1 ], in2[ 2 ][ 2 ] ) ) + in2[ 2 ][ 3 ];
}

void CMath::Normalize( Vector& vIn, Vector& vOut )
{
	float flLen = vIn.Length();
	if( flLen == 0 )
	{
		vOut.Init( 0, 0, 1 );
		return;
	}
	flLen = 1 / flLen;
	vOut.Init( vIn.x * flLen, vIn.y * flLen, vIn.z * flLen );
}

bool CMath::WorldToScreen( Vector& vecOrigin, Vector& vecScreen )
{
	return false;
	//return (g_pDebugOverlay->ScreenPosition(vecOrigin, vecScreen) != 1);
}

CMath* CMath::Singleton( void )
{
	static CMath* pMath = nullptr;

	if( !pMath )
		pMath = new CMath();

	return pMath;
}


VOID FORCEINLINE __SPL__( VOID )
{
}
