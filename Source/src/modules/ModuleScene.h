#pragma once
#include "Module.h"
#include "core/Scene.h"
#include "core/SceneSerializer.h"

class ModuleScene : public Module
{
public:
    ModuleScene() = default;
    ~ModuleScene() override;

    bool Init() override;
    bool Start() override;
    update_status Update(float delta) override;
    bool CleanUp() override;

    void CreateEmptyScene() const;
    BoxerEngine::Entity* CreateEmptyEntity() const;
    void RemoveEntity(BoxerEngine::Entity* entity) const;

    [[nodiscard]] BoxerEngine::Scene* GetScene() const;
    void SaveScene();
private:
    BoxerEngine::Scene* scene = nullptr;
    BoxerEngine::SceneSerializer scene_serializer;
};
