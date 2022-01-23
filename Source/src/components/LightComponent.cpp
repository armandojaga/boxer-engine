#include "core/bepch.h"
#include "LightComponent.h"


BoxerEngine::LightComponent::LightComponent(Entity* parent): Component(type, parent)
{
}

float3 BoxerEngine::LightComponent::GetColor() const
{
    return color;
}

float BoxerEngine::LightComponent::GetIntensity() const
{
    return intensity;
}
