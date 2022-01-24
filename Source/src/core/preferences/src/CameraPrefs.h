#pragma once

#include "../Prefs.h"

namespace BoxerEngine
{
	class CameraPrefs final : public Prefs
	{
        public:
            CameraPrefs();
            ~CameraPrefs() = default;
            void SetConfigData(const YAML::Node& yNode) override;
            void GetConfigData(YAML::Node& output_node) override;

        private:
            unsigned int move_speed = 15;
            unsigned int rotation_speed = 15;
            unsigned int orbit_speed = 25;
            unsigned int zoom_speed = 50;
            float fov = 90.0;
	};
}


