#pragma once
#include <vector>

template< typename T >
class ConfigItem
{
	std::string category, name;
	T* value;
public:
	ConfigItem(std::string category, std::string name, T* value)
	{
		this->category = category;
		this->name = name;
		this->value = value;
	}
};

template< typename T >
class ConfigValue
{
public:
	ConfigValue(std::string category_, std::string name_, T* value_)
	{
		category = category_;
		name = name_;
		value = value_;
	}

	std::string category, name;
	T* value;
};

class CConfig
{
protected:
	std::vector< ConfigValue< int >* > ints;
	std::vector< ConfigValue< bool >* > bools;
	std::vector< ConfigValue< float >* > floats;
private:
	void SetupValue(int&, int, std::string, std::string);
	void SetupValue(bool&, bool, std::string, std::string);
	void SetupValue(float&, float, std::string, std::string);
public:
	CConfig()
	{
		Setup();
	}

	void Setup();

	void Save();
	void Load();
};

extern CConfig* Config;



//namespace CfgManager
//{
//	const char* config_path = "";
//	void SetupPath()
//	{
//		CreateDirectory("C:\\Astrium", NULL);
//		config_path = "C:\\Astrium\\config.ini";
//	}
//
//	void Read()
//	{
//		CIniReader reader(config_path);
//
//		//Options.Ragebot.Aimbot
//		Options.Ragebot.Aimbot.bAimbotEnable = reader.ReadInteger("Config", "bAimbotEnable", 0);
//		Options.Ragebot.Aimbot.bAutoShoot = reader.ReadInteger("Config", "bAutoShoot", 0);
//		Options.Ragebot.Aimbot.bAutoScope = reader.ReadInteger("Config", "bAutoScope", 0);
//		Options.Ragebot.Aimbot.bAutoRevolver = reader.ReadInteger("Config", "bAutoRevolver", 0);
//		Options.Ragebot.Aimbot.bSilentAim = reader.ReadInteger("Config", "bSilentAim", 0);
//		Options.Ragebot.Aimbot.iHitbox = reader.ReadInteger("Config", "iHitbox", 0);
//		Options.Ragebot.Aimbot.iSelection = reader.ReadInteger("Config", "iSelection", 0);
//		//Options.Ragebot.Accuracy
//		Options.Ragebot.Accuracy.bVelocityPrediction = reader.ReadInteger("Config", "bVelocityPrediction", 0);
//		Options.Ragebot.Accuracy.iMultibox = reader.ReadInteger("Config", "iMultibox", 0);
//		Options.Ragebot.Accuracy.bMultipoint = reader.ReadInteger("Config", "bMultipoint", 0);
//		Options.Ragebot.Accuracy.iPointscale = reader.ReadInteger("Config", "iPointscale", 0);
//		Options.Ragebot.Accuracy.iHitchance = reader.ReadInteger("Config", "iHitchance", 0);
//		Options.Ragebot.Accuracy.iMinDmg = reader.ReadInteger("Config", "iMinDmg", 0);
//		Options.Ragebot.Accuracy.bAcceptKillDmg = reader.ReadInteger("Config", "bAcceptKillDmg", 0);
//		Options.Ragebot.Accuracy.bNoRecoil = reader.ReadInteger("Config", "bNoRecoil", 0);
//		Options.Ragebot.Accuracy.bAutoStop = reader.ReadInteger("Config", "bAutoStop", 0);
//		Options.Ragebot.Accuracy.iAutoStopKey = reader.ReadInteger("Config", "iAutoStopKey", 0);
//		//Options.Ragebot.HvH
//		Options.Ragebot.HvH.bAntiAimCorrection = reader.ReadInteger("Config", "bAntiAimCorrection", 0);
//		Options.Ragebot.HvH.iPreferBaim = reader.ReadInteger("Config", "iPreferBaim", 0);
//		Options.Ragebot.HvH.bPositionAdj = reader.ReadInteger("Config", "bPositionAdj", 0);
//		//Options.Ragebot.AntiAim.AntiAimStand
//		Options.Ragebot.AntiAim.AntiAimStand.bEnable_Stand = reader.ReadInteger("Config", "bEnable_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bAASwitch_Stand = reader.ReadInteger("Config", "bAASwitch_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.iPitch_Stand = reader.ReadInteger("Config", "iPitch_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.iRealYaw_Stand = reader.ReadInteger("Config", "iRealYaw_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.iFakeYaw_Stand = reader.ReadInteger("Config", "iFakeYaw_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bAtTargets_Stand = reader.ReadInteger("Config", "bAtTargets_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bMMSafe_Stand = reader.ReadInteger("Config", "bMMSafe_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bEdgeDetection_Stand = reader.ReadInteger("Config", "bEdgeDetection_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bFakeHitbox_Stand = reader.ReadInteger("Config", "bFakeHitbox_Stand", 0);
//		Options.Ragebot.AntiAim.AntiAimStand.bAntiLby_Stand = reader.ReadInteger("Config", "bAntiLby_Stand", 0);
//		//Options.Ragebot.AntiAim.AntiAimMove
//		//TODO
//		//Options.Ragebot.AntiAim.AntiAimJump
//		//TODO
//		//Options.Ragebot.AntiAim.AntiAimMisc
//		Options.Ragebot.AntiAim.AntiAimMisc.bMemewalk = reader.ReadInteger("Config", "bMemewalk", 0);
//		//Legitbot lass ich erstmal aus :)
//		//Options.Visuals.Esp.General.
//		Options.Visuals.Esp.General.iBox = reader.ReadInteger("Config", "iBox", 0);
//		Options.Visuals.Esp.General.bHealthbar = reader.ReadInteger("Config", "bHealthbar", 0);
//		Options.Visuals.Esp.General.bArmorBar = reader.ReadInteger("Config", "bArmorBar", 0);
//		Options.Visuals.Esp.General.iBarPos = reader.ReadInteger("Config", "iBarPos", 0);
//		Options.Visuals.Esp.General.bSkeleton = reader.ReadInteger("Config", "bSkeleton", 0);
//		Options.Visuals.Esp.General.bAimlines = reader.ReadInteger("Config", "bAimlines", 0);
//		Options.Visuals.Esp.General.bBarrel = reader.ReadInteger("Config", "bBarrel", 0);
//		//Options.Visuals.Esp.EspBox.
//		Options.Visuals.Esp.EspBox.bWeapons = reader.ReadInteger("Config", "bWeapons", 0);
//		Options.Visuals.Esp.EspBox.bAmmo = reader.ReadInteger("Config", "bAmmo", 0);
//		Options.Visuals.Esp.EspBox.bName = reader.ReadInteger("Config", "bName", 0);
//		Options.Visuals.Esp.EspBox.bIsScoped = reader.ReadInteger("Config", "bIsScoped", 0);
//		Options.Visuals.Esp.EspBox.bIsFlashed = reader.ReadInteger("Config", "bIsFlashed", 0);
//		//Options.Visuals.Esp.EspFilter.
//		Options.Visuals.Esp.EspFilter.bDroppedWeapons = reader.ReadInteger("Config", "bDroppedWeapons", 0);
//		Options.Visuals.Esp.EspFilter.bEspTeam = reader.ReadInteger("Config", "bEspTeam", 0);
//		Options.Visuals.Esp.EspFilter.bXQZ = reader.ReadInteger("Config", "bXQZ", 0);
//		Options.Visuals.Esp.EspFilter.bC4 = reader.ReadInteger("Config", "bC4", 0);
//		Options.Visuals.Esp.EspFilter.bHostage = reader.ReadInteger("Config", "bHostage", 0);
//		//Options.Visuals.Infobox.
//		Options.Visuals.Infobox.bInfoBox = reader.ReadInteger("Config", "bInfoBox", 0);
//		Options.Visuals.Infobox.bInfoLby = reader.ReadInteger("Config", "bInfoLby", 0);
//		Options.Visuals.Infobox.bInfoVelocity = reader.ReadInteger("Config", "bInfoVelocity", 0);
//		Options.Visuals.Infobox.bInfoAngles = reader.ReadInteger("Config", "bInfoAngles", 0);
//		//Options.Visuals.VisualsMisc.
//		Options.Visuals.VisualsMisc.bCrosshair = reader.ReadInteger("Config", "bCrosshair", 0);
//		Options.Visuals.VisualsMisc.bRecoilCrosshair = reader.ReadInteger("Config", "bRecoilCrosshair", 0);
//		Options.Visuals.VisualsMisc.bSpreadCrosshair = reader.ReadInteger("Config", "bSpreadCrosshair", 0);
//		Options.Visuals.VisualsMisc.bNoVisualRecoil = reader.ReadInteger("Config", "bNoVisualRecoil", 0);
//		Options.Visuals.VisualsMisc.bNoFlash = reader.ReadInteger("Config", "bNoFlash", 0);
//		Options.Visuals.VisualsMisc.bNoSmoke = reader.ReadInteger("Config", "bNoSmoke", 0);
//		Options.Visuals.VisualsMisc.bThirdPerson = reader.ReadInteger("Config", "bThirdPerson", 0);
//		Options.Visuals.VisualsMisc.bThirdPersonOnKey = reader.ReadInteger("Config", "bThirdPersonOnKey", 0);
//		Options.Visuals.VisualsMisc.iThirdPersonKey = reader.ReadInteger("Config", "iThirdPersonKey", 0);
//		Options.Visuals.VisualsMisc.bScopeRemover = reader.ReadInteger("Config", "bScopeRemover", 0);
//		Options.Visuals.VisualsMisc.bAsusWalls = reader.ReadInteger("Config", "bAsusWalls", 0);
//		Options.Visuals.VisualsMisc.bNightMode = reader.ReadInteger("Config", "bNightMode", 0);
//		Options.Visuals.VisualsMisc.iSkyboxChanger = reader.ReadInteger("Config", "iSkyboxChanger", 0);
//		Options.Visuals.VisualsMisc.bEngineRadar = reader.ReadInteger("Config", "bEngineRadar", 0);
//		Options.Visuals.VisualsMisc.bWatermark = reader.ReadInteger("Config", "bWatermark", 0);
//		Options.Visuals.VisualsMisc.bHitMarker = reader.ReadInteger("Config", "bHitMarker", 0);
//		//Options.Visuals.Chams.
//		Options.Visuals.Chams.bChamsEnable = reader.ReadInteger("Config", "bChamsEnable", 0);
//		Options.Visuals.Chams.iChamsPlayer = reader.ReadInteger("Config", "iChamsPlayer", 0);
//		Options.Visuals.Chams.iChamsWeapon = reader.ReadInteger("Config", "iChamsWeapon", 0);
//		Options.Visuals.Chams.bChamsXQZ = reader.ReadInteger("Config", "bChamsXQZ", 0);
//		Options.Visuals.Chams.bChamsTeam = reader.ReadInteger("Config", "bChamsTeam", 0);
//		//Options.Misc.Misc1.
//		Options.Misc.Misc1.bAutoJump = reader.ReadInteger("Config", "bAutoJump", 0);
//		Options.Misc.Misc1.bAutoStrafe = reader.ReadInteger("Config", "bAutoStrafe", 0);
//		Options.Misc.Misc1.iAutoStrafeMode = reader.ReadInteger("Config", "iAutoStrafeMode", 0);
//		Options.Misc.Misc1.iFakeLag = reader.ReadInteger("Config", "iFakeLag", 0);
//		Options.Misc.Misc1.bZStrafe = reader.ReadInteger("Config", "bZStrafe", 0);
//		Options.Misc.Misc1.iZStrafeKey = reader.ReadInteger("Config", "iZStrafeKey", 0);
//		Options.Misc.Misc1.bCircleStrafer = reader.ReadInteger("Config", "bCircleStrafer", 0);
//		Options.Misc.Misc1.iCircleStraferKey = reader.ReadInteger("Config", "iCircleStraferKey", 0);
//		Options.Misc.Misc1.bAutoAccpet = reader.ReadInteger("Config", "bAutoAccpet", 0);
//		Options.Misc.Misc1.bAimStep = reader.ReadInteger("Config", "bAimStep", 0);
//		Options.Misc.Misc1.bClanTag = reader.ReadInteger("Config", "bClanTag", 0);
//		Options.Misc.Misc1.iClanTagSelection = reader.ReadInteger("Config", "iClanTagSelection", 0);
//		Options.Misc.Misc1.bClanTagAnimation = reader.ReadInteger("Config", "bClanTagAnimation", 0);
//		Options.Misc.Misc1.bUi = reader.ReadInteger("Config", "bUi", 0);
//		Options.Misc.Misc1.bFreeCam = reader.ReadInteger("Config", "bFreeCam", 0);
//		Options.Misc.Misc1.iFreeCamSpeed = reader.ReadInteger("Config", "iFreeCamSpeed", 0);
//		Options.Misc.Misc1.iFreeCamKey = reader.ReadInteger("Config", "iFreeCamKey", 0);
//		Options.Misc.Misc1.bFakeWalk = reader.ReadInteger("Config", "bFakeWalk", 0);
//		Options.Misc.Misc1.iFakeWalkKey = reader.ReadInteger("Config", "iFakeWalkKey", 0);
//		Options.Misc.Misc1.bAirStuck = reader.ReadInteger("Config", "bAirStuck", 0);
//		Options.Misc.Misc1.iAirStuck = reader.ReadInteger("Config", "iAirStuck", 0);
//		Options.Misc.Misc1.iAirStuckKey = reader.ReadInteger("Config", "iAirStuckKey", 0);
//		//Options.Misc.Misc2
//		Options.Misc.Misc2.bAntiUntrusted = reader.ReadInteger("Config", "bAntiUntrusted", 0);
//		Options.Misc.Misc2.bEnableMenuKey = reader.ReadInteger("Config", "bEnableMenuKey", 0);
//		Options.Misc.Misc2.iMenuKey = reader.ReadInteger("Config", "iMenuKey", 0);
//		//Options.Misc.Other
//		Options.Misc.Other.bChatSpam = reader.ReadInteger("Config", "bChatSpam", 0);
//		Options.Misc.Other.bKnifeBot = reader.ReadInteger("Config", "bKnifeBot", 0);
//		Options.Misc.Other.bBlockBot = reader.ReadInteger("Config", "bBlockBot", 0);
//		Options.Misc.Other.iBlockBotKey = reader.ReadInteger("Config", "iBlockBotKey", 0);
//		Options.Misc.Other.bEnableFov = reader.ReadInteger("Config", "bEnableFov", 0);
//		Options.Misc.Other.flFovValue = reader.ReadFloat("Config", "flFovValue", 90);
//		Options.Misc.Other.iViewmodelChanger = reader.ReadInteger("Config", "iViewmodelChanger", 0);
//		Options.Misc.Other.flViewModelValue = reader.ReadFloat("Config", "flViewModelValue", 0);
//
//	}
//
//	void Save()
//	{
//		CIniWriter writer(config_path);
//
//		//Options.Ragebot.Genrral
//		writer.WriteInteger("Config", "bAimbotEnable = %d", Options.Ragebot.Aimbot.bAimbotEnable);
//		writer.WriteInteger("Config", "bAutoShoot = %d", Options.Ragebot.Aimbot.bAutoShoot);
//		writer.WriteInteger("Config", "bAutoScope = %d", Options.Ragebot.Aimbot.bAutoScope);
//		writer.WriteInteger("Config", "bAutoRevolver = %d", Options.Ragebot.Aimbot.bAutoRevolver);
//		writer.WriteInteger("Config", "bSilentAim = %d", Options.Ragebot.Aimbot.bSilentAim);
//		writer.WriteInteger("Config", "iHitbox = %d", Options.Ragebot.Aimbot.iHitbox);
//		writer.WriteInteger("Config", "iSelection = %d", Options.Ragebot.Aimbot.iSelection);
//		//Options.Ragebot.Accuracy
//		writer.WriteInteger("Config", "bVelocityPrediction = %d", Options.Ragebot.Accuracy.bVelocityPrediction);
//		writer.WriteInteger("Config", "iMultibox = %d", Options.Ragebot.Accuracy.iMultibox);
//		writer.WriteInteger("Config", "bMultipoint = %d", Options.Ragebot.Accuracy.bMultipoint);
//		writer.WriteInteger("Config", "iPointscale = %d", Options.Ragebot.Accuracy.iPointscale);
//		writer.WriteInteger("Config", "iHitchance = %d", Options.Ragebot.Accuracy.iHitchance);
//		writer.WriteInteger("Config", "iMinDmg = %d", Options.Ragebot.Accuracy.iMinDmg);
//		writer.WriteInteger("Config", "bAcceptKillDmg = %d", Options.Ragebot.Accuracy.bAcceptKillDmg);
//		writer.WriteInteger("Config", "bNoRecoil = %d", Options.Ragebot.Accuracy.bNoRecoil);
//		writer.WriteInteger("Config", "bAutoStop = %d", Options.Ragebot.Accuracy.bAutoStop);
//		writer.WriteInteger("Config", "iAutoStopKey = %d", Options.Ragebot.Accuracy.iAutoStopKey);
//		//Options.Ragebot.HvH
//		writer.WriteInteger("Config", "bAntiAimCorrection = %d", Options.Ragebot.HvH.bAntiAimCorrection);
//		writer.WriteInteger("Config", "iPreferBaim = %d", Options.Ragebot.HvH.iPreferBaim);
//		writer.WriteInteger("Config", "bPositionAdj = %d", Options.Ragebot.HvH.bPositionAdj);
//		//Options.Ragebot.AntiAim.AntiAimStand
//		writer.WriteInteger("Config", "bEnable_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bEnable_Stand);
//		writer.WriteInteger("Config", "bAASwitch_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bAASwitch_Stand);
//		writer.WriteInteger("Config", "iPitch_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iPitch_Stand);
//		writer.WriteInteger("Config", "iRealYaw_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iRealYaw_Stand);
//		writer.WriteInteger("Config", "iFakeYaw_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iFakeYaw_Stand);
//		writer.WriteInteger("Config", "bAtTargets_Stand", Options.Ragebot.AntiAim.AntiAimStand.bAtTargets_Stand);
//		writer.WriteInteger("Config", "bMMSafe_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bMMSafe_Stand);
//		writer.WriteInteger("Config", "bEdgeDetection_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bEdgeDetection_Stand);
//		writer.WriteInteger("Config", "bFakeHitbox_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bFakeHitbox_Stand);
//		writer.WriteInteger("Config", "bAntiLby_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bAntiLby_Stand);
//		//Options.Ragebot.AntiAim.AntiAimMove
//		//TODO
//		//Options.Ragebot.AntiAim.AntiAimJump
//		//TODO
//		//Options.Ragebot.AntiAim.AntiAimMisc
//		writer.WriteInteger("Config", "bMemewalk = %d", Options.Ragebot.AntiAim.AntiAimMisc.bMemewalk);
//		//Legitbot lass ich erstmal aus :)
//		//Options.Visuals.Esp.General.
//		writer.WriteInteger("Config", "iBox = %d", Options.Visuals.Esp.General.iBox);
//		writer.WriteInteger("Config", "bHealthbar = %d", Options.Visuals.Esp.General.bHealthbar);
//		writer.WriteInteger("Config", "bArmorBar = %d", Options.Visuals.Esp.General.bArmorBar);
//		writer.WriteInteger("Config", "iBarPos = %d", Options.Visuals.Esp.General.iBarPos);
//		writer.WriteInteger("Config", "bSkeleton = %d", Options.Visuals.Esp.General.bSkeleton);
//		writer.WriteInteger("Config", "bAimlines = %d", Options.Visuals.Esp.General.bAimlines);
//		writer.WriteInteger("Config", "bBarrel = %d", Options.Visuals.Esp.General.bBarrel);
//		//Options.Visuals.Esp.EspBox.
//		writer.WriteInteger("Config", "bWeapons = %d", Options.Visuals.Esp.EspBox.bWeapons);
//		writer.WriteInteger("Config", "bAmmo = %d", Options.Visuals.Esp.EspBox.bAmmo);
//		writer.WriteInteger("Config", "bName = %d", Options.Visuals.Esp.EspBox.bName);
//		writer.WriteInteger("Config", "bIsScoped = %d", Options.Visuals.Esp.EspBox.bIsScoped);
//		writer.WriteInteger("Config", "bIsFlashed = %d", Options.Visuals.Esp.EspBox.bIsFlashed);
//		//Options.Visuals.Esp.EspFilter.
//		writer.WriteInteger("Config", "bDroppedWeapons = %d", Options.Visuals.Esp.EspFilter.bDroppedWeapons);
//		writer.WriteInteger("Config", "bEspTeam = %d", Options.Visuals.Esp.EspFilter.bEspTeam);
//		writer.WriteInteger("Config", "bXQZ = %d", Options.Visuals.Esp.EspFilter.bXQZ);
//		writer.WriteInteger("Config", "bC4 = %d", Options.Visuals.Esp.EspFilter.bC4);
//		writer.WriteInteger("Config", "bHostage = %d", Options.Visuals.Esp.EspFilter.bHostage);
//		//Options.Visuals.Infobox.
//		writer.WriteInteger("Config", "bInfoBox = %d", Options.Visuals.Infobox.bInfoBox);
//		writer.WriteInteger("Config", "bInfoLby = %d", Options.Visuals.Infobox.bInfoLby);
//		writer.WriteInteger("Config", "bInfoVelocity = %d", Options.Visuals.Infobox.bInfoVelocity);
//		writer.WriteInteger("Config", "bInfoAngles = %d", Options.Visuals.Infobox.bInfoAngles);
//		//Options.Visuals.VisualsMisc.
//		writer.WriteInteger("Config", "bCrosshair = %d", Options.Visuals.VisualsMisc.bCrosshair);
//		writer.WriteInteger("Config", "bRecoilCrosshair = %d", Options.Visuals.VisualsMisc.bRecoilCrosshair);
//		writer.WriteInteger("Config", "bSpreadCrosshair = %d", Options.Visuals.VisualsMisc.bSpreadCrosshair);
//		writer.WriteInteger("Config", "bNoVisualRecoil = %d", Options.Visuals.VisualsMisc.bNoVisualRecoil);
//		writer.WriteInteger("Config", "bNoFlash = %d", Options.Visuals.VisualsMisc.bNoFlash);
//		writer.WriteInteger("Config", "bNoSmoke = %d", Options.Visuals.VisualsMisc.bNoSmoke);
//		writer.WriteInteger("Config", "bThirdPerson = %d", Options.Visuals.VisualsMisc.bThirdPerson);
//		writer.WriteInteger("Config", "bThirdPersonOnKey = %d", Options.Visuals.VisualsMisc.bThirdPersonOnKey);
//		writer.WriteInteger("Config", "iThirdPersonKey = %d", Options.Visuals.VisualsMisc.iThirdPersonKey);
//		writer.WriteInteger("Config", "bScopeRemover = %d", Options.Visuals.VisualsMisc.bScopeRemover);
//		writer.WriteInteger("Config", "bAsusWalls = %d", Options.Visuals.VisualsMisc.bAsusWalls);
//		writer.WriteInteger("Config", "bNightMode = %d", Options.Visuals.VisualsMisc.bNightMode);
//		writer.WriteInteger("Config", "iSkyboxChanger = %d", Options.Visuals.VisualsMisc.iSkyboxChanger);
//		writer.WriteInteger("Config", "bEngineRadar = %d", Options.Visuals.VisualsMisc.bEngineRadar);
//		writer.WriteInteger("Config", "bWatermark = %d", Options.Visuals.VisualsMisc.bWatermark);
//		writer.WriteInteger("Config", "bHitMarker = %d", Options.Visuals.VisualsMisc.bHitMarker);
//		//Options.Visuals.Chams.
//		writer.WriteInteger("Config", "bChamsEnable = %d", Options.Visuals.Chams.bChamsEnable);
//		writer.WriteInteger("Config", "iChamsPlayer = %d", Options.Visuals.Chams.iChamsPlayer);
//		writer.WriteInteger("Config", "iChamsWeapon = %d", Options.Visuals.Chams.iChamsWeapon);
//		writer.WriteInteger("Config", "bChamsXQZ = %d", Options.Visuals.Chams.bChamsXQZ);
//		writer.WriteInteger("Config", "bChamsTeam = %d", Options.Visuals.Chams.bChamsTeam);
//		//Options.Misc.Misc1.
//		writer.WriteInteger("Config", "bAutoJump = %d", Options.Misc.Misc1.bAutoJump);
//		writer.WriteInteger("Config", "bAutoStrafe = %d", Options.Misc.Misc1.bAutoStrafe);
//		writer.WriteInteger("Config", "iAutoStrafeMode = %d", Options.Misc.Misc1.iAutoStrafeMode);
//		writer.WriteInteger("Config", "iFakeLag = %d", Options.Misc.Misc1.iFakeLag);
//		writer.WriteInteger("Config", "bZStrafe = %d", Options.Misc.Misc1.bZStrafe);
//		writer.WriteInteger("Config", "iZStrafeKey = %d", Options.Misc.Misc1.iZStrafeKey);
//		writer.WriteInteger("Config", "bCircleStrafer = %d", Options.Misc.Misc1.bCircleStrafer);
//		writer.WriteInteger("Config", "iCircleStaferKey = %d", Options.Misc.Misc1.iCircleStraferKey);
//		writer.WriteInteger("Config", "bAutoAccept = %d", Options.Misc.Misc1.bAutoAccpet);
//		writer.WriteInteger("Config", "bAimStep = %d", Options.Misc.Misc1.bAimStep);
//		writer.WriteInteger("Config", "bClanTag = %d", Options.Misc.Misc1.bClanTag);
//		writer.WriteInteger("Config", "iClanTagSelection = %d", Options.Misc.Misc1.iClanTagSelection);
//		writer.WriteInteger("Config", "bClanTagAnimation = %d", Options.Misc.Misc1.bClanTagAnimation);
//		writer.WriteInteger("Config", "bUi = %d", Options.Misc.Misc1.bUi);
//		writer.WriteInteger("Config", "bFreeCam = %d", Options.Misc.Misc1.bFreeCam);
//		writer.WriteInteger("Config", "iFreeCamSpeed = %d", Options.Misc.Misc1.iFreeCamSpeed);
//		writer.WriteInteger("Config", "iFreeCamKey = %d", Options.Misc.Misc1.iFreeCamKey);
//		writer.WriteInteger("Config", "bFakeWalk = %d", Options.Misc.Misc1.bFakeWalk);
//		writer.WriteInteger("Config", "iFakeWalkKey = %d", Options.Misc.Misc1.iFakeWalkKey);
//		writer.WriteInteger("Config", "bAirStuck = %d", Options.Misc.Misc1.bAirStuck);
//		writer.WriteInteger("Config", "iAirStuck = %d", Options.Misc.Misc1.iAirStuck);
//		writer.WriteInteger("Config", "iAirStuckKey = %d", Options.Misc.Misc1.iAirStuckKey);
//		//Options.Misc.Misc2
//		writer.WriteInteger("Config", "bAntiUntrusted = %d", Options.Misc.Misc2.bAntiUntrusted);
//		writer.WriteInteger("Config", "bEnableMenuKey = %d", Options.Misc.Misc2.bEnableMenuKey);
//		writer.WriteInteger("Config", "iMenuKey = %d", Options.Misc.Misc2.iMenuKey);
//		//Options.Misc.Other
//		writer.WriteInteger("Config", "bChatSpam = %d", Options.Misc.Other.bChatSpam);
//		writer.WriteInteger("Config", "bKnifeBot = %d", Options.Misc.Other.bKnifeBot);
//		writer.WriteInteger("Config", "bBlockBot = %d", Options.Misc.Other.bBlockBot);
//		writer.WriteInteger("Config", "iBlockBotKey = %d", Options.Misc.Other.iBlockBotKey);
//		writer.WriteInteger("Config", "bEnableFov = %d", Options.Misc.Other.bEnableFov);
//		writer.WriteFloat("Config", "flFovValue = %f", Options.Misc.Other.flFovValue);
//		writer.WriteInteger("Config", "iViewModelChanger = %d", Options.Misc.Other.iViewmodelChanger);
//		writer.WriteFloat("Config", "flViewModelValue = %f", Options.Misc.Other.flViewModelValue);
//	}
//}