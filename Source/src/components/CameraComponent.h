#pragma once
#include "components/Component.h"

namespace BoxerEngine
{
    class CameraComponent : public Component
    {
    public:
        inline static Type type = Type::CAMERA;

        explicit CameraComponent(Entity* parent);
        ~CameraComponent() override = default;

        void UpdateUI() override;
        [[nodiscard]] const char* GetName() const override;
    };
}
