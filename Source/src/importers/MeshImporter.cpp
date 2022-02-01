#include "core/bepch.h"

#include "MeshImporter.h"

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

MeshImporter::MeshImporter()
    : Importer(Type::MESH)
{
}

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

    // Loads one mesh
    // For multiple ones, consider using ModelImport
    ImportMesh(scene->mMeshes[0], UUID::GenerateUUIDv4());
}

void MeshImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    std::string mesh_name(preferences->GetLibraryPath(ResourceType::MESH) + file_name);
    std::ofstream fout(mesh_name);
    fout << ticket;
}

void MeshImporter::ImportMesh(aiMesh* mesh, const std::string& uuid)
{
    YAML::Node ticket;
    ticket["mesh_id"] = uuid;
    PopulateTicket(mesh, ticket);
    SaveToFile(ticket, uuid);
}

void MeshImporter::PopulateTicket(aiMesh* mesh, YAML::Node& mesh_ticket)
{
    mesh_ticket["min_point"]["x"] = mesh->mVertices[0].x;
    mesh_ticket["min_point"]["y"] = mesh->mVertices[0].y;
    mesh_ticket["min_point"]["z"] = mesh->mVertices[0].z;

    mesh_ticket["max_point"]["x"] = mesh->mVertices[0].x;
    mesh_ticket["max_point"]["y"] = mesh->mVertices[0].y;
    mesh_ticket["max_point"]["z"] = mesh->mVertices[0].z;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        mesh_ticket["vertices"][i]["x"] = mesh->mVertices[i].x;
        mesh_ticket["vertices"][i]["y"] = mesh->mVertices[i].y;
        mesh_ticket["vertices"][i]["z"] = mesh->mVertices[i].z;

        mesh_ticket["normals"][i]["x"] = mesh->mNormals[i].x;
        mesh_ticket["normals"][i]["y"] = mesh->mNormals[i].y;
        mesh_ticket["normals"][i]["z"] = mesh->mNormals[i].z;

        if (mesh->HasTextureCoords(0)) // TODO: What does 0 means
        {
            mesh_ticket["texture_coords"][i]["x"] = mesh->mTextureCoords[0][i].x;
            mesh_ticket["texture_coords"][i]["y"] = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh_ticket["texture_coords"][i]["x"] = 0.0;
            mesh_ticket["texture_coords"][i]["y"] = 0.0;
        }

        mesh_ticket["min_point"]["x"] = std::min(mesh->mVertices[i].x, mesh_ticket["min_point"]["x"].as<float>());
        mesh_ticket["min_point"]["y"] = std::min(mesh->mVertices[i].y, mesh_ticket["min_point"]["y"].as<float>());
        mesh_ticket["min_point"]["z"] = std::min(mesh->mVertices[i].z, mesh_ticket["min_point"]["z"].as<float>());

        mesh_ticket["max_point"]["x"] = std::max(mesh->mVertices[i].x, mesh_ticket["max_point"]["x"].as<float>());
        mesh_ticket["max_point"]["y"] = std::max(mesh->mVertices[i].y, mesh_ticket["max_point"]["y"].as<float>());
        mesh_ticket["max_point"]["z"] = std::max(mesh->mVertices[i].z, mesh_ticket["max_point"]["z"].as<float>());
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            mesh_ticket["indices"][i][j] = face.mIndices[j];
        }
    }
}
