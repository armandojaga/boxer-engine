#pragma once

namespace BoxerEngine
{
    class GameOptions
    {
    private:
        float max_fps = 250.0f;
        bool fullscreen = false;
        int vsync = 0;

    public:
        [[nodiscard]] float GetMaxFPS() const
        {
            return max_fps;
        }

        void SetMaxFPS(const float maxFps)
        {
            max_fps = maxFps;
        }

        [[nodiscard]] bool IsFullScreen() const
        {
            return fullscreen;
        }

        void SetFullSceen(const bool fullscreen)
        {
            this->fullscreen = fullscreen;
        }

        void SetVsync(const int vsync)
        {
            this->vsync = vsync;
        }

        [[nodiscard]] int GetVsync() const
        {
            return vsync;
        }
    };
}
