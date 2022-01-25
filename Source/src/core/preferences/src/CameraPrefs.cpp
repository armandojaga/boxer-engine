#include "CameraPrefs.h"

using namespace BoxerEngine;

CameraPrefs::CameraPrefs() : Prefs(PreferenceType::CAMERA)
{
	group_name = "camera";
}

void CameraPrefs::SetConfigData(const YAML::Node& yNode)
{
	for (auto it = yNode.begin(); it != yNode.end(); ++it)
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
			continue;
		}
	}
}

void CameraPrefs::GetConfigData(YAML::Node& output_node)
{
	output_node["camera"]["move_speed"] = move_speed;
	output_node["camera"]["rotation_speed"] = rotation_speed;
	output_node["camera"]["orbit_speed"] = orbit_speed;
	output_node["camera"]["zoom_speed"] = zoom_speed;
	output_node["camera"]["fov"] = fov;
}
	