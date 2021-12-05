#pragma once
#include <chrono>
namespace BEbraEngine {
    class Time {
    public:
        Time() { }

        static void updateTime() {
            CurrentFrame = Clock::now();
            _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(CurrentFrame - lastFrame).count() / 1000000.f;
            lastFrame = CurrentFrame;
        }
        static float deltaTime() {
            return _deltaTime;
        }
        static float fixedDeltaTime() {
            return 0.16f;
        }
    private:
        typedef std::chrono::high_resolution_clock Clock;
        typedef std::chrono::time_point<std::chrono::steady_clock> time_point;
    private:

        static time_point lastFrame;
        static time_point CurrentFrame;
        static Clock clock;
        static float _deltaTime;
    };

}