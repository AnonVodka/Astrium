#pragma once

//#include "Config.h"

//class ConfigFile
//{
//public:
//
//	ConfigFile(const char *path, const char *name)
//	{
//		this->path = path;
//		this->name = name;
//	}
//
//public:
//
//	std::string path, name;
//};
//
//std::vector<ConfigFile> getAllConfInFolder(std::string path);
//std::vector<std::string> getAllConf();
//
//bool fileExists(std::string &file)
//{
//	std::ifstream in(file);
//	return in.good();
//}
//
//void createConfFolder(const char *path)
//{
//	if (!CreateDirectory(path, NULL)) return;
//}
//
//std::vector<ConfigFile> getAllConfInFolder(std::string path)
//{
//	std::vector<ConfigFile> configs;
//	std::string search_path = path + "*.aui";
//	WIN32_FIND_DATA fd;
//	HANDLE hFind = FindFirstFile(search_path.c_str(), &fd);
//	if (hFind != INVALID_HANDLE_VALUE)
//	{
//		do
//		{
//			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
//			{
//				std::string fPath = path + fd.cFileName;
//
//				std::string tmp_f_name(fd.cFileName);
//				size_t pos = tmp_f_name.find(".");
//				std::string fName = (std::string::npos == pos) ? tmp_f_name : tmp_f_name.substr(0, pos);
//
//				ConfigFile newConf(fPath.c_str(), fName.c_str());
//				configs.push_back(newConf);
//			}
//		} while (FindNextFile(hFind, &fd));
//		FindClose(hFind);
//	}
//	return configs;
//}
//
//std::vector<std::string> getAllConf()
//{
//	char file[MAX_PATH] = { 0 };
//	char buf[MAX_PATH];
//
//	GetTempPath(MAX_PATH, buf);
//
//	strcpy_s(file, buf);
//	strcat_s(file, "Astrium\\");
//
//	std::vector<ConfigFile> confFiles = getAllConfInFolder(file);
//	std::vector<std::string> confs;
//
//	for (auto config = confFiles.begin(); config != confFiles.end(); config++)
//		confs.push_back(config->name);
//
//	std::sort(confs.begin(), confs.end());
//
//	return confs;
//}
//
//void loadConf(std::string path)
//{
//	std::unique_ptr<ConfigMngr::Config> sConfigMgr = std::make_unique<ConfigMngr::Config>();
//
//	if (sConfigMgr->loadInitial(std::string(path)))
//	{
//		//Options.Ragebot.Aimbot
//	 Options.Ragebot.Aimbot.bAimbotEnable = sConfigMgr->getInt("bAimbotEnable");
//	 Options.Ragebot.Aimbot.bAutoShoot = sConfigMgr->getInt("bAutoShoot");
//	 Options.Ragebot.Aimbot.bAutoScope = sConfigMgr->getInt("bAutoScope");
//	 Options.Ragebot.Aimbot.bAutoRevolver = sConfigMgr->getInt("bAutoRevolver");
//	 Options.Ragebot.Aimbot.bSilentAim = sConfigMgr->getInt("bSilentAim");
//	 Options.Ragebot.Aimbot.iHitbox = sConfigMgr->getInt("iHitbox");
//	 Options.Ragebot.Aimbot.iSelection = sConfigMgr->getInt("iSelection");
//	//Options.Ragebot.Accuracy
//	 Options.Ragebot.Accuracy.bVelocityPrediction = sConfigMgr->getInt("bVelocityPrediction");
//	 Options.Ragebot.Accuracy.iMultibox = sConfigMgr->getInt("iMultibox");
//	 Options.Ragebot.Accuracy.bMultipoint = sConfigMgr->getInt("bMultipoint");
//	 Options.Ragebot.Accuracy.iPointscale = sConfigMgr->getInt("iPointscale");
//	 Options.Ragebot.Accuracy.iHitchance = sConfigMgr->getInt("iHitchance");
//	 Options.Ragebot.Accuracy.iMinDmg = sConfigMgr->getInt("iMinDmg");
//	 Options.Ragebot.Accuracy.bAcceptKillDmg = sConfigMgr->getInt("bAcceptKillDmg");
//	 Options.Ragebot.Accuracy.bNoRecoil = sConfigMgr->getInt("bNoRecoil");
//	 Options.Ragebot.Accuracy.bAutoStop = sConfigMgr->getInt("bAutoStop");
//	 Options.Ragebot.Accuracy.iAutoStopKey = sConfigMgr->getInt("iAutoStopKey");
//	//Options.Ragebot.HvH
//	 Options.Ragebot.HvH.bAntiAimCorrection = sConfigMgr->getInt("bAntiAimCorrection");
//	 Options.Ragebot.HvH.iPreferBaim = sConfigMgr->getInt("iPreferBaim");
//	 Options.Ragebot.HvH.bPositionAdj = sConfigMgr->getInt("bPositionAdj");
//	//Options.Ragebot.AntiAim.AntiAimStand
//	 Options.Ragebot.AntiAim.AntiAimStand.bEnable_Stand = sConfigMgr->getInt("bEnable_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bAASwitch_Stand = sConfigMgr->getInt("bAASwitch_Stand");
//   	 Options.Ragebot.AntiAim.AntiAimStand.iPitch_Stand = sConfigMgr->getInt("iPitch_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.iRealYaw_Stand = sConfigMgr->getInt("iRealYaw_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.iFakeYaw_Stand = sConfigMgr->getInt("iFakeYaw_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bAtTargets_Stand = sConfigMgr->getInt("bAtTargets_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bMMSafe_Stand = sConfigMgr->getInt("bMMSafe_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bEdgeDetection_Stand = sConfigMgr->getInt("bEdgeDetection_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bFakeHitbox_Stand = sConfigMgr->getInt("bFakeHitbox_Stand");
//	 Options.Ragebot.AntiAim.AntiAimStand.bAntiLby_Stand = sConfigMgr->getInt("bAntiLby_Stand");
//	//Options.Ragebot.AntiAim.AntiAimMove
//	//TODO
//	//Options.Ragebot.AntiAim.AntiAimJump
//	//TODO
//	//Options.Ragebot.AntiAim.AntiAimMisc
//	 Options.Ragebot.AntiAim.AntiAimMisc.bMemewalk = sConfigMgr->getInt("bMemewalk");
//	//Legitbot lass ich erstmal aus :)
//	//Options.Visuals.Esp.General.
//	 Options.Visuals.Esp.General.iBox = sConfigMgr->getInt("iBox");
//	 Options.Visuals.Esp.General.bHealthbar = sConfigMgr->getInt("bHealthbar");
//	 Options.Visuals.Esp.General.bArmorBar = sConfigMgr->getInt("bArmorBar");
//	 Options.Visuals.Esp.General.iBarPos = sConfigMgr->getInt("iBarPos");
//	 Options.Visuals.Esp.General.bSkeleton = sConfigMgr->getInt("bSkeleton");
//	 Options.Visuals.Esp.General.bAimlines = sConfigMgr->getInt("bAimlines");
//	 Options.Visuals.Esp.General.bBarrel = sConfigMgr->getInt("bBarrel");
//	//Options.Visuals.Esp.EspBox.
//	 Options.Visuals.Esp.EspBox.bWeapons = sConfigMgr->getInt("bWeapons");
//	 Options.Visuals.Esp.EspBox.bAmmo = sConfigMgr->getInt("bAmmo");
//	 Options.Visuals.Esp.EspBox.bName = sConfigMgr->getInt("bName");
//	 Options.Visuals.Esp.EspBox.bIsScoped = sConfigMgr->getInt("bIsScoped");
//	 Options.Visuals.Esp.EspBox.bIsFlashed = sConfigMgr->getInt("bIsFlashed");
//	//Options.Visuals.Esp.EspFilter.
//	 Options.Visuals.Esp.EspFilter.bDroppedWeapons = sConfigMgr->getInt("bDroppedWeapons");
//	 Options.Visuals.Esp.EspFilter.bEspTeam = sConfigMgr->getInt("bEspTeam");
//	 Options.Visuals.Esp.EspFilter.bXQZ = sConfigMgr->getInt("bXQZ");
//	 Options.Visuals.Esp.EspFilter.bC4 = sConfigMgr->getInt("bC4");
//	 Options.Visuals.Esp.EspFilter.bHostage = sConfigMgr->getInt("bHostage");
//	//Options.Visuals.Infobox.
//	 Options.Visuals.Infobox.bInfoBox = sConfigMgr->getInt("bInfoBox");
//	 Options.Visuals.Infobox.bInfoLby = sConfigMgr->getInt("bInfoLby");
//	 Options.Visuals.Infobox.bInfoVelocity = sConfigMgr->getInt("bInfoVelocity");
//	 Options.Visuals.Infobox.bInfoAngles = sConfigMgr->getInt("bInfoAngles");
//	//Options.Visuals.VisualsMisc.
//	 Options.Visuals.VisualsMisc.bCrosshair = sConfigMgr->getInt("bCrosshair");
//	 Options.Visuals.VisualsMisc.bRecoilCrosshair = sConfigMgr->getInt("bRecoilCrosshair");
//	 Options.Visuals.VisualsMisc.bSpreadCrosshair = sConfigMgr->getInt("bSpreadCrosshair");
//	 Options.Visuals.VisualsMisc.bNoVisualRecoil = sConfigMgr->getInt("bNoVisualRecoil");
//	 Options.Visuals.VisualsMisc.bNoFlash = sConfigMgr->getInt("bNoFlash");
//	 Options.Visuals.VisualsMisc.bNoSmoke = sConfigMgr->getInt("bNoSmoke");
//	 Options.Visuals.VisualsMisc.bThirdPerson = sConfigMgr->getInt("bThirdPerson");
//	 Options.Visuals.VisualsMisc.bThirdPersonOnKey = sConfigMgr->getInt("bThirdPersonOnKey");
//	 Options.Visuals.VisualsMisc.iThirdPersonKey = sConfigMgr->getInt("iThirdPersonKey");
//	 Options.Visuals.VisualsMisc.bScopeRemover = sConfigMgr->getInt("bScopeRemover");
//	 Options.Visuals.VisualsMisc.bAsusWalls = sConfigMgr->getInt("bAsusWalls");
//	 Options.Visuals.VisualsMisc.bNightMode = sConfigMgr->getInt("bNightMode");
//	 Options.Visuals.VisualsMisc.iSkyboxChanger = sConfigMgr->getInt("iSkyboxChanger");
//	 Options.Visuals.VisualsMisc.bEngineRadar = sConfigMgr->getInt("bEngineRadar");
//	 Options.Visuals.VisualsMisc.bWatermark = sConfigMgr->getInt("bWatermark");
//	 Options.Visuals.VisualsMisc.bHitMarker = sConfigMgr->getInt("bHitMarker");
//	//Options.Visuals.Chams.
//	 Options.Visuals.Chams.bChamsEnable = sConfigMgr->getInt("bChamsEnable");
//	 Options.Visuals.Chams.iChamsPlayer = sConfigMgr->getInt("iChamsPlayer");
//	 Options.Visuals.Chams.iChamsWeapon = sConfigMgr->getInt("iChamsWeapon");
//	 Options.Visuals.Chams.bChamsXQZ = sConfigMgr->getInt("bChamsXQZ");
//	 Options.Visuals.Chams.bChamsTeam = sConfigMgr->getInt("bChamsTeam");
//	//Options.Misc.Misc1.
//	 Options.Misc.Misc1.bAutoJump = sConfigMgr->getInt("bAutoJump");
//	 Options.Misc.Misc1.bAutoStrafe = sConfigMgr->getInt("bAutoStrafe");
//	 Options.Misc.Misc1.iAutoStrafeMode = sConfigMgr->getInt("iAutoStrafeMode");
//	 Options.Misc.Misc1.iFakeLag = sConfigMgr->getInt("iFakeLag");
//	 Options.Misc.Misc1.bZStrafe = sConfigMgr->getInt("bZStrafe");
//	 Options.Misc.Misc1.iZStrafeKey = sConfigMgr->getInt("iZStrafeKey");
//	 Options.Misc.Misc1.bCircleStrafer = sConfigMgr->getInt("bCircleStrafer");
//	 Options.Misc.Misc1.iCircleStraferKey = sConfigMgr->getInt("iCircleStraferKey");
//	 Options.Misc.Misc1.bAutoAccpet = sConfigMgr->getInt("bAutoAccpet");
//	 Options.Misc.Misc1.bAimStep = sConfigMgr->getInt("bAimStep");
//	 Options.Misc.Misc1.bClanTag = sConfigMgr->getInt("bClanTag");
//	 Options.Misc.Misc1.iClanTagSelection = sConfigMgr->getInt("iClanTagSelection");
//	 Options.Misc.Misc1.bClanTagAnimation = sConfigMgr->getInt("bClanTagAnimation");
//	 Options.Misc.Misc1.bUi = sConfigMgr->getInt("bUi");
//	 Options.Misc.Misc1.bFreeCam = sConfigMgr->getInt("bFreeCam");
//	 Options.Misc.Misc1.iFreeCamSpeed = sConfigMgr->getInt("iFreeCamSpeed");
//	 Options.Misc.Misc1.iFreeCamKey = sConfigMgr->getInt("iFreeCamKey");
//	 Options.Misc.Misc1.bFakeWalk = sConfigMgr->getInt("bFakeWalk");
//	 Options.Misc.Misc1.iFakeWalkKey = sConfigMgr->getInt("iFakeWalkKey");
//	 Options.Misc.Misc1.bAirStuck = sConfigMgr->getInt("bAirStuck");
//	 Options.Misc.Misc1.iAirStuck = sConfigMgr->getInt("iAirStuck");
//	 Options.Misc.Misc1.iAirStuckKey = sConfigMgr->getInt("iAirStuckKey");
//	//Options.Misc.Misc2
//	 Options.Misc.Misc2.bAntiUntrusted = sConfigMgr->getInt("bAntiUntrusted");
//	 Options.Misc.Misc2.bEnableMenuKey = sConfigMgr->getInt("bEnableMenuKey");
//	 Options.Misc.Misc2.iMenuKey = sConfigMgr->getInt("iMenuKey");
//	//Options.Misc.Other
//	 Options.Misc.Other.bChatSpam = sConfigMgr->getInt("bChatSpam");
//	 Options.Misc.Other.bKnifeBot = sConfigMgr->getInt("bKnifeBot");
//	 Options.Misc.Other.bBlockBot = sConfigMgr->getInt("bBlockBot");
//	 Options.Misc.Other.iBlockBotKey = sConfigMgr->getInt("iBlockBotKey");
//	 Options.Misc.Other.bEnableFov = sConfigMgr->getInt("bEnableFov");
//	 Options.Misc.Other.flFovValue = sConfigMgr->getFloat("flFovValue");
//	 Options.Misc.Other.iViewmodelChanger = sConfigMgr->getInt("iViewmodelChanger");
//	 Options.Misc.Other.flViewModelValue = sConfigMgr->getFloat("flViewModelValue");
//	}
//}
//
//void writeConf(std::string path)
//{
//	std::unique_ptr<Logging::FileLogger> fileLogger = std::make_unique<Logging::FileLogger>(path, path);
//
//	fileLogger->write("[Astrium]\n");
//
//	//Options.Ragebot.Aimbot
//	fileLogger->write("bAimbotEnable = %d", Options.Ragebot.Aimbot.bAimbotEnable);
//	fileLogger->write("bAutoShoot = %d", Options.Ragebot.Aimbot.bAutoShoot);
//	fileLogger->write("bAutoScope = %d", Options.Ragebot.Aimbot.bAutoScope);
//	fileLogger->write("bAutoRevolver = %d", Options.Ragebot.Aimbot.bAutoRevolver);
//	fileLogger->write("bSilentAim = %d", Options.Ragebot.Aimbot.bSilentAim);
//	fileLogger->write("iHitbox = %d", Options.Ragebot.Aimbot.iHitbox);
//	fileLogger->write("iSelection = %d", Options.Ragebot.Aimbot.iSelection);
//	//Options.Ragebot.Accuracy
//	fileLogger->write("bVelocityPrediction = %d", Options.Ragebot.Accuracy.bVelocityPrediction);
//	fileLogger->write("iMultibox = %d", Options.Ragebot.Accuracy.iMultibox);
//	fileLogger->write("bMultipoint = %d", Options.Ragebot.Accuracy.bMultipoint);
//	fileLogger->write("iPointscale = %d", Options.Ragebot.Accuracy.iPointscale);
//	fileLogger->write("iHitchance = %d", Options.Ragebot.Accuracy.iHitchance);
//	fileLogger->write("iMinDmg = %d", Options.Ragebot.Accuracy.iMinDmg);
//	fileLogger->write("bAcceptKillDmg = %d", Options.Ragebot.Accuracy.bAcceptKillDmg);
//	fileLogger->write("bNoRecoil = %d", Options.Ragebot.Accuracy.bNoRecoil);
//	fileLogger->write("bAutoStop = %d", Options.Ragebot.Accuracy.bAutoStop);
//	fileLogger->write("iAutoStopKey = %d", Options.Ragebot.Accuracy.iAutoStopKey);
//	//Options.Ragebot.HvH
//	fileLogger->write("bAntiAimCorrection = %d", Options.Ragebot.HvH.bAntiAimCorrection);
//	fileLogger->write("iPreferBaim = %d", Options.Ragebot.HvH.iPreferBaim);
//	fileLogger->write("bPositionAdj = %d", Options.Ragebot.HvH.bPositionAdj);
//	//Options.Ragebot.AntiAim.AntiAimStand
//	fileLogger->write("bEnable_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bEnable_Stand);
//	fileLogger->write("bAASwitch_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bAASwitch_Stand);
//	fileLogger->write("iPitch_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iPitch_Stand);
//	fileLogger->write("iRealYaw_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iRealYaw_Stand);
//	fileLogger->write("iFakeYaw_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.iFakeYaw_Stand);
//	fileLogger->write("bAtTargets_Stand", Options.Ragebot.AntiAim.AntiAimStand.bAtTargets_Stand);
//	fileLogger->write("bMMSafe_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bMMSafe_Stand);
//	fileLogger->write("bEdgeDetection_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bEdgeDetection_Stand);
//	fileLogger->write("bFakeHitbox_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bFakeHitbox_Stand);
//	fileLogger->write("bAntiLby_Stand = %d", Options.Ragebot.AntiAim.AntiAimStand.bAntiLby_Stand);
//	//Options.Ragebot.AntiAim.AntiAimMove
//	//TODO
//	//Options.Ragebot.AntiAim.AntiAimJump
//	//TODO
//	//Options.Ragebot.AntiAim.AntiAimMisc
//	fileLogger->write("bMemewalk = %d", Options.Ragebot.AntiAim.AntiAimMisc.bMemewalk);
//	//Legitbot lass ich erstmal aus :)
//	//Options.Visuals.Esp.General.
//	fileLogger->write("iBox = %d", Options.Visuals.Esp.General.iBox);
//	fileLogger->write("bHealthbar = %d", Options.Visuals.Esp.General.bHealthbar);
//	fileLogger->write("bArmorBar = %d", Options.Visuals.Esp.General.bArmorBar);
//	fileLogger->write("iBarPos = %d", Options.Visuals.Esp.General.iBarPos);
//	fileLogger->write("bSkeleton = %d", Options.Visuals.Esp.General.bSkeleton);
//	fileLogger->write("bAimlines = %d", Options.Visuals.Esp.General.bAimlines);
//	fileLogger->write("bBarrel = %d", Options.Visuals.Esp.General.bBarrel);
//	//Options.Visuals.Esp.EspBox.
//	fileLogger->write("bWeapons = %d", Options.Visuals.Esp.EspBox.bWeapons);
//	fileLogger->write("bAmmo = %d", Options.Visuals.Esp.EspBox.bAmmo);
//	fileLogger->write("bName = %d", Options.Visuals.Esp.EspBox.bName);
//	fileLogger->write("bIsScoped = %d", Options.Visuals.Esp.EspBox.bIsScoped);
//	fileLogger->write("bIsFlashed = %d", Options.Visuals.Esp.EspBox.bIsFlashed);
//	//Options.Visuals.Esp.EspFilter.
//	fileLogger->write("bDroppedWeapons = %d", Options.Visuals.Esp.EspFilter.bDroppedWeapons);
//	fileLogger->write("bEspTeam = %d", Options.Visuals.Esp.EspFilter.bEspTeam);
//	fileLogger->write("bXQZ = %d", Options.Visuals.Esp.EspFilter.bXQZ);
//	fileLogger->write("bC4 = %d", Options.Visuals.Esp.EspFilter.bC4);
//	fileLogger->write("bHostage = %d", Options.Visuals.Esp.EspFilter.bHostage);
//	//Options.Visuals.Infobox.
//	fileLogger->write("bInfoBox = %d", Options.Visuals.Infobox.bInfoBox);
//	fileLogger->write("bInfoLby = %d", Options.Visuals.Infobox.bInfoLby);
//	fileLogger->write("bInfoVelocity = %d", Options.Visuals.Infobox.bInfoVelocity);
//	fileLogger->write("bInfoAngles = %d", Options.Visuals.Infobox.bInfoAngles);
//	//Options.Visuals.VisualsMisc.
//	fileLogger->write("bCrosshair = %d", Options.Visuals.VisualsMisc.bCrosshair);
//	fileLogger->write("bRecoilCrosshair = %d", Options.Visuals.VisualsMisc.bRecoilCrosshair);
//	fileLogger->write("bSpreadCrosshair = %d", Options.Visuals.VisualsMisc.bSpreadCrosshair);
//	fileLogger->write("bNoVisualRecoil = %d", Options.Visuals.VisualsMisc.bNoVisualRecoil);
//	fileLogger->write("bNoFlash = %d", Options.Visuals.VisualsMisc.bNoFlash);
//	fileLogger->write("bNoSmoke = %d", Options.Visuals.VisualsMisc.bNoSmoke);
//	fileLogger->write("bThirdPerson = %d", Options.Visuals.VisualsMisc.bThirdPerson);
//	fileLogger->write("bThirdPersonOnKey = %d", Options.Visuals.VisualsMisc.bThirdPersonOnKey);
//	fileLogger->write("iThirdPersonKey = %d", Options.Visuals.VisualsMisc.iThirdPersonKey);
//	fileLogger->write("bScopeRemover = %d", Options.Visuals.VisualsMisc.bScopeRemover);
//	fileLogger->write("bAsusWalls = %d", Options.Visuals.VisualsMisc.bAsusWalls);
//	fileLogger->write("bNightMode = %d", Options.Visuals.VisualsMisc.bNightMode);
//	fileLogger->write("iSkyboxChanger = %d", Options.Visuals.VisualsMisc.iSkyboxChanger);
//	fileLogger->write("bEngineRadar = %d", Options.Visuals.VisualsMisc.bEngineRadar);
//	fileLogger->write("bWatermark = %d", Options.Visuals.VisualsMisc.bWatermark);
//	fileLogger->write("bHitMarker = %d", Options.Visuals.VisualsMisc.bHitMarker);
//	//Options.Visuals.Chams.
//	fileLogger->write("bChamsEnable = %d", Options.Visuals.Chams.bChamsEnable);
//	fileLogger->write("iChamsPlayer = %d", Options.Visuals.Chams.iChamsPlayer);
//	fileLogger->write("iChamsWeapon = %d", Options.Visuals.Chams.iChamsWeapon);
//	fileLogger->write("bChamsXQZ = %d", Options.Visuals.Chams.bChamsXQZ);
//	fileLogger->write("bChamsTeam = %d", Options.Visuals.Chams.bChamsTeam);
//	//Options.Misc.Misc1.
//	fileLogger->write("bAutoJump = %d", Options.Misc.Misc1.bAutoJump);
//	fileLogger->write("bAutoStrafe = %d", Options.Misc.Misc1.bAutoStrafe);
//	fileLogger->write("iAutoStrafeMode = %d", Options.Misc.Misc1.iAutoStrafeMode);
//	fileLogger->write("iFakeLag = %d", Options.Misc.Misc1.iFakeLag);
//	fileLogger->write("bZStrafe = %d", Options.Misc.Misc1.bZStrafe);
//	fileLogger->write("iZStrafeKey = %d", Options.Misc.Misc1.iZStrafeKey);
//	fileLogger->write("bCircleStrafer = %d", Options.Misc.Misc1.bCircleStrafer);
//	fileLogger->write("iCircleStaferKey = %d", Options.Misc.Misc1.iCircleStraferKey);
//	fileLogger->write("bAutoAccept = %d", Options.Misc.Misc1.bAutoAccpet);
//	fileLogger->write("bAimStep = %d", Options.Misc.Misc1.bAimStep);
//	fileLogger->write("bClanTag = %d", Options.Misc.Misc1.bClanTag);
//	fileLogger->write("iClanTagSelection = %d", Options.Misc.Misc1.iClanTagSelection);
//	fileLogger->write("bClanTagAnimation = %d", Options.Misc.Misc1.bClanTagAnimation);
//	fileLogger->write("bUi = %d", Options.Misc.Misc1.bUi);
//	fileLogger->write("bFreeCam = %d", Options.Misc.Misc1.bFreeCam);
//	fileLogger->write("iFreeCamSpeed = %d", Options.Misc.Misc1.iFreeCamSpeed);
//	fileLogger->write("iFreeCamKey = %d", Options.Misc.Misc1.iFreeCamKey);
//	fileLogger->write("bFakeWalk = %d", Options.Misc.Misc1.bFakeWalk);
//	fileLogger->write("iFakeWalkKey = %d", Options.Misc.Misc1.iFakeWalkKey);
//	fileLogger->write("bAirStuck = %d", Options.Misc.Misc1.bAirStuck);
//	fileLogger->write("iAirStuck = %d", Options.Misc.Misc1.iAirStuck);
//	fileLogger->write("iAirStuckKey = %d", Options.Misc.Misc1.iAirStuckKey);
//	//Options.Misc.Misc2
//	fileLogger->write("bAntiUntrusted = %d", Options.Misc.Misc2.bAntiUntrusted);
//	fileLogger->write("bEnableMenuKey = %d", Options.Misc.Misc2.bEnableMenuKey);
//	fileLogger->write("iMenuKey = %d", Options.Misc.Misc2.iMenuKey);
//	//Options.Misc.Other
//	fileLogger->write("bChatSpam = %d", Options.Misc.Other.bChatSpam);
//	fileLogger->write("bKnifeBot = %d", Options.Misc.Other.bKnifeBot);
//	fileLogger->write("bBlockBot = %d", Options.Misc.Other.bBlockBot);
//	fileLogger->write("iBlockBotKey = %d", Options.Misc.Other.iBlockBotKey);
//	fileLogger->write("bEnableFov = %d", Options.Misc.Other.bEnableFov);
//	fileLogger->write("flFovValue = %f", Options.Misc.Other.flFovValue);
//	fileLogger->write("iViewModelChanger = %d", Options.Misc.Other.iViewmodelChanger);
//	fileLogger->write("flViewModelValue = %f", Options.Misc.Other.flViewModelValue);
//}
