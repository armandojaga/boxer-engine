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
        {BoxerEngine::ResourceType::TEXTURE, ".tif"},
        {BoxerEngine::ResourceType::MODEL, ".fbx"},
        {BoxerEngine::ResourceType::SCENE, ".be"}
    };
    BoxerEngine::ResourcesPreferences* preferences = nullptr;
    BoxerEngine::FileManager file_manager;
    std::filesystem::path last_resource_path; // TODO: This will track every resource, his type and path loaded

    void HandleAssetsChanged(const std::filesystem::path& asset, BoxerEngine::ResourceType asset_type);
    void HandleResource(const std::filesystem::path& path);
public:
    bool Init() override;
    bool CleanUp() override;

    [[nodiscard]] std::filesystem::path GetLastResourceLoadedPath() const;
    BoxerEngine::ResourceType GetType(const std::filesystem::path& file);
};
