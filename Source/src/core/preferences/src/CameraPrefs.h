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

            [[nodiscard]] unsigned int GetMoveSpeed() const { return move_speed; }
            [[nodiscard]] unsigned int GetRotationSpeed() const { return rotation_speed; }
            [[nodiscard]] unsigned int GetOrbitSpeed() const { return orbit_speed; }
            [[nodiscard]] unsigned int GetZoomSpeed() const { return zoom_speed; }
            [[nodiscard]] float GetFov() const { return fov; }
            [[nodiscard]] float GetNearDistance() const { return near_distance; }
            [[nodiscard]] float GetFarDistance() const { return far_distance; }

            void SetMoveSpeed(unsigned int val) { move_speed = val; }
            void SetRotationSpeed(unsigned int val) { rotation_speed = val; }
            void SetOrbitSpeed(unsigned int val) { orbit_speed = val; }
            void SetZoomSpeed(unsigned int val) { zoom_speed = val; }
            void SetFov(float val) { fov = val; }
            void SetNearDistance(float val) { near_distance = val; }
            void SetFarDistance(float val) { far_distance = val; }

        private:
            unsigned int move_speed = 15;
            unsigned int rotation_speed = 15;
            unsigned int orbit_speed = 25;
            unsigned int zoom_speed = 50;
            float fov = 90.0;
            float near_distance = 0.1;
            float far_distance = 100.0;
	};
}


