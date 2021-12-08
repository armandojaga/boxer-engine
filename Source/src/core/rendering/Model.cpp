#include "Model.h"

#include "Application.h"
#include "Globals.h"
#include "Mesh.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "modules/ModuleTexture.h"

BoxerEngine::Model::Model() = default;

BoxerEngine::Model::~Model()
{
}

void BoxerEngine::Model::Load(const char* path)
{
    const aiScene* scene = aiImportFile(path, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene)
    {
        BE_LOG("Loaded model from %s", path);
        LoadMaterials(scene, path);
        LoadMeshes(scene);
    }
    else
    {
        BE_LOG("Error loading %s: %s", path, aiGetErrorString());
    }
}

void BoxerEngine::Model::LoadMaterials(const aiScene* scene, const char* path)
{
    aiString file;
    materials.reserve(scene->mNumMaterials);
    for (unsigned i = 0; i < scene->mNumMaterials; ++i)
    {
        if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
        {
            if (const unsigned int textureId = App->textures->Load(file.data, path);
                textureId != INVALID_ID)
            {
                materials.push_back(textureId);
            }
        }
    }
}

void BoxerEngine::Model::LoadMeshes(const aiScene* scene)
{
    meshes.reserve(scene->mNumMeshes);
    for (unsigned i = 0; i < scene->mNumMeshes; ++i)
    {
        Mesh m;
    }
}
