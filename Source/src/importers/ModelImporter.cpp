
#include "ModelImporter.h"
#include "MeshImporter.h"
#include "TextureImporter.h"
#include "Application.h"

#include <Globals.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <filesystem>

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

void ModelImporter::ImportAsset(const std::filesystem::path& model_path)
{
    BE_LOG("Entering ModelImporter: %s", model_path);
    Assimp::Importer import;
    const aiScene* scene = nullptr;

    scene = import.ReadFile(model_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        BE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }

    YAML::Node model_ticket;
    model_ticket["id"] = UUID::GenerateUUIDv4();
    model_ticket["file_path"] = model_path.string();
    std::string file_name = model_path.filename().replace_extension().string();

    ImportModel(scene, model_ticket);
    SaveToFile(model_ticket, file_name);
}

void ModelImporter::ImportModel(const aiScene* scene, YAML::Node& ticket)
{
    MeshImporter mesh_importer;
    std::string mesh_uuid;

    for (unsigned int i = 0; i < scene->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[i];
        mesh_uuid = UUID::GenerateUUIDv4();
        ticket["mesh"][i]["id"] = mesh_uuid;
        mesh_importer.ImportMesh(mesh, mesh_uuid);
    }
}

void BoxerEngine::ModelImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    std::string model_name(preferences->GetLibraryPath(ResourceType::MODEL) + file_name);
    std::ofstream fout(model_name);
    fout << ticket;
}
