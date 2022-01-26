#include "core/bepch.h"
#include "ScenePanel.h"

#include "modules/ModuleRender.h"

BoxerEngine::ScenePanel::ScenePanel() : Panel("Scene", true)
{
}

void BoxerEngine::ScenePanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    if (!ImGui::Begin(StringUtils::Concat(ICON_MD_VIEW_MODULE, GetTitle()).c_str(), &visible))
    {
        ImGui::End();
        return;
    }

    const ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    const float x = viewportPanelSize.x;
    const float y = viewportPanelSize.y;

    App->renderer->Resize(x, y);

    // to actually render inside the scene window
    ImGui::Image(reinterpret_cast<void*>(App->renderer->GetFrameBuffer()->GetTextureId()), ImVec2{x, y}, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();
    ImGui::PopStyleVar();
}
