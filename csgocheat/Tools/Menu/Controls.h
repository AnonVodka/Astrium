#pragma once
#include "../../stdafx.h"

extern DWORD DefaultFont;
extern CColor LightGray;
extern CColor Gray;
extern CColor DarkGray;
extern CColor MainColor;
extern CColor MiddleGray;
extern CColor Black;

class Color
{
public:
	Color()
	{
		*((int *)this) = 0;
	}
	Color(int color32)
	{
		*((int *)this) = color32;
	}
	Color(int _r, int _g, int _b)
	{
		SetColor(_r, _g, _b, 255);
	}
	Color(int _r, int _g, int _b, int _a)
	{
		SetColor(_r, _g, _b, _a);
	}

	void SetColor(int _r, int _g, int _b, int _a = 255)
	{
		_color[0] = (unsigned char)_r;
		_color[1] = (unsigned char)_g;
		_color[2] = (unsigned char)_b;
		_color[3] = (unsigned char)_a;
	}

	void GetColor(int &_r, int &_g, int &_b, int &_a) const
	{
		_r = _color[0];
		_g = _color[1];
		_b = _color[2];
		_a = _color[3];
	}

	void SetRawColor(int color32)
	{
		*((int*)this) = color32;
	}

	int GetRawColor() const
	{
		return *((int*)this);
	}

	int GetD3DColor() const
	{
		return ((int)((((_color[3]) & 0xff) << 24) | (((_color[0]) & 0xff) << 16) | (((_color[1]) & 0xff) << 8) | ((_color[2]) & 0xff)));
	}

	inline int r() const { return _color[0]; }
	inline int g() const { return _color[1]; }
	inline int b() const { return _color[2]; }
	inline int a() const { return _color[3]; }

	inline float rBase() const { return _color[0] / 255.0f; }
	inline float gBase() const { return _color[1] / 255.0f; }
	inline float bBase() const { return _color[2] / 255.0f; }
	inline float aBase() const { return _color[3] / 255.0f; }

	unsigned char &operator[](int index)
	{
		return _color[index];
	}

	const unsigned char &operator[](int index) const
	{
		return _color[index];
	}

	bool operator == (const Color &rhs) const
	{
		return (*((int *)this) == *((int *)&rhs));
	}

	bool operator != (const Color &rhs) const
	{
		return !(operator==(rhs));
	}

	Color &operator=(const Color &rhs)
	{
		SetRawColor(rhs.GetRawColor());
		return *this;
	}

	float* Base()
	{
		float clr[3];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;

		return &clr[0];
	}

	float* BaseAlpha()
	{
		float clr[4];

		clr[0] = _color[0] / 255.0f;
		clr[1] = _color[1] / 255.0f;
		clr[2] = _color[2] / 255.0f;
		clr[3] = _color[3] / 255.0f;

		return &clr[0];
	}

	//ImU32 GetU32()
	//{
	//	return ((_color[3] & 0xff) << 24) + ((_color[2] & 0xff) << 16) + ((_color[1] & 0xff) << 8)
	//		+ (_color[0] & 0xff);
	//}

	float Hue() const
	{
		if (_color[0] == _color[1] && _color[1] == _color[2])
		{
			return 0.0f;
		}

		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float delta = max - min;
		float hue = 0.0f;

		if (r == max)
		{
			hue = (g - b) / delta;
		}
		else if (g == max)
		{
			hue = 2 + (b - r) / delta;
		}
		else if (b == max)
		{
			hue = 4 + (r - g) / delta;
		}
		hue *= 60;

		if (hue < 0.0f)
		{
			hue += 360.0f;
		}
		return hue;
	}

	float Saturation() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		float l, s = 0;

