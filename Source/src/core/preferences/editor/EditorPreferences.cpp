#include "EditorPreferences.h"

using namespace BoxerEngine;

EditorPreferences::EditorPreferences() : Preferences(Type::EDITOR)
{
    group_name = "editor";
}

void EditorPreferences::SetConfigurationData(const YAML::Node& node)
{
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("display_camera_settings"))
        {
            display_camera_settings = it->second.as<bool>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("fullscreen"))
        {
            fullscreen = it->second.as<bool>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("display_debug_draw"))
        {
            display_debug_draw = it->second.as<bool>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("theme"))
        {
            light_theme = it->second.as<std::string>()._Equal("light");
            continue;
        }

        if (it->first.as<std::string>()._Equal("scene_background_color"))
        {
            scene_background_color = it->second.as<float>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("vsync"))
        {
            vsync = it->second.as<int>();
        }
    }
}

void EditorPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["display_camera_settings"] = display_camera_settings;
    node[group_name]["fullscreen"] = fullscreen;
    node[group_name]["display_debug_draw"] = display_debug_draw;
    node[group_name]["theme"] = light_theme ? "light" : "dark";
    node[group_name]["vsync"] = vsync;
    node[group_name]["scene_background_color"] = scene_background_color;
}
