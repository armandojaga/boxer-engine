#include "core/bepch.h"
#include "LightComponent.h"


BoxerEngine::LightComponent::LightComponent(Entity* entity): Component(type, entity)
{
}

void BoxerEngine::LightComponent::UpdateUI()
{
    ImGui::Text("Light here");
}

float3 BoxerEngine::LightComponent::GetColor() const
{
    return color;
}

float BoxerEngine::LightComponent::GetIntensity() const
{
    return intensity;
}

const char* BoxerEngine::LightComponent::GetName() const
{
    return "Light";
}