		if (max != min)
		{
			l = (max + min) / 2;
			if (l <= 0.5f)
				s = (max - min) / (max + min);
			else
				s = (max - min) / (2 - max - min);
		}
		return s;
	}

	float Brightness() const
	{
		float r = _color[0] / 255.0f;
		float g = _color[1] / 255.0f;
		float b = _color[2] / 255.0f;

		float max = r > g ? r : g > b ? g : b,
			min = r < g ? r : g < b ? g : b;
		return (max + min) / 2;
	}

	static Color FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 2)
		{
			return Color(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255)
			);
		}
		else if (h < 3)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255)
			);
		}
		else if (h < 4)
		{
			return Color(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else if (h < 5)
		{
			return Color(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255)
			);
		}
		else
		{
			return Color(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255)
			);
		}
	}

	static Color Red() { return Color(255, 0, 0); }
	static Color Green() { return Color(0, 255, 0); }
	static Color Blue() { return Color(0, 0, 255); }
	static Color LightBlue() { return Color(100, 100, 255); }
	static Color Grey() { return Color(128, 128, 128); }
	static Color DarkGrey() { return Color(45, 45, 45); }
	static Color Black() { return Color(0, 0, 0); }
	static Color White() { return Color(255, 255, 255); }
	static Color Purple() { return Color(220, 0, 220); }

	//Menu
	static Color Background() { return Color(55, 55, 55); }
	static Color FrameBorder() { return Color(80, 80, 80); }
	static Color MainText() { return Color(230, 230, 230); }
	static Color HeaderText() { return Color(49, 124, 230); }
	static Color CurrentTab() { return Color(55, 55, 55); }
	static Color Tabs() { return Color(23, 23, 23); }
	static Color Highlight() { return Color(49, 124, 230); }
	static Color ElementBorder() { return Color(0, 0, 0); }
	static Color SliderScroll() { return Color(78, 143, 230); }


private:
	unsigned char _color[4];
};

inline void Clear(int x, int y, int w, int h, Color color)
{
	Interfaces.pSurface->DrawSetColor(color.r(), color.g(), color.b(), color.a());
	Interfaces.pSurface->DrawFilledRect(x, y, x + w, y + h);
}

inline void GradientV(int x, int y, int w, int h, Color c1, Color c2)
{
	Clear(x, y, w, h, c1);
	BYTE first = c2.r();
	BYTE second = c2.g();
	BYTE third = c2.b();
	for (int i = 0; i < h; i++)
	{
		float fi = i, fh = h;
		float a = fi / fh;
		DWORD ia = a * 255;
		Clear(x, y + i, w, 1, Color(first, second, third, ia));
	}
}

inline void DrawRect(int x1, int y1, int x2, int y2, CColor clr)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawFilledRect(x1, y1, x2, y2);
}

inline void DrawFade(int x1, int y1, int x2, int y2, int alpha, int alpha2, CColor clr, bool horiz = false)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawFilledRectFade(x1, y1, x2, y2, alpha, alpha2, horiz);
}

inline void DrawLine(int x1, int y1, int x2, int y2, CColor clr)
{
	int width = 0;
	int height = 0;
	Interfaces.pEngine->GetScreenSize(width, height);
	if (!(x1 < width && x1 > 0 && y1 < height && y1 > 0) || !(x2 < width && x2 > 0 && y2 < height && y2 > 0))
		return;
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawLine(x1, y1, x2, y2);
}

inline void DrawOutlinedRect(int x1, int y1, int x2, int y2, CColor clr)
{
	Interfaces.pSurface->DrawSetColor1(clr);
	Interfaces.pSurface->DrawOutlinedRect(x1, y1, x2, y2);
}


inline void DrawCircle(int x, int y, float Radius, CColor Color)
{
	int Points = Radius * 2;
	Vertex_t* Circle = new Vertex_t[Points];

	for (int i = 0; i < Points; ++i)
	{
		float Theta = 2 * PI * i / Points;
		Circle[i].Init(x + cosf(Theta) * Radius, y + sinf(Theta) * Radius);
	}

	static int Texture = NULL;

	if (!Texture)
		Texture = Interfaces.pSurface->CreateNewTextureID(true);

	unsigned char buffer[4] = { Color._color[0], Color._color[1], Color._color[2], Color._color[3] };

	Interfaces.pSurface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texture);
	Interfaces.pSurface->DrawSetColor1(Color);
	Interfaces.pSurface->DrawTexturedPolygon(Points, Circle);
	//delete[]Circle;
}

