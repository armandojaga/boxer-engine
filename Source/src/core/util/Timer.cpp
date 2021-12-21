#include "Timer.h"
#include "SDL_timer.h"

namespace BoxerEngine
{
    void Timer::Start()
    {
        start = SDL_GetPerformanceCounter();
    }

    void Timer::Stop()
    {
        end = SDL_GetPerformanceCounter();
        stopped = true;
    }

    float Timer::Read() const
    {
        if (!stopped)
        {
            return (SDL_GetPerformanceCounter() - start) / frequency;
        }
        return (end - start) / frequency;
    }

    float Timer::ReadMs() const
    {
        if (!stopped)
        {
            return (SDL_GetPerformanceCounter() - start) * ms_frequency_factor;
        }
        return (end - start) * ms_frequency_factor;
    }

    float Timer::ReadUs() const
    {
        if (!stopped)
        {
            return (SDL_GetPerformanceCounter() - start) * us_frequency_factor;
        }
        return (end - start) * us_frequency_factor;
    }
}
