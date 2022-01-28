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

    void CreateEmptyScene() const;
    BoxerEngine::Entity* CreateEmptyEntity() const;
    void RemoveEntity(BoxerEngine::Entity* entity) const;

    [[nodiscard]] BoxerEngine::Scene* GetScene() const;

private:
    BoxerEngine::Scene* scene = nullptr;
};
