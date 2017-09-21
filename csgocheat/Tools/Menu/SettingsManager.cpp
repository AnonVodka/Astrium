#include "../../stdafx.h"
#include "SettingsManager.h"
#include <wininet.h>
#pragma comment(lib, "wininet")
/*
double SettingsArray[20][200][26];

SettingsManger Settings;
int currentgroup = 1;
int oldgroup = -1;
int weaponconfigTab = Group_Default;

bool SettingsManger::weaponconfigs()
{
if (Settings.GetSetting(Tab_Misc, Misc_WeaponConfigs))
{
if (Hacks.LocalWeapon->isSniper())
{
if (Hacks.LocalWeapon->isAWP())
{
currentgroup = Group_AWP;
}
else if (Hacks.LocalWeapon->isScout())
{
currentgroup = Group_Scout;
}
else if (Hacks.LocalWeapon->isDak())
{
currentgroup = Group_Dak;
}
}
else if (Hacks.LocalWeapon->isRifle())
{
currentgroup = Group_Rifle;
}
else if (Hacks.LocalWeapon->isSmgW())
{
currentgroup = Group_SMG;
}
else if (Hacks.LocalWeapon->isPistol())
{
currentgroup = Group_Pistol;
weaponconfigTab = Group_Pistol;
}
else if (Hacks.LocalWeapon->isShotgun())
{
currentgroup = Group_Shotgun;
}
else if (Hacks.LocalWeapon->isMachineW())
{
currentgroup = Group_Heavy;
}
Settings.SetSetting(Tab_Misc, Misc_WeaponConfigs, 1);
if (currentgroup != oldgroup)
{
oldgroup = currentgroup;
weaponconfigTab = currentgroup;
return true;
}
else
{
return false;
}
}
else
{
currentgroup = Group_Default;
weaponconfigTab = Group_Default;
return false;
}
}

void SettingsManger::SetSetting(int Tab, int Setting, double Value)
{
int someweaponvalue = 0;
if (Tab == Tab_Ragebot)
{
if (Settings.GetSetting(Tab_Misc, Misc_WeaponConfigs))
{
if (Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 9)
{
someweaponvalue = weaponconfigTab;
}
else
{
someweaponvalue = Settings.GetSetting(Tab_Misc, Misc_WhichWeapon);
}
}
}
SettingsArray[Tab][Setting][someweaponvalue] = Value;
}

double SettingsManger::GetSetting(int Tab, int Setting)
{
int someweaponvalue = 0;
if (Tab == Tab_Ragebot)
someweaponvalue = weaponconfigTab;

return SettingsArray[Tab][Setting][someweaponvalue];
}

double SettingsManger::GetSettingLegit(int Tab, int Setting)
{
int someweaponvalue = 0;
if (Tab == Tab_LegitBot)
{
if (Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 9)
{
if (Hacks.LocalWeapon && Hacks.LocalPlayer->isAlive())
{
someweaponvalue = *Hacks.LocalWeapon->GetItemDefinitionIndex() + 11;
}
else
{
someweaponvalue = currentgroup;
}
}
else
{
someweaponvalue = currentgroup;
}
}


return SettingsArray[Tab][Setting][someweaponvalue];
}

double SettingsManger::GetMenuSetting(int Tab, int Setting)
{
int someweaponvalue = 0;
if (Tab == Tab_Ragebot)
{
if (Settings.GetSetting(Tab_Misc, Misc_WeaponConfigs))
{
if (Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 0 || Settings.GetSetting(Tab_Misc, Misc_WhichWeapon) == 9)
{
someweaponvalue = weaponconfigTab;
}
else
{
someweaponvalue = Settings.GetSetting(Tab_Misc, Misc_WhichWeapon);
}
}
}

return SettingsArray[Tab][Setting][someweaponvalue];
}

void loadSettings(std::string settings)
{
// sets up settings char to a vector looks like this "0:3:2:2" ie tab-setting-value
std::string tovector = settings;

std::stringstream ss(tovector);
std::istream_iterator< std::string > begin(ss);
std::istream_iterator< std::string > end;
std::vector< std::string > settingarray(begin, end);
//Gets how many settings to set
int size = settingarray.size();
for (auto i = 0; i < size - 1; i++)
{
// Gets the setting we are dealing with
string meme = settingarray[i];
//Converst the string to char array
for (auto i = 0; i < meme.length(); i++)
{
if (meme[i] == ':')
meme[i] = ' ';
}
vector< double > indi;
stringstream ss(meme);
double temp;
while (ss >> temp)
indi.push_back(temp);
//0:1:2:8
// Sets the setting
SettingsArray[static_cast< int >(indi[0])][static_cast< int >(indi[1])][static_cast< int >(indi[2])] = static_cast< double >(indi[3]);
}
}

void savesets()
{
int number = Settings.GetSetting(Tab_Misc, Config_type);
//int number1 = Settings.GetSetting(Tab_LegitBot, Config_type);
//int number2 = Settings.GetSetting(Tab_Visuals, Config_type);
//int number3 = Settings.GetSetting(Tab_Ragebot, Config_type);
//int number4 = Settings.GetSetting(Tab_Config, Config_type);

if (CreateDirectory("C:/Astrium", nullptr) || ERROR_ALREADY_EXISTS == GetLastError())
{
}
std::string savetype = "c:/Astrium/save";
savetype.append(to_string(number));
savetype.append(".txt");

string txt;
ifstream file(savetype);

if (file.is_open())
while (file.good())
getline(file, txt);
file.close();
//#ifdef DEBUG
cout << txt << endl;

//#endif // DEBUG

loadSettings(txt);
}

void writefile(std::string string)
{
int number = Settings.GetSetting(Tab_Misc, Config_type);

if (CreateDirectory("C:/Astrium/", nullptr) || ERROR_ALREADY_EXISTS == GetLastError())
{
}
std::string savetype = "c:/Astrium/save";
savetype.append(to_string(number));
savetype.append(".txt");
ofstream myfile;
myfile.open(savetype);
myfile << string;
myfile.close();
cout << 1 << endl;
//CreateThread(0, 0, (LPTHREAD_START_ROUTINE)upload, 0, 0, 0);
cout << 2 << endl;
}

std::string settingstostring()
{
std::string stra;
int val = MAXVALUEMENU - 1;

for (int i = 0; i < val; i++)
{
int mena = 1;
switch (i)
{
case 0:
mena = MAXVALUERAGE;
break;
case 1:
mena = MAXVALUEVISUALS;
break;
case 2:
mena = MAXVALUEMISC;
break;
case 3:
mena = MAXVALUELEGITBOT;
break;
case 4:
mena = MAXVALUECOLORSMENU;
break;
case 5:
mena = MAXVALUESKINS;
break;
case 6:
mena = MAXVALUEWEAPONGROUPS;
break;

}
for (int a = 0; a < mena; a++)
{
double settingval;
if (i == 1 || i == 0)
{
for (int c = 0; c < 9; c++)
{
stra.append(to_string(i));
stra.append(":");
stra.append(to_string(a));
stra.append(":");
settingval = SettingsArray[i][a][c];
stra.append(to_string(c));
stra.append(":");
stra.append(to_string(settingval));
stra.append(" ");
}
}
else
{
stra.append(to_string(i));
stra.append(":");
stra.append(to_string(a));
stra.append(":");
settingval = SettingsArray[i][a][0];
stra.append(to_string(0));
stra.append(":");
stra.append(to_string(settingval));
stra.append(" ");
}
}
}
//#ifdef DEBUG
cout << "Saving" << endl;

cout << stra << endl;
//#endif
writefile(stra);

return stra;
}
*/

//void ForcePreload()
//{
//	static ConVar* Meme = Interfaces.g_ICVars->FindVar("cl_fullupdate");
//	Meme->nFlags &= ~FCVAR_CHEAT;
//	Interfaces.pEngine->ClientCmd_Unrestricted("cl_fullupdate", NULL);
//}
//
//void Restore()
//{
//
//}
//
//void LoadRage()
//{
//
//}
//
//void LoadHvH()
//{
//
//}
//
//void LoadLegit()
//{
//
//}