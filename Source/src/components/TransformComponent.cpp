#include "core/bepch.h"
#include "TransformComponent.h"

#include "modules/ModuleScene.h"
#include "ui/widgets/AxisSlider.h"

BoxerEngine::TransformComponent::TransformComponent(Entity* entity): Component(type, entity)
{
}

void BoxerEngine::TransformComponent::UpdateUI()
{
    AxisSlider::Config config;
    ImGui::PushStyleVar(ImGuiStyleVar_IndentSpacing, 30.0f);
    AxisSlider::Build("Position", position, config);
    if (AxisSlider::Build("Rotation", euler_angles, config))
    {
        const float3 rot = DegToRad(euler_angles);
        rotation = Quat::FromEulerXYZ(rot.x, rot.y, rot.z);
    }

    config.min = float3::zero;
    AxisSlider::Build("Scale", scale, config);
    ImGui::PopStyleVar();
}

const char* BoxerEngine::TransformComponent::GetName() const
{
    return "Transform";
}

void BoxerEngine::TransformComponent::SetPosition(const float3& position)
{
    this->position = position;
}

void BoxerEngine::TransformComponent::SetRotation(const Quat& rotation)
{
    euler_angles = RadToDeg(rotation.ToEulerXYZ());
    this->rotation = rotation;
}

void BoxerEngine::TransformComponent::SetScale(const float3& scale)
{
    this->scale = scale;
}

const float3& BoxerEngine::TransformComponent::GetPosition() const
{
    return position;
}

const Quat& BoxerEngine::TransformComponent::GetRotation() const
{
    return rotation;
}

const float3& BoxerEngine::TransformComponent::GetScale() const
{
    return scale;
}

const float4x4& BoxerEngine::TransformComponent::GetGlobalMatrix()
{
    CalculateGlobalMatrix();
    return global_matrix;
}

void BoxerEngine::TransformComponent::Save(YAML::Node)
{
}

void BoxerEngine::TransformComponent::Load(YAML::Node)
{
}
