#pragma once
#include "Component.h"

namespace BoxerEngine
{
    class LightComponent : public Component
    {
    public:
        inline static Type type = Type::LIGHT;

        explicit LightComponent(Entity* entity);
        ~LightComponent() override = default;

        void UpdateUI() override;

        [[nodiscard]] float3 GetColor() const;
        [[nodiscard]] float GetIntensity() const;

        [[nodiscard]] const char* GetName() const override;
    private:
        float3 color{255.0f};
        float intensity = 1.0f;
    };
}
