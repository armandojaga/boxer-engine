
#include "RenderPrefs.h"

using namespace BoxerEngine;

RenderPrefs::RenderPrefs() : Prefs(PreferenceType::RENDER)
{
}

void RenderPrefs::LoadConfig(const YAML::Node& yNode)
{
	for (auto it = yNode.begin(); it != yNode.end(); ++it)
	{
		if (it->first.as<std::string>()._Equal("display_debug_draw"))
		{
			display_debug_draw = it->second.as<bool>();
			continue;
		}

		if (it->first.as<std::string>()._Equal("scene_background_color"))
		{
			//scene_background_color[0] = it->second[0].as<float>();
			//scene_background_color[1] = it->second[1].as<float>();
			//scene_background_color[2] = it->second[2].as<float>();
			continue;
		}
	}

	//for (YAML::const_iterator it = yNode.begin(); it != yNode.end(); ++it) {
	//	std::string key = it->first.as<std::string>();
	//	YAML::Node value = it->second;
	//	// here, you can check what type the value is (e.g., scalar, sequence, etc.)
	//	switch (value.Type()) {
	//		case YAML::NodeType::Scalar: // do stuff
	//		case YAML::NodeType::Sequence: // do stuff
	//	}
	//}
}

void RenderPrefs::SaveConfig()
{
}