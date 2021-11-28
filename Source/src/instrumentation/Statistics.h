#pragma once

#include "Windows.h"
#include "Psapi.h"

namespace BoxerEngine
{
    class Statistics
    {
        //FPS counter
        //240 FPS = 4.1666ms
        //120 FPS = 8.3333ms
        //60 FPS = 16.6666ms
        //30 FPS = 33.3333ms
    private:
        float fps = 0.0;
        float ms = 0.0;
        int memory = 0.0;

        static const int SAMPLES = 60;
        static const int LOG_SIZE = 50;

        float historic[SAMPLES] = {};
        int current_frame = 0;
        int historic_counter = 0;
        float previousTicks = game_clock.ReadMs();

        float fps_log[LOG_SIZE] = {};
        float ms_log[LOG_SIZE] = {};
        
        int log_counter = 0;

    public:
        [[nodiscard]] float GetFramesPerSecond() const
        {
            return fps;
        }

        [[nodiscard]] float GetFrameSpeed() const
        {
            return ms;
        }

        [[nodiscard]] int GetUsedMemory() const
        {
            return memory;
        }

        // auto here refers to:
        // typedef float float50[50];
        // const float50*
        [[nodiscard]] auto GetFPSLog() const
        {
            return &fps_log;
        }

        [[nodiscard]] auto GetMSLog() const
        {
            return &ms_log;
        }

        void calculate()
        {
            PROCESS_MEMORY_COUNTERS_EX pmc;
            GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS*)&pmc, sizeof(pmc));
            memory = static_cast<int>(pmc.PrivateUsage);

            const float currentTicks = game_clock.ReadMs();
            ms = currentTicks - previousTicks;
            previousTicks = currentTicks;

            historic[current_frame % SAMPLES] = ms;

            if (++current_frame >= SAMPLES)
            {
                current_frame = 0;
                historic_counter = SAMPLES;
            }
            else if(historic_counter < SAMPLES)
            {
                historic_counter = current_frame;
            }

            float averageTime = 0;
            for (const float time : historic)
            {
                averageTime += time;
            }
            averageTime /= static_cast<float>(historic_counter);
            ms = averageTime;

            if (averageTime > 0)
            {
                fps = 1000.0f / averageTime;
            }
            else
            {
                fps = game_options.GetMaxFPS();
                ms = 1000.0f / game_options.GetMaxFPS();
            }
            
            ms_log[log_counter] = ms;
            fps_log[log_counter] = fps;

            if(++log_counter >= LOG_SIZE)
            {
                log_counter = 0;
            }
        }
    };
}
