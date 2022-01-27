#include "core/bepch.h"
#include "InspectorPanel.h"

#include "components/LightComponent.h"
#include "components/CameraComponent.h"
#include "core/events/Event.h"
#include "core/events/EventManager.h"
#include "modules/ModuleEditor.h"
#include "modules/ModuleScene.h"

#define ADD_COMPONENT(CType, name)                 \
if (!currentEntity->Has<CType>())                  \
    if (ImGui::MenuItem(name))                     \
        currentEntity->CreateComponent<CType>();

BoxerEngine::InspectorPanel::InspectorPanel(): Panel("Inspector", true)
{
    std::function setNewActiveEntity = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<SelectionChangedEventPayload>();
        BE_LOG("Setting new active item for inspector: %s", e.GetSelected()->GetName().c_str());
        currentEntity = e.GetSelected();
    };
    EventManager::GetInstance().Subscribe(Event::Type::SELECTION_CHANGED, setNewActiveEntity);
}

void BoxerEngine::InspectorPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(200, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(StringUtils::Concat(ICON_MD_INFO, GetTitle()).c_str(), &visible) || !currentEntity || currentEntity == App->scene->GetScene()->GetRoot())
    {
        ImGui::End();
        return;
    }


    bool enabled = currentEntity->IsEnabled();
    if (ImGui::Checkbox("###enabled", &enabled))
    {
        if (enabled)
        {
            currentEntity->Enable();
        }
        else
        {
            currentEntity->Disable();
        }
    }
    ImGui::SameLine();
    std::string buffer = currentEntity->GetName();
    ImGui::SameLine();
    if (ImGui::InputText("###rename", &buffer, ImGuiInputTextFlags_AutoSelectAll))
    {
        currentEntity->SetName(buffer);
    }
    ImGui::Separator();
    for (const auto component : currentEntity->GetComponents())
    {
        const bool nodeOpen = ImGui::TreeNodeEx(component->GetName(),
                                                ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick |
                                                ImGuiTreeNodeFlags_DefaultOpen | ImGuiTreeNodeFlags_Selected);
        if (component->GetType() != Component::Type::TRANSFORM) //can not remove the transform
        {
            ImGui::SameLine();
            if (ImGui::Button("?"))
            {
                ImGui::OpenPopup("RemoveComponentMenu");
            }
            if (ImGui::BeginPopup("RemoveComponentMenu"))
            {
                if (ImGui::MenuItem("Remove"))
                {
                    currentEntity->RemoveComponent(component->GetId());
                }
                ImGui::EndPopup();
            }
        }

        if (nodeOpen)
        {
            component->UpdateUI();
            ImGui::TreePop();
        }
    }
    ImGui::Separator();
    if (ImGui::Button("Add component", ImVec2(ImGui::GetContentRegionAvailWidth(), 0.0f)))
    {
        ImGui::OpenPopup("AddComponentMenu");
    }
    if (ImGui::BeginPopup("AddComponentMenu"))
    {
        ADD_COMPONENT(LightComponent, "Light");
        ADD_COMPONENT(CameraComponent, "Camera");

        ImGui::EndPopup();
    }

    ImGui::End();
}
