#include "core/bepch.h"
#include "MeshComponent.h"
#include "modules/ModuleTexture.h"
#include "Application.h"

#include "../vendors/ImGuiFileDialog/ImGuiFileDialog.h"
#include "core/util/Files.h"
#include "core/util/StringUtils.h"

BoxerEngine::MeshComponent::MeshComponent(Entity* parent)
	: Component(Component::Type::MESH, parent)
{
}

BoxerEngine::MeshComponent::~MeshComponent()
{
    delete Model;
}

void BoxerEngine::MeshComponent::UpdateUI()
{
    if (model_loaded)
    {
        DisplayLoadedUI();
    }
    else
    {
        DisplayNotLoadedUI();
    }
}

void BoxerEngine::MeshComponent::Update()
{
}

const char* BoxerEngine::MeshComponent::GetName() const
{
	return "Mesh";
}

void BoxerEngine::MeshComponent::Draw()
{
    if (!model_loaded || !enabled)
    {
        return;
    }

    Model->Draw();
}

void BoxerEngine::MeshComponent::DisplayLoadedUI()
{
    ImGui::TextWrapped("Meshes");
    ImGui::Separator();
    
    for (int i = 0; i <  Model->GetMeshesCount(); ++i)
    {
        ImGui::TextWrapped(BoxerEngine::StringUtils::Concat(ICON_MD_ARROW_FORWARD_IOS," ", std::to_string(i), ":").c_str());

        if (!texture_loaded)
        {
            AddTextureDisplay();
        }
    }
}

void BoxerEngine::MeshComponent::DisplayNotLoadedUI()
{
    if (ImGui::Button("Browse"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("Select Mesh", "Select Mesh", ".*", "./library/models/", 1, nullptr,
            ImGuiFileDialogFlags_DontShowHiddenFiles |
            ImGuiFileDialogFlags_DisableCreateDirectoryButton |
            ImGuiFileDialogFlags_HideColumnDate);
    }

    if (ImGuiFileDialog::Instance()->Display("Select Mesh"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            // TODO: If filepath is not asset. Import mesh

            Model = new BoxerEngine::Model(file_path.filename().replace_extension().string().c_str());
            model_loaded = true;
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void BoxerEngine::MeshComponent::AddTextureDisplay()
{
    if (ImGui::Button("Add Texture"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("Select Texture", "Select Texture", ".*", "./library/textures/", 1, nullptr,
            ImGuiFileDialogFlags_DontShowHiddenFiles |
            ImGuiFileDialogFlags_DisableCreateDirectoryButton |
            ImGuiFileDialogFlags_HideColumnDate);
    }

    if (ImGuiFileDialog::Instance()->Display("Select Texture"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path texture_path = ImGuiFileDialog::Instance()->GetFilePathName();
            unsigned int texture_id = App->textures->Load(texture_path.filename().string().c_str());
            Model->SetMeshTexture("", texture_id, "texture_diffuse");
            texture_loaded = true;
        }

        ImGuiFileDialog::Instance()->Close();
    }
}
