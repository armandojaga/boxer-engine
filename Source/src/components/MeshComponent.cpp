#include "core/bepch.h"
#include "MeshComponent.h"
#include "modules/ModuleTexture.h"

#include "ImGuiFileDialog.h"
#include "TransformComponent.h"
#include "modules/ModuleProgram.h"

static const char* texture_types[]{"Diffuse", "Specular"};

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
    delete model;
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

const char* BoxerEngine::MeshComponent::GetModelPath() const
{
    if (!model_loaded)
    {
        return nullptr;
    }

    return model->GetPath();
}

void BoxerEngine::MeshComponent::LoadModel(const char* path)
{
    if (model)
    {
        delete model;
    }

    std::filesystem::path model_path(path);
    model_path = model_path.filename().replace_extension();

    model = new Model(model_path.string().c_str());
    meshes.reserve(model->GetMeshesCount());
    for (int i = 0; i < model->GetMeshesCount(); ++i)
    {
        meshes.emplace_back(new MeshData());
    }
    model_loaded = true;
}

void BoxerEngine::MeshComponent::LoadTexture(const char* path, int mesh_index, int type)
{
    const unsigned int textureId = App->textures->Load(path);
    model->SetMeshTexture(mesh_index, textureId, texture_types[type]);
    meshes[mesh_index]->texture_loaded = true;
    meshes[mesh_index]->texture_name = path;
    meshes[mesh_index]->texture_type = type;
}

void BoxerEngine::MeshComponent::Draw()
{
    if (!model_loaded || !enabled)
    {
        return;
    }

    App->program->SetUniform("model", GetEntity()->GetComponent<TransformComponent>()->GetGlobalMatrix());
    model->Draw();
}

void BoxerEngine::MeshComponent::DisplayLoadedUI()
{
    ImGui::TextWrapped("Meshes");
    ImGui::Separator();

    for (int i = 0; i < model->GetMeshesCount(); ++i)
    {
        ImGui::TextWrapped(StringUtils::Concat(ICON_MD_ARROW_FORWARD_IOS, " ", std::to_string(i), " Mesh:").c_str());
        AddTextureDisplay(i);
        ImGui::NewLine();
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
            // TODO: If filepath is not asset. Import mesh
            const std::filesystem::path file_path = ImGuiFileDialog::Instance()->GetFilePathName();
            LoadModel(file_path.filename().replace_extension().string().c_str());
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

void BoxerEngine::MeshComponent::AddTextureDisplay(const int mesh_index)
{
    const std::string title = StringUtils::Concat("Select texture##%d", std::to_string(mesh_index));

    ImGui::PushID(mesh_index);
    const int index = TexturesTypesListBox();
    ImGui::PopID();

    ImGui::Text(ICON_MD_IMAGE_SEARCH);
    ImGui::SameLine();
    if (ImGui::Button(StringUtils::Concat(std::to_string(mesh_index).c_str(), " Texture").c_str()))
    {
        ImGuiFileDialog::Instance()->OpenDialog(title.c_str(), "Select Texture", ".*", "./library/textures/", 1, nullptr,
                                                ImGuiFileDialogFlags_DontShowHiddenFiles |
                                                ImGuiFileDialogFlags_DisableCreateDirectoryButton |
                                                ImGuiFileDialogFlags_HideColumnType |
                                                ImGuiFileDialogFlags_HideColumnDate);
    }
    ImGui::SameLine();
    if (meshes[mesh_index]->texture_loaded && ImGui::Button(ICON_MD_HIGHLIGHT_REMOVE))
    {
        model->SetMeshTexture(mesh_index, 0, texture_types[0]);
        meshes[mesh_index]->texture_loaded = false;
    }

    if (ImGuiFileDialog::Instance()->Display(title.c_str()))
    {
        if (ImGuiFileDialog::Instance()->IsOk())
        {
            const std::filesystem::path texture_path = ImGuiFileDialog::Instance()->GetFilePathName().c_str();
            LoadTexture(texture_path.filename().replace_extension().string().c_str(), mesh_index, index);
        }

        ImGuiFileDialog::Instance()->Close();
    }
}

int BoxerEngine::MeshComponent::TexturesTypesListBox()
{
    static int selection;
    ImGui::Combo("", &selection, texture_types, IM_ARRAYSIZE(texture_types));

    return selection;
}
