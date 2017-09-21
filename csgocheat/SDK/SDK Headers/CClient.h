#pragma once
#include "stdafx.h"

class iClientClass
{
public:
	const char* iClientClass::GetName( void )
	{
		return *( char** )( this + 0x8 );
	}

	RecvTable* iClientClass::GetTable()
	{
		return *( RecvTable** )( this + 0xC );
	}

	iClientClass* iClientClass::NextClass()
	{
		return *( iClientClass** )( this + 0x10 );
	}

	int iClientClass::GetClassID( void )
	{
		return *( int* )( this + 0x14 );
	}

	iClientClass* iClientClass::GetAllClasses( void )
	{
		typedef iClientClass* (__thiscall* OriginalFn)( PVOID );
		return getvfunc< OriginalFn >( this, 8 )( this );
	}
};

class ClientClassIDS
{
public:
	static const int CTestTraceline = 194;
	static const int CTEWorldDecal = 195;
	static const int CTESpriteSpray = 192;
	static const int CTESprite = 191;
	static const int CTESparks = 190;
	static const int CTESmoke = 189;
	static const int CTEShowLine = 187;
	static const int CTEProjectedDecal = 184;
	static const int CFEPlayerDecal = 61;
	static const int CTEPlayerDecal = 183;
	static const int CTEPhysicsProp = 180;
	static const int CTEParticleSystem = 179;
	static const int CTEMuzzleFlash = 178;
	static const int CTELargeFunnel = 176;
	static const int CTEKillPlayerAttachments = 175;
	static const int CTEImpact = 174;
	static const int CTEGlowSprite = 173;
	static const int CTEShatterSurface = 186;
	static const int CTEFootprintDecal = 170;
	static const int CTEFizz = 169;
	static const int CTEExplosion = 167;
	static const int CTEEnergySplash = 166;
	static const int CTEEffectDispatch = 165;
	static const int CTEDynamicLight = 164;
	static const int CTEDecal = 162;
	static const int CTEClientProjectile = 161;
	static const int CTEBubbleTrail = 160;
	static const int CTEBubbles = 159;
	static const int CTEBSPDecal = 158;
	static const int CTEBreakModel = 157;
	static const int CTEBloodStream = 156;
	static const int CTEBloodSprite = 155;
	static const int CTEBeamSpline = 154;
	static const int CTEBeamRingPoint = 153;
	static const int CTEBeamRing = 152;
	static const int CTEBeamPoints = 151;
	static const int CTEBeamLaser = 150;
	static const int CTEBeamFollow = 149;
	static const int CTEBeamEnts = 148;
	static const int CTEBeamEntPoint = 147;
	static const int CTEBaseBeam = 146;
	static const int CTEArmorRicochet = 145;
	static const int CTEMetalSparks = 177;
	static const int CSteamJet = 140;
	static const int CSmokeStack = 133;
	static const int DustTrail = 244;
	static const int CFireTrail = 64;
	static const int SporeTrail = 250;
	static const int SporeExplosion = 249;
	static const int RocketTrail = 247;
	static const int SmokeTrail = 248;
	static const int CPropVehicleDriveable = 120;
	static const int ParticleSmokeGrenade = 246;
	static const int CParticleFire = 99;
	static const int MovieExplosion = 245;
	static const int CTEGaussExplosion = 172;
	static const int CEnvQuadraticBeam = 56;
	static const int CEmbers = 46;
	static const int CEnvWind = 60;
	static const int CPrecipitation = 114;
	static const int CPrecipitationBlocker = 115;
	static const int CBaseTempEntity = 18;
	static const int NextBotCombatCharacter = 0;
	static const int CEconWearable = 45;
	static const int CBaseAttributableItem = 4;
	static const int CEconEntity = 44;
	static const int CWeaponXM1014 = 242;
	static const int CWeaponTaser = 237;
	static const int CSmokeGrenade = 131;
	static const int CWeaponSG552 = 234;
	static const int CSensorGrenade = 127;
	static const int CWeaponSawedoff = 230;
	static const int CWeaponNOVA = 226;
	static const int CIncendiaryGrenade = 87;
	static const int CMolotovGrenade = 96;
	static const int CWeaponM3 = 218;
	static const int CKnifeGG = 93;
	static const int CKnife = 92;
	static const int CHEGrenade = 84;
	static const int CFlashbang = 66;
	static const int CWeaponElite = 209;
	static const int CDecoyGrenade = 40;
	static const int CDEagle = 39;
	static const int CWeaponUSP = 241;
	static const int CWeaponM249 = 217;
	static const int CWeaponUMP45 = 240;
	static const int CWeaponTMP = 239;
	static const int CWeaponTec9 = 238;
	static const int CWeaponSSG08 = 236;
	static const int CWeaponSG556 = 235;
	static const int CWeaponSG550 = 233;
	static const int CWeaponScout = 232;
	static const int CWeaponSCAR20 = 231;
	static const int CSCAR17 = 125;
	static const int CWeaponP90 = 229;
	static const int CWeaponP250 = 228;
	static const int CWeaponP228 = 227;
	static const int CWeaponNegev = 225;
	static const int CWeaponMP9 = 224;
	static const int CWeaponMP7 = 223;
	static const int CWeaponMP5Navy = 222;
	static const int CWeaponMag7 = 221;
	static const int CWeaponMAC10 = 220;
	static const int CWeaponM4A1 = 219;
	static const int CWeaponHKP2000 = 216;
	static const int CWeaponGlock = 215;
	static const int CWeaponGalilAR = 214;
	static const int CWeaponGalil = 213;
	static const int CWeaponG3SG1 = 212;
	static const int CWeaponFiveSeven = 211;
	static const int CWeaponFamas = 210;
	static const int CWeaponBizon = 205;
	static const int CWeaponAWP = 203;
	static const int CWeaponAug = 202;
	static const int CAK47 = 1;
	static const int CWeaponCSBaseGun = 207;
	static const int CWeaponCSBase = 206;
	static const int CC4 = 29;
	static const int CWeaponBaseItem = 204;
	static const int CBaseCSGrenade = 8;
	static const int CSmokeGrenadeProjectile = 132;
	static const int CSensorGrenadeProjectile = 128;
	static const int CMolotovProjectile = 97;
	static const int CItem_Healthshot = 91;
	static const int CDecoyProjectile = 41;
	static const int CFireCrackerBlast = 62;
	static const int CInferno = 88;
	static const int CChicken = 31;
	static const int CFootstepControl = 68;
	static const int CCSGameRulesProxy = 34;
	static const int CWeaponCubemap = 0;
	static const int CWeaponCycler = 208;
	static const int CTEPlantBomb = 181;
	static const int CTEFireBullets = 168;
	static const int CTERadioIcon = 185;
	static const int CPlantedC4 = 107;
	static const int CCSTeam = 38;
	static const int CCSPlayerResource = 36;
	static const int CCSPlayer = 35;
	static const int CCSRagdoll = 37;
	static const int CTEPlayerAnimEvent = 182;
	static const int CHostage = 85;
	static const int CHostageCarriableProp = 86;
	static const int CBaseCSGrenadeProjectile = 9;
	static const int CHandleTest = 83;
	static const int CTeamplayRoundBasedRulesProxy = 144;
	static const int CSpriteTrail = 138;
	static const int CSpriteOriented = 137;
	static const int CSprite = 136;
	static const int CRagdollPropAttached = 123;
	static const int CRagdollProp = 122;
	static const int CPredictedViewModel = 116;
	static const int CPoseController = 112;
	static const int CGameRulesProxy = 82;
	static const int CInfoLadderDismount = 89;
	static const int CFuncLadder = 74;
	static const int CTEFoundryHelpers = 171;
	static const int CEnvDetailController = 52;
	static const int CWorld = 243;
	static const int CWaterLODControl = 201;
	static const int CWaterBullet = 200;
	static const int CVoteController = 199;
	static const int CVGuiScreen = 198;
	static const int CPropJeep = 119;
	static const int CPropVehicleChoreoGeneric = 0;
	static const int CTriggerSoundOperator = 197;
	static const int CBaseVPhysicsTrigger = 22;
	static const int CTriggerPlayerMovement = 196;
	static const int CBaseTrigger = 20;
	static const int CTest_ProxyToggle_Networkable = 193;
	static const int CTesla = 188;
	static const int CBaseTeamObjectiveResource = 17;
	static const int CTeam = 143;
	static const int CSunlightShadowControl = 142;
	static const int CSun = 141;
	static const int CParticlePerformanceMonitor = 100;
	static const int CSpotlightEnd = 135;
	static const int CSpatialEntity = 134;
	static const int CSlideshowDisplay = 130;
	static const int CShadowControl = 129;
	static const int CSceneEntity = 126;
	static const int CRopeKeyframe = 124;
	static const int CRagdollManager = 121;
	static const int CPhysicsPropMultiplayer = 105;
	static const int CPhysBoxMultiplayer = 103;
	static const int CPropDoorRotating = 118;
	static const int CBasePropDoor = 16;
	static const int CDynamicProp = 43;
	static const int CProp_Hallucination = 117;
	static const int CPostProcessController = 113;
	static const int CPointCommentaryNode = 111;
	static const int CPointCamera = 110;
	static const int CPlayerResource = 109;
	static const int CPlasma = 108;
	static const int CPhysMagnet = 106;
	static const int CPhysicsProp = 104;
	static const int CStatueProp = 139;
	static const int CPhysBox = 102;
	static const int CParticleSystem = 101;
	static const int CMovieDisplay = 98;
	static const int CMaterialModifyControl = 95;
	static const int CLightGlow = 94;
	static const int CInfoOverlayAccessor = 90;
	static const int CFuncTrackTrain = 81;
	static const int CFuncSmokeVolume = 80;
	static const int CFuncRotating = 79;
	static const int CFuncReflectiveGlass = 78;
	static const int CFuncOccluder = 77;
	static const int CFuncMoveLinear = 76;
	static const int CFuncMonitor = 75;
	static const int CFunc_LOD = 70;
	static const int CTEDust = 163;
	static const int CFunc_Dust = 69;
	static const int CFuncConveyor = 73;
	static const int CFuncBrush = 72;
	static const int CBreakableSurface = 28;
	static const int CFuncAreaPortalWindow = 71;
	static const int CFish = 65;
	static const int CFireSmoke = 63;
	static const int CEnvTonemapController = 59;
	static const int CEnvScreenEffect = 57;
	static const int CEnvScreenOverlay = 58;
	static const int CEnvProjectedTexture = 55;
	static const int CEnvParticleScript = 54;
	static const int CFogController = 67;
	static const int CEnvDOFController = 53;
	static const int CCascadeLight = 30;
	static const int CEnvAmbientLight = 51;
	static const int CEntityParticleTrail = 50;
	static const int CEntityFreezing = 49;
	static const int CEntityFlame = 48;
	static const int CEntityDissolve = 47;
	static const int CDynamicLight = 42;
	static const int CColorCorrectionVolume = 33;
	static const int CColorCorrection = 32;
	static const int CBreakableProp = 27;
	static const int CBeamSpotlight = 25;
	static const int CBaseButton = 5;
	static const int CBaseToggle = 19;
	static const int CBasePlayer = 15;
	static const int CBaseFlex = 12;
	static const int CBaseEntity = 11;
	static const int CBaseDoor = 10;
	static const int CBaseCombatCharacter = 6;
	static const int CBaseAnimatingOverlay = 3;
	static const int CBoneFollower = 26;
	static const int CBaseAnimating = 2;
	static const int CAI_BaseNPC = 0;
	static const int CBeam = 24;
	static const int CBaseViewModel = 21;
	static const int CBaseParticleEntity = 14;
	static const int CBaseGrenade = 13;
	static const int CBaseCombatWeapon = 7;
	static const int CBaseWeaponWorldModel = 23;
};

