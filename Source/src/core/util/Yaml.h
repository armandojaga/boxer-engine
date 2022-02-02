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
            out_vector.x = in_node[NODE_X].as<float>();
            out_vector.y = in_node[NODE_Y].as<float>();
            out_vector.z = in_node[NODE_Z].as<float>();
        }

        static inline void ToFloat2(YAML::Node& in_node, float2& out_vector)
        {
            out_vector.x = in_node[NODE_X].as<float>();
            out_vector.y = in_node[NODE_Y].as<float>();
        }

        static inline float3 ToFloat3(YAML::Node in_node)
        {
            float3 out_vector;
            out_vector.x = in_node[NODE_X].as<float>();
            out_vector.y = in_node[NODE_Y].as<float>();
            out_vector.z = in_node[NODE_Z].as<float>();
            return out_vector;
        }

        static inline float4 ToFloat4(YAML::Node in_node)
        {
            float4 out_vector;
            out_vector.x = in_node[NODE_X].as<float>();
            out_vector.y = in_node[NODE_Y].as<float>();
            out_vector.z = in_node[NODE_Z].as<float>();
            out_vector.w = in_node[NODE_W].as<float>();
            return out_vector;
        }

        static inline float2 ToFloat2(YAML::Node in_node)
        {
            float2 out_vector;
            out_vector.x = in_node[NODE_X].as<float>();
            out_vector.y = in_node[NODE_Y].as<float>();
            return out_vector;
        }
    };
}
