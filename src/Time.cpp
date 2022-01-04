#include "stdafx.h"
#include "Time.hpp"
namespace BEbraEngine {
	std::chrono::time_point<std::chrono::steady_clock> Time::lastFrame;
	std::chrono::time_point<std::chrono::steady_clock> Time::CurrentFrame;
	std::chrono::high_resolution_clock Time::clock;
	float Time::_deltaTime;
	float Time::_totalTime;
}