#pragma once
#include "Component.h"

namespace BoxerEngine
{
    class LightComponent : public Component
    {
    public:
        inline static Type type = Type::LIGHT;

        explicit LightComponent(Entity* parent);
        ~LightComponent() override = default;

        [[nodiscard]] float3 GetColor() const;
        [[nodiscard]] float GetIntensity() const;
    private:
        float3 color{255.0f};
        float intensity = 1.0f;
    };
}
