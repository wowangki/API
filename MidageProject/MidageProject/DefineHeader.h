#pragma once
#define SafeRelease(p) {if(p){(p)->Release(); (p) = nullptr;}}
#define SafeDelete(p) {if(p){delete(p); (p) = nullptr;}}
#define SafeDeleteClass(p) {if(p){(p)->Release(); delete(p); (p) = nullptr;}}
#define SafeDeleteArray(p){if(p) delete[](p); (p) = nullptr;}
#define SafeUpdate(p) {if(p) (p)->Update();}


#define GET_X_LPARAM(lp) ((int)(short)LOWORD(lp))
#define GET_Y_LPARAM(lp) ((int)(short)HIWORD(lp))

#define ArrSize(p) { sizeof(p)/ sizeof(*p) }

//=============================================
//¡Ø Singleton Module
//==============================================
#include "TimeModule.h"
#define _TIMER TimeModule::GetInstance()

#include "FontModule.h"
#define _FONT FontModule::GetInstance()

#include "CameraModule.h"
#define _CAM CameraModule::GetInstance()

#include "BrushModule.h"
#define _BRUSH BrushModule::GetInstance()

#include "SceneModule.h"
#define _SCENE SceneModule::GetInstance()

#include "ImageManager.h"
#define _IMAGE ImageManager::GetInstance()

#include "SoundModule.h"
#define _SOUND SoundModule::GetInstance()
//==============================================
//¡Ø ETC Module
//==============================================
#ifndef Assert
#if defined(DEBUG) || defined(_DEBUG)
#define Assert(b) do{if(!(b)){OutputDebugStringA("Assert : " #b "\n");}} while(0)
#else
#define Assert(b)
#endif
#endif

#include <crtdbg.h>
#ifdef _DEBUG
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif