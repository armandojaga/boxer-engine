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

    private:
        float max_fps = 250.0;
        int vsync = 0;
        float fps_threshold = 1000.0 / max_fps;
    };
}


