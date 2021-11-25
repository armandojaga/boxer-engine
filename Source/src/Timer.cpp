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
            return ((SDL_GetPerformanceCounter() - start) * 1000.0f) / frequency;
        }
        return ((end - start) * 1000.0f) / frequency;
    }

    float Timer::ReadUs() const
    {
        if (!stopped)
        {
            return ((SDL_GetPerformanceCounter() - start) * 1000000.0f) / frequency;
        }
        return ((end - start) * 1000000.0f) / frequency;
    }
}
