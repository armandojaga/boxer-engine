#include "core/bepch.h"
#include "ConfigurationPanel.h"
#include "core/preferences/editor/EditorPreferences.h"

BoxerEngine::ConfigurationPanel::ConfigurationPanel() : Panel("Configuration", true)
{
}

void BoxerEngine::ConfigurationPanel::Update()
{
    prefs = static_cast<EditorPreferences*>(App->preferences->GetEditorPreferences());

    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    float maxFps = game_options.GetMaxFPS();
    ImGui::SliderFloat("##FPSSlider", &maxFps, 24.0f, 250.0f, "FPS %.1f");
    game_options.SetMaxFPS(maxFps);

    bool vsync = prefs->GetVsync();
    ImGui::TextWrapped("Vsync");
    ImGui::SameLine();
    ImGui::Checkbox("##vsync", &vsync);
    prefs->SetVsync(vsync);

    bool fullscreen = prefs->IsFullscreen();
    ImGui::TextWrapped("Fullscreen");
    ImGui::SameLine();
    ImGui::Checkbox("##fullscreen", &fullscreen);
    prefs->SetFullscreen(fullscreen);

    bool displayDebugDraw = prefs->IsDisplayDebugDraw();
    ImGui::TextWrapped("Display debug draw");
    ImGui::SameLine();
    ImGui::Checkbox("##debugdraw", &displayDebugDraw);
    prefs->SetDisplayDebugDraw(displayDebugDraw);

    // float3 values = float3::zero;
    // std::string label = "Camera";
    // BoxerEngine::AxisSlider::Build(label, values);

    ImGui::End();
}
