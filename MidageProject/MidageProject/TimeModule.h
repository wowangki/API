#pragma once
class TimeModule
{
private:
	bool isHardware;

	float TimeScale;
	float TimeElapsed;
	__int64 _PeriodTime;
	__int64 _LastTime;
	__int64 _CurTime;

	unsigned long FrameRate;
	unsigned long FPSFrameCount;

	float FPSTimeElapsed;
	float WorldTime;

public:
	TimeModule();
	~TimeModule();

	void UpdateTime(float frameLock = 60.0f);
	void RenderTime(void);

	inline float GetElapsedTime(void) { return TimeElapsed; }
	inline float GetTime(void) { return WorldTime; }
	inline float GetFPSTime(void) { return (float)FrameRate; }

public:
	static TimeModule* GetInstance() {
		
		static TimeModule Instance;
		return &Instance;
	}
};

