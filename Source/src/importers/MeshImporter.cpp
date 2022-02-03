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
    float3 minValue(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);
    float3 maxValue(minValue);

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        mesh_ticket[VERTICES_NODE][i] = mesh->mVertices[i];

        mesh_ticket[NORMALS_NODE][i] = mesh->mNormals[i];

        YAML::Node textureCoords(float2(0.0f));

        if (mesh->HasTextureCoords(0))
        {
            mesh_ticket[TEXTURE_COORDS_NODE][i] = float2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
        }

        float3 current(mesh->mVertices[0].x, mesh->mVertices[0].y, mesh->mVertices[0].z);

        minValue = Min(minValue, current);
        maxValue = Max(maxValue, current);

        mesh_ticket[MIN_POINT] = minValue;
        mesh_ticket[MAX_POINT] = maxValue;
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        const aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j += 3)
        {
            mesh_ticket[INDICES_NODE][i] = float3(face.mIndices[j], face.mIndices[j + 1], face.mIndices[j + 2]);
        }
    }
}
