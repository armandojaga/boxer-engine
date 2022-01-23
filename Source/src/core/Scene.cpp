#include "bepch.h"
#include "Scene.h"

const std::string& BoxerEngine::Scene::GetSceneId() const
{
    return id;
}

BoxerEngine::Scene::Scene() : root(new Entity())
{
    root->Clear(); //empty entity with no default components
    root->SetName("Untitled");
    id = UUID::GenerateUUIDv4();
}

BoxerEngine::Scene::~Scene()
{
    root->Clear();
    delete root;
    id = "";
    root = nullptr;
}

void BoxerEngine::Scene::Init()
{
    root->Init();
}

void BoxerEngine::Scene::Start()
{
    root->Start();
}

void BoxerEngine::Scene::Update()
{
    root->Update();
}

BoxerEngine::Entity* BoxerEngine::Scene::CreateEntity()
{
    const auto e = new Entity(root);
    root->AddChild(e);
    return e;
}


void BoxerEngine::Scene::SetSceneId(const std::string& newId)
{
    id = newId;
}

bool BoxerEngine::Scene::IsLoaded() const
{
    return loaded;
}

const BoxerEngine::Entity* BoxerEngine::Scene::GetRoot() const
{
    return root;
}
