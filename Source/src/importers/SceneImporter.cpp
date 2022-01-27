
#include "SceneImporter.h"
#include "MeshImporter.h"

using namespace BoxerEngine;

void SceneImporter::ImportAsset(const std::filesystem::path& scene_path)
{
    BE_LOG("Loading Module: %s", scene_path);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(scene_path.string(), aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        BE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }

    BE_LOG("Scene Summary");
    BE_LOG("Meshes: %d", scene->mNumMeshes);
    BE_LOG("Materials: %d", scene->mNumMaterials);
    BE_LOG("Textures: %d", scene->mNumTextures);
    BE_LOG("Cameras: %d", scene->mNumCameras);
    BE_LOG("Animations: %d", scene->mNumAnimations);
    BE_LOG("Lights: %d", scene->mNumLights);

    ProcessRoot(scene->mRootNode, scene);
}

void SceneImporter::ProcessRoot(aiNode* node, const aiScene* scene)
{
    MeshImporter mesh_importer;
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        mesh_importer.ImportMesh(mesh);
    }

    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessRoot(node->mChildren[i], scene);
    }
}
