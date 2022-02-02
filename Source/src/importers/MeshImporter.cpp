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
    ticket[MESH_ID] = uuid;
    PopulateTicket(mesh, ticket);
    SaveToFile(ticket, uuid);
}

void MeshImporter::PopulateTicket(aiMesh* mesh, YAML::Node& mesh_ticket)
{
    mesh_ticket[MIN_POINT][NODE_X] = mesh->mVertices[0].x;
    mesh_ticket[MIN_POINT][NODE_Y] = mesh->mVertices[0].y;
    mesh_ticket[MIN_POINT][NODE_Z] = mesh->mVertices[0].z;

    mesh_ticket[MAX_POINT][NODE_X] = mesh->mVertices[0].x;
    mesh_ticket[MAX_POINT][NODE_Y] = mesh->mVertices[0].y;
    mesh_ticket[MAX_POINT][NODE_Z] = mesh->mVertices[0].z;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        mesh_ticket[VERTICES_NODE][i][NODE_X] = mesh->mVertices[i].x;
        mesh_ticket[VERTICES_NODE][i][NODE_Y] = mesh->mVertices[i].y;
        mesh_ticket[VERTICES_NODE][i][NODE_Z] = mesh->mVertices[i].z;

        mesh_ticket[NORMALS_NODE][i][NODE_X] = mesh->mNormals[i].x;
        mesh_ticket[NORMALS_NODE][i][NODE_Y] = mesh->mNormals[i].y;
        mesh_ticket[NORMALS_NODE][i][NODE_Z] = mesh->mNormals[i].z;

        if (mesh->HasTextureCoords(0)) // TODO: What does 0 means
        {
            mesh_ticket[TEXTURE_COORDS_NODE][i][NODE_X] = mesh->mTextureCoords[0][i].x;
            mesh_ticket[TEXTURE_COORDS_NODE][i][NODE_Y] = mesh->mTextureCoords[0][i].y;
        }
        else
        {
            mesh_ticket[TEXTURE_COORDS_NODE][i][NODE_X] = 0.0;
            mesh_ticket[TEXTURE_COORDS_NODE][i][NODE_Y] = 0.0;
        }

        mesh_ticket[MIN_POINT][NODE_X] = std::min(mesh->mVertices[i].x, mesh_ticket[MIN_POINT][NODE_X].as<float>());
        mesh_ticket[MIN_POINT][NODE_Y] = std::min(mesh->mVertices[i].y, mesh_ticket[MIN_POINT][NODE_Y].as<float>());
        mesh_ticket[MIN_POINT][NODE_Z] = std::min(mesh->mVertices[i].z, mesh_ticket[MIN_POINT][NODE_Z].as<float>());

        mesh_ticket[MAX_POINT][NODE_X] = std::max(mesh->mVertices[i].x, mesh_ticket[MAX_POINT][NODE_X].as<float>());
        mesh_ticket[MAX_POINT][NODE_Y] = std::max(mesh->mVertices[i].y, mesh_ticket[MAX_POINT][NODE_Y].as<float>());
        mesh_ticket[MAX_POINT][NODE_Z] = std::max(mesh->mVertices[i].z, mesh_ticket[MAX_POINT][NODE_Z].as<float>());
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            mesh_ticket[INDICES_NODE][i][j] = face.mIndices[j];
        }
    }
}