class IClientNetworkable;

typedef IClientNetworkable* (*CreateClientClassFn)( int entnum, int serialNum );

typedef IClientNetworkable* (*CreateEventFn)();

class ClientClass
{
public:
	CreateClientClassFn m_pCreateFn;
	CreateEventFn m_pCreateEventFn;
	char* m_pNetworkName;
	RecvTable* m_pRecvTable;
	ClientClass* m_pNext;
	int m_ClassID;
};

class HLCLient
{
public:
	ClientClass* GetAllClasses( VOID )
	{
		typedef ClientClass* (__thiscall* OriginalFn)( PVOID );
		return getvfunc< OriginalFn >( this, 8 )( this );
	}

	int GetScreenWidth( VOID )
	{
		typedef int (__thiscall* OriginalFn)( PVOID );
		return getvfunc< OriginalFn >( this, 63 )( this );
	}

	int GetScreenHeight( VOID )
	{
		typedef int (__thiscall* OriginalFn)( PVOID );
		return getvfunc< OriginalFn >( this, 64 )( this );
	}

	void IN_DeactivateMouse( VOID )
	{
		typedef void (__thiscall* OriginalFn)( PVOID );
		getvfunc< OriginalFn >( this, 16 )( this );
	}

	void IN_IsKeyDown( char const* key, bool& down )
	{
		typedef void (__thiscall* OriginalFn)( PVOID, char const*, bool& );
		getvfunc< OriginalFn >( this, 19 )( this, key, down );
	}
};
