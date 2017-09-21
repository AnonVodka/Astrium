//#include "../../stdafx.h"
////#include "SettingsManager.h"
//#include "Menu.h"
//
//int MenuRed;
//int MenuGreen;
//int MenuBlue;
//int MenuAlpha;
//int TextRed;
//int TextGreen;
//int TextBlue;
//int TextAlpha;
//int BackgroundRed;
//int BackgroundGreen;
//int BackgroundBlue;
//int BackgroundAlpha;
//int OutlineRed;
//int OutlineGreen;
//int OutlineBlue;
//int OutlineAlpha;
//
//float GlobalMenuAlpha = 0.f;
//
//bool IsMouseInRegion(int x, int y, int x2, int y2)
//{
//	POINT Mouse;
//	POINT mp;
//
//	GetCursorPos(&mp);
//	ScreenToClient(GetForegroundWindow(), &mp);
//	Mouse.x = mp.x;
//	Mouse.y = mp.y;
//
//	if (Mouse.x > x && Mouse.y > y && Mouse.x < x2 && Mouse.y < y2)
//		return true;
//	else
//		return false;
//}
//
//bool rIsMouseInRegion(RECT region)
//{
//	return IsMouseInRegion(region.left, region.top, region.left + region.right, region.top + region.bottom);
//}
//
//void Text(int x, int y, Color color, DWORD font, const char* text)
//{
//	size_t origsize = strlen(text) + 1;
//	const size_t newsize = 100;
//	size_t convertedChars = 0;
//	wchar_t wcstring[newsize];
//	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);
//
//	Interfaces.pSurface->DrawSetTextFont(font);
//
//	Interfaces.pSurface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
//	Interfaces.pSurface->DrawSetTextPos(x, y);
//	Interfaces.pSurface->DrawPrintText(wcstring, wcslen(wcstring));
//	return;
//}
//
//void Line(int x, int y, int x2, int y2, Color color)
//{
//	Interfaces.pSurface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
//	Interfaces.pSurface->DrawLine(x, y, x2, y2);
//}
//
//RECT pGetTextSize(DWORD font, const char* text)
//{
//	size_t origsize = strlen(text) + 1;
//	const size_t newsize = 100;
//	size_t convertedChars = 0;
//	wchar_t wcstring[newsize];
//	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);
//
//	RECT rect; int x, y;
//	Interfaces.pSurface->GetTextSize(font, wcstring, x, y);
//	rect.left = x; rect.bottom = y;
//	rect.right = x;
//	return rect;
//}
//
//void DrawRect(int x, int y, int w, int h, Color col)
//{
//	Interfaces.pSurface->DrawSetColor(col.r(), col.g(), col.b(), col.a());
//	Interfaces.pSurface->DrawFilledRect(x, y, x + w, y + h);
//}
//
//int TweakColor(int c1, int c2, int variation)
//{
//	if (c1 == c2)
//		return c1;
//	else if (c1 < c2)
//		c1 += variation;
//	else
//		c1 -= variation;
//	return c1;
//}
//
//void GradientSideways(int x, int y, int w, int h, Color color1, Color color2, int variation)
//{
//	int r1 = color1.r();
//	int g1 = color1.g();
//	int b1 = color1.b();
//	int a1 = color1.a();
//
//	int r2 = color2.r();
//	int g2 = color2.g();
//	int b2 = color2.b();
//	int a2 = color2.a();
//
//	for (int i = 0; i <= w; i++)
//	{
//		DrawRect(x + i, y, 1, h, Color(r1, g1, b1, a1));
//		r1 = TweakColor(r1, r2, variation);
//		g1 = TweakColor(g1, g2, variation);
//		b1 = TweakColor(b1, b2, variation);
//		a1 = TweakColor(a1, a2, variation);
//	}
//}
//
////void Clear(int x, int y, int w, int h, Color color)
////{
////	Interfaces.pSurface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
////	Interfaces.pSurface->DrawFilledRect(x, y, x + w, y + h);
////}
//
///*void GradientV(int x, int y, int w, int h, Color c1, Color c2)
//{
//Clear(x, y, w, h, c1);
//BYTE first = c2.r();
//BYTE second = c2.g();
//BYTE third = c2.b();
//for (int i = 0; i < h; i++)
//{
//float fi = i, fh = h;
//float a = fi / fh;
//DWORD ia = a * 255;
//Clear(x, y + i, w, 1, Color(first, second, third, ia));
//}
//}*/
//
//void Outline(int x, int y, int w, int h, Color color)
//{
//	Interfaces.pSurface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
//	Interfaces.pSurface->DrawOutlinedRect(x, y, x + w, y + h);
//}
//
//void DrawMenuBase()
//{
//	//int height = 500;
//	int height = 500;
//	int width = 618;
//
//	//WINDOW
//	Clear(Menu.pos.x + 8, Menu.pos.y + 1, width - 4 - 12, height - 2 - 8 - 26, Color(28, 28, 28, GlobalMenuAlpha));
//	Clear(Menu.pos.x + 8, Menu.pos.y + 1 - 6, width - 4 - 12, 6, Color(40, 40, 40, GlobalMenuAlpha));
//	Clear(Menu.pos.x + 8, Menu.pos.y + 1 + height - 2 - 8 - 26, width - 4 - 12, 6, Color(40, 40, 40, GlobalMenuAlpha));
//	Clear(Menu.pos.x + 8 - 6, Menu.pos.y + 1 - 6, 6, height - 2 - 8 - 26 + 12, Color(40, 40, 40, GlobalMenuAlpha));
//	Clear(Menu.pos.x + 8 + width - 4 - 12, Menu.pos.y + 1 - 6, 6, height - 2 - 8 - 26 + 12, Color(40, 40, 40, GlobalMenuAlpha));
//
//	int red = 70;
//	int green = 70;
//	int blue = 255;
//
//	//Tab area
//	Clear(Menu.pos.x + 8, Menu.pos.y + 1, 90, height - 2 - 8 - 26, Color(21, 21, 21, GlobalMenuAlpha));
//	//--------------
//	Outline(Menu.pos.x + 8, Menu.pos.y + 1, width - 4 - 12, height - 2 - 8 - 26, Color(48, 48, 48, GlobalMenuAlpha));
//	//Render::Clear(window->m_x + 8, window->m_y + 1 + 28 * 2, 1, window->m_iHeight - 2 - 8 - 26 - 1, Color(129, 129, 129, 255));
//	Outline(Menu.pos.x + 8 - 6, Menu.pos.y + 1 - 6, width - 4 - 12 + 12, height - 2 - 8 - 26 + 12, Color(48, 48, 48, GlobalMenuAlpha));
//	Outline(Menu.pos.x + 8, Menu.pos.y + 1, 90, height - 2 - 8 - 26, Color(48, 48, 48, GlobalMenuAlpha));
//	Line(Menu.pos.x + 97, Menu.pos.y + 2, Menu.pos.x + 97, (Menu.pos.y + 1) + (height - 37), Color(244, 244, 244, GlobalMenuAlpha));
//	//Line(Menu.pos.x + 98, Menu.pos.y + 1, Menu.pos.x + 98, (Menu.pos.y + 1) + (height - 36), Color(red, green, blue, GlobalMenuAlpha));
//
//	//skeet bar
//
//	static float rainbowr;
//	rainbowr += 0.8;
//	if (rainbowr > 255.f) rainbowr = 40.f;
//
//	static float rainbowg;
//	rainbowg += 0.6;
//	if (rainbowg > 255.f) rainbowg = 40.f;
//
//	static float rainbowb;
//	rainbowb += 0.4;
//	if (rainbowb > 255.f) rainbowb = 40.f;
//
//	static float scale;
//	scale += 0.8f;
//	if (scale > 609.f) scale = 0.f;
//
//	Line(Menu.pos.x + 98, Menu.pos.y + 2, Menu.pos.x + 609, Menu.pos.y + 2, Color(244, 244, 244, GlobalMenuAlpha));
//	Line(Menu.pos.x + 98, Menu.pos.y + 2 + (height - 39), Menu.pos.x + 609, Menu.pos.y + 2 + (height - 39), Color(244, 244, 244, GlobalMenuAlpha));
//	Line(Menu.pos.x + 609, Menu.pos.y + 2, Menu.pos.x + 609, Menu.pos.y + 2 + (height - 38), Color(244, 244, 244, GlobalMenuAlpha));
//
//	//Line(Menu.pos.x + 9, Menu.pos.y + 2, Menu.pos.x + width - 9, Menu.pos.y + 2, Color(rainbow, 120, 150, GlobalMenuAlpha));
//	GradientSideways(Menu.pos.x + 9 + 90, Menu.pos.y + 2, (609 / 2), 2, Color(0, 160, 255, GlobalMenuAlpha), Color(160, 0, 255, GlobalMenuAlpha), 2);
//	GradientSideways((Menu.pos.x + 609 / 2), Menu.pos.y + 2, 609 / 2, 2, Color(160, 0, 255, GlobalMenuAlpha), Color(255, 255, 0, GlobalMenuAlpha), 1);
//
//	//Line(Menu.pos.x + 9, Menu.pos.y + 2, Menu.pos.x + scale , Menu.pos.y + 2, Color(rainbowr, rainbowg, rainbowb, GlobalMenuAlpha));
//	//Line(Menu.pos.x + 609, Menu.pos.y + 3, (Menu.pos.x + 9 + 609) - scale, Menu.pos.y + 3, Color(rainbowr, rainbowg, rainbowb, GlobalMenuAlpha));
//
//}
//
///* func buttons here *//*
//					   void Unhook();
//
//					   void LoadPrebuildRage();
//
//					   void LoadPrebuildHvH();
//
//					   void LoadPrebuildLegit();
//
//					   void ApplySkins();
//
//					   void RestoreOldSettings();
//
//					   //void ResetSettings();*/
//
//int phase1 = 0;
//int phase2 = 30;
//int phase3 = 60;
//int phase4 = 90;
//
//bool Clicked_This_Frame;
//bool Holding_Mouse_1;
//bool Dont_Click;
//bool Holding_Menu;
//int Menu_Drag_X;
//int Menu_Drag_Y;
//int Tab_Count = 0;
//
//bool keys[256];
//bool oldKeys[256];
//
//bool GetKeyPress(unsigned int key)
//{
//	try
//	{
//		if (keys[key] == true && oldKeys[key] == false)
//			return true;
//		else
//			return false;
//	}
//	catch (...)
//	{
//	}
//}
//
//std::vector< char* > KeyStrings = { "[ _ ]", "[M1]", "[M2]", "[BRK]", "[M3]", "[M4]", "[M5]",
//"[ _ ]", "[BSPC]", "[TAB]", "[ _ ]", "[ _ ]", "[ _ ]", "[ENTER]", "[ _ ]", "[ _ ]", "[SHFT]",
//"[CTRL]", "[ALT]","[PAUSE]","[CAPS]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ESC]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[SPACE]","[PGUP]", "[PGDOWN]", "[END]", "[HOME]", "[Left]",
//"[UP]", "[RIGHT]", "[DOWN]", "[ _ ]", "[PRNT]", "[ _ ]", "[PRTSCR]", "[INS]","[DEL]", "[ _ ]", "[0]", "[1]",
//"[2]", "[3]", "[4]", "[5]", "[6]", "[7]", "[8]", "[9]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[A]", "[B]", "[C]", "[D]", "[E]", "[F]", "[G]", "[H]", "[I]", "[J]", "[K]", "[L]", "[M]", "[N]", "[O]", "[P]", "[Q]", "[R]", "[S]", "[T]", "[U]",
//"[V]", "[W]", "[X]","[Y]", "[Z]", "[LFTWIN]", "[RGHTWIN]", "[ _ ]", "[ _ ]", "[ _ ]", "[NUM0]", "[NUM1]",
//"[NUM2]", "[NUM3]", "[NUM4]", "[NUM5]", "[NUM6]","[NUM7]", "[NUM8]", "[NUM9]", "[*]", "[+]", "[_]", "[-]", "[.]", "[/]", "[F1]", "[F2]", "[F3]",
//"[F4]", "[F5]", "[F6]", "[F7]", "[F8]", "[F9]", "[F10]", "[F11]", "[F12]","[F13]", "[F14]", "[F15]", "[F16]", "[F17]", "[F18]", "[F19]", "[F20]", "[F21]",
//"[F22]", "[F23]", "[F24]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]","[ _ ]", "[ _ ]", "[ _ ]",
//"NUM LOCK", "SCROLL LOCK", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]","[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[LSHFT]", "[RSHFT]", "[LCTRL]",
//"[RCTRL]", "[LMENU]", "[RMENU]", "[ _ ]","[ _ ]", "[ _ ]","[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[NTRK]", "[PTRK]", "[STOP]", "[PLAY]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", ";", "+", ",", "-", ".", "/?", "~", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]","[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]","[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[{", "\\|", "}]", "'\"", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]","[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]", "[ _ ]",
//"[ _ ]", "[ _ ]" };
//
//void DrawMouse()
//{
//	POINT Mouse;
//	POINT mp;
//	GetCursorPos(&mp);
//	ScreenToClient(GetForegroundWindow(), &mp);
//	Mouse.x = mp.x;
//	Mouse.y = mp.y;
//	static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
//	unsigned char buffer[4] = { 220, 0, 220, GlobalMenuAlpha };
//
//	/*Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
//	Interfaces.pSurface->DrawSetTexture(Texturer);
//	Interfaces.pSurface->DrawSetColor(220, 0, 220, GlobalMenuAlpha);
//
//	Vertex_t Verts[3];
//	Verts[0].x = Mouse.x;
//	Verts[0].y = Mouse.y;
//	Verts[1].x = Mouse.x + 27;
//	Verts[1].y = Mouse.y + 13;
//	Verts[2].x = Mouse.x + 13;
//	Verts[2].y = Mouse.y + 27;
//	Interfaces.pSurface->DrawTexturedPolygon(3, Verts);*/
//
//	Clear(Mouse.x + 1, Mouse.y, 1, 17, Color(3, 6, 26, 255));
//	for (int i = 0; i < 11; i++)
//		Clear(Mouse.x + 2 + i, Mouse.y + 1 + i, 1, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 8, Mouse.y + 12, 5, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 8, Mouse.y + 13, 1, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 9, Mouse.y + 14, 1, 2, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 10, Mouse.y + 16, 1, 2, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 8, Mouse.y + 18, 2, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 7, Mouse.y + 16, 1, 2, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 6, Mouse.y + 14, 1, 2, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 5, Mouse.y + 13, 1, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 4, Mouse.y + 14, 1, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 3, Mouse.y + 15, 1, 1, Color(3, 6, 26, 255));
//	Clear(Mouse.x + 2, Mouse.y + 16, 1, 1, Color(3, 6, 26, 255));
//	for (int i = 0; i < 4; i++)
//		Clear(Mouse.x + 2 + i, Mouse.y + 2 + i, 1, 14 - (i * 2), Color(0, 161, 255, 255));
//	Clear(Mouse.x + 6, Mouse.y + 6, 1, 8, Color(0, 161, 255, 255));
//	Clear(Mouse.x + 7, Mouse.y + 7, 1, 9, Color(0, 161, 255, 255));
//	for (int i = 0; i < 4; i++)
//		Clear(Mouse.x + 8 + i, Mouse.y + 8 + i, 1, 4 - i, Color(0, 161, 255, 255));
//	Clear(Mouse.x + 8, Mouse.y + 14, 1, 4, Color(0, 161, 255, 255));
//	Clear(Mouse.x + 9, Mouse.y + 16, 1, 2, Color(0, 161, 255, 255));
//
//}
//
//void CMenu::Set_Current_Tab(int tab)
//{
//	Current_tab = tab;
//}
//
//int CMenu::GetCurret_Tab()
//{
//	return Current_tab;
//}
//
//void CMenu::Update_Frame()
//{
//	if (!Holding_Mouse_1)
//	{
//		if (GetClicked())
//		{
//			Holding_Menu = true;
//		}
//		else
//		{
//			Holding_Menu = false;
//		}
//	}
//
//	if (Holding_Menu)
//	{
//		MenuPOS NewPOS;
//		POINT Mouse;
//		POINT mp;
//		GetCursorPos(&mp);
//		ScreenToClient(GetForegroundWindow(), &mp);
//		Mouse.x = mp.x;
//		Mouse.y = mp.y;
//		NewPOS.x = Mouse.x - Menu_Drag_X;
//		NewPOS.y = Mouse.y - Menu_Drag_Y;
//		this->pos = NewPOS;
//	}
//}
//
//bool CMenu::GetClicked()
//{
//	if (!(GetAsyncKeyState(VK_LBUTTON) & 0x8000))
//	{
//		return false;
//	}
//
//	POINT Mouse;
//	POINT mp;
//	GetCursorPos(&mp);
//	ScreenToClient(GetForegroundWindow(), &mp);
//	Mouse.x = mp.x;
//	Mouse.y = mp.y;
//
//	if (Mouse.x > this->pos.x && Mouse.y > this->pos.y - 15 && Mouse.x < this->pos.x + 618 && Mouse.y < this->pos.y + 15)
//	{
//		if (!Holding_Mouse_1)
//		{
//			Menu_Drag_X = Mouse.x - pos.x;
//			Menu_Drag_Y = Mouse.y - pos.y;
//		}
//		return true;
//	}
//	/*else if( Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 175 && Mouse.y < this->pos.y + 150 )
//	{
//	if( !Holding_Mouse_1 )
//	{
//	Menu_Drag_X = Mouse.x - pos.x;
//	Menu_Drag_Y = Mouse.y - pos.y;
//	}
//	return true;
//	}*/
//	else
//	{
//		return false;
//	}
//}
//
//CMenu Menu;
//class CButton;
//class CDummy;
//class CSlider;
//class CSliderNormal;
//class CSliderDB;
//class CDropbox;
//class CKeybutton;
//class CTab;
//class CVerticalSlider;
//class CMenuBox;
//class CFancyButton;
//class CDropboxSwitch;
//
///*
//CColor CalcColorRatio(CColor Min, CColor Max, double Ratio)
//{
//int MinR, MinG, MinB, MinA;
//Min.GetColor(MinR, MinG, MinB, MinA);
//MinR *= (1 - Ratio);
//MinB *= (1 - Ratio);
//MinG *= (1 - Ratio);
//MinA *= (1 - Ratio);
//
//int MaxR, MaxG, MaxB, MaxA;
//Max.GetColor(MaxR, MaxG, MaxB, MaxA);
//MaxR *= (Ratio);
//MaxG *= (Ratio);
//MaxB *= (Ratio);
//MaxA *= (Ratio);
//
//return CColor(MinR + MaxR, MinG + MaxG, MinB + MaxB, MinA + MaxA);
//};
//
//class CButton
//{
//private:
//MenuPOS pos;
//MenuPOS offset;
//int Tab;
//int Sub;
//
//int Setting;
//char* Name = "ERROR";
//
//bool Hovering()
//{
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 50 && Mouse.y < this->pos.y + 14)
//{
//return true;
//}
//return false;
//}
//
//bool Clicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//
//if (Hovering())
//{
//return true;
//}
//return false;
//}
//
//public:
//void Update()
//{
//this->pos.x = Menu.pos.x + this->offset.x;
//this->pos.y = Menu.pos.y + this->offset.y;
//
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (Clicked())
//{
//Dont_Click = true;
//Settings.SetSetting(Tab, Setting, !Settings.GetMenuSetting(Tab, Setting));
//}
//}
//}
//
//void Draw()
//{
//int red = 70;
//int green = 70;
//int blue = 255;
//
//if (Menu.GetCurret_Tab() == Tab)
//{
////GradientV(this->pos.x, this->pos.y + 1, 124, 7, Color(55, 55, 55, GlobalMenuAlpha), Color(40, 40, 40, GlobalMenuAlpha));
//GradientV(this->pos.x, this->pos.y - 1, 12, 12, Color(55, 55, 55, GlobalMenuAlpha), Color(40, 40, 40, GlobalMenuAlpha));
//Outline(this->pos.x, this->pos.y - 1, 12, 12, Color(2, 2, 2, GlobalMenuAlpha));
//
//if (Settings.GetMenuSetting(this->Tab, this->Setting))
//{
//GradientV(this->pos.x, this->pos.y - 1, 12, 12, Color(255,255,255, GlobalMenuAlpha), Color(red - 15, green - 15, blue - 15, GlobalMenuAlpha - 10));
//}
//Outline(this->pos.x, this->pos.y - 1, 12, 12, Color(2, 2, 2, GlobalMenuAlpha));
//Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 2, CColor(245, 245, 245, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
//
///*Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y - 2, this->pos.x + 12, this->pos.y - 2 + 12);
//Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f));
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y - 2 + 1, this->pos.x + 11, this->pos.y - 2 + 11);
//
//if (Settings.GetMenuSetting(this->Tab, this->Setting))
//{
//Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f));
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y - 2 + 1, this->pos.x + 11, this->pos.y - 2 + 11);
//}
////Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
//Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(Settings.GetSetting(Tab_Colors, Colors_controls_text_r), Settings.GetSetting(Tab_Colors, Colors_controls_text_g), Settings.GetSetting(Tab_Colors, Colors_controls_text_b), Settings.GetSetting(Tab_Colors, Colors_controls_text_a) * (GlobalMenuAlpha / 255.f)), Hacks.Font_Controls, false, this->Name);*/
///*}
//}
//
//void Init(int Tab, int Setting, bool defult, int x, int y, char* name, int sub)
//{
//this->Tab = Tab;
//this->Setting = Setting;
//this->offset.y = y;
//this->offset.x = x;
//this->Name = name;
//this->Sub = sub;
//
//Settings.SetSetting(Tab, Setting, defult);
//}
//};
//
//class CDummy
//{
//private:
//int Tab = 0;
//int SubTab = 0;
//int Setting = 0;
//double Max = 100;
//double Min = 0;
//CColor CMAX = CColor(0, 200, 255, GlobalMenuAlpha);
//CColor CMIN = CColor(0, 200, 255, GlobalMenuAlpha);
//MenuPOS pos;
//MenuPOS offset;
//char* Name = "ERROR";
////char* SValue = "0";
//bool Is_Holding;
//int Animation = 0;
//int phase;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//this->Is_Holding = false;
//return false;
//}
//if (Holding_Mouse_1)
//{
//if (!this->Is_Holding)
//{
//return false;
//}
//}
//if (Dont_Click)
//return false;
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 13)
//{
//this->Is_Holding = true;
//return true;
//}
//else if (this->Is_Holding)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//
//}
//
//void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub)
//{
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Max = max;
//Min = min;
//Name = name;
//SubTab = sub;
//Settings.SetSetting(Tab, Setting, defult);
//}
//
//void Update()
//{
//this->pos.x = Menu.pos.x + offset.x;
//this->pos.y = Menu.pos.y + offset.y;
//
//// get clicked and changing value
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (this->GetClicked())
//{
//Dont_Click = true;
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//// get differance
//double idifference;
//idifference = Mouse.x - this->pos.x;
//// Set Value
//double value = ((idifference / 125) * (this->Max - this->Min));
//if (value < Min)
//{
//value = Min;
//}
//else if (value > Max)
//{
//value = Max;
//}
//
//Settings.SetSetting(Tab, Setting, value);
//}
//}
//}
//};
//
//class CFancyButton
//{
//private:
//MenuPOS pos;
//MenuPOS offset;
//int Tab;
//int Sub;
//
//int Setting;
//char* Text1 = "ERROR";
//char* Text2 = "ERROR";
//
//
//bool Hovering()
//{
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 50 && Mouse.y < this->pos.y + 8)
//{
//return true;
//}
//return false;
//}
//
//bool Clicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//
//if (Hovering())
//{
//return true;
//}
//return false;
//}
//
//public:
//void Update()
//{
//this->pos.x = Menu.pos.x + this->offset.x;
//this->pos.y = Menu.pos.y + this->offset.y;
//
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (Clicked())
//{
//Dont_Click = true;
//Settings.SetSetting(Tab, Setting, !Settings.GetMenuSetting(Tab, Setting));
//}
//}
//}
//
//void Draw()
//{
//
//if (Menu.GetCurret_Tab() == Tab)
//{
//Interfaces.pSurface->DrawSetColor(65, 65, 65, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 16, this->pos.y + 8);
//
////Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//
//
//if (!Settings.GetMenuSetting(this->Tab, this->Setting))
//{
//Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 1, this->pos.x + 7, this->pos.y + 7);
//
//Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Text1);
//}
//else
//{
//Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 9, this->pos.y + 1, this->pos.x + 15, this->pos.y + 7);
//
//Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Text2);
//
//}
////Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 12, this->pos.y + 12);
////Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
////Interfaces.pSurface->DrawT(this->pos.x + 20, this->pos.y - 3, CColor(Interface_R, Interface_G, Interface_B, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Text1);
//}
//}
//
//void Init(int Tab, int Setting, bool defult, int x, int y, char* text1, char* text2, int sub)
//{
//this->Tab = Tab;
//this->Setting = Setting;
//this->offset.y = y;
//this->offset.x = x;
//this->Text1 = text1;
//this->Text2 = text2;
//this->Sub = sub;
//
//Settings.SetSetting(Tab, Setting, defult);
//}
//};
//
//class CSlider
//{
//private:
//int Tab = 0;
//int SubTab = 0;
//int Setting = 0;
//double Max = 100;
//double Min = 0;
//CColor CMAX = CColor(0, 200, 255, GlobalMenuAlpha);
//CColor CMIN = CColor(0, 200, 255, GlobalMenuAlpha);
//MenuPOS pos;
//MenuPOS offset;
//bool Dummy;
//char* Name = "ERROR";
////char* SValue = "0";
//bool Is_Holding;
//int Animation = 0;
//int phase;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//this->Is_Holding = false;
//return false;
//}
//if (Holding_Mouse_1)
//{
//if (!this->Is_Holding)
//{
//return false;
//}
//}
//if (Dont_Click)
//return false;
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 13)
//{
//this->Is_Holding = true;
//return true;
//}
//else if (this->Is_Holding)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab && !(this->Dummy))
//{
//int red = 70;
//int green = 70;
//int blue = 255;
//
//GradientV(this->pos.x, this->pos.y + 1, 124, 7, Color(55, 55, 55, GlobalMenuAlpha), Color(40, 40, 40, GlobalMenuAlpha));
//
//float Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//float Location = Ratio * 124;
//
//GradientV(this->pos.x, this->pos.y + 1, Location, 7, Color(255, 255, 255, GlobalMenuAlpha), Color(255 - 20, 255 - 20, 255 - 20, GlobalMenuAlpha));
//
//Outline(this->pos.x - 1, this->pos.y, 124 + 2, 9, Color(2, 2, 2, 255 * ((GlobalMenuAlpha / 255.f))));
//
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[128];
//sprintf(vl, "%.f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 6.5, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Slider, false, vl);
////Interfaces.pSurface->DrawFilledCircle(this->pos.x + Location, this->pos.y + 8, 8, red - 10, green - 10, blue - 10, GlobalMenuAlpha - 15);
//Interfaces.pSurface->DrawSetColor(200, 200, blue, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + Location, this->pos.y + 1, this->pos.x + Location + 4, this->pos.y + 8);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location, this->pos.y + 1, 7, 7);
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//
///*double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//double Location = Ratio * 150;
//Interfaces.pSurface->DrawSetColor(65, 65, 65, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + 154, this->pos.y + 12);
//
//int r, g, b, a;
//CalcColorRatio(CMIN, CMAX, Ratio).GetColor(r, g, b, a);
//
//Interfaces.pSurface->DrawSetColor(r, g, b, a);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12);
//if (Settings.GetSetting(Tab_Visuals, Visuals_SliderMovement))
//{
//for (int i = 0; i < Location; i++)
//{
//int Temp = (i + (Animation / 5)) % 5;
//switch (Temp)
//{
//case 0:
//DrawLine(this->pos.x + i, this->pos.y + 10, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 1:
//DrawLine(this->pos.x + i, this->pos.y + 8, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 2:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 3:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 10, CColor(55, 55, 55, 155)); break;
//case 4:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 8, CColor(55, 55, 55, 155)); break;
//}
//}
//Animation++;
//Animation = Animation % 50;
//}
//
//Interfaces.pSurface->DrawSetColor(20, 20, 20, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 155, this->pos.y + 13);
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 10, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[24];
//sprintf(vl, "%.2f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 3.5, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, vl);*/
///*	}
//}
//
//void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub, bool dummy)
//{
//Dummy = dummy;
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Max = max;
//Min = min;
//Name = name;
//SubTab = sub;
//Settings.SetSetting(Tab, Setting, defult);
//}
//
//void Update()
//{
//this->pos.x = Menu.pos.x + offset.x;
//this->pos.y = Menu.pos.y + offset.y;
//
//// get clicked and changing value
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (this->GetClicked())
//{
//Dont_Click = true;
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//// get differance
//double idifference;
//idifference = Mouse.x - this->pos.x;
//// Set Value
//double value = ((idifference / 125) * (this->Max - this->Min));
//if (value < Min)
//{
//value = Min;
//}
//else if (value > Max)
//{
//value = Max;
//}
//
//Settings.SetSetting(Tab, Setting, value);
//}
//}
//}
//};
//
//class CSliderDB
//{
//private:
//int Tab = 0;
//int SubTab = 0;
//int Setting = 0;
//int ControlSetting = 0;
//int ShowValue = 0;
//int Animation = 0;
//double Max = 100;
//double Min = 0;
//MenuPOS pos;
//MenuPOS offset;
//char* Name = "ERROR";
////char* SValue = "0";
//bool Is_Holding;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//this->Is_Holding = false;
//return false;
//}
//if (Holding_Mouse_1)
//{
//if (!this->Is_Holding)
//{
//return false;
//}
//}
//if (Dont_Click)
//return false;
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + 13)
//{
//this->Is_Holding = true;
//return true;
//}
//else if (this->Is_Holding)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab && Settings.GetMenuSetting(this->Tab, ControlSetting) == ShowValue)
//{
//
//double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//double Location = Ratio * 150;
//Interfaces.pSurface->DrawSetColor(65, 65, 65, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + 154, this->pos.y + 12);
//
//Interfaces.pSurface->DrawSetColor(255, 255, 255, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12);
//
//Interfaces.pSurface->DrawSetColor(20, 20, 20, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 155, this->pos.y + 13);
//
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 10, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[24];
//sprintf(vl, "%.6f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 3.5, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, vl);
//}
//}
//
//void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub, int ShowSetting, int ShowSelection)
//{
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Max = max;
//Min = min;
//Name = name;
//SubTab = sub;
//ControlSetting = ShowSetting;
//ShowValue = ShowSelection;
//Settings.SetSetting(Tab, Setting, defult);
//}
//
//void Update()
//{
//this->pos.x = Menu.pos.x + offset.x;
//this->pos.y = Menu.pos.y + offset.y;
//
//// get clicked and changing value
//if (Menu.GetCurret_Tab() == Tab && Settings.GetMenuSetting(this->Tab, ControlSetting) == ShowValue)
//{
//if (this->GetClicked())
//{
//Dont_Click = true;
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//// get differance
//double idifference;
//idifference = Mouse.x - this->pos.x;
//// Set Value
//double value = ((idifference / 150) * (this->Max - this->Min));
//if (value < Min)
//{
//value = Min;
//}
//else if (value > Max)
//{
//value = Max;
//}
//
//Settings.SetSetting(Tab, Setting, value);
//}
//}
//}
//};
//
//class CSliderNormal
//{
//private:
//int Tab = 0;
//int SubTab = 0;
//int Setting = 0;
//double Max = 100;
//double Min = 0;
//int Animation = 0;
//MenuPOS pos;
//MenuPOS offset;
//char* Name = "ERROR";
////char* SValue = "0";
//bool Is_Holding;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//this->Is_Holding = false;
//return false;
//}
//if (Holding_Mouse_1)
//{
//if (!this->Is_Holding)
//{
//return false;
//}
//}
//if (Dont_Click)
//return false;
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + 13)
//{
//this->Is_Holding = true;
//return true;
//}
//else if (this->Is_Holding)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab)
//{
//
//int red = 70;
//int green = 70;
//int blue = 255;
//
//GradientV(this->pos.x, this->pos.y + 1, 124, 7, Color(55, 55, 55, GlobalMenuAlpha), Color(40, 40, 40, GlobalMenuAlpha));
//
//float Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//float Location = Ratio * 124;
//
//GradientV(this->pos.x, this->pos.y + 1, Location, 7, Color(red, green, blue, GlobalMenuAlpha), Color(red - 20, green - 20, blue - 20, GlobalMenuAlpha));
//
//Outline(this->pos.x - 1, this->pos.y, 124 + 2, 9, Color(2, 2, 2, 255 * ((GlobalMenuAlpha / 255.f))));
//
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[128];
//sprintf(vl, "%.2f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 6.5, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Slider, false, vl);
////Interfaces.pSurface->DrawFilledCircle(this->pos.x + Location, this->pos.y + 8, 8, red - 10, green - 10, blue - 10, GlobalMenuAlpha - 15);
//Interfaces.pSurface->DrawSetColor(200, 200, blue, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + Location, this->pos.y + 1, this->pos.x + Location + 4, this->pos.y + 8);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location, this->pos.y + 1, 7, 7);
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//
//
///*float Interface_R = Settings.GetSetting(Tab_Colors, Colors_Interface_R);
//float Interface_G = Settings.GetSetting(Tab_Colors, Colors_Interface_G);
//float Interface_B = Settings.GetSetting(Tab_Colors, Colors_Interface_B);
//
//double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//double Location = Ratio * 150;
//Interfaces.pSurface->DrawSetColor(65, 65, 65, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + 154, this->pos.y + 12);
//
//
//
//Interfaces.pSurface->DrawSetColor(Interface_R, Interface_G, Interface_B, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12);
//
//if (Settings.GetSetting(Tab_Visuals, Visuals_SliderMovement))
//{
//for (int i = 0; i < Location; i++)
//{
//int Temp = (i + (Animation / 5)) % 5;
//switch (Temp)
//{
//case 0:
//DrawLine(this->pos.x + i, this->pos.y + 10, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 1:
//DrawLine(this->pos.x + i, this->pos.y + 8, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 2:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 3:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 10, CColor(55, 55, 55, 155)); break;
//case 4:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 8, CColor(55, 55, 55, 155)); break;
//}
//}
//Animation++;
//Animation = Animation % 50;
//}
//
//Interfaces.pSurface->DrawSetColor(20, 20, 20, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 155, this->pos.y + 13);
//
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 10, CColor(Interface_R, Interface_G, Interface_B, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[24];
//sprintf(vl, "%.2f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 3.5, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, vl);
//}*/
///*	}
//}
//
//void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub)
//{
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Max = max;
//Min = min;
//Name = name;
//SubTab = sub;
//Settings.SetSetting(Tab, Setting, defult);
//}
//
//void Update()
//{
//this->pos.x = Menu.pos.x + offset.x;
//this->pos.y = Menu.pos.y + offset.y;
//
//// get clicked and changing value
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (this->GetClicked())
//{
//Dont_Click = true;
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//// get differance
//double idifference;
//idifference = Mouse.x - this->pos.x;
//// Set Value
//double value = ((idifference / 125) * (this->Max - this->Min));
//if (value < Min)
//{
//value = Min;
//}
//else if (value > Max)
//{
//value = Max;
//}
//
//Settings.SetSetting(Tab, Setting, value);
//}
//}
//}
//};
//
//class CSliderFloat
//{
//private:
//int Tab = 0;
//int SubTab = 0;
//int Setting = 0;
//double Max = 100;
//double Min = 0;
//int Animation = 0;
//MenuPOS pos;
//MenuPOS offset;
//char* Name = "ERROR";
////char* SValue = "0";
//bool Is_Holding;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//this->Is_Holding = false;
//return false;
//}
//if (Holding_Mouse_1)
//{
//if (!this->Is_Holding)
//{
//return false;
//}
//}
//if (Dont_Click)
//return false;
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + 13)
//{
//this->Is_Holding = true;
//return true;
//}
//else if (this->Is_Holding)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab)
//{
//int red = 70;
//int green = 70;
//int blue = 255;
//
//GradientV(this->pos.x, this->pos.y + 1, 124, 7, Color(55, 55, 55, GlobalMenuAlpha), Color(40, 40, 40, GlobalMenuAlpha));
//
//float Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//float Location = Ratio * 124;
//
//GradientV(this->pos.x, this->pos.y + 1, Location, 7, Color(255, 255, 255, GlobalMenuAlpha), Color(255 - 20, 255 - 20, 255 - 20, GlobalMenuAlpha));
//
//Outline(this->pos.x - 1, this->pos.y, 124 + 2, 9, Color(2, 2, 2, 255 * ((GlobalMenuAlpha / 255.f))));
//
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[128];
//sprintf(vl, "%.3f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 6.5, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Slider, false, vl);
////Interfaces.pSurface->DrawFilledCircle(this->pos.x + Location, this->pos.y + 8, 8, red - 10, green - 10, blue - 10, GlobalMenuAlpha - 15);
//Interfaces.pSurface->DrawSetColor(200, 200, blue, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + Location, this->pos.y + 1, this->pos.x + Location + 4, this->pos.y + 8);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x + Location, this->pos.y + 1, 7, 7);
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//
///*double Ratio = Settings.GetMenuSetting(this->Tab, this->Setting) / (this->Max - this->Min);
//double Location = Ratio * 150;
//Interfaces.pSurface->DrawSetColor(65, 65, 65, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + 154, this->pos.y + 12);
//
//int r, g, b, a;
//CalcColorRatio(CMIN, CMAX, Ratio).GetColor(r, g, b, a);
//
//Interfaces.pSurface->DrawSetColor(r, g, b, a);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 6, this->pos.x + Location, this->pos.y + 12);
//if (Settings.GetSetting(Tab_Visuals, Visuals_SliderMovement))
//{
//for (int i = 0; i < Location; i++)
//{
//int Temp = (i + (Animation / 5)) % 5;
//switch (Temp)
//{
//case 0:
//DrawLine(this->pos.x + i, this->pos.y + 10, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 1:
//DrawLine(this->pos.x + i, this->pos.y + 8, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 2:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 12, CColor(55, 55, 55, 155)); break;
//case 3:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 10, CColor(55, 55, 55, 155)); break;
//case 4:
//DrawLine(this->pos.x + i, this->pos.y + 6, this->pos.x + i, this->pos.y + 8, CColor(55, 55, 55, 155)); break;
//}
//}
//Animation++;
//Animation = Animation % 50;
//}
//
//Interfaces.pSurface->DrawSetColor(20, 20, 20, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y + 5, this->pos.x + 155, this->pos.y + 13);
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 10, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, "%s", this->Name, (float)Settings.GetMenuSetting(this->Tab, this->Setting));
//float Value1 = (float)Settings.GetMenuSetting(this->Tab, this->Setting);
//char vl[24];
//sprintf(vl, "%.2f", Value1);
//Interfaces.pSurface->DrawT(this->pos.x + Location, this->pos.y + 3.5, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, vl);*/
///*}
//}
//
//void Init(int x, int y, double min, double max, double defult, char* name, int tab, int setting, int sub)
//{
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Max = max;
//Min = min;
//Name = name;
//SubTab = sub;
//Settings.SetSetting(Tab, Setting, defult);
//}
//
//void Update()
//{
//this->pos.x = Menu.pos.x + offset.x;
//this->pos.y = Menu.pos.y + offset.y;
//
//// get clicked and changing value
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (this->GetClicked())
//{
//Dont_Click = true;
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//// get differance
//double idifference;
//idifference = Mouse.x - this->pos.x;
//// Set Value
//double value = ((idifference / 150) * (this->Max - this->Min));
//if (value < Min)
//{
//value = Min;
//}
//else if (value > Max)
//{
//value = Max;
//}
//
//Settings.SetSetting(Tab, Setting, value);
//}
//}
//}
//};
//
//class CDropBox
//{
//private:
//int Tab = 0;
//int Setting = 0;
//
//char* Name = "ERROR";
//char* Parts[256];
//int Amount = 0;
//
//bool Dropping = false;
//
//MenuPOS pos;
//MenuPOS offset;
//int Sub = 0;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + 20)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//int GetPartClicked()
//{
//if (!Clicked_This_Frame)
//{
//return -1;
//}
//if (Holding_Mouse_1)
//{
//return -1;
//}
//if (Dont_Click)
//{
//return -1;
//}
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//for (int i = 1; i < this->Amount; i++)
//{
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (16 * (i)) && Mouse.x < this->pos.x + 125 && Mouse.y < this->pos.y + (16 * (i + 1)))
//{
//return i;
//}
//}
//return -1;
//}
//
//public:
//void Update()
//{
//pos.x = Menu.pos.x + offset.x;
//pos.y = Menu.pos.y + offset.y;
//
//if (Tab == Menu.GetCurret_Tab())
//{
//if (this->GetClicked())
//{
//if (this->Dropping == true)
//{
//this->Dropping = false;
//}
//else
//{
//this->Dropping = true;
//}
//Dont_Click = true;
//}
//else if (this->Dropping)
//{
//int index = this->GetPartClicked();
//if (index != -1)
//{
//Settings.SetSetting(this->Tab, this->Setting, index);
//this->Dropping = false;
//Dont_Click = true;
//}
//else if (Clicked_This_Frame && !Holding_Mouse_1)
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//
//void Draw()
//{
//int red = 70;
//int green = 70;
//int blue = 255;
//
//if (Tab == Menu.GetCurret_Tab())
//{
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 15, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
//
//Outline(this->pos.x, this->pos.y - 2, 124, 20, Color(2, 2, 2, GlobalMenuAlpha));
//GradientV(this->pos.x + 2, this->pos.y, 124 - 4, 16, Color(35, 35, 35, GlobalMenuAlpha), Color(32, 32, 32, GlobalMenuAlpha));
//
//if (this->Dropping)
//{
//GradientV(this->pos.x, this->pos.y + 16, 124, (this->Amount - 1) * 16 + 4, Color(35, 35, 35, GlobalMenuAlpha), Color(32, 32, 32, GlobalMenuAlpha));
//for (int i = 1; i < this->Amount; i++)
//{
//
////Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f)); //dark top color
////Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (16 * i), this->pos.x + 125, this->pos.y + (16 * i) + 16);
////Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
////Interfaces.pSurface->DrawOutlinedRect(pos.x, pos.y + (16 * i) - 1, pos.x + 125, pos.y + (16 * i) + 17);
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y + (16 * i) + 4, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[i]);
////part 2
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
////Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Controls, false, Parts[value]);
//
////static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
////unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha / 2 };//{ color.r(), color.g(), color.b(), color.a() };
//
////Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
////Interfaces.pSurface->DrawSetColor(red, green, blue, GlobalMenuAlpha);
////Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
///*Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 113;
//Verts2[0].y = pos.y + 11;
//Verts2[1].x = pos.x + 117.5;
//Verts2[1].y = pos.y + 6;
//Verts2[2].x = pos.x + 122;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);*/
///*
//Interfaces.pSurface->DrawT(this->pos.x + 110, this->pos.y + 1, CColor(red, green, blue, GlobalMenuAlpha), Hacks.Font_Controls, false, "V");
//}
//Outline(this->pos.x, this->pos.y + 16, 124, (this->Amount - 1) * 16 + 4, Color(2, 2, 2, 255));
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//}
//else
//{
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//
////static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
////unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };
//
////Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
////Interfaces.pSurface->DrawSetColor(red, green, blue, GlobalMenuAlpha);
////Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
///*Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 113;
//Verts2[0].y = pos.y + 6;
//Verts2[1].x = pos.x + 122;
//Verts2[1].y = pos.y + 6;
//Verts2[2].x = pos.x + 117.5;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);*/
///*
//Interfaces.pSurface->DrawT(this->pos.x + 110, this->pos.y + 1, CColor(240, 240, 240, GlobalMenuAlpha), Hacks.Font_Controls, false, "V");
//}
//}
//}
//
//void Init(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub)
//{
//Name = name;
//Amount = parts;
//
//for (int i = 0; i < parts; i++)
//{
//Parts[i] = arr[i];
//}
//
//Tab = tab;
//Setting = setting;
//offset.x = x;
//offset.y = y;
//Sub = sub;
//}
//};
//
//class CDropBoxCTRL
//{
//private:
//int Tab = 0;
//int Setting = 0;
//
//char* Name = "ERROR";
//char* Parts[256];
//int Amount = 0;
//
//bool Dropping = false;
//
//MenuPOS pos;
//MenuPOS offset;
//int Sub = 0;
//int CTRLSetting = 0;
//int CTRLSettingValue = 0;
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + 20)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//int GetPartClicked()
//{
//if (!Clicked_This_Frame)
//{
//return -1;
//}
//if (Holding_Mouse_1)
//{
//return -1;
//}
//if (Dont_Click)
//{
//return -1;
//}
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//for (int i = 1; i < this->Amount; i++)
//{
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (20 * (i)) && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + (20 * (i + 1)))
//{
//return i;
//}
//}
//return -1;
//}
//
//public:
//void Update()
//{
//pos.x = Menu.pos.x + offset.x;
//pos.y = Menu.pos.y + offset.y;
//
//if (Tab == Menu.GetCurret_Tab() && Settings.GetSetting(Tab, CTRLSetting) == CTRLSettingValue)
//{
//if (this->GetClicked())
//{
//if (this->Dropping == true)
//{
//this->Dropping = false;
//}
//else
//{
//this->Dropping = true;
//}
//Dont_Click = true;
//}
//else if (this->Dropping)
//{
//int index = this->GetPartClicked();
//if (index != -1)
//{
//Settings.SetSetting(this->Tab, this->Setting, index);
//this->Dropping = false;
//Dont_Click = true;
//}
//else if (Clicked_This_Frame && !Holding_Mouse_1)
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//
//void Draw()
//{
//int red = 70;
//int green = 70;
//int blue = 255;
//
//if (Tab == Menu.GetCurret_Tab())
//{
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 15, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
//
//Outline(this->pos.x, this->pos.y - 2, 124, 20, Color(2, 2, 2, GlobalMenuAlpha));
//GradientV(this->pos.x + 2, this->pos.y, 124 - 4, 16, Color(35, 35, 35, GlobalMenuAlpha), Color(32, 32, 32, GlobalMenuAlpha));
//
//if (this->Dropping)
//{
//GradientV(this->pos.x, this->pos.y + 16, 124, (this->Amount - 1) * 16 + 4, Color(35, 35, 35, GlobalMenuAlpha), Color(32, 32, 32, GlobalMenuAlpha));
//for (int i = 1; i < this->Amount; i++)
//{
//
////Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_controls_background_r), Settings.GetSetting(Tab_Colors, Colors_controls_background_g), Settings.GetSetting(Tab_Colors, Colors_controls_background_b), Settings.GetSetting(Tab_Colors, Colors_controls_background_a) * (GlobalMenuAlpha / 255.f)); //dark top color
////Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (16 * i), this->pos.x + 125, this->pos.y + (16 * i) + 16);
////Interfaces.pSurface->DrawSetColor(Settings.GetSetting(Tab_Colors, Colors_outline_r), Settings.GetSetting(Tab_Colors, Colors_outline_g), Settings.GetSetting(Tab_Colors, Colors_outline_b), Settings.GetSetting(Tab_Colors, Colors_outline_a) * (GlobalMenuAlpha / 255.f));
////Interfaces.pSurface->DrawOutlinedRect(pos.x, pos.y + (16 * i) - 1, pos.x + 125, pos.y + (16 * i) + 17);
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y + (16 * i) + 4, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[i]);
////part 2
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
////Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Controls, false, Parts[value]);
//
////static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
////unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha / 2 };//{ color.r(), color.g(), color.b(), color.a() };
//
////Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
////Interfaces.pSurface->DrawSetColor(red, green, blue, GlobalMenuAlpha);
////Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
///*Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 113;
//Verts2[0].y = pos.y + 11;
//Verts2[1].x = pos.x + 117.5;
//Verts2[1].y = pos.y + 6;
//Verts2[2].x = pos.x + 122;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);*/
///*
//Interfaces.pSurface->DrawT(this->pos.x + 110, this->pos.y + 1, CColor(red, green, blue, GlobalMenuAlpha), Hacks.Font_Controls, false, "V");
//}
//Outline(this->pos.x, this->pos.y + 16, 124, (this->Amount - 1) * 16 + 4, Color(2, 2, 2, 255));
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//}
//else
//{
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 5, this->pos.y, CColor(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//
////static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
////unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };
//
////Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
////Interfaces.pSurface->DrawSetColor(red, green, blue, GlobalMenuAlpha);
////Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
///*Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 113;
//Verts2[0].y = pos.y + 6;
//Verts2[1].x = pos.x + 122;
//Verts2[1].y = pos.y + 6;
//Verts2[2].x = pos.x + 117.5;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);*/
///*
//Interfaces.pSurface->DrawT(this->pos.x + 110, this->pos.y + 1, CColor(240, 240, 240, GlobalMenuAlpha), Hacks.Font_Controls, false, "V");
//}
//}
//}
//
//void Init(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub, int ctrlSetting, int settingValue)
//{
//Name = name;
//Amount = parts;
//
//for (int i = 0; i < parts; i++)
//{
//Parts[i] = arr[i];
//}
//
//Tab = tab;
//Setting = setting;
//offset.x = x;
//offset.y = y;
//Sub = sub;
//CTRLSetting = ctrlSetting;
//CTRLSettingValue = settingValue;
//}
//};
//
//class CKeyButton
//{
//private:
//MenuPOS pos;
//MenuPOS offset;
//
//int Tab;
//int Setting;
//bool Getting_New_Key;
//char* Name = "ERROR";
//int Sub = 0;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 15 && Mouse.y < this->pos.y + 20)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//public:
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab)
//{
////Interfaces.pSurface->DrawT(this->pos.x, this->pos.y - 12, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, "%s", this->Name);
////Interfaces.pSurface->DrawSetColor(39, 42, 47, 255);
////Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);
////Interfaces.pSurface->DrawSetColor(25, 25, 25, 255);
////Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 80, this->pos.y + 20);
//if (this->Getting_New_Key)
//{
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y, CColor(110, 110, 110, GlobalMenuAlpha), Hacks.Font_Controls, false, "[ _ ]");
//}
//else
//{
//if (Settings.GetMenuSetting(this->Tab, this->Setting) == -1)
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y, CColor(90, 90, 90, GlobalMenuAlpha), Hacks.Font_Controls, false, "[ _ ]");
//else
//{
//char* NameOfKey = KeyStrings[(int)Settings.GetMenuSetting(this->Tab, this->Setting)];
//Interfaces.pSurface->DrawT(this->pos.x, this->pos.y, CColor(90, 90, 90, GlobalMenuAlpha), Hacks.Font_Controls, false, NameOfKey);
//}
//}
//}
//}
//
//void Update()
//{
//pos.x = Menu.pos.x + offset.x;
//pos.y = Menu.pos.y + offset.y;
//
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (Getting_New_Key)
//{
//for (int i = 0; i < 255; i++)
//{
//if (GetKeyPress(i))
//{
//if (i == VK_DELETE)
//{
//this->Getting_New_Key = false;
//Settings.SetSetting(Tab, Setting, -1);
//break;
//}
//if (i == VK_ESCAPE)
//{
//Settings.SetSetting(Tab, Setting, -1);
//this->Getting_New_Key = false;
//break;
//}
//Settings.SetSetting(Tab, Setting, i);
//this->Getting_New_Key = false;
//break;
//}
//}
//}
//else if (this->GetClicked())
//{
//this->Getting_New_Key = !this->Getting_New_Key;
//}
//}
//}
//
//void Init(int x, int y, int tab, int setting, char* name, int sub)
//{
//offset.x = x;
//offset.y = y;
//Tab = tab;
//Setting = setting;
//Name = name;
//Sub = sub;
//Settings.SetSetting(Tab, Setting, -1);
//}
//};
//
//class CTab
//{
//public:
//void Update()
//{
//pos.x = Menu.pos.x - 5;
//pos.y = Menu.pos.y + ((215 / Tab_Count) * Tab);
//
//if (GetClicked())
//{
//Dont_Click = true;
//Menu.Set_Current_Tab(Tab);
//}
//}
//
//void Draw()
//{
//
///*Interfaces.pSurface->DrawSetColor(5, 5, 5, GlobalMenuAlpha);
//Interfaces.pSurface->DrawLine(pos.x, pos.y, pos.x + 174, pos.y);
//Interfaces.pSurface->DrawLine(pos.x, pos.y + ((270 / Tab_Count) * Tab), pos.x + 174, pos.y + ((270 / Tab_Count) * Tab));
//Interfaces.pSurface->DrawT(pos.x + 60, pos.y + (220 / Tab_Count / 2) - 3, CColor(0, 200, 255, (GlobalMenuAlpha / 255.f) * 110.f), Hacks.Font_Tab, false, Name);
//Interfaces.pSurface->DrawT(pos.x + 20, pos.y + (220 / Tab_Count / 2) - 5, CColor(0, 200, 255, (GlobalMenuAlpha / 255.f) * 110.f), Hacks.Font_Icons, false, Icon);*/
///*
//RECT TextSize;
//TextSize = pGetTextSize(Hacks.Font_ESP, Name);
//
//float xAxis = Menu.pos.x + 8 - (45 + TextSize.right / 2);;
//float yAxis;
//float yWinPos = Menu.pos.y + 16;
//float yWinHeight = 500 - 2 - 8 - 26;
//
//yAxis = yWinPos + 16 + (Tab * 72) - 10;
//
//RECT TabDrawArea = { Menu.pos.x + 8 + 1, yWinPos + 8 + (Tab * 72) - 8,90 - 1, 72 };
//
//RECT ClickTabArea = {
//xAxis,
//yAxis,
//TextSize.right,
//TextSize.bottom
//};
//
//if (Menu.GetCurret_Tab() == Tab)
//{
////Interfaces.pSurface->DrawSetColor(75, 75, 75, GlobalMenuAlpha);
//// Interfaces.pSurface->DrawFilledRect(pos.x - 1, pos.y - 2, pos.x + 174, pos.y + 12 + (220 / Tab_Count));
//
////Interfaces.pSurface->DrawSetColor(5, 255, 5, GlobalMenuAlpha);
////Interfaces.pSurface->DrawFilledRect(pos.x, pos.y - 1, pos.x + 175, pos.y + 11 + (220 / Tab_Count));
//
////Interfaces.pSurface->DrawSetColor(25, 25, 25, GlobalMenuAlpha);
////Interfaces.pSurface->DrawFilledRect(pos.x, pos.y, pos.x + 176, pos.y + 10 + (220 / Tab_Count));
//
//int red = 70;
//int green = 70;
//int blue = 255;
//
//Clear(TabDrawArea.left, TabDrawArea.top, TabDrawArea.right, TabDrawArea.bottom, Color(28, 28, 28, GlobalMenuAlpha));
//Line(TabDrawArea.left, TabDrawArea.top, TabDrawArea.left + TabDrawArea.right, TabDrawArea.top, Color(244, 244, 244, GlobalMenuAlpha));
//Line(TabDrawArea.left, TabDrawArea.top + TabDrawArea.bottom, TabDrawArea.left + TabDrawArea.right, TabDrawArea.top + TabDrawArea.bottom, Color(244, 244, 244, GlobalMenuAlpha));
//Text(TabDrawArea.left + (TabDrawArea.right / 2) - (TextSize.right / 2) - 18, TabDrawArea.top + (TabDrawArea.bottom / 2) - (TextSize.bottom / 2) - 16, Color(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Icon, Name);
//}
//else
//{
//Text(TabDrawArea.left + (TabDrawArea.right / 2) - (TextSize.right / 2) - 18, TabDrawArea.top + (TabDrawArea.bottom / 2) - (TextSize.bottom / 2) - 16, Color(255, 255, 255, 255), Hacks.Font_Icon, Name);
//}
//}
//
//void Init(char* name, int tab, char* icon)
//{
//Name = name;
//Tab = tab;
//Icon = icon;
//}
//
//private:
//int Tab;
//MenuPOS pos;
//char* Name = "ERROR";
//char* Icon = "ERROR";
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//
//float yWinPos = Menu.pos.y + 16;
//
//RECT TabDrawArea = { Menu.pos.x + 8 + 1, yWinPos + 16 + (Tab * 72) - 8,90 - 1, 72 };
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (rIsMouseInRegion(TabDrawArea))
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//};
//
//class CTabVerticalSlider
//{
//public:
//void Update()
//{
//if (!Draging)
//{
//pos.x = Menu.pos.x;
//pos.y = Menu.pos.y + 170 + (Tab_hight*Menu.GetCurret_Tab());
//}
//}
//
//void Init(int x, int y, int width, int hight)
//{
//pos.x = x;
//pos.y = y;
//Tab_width = width;
//Tab_hight = hight;
//Draging = false;
//};
//
//private:
//Vector2D pos;
//Vector2D SelectorPos;
//int Tab_width;
//int Tab_hight;
//bool Draging;
//};
//
//class CMenuBox
//{
//public:
//void Init(char* name, int x, int y, int w, int h, int tab, int sub)
//{
//Name = name;
//offset.x = x;
//offset.y = y;
//size.x = w;
//size.y = h;
//Tab = tab;
//SubTab = sub;
//}
//
//void Update()
//{
//pos.x = Menu.pos.x + offset.x;
//pos.y = Menu.pos.y + offset.y;
//}
//
//void Draw()
//{
//if (Tab == Menu.GetCurret_Tab())
//{
//
//int Width = 0, Height = 0;
//char Buffer[256] = { '\0' };
//va_list Args;
//va_start(Args, Name);
//vsprintf_s(Buffer, Name, Args);
//va_end(Args);
//size_t Size = strlen(Buffer);
//
//RECT txtSize = GetTextSize(Hacks.Font_Controls, Name);
//
//Clear(pos.x + 2, pos.y + 2, size.x - 4, size.y - 4, Color(40, 40, 40, 0));
//Text(pos.x + (size.x / 2) - (txtSize.right / 2), pos.y - (txtSize.bottom / 2) - 1, Color(244, 244, 244, GlobalMenuAlpha), Hacks.Font_Controls, Name);
//
////box
//
//Line(pos.x, pos.y, pos.x + (size.x / 2) - (txtSize.right / 2) - 2, pos.y, Color(230, 230, 230, GlobalMenuAlpha));
//Line(pos.x + (size.x / 2) + (txtSize.right / 2) + 2, pos.y, pos.x + size.x, pos.y, Color(230, 230, 230, GlobalMenuAlpha));
//
//Line(pos.x, pos.y + size.y, pos.x + size.x, pos.y + size.y, Color(230, 230, 230, GlobalMenuAlpha));
//
//}
//}
//
//private:
//MenuPOS pos;
//MenuPOS offset;
//MenuPOS size;
//char* Name = "ERROR";
//int Tab;
//char* Icon = "ERROR";
//int SubTab = 0;
//};
//
//class CFunctionButton
//{
//public:
//void Update()
//{
//this->pos.x = Menu.pos.x + this->offset.x;
//this->pos.y = Menu.pos.y + this->offset.y;
//
//if (Menu.GetCurret_Tab() == Tab)
//{
//if (this->GetClicked())
//{
//DWORD disfunc = Function;
//__asm
//{
//CALL disfunc
//}
//}
//}
//}
//
//void Draw()
//{
//if (Menu.GetCurret_Tab() == Tab)
//{
//
//Interfaces.pSurface->DrawSetColor(55, 55, 55, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y, this->pos.x + 155, this->pos.y + 20);
//Interfaces.pSurface->DrawSetColor(5, 5, 5, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x + 1, this->pos.y + 1, this->pos.x + 154, this->pos.y + 19);
//Interfaces.pSurface->DrawSetColor(40, 40, 40, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 2, this->pos.y + 2, this->pos.x + 153, this->pos.y + 18);
//Interfaces.pSurface->DrawT(this->pos.x + 77.5, this->pos.y + 3, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, true, Name);
//}
//}
//
//void Init(int x, int y, DWORD function, char* name, int tab)
//{
//Function = function;
//Name = name;
//offset.x = x;
//offset.y = y;
//Tab = tab;
//}
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 150 && Mouse.y < this->pos.y + 20)
//{
//return true;
//}
//
//return false;
//}
//
//private:
//DWORD Function;
//char* Name = "NO NAME";
//MenuPOS pos;
//MenuPOS offset;
//int Tab = -1;
//};
//
//class CDropBoxSwitch
//{
//private:
//int Tab = 0;
//int Setting = 0;
//int ControlSetting = 0;
//int ShowValue = 0;
//
//char* Name = "ERROR";
//char* Parts[256];
//int Amount = 0;
//
//bool Dropping = false;
//
//MenuPOS pos;
//MenuPOS offset;
//int Sub = 0;
//
//bool GetClicked()
//{
//if (!Clicked_This_Frame)
//{
//return false;
//}
//if (Holding_Mouse_1)
//{
//return false;
//}
//if (Dont_Click)
//{
//return false;
//}
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + 20)
//{
//return true;
//}
//else
//{
//return false;
//}
//}
//
//int GetPartClicked()
//{
//if (!Clicked_This_Frame)
//{
//return -1;
//}
//if (Holding_Mouse_1)
//{
//return -1;
//}
//if (Dont_Click)
//{
//return -1;
//}
//
//POINT Mouse;
//POINT mp;
//GetCursorPos(&mp);
//ScreenToClient(GetForegroundWindow(), &mp);
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//
//for (int i = 1; i < this->Amount; i++)
//{
//if (Mouse.x > this->pos.x && Mouse.y > this->pos.y + (20 * (i)) && Mouse.x < this->pos.x + 155 && Mouse.y < this->pos.y + (20 * (i + 1)))
//{
//return i;
//}
//}
//return -1;
//}
//
//public:
//void Update()
//{
//pos.x = Menu.pos.x + offset.x;
//pos.y = Menu.pos.y + offset.y;
//
//if (Tab == Menu.GetCurret_Tab() && Settings.GetMenuSetting(this->Tab, ControlSetting) == ShowValue)
//{
//if (this->GetClicked())
//{
//if (this->Dropping == true)
//{
//this->Dropping = false;
//}
//else
//{
//this->Dropping = true;
//}
//Dont_Click = true;
//}
//else if (this->Dropping)
//{
//int index = this->GetPartClicked();
//if (index != -1)
//{
//Settings.SetSetting(this->Tab, this->Setting, index);
//this->Dropping = false;
//Dont_Click = true;
//}
//else if (Clicked_This_Frame && !Holding_Mouse_1)
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//else
//{
//Dropping = false;
//}
//}
//
//void Draw()
//{
//if (Tab == Menu.GetCurret_Tab() && Settings.GetMenuSetting(this->Tab, ControlSetting) == ShowValue)
//{
//Interfaces.pSurface->DrawSetColor(35, 35, 35, GlobalMenuAlpha);
//Interfaces.pSurface->DrawFilledRect(this->pos.x + 1, this->pos.y + 1, this->pos.x + 154, this->pos.y + 19);
//Interfaces.pSurface->DrawSetColor(5, 5, 5, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(this->pos.x, this->pos.y, this->pos.x + 155, this->pos.y + 20);
//Interfaces.pSurface->DrawT(this->pos.x + 1, this->pos.y - 13, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Name);
//
//if (this->Dropping)
//{
//for (int i = 1; i < this->Amount; i++)
//{
//Interfaces.pSurface->DrawSetColor(35, 35, 35, GlobalMenuAlpha); //dark top color
//Interfaces.pSurface->DrawFilledRect(this->pos.x, this->pos.y + (20 * i), this->pos.x + 155, this->pos.y + (20 * i) + 20);
//Interfaces.pSurface->DrawSetColor(5, 5, 5, GlobalMenuAlpha);
//Interfaces.pSurface->DrawOutlinedRect(pos.x, pos.y, pos.x + 155, pos.y + (20 * i) + 21);
//Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y + 4 + (20 * i), CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[i]);
////part 2
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
////Interfaces.pSurface->DrawT(pos.x + 11, pos.y + 4, CColor(255, 255, 255, 255), Hacks.Font_Tahoma, false, Parts[value]);
//
//static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
//unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };
//
//Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
//Interfaces.pSurface->DrawSetColor(152, 152, 152, GlobalMenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
//Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
//Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 145;
//Verts2[0].y = pos.y + 8;
//Verts2[1].x = pos.x + 150;
//Verts2[1].y = pos.y + 8;
//Verts2[2].x = pos.x + 147.5;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);
//}
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y + 4, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//}
//else
//{
//int value = (int)Settings.GetMenuSetting(Tab, Setting);
//if (value >= this->Amount)
//value = 0;
//Interfaces.pSurface->DrawT(this->pos.x + 11, this->pos.y + 4, CColor(255, 255, 255, GlobalMenuAlpha), Hacks.Font_Controls, false, this->Parts[value]);
//
//static int Texture = Interfaces.pSurface->CreateNewTextureID(true); //need to make a texture with procedural true
//unsigned char buffer[4] = { 152, 152, 152, GlobalMenuAlpha };//{ color.r(), color.g(), color.b(), color.a() };
//
//Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1); //Texture, char array of texture, width, height
//Interfaces.pSurface->DrawSetColor(152, 152, 152, GlobalMenuAlpha); // keep this full color and opacity use the RGBA @top to set values.
//Interfaces.pSurface->DrawSetTexture(Texture); // bind texture
//
//Vertex_t Verts2[3];
//Verts2[0].x = pos.x + 145;
//Verts2[0].y = pos.y + 8;
//Verts2[1].x = pos.x + 150;
//Verts2[1].y = pos.y + 8;
//Verts2[2].x = pos.x + 147.5;
//Verts2[2].y = pos.y + 11;
//
//Interfaces.pSurface->DrawTexturedPolygon(3, Verts2);
//}
//}
//}
//
//void Init(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int sub, int ShowSetting, int ShowSelection)
//{
//Name = name;
//Amount = parts;
//
//for (int i = 0; i < parts; i++)
//{
//Parts[i] = arr[i];
//}
//
//Tab = tab;
//Setting = setting;
//offset.x = x;
//offset.y = y;
//Sub = sub;
//ControlSetting = ShowSetting;
//ShowValue = ShowSelection;
//}
//};
//
//std::vector< CSlider > Sliders;
//std::vector< CSliderDB > SlidersDB;
//std::vector< CSliderNormal > SlidersNormal;
//std::vector< CSliderFloat > SlidersFloat;
//std::vector< CButton > Buttons;
//std::vector< CDummy > Dummies;
//std::vector< CFancyButton > FancyButtons;
//std::vector< CDropBox > Dropboxes;
//std::vector< CDropBoxCTRL > CTRLDropboxes;
//std::vector< CKeyButton > KeyButtons;
//std::vector< CMenuBox > MenuBoxs;
//std::vector< CTab > Tabs;
//std::vector< CTabVerticalSlider > TabSlider;
//std::vector< CDropBoxSwitch > DropboxSwitch;
//
//std::vector< CFunctionButton > FuncButtons;
//
//int Dropboxs_Amount = 0;
//
//void AddNewButton( int Tab, int Setting, bool defult, int x, int y, char* name )
//{
//CButton Filler;
//Filler.Init( Tab, Setting, defult, x, y, name, -1 );
//Buttons.push_back( Filler );
//}
//
//void AddNewDummySlider(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
//{
//CDummy Slid;
//Slid.Init(x, y, min, max, defult, name, tab, setting, -1);
//Dummies.push_back(Slid);
//}
//
//void AddNewFancyButton(int Tab, int Setting, bool defult, int x, int y, char* Text1, char* Text2)
//{
//CFancyButton Filler;
//Filler.Init(Tab, Setting, defult, x, y, Text1,Text2, -1);
//FancyButtons.push_back(Filler);
//}
//
//void AddDummy(char* name, int tab, int setting)
//{
//CSlider Slid;
//Slid.Init(0, 0, 0, 0, 0, name, tab, setting, -1, true);
//Sliders.push_back(Slid);
//}
//
//void AddNewSlider( int x, int y, double min, double max, double defult, char* name, int tab, int setting)
//{
//CSlider Slid;
//Slid.Init( x, y, min, max, defult, name, tab, setting, -1, false);
//Sliders.push_back( Slid );
//}
//
//void AddNewSliderDB(int x, int y, double min, double max, double defult, char* name, int tab, int setting,int ShowSetting, int ShowSelection)
//{
//CSliderDB Slid;
//Slid.Init(x, y, min, max, defult, name, tab, setting, -1, ShowSetting, ShowSelection);
//SlidersDB.push_back(Slid);
//}
//
//void AddNewSliderNormal(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
//{
//CSliderNormal SliderNormal;
//SliderNormal.Init(x, y, min, max, defult, name, tab, setting, -1);
//SlidersNormal.push_back(SliderNormal);
//}
//
//void AddNewSliderFloat(int x, int y, double min, double max, double defult, char* name, int tab, int setting)
//{
//CSliderFloat SliderFloat;
//SliderFloat.Init(x, y, min, max, defult, name, tab, setting, -1);
//SlidersFloat.push_back(SliderFloat);
//}
//
//void AddNewDropbox( int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr )
//{
//CDropBox Dropper;
//Dropper.Init( x, y, tab, setting, name, parts, arr, -1 );
//Dropboxes.push_back( Dropper );//
//Dropboxs_Amount++;
//}
//
//void AddNewCTRLDropbox(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int CTRLSetting, int CTRLSettingValue)
//{
//CDropBoxCTRL Dropper;
//Dropper.Init(x, y, tab, setting, name, parts, arr, -1,CTRLSetting,CTRLSettingValue);
//CTRLDropboxes.push_back(Dropper);//
//Dropboxs_Amount++;
//}
//
//void AddNewKeyButton( int x, int y, int tab, int setting, char* name )
//{
//CKeyButton KeyButton;
//KeyButton.Init( x, y, tab, setting, name, -1 );
//KeyButtons.push_back( KeyButton );
//}
//
//void AddNewTab( char* Name, int Tab, char* Icon )
//{
//CTab Filler;
//Filler.Init( Name, Tab, Icon );
//Tabs.push_back( Filler );
//Tab_Count++;
//}
//
//void AddNewTabslider()
//{
//
//}
//
//void AddNewMenuBox( char* name, int x, int y, int w, int h, int tab )
//{
//CMenuBox Filler;
//Filler.Init( name, x, y, w, h, tab, -1 );
//MenuBoxs.push_back( Filler );
//}
//
//void AddNewFuncButton( int x, int y, DWORD function, char* name, int tab )
//{
//CFunctionButton Filler;
//Filler.Init( x, y, function, name, tab );
//FuncButtons.push_back( Filler );
//}
//
//void AddNewDropboxSwitch(int x, int y, int tab, int setting, char* name, int parts, std::vector< char* > arr, int ShowSetting, int ShowSelection)
//{
//CDropBoxSwitch Dropper;
//Dropper.Init(x, y, tab, setting, name, parts, arr, -1, ShowSetting, ShowSelection);
//DropboxSwitch.push_back(Dropper);//
//Dropboxs_Amount++;
//}
//
//extern player_info_t* Info;
//std::vector< char* > ingameNames{ "NONE", "DEAGLE", "DUALBERETTAS", "FIVESEVEN", "GLOCK", "AK47", "AUG", "AWP", "FAMAS", "G3SG1",
//"GALILAR", "M249", "M4A4", "MAC10", "P90", "UMP45", "XM1014", "PPBIZON", "MAG7", "NEGEV", "SAWEDOFF", "TEC9",
//"P2000", "MP7", "MP9", "NOVA", "P250", "SCAR20", "SG553", "SSG08", "CTKnife", "TKnife", "M4A1S", "USPS", "CZ75AUTO", "R8Revolver" };
//int page[256];
//int selected[256];
//int realselected[256];
//
//void drawselectbox( int amount, char* arr[100], int width, int height, int setting, int realvals[100] )
//{
//int startx = Menu.pos.x + width + 3;
//int starty = Menu.pos.y + height + 3;
//Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
//Interfaces.pSurface->DrawOutlinedRect( startx - 2, starty - 2, startx + 137, starty + 202 );
//
//for( int i = 0; i < 10; i++ )
//{
//int number = i + 10 * page[ setting ];
//if( number > amount )
//{
//}
//else
//{
//Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
//Interfaces.pSurface->DrawFilledRect( startx, starty + i * 20, startx + 120, starty + i * 20 + 20 );
//Interfaces.pSurface->DrawSetColor( 30, 30, 30, GlobalMenuAlpha );
//Interfaces.pSurface->DrawFilledRect( startx + 1, starty + i * 20 + 1, startx + 119, starty + i * 20 + 19 );
//if( number == selected[ setting ] )
//{
//Interfaces.pSurface->DrawT( startx + 3, starty + i * 20 + 3, CColor( 20, 200, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
//realselected[ setting ] = realvals[ number ];
//}
//else
//Interfaces.pSurface->DrawT( startx + 3, starty + i * 20 + 3, CColor( 255, 255, 255, GlobalMenuAlpha ), Hacks.Font_Controls, false, arr[ number ] );
//}
//}
//double drawbarheight = ( 10 * 200 );
//drawbarheight /= amount;
//if( drawbarheight > 200 )
//drawbarheight = 200;
//Interfaces.pSurface->DrawSetColor( 20, 200, 255, GlobalMenuAlpha );
//Interfaces.pSurface->DrawOutlinedRect( startx + 125, starty, startx + 135, starty + 200 );
//Interfaces.pSurface->DrawFilledRect( startx + 127, starty + page[ setting ] * drawbarheight, startx + 133, starty + drawbarheight + page[ setting ] * drawbarheight );
//// scroll
//if( Clicked_This_Frame )
//{
//if( !Holding_Mouse_1 )
//{
//if( !Dont_Click )
//{
//POINT Mouse;
//POINT mp;
//GetCursorPos( &mp );
//ScreenToClient( GetForegroundWindow(), &mp );
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//if( Mouse.x > startx + 125 && Mouse.y > starty && Mouse.x < startx + 135 && Mouse.y < starty + 200 )
//{
//int percentage = ( Mouse.y - starty );
//for( int i = 0; i < 10; i++ )
//{
//if( drawbarheight * i < percentage && percentage < drawbarheight * ( i + 1 ) )
//{
//page[ setting ] = i;
//}
//}
//}
//}
//}
//}
//// getting clicked
//if( Clicked_This_Frame )
//{
//if( !Holding_Mouse_1 )
//{
//if( !Dont_Click )
//{
//POINT Mouse;
//POINT mp;
//GetCursorPos( &mp );
//ScreenToClient( GetForegroundWindow(), &mp );
//Mouse.x = mp.x;
//Mouse.y = mp.y;
//if( Mouse.x > startx && Mouse.y > starty && Mouse.x < startx + 120 && Mouse.y < starty + 200 )
//{
//int percentage = ( Mouse.y - starty );
//for( int i = 0; i < 10; i++ )
//{
//if( 20 * i < percentage && percentage < 20 * ( i + 1 ) )
//{
//int number = i + 10 * page[ setting ];
//selected[ setting ] = number;
//}
//}
//}
//}
//}
//}
//}
//
//void skinchanger()
//{
//}
//
//void SetupMenu()
//{
///*char* arr[512] = { "ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR","ERROR", };
//
////Tabs
//AddNewTab( "A", Tab_Ragebot, "a" );
//AddNewTab( "B", Tab_Visuals, "c" );
//AddNewTab( "C", Tab_Misc, "d" );
//AddNewTab("F", Tab_Colors, "g");
//AddNewTab("E", Tab_Skins, "e");
//AddNewTab( "D", Tab_LegitBot, "b" );
//
//
//
//
//
//{
//
//AddNewMenuBox("Rage Aimbot", 105, 15, 158, 180, Tab_Ragebot);
//{
////Dropbox Config
//std::vector< char* > Selection = { "Distance", "Distance","Cycle" };
//std::vector< char* > Hitbox = { "Head", "Head", "Neck", "Chest", "Pelvis" };
//std::vector< char* > MultipointType = { "Pointscale", "Pointscale", "Max", };
//std::vector< char * > MultiBox = { "Off", "Off", "Important", "Max" };
//
////Controls
//AddNewButton(Tab_Ragebot, Ragebot_AimbotEnabled, false, 110, 25, "Enable Aimbot");
//AddNewButton(Tab_Ragebot, Ragebot_AutoShoot, false, 110, 45, "Automatically Shoot");
//AddNewButton(Tab_Ragebot, Ragebot_Autoscope, false, 110, 65, "Automatically Scope");
//AddNewButton(Tab_Ragebot, Ragebot_Autorevolver, false, 110, 85, "Auto Revolver");
//AddNewButton(Tab_Ragebot, Ragebot_SilentAim, false, 110, 105, "Silent Aim");
////AddNewButton(Tab_Ragebot, Ragebot_Multipoint, false, 110, 125, "Multiple Aimpoints");
//AddNewDropbox(130, 135, Tab_Ragebot, Ragebot_Hitbox, "Hitbox", 5, Hitbox);
//AddNewDropbox(130, 170, Tab_Ragebot, Ragebot_Selection, "Select Target by:", 3, Selection);
//}
//
//AddNewMenuBox("Accuracy", 105, 205, 158, 244, Tab_Ragebot);
//{
////Dropbox Config
//std::vector< char* > Selection = { "Distance", "Distance","Cycle" };
//std::vector< char* > Hitbox = { "Head", "Head", "Neck", "Chest", "Pelvis" };
//std::vector< char* > MultipointType = { "Pointscale", "Pointscale", "Max", };
//std::vector< char * > MultiBox = { "Off", "Off", "Vitals", "Max" };
//
////Controls
//
//AddNewButton(Tab_Ragebot, Ragebot_Velocity, false, 110, 215, "Velocity Prediciton");
//AddNewDropbox(130, 245, Tab_Ragebot, Ragebot_Multibox, "Multibox", 4, MultiBox);
//AddNewButton(Tab_Ragebot, Ragebot_Multipoint, false, 110, 270, "Multipoint");
//AddNewSlider(130, 295, 0, 100, 50, "Scale", Tab_Ragebot, Ragebot_PS);
//AddNewSlider(110, 325, 0, 100, 20, "Hitchance", Tab_Ragebot, Ragebot_Hitchance);
//AddNewSlider(110, 355, 0, 100, 5, "Minimum Damage", Tab_Ragebot, Ragebot_MinDamage);
//AddNewButton(Tab_Ragebot, Ragebot_AcceptKill, false, 110, 375, "Smart Aim");
//AddNewButton(Tab_Ragebot, Ragebot_NoRecoil, false, 110, 395, "Remove Recoil");
//AddNewButton(Tab_Ragebot, Ragebot_AutoStop, false, 110, 415, "Auto Stop");
//AddNewKeyButton(220, 414, Tab_Ragebot, Ragebot_AutoStop_Key, "");
//}
//
//AddNewMenuBox("Hack vs Hack", 274, 15, 158, 212, Tab_Ragebot);
//{
////Dropbox Config
////std::vector<char*> Accuracy = { "Off", "Off", "FPS Save", "Medium", "Maximum" };
//std::vector< char* > PreferBodyAim = { "Never", "Never", "Unresolved", "Always" };
//
////Controls
//AddNewButton(Tab_Ragebot, Ragebot_AntiAimCorrection, false, 279, 25, "Resolver");
////AddNewFancyButton(Tab_Ragebot, Resolver_Switch, false, 600, 60, "Spread", "Nospread");
////AddNewButton(Tab_Ragebot, Ragebot_Resolver, false, 470, 60, "Anti Aim Resolver");
//
////AddNewDropbox(490, 70, Tab_Ragebot, Ragebot_Accuracy, "Accuracy Boost", 5, Accuracy);
//AddNewDropbox(299, 75, Tab_Ragebot, Ragebot_PreferBodyAim, "Prefer Body-Aim if", 4, PreferBodyAim);
//AddNewButton(Tab_Ragebot, Ragebot_PositionAdjustment, false, 279, 45, "Position Adjustment");
//}
//
//AddNewMenuBox("AA - Stand", 443, 15, 158, 212, Tab_Ragebot);
//{
////Dropbox Config
//std::vector< char* > Antiaim_Pitch_Stand = { "Off", "Off","Emotion", "Up", "Fake Fake-Zero", "Fake Fake-Half-Up", "Minimal", "Fake Down", "Fake Up", "Fake Zero", "Auitism", "420", "666", "4200", "Overflow Test" };
//std::vector< char* > Antiaim_RealYaw_Stand = {"Off", "Off", "Backwards", "Fake - Spin / LBY", "Fake Jitter", "Fake Jitter 2" , "Legit", "Lowerbody Rand", "Lowerbody Simple"};
////Controls
//AddNewButton(Tab_Ragebot, AntiAim_Enabled, false, 453, 25, "Enable");
//AddNewFancyButton(Tab_Ragebot, AntiAim_Switch, false, 530, 25, "Spread", "Nospread");
//
//AddNewCTRLDropbox(473, 55, Tab_Ragebot, AntiAim_Pitch, "Pitch", 7, Antiaim_Pitch_Stand, AntiAim_Switch, 0);
//AddNewCTRLDropbox(473, 55, Tab_Ragebot, AntiAim_Pitch, "Pitch", 15, Antiaim_Pitch_Stand,AntiAim_Switch, 1);
//
//AddNewDropbox(473, 85, Tab_Ragebot, AntiAim_Real_Yaw, "Yaw", 9, Antiaim_RealYaw_Stand);
//
//AddNewFancyButton(Tab_Ragebot, AntiAim_AtTargets, false, 473, 110, "Relative to view", "At Target");
//AddNewButton(Tab_Ragebot, AntiAim_MMSafe, false, 473, 125, "Matchmaking Safe");
//AddNewButton(Tab_Ragebot, AntiAim_EdgeDetection, false, 453, 145, "Edge Detection");
//AddNewButton(Tab_Ragebot, AntiAim_FakeHitbox, false, 453, 165, "Fake Hitbox");
//AddNewButton(Tab_Ragebot, AntiAim_MemeWalk, false, 453, 185, "Memewalk");
//AddNewButton(Tab_Ragebot, AntiAim_AntiResolver, false, 453, 205, "Anti-LBY");
////AddNewButton(Tab_Ragebot, AntiAim_LegitTroll, false, 453, 225, "Legit Troll");
//}
//*//*
//AddNewMenuBox("AA - Move", 274, 237, 158, 212, Tab_Ragebot);
//{
////Dropbox Config
//std::vector< char* > Antiaim_Pitch_Move = { "Off", "Off", "Spread", "Nospread" };
//std::vector< char* > Antiaim_RealYaw_Move = { "Off", "Off", "WIP" };
////Controls
//AddNewButton(Tab_Ragebot, AntiAim_Enabled_Move, false, 284, 247, "Enable");
//AddNewFancyButton(Tab_Ragebot, AntiAim_Switch_Move, false, 361, 247, "Spread", "Nospread");
//
//AddNewCTRLDropbox(294, 277, Tab_Ragebot, AntiAim_Pitch_Move, "Pitch", 3, Antiaim_Pitch_Move, AntiAim_Switch_Move, 0);
//AddNewCTRLDropbox(294, 277, Tab_Ragebot, AntiAim_Pitch_Move, "Pitch", 4, Antiaim_Pitch_Move, AntiAim_Switch_Move, 1);
//
//AddNewDropbox(294, 307, Tab_Ragebot, AntiAim_Real_Yaw_Move, "Yaw", 3, Antiaim_RealYaw_Move);
//
//AddNewFancyButton(Tab_Ragebot, AntiAim_AtTargets_Move, false, 304, 332, "Relative to view", "At Target");
//AddNewButton(Tab_Ragebot, AntiAim_MMSafe_Move, false, 304, 347, "Matchmaking Safe");
//AddNewButton(Tab_Ragebot, AntiAim_EdgeDetection_Move, false, 284, 367, "Edge Detection");
//AddNewButton(Tab_Ragebot, AntiAim_FakeHitbox_Move, false, 284, 387, "Fake Hitbox");
//AddNewButton(Tab_Ragebot, AntiAim_MemeWalk_Move, false, 284, 407, "Memewalk");
//AddNewButton(Tab_Ragebot, AntiAim_AntiResolver_Move, false, 284, 427, "Anti-LBY");
////AddNewButton(Tab_Ragebot, AntiAim_LegitTroll, false, 453, 447, "Legit Troll");
//}
//
//AddNewMenuBox("AA - Jump", 443, 237, 158, 212, Tab_Ragebot);
//{
////Dropbox Config
//std::vector< char* > Antiaim_Pitch_Jump = { "Off", "Off", "Spread", "Nospread" };
//std::vector< char* > Antiaim_RealYaw_Jump = { "Off", "Off", "WIP"};
////Controls
//AddNewButton(Tab_Ragebot, AntiAim_Enabled_Jump, false, 453, 247, "Enable");
//AddNewFancyButton(Tab_Ragebot, AntiAim_Switch_Jump, false, 530, 247, "Spread", "Nospread");
//
//AddNewCTRLDropbox(473, 277, Tab_Ragebot, AntiAim_Pitch_Jump, "Pitch", 3, Antiaim_Pitch_Jump, AntiAim_Switch_Jump, 0);
//AddNewCTRLDropbox(473, 277, Tab_Ragebot, AntiAim_Pitch_Jump, "Pitch", 4, Antiaim_Pitch_Jump, AntiAim_Switch_Jump, 1);
//
//AddNewDropbox(473, 307, Tab_Ragebot, AntiAim_Real_Yaw_Jump, "Yaw", 3, Antiaim_RealYaw_Jump);
//
//AddNewFancyButton(Tab_Ragebot, AntiAim_AtTargets_Jump, false, 473, 332, "Relative to view", "At Target");
//AddNewButton(Tab_Ragebot, AntiAim_MMSafe_Jump, false, 473, 347, "Matchmaking Safe");
//AddNewButton(Tab_Ragebot, AntiAim_EdgeDetection_Jump, false, 453, 367, "Edge Detection");
//AddNewButton(Tab_Ragebot, AntiAim_FakeHitbox_Jump, false, 453, 387, "Fake Hitbox");
//AddNewButton(Tab_Ragebot, AntiAim_MemeWalk_Jump, false, 453, 407, "Memewalk");
//AddNewButton(Tab_Ragebot, AntiAim_AntiResolver_Jump, false, 453, 427, "Anti-LBY");
////AddNewButton(Tab_Ragebot, AntiAim_LegitTroll_Jump, false, 453, 447, "Legit Troll");
//}
//
//}
//
//
//{
//AddNewMenuBox("Legit Aimbot", 105, 15, 158, 434, Tab_LegitBot);
//{
//std::vector<char*> hitbox = { "Head","Head","Chest","Stomach" };
//std::vector<char*> Selection = { "Static", "Static" };
//std::vector<char*> smooth = {"Static", "Static"};
//
//AddNewButton(Tab_LegitBot, Legitbot_enable, false, 110, 25, "Enable Legitbot");
//AddNewButton(Tab_LegitBot, Legitbot_Aimonkey, false, 110, 45, "On Key");
//AddNewKeyButton(220, 44, Tab_LegitBot, Legitbot_Aimbotkey, "");
//AddNewButton(Tab_LegitBot, Legitbot_multihitbox, false, 110, 65, "Multibox");
//AddNewDropbox(130, 100, Tab_LegitBot, Legitbot_hitbox, "Hitbox Selection", 4, hitbox);
////AddNewDropbox(215, 140, Tab_LegitBot, Legitbot_fovtype, "Fov Type", 2, FovType);
//AddNewSlider(110, 130, 0, 40, 0, "Fov", Tab_LegitBot, Legitbot_fov);
////AddNewDropbox(215, 200, Tab_LegitBot, Legitbot_smoothtype, "Smooth Type", 2, SmoothType);
//AddNewSlider(110, 160, 0, 100, 0, "Smooth X", Tab_LegitBot, Legitbot_smoothY);
//AddNewSlider(110, 190, 0, 100, 0, "Smooth Y", Tab_LegitBot, Legitbot_smoothX);
////AddNewButton(Tab_LegitBot, Legitbot_rcs, false, 215, 270, "Rcs");
//AddNewSlider(110, 220, 0, 100, 0, "Rcs X", Tab_LegitBot, Legitbot_rcsforceX);
//AddNewSlider(110, 250, 0, 100, 0, "Rcs Y", Tab_LegitBot, Legitbot_rcsforceY);
//AddNewSlider(110, 280, 0, 150, 0, "Fire delay", Tab_LegitBot, Legitbot_Firedelay);
//
//}
//
///*	AddNewButton(Tab_LegitBot, Legit_Activate, false, 200, 8.5, "Active Legitbot");
//AddNewKeyButton(310, 4.5, Tab_LegitBot, Legit_Aimbot_Key, "Aim Key");
//AddNewButton(Tab_LegitBot, Legit_ME, true, 345, 7.5, "ME Aimbot");
//
//// Aimbot
//{
//
//AddNewMenuBox("Aimbot", 195, 30, 235, 217.5, Tab_LegitBot);
//{
//AddNewButton(Tab_LegitBot, Legit_Normal_Active, false, 215, 40, "Active");
//AddNewSliderNormal(215, 60, 0, 10, 4, "FOV", Tab_LegitBot, Legit_Normal_FOV);
//std::vector<char*> aimbone = { "Head", "Head", "Neck", "Chest", "Stomach" };
//AddNewDropbox(215, 90, Tab_LegitBot, Legit_Normal_SelectionBone, "Aimbone", 5, aimbone);
//std::vector<char*> aimSelection = { "Priority Only", "Priority Only", "Dynamic", "Nearest", "Random" };
//AddNewDropbox(215, 125, Tab_LegitBot, Legit_Normal_SelectionType, "Selection", 5, aimSelection);
//AddNewSliderNormal(215, 160, 0, 20, 4, "Smooth", Tab_LegitBot, Legit_Normal_Speed);
//AddNewSliderNormal(215, 190, 0.1, 20, 4, "Time", Tab_LegitBot, Legit_Normal_AimTime);
//AddNewSliderNormal(215, 220, 0, 20, 4, "Curve", Tab_LegitBot, Legit_Normal_Curve);
//}
//
//AddNewMenuBox("Rcs", 450, 30, 235, 217.5, Tab_LegitBot);
//{
//AddNewButton(Tab_LegitBot, Legit_RCS_Enable, false, 475, 40, "Active");
//std::vector<char*> rcstype = { "Aim", "Aim", "Standalone", "Aim+" };
//AddNewDropbox(475, 70, Tab_LegitBot, Legit_RCS_Type, "Type", 4, rcstype);
//AddNewSliderNormal(475, 105, 0, 2, 2, "RCS X", Tab_LegitBot, Legit_RCS_X);
//AddNewSliderNormal(475, 135, 0, 2, 2, "RCS Y", Tab_LegitBot, Legit_RCS_Y);
//AddNewSliderNormal(475, 165, 0, 20, 0, "RCS Smooth", Tab_LegitBot, Legit_RCS_Smooth);
//}
//
//}
//
////Trigger
//{
//
//AddNewMenuBox("Trigger", 195, 267.5, 235, 217.5, Tab_LegitBot);
//{
//AddNewButton(Tab_LegitBot, Trigger_Active, false, 215, 280, "Active");
//AddNewButton(Tab_LegitBot, Trigger_Type, true, 300, 280, "On Key");
//AddNewKeyButton(390, 277, Tab_LegitBot, Trigger_Key, "Key");
//std::vector<char*> Trigbone = { "All", "All", "Head", "No Legs" };
//AddNewDropbox(215, 305, Tab_LegitBot, Trigger_Hitboxs, "Selection", 4, Trigbone);
//AddNewSliderNormal(215, 335, 0, 30, 0, "Delay", Tab_LegitBot, Trigger_Delay);
//AddNewSliderNormal(215, 365, 0, 30, 0, "After", Tab_LegitBot, Trigger_After);
//AddNewButton(Tab_LegitBot, Trigger_Check_Scope, true, 215, 395, "Check Scoped");
//}
//
//AddNewMenuBox("Magnet", 450, 267.5, 235, 217.5, Tab_LegitBot);
//{
//AddNewButton(Tab_LegitBot, Trigger_Magnet_Active, false, 475, 280, "Active");
//AddNewSliderNormal(475, 300, 0, 10, 4, "FOV", Tab_LegitBot, Trigger_Magnet_FOV);
//std::vector<char*> aimbone = { "Head", "Head", "Neck", "Chest", "Stomach" };
//AddNewDropbox(475, 330, Tab_LegitBot, Trigger_Magnet_SelectionBone, "Aimbone", 5, aimbone);
//std::vector<char*> aimSelection = { "Priority Only", "Priority Only", "Dynamic", "Nearest", "Random" };
//AddNewDropbox(475, 365, Tab_LegitBot, Trigger_Magnet_SelectionType, "Selection", 5, aimSelection);
//AddNewSliderNormal(475, 395, 0, 20, 4, "Smooth", Tab_LegitBot, Trigger_Magnet_Speed);
//AddNewSliderNormal(475, 425, 0.1, 20, 4, "Time", Tab_LegitBot, Trigger_Magnet_AimTime);
//AddNewSliderNormal(475, 455, 0, 20, 4, "Curve", Tab_LegitBot, Trigger_Magnet_Curve);
//}
//
//}*//*
//}
//
//
//{
//
//AddNewMenuBox("ESP - General", 105, 15, 158, 216, Tab_Visuals);
//{
////Dropbox Config
//std::vector<char*> VisBox = { "Off" ,"Off", "Triangle", "Bounding", "Filled Box", "Headbox"  };
//std::vector<char*>BarPos = { "Left","Left","Right" ,"Split L/R"};
//
////Controls
//AddNewDropbox(110, 35, Tab_Visuals, Visuals_BoxEnabled, "Box", 6, VisBox);
//AddNewButton(Tab_Visuals, Visuals_HealthBar, false, 110, 55, "Show Healthbar");
//AddNewButton(Tab_Visuals, Visuals_ArmorBar, false, 110, 75, "Show Armorbar");
//AddNewDropbox(130, 105, Tab_Visuals, Visuals_BarPos, "Bar Positioning", 4, BarPos);
//AddNewButton(Tab_Visuals, Visuals_Skeltal, false, 110, 125, "Show Skeleton");
//AddNewButton(Tab_Visuals, Visuals_AimLines, false, 110, 145, "Show Snaplines");
//}
//
//AddNewMenuBox("ESP - Box", 105, 241, 158, 208, Tab_Visuals);
//{
////Controls
//AddNewButton(Tab_Visuals, Visuals_Weapons, false, 110, 251, "Display Weapon");
//AddNewButton(Tab_Visuals, Visuals_Ammo, false, 130, 271, "Add Ammo");
//AddNewButton(Tab_Visuals, Visuals_Name, false, 110, 291, "Display Name");
//AddNewButton(Tab_Visuals, Visuals_Scoped, false, 110, 311, "Is Scoped");
//AddNewButton(Tab_Visuals, Visuals_Flashed, false, 110, 331, "Is Flashed");
//}
//
//AddNewMenuBox("ESP - Filter", 274, 15, 158, 130, Tab_Visuals);
//{
////Controls
//AddNewButton(Tab_Visuals, Visuals_DroppedWeapons, false, 279, 25, "Dropped Weapons");
//AddNewButton(Tab_Visuals, Visuals_EspTeam, false, 279, 45, "Show Team");
//AddNewButton(Tab_Visuals, Visuals_XQZ, false, 279, 65, "Visible Only");
//AddNewButton(Tab_Visuals, Visuals_C4, false, 279, 85, "Show C4");
//AddNewButton(Tab_Visuals, Visuals_Hostage, false, 279, 105, "Show Hostages");
//}
//
//AddNewMenuBox("Infobox", 274, 155, 158, 142, Tab_Visuals);
//{
////Controls
//AddNewButton(Tab_Visuals, Visuals_InfoBox , false, 279, 165, "Show Infobox");
//AddNewButton(Tab_Visuals, Visuals_InfoLBY, false, 299, 185, "Add LBY Status");
//AddNewButton(Tab_Visuals, Visuals_InfoVel, false, 299, 205, "Add Velocity");
//AddNewButton(Tab_Visuals, Visuals_InfoAngs, false, 299, 225, "Add Viewangles");
//}
//
//AddNewMenuBox("Visuals - Misc", 443, 15, 158, 434, Tab_Visuals);
//{
//std::vector< char* > skybox = { "Default", "Default", "Cloudy 1", "Night02", "Night02b", "No Sky", "Vertigo Blue", "Baggage" };
////Controls
//AddNewButton(Tab_Visuals, Visuals_Crosshair, false, 448, 25, "Draw Custom Crosshair");
//AddNewButton(Tab_Visuals, Visuals_CrosshairDynamic, false, 468, 45, "Recoil-Based");
//AddNewButton(Tab_Visuals, Visuals_CrosshairSpread, false, 468, 65, "Show Spread");
//AddNewButton(Tab_Visuals, Visuals_NoRecoil, false, 448, 85, "Remove Visual Recoil");
//AddNewButton(Tab_Visuals, Visuals_NoFlash, false, 448, 105, "No Flash");
//AddNewButton(Tab_Visuals, Visuals_NoSmoke, false, 448, 125, "No Smoke");
//AddNewButton(Tab_Visuals, Visuals_ThirdPerson, false, 448, 145, "ThirdPerson");
//AddNewButton(Tab_Visuals, Visuals_ThirdPerson_OnKey, false, 460, 165, "On Key");
//AddNewKeyButton(538, 163, Tab_Visuals, Visuals_ThirdPerson_Key, "");
//AddNewButton(Tab_Visuals, Visuals_NoScope, false, 448, 185, "Remove Scope");
//AddNewButton(Tab_Visuals, Visuals_Asuswalls, false, 448, 205, "Transparent Walls");
//AddNewButton(Tab_Visuals, Visuals_Nightmode, false, 448, 225, "Nightmode");
//AddNewDropbox(468, 255, Tab_Visuals, Visuals_Skyboxchanger, "Skybox Changer", 8, skybox);
//AddNewButton(Tab_Visuals, Visuals_EngineRadar, false, 448, 285, "Engine Radar");
//AddNewButton(Tab_Visuals, Visuals_Watermark, true, 448, 305, "Watermark");
//AddNewButton(Tab_Visuals, Visuals_Hitmarker, false, 448, 325, "Hitmarker");
//}
//
//AddNewMenuBox("Chams", 274, 307, 158, 142, Tab_Visuals);
//{
////Controls
//
//std::vector<char*> ChamsPlayer = { "Off", "Off", "Color", "Semi Invisible", "Invisible", "Rainbow" };
//std::vector<char*> ChamsWeapon = { "Off", "Off", "Color", "Semi Invisible", "Invisible", "Rainbow" };
//
//AddNewButton(Tab_Visuals, Visuals_Chams, false, 279, 312, "Enable");
//AddNewDropbox(289, 342, Tab_Visuals, Visuals_Chams_Player, "Player", 6, ChamsPlayer);
//AddNewDropbox(289, 372, Tab_Visuals, Visuals_Chams_Weapons, "Weapons", 6, ChamsWeapon);
//AddNewButton(Tab_Visuals, Visuals_ChamsXQZ, false, 279, 397, "Only Visible");
//AddNewButton(Tab_Visuals, Visuals_ChamsTeam, false, 279, 417, "Show Team");
//}
//
//}
//
//
//{
//
//AddNewMenuBox("Miscellaneous I", 105, 15, 158, 434, Tab_Misc);
//{
////Dropbox Config
//std::vector< char* > AutoStraferMode = { "Silent", "Silent", "Normal", "Sideways", "W Only" };
//std::vector< char* > ClanTag = { "Astrium", "Astrium", "No Vac On Linux", "Resolved", "unityhacks '", "Mutiny.pw -", "1'd", "Invis name", "Fck The Scoreboard", "Fck The Scoreboard 2", "Astrium" };
//std::vector< char* > Fakelag = { "Off", "Off", "Maximum", "Adaptive", "Switch", "Step", "Random" };
//std::vector< char* > airstuck = { "Off", "Off", "Toggle", "On Key" };
//
//
////Controls
//AddNewButton(Tab_Misc, Misc_AutoJump, false, 110, 25, "Auto Jump");
//AddNewButton(Tab_Misc, Misc_AutoStrafe, false, 110, 45, "Auto Strafe");
//AddNewDropbox(125, 65, Tab_Misc, Misc_AutoStraferMode, "", 5, AutoStraferMode);
//AddNewDropbox(110, 95, Tab_Misc, Misc_FakeLag, "Fake Lag", 6, Fakelag);
//AddNewButton(Tab_Misc, Misc_ZStrafe, false, 110, 125, "Z Strafe");
//AddNewKeyButton(220, 123, Tab_Misc, Misc_ZStrafeKey, "");
//AddNewButton(Tab_Misc, Misc_CircleStrafe, false, 110, 145, "Circle Strafe");
//AddNewKeyButton(220, 143, Tab_Misc, Misc_CircleStrafeKey, "");
////AddNewButton(Tab_Misc, Misc_AutoAccept, true, 110, 180, "Auto Accept");
////AddNewButton(Tab_Misc, Misc_Aimstep, false, 110, 190, "Aimstep");
//AddNewButton(Tab_Misc, Misc_ClanTagSpammer, false, 110, 165, "Clan Tag");
//AddNewDropbox(125, 185, Tab_Misc, Misc_ClanTagSelection, "", 11, ClanTag);
//AddNewFancyButton(Tab_Misc, Misc_ClanTagAnimate, false, 125, 205, "Normal", "Animated");
////AddNewFancyButton(Tab_Misc, Misc_UI, false, 105, 350, "Normal UI", "Custom UI");
//AddNewButton(Tab_Misc, Misc_Freecam, false, 110, 225, "Freecam");
//AddNewKeyButton(220, 223, Tab_Misc, Misc_Freecam_Key, "");
//AddNewSliderNormal(110, 253, 0, 10, 5, "Freecam Speed", Tab_Misc, Misc_Freecam_Speed);
//AddNewButton(Tab_Misc, Misc_Fakewalk, false, 110, 275, "Fakewalk");
//AddNewKeyButton(220, 273, Tab_Misc, Misc_Fakewalk_Key, "");
//AddNewDropbox(110, 305, Tab_Misc, Misc_Airstuck_Enable, "Airstuck", 4, airstuck);
////AddNewButton(Tab_Misc, Misc_Airstuck_Enable, false, 110, 350, "Airstuck");
//AddNewKeyButton(220, 290, Tab_Misc, Misc_Airstuck_Key, "");
//}
//AddNewMenuBox("Miscellaneous II", 274, 15, 158, 212, Tab_Misc);
//{
////Controls
//AddNewFancyButton(Tab_Misc, Misc_AntiUntrusted, true, 284, 30, "Anti Untrusted Off", "Anti Untrusted On");
//AddNewFancyButton(Tab_Misc, Misc_Menukeyenable, false, 284, 50, "Insert", "Menu Key:");
//AddNewKeyButton(370, 47, Tab_Misc, Misc_Menukey, "");
////AddNewButton(Tab_Misc, Misc_Playerbox, false, 284, 70, "Show Playerbox");
//}
//AddNewMenuBox("Other", 443, 15, 158, 212, Tab_Misc);
//{
////Dropbox Config
//std::vector< char* > VM = { "Off", "Off", "SliderValue", "Low Auitismo", "High Auitismo", "CoD" };
//
////Controls
//AddNewButton(Tab_Misc, Misc_Chatspam, false, 453, 30, "Chatspam");
//AddNewFancyButton(Tab_Misc, Misc_KnifeBot, false, 453, 50, "Knife Bot Off", "Knife Bot On");
//AddNewFancyButton(Tab_Misc, Misc_BlockBot, false, 453, 70, "Block Bot Off", "Block Bot On");
//AddNewKeyButton(563, 69, Tab_Misc, Misc_BlockBot_Key, "");
//
//AddDummy("dummyother", Tab_Misc, Misc_DummyOther);
//AddNewButton(Tab_Misc, Misc_FovEnabled, false, 453, 90, "Override FOV");
//AddNewSlider(473, 110, 0, 200, 90, "", Tab_Misc, Misc_FovValue);
//AddNewDropbox(453, 140, Tab_Misc, Misc_ViewmodelChanger, "Override Viewmodel", 6, VM);
//AddNewSlider(473, 160, 0, 200, 68, "", Tab_Misc, Misc_ViewmodelValue);
//
//
//}
//AddNewMenuBox("Config", 274, 238, 327, 211, Tab_Misc);
//{
//std::vector< char* > ConfigType = { "Legit", "Legit", "HvH", "Rage", "Casual", "Custom 1", "Custom 2" };
//std::vector< char* > wgroup = { "Current", "Rifle", "Pistol", "Auto Sniper", "Awp", "Scout", "Shotgun", "SMG", "Heavy", "Current" };
//
//AddNewFuncButton(279, 247, (DWORD)LoadPrebuildRage, "Load Rage", Tab_Misc);
//AddNewFuncButton(279, 267, (DWORD)LoadPrebuildHvH, "Load HvH", Tab_Misc);
//AddNewFuncButton(279, 287, (DWORD)LoadPrebuildLegit, "Load Legit", Tab_Misc);
//
////Controls
//AddNewFuncButton(443, 247, (DWORD)LoadSettings, "Load Config", Tab_Misc);
//AddNewFuncButton(443, 267	, (DWORD)SaveSettings, "Save Config", Tab_Misc);
////AddNewFuncButton(443, 284, (DWORD)ResetSettings, "Reset Config", Tab_Misc);
//AddNewFuncButton(443, 287, (DWORD)Unhook, "Unload Cheat", Tab_Misc);
//AddNewDropbox(443, 324, Tab_Misc, Config_type, "Config", 7, ConfigType);
//
//AddNewButton(Tab_Misc, Misc_WeaponConfigs, false, 443, 354, "Enabled");
//AddNewDropbox(453, 384, Tab_Misc, Misc_WhichWeapon, "Weapon Group", 10, wgroup);
//}
//
//}
//
//
//{
//
///* Links */
///*
//AddNewMenuBox("Interface", 105, 15, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
////AddNewSlider(115, 30, 0, 255, 70, "Red", Tab_Colors, DummyMeme);
//AddNewSlider(115, 30, 0, 255, 70, "Red", Tab_Colors, Colors_Interface_R);
//AddNewSlider(115, 60, 0, 255, 70, "Green", Tab_Colors, Colors_Interface_G);
//AddNewSlider(115, 90, 0, 255, 255, "Blue", Tab_Colors, Colors_Interface_B);
//}
//
//AddNewMenuBox("Current Tab", 274, 15, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(284, 30, 0, 255, 255, "Red", Tab_Colors, Colors_CurrentTab_R);
//AddNewSlider(284, 60, 0, 255, 255, "Green", Tab_Colors, Colors_CurrentTab_G);
//AddNewSlider(284, 90, 0, 255, 255, "Blue", Tab_Colors, Colors_CurrentTab_B);
//}
//
//AddNewMenuBox("Tabs", 443, 15, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(453, 30, 0, 255, 100, "Red", Tab_Colors, Colors_Tabs_R);
//AddNewSlider(453, 60, 0, 255, 100, "Green", Tab_Colors, Colors_Tabs_G);
//AddNewSlider(453, 90, 0, 255, 100, "Blue", Tab_Colors, Colors_Tabs_B);
//}
//
//*/		/* Mitte */
///*
//AddNewMenuBox("Chams CT Visible", 105, 163, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(115, 178, 0, 255, 0, "Red", Tab_Colors, Chams_CT_Visible_R);
//AddNewSlider(115, 208, 0, 255, 200, "Green", Tab_Colors, Chams_CT_Visible_G);
//AddNewSlider(115, 238, 0, 255, 255, "Blue", Tab_Colors, Chams_CT_Visible_B);
//}
//
//AddNewMenuBox("Chams T Visible", 274, 163, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(284, 178, 0, 255, 200, "Red", Tab_Colors, Chams_T_Visible_R);
//AddNewSlider(284, 208, 0, 255, 255, "Green", Tab_Colors, Chams_T_Visible_G);
//AddNewSlider(284, 238, 0, 255, 0, "Blue", Tab_Colors, Chams_T_Visible_B);
//}
//
//AddNewMenuBox("Esp CT", 443, 163, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(453, 178, 0, 255, 0, "Red", Tab_Colors, Esp_CT_R);
//AddNewSlider(453, 208, 0, 255, 200, "Green", Tab_Colors, Esp_CT_G);
//AddNewSlider(453, 238, 0, 255, 255, "Blue", Tab_Colors, Esp_CT_B);
//}
//
///* Rechts*/
//
///*	AddNewMenuBox("Chams CT Invisible", 105, 312, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(115, 327, 0, 255, 0, "Red", Tab_Colors, Chams_CT_Invisible_R);
//AddNewSlider(115, 357, 0, 255, 255, "Green", Tab_Colors, Chams_CT_Invisible_G);
//AddNewSlider(115, 387, 0, 255, 200, "Blue", Tab_Colors, Chams_CT_Invisible_B);
//}
//
//AddNewMenuBox("Chams T Invisible", 274, 312, 158, 107.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(284, 327, 0, 255, 255, "Red", Tab_Colors, Chams_T_Invisible_R);
//AddNewSlider(284, 357, 0, 255, 200, "Green", Tab_Colors, Chams_T_Invisible_G);
//AddNewSlider(284, 387, 0, 255, 0, "Blue", Tab_Colors, Chams_T_Invisible_B);
//}
//
//AddNewMenuBox("ESP T", 443, 312, 158, 137.3, Tab_Colors);
//{
//AddDummy("rjrejehgeh", Tab_Colors, DummyMeme);
//AddNewSlider(453, 327, 0, 255, 255, "Red", Tab_Colors, Esp_T_R);
//AddNewSlider(453, 357, 0, 255, 200, "Green", Tab_Colors, Esp_T_G);
//AddNewSlider(453, 387, 0, 255, 0, "Blue", Tab_Colors, Esp_T_B);
//}
//
//AddNewFuncButton(276, 427, (DWORD)RestoreOldSettings, "Restore Default", Tab_Colors);
//
//}
//
//
//{
//AddNewButton(Tab_Skins, Skins_Enable, false, 105, 7.5, "Enable Skins");
//
///*AddNewMenuBox("Knifes", 195, 30, 235, 130, Tab_Skins);
//{
//std::vector<char*> knife = {"Off", "Off", "Bayonet", "Karambit", "Flip Knife", "Butterfly", "M9 Bayonett", "Gut Knife", "Huntsman Knife", "Shadow Daggers", "Bowie Knife", "Falchion Knife"};
//std::vector<char*> knife_skin = { "Off", "Off" };
//
//AddNewDropbox(205, 50, Tab_Skins, Skins_Knife, "Knife", 12, knife);
//AddNewDropbox(205, 85, Tab_Skins, Skins_Knife_Skin, "Skin", 2, knife_skin);
//AddNewSliderFloat(205, 115, 0, 1, 0, "Float", Tab_Skins, Skins_Knife_Float);
//}
//AddNewMenuBox("Gloves", 450, 30, 235, 130, Tab_Skins);
//{
//std::vector<char*> glove = { "Off", "Off", "Bloodhound Gloves", "Driver Gloves", "Hand Wraps", "Moto Gloves", "Specialist Gloves", "Sport Gloves"};
//std::vector<char*> glove_skin = { "Off", "Off" };
//
//AddNewDropbox(465, 50, Tab_Skins, Skins_Glove, "Glove", 8, glove);
//AddNewDropbox(465, 85, Tab_Skins, Skins_Glove_Skin, "Skin", 2, glove_skin);
//AddNewSliderFloat(465, 115, 0, 1, 0, "Float", Tab_Skins, Skins_Glove_Float);
//
//}
//AddNewMenuBox("Sniper", 195, 150, 235, 130, Tab_Skins);
//{
//std::vector<char*> sniper = { "Off", "Off", "Scout", "AWP", "Scar-20", "G3SG1" };
//std::vector<char*> sniper_skin = { "Off", "Off" };
//
//AddNewDropbox(205, 290, Tab_Skins, Skins_Sniper, "Sniper", 6, sniper);
//AddNewDropbox(205, 325, Tab_Skins, Skins_Sniper_Skin, "Skin", 2, sniper_skin);
//AddNewSliderFloat(205, 355, 0, 1, 0, "Float", Tab_Skins, Skins_Sniper_Float);
//}
//AddNewMenuBox("Pistols", 195, 270, 235, 130, Tab_Skins);
//{
//std::vector<char*> pistol = { "Off", "Off", "USP", "P2000", "Glock", "Duals", "P250", "Five Seven", "Tec-9", "CZ", "Deagle", "Revolver" };
//std::vector<char*> pistol_skin = { "Off", "Off" };
//
//AddNewDropbox(205, 170, Tab_Skins, Skins_Pistol, "Pistols", 12, pistol);
//AddNewDropbox(205, 205, Tab_Skins, Skins_Pistol_Skin, "Skin", 2, pistol_skin);
//AddNewSliderFloat(205, 235, 0, 1, 0, "Float", Tab_Skins, Skins_Pistol_Float);
//}
//AddNewMenuBox("Rifles", 450, 150, 235, 130, Tab_Skins);
//{
//std::vector<char*> rifles_famas = { "Off", "Off", "Roll Cage", "Mecha Industries", "Djinn", "Afterimage", "Valence", "Neural Net", "Sergeant", "Pulse", "Styx", "Spitfire", "Macabre", "Survivor Z", "Hexane", "DoomKktty", "Teardown", "Cyanospatter", "Colony", "Contrast Spray" };
//
//std::vector<char*> rifles_galil = { "Off", "Off", "Chatterbox", "Sugar Rush", "Eco", "Crimson Tsunami", "Firefight", "Stone Cold", "Orange DDPAT", "Cerberus", "Black Sand", "Rocket Pop", "Kami", "Blue Titanium", "Sandstorm", "Shattered", "Aqua Terrace" };
//
//std::vector<char*> rifles_m4a4 = { "Off", "Off", "Howl", "Buzz Kill", "The Battlestar", "Royal Paladin", "Bullet Rain", "Desert-Strike", "Asiimov", "X-Ray", "Hellfire", "Desolate Space", "Dragon King", "Poseidon", "Evil Daimyo", "Griffin", "Zirka", "Daybreak" };
//
//std::vector<char*> rifles_m4a1 = { "Off", "Off", "Mecha Industries", "Chantico's Fire", "Golden Coil", "Hyper Beast", "Cyrex", "Decimator", "Atomic Alloy", "Guardian", "Hot Rod", "Knight", "Master Piece", "Flashback", "Basilisk", "Bright Water", "Dark Water", "Icarus Fell", "Nitro" };
//
//std::vector<char*> rifles_ak47 = { "Off", "Off", "Bloodsport", "Neon Revolution", "Fuel Injector", "Aquamarine Revenge", "Wasteland Rebel", "Jaguar", "Vulcan", "Fire Serpent", "Point Disarray", "Frontside Misty", "Cartel", "Redline", "Case Hardened", "Red Laminate", "Hydroponic", "Jet Set", "Orbit Mk01", "Blue Laminate" };
//
//std::vector<char*> rifles_aug = { "Off", "Off", "Chameleon", "Akihabara Accept", "Syd Mead", "Fleet Flock", "Bengal Tiger", "Aristocrat", "Torque", "Ricochet", "Wings", "Anodized Navy", "Hot Rod", "Daedalus" };
//
//std::vector<char*> rifles_sg553 = { "Off", "Off", "Cyrex", "Triarch", "Tiger Moth", "Pulse", "Bulldozer", "Aerial", "Atlas", "Wave Spray", "Ultraviolet", "Anodized Navy", "Damascus Steel" };
//
//AddNewDropbox(465, 170, Tab_Skins, Skins_Famas, "Famas", 20, rifles_famas);
//
//AddNewDropbox(465, 205, Tab_Skins, Skins_Galil, "Galil AR", 17, rifles_galil);
//
//AddNewDropbox(465, 235, Tab_Skins, Skins_M4a4, "M4A4", 18, rifles_m4a4);
//
//AddNewDropbox(465, 265, Tab_Skins, Skins_M4a1, "M4A1-S", 19, rifles_m4a1);
//
//AddNewDropbox(465, 295, Tab_Skins, Skins_Ak47, "AK-47", 20, rifles_ak47);
//
//AddNewDropbox(465, 325, Tab_Skins, Skins_Aug, "AUG", 14, rifles_aug);
//
//AddNewDropbox(465, 355, Tab_Skins, Skins_SG553, "SG 553", 13, rifles_sg553);
//
//AddNewSliderFloat(465, 385, 0, 1, 0, "Float", Tab_Skins, Skins_Rifles_Float);
//}*/
//
///*	}*/
///*
//}
//
//void DrawMenu()
//{
//static bool firsttime = true;
//Dont_Click = false;
//
//if (firsttime)
//{
//SetupMenu();
//GlobalMenuAlpha = 255;
//firsttime = false;
//}
//
//if(Options.Misc.Misc2.bEnableMenuKey)
//{
//int MenuKey = Options.Misc.Misc2.iMenuKey;
//
//static int Clock = 0;
//if (GlobalMenuAlpha == 0 || GlobalMenuAlpha == 255)
//if (GetKeyPress(MenuKey))
//{
//Clock = 0;
//Menu.Opened = !Menu.Opened;
//std::string msg = "cl_mouseenable " + std::to_string(!Menu.Opened);
//Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
//}
//
//double timeSoFar1 = (double)Clock / 70.f;
//Clock++;
//}
//else if(!Options.Misc.Misc2.bEnableMenuKey)
//{
//static int Clock = 0;
//if (GlobalMenuAlpha == 0 || GlobalMenuAlpha == 255)
//if (GetKeyPress(VK_INSERT))
//{
//Clock = 0;
//Menu.Opened = !Menu.Opened;
//std::string msg = "cl_mouseenable " + std::to_string(!Menu.Opened);
//Interfaces.pEngine->ClientCmd_Unrestricted(msg.c_str(), 0);
//}
//
//double timeSoFar1 = (double)Clock / 70.f;
//Clock++;
//}
//
///* UPDATE KEYS *//*
//std::copy( keys, keys + 255, oldKeys );
//for( int x = 0; x < 255; x++ )
//{
//keys[ x ] = ( GetAsyncKeyState( x ) );
//}
//
///*if (Menu.Opened)
//{
//if (GlobalMenuAlpha != 255)
//if (GlobalMenuAlpha > 255)
//GlobalMenuAlpha = 255;
//else
//GlobalMenuAlpha = timeSoFar1 * 255.f;
//}
//else if (GlobalMenuAlpha != 0)
//{
//if (GlobalMenuAlpha < 0)
//GlobalMenuAlpha = 0;
//else
//GlobalMenuAlpha = 255 - (timeSoFar1 * 255.f);
//}*/
///*
//if (!Menu.Opened)
//return;
//
//if( !( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 ) )
//{
//Holding_Mouse_1 = false;
//}
//if( GetAsyncKeyState( VK_LBUTTON ) & 0x8000 )
//{
//Clicked_This_Frame = true;
//}
//else
//{
//Clicked_This_Frame = false;
//}
//
//Menu.Update_Frame();
//
//auto BuildNumber = Interfaces.pEngine->GetEngineBuildNumber();
//
////Drawing the menu base
//DrawMenuBase();
//
//// Horizontale Linie zwischen tabs und Feautres
///*Interfaces.pSurface->DrawSetColor( 5, 5, 5, GlobalMenuAlpha );
//Interfaces.pSurface->DrawFilledRect( Menu.pos.x - 2, Menu.pos.y - 2, Menu.pos.x + 707, Menu.pos.y + 497 );
//
//// Vertikale Linie zwischen tabs und Icon
//Interfaces.pSurface->DrawSetColor( 75, 75, 75, GlobalMenuAlpha );
//Interfaces.pSurface->DrawOutlinedRect( Menu.pos.x - 1, Menu.pos.y - 1, Menu.pos.x + 706, Menu.pos.y + 496 );
//
//// Menu Shadow
//Interfaces.pSurface->DrawSetColor( 22.5, 22.5, 22.5, GlobalMenuAlpha );
//Interfaces.pSurface->DrawFilledRect( Menu.pos.x, Menu.pos.y, Menu.pos.x + 175, Menu.pos.y + 495 );
//
//// Menu Shadow
//Interfaces.pSurface->DrawSetColor( 25, 25, 25, GlobalMenuAlpha );
//Interfaces.pSurface->DrawFilledRect( Menu.pos.x + 176, Menu.pos.y, Menu.pos.x + 705, Menu.pos.y + 495 );
//
//// Shadow für Die linien
//Interfaces.pSurface->DrawSetColor( 75, 75, 75, GlobalMenuAlpha );
//Interfaces.pSurface->DrawLine( Menu.pos.x + 174, Menu.pos.y, Menu.pos.x + 174, Menu.pos.y + 495 );
//Interfaces.pSurface->DrawLine( Menu.pos.x + 10, Menu.pos.y + 140, Menu.pos.x + 165, Menu.pos.y + 140 );
//
//Interfaces.pSurface->DrawSetColor( 5, 5, 5, GlobalMenuAlpha );
//Interfaces.pSurface->DrawLine( Menu.pos.x + 10, Menu.pos.y + 141, Menu.pos.x + 165, Menu.pos.y + 141 );
//
//Interfaces.pSurface->DrawString(Hacks.Font_Logo, Menu.pos.x + 5, Menu.pos.y + 12.5, 0, CColor(12, 23, 25, GlobalMenuAlpha), L"自閉症児"); // Schatten?! // الخوض
//Interfaces.pSurface->DrawString(Hacks.Font_Logo, Menu.pos.x + 5, Menu.pos.y + 17.5, 0, CColor(0, 200, 255, GlobalMenuAlpha), L"自閉症児"); // Text
//Interfaces.pSurface->DrawT2(Menu.pos.x + 45, Menu.pos.y + 70, CColor(255, 255, 255, (GlobalMenuAlpha / 255.f) * 240.f), Hacks.Font_MenuTitle, true, "Astrium");
//Interfaces.pSurface->DrawT2(Menu.pos.x + 30, Menu.pos.y + 85, CColor(255, 255, 255, (GlobalMenuAlpha / 255.f) * 240.f), Hacks.Font_MenuTitle, true, "Build Version: 13595");
//Interfaces.pSurface->DrawT2(Menu.pos.x + 30, Menu.pos.y + 95, CColor(255, 255, 255, (GlobalMenuAlpha / 255.f) * 240.f), Hacks.Font_MenuTitle, true, "Build Date: 18.07.17");*/
///*
//for( CTab& Tab : Tabs )
//Tab.Draw();
//
//for( CMenuBox& MenuBox : MenuBoxs )
//MenuBox.Draw();
//
//for( CFunctionButton& FuncButton : FuncButtons )
//FuncButton.Draw();
//
//for( CKeyButton& KeyButton : KeyButtons )
//KeyButton.Draw();
//
//for( CSlider& slider : Sliders )
//slider.Draw();
//
//for (CSliderDB& sliderDB : SlidersDB)
//sliderDB.Draw();
//
//for (CSliderNormal& SliderNormal : SlidersNormal)
//SliderNormal.Draw();
//
//for (CSliderFloat& SliderFloat : SlidersFloat)
//SliderFloat.Draw();
//
//for( CButton& Button : Buttons )
//Button.Draw();
//
//for (CFancyButton& Button : FancyButtons)
//Button.Draw();
//
//std::reverse( Dropboxes.begin(), Dropboxes.end() );
//
//for( CDropBox& Dropbox : Dropboxes )
//Dropbox.Draw();
//
//for (CDropBoxCTRL& Dropbox : CTRLDropboxes)
//Dropbox.Draw();
//
//for (CDropBoxSwitch& DropboxSwitch : DropboxSwitch)
//DropboxSwitch.Draw();
//
//std::reverse( Dropboxes.begin(), Dropboxes.end() );
//
//if( Menu.Opened )
//{
//DrawMouse();
//for( CTab& Tab : Tabs )
//Tab.Update();
//
//for( CMenuBox& MenuBox : MenuBoxs )
//MenuBox.Update();
//
//for (CDropBoxCTRL& Dropbox : CTRLDropboxes)
//Dropbox.Update();
//for( CDropBox& Dropbox : Dropboxes )
//Dropbox.Update();
//
//for( CSlider& slider : Sliders )
//slider.Update();
//
//for (CSliderDB& slider : SlidersDB)
//slider.Update();
//
//for (CSliderNormal& SliderNormal : SlidersNormal)
//SliderNormal.Update();
//
//for (CSliderFloat& SliderFloat : SlidersFloat)
//SliderFloat.Update();
//
//for( CButton& Button : Buttons )
//Button.Update();
//
//for (CFancyButton& Button : FancyButtons)
//Button.Update();
//
//for( CKeyButton& KeyButton : KeyButtons )
//KeyButton.Update();
//
//for( CFunctionButton& FuncButton : FuncButtons )
//FuncButton.Update();
//
//for (CDropBoxSwitch& DropboxSwitch : DropboxSwitch)
//DropboxSwitch.Update();
//
//}
//if( Clicked_This_Frame )
//{
//Holding_Mouse_1 = true;
//}
//}
//*/
