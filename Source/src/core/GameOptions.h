#pragma once

namespace BoxerEngine
{
    class GameOptions
    {
    private:
        float max_fps = 250.0f;
        float fps_threshold = 1000.0f / max_fps;

    public:
        [[nodiscard]] float GetMaxFPS() const
        {
            return max_fps;
        }

        void SetMaxFPS(const float maxFps)
        {
            max_fps = std::max(24.0f, maxFps);
            max_fps = std::min(max_fps, 250.0f);
            fps_threshold = 1000.0f / max_fps;
        }

        [[nodiscard]] float GetFPSThreshold() const
        {
            return fps_threshold;
        }
    };
}
