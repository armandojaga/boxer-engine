#pragma once

#include <filesystem>
#include <string>
#include <vector>

#include "Module.h"

enum class ResourceType
{
    MODEL = 1,
    TEXTURE,
    AUDIO,
    VIDEO,
    SCRIPT,
    UNKNOWN
};

class ModuleResources : public Module
{
private:
    std::vector<std::pair<ResourceType, std::string>> supported_extensions = {
        {ResourceType::TEXTURE, ".png"},
        {ResourceType::MODEL, ".fbx"}
    };
public:
    bool Init() override;
    bool CleanUp() override;

    void HandleResource(const char* path);
    ResourceType GetType(const std::filesystem::path& file);
};
