// stdafx.h : 자주 사용하지만 자주 변경되지는 않는
// 표준 시스템 포함 파일 또는 프로젝트 관련 포함 파일이
// 들어 있는 포함 파일입니다.
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // 거의 사용되지 않는 내용은 Windows 헤더에서 제외합니다.
// Windows 헤더 파일:
#include <windows.h>

// C 런타임 헤더 파일입니다.
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <math.h>
#include <string>
#include <memory>
#include <commdlg.h>
#include <typeinfo>
#include <algorithm>
using namespace std;

//외부 종속성
//DirectX2D Header File
#pragma comment(lib, "d2d1.lib")
#include <d2d1.h>
#include <d2d1helper.h>
using namespace D2D1;

#pragma comment(lib, "WindowsCodecs.lib")
#include <wincodec.h>

//PNG incoder
#pragma comment(lib, "dwrite.lib")
#include <dwrite.h>

//D2D1 Header
#include "DX2DApp.h"

struct App_Desc {
	HINSTANCE _hInstance;
	HWND _hWnd;
	float width;
	float height;
};

//extern
extern App_Desc AppDesc;
extern POINT AppMouse;

#define ApplicationName TEXT("MidageProject")
#define WINSIZEX AppDesc.width
#define WINSIZEY AppDesc.height

// TODO: 프로그램에 필요한 추가 헤더는 여기에서 참조합니다.

//Define Header
#include "DefineHeader.h"
#include "Utillity.h"
using namespace nString;
using namespace nSource;
using namespace nCollision;
using namespace nCull;
using namespace randomFunction;