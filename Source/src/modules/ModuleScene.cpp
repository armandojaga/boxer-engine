#include "ModuleScene.h"

bool ModuleScene::Init()
{
    scene = new BoxerEngine::Scene();
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

void ModuleScene::CreateEmptyScene()
{
    scene->Clear();
    scene->InitRoot();
    scene->Init();
    scene->Start();
}

BoxerEngine::Entity* ModuleScene::CreateEmptyEntity()
{
    return scene->CreateEntity();
}

BoxerEngine::Scene* ModuleScene::GetScene() const
{
    return scene;
}

ModuleScene::~ModuleScene()
{
    delete scene;
};
