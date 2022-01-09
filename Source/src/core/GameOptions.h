#pragma once
#include "Math/float3.h"

namespace BoxerEngine
{
    class GameOptions
    {
    private:
        float max_fps = 250.0f;
        bool fullscreen = false;
        int vsync = 0;
        bool display_debug_draw = false;
        float3 scene_background_color = float3(0.0f);
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

        [[nodiscard]] bool IsFullscreen() const
        {
            return fullscreen;
        }

        void SetFullscreen(const bool fullscreen)
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

        void SetDisplayDebugDraw(const bool displayDebugDraw)
        {
            display_debug_draw = displayDebugDraw;
        }

        [[nodiscard]] bool IsDisplayDebugDraw() const
        {
            return display_debug_draw;
        }

        void SetSceneBackgroundColor(const float3& sceneBackgroundColor)
        {
            scene_background_color = sceneBackgroundColor;
        }

        [[nodiscard]] const float3& GetSceneBackgroundColor() const
        {
            return scene_background_color;
        }
    };
}
