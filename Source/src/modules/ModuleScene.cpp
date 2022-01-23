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

ModuleScene::~ModuleScene()
{
    delete scene;
};
