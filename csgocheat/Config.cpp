#include "Config.h"
#include "Globals.h"

void CConfig::Setup()
{

			//SetupValue(Options.Ragebot.Aimbot
			SetupValue(Options.Ragebot.Aimbot.bAimbotEnable, false, "Rage_Aimbot", "bAimbotEnable");
			SetupValue(Options.Ragebot.Aimbot.bAutoShoot, false, "Rage_Aimbot", "bAutoShoot");
			SetupValue(Options.Ragebot.Aimbot.bAutoScope, false, "Rage_Aimbot", "bAutoScope");
			SetupValue(Options.Ragebot.Aimbot.bAutoRevolver, false, "Rage_Aimbot", "bAutoRevolver");
			SetupValue(Options.Ragebot.Aimbot.bSilentAim, false, "Rage_Aimbot", "bSilentAim");
			SetupValue(Options.Ragebot.Aimbot.bAutoPistol, false, "Rage_Aimbot", "bAutoPisotl");
			SetupValue(Options.Ragebot.Aimbot.iHitbox, 0, "Rage_Aimbot", "iHitbox");
			SetupValue(Options.Ragebot.Aimbot.iSelection, 0, "Rage_Aimbot", "iSelection");
			//SetupValue(Options.Ragebot.Accuracy
			SetupValue(Options.Ragebot.Accuracy.bVelocityPrediction, false, "Rage_Accuracy", "bVelocityPrediction");
			SetupValue(Options.Ragebot.Accuracy.iMultibox, 0, "Rage_Accuracy", "iMultibox");
			SetupValue(Options.Ragebot.Accuracy.bMultipoint, false, "Rage_Accuracy", "bMultipoint");
			SetupValue(Options.Ragebot.Accuracy.iPointscale, 50, "Rage_Accuracy", "iPointscale");
			SetupValue(Options.Ragebot.Accuracy.iHitchance, 20, "Rage_Accuracy", "iHitchance");
			SetupValue(Options.Ragebot.Accuracy.iMinDmg, 5, "Rage_Accuracy", "iMinDmg");
			SetupValue(Options.Ragebot.Accuracy.bAcceptKillDmg, false, "Rage_Accuracy", "bAcceptKillDmg");
			SetupValue(Options.Ragebot.Accuracy.bNoRecoil, false, "Rage_Accuracy", "bNoRecoil");
			//SetupValue(Options.Ragebot.Accuracy.bAutoStop, false, "Rage_Accuracy", "bAutoStop");
			//SetupValue(Options.Ragebot.Accuracy.iAutoStopKey, 20, "Rage_Accuracy", "iAutoStopKey");
			//SetupValue(Options.Ragebot.HvH
			SetupValue(Options.Ragebot.HvH.iAntiAimResolver, 0, "Rage_HvH", "iAntiAimResolver");
			SetupValue(Options.Ragebot.HvH.iPreferBaim, 0, "Rage_HvH", "iPreferBaim");
			SetupValue(Options.Ragebot.HvH.bPositionAdj, false, "Rage_HvH", "bPositionAdj");
			//SetupValue(Options.Ragebot.AntiAim.Stand
			SetupValue(Options.Ragebot.AntiAim.Stand.bEnableAntiAim, 0, "Stand AA", "bEnableAntiAim");
			SetupValue(Options.Ragebot.AntiAim.Stand.bAtTargets, 0, "Stand AA", "bAtTargets");
			SetupValue(Options.Ragebot.AntiAim.Stand.iPitch, 0, "Stand AA", "iPitch");
			SetupValue(Options.Ragebot.AntiAim.Stand.iYaw, false, "Stand AA", "iYaw");
			SetupValue(Options.Ragebot.AntiAim.Stand.iYawAdd, false, "Stand AA", "iYawAdd");
			SetupValue(Options.Ragebot.AntiAim.Stand.iFakeYaw, 0, "Stand AA", "iFakeYaw");
			SetupValue(Options.Ragebot.AntiAim.Stand.iFakeYawAdd, 0, "Stand AA", "iFakeYawAdd");
			//SetupValue(Options.Ragebot.AntiAim.Move
			SetupValue(Options.Ragebot.AntiAim.Move.bEnableAntiAim, 0, "Move AA", "bEnableAntiAim");
			SetupValue(Options.Ragebot.AntiAim.Move.bMemeWalk, 0, "Move AA", "bMemeWalk");
			SetupValue(Options.Ragebot.AntiAim.Move.bAtTargets, 0, "Move AA", "bAtTargets");
			SetupValue(Options.Ragebot.AntiAim.Move.iPitch, 0, "Move AA", "iPitch");
			SetupValue(Options.Ragebot.AntiAim.Move.iYaw, false, "Move AA", "iYaw");
			SetupValue(Options.Ragebot.AntiAim.Move.iYawAdd, false, "Move AA", "iYawAdd");
			SetupValue(Options.Ragebot.AntiAim.Move.iFakeYaw, 0, "Move AA", "iFakeYaw");
			SetupValue(Options.Ragebot.AntiAim.Move.iFakeYawAdd, 0, "Move AA", "iFakeYawAdd");
			//SetupValue(Options.Ragebot.AntiAim.Edge
			SetupValue(Options.Ragebot.AntiAim.Edge.bEnableEdge, 0, "Edge AA", "bEnableEdge");
			SetupValue(Options.Ragebot.AntiAim.Edge.iPitch, 0, "Edge AA", "iPitch");
			SetupValue(Options.Ragebot.AntiAim.Edge.iYaw, false, "Edge AA", "iYaw");
			SetupValue(Options.Ragebot.AntiAim.Edge.iYawAdd, false, "Edge AA", "iYawAdd");
			SetupValue(Options.Ragebot.AntiAim.Edge.iFakeYaw, 0, "Edge AA", "iFakeYaw");
			SetupValue(Options.Ragebot.AntiAim.Edge.iFakeYawAdd, 0, "Edge AA", "iFakeYawAdd");
			//SetupValue(Options.Ragebot.AntiAim.Misc
			SetupValue(Options.Ragebot.AntiAim.Misc.bFakeWalk, false, "AntiAim_Misc", "bFakeWalk");
			SetupValue(Options.Ragebot.AntiAim.Misc.iFakeWalkKey, 0, "AntiAim_Misc", "iFakeWalkKey");
			//SetupValue(Options.Legitbot.Aimbot.Pistols
			SetupValue(Options.Legitbot.Aimbot.Pistols.bAutoPistol, false, "Legitbot_Aimbot_Pistols", "bAutoPistol");
			SetupValue(Options.Legitbot.Aimbot.Pistols.bEnableAimbot, false, "Legitbot_Aimbot_Pistols", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Pistols.bOnKey, false, "Legitbot_Aimbot_Pistols", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Pistols.iKey, 0, "Legitbot_Aimbot_Pistols", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Pistols.bSilentAim, false, "Legitbot_Aimbot_Pistols", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Pistols.flAimbotRecoil, 0, "Legitbot_Aimbot_Pistols", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Pistols.iAimbotFov, 0, "Legitbot_Aimbot_Pistols", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Pistols.iAimbotHitbox, 0, "Legitbot_Aimbot_Pistols", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Aimbot.Rifles
			SetupValue(Options.Legitbot.Aimbot.Rifles.bEnableAimbot, false, "Legitbot_Aimbot_Rifles", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Rifles.bSilentAim, false, "Legitbot_Aimbot_Rifles", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Rifles.bOnKey, false, "Legitbot_Aimbot_Rifles", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Rifles.iKey, 0, "Legitbot_Aimbot_Rifles", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Rifles.flAimbotRecoil, 0, "Legitbot_Aimbot_Rifles", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Rifles.iAimbotFov, 0, "Legitbot_Aimbot_Rifles", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Rifles.iAimbotHitbox, 0, "Legitbot_Aimbot_Rifles", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Aimbot.Snipers
			SetupValue(Options.Legitbot.Aimbot.Snipers.bEnableAimbot, false, "Legitbot_Aimbot_Snipers", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Snipers.bSilentAim, false, "Legitbot_Aimbot_Snipers", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Snipers.bOnKey, false, "Legitbot_Aimbot_Snipers", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Snipers.iKey, 0, "Legitbot_Aimbot_Snipers", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Snipers.flAimbotRecoil, 0, "Legitbot_Aimbot_Snipers", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Snipers.iAimbotFov, 0, "Legitbot_Aimbot_Snipers", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Snipers.iAimbotHitbox, 0, "Legitbot_Aimbot_Snipers", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Aimbot.Shotguns
			SetupValue(Options.Legitbot.Aimbot.Shotguns.bEnableAimbot, false, "Legitbot_Aimbot_Shotguns", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.bSilentAim, false, "Legitbot_Aimbot_Shotguns", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.bOnKey, false, "Legitbot_Aimbot_Shotguns", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.iKey, 0, "Legitbot_Aimbot_Shotguns", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.flAimbotRecoil, 0, "Legitbot_Aimbot_Shotguns", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.iAimbotFov, 0, "Legitbot_Aimbot_Shotguns", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Shotguns.iAimbotHitbox, 0, "Legitbot_Aimbot_Shotguns", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Aimbot.Smgs
			SetupValue(Options.Legitbot.Aimbot.Smgs.bEnableAimbot, false, "Legitbot_Aimbot_Smgs", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Smgs.bSilentAim, false, "Legitbot_Aimbot_Smgs", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Smgs.bOnKey, false, "Legitbot_Aimbot_Smgs", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Smgs.iKey, 0, "Legitbot_Aimbot_Smgs", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Smgs.flAimbotRecoil, 0, "Legitbot_Aimbot_Smgs", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Smgs.iAimbotFov, 0, "Legitbot_Aimbot_Smgs", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Smgs.iAimbotHitbox, 0, "Legitbot_Aimbot_Smgs", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Aimbot.Heavy
			SetupValue(Options.Legitbot.Aimbot.Heavy.bEnableAimbot, false, "Legitbot_Aimbot_Heavy", "bEnableAimbot");
			SetupValue(Options.Legitbot.Aimbot.Heavy.bSilentAim, false, "Legitbot_Aimbot_Heavy", "bSilentAim");
			SetupValue(Options.Legitbot.Aimbot.Heavy.bOnKey, false, "Legitbot_Aimbot_Heavy", "bOnKey");
			SetupValue(Options.Legitbot.Aimbot.Heavy.iKey, 0, "Legitbot_Aimbot_Heavy", "iKey");
			SetupValue(Options.Legitbot.Aimbot.Heavy.flAimbotRecoil, 0, "Legitbot_Aimbot_Heavy", "flAimbotRecoil");
			SetupValue(Options.Legitbot.Aimbot.Heavy.iAimbotFov, 0, "Legitbot_Aimbot_Heavy", "iAimbotFov");
			SetupValue(Options.Legitbot.Aimbot.Heavy.iAimbotHitbox, 0, "Legitbot_Aimbot_Heavy", "iAimbotHitbox");
			//SetupValue(Options.Legitbot.Trigger.Pistols
			SetupValue(Options.Legitbot.Trigger.Pistols.bEnableTrigger, false, "Legitbot_Trigger_Pistols", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerOnKey, false, "Legitbot_Trigger_Pistols", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Pistols.iTriggerKey, 0, "Legitbot_Trigger_Pistols", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerRecoil, false, "Legitbot_Trigger_Pistols", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Pistols.bAutoPistol, false, "Legitbot_Trigger_Pistols", "bAutoPistol");
			SetupValue(Options.Legitbot.Trigger.Pistols.bAutoRevolver, false, "Legitbot_Trigger_Pistols", "bAutoRevolver");
			SetupValue(Options.Legitbot.Trigger.Pistols.bRevolverSecondary, false, "Legitbot_Trigger_Pistols", "bRevolverSecondary");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerFullBody, false, "Legitbot_Trigger_Pistols", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerHead, false, "Legitbot_Trigger_Pistols", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerChest, false, "Legitbot_Trigger_Pistols", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerStomach, false, "Legitbot_Trigger_Pistols", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerArms, false, "Legitbot_Trigger_Pistols", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Pistols.bTriggerLegs, false, "Legitbot_Trigger_Pistols", "bTriggerLegs");			
			//SetupValue(Options.Legitbot.Trigger.Rifles
			SetupValue(Options.Legitbot.Trigger.Rifles.bEnableTrigger, false, "Legitbot_Trigger_Rifles", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerOnKey, false, "Legitbot_Trigger_Rifles", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Rifles.iTriggerKey, 0, "Legitbot_Trigger_Rifles", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerRecoil, false, "Legitbot_Trigger_Rifles", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerFullBody, false, "Legitbot_Trigger_Rifles", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerHead, false, "Legitbot_Trigger_Rifles", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerChest, false, "Legitbot_Trigger_Rifles", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerStomach, false, "Legitbot_Trigger_Rifles", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerArms, false, "Legitbot_Trigger_Rifles", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Rifles.bTriggerLegs, false, "Legitbot_Trigger_Rifles", "bTriggerLegs");
			//SetupValue(Options.Legitbot.Trigger.Snipers
			SetupValue(Options.Legitbot.Trigger.Snipers.bEnableTrigger, false, "Legitbot_Trigger_Snipers", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerOnKey, false, "Legitbot_Trigger_Snipers", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Snipers.iTriggerKey, 0, "Legitbot_Trigger_Snipers", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Snipers.bScoped, false, "Legitbot_Trigger_Snipers", "bScoped");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerRecoil, false, "Legitbot_Trigger_Snipers", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerFullBody, false, "Legitbot_Trigger_Snipers", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerHead, false, "Legitbot_Trigger_Snipers", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerChest, false, "Legitbot_Trigger_Snipers", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerStomach, false, "Legitbot_Trigger_Snipers", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerArms, false, "Legitbot_Trigger_Snipers", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Snipers.bTriggerLegs, false, "Legitbot_Trigger_Snipers", "bTriggerLegs");
			//SetupValue(Options.Legitbot.Trigger.Shotguns
			SetupValue(Options.Legitbot.Trigger.Shotguns.bEnableTrigger, false, "Legitbot_Trigger_Shotguns", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerOnKey, false, "Legitbot_Trigger_Shotguns", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Shotguns.iTriggerKey, 0, "Legitbot_Trigger_Shotguns", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerRecoil, false, "Legitbot_Trigger_Shotguns", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerFullBody, false, "Legitbot_Trigger_Shotguns", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerHead, false, "Legitbot_Trigger_Shotguns", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerChest, false, "Legitbot_Trigger_Shotguns", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerStomach, false, "Legitbot_Trigger_Shotguns", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerArms, false, "Legitbot_Trigger_Shotguns", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Shotguns.bTriggerLegs, false, "Legitbot_Trigger_Shotguns", "bTriggerLegs");
			//SetupValue(Options.Legitbot.Trigger.Smgs
			SetupValue(Options.Legitbot.Trigger.Smgs.bEnableTrigger, false, "Legitbot_Trigger_Smgs", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerOnKey, false, "Legitbot_Trigger_Smgs", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Smgs.iTriggerKey, 0, "Legitbot_Trigger_Smgs", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerRecoil, false, "Legitbot_Trigger_Smgs", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerFullBody, false, "Legitbot_Trigger_Smgs", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerHead, false, "Legitbot_Trigger_Smgs", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerChest, false, "Legitbot_Trigger_Smgs", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerStomach, false, "Legitbot_Trigger_Smgs", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerArms, false, "Legitbot_Trigger_Smgs", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Smgs.bTriggerLegs, false, "Legitbot_Trigger_Smgs", "bTriggerLegs");
			//SetupValue(Options.Legitbot.Trigger.Heavy
			SetupValue(Options.Legitbot.Trigger.Heavy.bEnableTrigger, false, "Legitbot_Trigger_Heavy", "bEnableTrigger");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerOnKey, false, "Legitbot_Trigger_Heavy", "bTriggerOnKey");
			SetupValue(Options.Legitbot.Trigger.Heavy.iTriggerKey, 0, "Legitbot_Trigger_Heavy", "iTriggerKey");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerRecoil, false, "Legitbot_Trigger_Heavy", "bTriggerRecoil");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerFullBody, false, "Legitbot_Trigger_Heavy", "bTriggerFullBody");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerHead, false, "Legitbot_Trigger_Heavy", "bTriggerHead");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerChest, false, "Legitbot_Trigger_Heavy", "bTriggerChest");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerStomach, false, "Legitbot_Trigger_Heavy", "bTriggerStomach");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerArms, false, "Legitbot_Trigger_Heavy", "bTriggerArms");
			SetupValue(Options.Legitbot.Trigger.Heavy.bTriggerLegs, false, "Legitbot_Trigger_Heavy", "bTriggerLegs");
			//SetupValue(Options.Visuals.Esp.EspBox.
			SetupValue(Options.Visuals.Esp.EspBox.bBox, false, "Esp_EspBox", "bBox");
			SetupValue(Options.Visuals.Esp.EspBox.bHealthbar, false, "Esp_EspBox", "bHealthbar");
			SetupValue(Options.Visuals.Esp.EspBox.bHealthText, false, "Esp_EspBox", "bHealthText");
			SetupValue(Options.Visuals.Esp.EspBox.bArmorBar, false, "Esp_EspBox", "bArmorBar");
			SetupValue(Options.Visuals.Esp.EspBox.bSkeleton, false, "Esp_EspBox", "bSkeleton");
			SetupValue(Options.Visuals.Esp.EspBox.bAimlines, false, "Esp_EspBox", "bAimlines");
			SetupValue(Options.Visuals.Esp.EspBox.bPitch, false, "Esp_EspBox", "bPitch");
			SetupValue(Options.Visuals.Esp.EspBox.bYaw, false, "Esp_EspBox", "bYaw");
			//SetupValue(Options.Visuals.Esp.EspMisc.
			SetupValue(Options.Visuals.Esp.EspMisc.bWeapons, false, "Esp_EspMisc", "bWeapons");
			SetupValue(Options.Visuals.Esp.EspMisc.bAmmo, false, "Esp_EspMisc", "bAmmo");
			SetupValue(Options.Visuals.Esp.EspMisc.bName, false, "Esp_EspMisc", "bName");
			SetupValue(Options.Visuals.Esp.EspMisc.bIsScoped, false, "Esp_EspMisc", "bIsScoped");
			SetupValue(Options.Visuals.Esp.EspMisc.bIsFlashed, false, "Esp_EspMisc", "bIsFlashed");
			//SetupValue(Options.Visuals.Esp.EspFilter.
			SetupValue(Options.Visuals.Esp.EspFilter.bDroppedWeapons, false, "Esp_EspFilter", "bDroppedWeapons");
			SetupValue(Options.Visuals.Esp.EspFilter.bEnemyOnly, false, "Esp_EspFilter", "bEnemyOnly");
			SetupValue(Options.Visuals.Esp.EspFilter.bXQZ, false, "Esp_EspFilter", "bXQZ");
			SetupValue(Options.Visuals.Esp.EspFilter.bC4, false, "Esp_EspFilter", "bC4");
			SetupValue(Options.Visuals.Esp.EspFilter.bHostage, false, "Esp_EspFilter", "bHostage");
			//SetupValue(Options.Visuals.Infobox.
			SetupValue(Options.Visuals.Infobox.bInfoBox, false, "Esp_Infobox", "bInfoBox");
			SetupValue(Options.Visuals.Infobox.bInfoLby, false, "Esp_Infobox", "bInfoLby");
			SetupValue(Options.Visuals.Infobox.bInfoVelocity, false, "Esp_Infobox", "bInfoVelocity");
			SetupValue(Options.Visuals.Infobox.bInfoAngles, false, "Esp_Infobox", "bInfoAngles");
			//SetupValue(Options.Visuals.VisualsMisc.
			SetupValue(Options.Visuals.VisualsMisc.bCrosshair, false, "Visuals_VisualsMisc", "bCrosshair");
			SetupValue(Options.Visuals.VisualsMisc.bNormalCrosshair, false, "Visuals_VisualsMisc", "bNormalCrosshair");
			SetupValue(Options.Visuals.VisualsMisc.bRecoilCrosshair, false, "Visuals_VisualsMisc", "bRecoilCrosshair");
			SetupValue(Options.Visuals.VisualsMisc.bSpreadCrosshair, false, "Visuals_VisualsMisc", "bSpreadCrosshair");
			SetupValue(Options.Visuals.VisualsMisc.bNoVisualRecoil, false, "Visuals_VisualsMisc", "bNoVisualRecoil");
			SetupValue(Options.Visuals.VisualsMisc.iThirdPerson, 0, "Visuals_VisualsMisc", "iThirdPerson");
				SetupValue(Options.Visuals.VisualsMisc.iThirdPersonKey, 0, "Visuals_VisualsMisc", "iThirdPersonKey");
			SetupValue(Options.Visuals.VisualsMisc.flThirdPersonRange, 0, "Visuals_VisualsMisc", "flThirdPersonRange");
			SetupValue(Options.Visuals.VisualsMisc.bScopeRemover, false, "Visuals_VisualsMisc", "bScopeRemover");
			SetupValue(Options.Visuals.VisualsMisc.bEngineRadar, false, "Visuals_VisualsMisc", "bEngineRadar");
			SetupValue(Options.Visuals.VisualsMisc.bWatermark, true, "Visuals_VisualsMisc", "bWatermark");
			SetupValue(Options.Visuals.VisualsMisc.bTime, false, "Visuals_VisualsMisc", "bTime");
			SetupValue(Options.Visuals.VisualsMisc.bRankReveal, false, "Visuals_VisualsMisc", "bRankReveal");
			SetupValue(Options.Visuals.VisualsMisc.bHitMarker, false, "Visuals_VisualsMisc", "bHitMarker");
			SetupValue(Options.Visuals.VisualsMisc.iHitsound, 0, "Visuals_VisualsMisc", "iHitsound");
			SetupValue(Options.Visuals.VisualsMisc.iKillsound, 0, "Visuals_VisualsMisc", "iKillsound");
			SetupValue(Options.Visuals.VisualsMisc.bSpecList, false, "Visuals_VisualsMisc", "bSpecList");
			//SetupValue(Options.Visuals.VisualsWorlds.
			SetupValue(Options.Visuals.VisualsWorlds.bNoFlash, false, "Visuals_VisualsWorlds", "bNoFlash");
			SetupValue(Options.Visuals.VisualsWorlds.bNoSmoke, false, "Visuals_VisualsWorlds", "bNoSmoke");
			SetupValue(Options.Visuals.VisualsWorlds.bAsusWalls, false, "Visuals_VisualsWorlds", "bAsusWalls");
			SetupValue(Options.Visuals.VisualsWorlds.bNightMode, false, "Visuals_VisualsWorlds", "bNightMode");
			//SetupValue(Options.Visuals.Chams.
			SetupValue(Options.Visuals.Chams.bPlayers, false, "Visuals_Chams", "bPlayers");
			SetupValue(Options.Visuals.Chams.bEnemyOnly, false, "Visuals_Chams", "bEnemyOnly");
			SetupValue(Options.Visuals.Chams.bWireframe, false, "Visuals_Chams", "bWireframe");
			SetupValue(Options.Visuals.Chams.bFlat, false, "Visuals_Chams", "bFlat");
			SetupValue(Options.Visuals.Chams.bThroughWalls, false, "Visuals_Chams", "bThroughWalls");
			SetupValue(Options.Visuals.Chams.bTransparent, false, "Visuals_Chams", "bTransparent");
			SetupValue(Options.Visuals.Chams.bArms, false, "Visuals_Chams", "bArms");
			SetupValue(Options.Visuals.Chams.bArmsWireframe, false, "Visuals_Chams", "bArmsWireframe");
			SetupValue(Options.Visuals.Chams.bArmsFlat, false, "Visuals_Chams", "bArmsFlat");
			SetupValue(Options.Visuals.Chams.bArmsThroughWalls, false, "Visuals_Chams", "bArmsThroughWalls");
			SetupValue(Options.Visuals.Chams.bArmsTransparent, false, "Visuals_Chams", "bArmsTransparent");
			//SetupValue(Options.Visuals.Glow.
			//SetupValue(Options.Visuals.Glow.bEnemyOnly, false, "Visuals_Glow", "bEnemyOnly");
			//SetupValue(Options.Visuals.Glow.bC4Carrier, false, "Visuals_Glow", "bC4Carrier");
			//SetupValue(Options.Visuals.Glow.bChickens, false, "Visuals_Glow", "bChickens");
			//SetupValue(Options.Visuals.Glow.bDefuseKits, false, "Visuals_Glow", "bDefuseKits");
			//SetupValue(Options.Visuals.Glow.bEnabled, false, "Visuals_Glow", "bEnabled");
			//SetupValue(Options.Visuals.Glow.bPlantedC4, false, "Visuals_Glow", "bPlantedC4");
			//SetupValue(Options.Visuals.Glow.bPlayers, false, "Visuals_Glow", "bPlayers");
			//SetupValue(Options.Visuals.Glow.bWeapons, false, "Visuals_Glow", "bWeapons");
			//SetupValue(Options.Misc.Misc1.
			SetupValue(Options.Misc.Misc1.iFakeLag, 0, "Misc_Misc1", "iFakeLag");
			SetupValue(Options.Misc.Misc1.iFakeLagFactor, 0, "Misc_Misc1", "iFakeLagFactor");
			SetupValue(Options.Misc.Misc1.bInAirOnly, false, "Misc_Misc1", "bInAirOnly");
			//SetupValue(Options.Misc.Misc1.bAutoAccpet, false, "Misc_Misc1", "bAutoAccpet");
			SetupValue(Options.Misc.Misc1.bClanTag, false, "Misc_Misc1", "bClanTag");
			SetupValue(Options.Misc.Misc1.iClanTagSelection, 0, "Misc_Misc1", "iClanTagSelection");
			SetupValue(Options.Misc.Misc1.bClanTagAnimation, false, "Misc_Misc1", "bClanTagAnimation");
			SetupValue(Options.Misc.Misc1.bCorruption, false, "Misc_Misc1", "bCorruption");
			SetupValue(Options.Misc.Misc1.bFreeCam, false, "Misc_Misc1", "bFreeCam");
			SetupValue(Options.Misc.Misc1.flFreeCamSpeed, 5, "Misc_Misc1", "flFreeCamSpeed");
			SetupValue(Options.Misc.Misc1.iFreeCamKey, 0, "Misc_Misc1", "iFreeCamKey");
			//SetupValue(Options.Misc.Misc2
			SetupValue(Options.Misc.Misc2.bAntiUntrusted, false, "Misc_Misc2", "bAntiUntrusted");
			SetupValue(Options.Misc.Misc2.bChatSpam, false, "Misc_Misc2", "bChatSpam");
			SetupValue(Options.Misc.Misc2.iNameSpam, 0, "Misc_Misc2", "iNameSpam");
			SetupValue(Options.Misc.Misc2.bKnifeBot, false, "Misc_Misc2", "bKnifeBot");
			SetupValue(Options.Misc.Misc2.bBlockBot, false, "Misc_Misc2", "bBlockBot");
			SetupValue(Options.Misc.Misc2.iBlockBotKey, 0, "Misc_Misc2", "iBlockBotKey");
			SetupValue(Options.Misc.Misc2.bEnableFov, false, "Misc_Misc2", "bEnableFov");
			SetupValue(Options.Misc.Misc2.flFovValue, 90.f, "Misc_Misc2", "flFovValue");
			SetupValue(Options.Misc.Misc2.flViewModelValue, 30.f, "Misc_Misc2", "flViewModelValue");
			//SetupValue(Options.Misc.Movement.
			SetupValue(Options.Misc.Movement.bAutoJump, false, "Misc_Movement", "bAutoJump");
			SetupValue(Options.Misc.Movement.bAutoStrafe, false, "Misc_Movement", "bAutoStrafe");
			SetupValue(Options.Misc.Movement.iAutoStrafeMode, 0, "Misc_Movement", "iAutoStrafeMode");
			SetupValue(Options.Misc.Movement.bZStrafe, false, "Misc_Movement", "bZStrafe");
			SetupValue(Options.Misc.Movement.iZStrafeKey, false, "Misc_Movement", "iZStrafeKey");
			SetupValue(Options.Misc.Movement.iCircleStraferMode , 0, "Misc_Movement", "iCircleStraferMode");
			SetupValue(Options.Misc.Movement.iCircleStraferKey, 20, "Misc_Movement", "iCircleStraferKey");
			SetupValue(Options.Misc.Movement.bAirStuck, false, "Misc_Movement", "bAirStuck");
			SetupValue(Options.Misc.Movement.iAirStuck, 0, "Misc_Movement", "iAirStuck");
			SetupValue(Options.Misc.Movement.iAirStuckKey, 0, "Misc_Movement", "iAirStuckKey");
			SetupValue(Options.Misc.Movement.bSlowmotion, false, "Misc_Movement", "bSlowmotion");
			SetupValue(Options.Misc.Movement.iSlowMotionKey, 0, "Misc_Movement", "iSlowMotionKey");
			SetupValue(Options.Misc.Movement.bWalkBot, false, "Misc_Movement", "bWalkBot");
			SetupValue(Options.Misc.Movement.bBunnyhop, false, "Misc_Movement", "bBunnyhop");
			SetupValue(Options.Misc.Movement.flDistance, 0, "Misc_Movement", "flDistance");
			SetupValue(Options.Misc.Movement.iTurn, 0, "Misc_Movement", "iTurn");
			//COLORS
			SetupValue(Options.Col.espVisT[0], 0.9f, "Colors", "espVisT1");
			SetupValue(Options.Col.espVisT[1], 0.f, "Colors", "espVisT2");
			SetupValue(Options.Col.espVisT[2], 0.f, "Colors", "espVisT3");

			SetupValue(Options.Col.espInvisT[0], 0.9f, "Colors", "espInvisT1");
			SetupValue(Options.Col.espInvisT[1], 0.4f, "Colors", "espInvisT2");
			SetupValue(Options.Col.espInvisT[2], 0.f, "Colors", "espInvisT3");

			SetupValue(Options.Col.espVisCT[0], 0.f, "Colors", "espVisCT1");
			SetupValue(Options.Col.espVisCT[1], 0.f, "Colors", "espVisCT2");
			SetupValue(Options.Col.espVisCT[2], 0.9f, "Colors", "espVisCT3");

			SetupValue(Options.Col.espInvisCT[0], 0.f, "Colors", "espInvisCT1");
			SetupValue(Options.Col.espInvisCT[1], 0.4f, "Colors", "espInvisCT2");
			SetupValue(Options.Col.espInvisCT[2], 0.9f, "Colors", "espInvisCT3");

			SetupValue(Options.Col.chamsPlyrTVis[0], 0.9f, "Colors", "chamsPlyrTVis1");
			SetupValue(Options.Col.chamsPlyrTVis[1], 0.f, "Colors", "chamsPlyrTVis2");
			SetupValue(Options.Col.chamsPlyrTVis[2], 0.f, "Colors", "chamsPlyrTVis3");

			SetupValue(Options.Col.chamsPlyrTInvis[0], 0.9f, "Colors", "chamsPlyrTInvis1");
			SetupValue(Options.Col.chamsPlyrTInvis[1], 0.4f, "Colors", "chamsPlyrTInvis2");
			SetupValue(Options.Col.chamsPlyrTInvis[2], 0.f, "Colors", "chamsPlyrTInvis3");

			SetupValue(Options.Col.chamsPlyrCTVis[0], 0.f, "Colors", "chamsPlyrCTVis1");
			SetupValue(Options.Col.chamsPlyrCTVis[1], 0.f, "Colors", "chamsPlyrCTVis2");
			SetupValue(Options.Col.chamsPlyrCTVis[2], 0.9f, "Colors", "chamsPlyrCTVis3");

			SetupValue(Options.Col.chamsPlyrCTInvis[0], 0.f, "Colors", "chamsPlyrCTInvis1");
			SetupValue(Options.Col.chamsPlyrCTInvis[1], 0.4f, "Colors", "chamsPlyrCTInvis2");
			SetupValue(Options.Col.chamsPlyrCTInvis[2], 0.9f, "Colors", "chamsPlyrCTInvis3");

			SetupValue(Options.Col.chamsHandsVis[0], 0.4f, "Colors", "chamsHandsVis1");
			SetupValue(Options.Col.chamsHandsVis[1], 0.2f, "Colors", "chamsHandsVis2");
			SetupValue(Options.Col.chamsHandsVis[2], 1.f, "Colors", "chamsHandsVis3");

			SetupValue(Options.Col.chamsHandsInvis[0], 1.f, "Colors", "chamsHandsInvis1");
			SetupValue(Options.Col.chamsHandsInvis[0], .2f, "Colors", "chamsHandsInvis2");
			SetupValue(Options.Col.chamsHandsInvis[0], .4f, "Colors", "chamsHandsInvis3");
}

