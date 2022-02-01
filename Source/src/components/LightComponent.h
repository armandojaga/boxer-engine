#pragma once
#include "Component.h"

namespace BoxerEngine
{
    namespace Light
    {
        enum class Type
        {
            SPOT,
            DIRECTIONAL,
            POINT
        };
    }

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
        float intensity = 1.0f;
        float radius = 1.0f;

        float3 color{255.0f};
        float3 direction{0.0f};

        Light::Type lightType = Light::Type::SPOT;
    };
}
