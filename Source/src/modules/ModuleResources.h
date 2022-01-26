#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Module.h"
#include "core/preferences/editor/ResourcesPreferences.h"
#include "core/file system/FileManager.h"

class ModuleResources : public Module
{
private:
    std::vector<std::pair<BoxerEngine::ResourceType, std::string>> supported_extensions = {
        {BoxerEngine::ResourceType::TEXTURE, ".png"},
        {BoxerEngine::ResourceType::MODEL, ".fbx"}
    };
    BoxerEngine::ResourcesPreferences* preferences = nullptr;
    BoxerEngine::FileManager file_manager;

    void HandleAssetsChanged(const std::filesystem::path& asset,const BoxerEngine::ResourceType asset_type);
public:
    bool Init() override;
    bool CleanUp() override;

    void HandleResource(const std::filesystem::path& path);
    BoxerEngine::ResourceType GetType(const std::filesystem::path& file);
};
