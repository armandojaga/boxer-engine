#pragma once
#include "Module.h"

class ModuleScene : public Module
{
private:
public:
    ModuleScene() = default;
    ~ModuleScene() override;

    bool Init() override;
    bool CleanUp() override;
};
