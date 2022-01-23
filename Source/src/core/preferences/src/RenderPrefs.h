#pragma once
#include "../Prefs.h"
//#include "Math/float3.h"

namespace BoxerEngine
{
    class RenderPrefs final : public Prefs
    {
    public:
        RenderPrefs();
        ~RenderPrefs() = default;
        void SetConfigData(const YAML::Node& yNode) override;
        void GetConfigData(YAML::Node& output_node) override;
    };
}