inline bool CheckCirlce(int MouseX, int MouseY, int x, int y, float Radius)
{
	if (24 >= sqrt(pow(MouseX - x, 2) + pow(MouseY - y, 2)))
	{
		return true;
	}
	return true;
}

inline RECT GetTextSize(DWORD font, const char* text)
{
	char Buffer[1024] = { '\0' };

	/* set up varargs*/
	va_list Args;

	va_start(Args, text);
	vsprintf_s(Buffer, text, Args);
	va_end(Args);

	size_t Size = strlen(Buffer) + 1;
	wchar_t* WideBuffer = new wchar_t[Size];

	mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);

	RECT rect;
	int x, y;
	Interfaces.pSurface->GetTextSize(font, WideBuffer, x, y);
	rect.left = x;
	rect.bottom = y;
	rect.right = x;
	return rect;
}

inline RECT GetTextSize1(DWORD font, const wchar_t* text)
{
	RECT rect;
	int x, y;
	Interfaces.pSurface->GetTextSize(font, text, x, y);
	rect.left = x;
	rect.bottom = y;
	rect.right = x;
	return rect;
}

inline bool IsMousePressed()
{
	return (GetAsyncKeyState(0x01));
}

inline bool IsMousePressedRight()
{
	return (GetAsyncKeyState(0x02));
}


/*
class CControl
{
public:
virtual ~CControl() {}

CControl() {}
bool active = false;
char *name = "";
char *type = "";
int actualdrawx, actualdrawy;
bool holdingmenu = false;
int x = 0, y = 0, width = 0, height = 0, drawnheight = 0, drawnwidth = 0, originalx = 0, originaly = 0;
virtual bool Draw(int x, int y, int add) = 0;
virtual bool Check(int x, int y, int add) = 0;
virtual void Save(std::ofstream &output) = 0;
virtual void Load(std::ifstream &output) = 0;
CControl* window;
CControl* parent;
std::vector<CControl*> controls;
void AddControl(CControl *control);
void SetWindow(CControl *window);
};

class CWindow : public CControl
{
public:
int LastMouseX = 0, LastMouseY = 0;
CWindow(int x, int y, int width, int height, char* name);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CSeperator : public CControl {
public:
CSeperator(char* name);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CTab : public CControl {
public:
CTab(char* name);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CMenu : public CControl
{
public:
DWORD TitleFont = 0;
int SizeX = 0, SizeY = 0;
int activeid = 0;
int LastMouseX = 0, LastMouseY = 0;
CMenu(int x, int y, int width, int height, char* name);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CButton : public CControl
{
public:
CButton(int nx, int ny, int nsize, char* text);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CText : public CControl
{
public:
CText(char* text);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CKey : public CControl
{
public:
int selectedKey = 0x00;
CKey(int x, int y, int height, int width, char* text);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual bool Check(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};

class CComboBox : public CControl
{
public:
CComboBox();
CComboBox(int xz, int yz, int height, int width, char* ttag);
int count = 0;
int activeid = 0;
std::vector<char*> content = {};

void addContent(char* ttag);
virtual bool Check(int Windowx, int Windowy, int add);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
void reset();
};

class CSlider : public CControl
{
public:
int size = 0;
float max = 0;
float min = 0;
float disvalue = 0;
float value = 0;
int Step = 0;
bool washolding = false;

CSlider(int xz, int yz, int width, int height, float valuez, float minz, float maxz, char* ttag);
CSlider(int xz, int yz, int width, int height, float valuez, float minz, float maxz, char* ttag, int Step);

virtual bool Check(int Windowx, int Windowy, int add);
virtual bool Draw(int Windowx, int Windowy, int add);
virtual void Save(std::ofstream &output);
virtual void Load(std::ifstream &output);
};
*/
