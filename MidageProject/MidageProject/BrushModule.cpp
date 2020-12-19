#include "stdafx.h"
#include "BrushModule.h"


BrushModule::BrushModule()
{
}


BrushModule::~BrushModule()
{
	for (mIter iter = mBrush.begin(); iter != mBrush.end(); iter++) {
		SafeRelease(iter->second);
	}
}

HRESULT BrushModule::CreateBrush(string NickName, COLORREF color, float opacity)
{
	ID2D1SolidColorBrush* pTemp = nullptr;
	UINT col = (((BYTE)GetBValue(color)) |
		((WORD)((BYTE)GetGValue(color))) << 8 |
		(((DWORD)(BYTE)(GetRValue(color))) << 16));
		
	D2D1_COLOR_F c = ColorF(col, opacity);

	if (FAILED(_RenderTarget->CreateSolidColorBrush(c, &pTemp)))
		return E_FAIL;

	mBrush.insert(make_pair(NickName, pTemp));

	return S_OK;
}

ID2D1SolidColorBrush * BrushModule::GetBrush(string NickName)
{
	mIter iter = mBrush.find(NickName);
	if (iter == mBrush.end()) return nullptr;

	return iter->second;
}
