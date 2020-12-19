#include "stdafx.h"
#include "DX2DApp.h"


DX2DApp::DX2DApp()
	:pWriteFactory(nullptr),
	pDefaultBrush(nullptr),
	pRenderTarget(nullptr),
	pDirect2dFactory(nullptr)
{
}

bool DX2DApp::CreateFactory(void)
{
	if (FAILED(D2D1CreateFactory(D2D1_FACTORY_TYPE_SINGLE_THREADED, &pDirect2dFactory)))
		return false;

	return true;
}

bool DX2DApp::CreateDirect2dResources(void)
{
	//==================== °íÃÆ´Ù!!!!!!!!!!! ===============================
	RECT rc = { 0,0, (UINT)AppDesc.width, (UINT)AppDesc.height };
	RECT winDC;
	GetClientRect(AppDesc._hWnd, &winDC);

	D2D1_SIZE_U size = D2D1::SizeU(
		rc.right - rc.left,
		rc.bottom - rc.top);

	UINT CenterX = (GetSystemMetrics(SM_CXSCREEN) - size.width) / 2;
	UINT CenterY = (GetSystemMetrics(SM_CYSCREEN) - size.height) / 2;
	
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	MoveWindow(AppDesc._hWnd, CenterX, CenterY,
		size.width, size.height, TRUE);

	D2D1_SIZE_U dcSize = D2D1::SizeU(winDC.right, winDC.bottom);

	if (FAILED(
		pDirect2dFactory->CreateHwndRenderTarget(
			D2D1::RenderTargetProperties(),
			D2D1::HwndRenderTargetProperties(AppDesc._hWnd, dcSize),
			&pRenderTarget)))
		return false;

	//==================== °íÃÆ´Ù!!!!!!!!!!! ===============================
	if (FAILED(pRenderTarget->CreateSolidColorBrush(
		D2D1::ColorF(D2D1::ColorF::White), &pDefaultBrush)))
		return false;

	if (FAILED(DWriteCreateFactory(DWRITE_FACTORY_TYPE_SHARED, 
		__uuidof(pWriteFactory),
		reinterpret_cast<IUnknown**>(&pWriteFactory))))
		return false;

	return true;
}

void DX2DApp::OnResize(UINT width, UINT height)
{
	pRenderTarget->Resize(D2D1::SizeU(width, height));
}

void DX2DApp::Release(void)
{
	SafeRelease(pWriteFactory);
	SafeRelease(pDefaultBrush);
	SafeRelease(pRenderTarget);
	SafeRelease(pDirect2dFactory);

}

void DX2DApp::BeginDraw(void)
{
	if (pRenderTarget) {
		pRenderTarget->BeginDraw();
		pRenderTarget->SetTransform(D2D1::Matrix3x2F::Identity());
		pRenderTarget->Clear(D2D1::ColorF(D2D1::ColorF::Black));
	}
}

void DX2DApp::EndDraw(void)
{
	if (pRenderTarget)
		pRenderTarget->EndDraw();
}

void DX2DApp::ChangeColor(const COLORREF & color, float opactity)
{
	UINT col = (((BYTE)GetBValue(color)) |
		((WORD)(BYTE)GetGValue(color))) << 8 |
		((((DWORD)(BYTE)(GetRValue(color))) << 16));

	pDefaultBrush->SetColor(ColorF(col, opactity));
}

void DX2DApp::ChangeColor(const D2D1_COLOR_F & color)
{
	pDefaultBrush->SetColor(color);
}
