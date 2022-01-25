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

    void CreateEmptyScene();
    BoxerEngine::Entity* CreateEmptyEntity();

    [[nodiscard]] BoxerEngine::Scene* GetScene() const;

private:
    BoxerEngine::Scene* scene = nullptr;
};
