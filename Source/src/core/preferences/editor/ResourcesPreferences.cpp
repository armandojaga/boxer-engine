
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
        // Assets path
        if (it->first.as<std::string>()._Equal("scene_assets"))
        {
            scene_assets = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("meshes_assets"))
        {
            meshes_assets = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("textures_assets"))
        {
            textures_assets = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("audio_assets"))
        {
            audio_assets = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("video_assets"))
        {
            video_assets = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("script_assets"))
        {
            script_assets = it->second.as<std::string>();
            continue;
        }

        // Library path
        if (it->first.as<std::string>()._Equal("scene_library"))
        {
            meshes_library = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("meshes_library"))
        {
            meshes_library = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("textures_library"))
        {
            textures_library = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("audio_library"))
        {
            audio_library = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("video_library"))
        {
            video_library = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("script_library"))
        {
            script_library = it->second.as<std::string>();
            continue;
        }
    }
}

void ResourcesPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["scene_assets"] = meshes_assets;
    node[group_name]["meshes_assets"] = meshes_assets;
    node[group_name]["textures_assets"] = textures_assets;
    node[group_name]["audio_assets"] = audio_assets;
    node[group_name]["video_assets"] = video_assets;
    node[group_name]["script_assets"] = script_assets;

    node[group_name]["scene_library"] = meshes_library;
    node[group_name]["meshes_library"] = meshes_library;
    node[group_name]["textures_library"] = textures_library;
    node[group_name]["audio_library"] = audio_library;
    node[group_name]["video_library"] = video_library;
    node[group_name]["script_library"] = script_library;
}

const char* BoxerEngine::ResourcesPreferences::GetAssetsPath(ResourceType type)
{
    switch (type)
    {
    case ResourceType::SCENE:
        return scene_assets.c_str();    
    case ResourceType::MESH:
        return meshes_assets.c_str();
    case ResourceType::TEXTURE:
        return textures_assets.c_str();
    case ResourceType::AUDIO:
        return audio_assets.c_str();
    case ResourceType::VIDEO:
        return video_assets.c_str();
    case ResourceType::SCRIPT:
        return script_assets.c_str();
    case ResourceType::UNKNOWN:
        assert(false);
    }
}

const char* BoxerEngine::ResourcesPreferences::GetLibraryPath(ResourceType type)
{
    switch (type)
    {
    case ResourceType::SCENE:
        return scene_library.c_str();
    case ResourceType::MESH:
        return meshes_library.c_str();
    case ResourceType::TEXTURE:
        return textures_library.c_str();
    case ResourceType::AUDIO:
        return audio_library.c_str();
    case ResourceType::VIDEO:
        return video_library.c_str();
    case ResourceType::SCRIPT:
        return script_library.c_str();
    case ResourceType::UNKNOWN:
        assert(false);
    }
}
