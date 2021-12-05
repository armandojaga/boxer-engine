#pragma once
#include "SDL_stdinc.h"
#include "SDL_timer.h"

namespace BoxerEngine
{
    class Timer
    {
    private:
        Uint64 start{};
        Uint64 end{};
        inline static float frequency = static_cast<float>(SDL_GetPerformanceFrequency());
        bool stopped = false;
    public:
        Timer() = default;
        ~Timer() = default;
        void Start();
        void Stop();
        float Read() const; //seconds
        float ReadMs() const;
        float ReadUs() const;
    };
}
