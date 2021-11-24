#pragma once
#include "SDL_stdinc.h"
#include "SDL_timer.h"

class Timer
{
private:
    Uint64 startMs;
    Uint64 startUs;
    Uint64 endMs;
    Uint64 endUs;
    inline static Uint64 frequency = SDL_GetPerformanceFrequency();
    const char* name;
    bool stopped = false;
public:
    Timer() = default;
    ~Timer() = default;
    void Start();
    void Stop();
    Uint64 ReadMs() const;
    Uint64 ReadUs() const;
    const char* GetName() const;
};
