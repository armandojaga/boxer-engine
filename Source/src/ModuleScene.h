#pragma once
#include "Module.h"

class ModuleScene : public Module
{
private:
public:
    ModuleScene() = default;
    ~ModuleScene() override;

    bool Init() override;

    update_status PreUpdate() override;
    update_status Update() override;
    update_status PostUpdate() override;

    bool CleanUp() override;

    void LoadModel(const char*);
};
