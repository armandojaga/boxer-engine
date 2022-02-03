#pragma once
#include "components/Component.h"
#include "Geometry/Frustum.h"

namespace BoxerEngine
{
    class CameraComponent : public Component
    {
    public:
        inline static Type type = Type::CAMERA;

        explicit CameraComponent(Entity* entity);
        ~CameraComponent() override = default;

        void Init() override;
        void UpdateUI() override;
        void DisplayGizmos() override;
        [[nodiscard]] const char* GetName() const override;

        void Save(::YAML::Node) override;
        void Load(::YAML::Node) override;
    private:
        Frustum frustum;
    };
}
