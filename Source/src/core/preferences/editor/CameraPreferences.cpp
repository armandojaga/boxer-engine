#include "CameraPreferences.h"

using namespace BoxerEngine;

CameraPreferences::CameraPreferences() : Preferences(Type::CAMERA)
{
    group_name = "camera";
}

void CameraPreferences::SetConfigurationData(const YAML::Node& node)
{
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("move_speed"))
        {
            move_speed = it->second.as<int>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("rotation_speed"))
        {
            rotation_speed = it->second.as<int>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("orbit_speed"))
        {
            orbit_speed = it->second.as<int>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("zoom_speed"))
        {
            zoom_speed = it->second.as<int>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("fov"))
        {
            fov = it->second.as<float>();
        }
    }
}

void CameraPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["move_speed"] = move_speed;
    node[group_name]["rotation_speed"] = rotation_speed;
    node[group_name]["orbit_speed"] = orbit_speed;
    node[group_name]["zoom_speed"] = zoom_speed;
    node[group_name]["fov"] = fov;
}
