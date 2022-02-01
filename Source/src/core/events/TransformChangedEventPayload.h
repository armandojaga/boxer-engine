#pragma once
#include "Math/float3x3.h"

namespace BoxerEngine
{
    struct TransformChangedEventPayload
    {
        TransformChangedEventPayload(const float3x3& transform) : transform(transform)
        {
        }

        [[nodiscard]] float3x3 GetTransform() const
        {
            return transform;
        }

    private:
        float3x3 transform;
    };
}
