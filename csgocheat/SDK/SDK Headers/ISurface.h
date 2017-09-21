#pragma once
#include "stdafx.h"

class IMaterial;

// ---------------------------------------------------------
// Purpose: Passing position to drawing functions.
// Usage: Position{_x, _y}
// ---------------------------------------------------------
struct Position
{
public:

	int x;
	int y;
};

// ---------------------------------------------------------
// Usage: FilledCircle{Position{_x, _y}, 10f}
// ---------------------------------------------------------
struct FilledCircle
{
public:

	Position pos;
	float radius;
};

// ---------------------------------------------------------
// Purpose: 
// ---------------------------------------------------------
struct Vertex_t
{
public:

	float x;
	float y;

	Vertex_t()
	{
		x = 0;
		y = 0;
	}

	void Init(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

private:

	float tex_x = 0.f;
	float tex_y = 0.f;
};

class CColor
{
public:
	bool operator==(const CColor& v) const
	{
		return v._color == _color;
	}

	unsigned int _color[4];

	CColor(int R, int G, int B, int A)
	{
		_color[0] = (unsigned char)R;
		_color[1] = (unsigned char)G;
		_color[2] = (unsigned char)B;
		_color[3] = (unsigned char)A;
	}

	void SetColor(int r, int g, int b, int a = 0)
	{
		_color[0] = (unsigned char)r;
		_color[1] = (unsigned char)g;
		_color[2] = (unsigned char)b;
		_color[3] = (unsigned char)a;
	}

	void GetColor(int& r, int& g, int& b, int& a) const
	{
		r = _color[0];
		g = _color[1];
		b = _color[2];
		a = _color[3];
	}

	static CColor FromHSB(float hue, float saturation, float brightness)
	{
		float h = hue == 1.0f ? 0 : hue * 6.0f;
		float f = h - (int)h;
		float p = brightness * (1.0f - saturation);
		float q = brightness * (1.0f - saturation * f);
		float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if (h < 1)
		{
			return CColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(255)
			);
		}
		else if (h < 2)
		{
			return CColor(
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(255)
			);
		}
		else if (h < 3)
		{
			return CColor(
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(t * 255),
				(unsigned char)(255)
			);
		}
		else if (h < 4)
		{
			return CColor(
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(255)
			);
		}
		else if (h < 5)
		{
			return CColor(
				(unsigned char)(t * 255),
				(unsigned char)(p * 255),
				(unsigned char)(brightness * 255),
				(unsigned char)(255)
			);
		}
		else
		{
			return CColor(
				(unsigned char)(brightness * 255),
				(unsigned char)(p * 255),
				(unsigned char)(q * 255),
				(unsigned char)(255)
			);
		}
	}


	/*float Hue() const
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
	}*/

};

enum MaterialVarFlags_t
{
	MATERIAL_VAR_DEBUG = (1 << 0),
	MATERIAL_VAR_NO_DEBUG_OVERRIDE = (1 << 1),
	MATERIAL_VAR_NO_DRAW = (1 << 2),
	MATERIAL_VAR_USE_IN_FILLRATE_MODE = (1 << 3),
	MATERIAL_VAR_VERTEXCOLOR = (1 << 4),
	MATERIAL_VAR_VERTEXALPHA = (1 << 5),
	MATERIAL_VAR_SELFILLUM = (1 << 6),
	MATERIAL_VAR_ADDITIVE = (1 << 7),
	MATERIAL_VAR_ALPHATEST = (1 << 8),
	MATERIAL_VAR_MULTIPASS = (1 << 9),
	MATERIAL_VAR_ZNEARER = (1 << 10),
	MATERIAL_VAR_MODEL = (1 << 11),
	MATERIAL_VAR_FLAT = (1 << 12),
	MATERIAL_VAR_NOCULL = (1 << 13),
	MATERIAL_VAR_NOFOG = (1 << 14),
	MATERIAL_VAR_IGNOREZ = (1 << 15),
	MATERIAL_VAR_DECAL = (1 << 16),
	MATERIAL_VAR_ENVMAPSPHERE = (1 << 17),
	MATERIAL_VAR_NOALPHAMOD = (1 << 18),
	MATERIAL_VAR_ENVMAPCAMERASPACE = (1 << 19),
	MATERIAL_VAR_BASEALPHAENVMAPMASK = (1 << 20),
	MATERIAL_VAR_TRANSLUCENT = (1 << 21),
	MATERIAL_VAR_NORMALMAPALPHAENVMAPMASK = (1 << 22),
	MATERIAL_VAR_NEEDS_SOFTWARE_SKINNING = (1 << 23),
	MATERIAL_VAR_OPAQUETEXTURE = (1 << 24),
	MATERIAL_VAR_ENVMAPMODE = (1 << 25),
	MATERIAL_VAR_SUPPRESS_DECALS = (1 << 26),
	MATERIAL_VAR_HALFLAMBERT = (1 << 27),
	MATERIAL_VAR_WIREFRAME = (1 << 28),
	MATERIAL_VAR_ALLOWALPHATOCOVERAGE = (1 << 29),
};

