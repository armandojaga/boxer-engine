#include "core/bepch.h"
#include "InspectorPanel.h"

BoxerEngine::InspectorPanel::InspectorPanel(): Panel("Inspector", true)
{
}

void BoxerEngine::InspectorPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(200, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    ImGui::End();
}
