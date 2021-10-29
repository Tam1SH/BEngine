#pragma once
#include <chrono>
namespace BEbraEngine {
    class Time {
    public:
        Time() { }
        static  void UpdateTime() {
            CurrentFrame = Clock::now();
            deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(CurrentFrame - lastFrame).count() / 1000000.f;
            lastFrame = CurrentFrame;
        }
        static float GetDeltaTime() {
            return deltaTime;
        }
    private:
        typedef std::chrono::high_resolution_clock Clock;
        typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
    private:

        static time_point lastFrame;
        static time_point CurrentFrame;
        static Clock clock;
        static float deltaTime;
    };

}