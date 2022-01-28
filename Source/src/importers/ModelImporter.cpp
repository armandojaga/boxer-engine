
#include "ModelImporter.h"
#include "MeshImporter.h"
#include "Application.h"

#include <Globals.h>
#include <yaml-cpp/yaml.h>
#include <fstream>

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

void ModelImporter::ImportAsset(const std::filesystem::path& model_path)
{
    BE_LOG("Entering ModelImporter: %s", model_path);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(model_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        BE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }

    YAML::Node model_ticket;
    ImportModel(scene->mRootNode, scene, model_ticket);
    SaveToFile(model_ticket, UUID::GenerateUUIDv4());
}

void ModelImporter::ImportModel(aiNode* node, const aiScene* scene, YAML::Node& ticket)
{
    MeshImporter mesh_importer;

    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        const std::string mesh_uuid = UUID::GenerateUUIDv4();
        ticket["mesh"][i]["id"] = mesh_uuid;
        mesh_importer.ImportMesh(mesh, mesh_uuid);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        YAML::Node yNode = ticket[i];
        ImportModel(node->mChildren[i], scene, yNode);
    }
}

void BoxerEngine::ModelImporter::SaveToFile(YAML::Node& ticket, const std::string& uuid)
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    std::string model_name(preferences->GetLibraryPath(ResourceType::MODEL) + uuid);
    std::ofstream fout(model_name);
    fout << ticket;
}
