#include "core/bepch.h"
#include "CameraComponent.h"

BoxerEngine::CameraComponent::CameraComponent(Entity* parent): Component(type, parent)
{
}

void BoxerEngine::CameraComponent::UpdateUI()
{
    ImGui::Text("Camera component here");
}

const char* BoxerEngine::CameraComponent::GetName() const
{
    return "Camera";
}
