#include "core/bepch.h"
#include "ConfigurationPanel.h"

BoxerEngine::ConfigurationPanel::ConfigurationPanel() : Panel("Configuration", true)
{
}

void BoxerEngine::ConfigurationPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    float maxFps = game_options.GetMaxFPS();
    ImGui::SliderFloat("##FPSSlider", &maxFps, 24.0f, 250.0f, "FPS %.1f");
    game_options.SetMaxFPS(maxFps);

    bool vsync = game_options.GetVsync();
    ImGui::TextWrapped("Vsync");
    ImGui::SameLine();
    ImGui::Checkbox("##vsync", &vsync);
    game_options.SetVsync(vsync);

    bool fullscreen = game_options.IsFullscreen();
    ImGui::TextWrapped("Fullscreen");
    ImGui::SameLine();
    ImGui::Checkbox("##fullscreen", &fullscreen);
    game_options.SetFullscreen(fullscreen);

    bool displayDebugDraw = game_options.IsDisplayDebugDraw();
    ImGui::TextWrapped("Display debug draw");
    ImGui::SameLine();
    ImGui::Checkbox("##debugdraw", &displayDebugDraw);
    game_options.SetDisplayDebugDraw(displayDebugDraw);

    // float3 values = float3::zero;
    // std::string label = "Camera";
    // BoxerEngine::AxisSlider::Build(label, values);

    ImGui::End();
}
