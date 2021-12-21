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
        inline static float ms_frequency_factor = 1000.0f / frequency;
        inline static float us_frequency_factor = 1000000.0f / frequency;
        bool stopped = false;
    public:
        Timer() = default;
        ~Timer() = default;
        void Start();
        void Stop();
        [[nodiscard]] float Read() const; //seconds
        [[nodiscard]] float ReadMs() const;
        [[nodiscard]] float ReadUs() const;
    };
}
