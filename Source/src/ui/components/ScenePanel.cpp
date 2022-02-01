#include "core/bepch.h"
#include "ScenePanel.h"

#include "components/TransformComponent.h"
#include "core/events/Event.h"
#include "core/events/EventManager.h"
#include "modules/ModuleCamera.h"
#include "modules/ModuleInput.h"
#include "modules/ModuleRender.h"

BoxerEngine::ScenePanel::ScenePanel() : Panel("Scene", true)
{
    std::function setActiveEntity = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<SelectionChangedEventPayload>();
        active_entity = e.GetSelected();
    };
    EventManager::GetInstance().Subscribe(Event::Type::SELECTION_CHANGED, setActiveEntity);
}

void BoxerEngine::ScenePanel::UpdateGizmoType()
{
    //TODO move to event?
    if (App->input->IsKeyPressed(SDL_SCANCODE_Q))
    {
        guizmo_operation = -1;
    }
    if (App->input->IsKeyPressed(SDL_SCANCODE_W))
    {
        guizmo_operation = ImGuizmo::OPERATION::TRANSLATE;
    }
    if (App->input->IsKeyPressed(SDL_SCANCODE_E))
    {
        guizmo_operation = ImGuizmo::OPERATION::ROTATE;
    }
    if (App->input->IsKeyPressed(SDL_SCANCODE_R))
    {
        guizmo_operation = ImGuizmo::OPERATION::SCALE;
    }
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

    UpdateGizmoType();

    //guizmos
    if (active_entity && guizmo_operation != -1 && active_entity->GetComponent<TransformComponent>())
    {
        FrameBuffer* frameBuffer = App->renderer->GetFrameBuffer();
        ImGuizmo::SetOrthographic(false);
        ImGuizmo::SetDrawlist();
        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, static_cast<float>(frameBuffer->GetWidth()), static_cast<float>(frameBuffer->GetHeight()));

        float4x4 delta = float4x4::identity;

        Frustum engineFrustum = App->camera->GetCameraFrustum();
        float4x4 cameraView = float4x4(engineFrustum.ViewMatrix()).Transposed();
        float4x4 cameraProjection = engineFrustum.ProjectionMatrix().Transposed();

        auto tc = active_entity->GetComponent<TransformComponent>();
        auto trans = tc->GetGlobalMatrix().Transposed();

        // Snapping
        bool snap = App->input->IsModKeyPressed(KMOD_LCTRL);
        float snapValue = 1.0f;
        if (guizmo_operation == ImGuizmo::OPERATION::ROTATE)
        {
            snapValue = 15.0f;
        }

        float snapValues[3] = {snapValue, snapValue, snapValue};

        // ImGuizmo::DrawGrid(cameraView.ptr(), cameraProjection.ptr(), float4x4::identity.ptr(), 10.f);

        Manipulate(cameraView.ptr(), cameraProjection.ptr(),
                   static_cast<ImGuizmo::OPERATION>(guizmo_operation), ImGuizmo::LOCAL, trans.ptr(), delta.ptr(), snap ? snapValues : nullptr);

        // auto viewManipulateRight = ImGui::GetWindowPos().x + ImGui::GetWindowWidth();
        // auto viewManipulateTop = ImGui::GetWindowPos().y;
        // ImGuizmo::ViewManipulate(cameraView.ptr(), 6.0, ImVec2(viewManipulateRight - 128, viewManipulateTop), ImVec2(128, 128), 0x10101010);

        if (ImGuizmo::IsUsing() && !delta.IsIdentity())
        {
            Entity* parent = active_entity->GetParent();
            float4x4 inverseParentMatrix = float4x4::identity;
            if (parent != nullptr && parent != App->scene->GetScene()->GetRoot())
            {
                TransformComponent* parentTransform = parent->GetComponent<TransformComponent>();
                inverseParentMatrix = parentTransform->GetGlobalMatrix().Inverted();
            }
            float4x4 localMatrix = inverseParentMatrix * trans.Transposed();

            float3 position = float3::zero;
            Quat rotation = Quat::identity;
            float3 scale = float3::one;

            localMatrix.Decompose(position, rotation, scale);

            switch (guizmo_operation)
            {
            case ImGuizmo::TRANSLATE:
                tc->SetPosition(position);
                break;
            case ImGuizmo::ROTATE:
                tc->SetRotation(rotation);
                break;
            case ImGuizmo::SCALE:
                tc->SetScale(scale);
                break;
            }
        }
    }

    ImGui::End();
    ImGui::PopStyleVar();
}
