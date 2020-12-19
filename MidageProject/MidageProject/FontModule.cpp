#include "stdafx.h"
#include "FontModule.h"


FontModule::FontModule()
{
	IDWriteTextFormat* temp = nullptr;

	_Device->pWriteFactory->CreateTextFormat(
		L"휴먼굴림체",
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		10.0f, L"",
		&temp
	);

	temp->SetTextAlignment(DWRITE_TEXT_ALIGNMENT_JUSTIFIED);

	mFont.insert(make_pair("DEFAULT", temp));
}


FontModule::~FontModule()
{
	mIter iter = mFont.begin();
	for (iter; iter != mFont.end(); ++iter) {
		SafeRelease(iter->second);
	}

	mFont.clear();
}

void FontModule::Create(string NickName, wstring FontName, float FontSize, DWRITE_TEXT_ALIGNMENT Type)
{
	IDWriteTextFormat* pTemp = nullptr;

	if (FAILED(_Device->pWriteFactory->CreateTextFormat(
		FontName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		FontSize, L"",
		&pTemp
	))) {
		MessageBox(AppDesc._hWnd, L"폰트를 추가할 수 없습니다.!", nullptr, MB_OK);
		return;
	}

	pTemp->SetTextAlignment(Type);
	mFont.insert(make_pair(NickName, pTemp));
}

void FontModule::Render(string Text, D2D_RECT_F rc, ID2D1SolidColorBrush * brush, string NickName)
{
	if (brush == nullptr) {
		_RenderTarget->DrawTextW(StringToWstring(Text).c_str(),
			(UINT32)Text.size(),
			mFont[NickName],
			rc,
			_Device->pDefaultBrush);
	}
	else {
		_RenderTarget->DrawTextW(StringToWstring(Text).c_str(),
			(UINT32)Text.size(),
			mFont[NickName],
			rc,
			brush);
	}
}

void FontModule::Render(wstring Text, D2D_RECT_F rc, ID2D1SolidColorBrush * brush, string NickName)
{
	if (brush == nullptr) {
		_RenderTarget->DrawTextW(Text.c_str(),
			(UINT32)Text.size(),
			mFont[NickName],
			rc,
			_Device->pDefaultBrush);
	}
	else {
		_RenderTarget->DrawTextW(Text.c_str(),
			(UINT32)Text.size(),
			mFont[NickName],
			rc,
			brush);
	}
}

void FontModule::SetFontSize(string NickName, float FontSize)
{
	mIter iter = mFont.find(NickName);
	if (iter == mFont.end()) return;
	wstring FontNickName = StringToWstring(iter->first);

	SafeRelease(iter->second);

	_Device->pWriteFactory->CreateTextFormat(
		FontNickName.c_str(),
		nullptr,
		DWRITE_FONT_WEIGHT_NORMAL,
		DWRITE_FONT_STYLE_NORMAL,
		DWRITE_FONT_STRETCH_NORMAL,
		FontSize, L"",
		&iter->second
	);
}
