#pragma once

#include "../Prefs.h"

namespace BoxerEngine
{
	class EditorPrefs final : public Prefs
	{
	public:
        EditorPrefs();
		~EditorPrefs() = default;
		void LoadConfig(const YAML::Node& yNode) override;
		void SaveConfig() override;

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

        void SetDisplayAbout(const bool val)
        {
            display_about = val;
        }

        [[nodiscard]] bool GetDisplayAbout() const
        {
            return display_about;
        }

        void SetDisplayConsole(const bool val)
        {
            display_console = val;
        }

        [[nodiscard]] bool GetDisplayConsole() const
        {
            return display_console;
        }

        void SetDisplayStats(const bool val)
        {
            display_stats = val;
        }

        [[nodiscard]] bool GetDisplayStats() const
        {
            return display_stats;
        }

        void SetDisplayConfig(const bool val)
        {
            display_config = val;
        }

        [[nodiscard]] bool GetDisplayConfig() const
        {
            return display_config;
        }

        void SetDisplayHardware(const bool val)
        {
            display_hardware = val;
        }

        [[nodiscard]] bool GetDisplayHardware() const
        {
            return display_hardware;
        }

        void SetDisplayCameraSettings(const bool val)
        {
            display_camera_settings = val;
        }

        [[nodiscard]] bool GetDisplayCameraSettings() const
        {
            return display_camera_settings;
        }

	private:
        mutable bool display_about = false;
        bool display_console = true;
        bool display_stats = true;
        bool display_config = true;
        bool display_hardware = true;
        bool display_camera_settings = false;
		float max_fps = 250.0f;
		bool fullscreen = false;
		int vsync = 0;
		float fps_threshold = 1000.0f / max_fps;
	};
}


