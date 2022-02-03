#pragma once
#include <mutex>
#include "Module.h"
#include "core/Scene.h"
#include "core/serialization/SceneSerializer.h"

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
    [[nodiscard]] BoxerEngine::Entity* CreateEmptyEntity() const;
    void RemoveEntity(BoxerEngine::Entity* entity) const;

    [[nodiscard]] BoxerEngine::Scene* GetScene() const;

    void SaveScene(const char* sceneName);
    void LoadScene(const char* scenePath);

private:
    BoxerEngine::Scene* scene = nullptr;
    BoxerEngine::SceneSerializer scene_serializer;
    std::mutex scene_acces;
};
