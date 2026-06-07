#include "GameTimer.h"

dx3d::GameTimer::GameTimer()
{
	start = std::chrono::high_resolution_clock::now();
	stop = std::chrono::high_resolution_clock::now();
}

double dx3d::GameTimer::getMilisecondsElapsed()
{
	if (isRunning)
	{
		auto elapsed = std::chrono::duration<double, std::milli>(std::chrono::high_resolution_clock::now()-start);
		return elapsed.count();
	}

	else
	{
		auto elapsed = std::chrono::duration<double, std::milli>(stop - start);
		return elapsed.count();
	}
}

void dx3d::GameTimer::restart()
{
	isRunning = true;
	start = std::chrono::high_resolution_clock::now();
}

bool dx3d::GameTimer::Stop()
{
	if (!isRunning)
	{
		return false;
	}
	else
	{
		stop = std::chrono::high_resolution_clock::now();
		isRunning = false;
		return true;
	}
}

bool dx3d::GameTimer::Start()
{
	if (isRunning)
	{
		return false;
	}
	else
	{
		start = std::chrono::high_resolution_clock::now();
		isRunning = true;
		return true;
	}


}
