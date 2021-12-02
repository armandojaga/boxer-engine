#include "ModuleScene.h"

bool ModuleScene::Init()
{
    return Module::Init();
}

update_status ModuleScene::PreUpdate()
{
    return Module::PreUpdate();
}

update_status ModuleScene::Update()
{
    return Module::Update();
}

update_status ModuleScene::PostUpdate()
{
    return Module::PostUpdate();
}

bool ModuleScene::CleanUp()
{
    return Module::CleanUp();
}

void ModuleScene::LoadModel(const char* model)
{
}

ModuleScene::~ModuleScene() = default;
