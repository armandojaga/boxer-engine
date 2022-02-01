#include "core/bepch.h"
#include "ModelComponent.h"

BoxerEngine::ModelComponent::ModelComponent(Entity* entity) : Component(type, entity)
{
}

void BoxerEngine::ModelComponent::UpdateUI()
{
    ImGui::Text("Model component here");
}

const char* BoxerEngine::ModelComponent::GetName() const
{
    return "Model";
}
