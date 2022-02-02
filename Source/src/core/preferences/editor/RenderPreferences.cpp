#include "RenderPreferences.h"

using namespace BoxerEngine;

RenderPreferences::RenderPreferences() : Preferences(Type::RENDER)
{
    group_name = RENDER_NODE;
}

void RenderPreferences::SetConfigurationData(const YAML::Node& node)
{
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal(MAX_FPS))
        {
            max_fps = it->second.as<float>();
            continue;
        }

        if (it->first.as<std::string>()._Equal(FPS_THRESHOLD))
        {
            fps_threshold = it->second.as<float>();
        }
    }
}

void RenderPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name][MAX_FPS] = max_fps;
    node[group_name][FPS_THRESHOLD] = fps_threshold;
}
