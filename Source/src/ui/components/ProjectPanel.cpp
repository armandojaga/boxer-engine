#include "core/bepch.h"
#include "ProjectPanel.h"

BoxerEngine::ProjectPanel::ProjectPanel() : Panel("Project", true)
{
}

void BoxerEngine::ProjectPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(StringUtils::Concat(ICON_MD_FOLDER_SPECIAL, GetTitle()).c_str(), &visible))
    {
        ImGui::End();
        return;
    }

    ImGui::Text("Project content here");
    ImGui::End();
}
