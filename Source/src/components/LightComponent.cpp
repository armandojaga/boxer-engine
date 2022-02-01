#include "core/bepch.h"
#include "LightComponent.h"


BoxerEngine::LightComponent::LightComponent(Entity* entity): Component(type, entity)
{
}

void BoxerEngine::LightComponent::UpdateUI()
{
    int selected = static_cast<int>(lightType);;
    const char* items[static_cast<int>(Light::Type::COUNT)]{};
    items[static_cast<int>(Light::Type::SPOT)] = "Spot";
    items[static_cast<int>(Light::Type::DIRECTIONAL)] = "Directional";
    items[static_cast<int>(Light::Type::POINT)] = "Point";
    if(ImGui::Combo("##light", &selected, items, IM_ARRAYSIZE(items)))
    {
        lightType = static_cast<Light::Type>(selected);
    }
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
