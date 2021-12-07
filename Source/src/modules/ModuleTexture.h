#pragma once

#include <string>

#include "Module.h"
#include "IL/il.h"
#include "IL/ilu.h"

class ModuleTexture : public Module
{
private:

public:
    ModuleTexture() = default;
    ~ModuleTexture() override = default;

    bool Init() override;
    bool CleanUp() override;
    unsigned int Load(std::string&&);
};
