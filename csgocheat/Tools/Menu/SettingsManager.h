#pragma once
#include "../../stdafx.h"

//Don't change the location of max value, always at the end.
//And also add new vars to bottom of lists or it will cause problems in cfgs.
//Skeltal is the cutest
//enum MenuTabs
//{
//	Tab_Ragebot = 0,
//	Tab_LegitBot,
//	Tab_Visuals,
//	Tab_Misc,
//	Tab_Skins,
//	Tab_Colors,
//	MAXVALUEMENU
//};
//
//enum Config
//{
//	Config_save,
//	Config_load,
//	Config_type,
//};
///*
//enum RagebotTab
//{
//Ragebot_AimbotEnabled,
//Ragebot_Selection,
//Ragebot_FovSlider,
//Ragebot_Hitbox,
//Ragebot_Multipoint,
//Ragebot_PS,
//Ragebot_Multibox,
//Ragebot_Velocity,
//Ragebot_AutoShoot,
//Ragebot_Autoscope,
//Ragebot_SilentAim,
//Ragebot_pSilent,
//Ragebot_Hitchance,
//Ragebot_MinDamage,
//Ragebot_AcceptKill,
//Ragebot_Resolver,
//Ragebot_Resolver_Mode,
//Resolver_Switch,
//Ragebot_AntiAimCorrection,
//Ragebot_Accuracy,
//Ragebot_PreferBodyAim,
//Ragebot_PositionAdjustment,
//Ragebot_EnginePrediction,
//Ragebot_MultipointType,
//Ragebot_Autorevolver,
//Ragebot_NoRecoil,
//
//AntiAim_Enabled,
//AntiAim_Switch,
//AntiAim_Pitch,
//AntiAim_Real_Yaw,
//AntiAim_FakeHitbox,
//AntiAim_AtTargets,
//AntiAim_EdgeDetection,
//AntiAim_LegitTroll,
//AntiAim_MMSafe,
//AntiAim_MemeWalk,
//AntiAim_AntiResolver,
//
//AntiAim_Enabled_Move,
//AntiAim_Switch_Move,
//AntiAim_Pitch_Move,
//AntiAim_Real_Yaw_Move,
//AntiAim_FakeHitbox_Move,
//AntiAim_AtTargets_Move,
//AntiAim_EdgeDetection_Move,
//AntiAim_LegitTroll_Move,
//AntiAim_MMSafe_Move,
//AntiAim_MemeWalk_Move,
//AntiAim_AntiResolver_Move,
//
//AntiAim_Enabled_Jump,
//AntiAim_Switch_Jump,
//AntiAim_Pitch_Jump,
//AntiAim_Real_Yaw_Jump,
//AntiAim_FakeHitbox_Jump,
//AntiAim_AtTargets_Jump,
//AntiAim_EdgeDetection_Jump,
//AntiAim_LegitTroll_Jump,
//AntiAim_MMSafe_Jump,
//AntiAim_MemeWalk_Jump,
//AntiAim_AntiResolver_Jump,
//
//Ragebot_AutoStop,
//Ragebot_AutoStop_Key,
//MAXVALUERAGE
//};
///*
//enum Visualstab
//{
//Visuals_Enable,
//Visuals_BoxEnabled,
//Visuals_BoxType,
//Visuals_FilledBoxAlpha,
//Visuals_EspTeam,
//Visuals_HeadEsp,
//Visuals_HealthBar,
//Visuals_ArmorBar,
//Visuals_Name,
//Visuals_Flashed,
//Visuals_Weapons,
//Visuals_AimLines,
//Visuals_Skeltal,
//Visuals_Ammo,
//Visuals_EngineRadar,
//Visuals_Hostage,
//Visuals_BarrelESP,
//Visuals_DroppedWeapons,
//Visuals_InfoBox,
//Visuals_InfoLBY,
//Visuals_InfoVel,
//Visuals_InfoAngs,
//Visuals_NoRecoil,
//Visuals_NoFlash,
//Visuals_NoSmoke,
//Visuals_ThirdPerson,
//Visuals_Thirdpersonkey,
//Visuals_ThirdPerson_OnKey,
//Visuals_ThirdPerson_Key,
//Visuals_NoScope,
//Visuals_Chams,
//Visuals_Chams_Player,
//Visuals_Chams_Weapons,
//Visuals_ChamsXQZ,
//Visuals_ChamsTeam,
//Visuals_ChamsGuns,
//Visuals_XQZ,
//Visuals_Crosshair,
//Visuals_CrosshairDynamic,
//Visuals_CrosshairSpread,
//Visuals_C4,
//Visuals_Flags,
//Visuals_Dlights,
//Visuals_Watermark,
//Visuals_Enable_MapVisuals,
//Visuals_MapMode,
//Visuals_Hitmarker,
//Visuals_Nightmode,
//Visuals_Asuswalls,
//Visuals_Skyboxchanger,
//Visuals_BrightnessAdjustments,
//Visuals_RGBSelector,
//Visuals_R,
//Visuals_G,
//Visuals_B,
//Visuals_SliderMovement,
//Visuals_GrenadePrediction,
//Visuals_BarPos,
//Visuals_Scoped,
//MAXVALUEVISUALS
//};
//
//enum MiscTab
//{
//Misc_WeaponConfigs,
//Misc_WhichWeapon,
//Misc_AntiUntrusted,
//Misc_AutoJump,
//Misc_AutoStrafe,
//Misc_AutoStraferMode,
//Misc_ClanTagSpammer,
//Misc_ClanTagSelection,
//Misc_ClanTagAnimate,
//Misc_AutoAccept,
//Misc_FakeLag,
//Misc_Aimstep,
//Misc_ZStrafe,
//Misc_ZStrafeKey,
//Misc_CircleStrafe,
//Misc_CircleStrafeKey,
//Misc_UI,
//Misc_KnifeBot,
//Misc_BlockBot,
//Misc_BlockBot_Key,
//Misc_Fov,
//Misc_Config_save,
//Misc_Config_load,
//Misc_Config_type,
//Misc_Chatspam,
//Misc_Menukeyenable,
//Misc_Menukey,
//Misc_RankReveal,
//Misc_Freecam,
//Misc_Freecam_Key,
//Misc_Freecam_Speed,
//Misc_Fakewalk,
//Misc_Fakewalk_Key,
//Misc_Slowmotion,
//Misc_Slowmotion_Key,
//Misc_Slowmotion_Speed,
//Misc_ViewmodelChanger,
//Misc_ViewmodelValue,
//Misc_FovEnabled,
//Misc_FovValue,
//Misc_DummyOther,
//Misc_Airstuck_Enable,
//Misc_Airstuck_Key,
//Misc_Playerbox,
//MAXVALUEMISC
//};
//
//enum LegitBot
//{
//Legitbot_enable,
//Legitbot_hitbox,
//
//Legitbot_multihitbox,
//Legitbot_rcsforceX,
//Legitbot_fov,
//Legitbot_rcsforceY,
//Legitbot_smoothX,
//Legitbot_smoothY,
//Legitbot_Firedelay,
//
//Legitbot_Aimonkey,
//Legitbot_Aimbotkey,
//
//Legit_Activate,
//Legit_Aimbot_Key,
//
//Legit_Normal_Active,
//Legit_Normal_FOV,
//Legit_Normal_SelectionBone,
//Legit_Normal_SelectionType,
//Legit_Normal_Speed,
//Legit_Normal_Curve,
//Legit_Normal_AimTime,
//
//Legit_SA_Amount,
//Legit_SA_FOV,
//Legit_SA_SelectionBone,
//Legit_SA_SelectionType,
//Legit_SA_Speed,
//Legit_SA_Curve,
//Legit_SA_AimTime,
//
//
//Legit_RCS_Enable,
//Legit_RCS_X,
//Legit_RCS_Y,
//Legit_RCS_Type,
//
//Legit_SlowAim_Active,
//Legit_SlowAim_Type,
//Legit_SlowAim_Amount,
//Legit_SlowAim_FOV,
//Legit_SlowAim_Bone,
//
//Legit_TargetDelay,
//
//Trigger_Active,
//Trigger_Type,
//Trigger_Key,
//Trigger_Hitboxs,
//Trigger_Delay,
//Trigger_After,
//Trigger_Check_Scope,
//
//Trigger_Magnet_Active,
//Trigger_Magnet_FOV,
//Trigger_Magnet_SelectionBone,
//Trigger_Magnet_SelectionType,
//Trigger_Magnet_Speed,
//Trigger_Magnet_Curve,
//Trigger_Magnet_AimTime,
//
//Trigger_Magnet,
//
//Legit_Random,
//LegitBot_ME,
//Legit_HsPer,
//Legit_IgnoreInAir,
//Legit_AimPause,
//Legit_FireDelay,
//
//Trigger_Lock_Active,
//Trigger_Lock_Smooth,
//Trigger_Lock_Strength,
//Trigger_Lock_Key,
//Legit_RCS_Smooth,
//Legit_ME,
//Legit_typeofaim,
//
//MAXVALUELEGITBOT
//};
//
//enum ColorsTabMenu
//{
//Colors_ESP_R,
//Colors_ESP_G,
//Colors_ESP_B,
//
//Colors_Interface_R,
//Colors_Interface_G,
//Colors_Interface_B,
//
//Colors_Arabic_R,
//Colors_Arabic_G,
//Colors_Arabic_B,
//
//Colors_TextArabic_R,
//Colors_TextArabic_G,
//Colors_TextArabic_B,
//
//Colors_Tabs_R,
//Colors_Tabs_G,
//Colors_Tabs_B,
//
//Colors_CurrentTab_R,
//Colors_CurrentTab_G,
//Colors_CurrentTab_B,
//
//Chams_CT_Visible_R,
//Chams_CT_Visible_G,
//Chams_CT_Visible_B,
//
//Chams_CT_Invisible_R,
//Chams_CT_Invisible_G,
//Chams_CT_Invisible_B,
//
//Chams_T_Visible_R,
//Chams_T_Visible_G,
//Chams_T_Visible_B,
//
//Chams_T_Invisible_R,
//Chams_T_Invisible_G,
//Chams_T_Invisible_B,
//
//Esp_CT_R,
//Esp_CT_G,
//Esp_CT_B,
//
//Esp_T_R,
//Esp_T_G,
//Esp_T_B,
//
//DummyMeme,
//MAXVALUECOLORSMENU
//};
//
//enum SkinsTab
//{
//Skins_Enable,
//Skins_Knife,
//Skins_Knife_Skin,
//Skins_Knife_Float,
//
//Skins_Glove,
//Skins_Glove_Skin,
//Skins_Glove_Float,
//
//Skins_Pistol,
//Skins_Pistol_Skin,
//Skins_Pistol_Float,
//
//Skins_Famas,
//Skins_Galil,
//Skins_M4a4,
//Skins_M4a1,
//Skins_Ak47,
//Skins_Aug,
//Skins_SG553,
//Skins_Rifles_Float,
//
//Skins_Sniper,
//Skins_Sniper_Skin,
//Skins_Sniper_Float,
//MAXVALUESKINS
//};
//*/
//enum weapongroups
//{
//	Group_Default = 0,
//	Group_Rifle,
//	Group_Pistol,
//	Group_Dak,
//	Group_AWP,
//	Group_Scout,
//	Group_Shotgun,
//	Group_SMG,
//	Group_Heavy,
//
//	MAXVALUEWEAPONGROUPS
//};
//
//class SettingsManger
//{
//public:
//	//bool weaponconfigs();
//
//	//	static void SetSetting( int Tab, int Setting, double Value );
//
//	//	static double GetSetting( int Tab, int Setting );
//
//	//	static double GetSettingLegit(int Tab, int Setting);
//
//	//	double GetPlayer( int index, int Tab, int Setting );
//
//	//	static double GetMenuSetting( int Tab, int Setting );
//};
//
//extern SettingsManger Settings;
