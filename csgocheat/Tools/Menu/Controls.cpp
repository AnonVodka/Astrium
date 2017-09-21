#pragma once
#include "../../stdafx.h"
//#include "XorStr.hpp"

CColor LightGray = CColor(170, 170, 170, 255);
CColor Gray = CColor(150, 150, 150, 255);
CColor DarkGray = CColor(25, 26, 25, 255);
CColor MainColor = CColor(255, 188, 88, 255);
CColor MiddleGray = CColor(42, 43, 42, 255);
CColor Black = CColor(14, 14, 14, 255);

DWORD DefaultFont = 0;
bool IsClicked = false;
bool IsClicked2 = false;
bool ClickedThisTick1 = false;
bool ClickedThisTick2 = false;
bool HoldingOtherMenu = false;
bool firstclicked = true;
bool firstclicked2 = true;
int alpha = 255;
/*
void CControl::AddControl(CControl *control)
{
control->parent = this;
controls.push_back(control);
}
void CControl::SetWindow(CControl *window)
{
window->parent = this;
this->window = window;
}

CWindow::CWindow(int x, int y, int width, int height, char* name)
{
this->x = x; this->y = y; this->width = width; this->height = height; this->name = name; type = "Window";
}
bool CWindow::Draw(int Windowx, int Windowy, int add)
{
RECT nameSize = GetTextSize(DefaultFont, name);
actualdrawx = x; actualdrawy = y;
DrawRect(x, Windowy + y, Windowx + x + width, Windowy + y + 20, MainColor);
DrawRect(Windowx + x, Windowy + y+20, Windowx + x + width, Windowy + y + height, Black);
Interfaces.pSurface->DrawT(Windowx + x + (width / 2) - (nameSize.right / 2), Windowy + y + 10.f - (nameSize.bottom / 2), LightGray, DefaultFont, false, name);
int curheight = 0;

for each(CControl *control in controls)
{
control->Draw(Windowx + x + 10, Windowy + y + 25 + curheight, 0);
curheight += control->drawnheight + 5;
}
height = 25 + curheight;
this->originalx = actualdrawx; this->originaly = actualdrawy;
return false;
}
bool CWindow::Check(int Windowx, int Windowy, int add)
{
actualdrawx = Windowx + x; actualdrawy = Windowy + y;
RECT nameSize = GetTextSize(DefaultFont, name);
POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
if (!IsClicked)
{
if (holdingmenu)
HoldingOtherMenu = false;
holdingmenu = false;
}
if (HoldingOtherMenu && !holdingmenu)
return false;
int MouseX = Mouse.x, MouseY = Mouse.y;
if (IsClicked)
if (MouseX >= x && MouseX <= x + width)
if (MouseY >= y && MouseY <= y + 20)
{
holdingmenu = true;
}
if(holdingmenu) {
x -= LastMouseX-MouseX;
y -= LastMouseY - MouseY;
}
LastMouseX = MouseX; LastMouseY = MouseY;
int curheight = 0;
for each(CControl *control in controls)
{
control->Check(Windowx + x + 10, Windowy + y + 25 + curheight, 0);
curheight += control->drawnheight + 5;
}
height = 25 + curheight;
return false;
}


void CWindow::Save(std::ofstream &output) {
output << std::to_string(x) << std::endl;
output << std::to_string(y) << std::endl;
output << std::to_string(originalx) << std::endl;
output << std::to_string(originaly) << std::endl;
for each(CControl *control in controls)
{
control->Save(output);
}
}
void CWindow::Load(std::ifstream &input) {
std::string line;
std::string::size_type sz;
getline(input, line);
x = std::stoi(line, &sz);
getline(input, line);
y = std::stoi(line, &sz);
getline(input, line);
originalx = std::stoi(line, &sz);
getline(input, line);
originaly = std::stoi(line, &sz);
for each(CControl *control in controls)
{
control->Load(input);
}
}

CMenu::CMenu(int x, int y, int width, int height, char* name)
{
this->x = x; this->y = y; this->width = width; this->height = height; this->name = name; type = "Menu"; drawnheight = height;
}
/*bool CMenu::Draw(int Windowx, int Windowy, int add)
{
if (!active)
return false;

actualdrawx = x; actualdrawy = y;
RECT nameSize = GetTextSize(DefaultFont, name);
DrawRect(x, y, x + width, y + 20, Teal);
DrawRect(x, y+20, x + width, y + height, Black);
Interfaces.pSurface->DrawT(x + (width / 2) - (nameSize.right / 2),  y + 10.f - (nameSize.bottom / 2), LightGray, DefaultFont, false, name);

int curheight = 0;
for each(CControl *control in controls)
{
control->Draw(Windowx + x + 10, Windowy + y + 25 + curheight, 0);
curheight += control->drawnheight + 5;
}

POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;

Vertex_t Verts[3];
Verts[0].x = MouseX;
Verts[0].y = MouseY;
Verts[1].x = MouseX + 16;
Verts[1].y = MouseY + 10;
Verts[2].x = MouseX;
Verts[2].y = MouseY + 16;

static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
unsigned char buffer[4] = { Teal._color[0], Teal._color[1], Teal._color[2], Teal._color[3] };

Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
Interfaces.pSurface->DrawSetTexture(Texturer);
Interfaces.pSurface->DrawSetColor1(Teal);
Interfaces.pSurface->DrawTexturedPolygon(3, Verts);


height = 25 + curheight;
this->originalx = actualdrawx; this->originaly = actualdrawy;
return false;
}*/
/*bool CMenu::Check(int Windowx, int Windowy, int add)
{
firstclicked = true;
RECT nameSize = GetTextSize(DefaultFont, name);
static bool once = false;
if (GetAsyncKeyState(VK_INSERT))
{
if (!once)
{
active = !active;
if (active)
Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 0", false);
else
Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1", false);
once = true;
}
}
else
once = false;
if (!active)
return false;
static auto once1 = false;
IsClicked = IsMousePressed();

POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;

ClickedThisTick1 = false;
if (IsClicked)
{
if (!once1)
{
ClickedThisTick1 = true;
once1 = true;
}
}
else
once1 = false;

if (!IsClicked)
{
if (holdingmenu)
HoldingOtherMenu = false;
holdingmenu = false;
}
if (HoldingOtherMenu && !holdingmenu)
return false;
if (IsClicked)
if (MouseX >= x && MouseX <= x + width)
if (MouseY >= y && MouseY <= y + 20)
{
holdingmenu = true;
}
if (holdingmenu) {
x -= LastMouseX - MouseX;
y -= LastMouseY - MouseY;
}
LastMouseX = MouseX; LastMouseY = MouseY;

int curheight = 0;
for each(CControl *control in controls)
{
control->Check(Windowx + x + 10, Windowy + y + 25 + curheight, 0);
curheight += control->drawnheight + 5;
}

height = 25 + curheight;
return false;
}*/

