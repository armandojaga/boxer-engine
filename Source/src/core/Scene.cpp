#include "bepch.h"
#include "Scene.h"

const std::string& BoxerEngine::Scene::GetSceneId() const
{
    return id;
}

BoxerEngine::Scene::Scene()
{
    InitRoot();
}

BoxerEngine::Scene::~Scene()
{
    Clear();
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
    e->SetName(StringUtils::Concat("New Entity (", std::to_string(root->GetChildren().size()), ")"));
    if (root) //root can be nullptr when creating a new empty scene
    {
        root->AddChild(e);
    }
    dirty = true;
    return e;
}

void BoxerEngine::Scene::InitRoot()
{
    root = new Entity();
    root->Clear(); //empty entity with no default components
    root->SetName("Untitled");
    id = UUID::GenerateUUIDv4();
}

void BoxerEngine::Scene::Clear()
{
    root->Clear();
    delete root;
    id = "";
    root = nullptr;
}


void BoxerEngine::Scene::SetSceneId(const std::string& newId)
{
    id = newId;
}

bool BoxerEngine::Scene::IsLoaded() const
{
    return loaded;
}

BoxerEngine::Entity* BoxerEngine::Scene::GetRoot() const
{
    return root;
}

void BoxerEngine::Scene::SetDirty(const bool isDirty)
{
    dirty = isDirty;
}

bool BoxerEngine::Scene::IsDirty() const
{
    return dirty;
}

bool BoxerEngine::Scene::IsEmpty() const
{
    return root == nullptr || root->GetChildren().empty();
}
