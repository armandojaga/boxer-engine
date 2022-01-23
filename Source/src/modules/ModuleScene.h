#pragma once
#include "Module.h"
#include "core/Scene.h"

class ModuleScene : public Module
{
public:
    ModuleScene() = default;
    ~ModuleScene() override;

    bool Init() override;
    bool Start() override;
    update_status Update(float delta) override;

private:
    BoxerEngine::Scene* scene = nullptr;
};
