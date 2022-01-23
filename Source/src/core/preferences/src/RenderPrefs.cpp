
#include "RenderPrefs.h"

using namespace BoxerEngine;

RenderPrefs::RenderPrefs() : Prefs(PreferenceType::RENDER)
{
}

void RenderPrefs::SetConfigData(const YAML::Node& yNode)
{

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

void RenderPrefs::GetConfigData(YAML::Node& output_node)
{
}