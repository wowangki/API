#include "stdafx.h"
#include "MainEntry.h"

MainEntry MainClass;

int APIENTRY wWinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR lpCmdLine,
	_In_ int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

#ifdef _DEBUG
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif

	if (FAILED(MainClass.CreateDevice(hInstance, nCmdShow))) return E_FAIL;
	if (FAILED(MainClass.Init()))return FALSE;

	MSG msg;

	while (true)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) break;
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			_TIMER->UpdateTime();
			MainClass.Update();

			_Device->BeginDraw();
			MainClass.Render();
			_TIMER->RenderTime();
			_Device->EndDraw();
		}
	}
	
	MainClass.Release();
	_Device->Release();

	return (int)msg.wParam;
}