#include "MeshImporter.h"
#include <Globals.h>

#include <yaml-cpp/yaml.h>

#include "core/file system/FileManager.h"
#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

void MeshImporter::ImportAsset(const std::filesystem::path& mesh_path)
{
    BE_LOG("Loading Module: %s", mesh_path);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(mesh_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        BE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }

    if (scene->HasMeshes())
    {
        // This only import one mesh.
        // For multiple imports consider use SceneImporter
        ImportMesh(scene->mMeshes[0], UUID::GenerateUUIDv4());
    }
}

void MeshImporter::ImportMesh(aiMesh* mesh, const std::string& mesh_uid)
{
    YAML::Node yaml_node;
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));

    yaml_node["min_point"]["x"] = mesh->mVertices[0].x;
    yaml_node["min_point"]["y"] = mesh->mVertices[0].y;
    yaml_node["min_point"]["z"] = mesh->mVertices[0].z;

    yaml_node["max_point"]["x"] = mesh->mVertices[0].x;
    yaml_node["max_point"]["y"] = mesh->mVertices[0].y;
    yaml_node["max_point"]["z"] = mesh->mVertices[0].z;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        yaml_node["vertices"][i]["x"] = mesh->mVertices[i].x;
        yaml_node["vertices"][i]["y"] = mesh->mVertices[i].y;
        yaml_node["vertices"][i]["z"] = mesh->mVertices[i].z;

        yaml_node["normals"][i]["x"] = mesh->mNormals[i].x;
        yaml_node["normals"][i]["y"] = mesh->mNormals[i].y;
        yaml_node["normals"][i]["z"] = mesh->mNormals[i].z;

        if (mesh->HasTextureCoords(0)) // TODO: What does 0 means
        {
            yaml_node["texture_coords"][i]["x"] = mesh->mTextureCoords[0][i].x;
            yaml_node["texture_coords"][i]["y"] = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            yaml_node["texture_coords"][i]["x"] = 0.0;
            yaml_node["texture_coords"][i]["y"] = 0.0;
        }

        yaml_node["min_point"]["x"] = std::min(mesh->mVertices[i].x, yaml_node["min_point"]["x"].as<float>());
        yaml_node["min_point"]["y"] = std::min(mesh->mVertices[i].y, yaml_node["min_point"]["y"].as<float>());
        yaml_node["min_point"]["z"] = std::min(mesh->mVertices[i].z, yaml_node["min_point"]["z"].as<float>());

        yaml_node["max_point"]["x"] = std::max(mesh->mVertices[i].x, yaml_node["max_point"]["x"].as<float>());
        yaml_node["max_point"]["y"] = std::max(mesh->mVertices[i].y, yaml_node["max_point"]["y"].as<float>());
        yaml_node["max_point"]["z"] = std::max(mesh->mVertices[i].z, yaml_node["max_point"]["z"].as<float>());
       
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            yaml_node["indices"][i]["face#, %d", i][j] = face.mIndices[j];
        }
    }
    std::string mesh_name(preferences->GetLibraryPath(ResourceType::MESH) + mesh_uid);
    std::ofstream fout(mesh_name);
    fout << yaml_node;
}