void CConfig::SetupValue(int& value, int def, std::string category, std::string name)
{
	value = def;
	ints.push_back(new ConfigValue< int >(category, name, &value));
}

void CConfig::SetupValue(float& value, float def, std::string category, std::string name)
{
	value = def;
	floats.push_back(new ConfigValue< float >(category, name, &value));
}

void CConfig::SetupValue(bool& value, bool def, std::string category, std::string name)
{
	value = def;
	bools.push_back(new ConfigValue< bool >(category, name, &value));
}

void CConfig::Save()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\Astrium\\";
		file = std::string(path) + "\\Astrium\\config.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	for (auto value : ints)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : floats)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), std::to_string(*value->value).c_str(), file.c_str());

	for (auto value : bools)
		WritePrivateProfileString(value->category.c_str(), value->name.c_str(), *value->value ? "true" : "false", file.c_str());
}

void CConfig::Load()
{
	static TCHAR path[MAX_PATH];
	std::string folder, file;

	if (SUCCEEDED(SHGetFolderPath(NULL, CSIDL_APPDATA, NULL, 0, path)))
	{
		folder = std::string(path) + "\\Astrium\\";
		file = std::string(path) + "\\Astrium\\config.ini";
	}

	CreateDirectory(folder.c_str(), NULL);

	char value_l[32] = { '\0' };

	for (auto value : ints)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atoi(value_l);
	}

	for (auto value : floats)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = atof(value_l);
	}

	for (auto value : bools)
	{
		GetPrivateProfileString(value->category.c_str(), value->name.c_str(), "", value_l, 32, file.c_str());
		*value->value = !strcmp(value_l, "true");
	}
}

CConfig* Config = new CConfig();
//cOptions Options;