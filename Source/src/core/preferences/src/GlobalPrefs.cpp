#include "GlobalPrefs.h"

using namespace BoxerEngine;

GlobalPrefs::GlobalPrefs() : Prefs(PreferenceType::GLOBALS)
{
}

void GlobalPrefs::SetConfigData(const YAML::Node& yNode)
{
	for (auto it = yNode.begin(); it != yNode.end(); ++it)
	{
		if (it->first.as<std::string>()._Equal("title"))
		{
			title = it->second.as<std::string>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("version"))
		{
			version = it->second.as<std::string>();
			continue;
		}
	}
}

void GlobalPrefs::GetConfigData(YAML::Node& output_node)
{
	output_node["globals"]["title"] = title;
	output_node["globals"]["version"] = version;
}
