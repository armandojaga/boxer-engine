#include "core/bepch.h"
#include "HierarchyPanel.h"

#include "modules/ModuleEditor.h"
#include "modules/ModuleScene.h"

BoxerEngine::HierarchyPanel::HierarchyPanel() : Panel("Hierarchy", true)
{
}

void BoxerEngine::HierarchyPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(300, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(StringUtils::Concat(ICON_MD_SOURCE, GetTitle()).c_str(), &visible))
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
void BoxerEngine::HierarchyPanel::UpdateHierarchyTree(Entity* entity)
{
    const auto children = entity->GetChildren();
    constexpr ImGuiTreeNodeFlags baseFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
    ImGuiTreeNodeFlags nodeFlags = baseFlags;

    if (entity == App->scene->GetScene()->GetRoot())
    {
        nodeFlags |= ImGuiTreeNodeFlags_DefaultOpen;
    }
    if (activeEntity == entity)
    {
        nodeFlags |= ImGuiTreeNodeFlags_Selected;
    }
    if (children.empty())
    {
        nodeFlags |= ImGuiTreeNodeFlags_Leaf;
    }
    const std::string icon = entity == App->scene->GetScene()->GetRoot() ? ICON_MD_TOKEN : ICON_MD_HEXAGON;
    const bool nodeOpen = ImGui::TreeNodeEx(StringUtils::Concat(icon, entity->GetName()).c_str(), nodeFlags);

    if (ImGui::IsItemClicked())
    {
        App->editor->SetActiveEntity(entity);
        activeEntity = entity;
    }

    ImGui::PushID(entity);
    if (ImGui::BeginPopupContextItem(entity->GetName().c_str()))
    {
        if (ImGui::Selectable("Create Empty"))
        {
            auto e = App->scene->CreateEmptyEntity();
            e->SetParent(entity);
            e->SetName(StringUtils::Concat("New Entity (", std::to_string(entity->GetChildren().size()), ")"));
            App->editor->SetActiveEntity(e);
            activeEntity = e;
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
