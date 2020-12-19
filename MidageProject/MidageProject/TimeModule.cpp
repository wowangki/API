#include "stdafx.h"
#include "TimeModule.h"

#pragma comment (lib, "winmm.lib")
#include <mmsystem.h>

TimeModule::TimeModule()
{
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&_PeriodTime)){
		isHardware = true;
		QueryPerformanceCounter((LARGE_INTEGER*)&_LastTime);
		TimeScale = 1.0f / _PeriodTime;
	}
	else {
		isHardware = false;
		_LastTime = timeGetTime();
		TimeScale = 0.001f;
	}
}


TimeModule::~TimeModule()
{
}

void TimeModule::UpdateTime(float frameLock)
{
	if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_CurTime);
	else _CurTime = timeGetTime();

	TimeElapsed = (_CurTime - _LastTime) * TimeScale;

	if (frameLock > 0.0f) {
		while (TimeElapsed < (1.0f / frameLock))
		{
			if (isHardware) QueryPerformanceCounter((LARGE_INTEGER*)&_CurTime);
			else _CurTime = timeGetTime();

			TimeElapsed = (_CurTime - _LastTime) * TimeScale;
		}
	}

	_LastTime = _CurTime;
	FPSFrameCount++;
	FPSTimeElapsed += TimeElapsed;
	WorldTime += TimeElapsed;

	if (FPSTimeElapsed > 1.0f) {
		FrameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0f;
	}
}

void TimeModule::RenderTime(void)
{
	WCHAR TimeString[256];
#if defined(DEBUG)|| defined (_DEBUG)
	static TCHAR TimeTextString[] = L"WorldTime : %.2f\nFrameCount : %f\nFPS : %d";
	_stprintf_s(TimeString, TimeTextString, WorldTime, TimeElapsed, FrameRate);
	_FONT->Render(TimeString, RectF(0.0f, 0.0f, 200.0f, 100.0f));
#else
	static TCHAR TimeTextString[] = L"FPS : %d";
	_stprintf_s(TimeString, TimeTextString, FrameRate);
	_FONT->Render(TimeString, RectF(WINSIZEX - 50.0f, 0.0f, 100.0f, 30.0f));
#endif
}
