#include "core/bepch.h"
#include "HierarchyPanel.h"

#include "modules/ModuleScene.h"

BoxerEngine::HierarchyPanel::HierarchyPanel() : Panel("Hierarchy", true)
{
}

void BoxerEngine::HierarchyPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    UpdateHierarchyTree(App->scene->GetScene()->GetRoot());
    ImGui::End();
}

void BoxerEngine::HierarchyPanel::CreateEmptyEntity()
{
    App->scene->CreateEmptyEntity();
}

//updating only the tree of an entity improves performance when only it changes
void BoxerEngine::HierarchyPanel::UpdateHierarchyTree(const Entity* entity)
{
    auto children = entity->GetChildren();
    
}
