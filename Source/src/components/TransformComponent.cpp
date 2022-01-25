#include "core/bepch.h"
#include "TransformComponent.h"

BoxerEngine::TransformComponent::TransformComponent(Entity* parent): Component(type, parent)
{
}

void BoxerEngine::TransformComponent::UpdateUI()
{
    ImGui::Text("Transform here");
}

const char* BoxerEngine::TransformComponent::GetName() const
{
    return "Transform";
}
