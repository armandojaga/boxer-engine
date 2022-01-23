#include "core/bepch.h"
#include "HierarchyPanel.h"

#include "core/util/StringUtils.h"
#include "modules/ModuleScene.h"

BoxerEngine::HierarchyPanel::HierarchyPanel() : Panel("Hierarchy", true)
{
}

void BoxerEngine::HierarchyPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_FirstUseEver);
    if (ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::PushID("hierarchyGlobalContextualMenu");
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Create Empty"))
            {
                App->scene->CreateEmptyEntity();
                //TODO select this object
            }
            ImGui::EndPopup();
        }
        ImGui::PopID();
        UpdateHierarchyTree(App->scene->GetScene()->GetRoot());
        ImGui::End();
    }
}

void BoxerEngine::HierarchyPanel::CreateEmptyEntity()
{
    App->scene->CreateEmptyEntity();
}

//updating only the tree of an entity improves performance when only it changes
void BoxerEngine::HierarchyPanel::UpdateHierarchyTree(Entity* entity)
{
    const auto children = entity->GetChildren();
    constexpr ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    ImGuiTreeNodeFlags nodeFlags = baseFlags;
    bool selected = true;
    //TODO how to determine currently selected entity?

    if (entity == App->scene->GetScene()->GetRoot())
    {
        nodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
    }
    if (selected)
    {
        nodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    if (children.empty())
    {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }

    bool nodeOpen = ImGui::TreeNodeEx(entity->GetName().c_str(), nodeFlags);

    ImGui::PushID(entity->GetName().c_str());
    if (ImGui::BeginPopupContextItem(entity->GetName().c_str()))
    {
        if (ImGui::Selectable("Create Empty"))
        {
            auto e = App->scene->CreateEmptyEntity();
            e->SetParent(entity);
            e->SetName(StringUtils::Concat("New Entity (", std::to_string(entity->GetChildren().size()), ")"));
            //TODO select this object
        }
        ImGui::EndPopup();
    }
    ImGui::PopID();
    if (nodeOpen)
    {
        for (const auto child : children)
        {
            UpdateHierarchyTree(child);
        }
        ImGui::TreePop();
    }
}