enum EFontFlags
{
	FONTFLAG_NONE,
	FONTFLAG_ITALIC = 0x001,
	FONTFLAG_UNDERLINE = 0x002,
	FONTFLAG_STRIKEOUT = 0x004,
	FONTFLAG_SYMBOL = 0x008,
	FONTFLAG_ANTIALIAS = 0x010,
	FONTFLAG_GAUSSIANBLUR = 0x020,
	FONTFLAG_ROTARY = 0x040,
	FONTFLAG_DROPSHADOW = 0x080,
	FONTFLAG_ADDITIVE = 0x100,
	FONTFLAG_OUTLINE = 0x200,
	FONTFLAG_CUSTOM = 0x400,
	FONTFLAG_BITMAP = 0x800,
};

enum FontDrawType_t
{
	// Use the "additive" value from the scheme file
	FONT_DRAW_DEFAULT = 0,

	// Overrides
	FONT_DRAW_NONADDITIVE,
	FONT_DRAW_ADDITIVE,

	FONT_DRAW_TYPE_COUNT = 2,
};

class ISurface
{
public:
	// ISURFACE
	unsigned long Create_Font()
	{
		typedef unsigned int(__thiscall* OriginalFn)(PVOID);
		return getvfunc< OriginalFn >(this, 71)(this);
	}

