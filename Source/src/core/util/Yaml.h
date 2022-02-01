#pragma once

#include "yaml-cpp/yaml.h"
#include "Math/float3.h"
#include "Math/float2.h"

namespace BoxerEngine
{
    class Yaml
    {
    public:
        static inline void ToFloat3(YAML::Node& in_node, float3& out_vector)
        {
            out_vector.x = in_node["x"].as<float>();
            out_vector.y = in_node["y"].as<float>();
            out_vector.z = in_node["z"].as<float>();
        }

        static inline void ToFloat2(YAML::Node& in_node, float2& out_vector)
        {
            out_vector.x = in_node["x"].as<float>();
            out_vector.y = in_node["y"].as<float>();
        }
    };
}
