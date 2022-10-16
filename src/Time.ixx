
export module Time;
import <chrono>;
namespace BEbraEngine {
    export struct Time {

        Time() { }
        static float& time() {
            return _totalTime;
        }
        static void updateTime() {
            CurrentFrame = Clock::now();
            _deltaTime = std::chrono::duration_cast<std::chrono::microseconds>(CurrentFrame - lastFrame).count() / 1000000.f;
            lastFrame = CurrentFrame;
            _totalTime += _deltaTime;
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
        static float _totalTime;
    };
    std::chrono::time_point<std::chrono::steady_clock> Time::lastFrame;
    std::chrono::time_point<std::chrono::steady_clock> Time::CurrentFrame;
    std::chrono::high_resolution_clock Time::clock;
    float Time::_deltaTime;
    float Time::_totalTime;
}