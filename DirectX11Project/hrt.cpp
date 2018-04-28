#include "hrt.h"

double HRT::countsPerSecond = 0.0;
__int64 HRT::CounterStart = 0;

int HRT::frameCount = 0;
int HRT::fps = 0;

__int64 HRT::frameTimeOld = 0;

void HRT::StartTimer()
{
	LARGE_INTEGER frequencyCount;
	QueryPerformanceFrequency(&frequencyCount);

	countsPerSecond = double(frequencyCount.QuadPart);

	QueryPerformanceCounter(&frequencyCount);
	CounterStart = frequencyCount.QuadPart;
}

double HRT::GetTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);
	return double(currentTime.QuadPart - CounterStart) / countsPerSecond;
}

double HRT::GetFrameTime()
{
	LARGE_INTEGER currentTime;
	QueryPerformanceCounter(&currentTime);

	__int64 tickCount = currentTime.QuadPart - frameTimeOld;
	frameTimeOld = currentTime.QuadPart;

	if (tickCount < 0.0f)
		tickCount = 0.0f;

	return float(tickCount) / countsPerSecond;
}

int HRT::GetFPS()
{
	return fps;
}

void HRT::Tick()
{
	frameCount++;
	if (GetTime() > 1.0f)
	{
		fps = frameCount;
		frameCount = 0;
		StartTimer();
	}
}
