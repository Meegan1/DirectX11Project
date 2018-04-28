#pragma once
#include <windows.h>

class HRT
{
public:
	static void StartTimer();
	static double GetTime();
	static double GetFrameTime();
	static int GetFPS();
	static void Tick();

private:
	static double countsPerSecond;
	static __int64 CounterStart;

	static int frameCount;
	static int fps;

	static __int64 frameTimeOld;
	static double frameTime;
};

