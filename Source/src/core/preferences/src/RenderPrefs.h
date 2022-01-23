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
        void LoadConfig(const YAML::Node& yNode) override;
        void SaveConfig() override;

        void SetDisplayDebugDraw(const bool displayDebugDraw)
        {
            display_debug_draw = displayDebugDraw;
        }

        [[nodiscard]] bool IsDisplayDebugDraw() const
        {
            return display_debug_draw;
        }

        //void SetSceneBackgroundColor(const float3& sceneBackgroundColor)
        //{
        //    scene_background_color = sceneBackgroundColor;
        //}

        //[[nodiscard]] const float3& GetSceneBackgroundColor() const
        //{
        //    return scene_background_color;
        //}
    private:
        bool display_debug_draw = false;
        //float3 scene_background_color = float3(0.0f);
    };
}


