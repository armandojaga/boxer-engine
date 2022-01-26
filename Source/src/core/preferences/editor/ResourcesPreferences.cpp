
#include <cassert>

#include "ResourcesPreferences.h"

using namespace BoxerEngine;

ResourcesPreferences::ResourcesPreferences() : Preferences(Type::RESOURCES)
{
	group_name = "resources";
}
void ResourcesPreferences::SetConfigurationData(const YAML::Node& node)
{
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("meshes_path"))
        {
            meshes_path = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("textures_path"))
        {
            textures_path = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("audio_path"))
        {
            audio_path = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("video_path"))
        {
            video_path = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("script_path"))
        {
            script_path = it->second.as<std::string>();
            continue;
        }
    }
}

void ResourcesPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["meshes_path"] = meshes_path;
    node[group_name]["textures_path"] = textures_path;
    node[group_name]["audio_path"] = audio_path;
    node[group_name]["video_path"] = video_path;
    node[group_name]["script_path"] = script_path;
}

const char* BoxerEngine::ResourcesPreferences::GetResourcePath(ResourceType type)
{
    switch (type)
    {
    case ResourceType::MODEL:
        return meshes_path.c_str();
    case ResourceType::TEXTURE:
        return textures_path.c_str();
    case ResourceType::AUDIO:
        return audio_path.c_str();
    case ResourceType::VIDEO:
        return video_path.c_str();
    case ResourceType::SCRIPT:
        return script_path.c_str();
    case ResourceType::UNKNOWN:
        assert(false);
    }
}
