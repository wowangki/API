#pragma once
class DX2DApp
{
public:
	DX2DApp();
	
	ID2D1Factory*			pDirect2dFactory;
	ID2D1HwndRenderTarget*	pRenderTarget;
	ID2D1SolidColorBrush*	pDefaultBrush;
	IDWriteFactory*			pWriteFactory;

	bool CreateFactory(void);
	bool CreateDirect2dResources(void);
	void OnResize(UINT width, UINT height);

	void Release(void);
	
	void BeginDraw(void);
	void EndDraw(void);

	void ChangeColor(const COLORREF& color, float opactity = 1.0f);
	void ChangeColor(const D2D1_COLOR_F& color);

	static DX2DApp* GetInstance()
	{
		static DX2DApp Instance;
		return &Instance;
	}

};

#define _Device			DX2DApp::GetInstance()
#define _RenderTarget	DX2DApp::GetInstance()->pRenderTarget
#define _Factory		DX2DApp::GetInstance()->pDirect2dFactory


