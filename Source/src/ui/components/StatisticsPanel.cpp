#include "core/bepch.h"
#include "StatisticsPanel.h"

BoxerEngine::StatisticsPanel::StatisticsPanel(): Panel("Statistics", false)
{
}

void BoxerEngine::StatisticsPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    static int counter = 0;
    static float fps = App->statistics->GetFramesPerSecond();
    static float ms = App->statistics->GetFrameSpeed();
    if (counter >= 10)
    {
        fps = App->statistics->GetFramesPerSecond();
        ms = App->statistics->GetFrameSpeed();
        counter = 0;
    }
    ++counter;
    ImGui::TextWrapped("Memory used: %d MB", App->statistics->GetUsedMemory() / 1000000);
    char fpsOverlay[32];
    sprintf(fpsOverlay, "FPS %.2f", fps);
    const float fpsLimit = App->statistics->GetFramesPerSecond() + 10.0f;
    ImGui::PlotHistogram("##framerate", *App->statistics->GetFPSLog(), IM_ARRAYSIZE(*App->statistics->GetFPSLog()), 0, fpsOverlay, 0.0f, fpsLimit, ImVec2(310, 100));

    char msOverlay[32];
    sprintf(msOverlay, "%.2f ms", ms);
    ImGui::PlotHistogram("##framespeed", *App->statistics->GetMSLog(), IM_ARRAYSIZE(*App->statistics->GetMSLog()), 0, msOverlay, 0.0f, 40.0f, ImVec2(310, 100));
    ImGui::End();
}
