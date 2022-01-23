#include "EditorPrefs.h"

using namespace BoxerEngine;

EditorPrefs::EditorPrefs() : Prefs(PreferenceType::EDITOR)
{
}

void EditorPrefs::LoadConfig(const YAML::Node& yNode)
{
	for (auto it = yNode.begin(); it != yNode.end(); ++it)
	{
		if (it->first.as<std::string>()._Equal("display_about"))
		{
			display_about = it->second.as<bool>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("display_console"))
		{
			display_console = it->second.as<bool>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("display_stats"))
		{
			display_stats = it->second.as<bool>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("display_config"))
		{
			display_config = it->second.as<bool>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("display_hardware"))
		{
			display_hardware = it->second.as<bool>();
			continue;
		}

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
	}
}

void EditorPrefs::SaveConfig()
{
}
