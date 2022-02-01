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
            scene_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("models_assets"))
        {
            models_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("meshes_assets"))
        {
            meshes_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("textures_assets"))
        {
            textures_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("audio_assets"))
        {
            audio_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("video_assets"))
        {
            video_assets = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("script_assets"))
        {
            script_assets = std::move(it->second.as<std::string>());
            continue;
        }

        // Library path
        if (it->first.as<std::string>()._Equal("scene_library"))
        {
            meshes_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("models_library"))
        {
            models_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("meshes_library"))
        {
            meshes_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("textures_library"))
        {
            textures_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("audio_library"))
        {
            audio_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("video_library"))
        {
            video_library = std::move(it->second.as<std::string>());
            continue;
        }

        if (it->first.as<std::string>()._Equal("script_library"))
        {
            script_library = std::move(it->second.as<std::string>());
        }
    }
}

void ResourcesPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["scene_assets"] = scene_assets;
    node[group_name]["models_assets"] = models_assets;
    node[group_name]["meshes_assets"] = meshes_assets;
    node[group_name]["textures_assets"] = textures_assets;
    node[group_name]["audio_assets"] = audio_assets;
    node[group_name]["video_assets"] = video_assets;
    node[group_name]["script_assets"] = script_assets;

    node[group_name]["scene_library"] = scene_library;
    node[group_name]["models_library"] = models_library;
    node[group_name]["meshes_library"] = meshes_library;
    node[group_name]["textures_library"] = textures_library;
    node[group_name]["audio_library"] = audio_library;
    node[group_name]["video_library"] = video_library;
    node[group_name]["script_library"] = script_library;
}

const char* ResourcesPreferences::GetAssetsPath(ResourceType type)
{
    switch (type)
    {
    case ResourceType::SCENE:
        return scene_assets.c_str();
    case ResourceType::MODEL:
        return models_assets.c_str();
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
    default:
        assert(false);
    }
}

const char* ResourcesPreferences::GetLibraryPath(ResourceType type) const
{
    switch (type)
    {
    case ResourceType::SCENE:
        return scene_library.c_str();
    case ResourceType::MODEL:
        return models_library.c_str();
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
    default:
        assert(false);
    }
}
