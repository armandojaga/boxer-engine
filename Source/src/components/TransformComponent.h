#pragma once
#include "components/Component.h"
#include <Math/float3.h>

#include "Math/float4x4.h"
#include "Math/Quat.h"
#include "modules/ModuleScene.h"
#include "Application.h"

namespace BoxerEngine
{
    class TransformComponent final : public Component
    {
    public:
        inline static Type type = Type::TRANSFORM;

        explicit TransformComponent(Entity* entity);
        ~TransformComponent() override = default;

        void UpdateUI() override;

        [[nodiscard]] const char* GetName() const override;

        void SetPosition(const float3& position);
        void SetRotation(const Quat& rotation);
        void SetScale(const float3& scale);

        [[nodiscard]] const float3& GetPosition() const;
        [[nodiscard]] const Quat& GetRotation() const;
        [[nodiscard]] const float3& GetScale() const;

        void CalculateGlobalMatrix()
        {
            local_matrix = float4x4::FromTRS(position, rotation, scale);

            Entity* parent = GetEntity()->GetParent();
            if (parent != nullptr && parent != App->scene->GetScene()->GetRoot())
            {
                TransformComponent* parentTransform = parent->GetComponent<TransformComponent>();
                parentTransform->CalculateGlobalMatrix();
                global_matrix = parentTransform->global_matrix * local_matrix;
            }
            else
            {
                global_matrix = local_matrix;
            }
        }

        [[nodiscard]] const float4x4& GetGlobalMatrix();

        void Save(::YAML::Node) override;
        void Load(::YAML::Node) override;

    private:
        float3 position = float3::zero;
        Quat rotation = Quat::identity;
        float3 scale = float3::one;
        float3 euler_angles = float3::zero;

        float4x4 local_matrix = float4x4::identity;
        float4x4 global_matrix = float4x4::identity;
    };
}
