#pragma once
#include "SingletonBase.h"
#include <map>
class FontModule : public SingletonBase<FontModule>
{
private:
	typedef map<string, IDWriteTextFormat*> _mFont;
	typedef _mFont::iterator mIter;

	_mFont mFont;

public:
	FontModule();
	~FontModule();

	void Create(string NickName, wstring FontName, float FontSize,
		DWRITE_TEXT_ALIGNMENT Type = DWRITE_TEXT_ALIGNMENT_JUSTIFIED);
	void Render(string Text, D2D_RECT_F rc, ID2D1SolidColorBrush* brush = nullptr, string NickName = "DEFAULT");
	void Render(wstring Text, D2D_RECT_F rc, ID2D1SolidColorBrush* brush = nullptr, string NickName = "DEFAULT");

	void SetFontSize(string NickName, float FontSize);
};

