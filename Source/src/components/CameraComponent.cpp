#include "core/bepch.h"
#include "CameraComponent.h"
#include "debugdraw.h"

BoxerEngine::CameraComponent::CameraComponent(Entity* entity): Component(type, entity)
{
}

void BoxerEngine::CameraComponent::Init()
{
}

void BoxerEngine::CameraComponent::UpdateUI()
{
    ImGui::Text("Camera component here");
}

void BoxerEngine::CameraComponent::DisplayGizmos()
{
    if (IsEnabled())
    {
        dd::frustum(frustum.ViewProjMatrix().Inverted(), dd::colors::White);
    }
}

const char* BoxerEngine::CameraComponent::GetName() const
{
    return "Camera";
}
