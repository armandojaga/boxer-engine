
#include "RenderPrefs.h"

using namespace BoxerEngine;

RenderPrefs::RenderPrefs() : Prefs(PreferenceType::RENDER)
{
	group_name = "render";
}

void RenderPrefs::SetConfigData(const YAML::Node& yNode)
{
	for (auto it = yNode.begin(); it != yNode.end(); ++it)
	{
		if (it->first.as<std::string>()._Equal("max_fps"))
		{
			max_fps = it->second.as<float>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("fps_threshold"))
		{
			fps_threshold = it->second.as<float>();
			continue;
		}
	}
}

void RenderPrefs::GetConfigData(YAML::Node& output_node)
{
	output_node[group_name]["max_fps"] = max_fps;
	output_node[group_name]["fps_threshold"] = fps_threshold;
}