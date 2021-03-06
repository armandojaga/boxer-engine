#include "core/bepch.h"

#include "ModuleScene.h"

bool ModuleScene::Init()
{
    LoadScene("./assets/scene/MyScene.be");

    if (!scene)
    {
        scene = new BoxerEngine::Scene();
    }

    scene->Init();
    return true;
}

bool ModuleScene::Start()
{
    scene->Start();
    return true;
}

update_status ModuleScene::Update(float delta)
{
    scene->Update();
    return update_status::UPDATE_CONTINUE;
}

bool ModuleScene::CleanUp()
{
    SaveScene("MyScene.be");
    return true;
}

void ModuleScene::CreateEmptyScene() const
{
    scene->Clear();
    scene->InitRoot();
    scene->Init();
    scene->Start();
    scene->SetDirty(false);
}

BoxerEngine::Entity* ModuleScene::CreateEmptyEntity() const
{
    scene->SetDirty(true);
    return scene->CreateEntity();
}

void ModuleScene::RemoveEntity(BoxerEngine::Entity* entity) const
{
    if (entity != nullptr)
    {
        entity->GetParent()->RemoveChild(entity->GetId());
        delete entity;
        scene->SetDirty(!scene->IsEmpty());
    }
}

BoxerEngine::Scene* ModuleScene::GetScene() const
{
    return scene;
}

void ModuleScene::SaveScene(const char* sceneName)
{
    scene_serializer.Save(scene, sceneName);
}

void ModuleScene::LoadScene(const char* scenePath)
{
    auto load = [&]
    {
        delete scene;
        scene = scene_serializer.Load(scenePath);
    };
    load();
}

ModuleScene::~ModuleScene()
{
    delete scene;
};
