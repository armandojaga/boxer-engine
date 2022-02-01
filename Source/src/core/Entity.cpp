#include "bepch.h"
#include "Entity.h"
#include "components/TransformComponent.h"

BoxerEngine::Entity::Entity() : Entity(nullptr)
{
}

BoxerEngine::Entity::Entity(Entity* parent) : id(UUID::GenerateUID()), parent(parent)
{
    CreateComponent<TransformComponent>();
}

BoxerEngine::Entity::~Entity()
{
    Clear();
}

void BoxerEngine::Entity::Init()
{
    for (const auto& component : components)
    {
        component->Init();
    }

    for (const auto child : children)
    {
        child->Init();
    }
}

void BoxerEngine::Entity::Start()
{
    for (const auto& component : components)
    {
        component->Start();
    }

    for (const auto child : children)
    {
        child->Start();
    }
}

void BoxerEngine::Entity::Update()
{
    for (const auto& component : components)
    {
        component->Update();
    }

    for (const auto child : children)
    {
        child->Update();
    }
}

void BoxerEngine::Entity::DisplayGizmos() const
{
    for (const auto& component : components)
    {
        component->DisplayGizmos();
    }

    for (const auto child : children)
    {
        child->DisplayGizmos();
    }
}

void BoxerEngine::Entity::Draw() const
{
    for (const auto& component : components)
    {
        component->Draw();
    }

    for (const auto child : children)
    {
        child->Draw();
    }
}

void BoxerEngine::Entity::SetParent(Entity* parentEntity)
{
    if (parentEntity && parentEntity != this)
    {
        parent->RemoveChild(id);
        parent = parentEntity;
        parent->AddChild(this);
    }
}

BoxerEngine::Entity* BoxerEngine::Entity::GetParent() const
{
    return parent;
}

void BoxerEngine::Entity::AddChild(Entity* child)
{
    if (child && child != this && !Has(child->GetId()))
    {
        children.emplace_back(child);
    }
}

bool BoxerEngine::Entity::HasChildren() const
{
    return !children.empty();
}

BoxerEngine::Entity* BoxerEngine::Entity::GetEntity(UID entityId)
{
    auto sameId = [&](const auto c) { return c->GetId() == entityId; };
    return GetEntity(sameId);
}

BoxerEngine::Entity* BoxerEngine::Entity::GetEntity(const std::string& entityName)
{
    auto sameName = [&](const auto c) { return c->GetName() == entityName; };
    return GetEntity(sameName);
}


BoxerEngine::Entity* BoxerEngine::Entity::GetEntity(const std::function<bool(Entity*)>& predicate)
{
    const auto result = std::find_if(std::begin(children), std::end(children), predicate);
    if (result != std::end(children))
    {
        return *result;
    }
    return nullptr;
}

void BoxerEngine::Entity::RemoveChild(UID entityId)
{
    auto isSameEntityId = [&](const auto entt) { return entt->GetId() == entityId; };
    children.erase(
        std::remove_if(std::begin(children), std::end(children), isSameEntityId),
        children.end()
    );
}

bool BoxerEngine::Entity::IsChildOf(UID entityId) const
{
    if (!GetParent())
    {
        return false;
    }
    if (GetParent()->GetId() == entityId)
    {
        return true;
    }
    return GetParent()->IsChildOf(entityId);
}

void BoxerEngine::Entity::RemoveComponent(UID componentId)
{
    auto isSameComponentId = [&](const auto c) { return c->GetId() == componentId; };
    components.erase(
        std::remove_if(std::begin(components), std::end(components), isSameComponentId),
        components.end()
    );
}

void BoxerEngine::Entity::Enable()
{
    enabled = true;
}

void BoxerEngine::Entity::Disable()
{
    enabled = false;
}

BoxerEngine::UID BoxerEngine::Entity::GetId() const
{
    return id;
}

const std::string& BoxerEngine::Entity::GetName() const
{
    return name;
}

void BoxerEngine::Entity::SetName(const std::string& newName)
{
    this->name = newName;
}

bool BoxerEngine::Entity::IsEnabled() const
{
    return enabled;
}

std::vector<std::shared_ptr<BoxerEngine::Component>> BoxerEngine::Entity::GetComponents() const
{
    return components;
}

std::vector<BoxerEngine::Entity*> BoxerEngine::Entity::GetChildren() const
{
    return children;
}

void BoxerEngine::Entity::Clear()
{
    components.erase(std::begin(components), std::end(components));
    for (const auto child : children)
    {
        delete child;
    }
    children.clear();
    components.clear();
}

void BoxerEngine::Entity::SetId(const UID newId)
{
    this->id = newId;
}

bool BoxerEngine::Entity::Has(const UID entityId)
{
    auto isSameEntity = [&](const auto entt) { return entt->GetId() == entityId; };
    return std::find_if(std::begin(children), std::end(children), isSameEntity) != std::end(children);
}
