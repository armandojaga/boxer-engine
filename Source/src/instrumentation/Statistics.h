#pragma once

namespace BoxerEngine
{
    class Statistics
    {
        //FPS counter
        //60 FPS = 16.6666ms
        //30 FPS = 33.3333ms
    private:
        float fps = 0.0;
        float ups = 0.0;
    public:
        [[nodiscard]] float GetFramesPerSecond() const
        {
            return fps;
        }

        [[nodiscard]] float GetUpdatesPerSecond() const
        {
            return ups;
        }

        void calculate()
        {
            static const int SAMPLES = 16;
            static float historic[SAMPLES];
            static int currentFrame = 0;
            static float previousTicks = game_clock.ReadMs();

            const float currentTicks = game_clock.ReadMs();
            ups = currentTicks - previousTicks;

            historic[currentFrame % SAMPLES] = ups;

            int count;
            if (currentFrame < SAMPLES)
            {
                count = currentFrame;
            }
            else
            {
                count = SAMPLES;
            }

            float averageTime = 0;
            for (const float time : historic)
            {
                averageTime += time;
            }
            averageTime /= static_cast<float>(count);
            if (averageTime > 0)
            {
                fps = 1000.0f / averageTime;
            }
            else
            {
                fps = FPS_LIMIT;
            }
            ++currentFrame;
            previousTicks = currentTicks;
        }
    };
}
