#include "core/bepch.h"
#include "Component.h"

BoxerEngine::Component::Component(Entity* parent): id(UUID::GenerateUID()), parent(parent)
{
}

BoxerEngine::Component::Component(const Type type, Entity* parent): type(type), id(UUID::GenerateUID()), parent(parent)
{
}

void BoxerEngine::Component::Init()
{
}

void BoxerEngine::Component::Start()
{
}

void BoxerEngine::Component::Update()
{
}

void BoxerEngine::Component::UpdateUI()
{
}

void BoxerEngine::Component::DisplayGizmos()
{
}

void BoxerEngine::Component::Draw()
{
}

void BoxerEngine::Component::Enable()
{
    enabled = true;
}

void BoxerEngine::Component::Disable()
{
    enabled = false;
}

bool BoxerEngine::Component::IsEnabled() const
{
    return enabled;
}

BoxerEngine::Component::Type BoxerEngine::Component::GetType() const
{
    return type;
}

void BoxerEngine::Component::SetType(Type type)
{
    this->type = type;
}

BoxerEngine::UID BoxerEngine::Component::GetId() const
{
    return id;
}

void BoxerEngine::Component::SetId(const UID id)
{
    this->id = id;
}