	void DrawSetColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int); // 
		getvfunc< OriginalFn >(this, 15)(this, r, g, b, a); // r, g, b, a
	}

	void DrawSetColor1(CColor color)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, CColor); // int, int , int, int
		getvfunc< OriginalFn >(this, 15)(this, color); // r, g, b, a
	}

	void DrawFilledRect(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc< OriginalFn >(this, 16)(this, x0, y0, x1, y1);
	}

	void DrawFilledRectFade(int x0, int y0, int x1, int y1, unsigned int alpha0, unsigned int alpha1, bool bHorizontal)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int, unsigned int, unsigned int, bool);
		getvfunc< OriginalFn >(this, 123)(this, x0, y0, x1, y1, alpha0, alpha1, bHorizontal);
	}

	void DrawSetTextFont(unsigned long font)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long);
		getvfunc< OriginalFn >(this, 23)(this, font);
	}

	void DrawLine(int x0, int y0, int x1, int y1)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc< OriginalFn >(this, 19)(this, x0, y0, x1, y1);
	}

	void DrawSetTextColor(int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int, int, int);
		getvfunc< OriginalFn >(this, 25)(this, r, g, b, a);
	}

	void DrawSetTextPos(int x, int y)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, int, int);
		getvfunc< OriginalFn >(this, 26)(this, x, y);
	}

	void DrawPrintText(const wchar_t* text, int textLen)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, const wchar_t*, int, int);
		return getvfunc< OriginalFn >(this, 28)(this, text, textLen, 0);
	}

	void SetFontGlyphSet(unsigned long& font, const char* windowsFontName, int tall, int weight, int blur, int scanlines, int flags)
	{
		typedef void(__thiscall* OriginalFn)(PVOID, unsigned long, const char*, int, int, int, int, int, int, int);
		getvfunc< OriginalFn >(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, 0, 0);
	}

	void GetTextSize(unsigned long font, const wchar_t* text, int& wide, int& tall)
	{
		typedef void(__thiscall* OriginalFn)(void*, unsigned long font, const wchar_t* text, int& wide, int& tall);
		getvfunc< OriginalFn >(this, 79)(this, font, text, wide, tall);
	}

	void DrawColoredCircle(int centerx, int centery, float radius, int r, int g, int b, int a)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, float, int, int, int, int);
		getvfunc< OriginalFn >(this, 162)(this, centerx, centery, radius, r, g, b, a);
	}

	void DrawOutlinedCircle(int x, int y, int r, int seg)
	{
		typedef void(__thiscall* oDrawOutlinedCircle)(PVOID, int, int, int, int);
		return getvfunc< oDrawOutlinedCircle >(this, 103)(this, x, y, r, seg);
	}

	void LockCursor()
	{
		typedef void(__thiscall* OriginalFn)(void*);
		getvfunc< OriginalFn >(this, 67)(this);
	}

	void DrawOutlinedRect(int X, int Y, int W, int H)
	{
		typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
		return getvfunc< OriginalFn >(this, 18)(this, X, Y, W, H);
	}

	void DrawT(int X, int Y, CColor Color, int Font, bool Center, char* _Input, ...)
	{
		char Buffer[1024] = { '\0' };

		/* set up varargs*/
		va_list Args;

		va_start(Args, _Input);
		vsprintf_s(Buffer, _Input, Args);
		va_end(Args);

		size_t Size = strlen(Buffer) + 1;

		/* set up widebuffer*/
		wchar_t* WideBuffer = new wchar_t[Size];

		/* char -> wchar */
		mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);

		/* check center */
		int Width = 0, Height = 0;

		if (Center)
		{
			GetTextSize(Font, WideBuffer, Width, Height);
		}

		/* call and draw*/
		DrawSetTextColor(Color._color[0], Color._color[1], Color._color[2], Color._color[3]);
		DrawSetTextFont(Font);
		DrawSetTextPos(X - (Width / 2), Y);
		DrawPrintText(WideBuffer, wcslen(WideBuffer));

		return;
	}

	void DrawString(int font, int x, int y, int align, CColor color, const wchar_t* text, ...)
	{
		DrawSetTextPos(x, y);
		DrawSetTextColor(color._color[0], color._color[1], color._color[2], color._color[3]);
		DrawSetTextFont(font);
		DrawPrintText(text, wcslen(text));

		return;
	}

	int CreateNewTextureID(bool procedural)
	{
		typedef int(__thiscall* oDrawSetTextColor)(PVOID, bool);
		return getvfunc< oDrawSetTextColor >(this, 43)(this, procedural);
	}

	int DrawUnicodeString(wchar_t const* cx, int textLen, FontDrawType_t drawType = FONT_DRAW_DEFAULT)
	{
		typedef int(__thiscall* oDrawSetTextColor)(PVOID, wchar_t const*, int, FontDrawType_t);
		return getvfunc< oDrawSetTextColor >(this, 132)(this, cx, textLen, drawType);
	}

	void DrawSetTexture(int textureID)
	{
		typedef void(__thiscall* oDrawSetTextColor)(PVOID, int);
		return getvfunc< oDrawSetTextColor >(this, 38)(this, textureID);
	}

	void DrawSetTextureRGBA(int textureID, unsigned char const* colors, int w, int h)
	{
		typedef void(__thiscall* oDrawSetTextColor)(PVOID, int, unsigned char const*, int, int);
		return getvfunc< oDrawSetTextColor >(this, 37)(this, textureID, colors, w, h);
	}

	void DrawTexturedPolygon(int vtxCount, Vertex_t* vtx, bool bClipVertices = true)
	{
		typedef void(__thiscall* oDrawSetTextColor)(PVOID, int, Vertex_t*, bool);
		return getvfunc< oDrawSetTextColor >(this, 106)(this, vtxCount, vtx, bClipVertices);
	}

	void DrawFilledCircle(int centerx, int centery, float radius, int r, int g, int b, int a)
	{
		for (int i = 0; i < radius; i++)
		{
			DrawColoredCircle(centerx, centery, i, r, g, b, a);
		}
	}

	void DrawT2(int x, int y, CColor color, DWORD font, bool Center, char* _Input, ...)
	{
		int apple = 0;
		char Buffer[1024] = { '\0' };
		va_list Args;
		va_start(Args, _Input);
		vsprintf_s(Buffer, _Input, Args);
		va_end(Args);
		size_t Size = strlen(Buffer) + 1;
		wchar_t* WideBuffer = new wchar_t[Size];
		mbstowcs_s(nullptr, WideBuffer, Size, Buffer, Size - 1);
		/* check center */
		int Width = 0, Height = 0;

		if (Center)
		{
			GetTextSize(font, WideBuffer, Width, Height);
		}

		DrawSetTextFont(font);
		DrawSetTextColor(color._color[0], color._color[1], color._color[2], color._color[3]);
		DrawSetTextPos(x, y);
		DrawPrintText(WideBuffer, wcslen(WideBuffer));
	}

	/*static CColor FromHSB(float hue, float saturation, float brightness)
	{
	float h = hue == 1.0f ? 0 : hue * 4.0f;
	float f = h - (int)h;
	float p = brightness * (1.0f - saturation);
	float q = brightness * (1.0f - saturation * f);
	float t = brightness * (1.0f - (saturation * (1.0f - f)));

	if (h < 1)
	{
	return CColor(
	(unsigned char)(brightness * 255),
	(unsigned char)(t * 255),
	(unsigned char)(p * 255)
	);
	}
	else if (h < 2)
	{
	return CColor(
	(unsigned char)(q * 1),
	(unsigned char)(brightness * 255),
	(unsigned char)(p * 255)
	);
	}
	else if (h < 3)
	{
	return CColor(
	(unsigned char)(p * 255),
	(unsigned char)(brightness * 255),
	(unsigned char)(t * 255)
	);
	}
	else if (h < 4)
	{
	return CColor(
	(unsigned char)(p * 255),
	(unsigned char)(q * 255),
	(unsigned char)(brightness * 255)
	);
	}
	else if (h < 5)
	{
	return CColor(
	(unsigned char)(t * 255),
	(unsigned char)(p * 255),
	(unsigned char)(brightness * 255)
	);
	}
	else
	{
	return CColor(
	(unsigned char)(brightness * 255),
	(unsigned char)(p * 255),
	(unsigned char)(q * 255)
	);
	}
	}*/
};

class IPanel
{
public:
	unsigned int GetPanel(int type)
	{
		typedef unsigned int(__thiscall *tGetPanel)(void*, int type);
		return getvfunc< tGetPanel >(this, 1)(this, type);
	}

	const char* GetName(unsigned int vguiPanel)
	{
		typedef const char* (__thiscall* OriginalFn)(PVOID, unsigned int);
		return getvfunc< OriginalFn >(this, 36)(this, vguiPanel);
	}
};
