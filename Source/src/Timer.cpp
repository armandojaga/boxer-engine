#include "Timer.h"
#include "SDL_timer.h"

void Timer::Start()
{
    startUs = SDL_GetPerformanceCounter();
    startMs = SDL_GetTicks();
}

void Timer::Stop()
{
    endUs = SDL_GetPerformanceCounter();
    endMs = SDL_GetTicks();
    stopped = true;
}

Uint64 Timer::ReadUs() const
{
    if (!stopped)
    {
        return SDL_GetPerformanceCounter() - startUs;
    }
    return endUs - startUs;
}

const char* Timer::GetName() const
{
    return name;
}

Uint64 Timer::ReadMs() const
{
    if (!stopped)
    {
        return SDL_GetTicks() - startMs;
    }
    return endMs - startMs;
}
