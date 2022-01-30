#include "core/bepch.h"
#include "MeshComponent.h"
#include "modules/ModuleTexture.h"
#include "Application.h"

#include "../vendors/ImGuiFileDialog/ImGuiFileDialog.h"
#include "core/util/Files.h"

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
    if (loaded)
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
    if (!loaded || !enabled)
    {
        return;
    }

    Model->Draw();
}

void BoxerEngine::MeshComponent::DisplayLoadedUI()
{
    if (ImGui::Button("Add Texture"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("Select Texture", "Select Texture", ".png, .tif", "./assets/textures/", 1, nullptr,
            ImGuiFileDialogFlags_DontShowHiddenFiles |
            ImGuiFileDialogFlags_DisableCreateDirectoryButton |
            ImGuiFileDialogFlags_HideColumnDate |
            ImGuiWindowFlags_NoNav);
    }

    if (ImGuiFileDialog::Instance()->Display("Select Texture"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            unsigned int texture_id = App->textures->Load(file_path.filename().string().c_str());
            Model->SetMeshTexture("", texture_id, "texture_diffuse");
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void BoxerEngine::MeshComponent::DisplayNotLoadedUI()
{
    if (ImGui::Button("Browse"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("Select Mesh", "Select Mesh", ".fbx", "./assets/models/", 1, nullptr,
            ImGuiFileDialogFlags_DontShowHiddenFiles |
            ImGuiFileDialogFlags_DisableCreateDirectoryButton |
            ImGuiFileDialogFlags_HideColumnDate |
            ImGuiWindowFlags_NoNav);
    }

    if (ImGuiFileDialog::Instance()->Display("Select Mesh"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            std::filesystem::path file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            // TODO: If filepath is not asset. Import mesh

            Model = new BoxerEngine::Model(file_path.filename().replace_extension().string().c_str());
            loaded = true;
        }

        ImGuiFileDialog::Instance()->Close();
    }
}
