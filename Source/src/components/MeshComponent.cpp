#include "core/bepch.h"
#include "MeshComponent.h"
#include "modules/ModuleTexture.h"
#include "Application.h"

#include "core/util/Files.h"
#include "core/util/StringUtils.h"
#include "ImGuiFileDialog.h"
#include "TransformComponent.h"
#include "modules/ModuleProgram.h"

static const char* types[]{"Diffuse", "Specular"};

BoxerEngine::MeshComponent::MeshComponent(Entity* entity)
    : Component(Type::MESH, entity)
{
}

BoxerEngine::MeshComponent::~MeshComponent()
{
    for (const auto mesh : meshes)
    {
        delete mesh;
    }
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

    App->program->SetUniform("model", GetEntity()->GetComponent<TransformComponent>()->GetGlobalMatrix());
    Model->Draw();
}

void BoxerEngine::MeshComponent::DisplayLoadedUI()
{
    ImGui::TextWrapped("Meshes");
    ImGui::Separator();

    for (int i = 0; i < Model->GetMeshesCount(); ++i)
    {
        ImGui::TextWrapped(StringUtils::Concat(ICON_MD_ARROW_FORWARD_IOS, " ", std::to_string(i), " Mesh:").c_str());

        if (!meshes[i]->texture_loaded)
        {
            AddTextureDisplay(i);
        }
    }
}

void BoxerEngine::MeshComponent::DisplayNotLoadedUI()
{
    if (ImGui::Button("Browse"))
    {
        ImGuiFileDialog::Instance()->OpenDialog("Select Mesh", "Select Mesh", ".*", "./library/models/", 1, nullptr,
                                                ImGuiFileDialogFlags_DontShowHiddenFiles |
                                                ImGuiFileDialogFlags_HideColumnType |
                                                ImGuiFileDialogFlags_DisableCreateDirectoryButton |
                                                ImGuiFileDialogFlags_HideColumnDate);
    }

    if (ImGuiFileDialog::Instance()->Display("Select Mesh"))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            const std::filesystem::path file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            // TODO: If filepath is not asset. Import mesh

            Model = new BoxerEngine::Model(file_path.filename().replace_extension().string().c_str());
            model_loaded = true;

            meshes.reserve(Model->GetMeshesCount());
            for (int i = 0; i < Model->GetMeshesCount(); ++i)
            {
                meshes.emplace_back(new MeshData());
            }
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void BoxerEngine::MeshComponent::AddTextureDisplay(const int meshIndex)
{
    const std::string title = StringUtils::Concat("Select texture##%d", std::to_string(meshIndex));

    ImGui::TextWrapped(ICON_MD_IMAGE_SEARCH);
    ImGui::SameLine();
    if (ImGui::Button(StringUtils::Concat(std::to_string(meshIndex).c_str(), " Mesh").c_str()))
    {
        ImGuiFileDialog::Instance()->OpenDialog(title.c_str(), "Select Texture", ".*", "./library/textures/", 1, nullptr,
                                                ImGuiFileDialogFlags_DontShowHiddenFiles |
                                                ImGuiFileDialogFlags_DisableCreateDirectoryButton |
                                                ImGuiFileDialogFlags_HideColumnType |
                                                ImGuiFileDialogFlags_HideColumnDate);
    }

    ImGui::PushID(meshIndex);
    const int index = TexturesTypesListBox();
    ImGui::PopID();

    if (ImGuiFileDialog::Instance()->Display(title.c_str()))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            const std::filesystem::path texturePath = ImGuiFileDialog::Instance()->GetFilePathName();
            const unsigned int textureId = App->textures->Load(texturePath.filename().string().c_str());
            Model->SetMeshTexture(meshIndex, textureId, types[index]);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

int BoxerEngine::MeshComponent::TexturesTypesListBox()
{
    static int selection;
    ImGui::Combo("", &selection, types, IM_ARRAYSIZE(types));

    return selection;
}
