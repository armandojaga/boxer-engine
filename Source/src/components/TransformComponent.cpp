#include "core/bepch.h"
#include "TransformComponent.h"
#include "ui/widgets/AxisSlider.h"

BoxerEngine::TransformComponent::TransformComponent(Entity* entity): Component(type, entity)
{
}

void BoxerEngine::TransformComponent::UpdateUI()
{
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 30.0f);
    AxisSlider::Build("Position", position);
    AxisSlider::Build("Rotation", rotation);
    AxisSlider::Build("Scale", scale);
    ImGui::PopStyleVar();
}

const char* BoxerEngine::TransformComponent::GetName() const
{
    return "Transform";
}

const float3& BoxerEngine::TransformComponent::GetPosition() const
{
    return position;
}

const float3& BoxerEngine::TransformComponent::GetRotation() const
{
    return rotation;
}

const float3& BoxerEngine::TransformComponent::GetScale() const
{
    return scale;
}