/*
void CMenu::Save(std::ofstream &output) {
output << std::to_string(x) << std::endl;
output << std::to_string(y) << std::endl;
output << std::to_string(originalx) << std::endl;
output << std::to_string(originaly) << std::endl;
for each(CControl *control in controls)
{
control->Save(output);
}
}
void CMenu::Load(std::ifstream &input) {
std::string line;
std::string::size_type sz;
getline(input, line);
x = std::stoi(line, &sz);
getline(input, line);
y = std::stoi(line, &sz);
getline(input, line);
originalx = std::stoi(line, &sz);
getline(input, line);
originaly = std::stoi(line, &sz);
for each(CControl *control in controls)
{
control->Load(input);
}
}

CSeperator::CSeperator(char* name) {
this->name = name;
}
bool CSeperator::Check(int Windowx, int Windowy, int add) { return false; }
void CSeperator::Save(std::ofstream &output) {}
void CSeperator::Load(std::ifstream &input) {}

bool CSeperator::Draw(int Windowx, int Windowy, int add) {
actualdrawx = Windowx; actualdrawy = Windowy;
RECT nameSize = GetTextSize(DefaultFont, name);
drawnheight = nameSize.bottom;
int left = parent->actualdrawx + parent->drawnwidth / 2 - nameSize.right/2;
int right = parent->actualdrawx + parent->drawnwidth / 2 + nameSize.right/2;
Interfaces.pSurface->DrawT(left, Windowy, LightGray, DefaultFont, false, name);
DrawRect(parent->actualdrawx, Windowy + drawnheight / 2 - 2, left - 6, Windowy + drawnheight / 2 + 2, Gray);
DrawRect(right + 6, Windowy + drawnheight / 2 - 2, parent->actualdrawx + parent->drawnwidth, Windowy + drawnheight / 2 + 2, Gray);
return false;
}

CTab::CTab(char* name)
{
this->name = name;
}

bool CTab::Draw(int Windowx, int Windowy, int add) {
drawnwidth = parent->drawnwidth;
actualdrawx = Windowx;
drawnheight = 0;
for (auto c : controls)
{
c->Draw(Windowx, Windowy + drawnheight, 0);
drawnheight += c->drawnheight + 5;
}
return false;
}

bool CTab::Check(int Windowx, int Windowy, int add)
{
drawnwidth = parent->drawnwidth;
actualdrawx = Windowx;
drawnheight = 0;
for (auto c : controls)
{
c->Check(Windowx, Windowy + drawnheight, 0);
drawnheight += c->drawnheight + 5;
}
return false;
}

void CTab::Save(std::ofstream &output) {

for each(CControl *control in controls)
{
control->Save(output);
}
}
void CTab::Load(std::ifstream &input) {

for each(CControl *control in controls)
{
control->Load(input);
}
}
bool CMenu::Draw(int Windowx, int Windowy, int add)
{
static char* credits = XorStr(8, 0xF4, 0xB60AD238, 0x9E1A9C08).c(); //no hex editing this shit
if (!active)
return false;
//RECT nameSize = GetTextSize1(TitleFont, L"\u7121\u6557");
RECT nameSize = GetTextSize1(TitleFont, L"天皇");
int NewX = x + 1, NewY = y + 1, NewWidth = width - 2, NewHeight = drawnheight - 2;
bool anyactive = false;
int basetaby = NewY + 85 + nameSize.bottom + (((NewHeight - 41 - (85 + nameSize.bottom)) / 2) - (controls.size() * 15) / 2);
int Usable = NewX + 85 + nameSize.right + 1;

DrawRect(x, y, x + width, y + drawnheight, MiddleGray);
DrawRect(NewX, NewY, NewX + NewWidth, NewY + NewHeight, Black);

DrawRect(NewX, NewY, Usable, NewY + NewHeight, DarkGray);
DrawRect(Usable, NewY, Usable+1, NewY + NewHeight, MiddleGray);

//Interfaces.pSurface->DrawString(TitleFont, NewX + 45, NewY + 45, 0, Black, L"\u7121\u6557");
//Interfaces.pSurface->DrawString(TitleFont, NewX + 40, NewY + 40, 0, MainColor, L"\u7121\u6557");
Interfaces.pSurface->DrawString(TitleFont, NewX + 45, NewY + 45, 0, CColor(255,255,255,255), L"天皇");
Interfaces.pSurface->DrawString(TitleFont, NewX + 40, NewY + 40, 0, MainColor, L"天皇");

DrawRect(NewX + 5, NewY + 85 + nameSize.bottom, Usable - 5, NewY + 86 + nameSize.bottom, Gray);
DrawRect(NewX + 5, NewY + NewHeight - 41, Usable - 5, NewY + NewHeight - 40, Gray);
nameSize = GetTextSize(DefaultFont, credits);
Interfaces.pSurface->DrawT(NewX + (Usable- NewX)/2 - nameSize.right/2, NewY + NewHeight - 20 - nameSize.bottom/2, Gray, DefaultFont, false, credits);

drawnwidth = NewX + NewWidth - Usable -30;
actualdrawx = Usable + 15;
drawnheight = 0;

int currenttaby = 0;

for (int i = 0; i < controls.size(); i++)
{
CControl *c = controls[i];
nameSize = GetTextSize(DefaultFont, c->name);
if (i == activeid)
{
DrawRect(NewX, basetaby + currenttaby, Usable, basetaby + currenttaby + 15, MiddleGray);
c->Draw(Usable + 15, NewY + 15, 0);
}
Interfaces.pSurface->DrawT(NewX + (Usable - NewX) / 2 - nameSize.right / 2, basetaby + currenttaby + 7.5f - nameSize.bottom / 2, Gray, DefaultFont, false, c->name);
currenttaby += 15;
if (c->drawnheight + 5 + 15 > drawnheight)
drawnheight = c->drawnheight + 5 + 15;
}

if (height > drawnheight)
drawnheight = height;
POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;

Vertex_t Verts[3];
Verts[0].x = MouseX;
Verts[0].y = MouseY;
Verts[1].x = MouseX + 16;
Verts[1].y = MouseY + 10;
Verts[2].x = MouseX;
Verts[2].y = MouseY + 16;

static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
unsigned char buffer[4] = { MainColor._color[0], MainColor._color[1], MainColor._color[2], MainColor._color[3] };

Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
Interfaces.pSurface->DrawSetTexture(Texturer);
Interfaces.pSurface->DrawSetColor1(MainColor);
Interfaces.pSurface->DrawTexturedPolygon(3, Verts);

return false;
}

bool CMenu::Check(int Windowx, int Windowy, int add) {
firstclicked = true;
firstclicked2 = true;
static bool once = false;
if (GetAsyncKeyState(VK_INSERT))
{
if (!once)
{
active = !active;
if (active)
Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 0", false);
else
Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1", false);
once = true;
}
}
else
once = false;
if (!active)
return false;
static auto once1 = false;
IsClicked = IsMousePressed();

POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;

ClickedThisTick1 = false;
if (IsClicked)
{
if (!once1)
{
ClickedThisTick1 = true;
once1 = true;
}
}
else
once1 = false;


static auto once2 = false;
IsClicked2 = IsMousePressedRight();

ClickedThisTick2 = false;
if (IsClicked2)
{
if (!once2)
{
ClickedThisTick2 = true;
once2 = true;
}
}
else
once2 = false;

int NewX = x + 1, NewY = y + 1, NewWidth = width - 2, NewHeight = drawnheight - 2;
RECT nameSize = GetTextSize1(TitleFont, L"天皇");
int Usable = NewX + 85 + nameSize.right + 1;
int basetaby = NewY + 85 + nameSize.bottom + (((NewHeight - 41 - (85 + nameSize.bottom)) / 2) - (controls.size() * 15) / 2);

if (!IsClicked)
{
HoldingOtherMenu = false;
holdingmenu = false;
}
if (HoldingOtherMenu && !holdingmenu)
return false;
if (IsClicked && firstclicked)
if (MouseX >= NewX && MouseX <= Usable)
if (MouseY >= NewY&& MouseY <= NewY + 85 + nameSize.bottom)
{
firstclicked = false;
holdingmenu = true;
}
if (holdingmenu) {
x -= LastMouseX - MouseX;
y -= LastMouseY - MouseY;
}
LastMouseX = MouseX; LastMouseY = MouseY;
int currenttaby = 0;

for (int i = 0; i < controls.size(); i++)
{
CControl *c = controls[i];
nameSize = GetTextSize(DefaultFont, c->name);
if (NewX < MouseX && MouseX < Usable)
if (basetaby + currenttaby < MouseY && MouseY < basetaby + currenttaby + 15) {
if (ClickedThisTick1 && firstclicked)
{
activeid = i;
firstclicked = false;
}
}
currenttaby += 15;
if (i == activeid)
c->Check(Usable + 15, NewY + 15, 0);

if(c->drawnheight + 5 > drawnheight)
drawnheight = c->drawnheight + 5;
}
if (height > drawnheight)
drawnheight = height;
}
CButton::CButton(int nx, int ny, int nsize, char* text)
{
x = nx; y = ny; this->height = nsize; this->width = nsize; this->name = text; type = "";
}

bool CButton::Draw(int Windowx, int Windowy, int add)
{
int nX = Windowx, nY = Windowy;
actualdrawx = nX; actualdrawy = nY;
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
if (height > nameSize.bottom)
Interfaces.pSurface->DrawT(nX, nY + (height / 2) - (nameSize.bottom / 2), LightGray, DefaultFont, false, name);
else {
Interfaces.pSurface->DrawT(nX, nY, LightGray, DefaultFont, false, name);
drawnheight = nameSize.bottom;
nY += nameSize.bottom / 2 - height / 2;
}
int boxx = parent->actualdrawx + parent->drawnwidth - width;
if (active)
DrawRect(boxx, nY, boxx + width, nY + height, MainColor);
DrawOutlinedRect(boxx, nY, boxx + width, nY + height, LightGray);
this->originalx = actualdrawx; this->originaly = actualdrawy;
return false;
}

bool CButton::Check(int Windowx, int Windowy, int add)
{
int nX = Windowx , nY = Windowy;
actualdrawx = nX; actualdrawy = nY;
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
if (!height > nameSize.bottom) {
drawnheight = nameSize.bottom;
nY += nameSize.bottom / 2 - height / 2;
}
POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;
int boxx = parent->actualdrawx + parent->drawnwidth - width;
if (ClickedThisTick1&&firstclicked)
if (MouseX >= boxx  && MouseX <= boxx + width)
if (MouseY >= nY && MouseY <= nY + height)
{
active = !active;
firstclicked = false;
}
if(active && window != nullptr)
window->Check(0, 0, 0);
return false;
}

void CButton::Save(std::ofstream &output) {
output << std::to_string(active) << std::endl;
if(window != nullptr)
window->Save(output);
}
void CButton::Load(std::ifstream &input) {
std::string line;
getline(input, line);
std::string::size_type sz;
active = std::stoi(line, &sz);
if (window != nullptr)
window->Load(input);
}

CText::CText(char* text)
{
this->name = text;
}

bool CText::Draw(int Windowx, int Windowy, int add)
{
int nX = Windowx, nY = Windowy;
actualdrawx = nX; actualdrawy = nY;
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
nX = parent->actualdrawx + parent->width - 10 - nameSize.right;
Interfaces.pSurface->DrawT(nX, nY, LightGray, DefaultFont, false, name);
drawnheight = nameSize.bottom;
return false;
}

bool CText::Check(int Windowx, int Windowy, int add)
{
return false;
}

void CText::Save(std::ofstream &output) {
}
void CText::Load(std::ifstream &input) {
}

CComboBox::CComboBox()
{
}

CComboBox::CComboBox(int xz, int yz, int height, int width, char* ttag)
{
x = xz;
y = yz;
this->width = width;
this->height = height;
name = ttag;
type = "ComboBox";
}

void CComboBox::addContent(char* ttag)
{
content.push_back(ttag);
}

bool CComboBox::Check(int Windowx, int Windowy, int add)
{
if (!ClickedThisTick1)
return false;
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
if (!height > nameSize.bottom) {
drawnheight = nameSize.bottom;
Windowy += nameSize.bottom / 2 - height / 2;
}
int boxx = parent->actualdrawx + parent->drawnwidth - width;
auto draw = height;
POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
int MouseX = Mouse.x, MouseY = Mouse.y;
if (active)
{
for (int i = 0; i < content.size(); i++)
{
if (i != activeid && content[i] != "")
{
if (ClickedThisTick1 && firstclicked)
if (MouseX >= boxx + 1 && MouseX <= boxx + width - 1)
if (MouseY >= Windowy + 1 + draw && MouseY <= Windowy + height + 1 + draw)
{
firstclicked = false;
activeid = i;
break;
}
draw += height - 1;
}
}
active = false;
}
else{
if (ClickedThisTick1 && firstclicked)
if (MouseX >= boxx && MouseX <= boxx + width)
if (MouseY >= Windowy && MouseY <= Windowy + height)
{
active = true;
firstclicked = false;
}
}
if (draw > drawnheight)
drawnheight = draw;
return false;
}

bool CComboBox::Draw(int Windowx, int Windowy, int add)
{
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
if (height > nameSize.bottom)
Interfaces.pSurface->DrawT(Windowx, Windowy + (height / 2) - (nameSize.bottom / 2), LightGray, DefaultFont, false, name);
else {
Interfaces.pSurface->DrawT(Windowx, Windowy, LightGray, DefaultFont, false, name);
drawnheight = nameSize.bottom;
Windowy += nameSize.bottom / 2 - height / 2;
}
int boxx = parent->actualdrawx + parent->drawnwidth - width;
auto draw = 0;

DrawOutlinedRect (boxx, Windowy, boxx + width, Windowy + height, LightGray);

if (content[activeid] != "")
{
DrawRect(boxx + 1, Windowy + draw + 1, boxx + width - 1, Windowy + height + draw - 1, Black);
RECT nameSize = GetTextSize(DefaultFont, content[activeid]);
Interfaces.pSurface->DrawT(boxx + 1 + (width - 2) / 2 - nameSize.right/2 , Windowy + 1 + ((height-2) / 2) - (nameSize.bottom / 2) + draw, LightGray, DefaultFont, false, content[activeid]);
draw += height-3;
}
if (active)
{
for (int i = 0; i < content.size(); i++)
{
if (i != activeid && content[i] != "")
{
DrawRect(boxx, Windowy + draw + 1, boxx + width, Windowy + height + draw+1, LightGray);
DrawRect(boxx + 1, Windowy + draw + 1, boxx + width - 1, Windowy + height + draw, Black);
RECT nameSize = GetTextSize(DefaultFont, content[i]);
Interfaces.pSurface->DrawT(boxx + (width - 2)/2 - nameSize.right/2, Windowy + 1 + (height / 2) - (nameSize.bottom / 2) + draw, LightGray, DefaultFont, false, content[i]);
draw += height-1;
}
}
draw += 1;
}
if(draw > drawnheight)
drawnheight = draw;
this->originalx = actualdrawx; this->originaly = actualdrawy;
return false;
}

void CComboBox::reset()
{
content[100] = {};
}

void CComboBox::Save(std::ofstream &output) {
output << std::to_string(activeid) << std::endl;
}
void CComboBox::Load(std::ifstream &input) {
std::string line;
getline(input, line);
std::string::size_type sz;
activeid = std::stoi(line, &sz);
}

CKey::CKey(int x, int y, int width, int height, char* text) {
this->x = x;
this->y = y;
this->width = width;
this->height = height;
this->name = text;
}

bool CKey::Draw ( int Windowx, int Windowy, int add ) {
return false;
}

bool CKey::Check ( int Windowx, int Windowy, int add ) {
return false;
}

void CKey::Save(std::ofstream &output) {
}

void CKey::Load(std::ifstream &input) {
}

CSlider::CSlider(int xz, int yz, int width, int height, float valuez, float minz, float maxz, char* ttag)
{
x = xz;
y = yz;
this->width = width;
this->height = height;
value = valuez;
max = maxz;
min = minz;
disvalue = (value - min) * (float(width) / float(max - min));
name = ttag;
type = "Slider";
}

bool CSlider::Draw(int Windowx, int Windowy, int add)
{
drawnheight = height;
int oldWindowy = Windowy;
RECT nameSize = GetTextSize(DefaultFont, name);
if (height > nameSize.bottom)
Interfaces.pSurface->DrawT(Windowx, Windowy + 6 - (nameSize.bottom / 2), LightGray, DefaultFont, false, name);
else {
Interfaces.pSurface->DrawT(Windowx, Windowy, LightGray, DefaultFont, false, name);
drawnheight = nameSize.bottom;
Windowy += nameSize.bottom / 2 - 6;
}
if (width == 0)
return false;
int sliderx = parent->actualdrawx + parent->drawnwidth - width;

char* valueText = _strdup(std::to_string((int)round(value)).c_str());
nameSize = GetTextSize(DefaultFont, valueText);
if(drawnheight != height)
Interfaces.pSurface->DrawT(sliderx - nameSize.right - 5, oldWindowy, LightGray, DefaultFont, false, valueText);
else
Interfaces.pSurface->DrawT(sliderx - nameSize.right - 5, oldWindowy + 6 - (nameSize.bottom / 2), LightGray, DefaultFont, false, valueText);

DrawRect(sliderx, Windowy + height/2 - 1, sliderx + width, Windowy + height/2 +1, LightGray);
DrawRect(sliderx + disvalue - 2, Windowy, sliderx + disvalue + 2, Windowy + height, MainColor);
this->originalx = actualdrawx; this->originaly = actualdrawy;
return false;
}

bool CSlider::Check(int Windowx, int Windowy, int add)
{
POINT Mouse;
GetCursorPos(&Mouse);
ScreenToClient(GetForegroundWindow(), &Mouse);
drawnheight = height;
RECT nameSize = GetTextSize(DefaultFont, name);
if (!height > nameSize.bottom) {
drawnheight = nameSize.bottom;
Windowy += nameSize.bottom / 2 - height / 2;
}
int sliderx = parent->actualdrawx + parent->drawnwidth - width;
if (IsClicked)
{
if (ClickedThisTick1 && firstclicked)
if (Mouse.x >= sliderx && Mouse.x <= sliderx + width)
if (Mouse.y >= Windowy && Mouse.y <= Windowy + height)
{
washolding = true;
firstclicked = false;
}
}
else
washolding = false;
if (washolding)
{
washolding = true;
value = (Mouse.x - sliderx) / (float(width) / float(max - min));
if(Step > 0)
value = round(value / Step)*Step;
if (value > max)
value = max;
if (value < min)
value = min;
disvalue = (value- min) * (float(width) / float(max - min));
}
return false;
}
void CSlider::Save(std::ofstream &output) {
output << std::to_string(value) << std::endl;
}
void CSlider::Load(std::ifstream &input) {
std::string line;
getline(input, line);
std::string::size_type sz;
value = std::stof(line, &sz);
disvalue = (value - min) * (float(width) / float(max - min));
}

*/
