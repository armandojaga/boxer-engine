#include "core/bepch.h"
#include "TransformComponent.h"

BoxerEngine::TransformComponent::TransformComponent(Entity* parent): Component(type, parent)
{
}

void BoxerEngine::TransformComponent::UpdateUI()
{
    BE_LOG("Transform component update ui");
    if (ImGui::CollapsingHeader("Transform"))
    {
    }
}
