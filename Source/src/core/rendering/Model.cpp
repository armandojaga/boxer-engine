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

    const auto preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    std::string meshesLibraryPath(preferences->GetLibraryPath(ResourceType::MESH));
    std::string modelsLibraryPath(preferences->GetLibraryPath(ResourceType::MODEL));

    modelsLibraryPath.append(modelName);
    if (!Files::IsValidFilePath(modelsLibraryPath))
    {
        return;
    }

    YAML::Node modelData = YAML::LoadFile(modelsLibraryPath);

    for (auto it = modelData.begin(); it != modelData.end(); ++it)
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

    const std::string meshesPath = preferences->GetLibraryPath(ResourceType::MESH);

    for (int i = 0; i < modelData[MESH_NODE].size(); ++i)
    {
        std::string meshId = std::move(modelData[MODEL_MESH_NODE][i][MODEL_MESH_ID].as<std::string>());
        meshId.insert(0, meshesPath);
        meshes.emplace_back(new Mesh(meshId.c_str()));
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
