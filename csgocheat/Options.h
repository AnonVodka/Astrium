#pragma once

struct ColorP
{
public:
	const char* Name;
	float* Ccolor;

	ColorP(const char* name, float* color)
	{
		this->Name = name;
		this->Ccolor = color;
	}
};

class cOptions
{
public:
	struct
	{
		struct
		{
			bool bAimbotEnable;
			bool bAutoShoot;
			bool bAutoScope;
			bool bAutoRevolver;
			bool bSilentAim;
			bool bAutoPistol;
			int  iHitbox;
			int  iSelection;
		}Aimbot;
		struct
		{
			bool bVelocityPrediction;
			int	 iMultibox;
			bool bMultipoint;
			int  iPointscale;
			int  iHitchance;
			int  iMinDmg;
			bool bAcceptKillDmg;
			bool bNoRecoil;
		}Accuracy;
		struct
		{
			int  iAntiAimResolver;
			int  iAccuracyBoost;
			int  iPreferBaim;
			bool bPositionAdj;
			bool bBruteforce;
			bool bResolver;

		}HvH;	
		struct
		{
			struct 
			{
				bool bEnableAntiAim;
				bool bAtTargets;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Stand;
			struct
			{
				bool bEnableAntiAim;
				bool bAtTargets;
				bool bMemeWalk;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Move;
			struct
			{
				bool bEnableEdge;

				int  iPitch;
				int  iYaw;
				int  iYawAdd;
				int  iFakeYaw;
				int  iFakeYawAdd;
			}Edge;
			struct
			{
				bool bFakeWalk;
				int  iFakeWalkKey;
			}Misc;
		}AntiAim;

	}Ragebot;
	struct
	{
		struct
		{
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bAutoPistol;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Pistols;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Rifles;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Snipers;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Shotguns;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Smgs;
			struct
			{
				bool bEnableAimbot;
				bool bSilentAim;
				bool bOnKey;
				int  iKey;
				float  iAimbotFov;
				float  flAimbotRecoil;
				int  iAimbotHitbox;
			}Heavy;

		}Aimbot;
		struct
		{
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
			//	int  iTriggerDelay = 10;
				bool bTriggerRecoil;
				bool bAutoRevolver;
				bool bRevolverSecondary;
				bool bAutoPistol;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Pistols;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Rifles;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
				bool bScoped;
			}Snipers;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Shotguns;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Smgs;
			struct
			{
				bool bEnableTrigger;
				bool bTriggerOnKey;
				int  iTriggerKey;
				//int  iTriggerDelay = 10;
				bool bTriggerRecoil;

				bool bTriggerFullBody;
				bool bTriggerHead;
				bool bTriggerChest;
				bool bTriggerStomach;
				bool bTriggerArms;
				bool bTriggerLegs;
			}Heavy;

		}Trigger;
	}Legitbot;
	struct
	{
		struct
		{
			struct
			{
				bool bBox;
				bool bHealthbar;
				bool bHealthText;
				bool bArmorBar;
				int	 iBarPos;
				bool bSkeleton;
				bool bAimlines;
				bool bPitch;
				bool bYaw;
			}EspBox;
			struct
			{
				bool bWeapons;
				bool bAmmo;
				bool bName;
				bool bIsScoped;
				bool bIsFlashed;
			}EspMisc;
			struct
			{
				bool bDroppedWeapons;
				bool bEnemyOnly;
				bool bXQZ;
				bool bC4;
				bool bHostage;
			}EspFilter;
		}Esp;
		struct
		{
			bool bInfoBox;
			bool bInfoLby;
			bool bInfoVelocity;
			bool bInfoAngles;
			bool bPlayerBox;
		}Infobox;
		struct
		{
			bool bSpecList;
			bool bCrosshair;
			bool bNormalCrosshair;
			bool bRecoilCrosshair;
			bool bSpreadCrosshair;
			bool bNoVisualRecoil;
			bool bRankReveal;
			bool bThirdperson;
			int  iThirdPerson;
			int  iThirdPersonKey;
			float flThirdPersonRange;
			bool bScopeRemover;
			bool bEngineRadar;
			bool bWatermark = true;
			bool bTime;
			bool bHitMarker;
			int	 iHitsound;
			int  iKillsound;
		}VisualsMisc;
		struct 
		{
			bool bAsusWalls;
			float flAsusFactor = 100;
			bool bNightMode;		
			bool bNoFlash;
			bool bNoSmoke;
			int	 iSkyboxChanger;
			bool bBulletTracer;
			float flTracerLenght = 1;

		}VisualsWorlds;
		struct
		{
			bool bPlayers;
			bool bEnemyOnly;
			bool bWireframe;
			bool bFlat;
			bool bThroughWalls;
			bool bTransparent;
			bool bArms;
			bool bArmsWireframe;
			bool bArmsFlat;
			bool bArmsThroughWalls;
			bool bArmsTransparent;
		}Chams;
		struct 
		{
			bool bEnabled;
			bool bEnemyOnly;
			bool bPlayers;
			bool bChickens;
			bool bC4Carrier;
			bool bPlantedC4;
			bool bDefuseKits;
			bool bWeapons;
		}Glow;
	}Visuals;
	struct
	{
		struct
		{
			int  iFakeLag;
			bool bInAirOnly;
			int  iFakeLagFactor;
			//bool bAutoAccpet;
			bool bClanTag;
			bool bCorruption;
			int  iClanTagSelection;
			bool bClanTagAnimation;
			bool bFreeCam;
			int  iFreeCamKey;
			float flFreeCamSpeed = 5;
		}Misc1;
		struct
		{
			bool bAntiUntrusted = true;
			bool bChatSpam;
			int  iNameSpam;
			bool bKnifeBot;
			bool bBlockBot;
			int  iBlockBotKey;
			bool bEnableFov;
			float flFovValue = 90;
			float	flViewModelValue;
		}Misc2;
		struct
		{
			bool bAutoJump;
			bool bAutoStrafe;
			bool bAirStuck;
			bool bSlowmotion;
			bool bZStrafe;
			bool bCircleStrafer;
			bool bWalkBot;
			bool bBunnyhop;
			float flDistance = 0;
			int  iTurn = 0;
			int  iAirStuck;
			int  iAirStuckKey;
			int  iSlowMotionKey;
			int  iZStrafeKey;
			int  iCircleStraferMode;
			int  iCircleStraferKey;
			int  iAutoStrafeMode;

		}Movement;
	}Misc;
	struct 
	{
		float espVisT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisT[3] = { 0.7f, 0.1f, 0.1f };
		float espVisCT[3] = { 0.9f, 0.2f, 0.2f };
		float espInvisCT[3] = { 0.7f, 0.1f, 0.1f };

		float chamsPlyrTVis[3] = { 0.9f,0.4f,0.f };
		float chamsPlyrTInvis[3] = { 0.9f, 0.0f, 0.f };
		float chamsPlyrCTVis[3] = { 0.f,0.4f,0.9f };
		float chamsPlyrCTInvis[3] = { 0.f,0.0f,0.9f };

		float chamsHandsVis[3] = { 0.4f, 0.2f, 1.f };
		float chamsHandsInvis[3] = { 1.f, 0.2f, 0.4f };

		float bullettracer[3] = { 0.9f, 0.2f, 0.2f };
		
	}Col;
	struct
	{
		bool bEnableSkins;
	}Skins;
	struct 
	{
		bool setup = false;
		int current;
	}Config;
};

extern cOptions Options;