
#include "RenderPrefs.h"

using namespace BoxerEngine;

RenderPrefs::RenderPrefs() : Prefs(PreferenceType::RENDER)
{
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

		if (it->first.as<std::string>()._Equal("vsync"))
		{
			vsync = it->second.as<int>();
			continue;
		}
	}
}

void RenderPrefs::GetConfigData(YAML::Node& output_node)
{
	output_node["render"]["max_fps"] = max_fps;
	output_node["render"]["fps_threshold"] = fps_threshold;
	output_node["render"]["vsync"] = vsync;
}