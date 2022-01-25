#pragma once
#include "components/Component.h"
#include <Math/float3.h>

namespace BoxerEngine
{
    class TransformComponent final : public Component
    {
    public:
        inline static Type type = Type::TRANSFORM;

        explicit TransformComponent(Entity* parent);
        ~TransformComponent() override = default;

        void UpdateUI() override;

        [[nodiscard]] const char* GetName() const override;

        [[nodiscard]] const float3& GetPosition() const;
        [[nodiscard]] const float3& GetRotation() const;
        [[nodiscard]] const float3& GetScale() const;
    private:
        float3 position{0.0f};
        float3 rotation{0.0f};
        float3 scale{1.0f};
    };
}
