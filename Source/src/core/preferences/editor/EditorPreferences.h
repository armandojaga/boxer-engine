#pragma once

#include "core/preferences/Preferences.h"

namespace BoxerEngine
{
    class EditorPreferences final : public Preferences
    {
    public:
        EditorPreferences();
        ~EditorPreferences() override = default;
        void SetConfigurationData(const YAML::Node& node) override;
        void GetConfigurationData(YAML::Node& node) override;

        void SetDisplayDebugDraw(const bool displayDebugDraw)
        {
            display_debug_draw = displayDebugDraw;
        }

        [[nodiscard]] bool IsDisplayDebugDraw() const
        {
            return display_debug_draw;
        }

        void SetSceneBackgroundColor(const float& sceneBackgroundColor)
        {
            scene_background_color = sceneBackgroundColor;
        }

        [[nodiscard]] const float& GetSceneBackgroundColor() const
        {
            return scene_background_color;
        }

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

        void SetDisplayCameraSettings(const bool displayCameraSettings)
        {
            display_camera_settings = displayCameraSettings;
        }

        [[nodiscard]] bool GetDisplayCameraSettings() const
        {
            return display_camera_settings;
        }

        void SetLightTheme(const bool lightTheme)
        {
            light_theme = lightTheme;
        }

        [[nodiscard]] bool IsLightTheme() const
        {
            return light_theme;
        }

    private:
        bool display_debug_draw = false;
        float scene_background_color = 0.9f;

        //TODO remove this property in favor of the camera component
        bool display_camera_settings = false;

        float max_fps = 250.0f;
        bool fullscreen = false;
        int vsync = 0;
        float fps_threshold = 1000.0f / max_fps;
        bool light_theme = true;
    };
}
