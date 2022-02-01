#pragma once

#include "Module.h"
#include <map>

class ModuleTexture : public Module
{
public:
    ModuleTexture() = default;
    ~ModuleTexture() override = default;

    bool Init() override;
    bool CleanUp() override;
    unsigned int Load(const char* texture_name);
private:
    std::map<std::string, unsigned int> textures_loaded{};

    unsigned int LoadNew(const char* texture_name);
};
