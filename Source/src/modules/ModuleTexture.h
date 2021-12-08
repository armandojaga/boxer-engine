#pragma once

#include "Module.h"

class ModuleTexture : public Module
{
private:

public:
    ModuleTexture() = default;
    ~ModuleTexture() override = default;

    bool Init() override;
    bool CleanUp() override;
    unsigned int Load(const char*, const char* = nullptr);
};
