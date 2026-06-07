#pragma once
#include <chrono>

namespace dx3d
{
	class GameTimer
	{
	public:
		GameTimer();
		double getMilisecondsElapsed();
		void restart();
		bool Stop();
		bool Start();
	private:
		bool isRunning = false;

#ifdef _WIN32
		std::chrono::time_point<std::chrono::steady_clock> start;
		std::chrono::time_point<std::chrono::steady_clock> stop;
#endif
	};

}

