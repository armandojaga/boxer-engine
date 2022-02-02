#include "core/bepch.h"

#include "Model.h"

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

Model::Model(const char* modelName)
{
    Load(modelName);
}

void Model::Load(const char* modelName)
{
    BE_LOG("Loading Model: %s", modelName);

    auto preferences =
        static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    std::string meshes_library_path(preferences->GetLibraryPath(ResourceType::MESH));
    std::string models_library_path(preferences->GetLibraryPath(ResourceType::MODEL));

    models_library_path.append(modelName);
    if (!Files::IsValidFilePath(models_library_path))
    {
        return;
    }

    YAML::Node model_data = YAML::LoadFile(models_library_path);

    for (auto it = model_data.begin(); it != model_data.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal(MODEL_ID))
        {
            id = std::move(it->second.as<std::string>());
        }

        if (it->first.as<std::string>()._Equal(MODEL_FILE_PATH))
        {
            path = std::move(it->second.as<std::string>());
        }
    }

    std::string meshes_path = preferences->GetLibraryPath(ResourceType::MESH);

    for (int i = 0; i < model_data[MESH_NODE].size(); ++i)
    {
        std::string mesh_id = std::move(model_data[MODEL_MESH_NODE][i][MODEL_MESH_ID].as<std::string>());
        mesh_id.insert(0, meshes_path);
        meshes.emplace_back(new Mesh(mesh_id.c_str()));
    }
}

Model::~Model()
{
    for (const auto mesh : meshes)
    {
        delete mesh;
    }
}

void Model::Draw() const
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i]->Draw();
    }
}

void Model::SetTransform()
{
}

void Model::SetMeshTexture(const int meshIndex, const int textureId, const char* textureType)
{
    meshes[meshIndex]->SetTexture(textureId, textureType);
}
