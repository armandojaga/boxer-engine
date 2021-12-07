#include "Model.h"

#include "Application.h"
#include "Globals.h"
#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "modules/ModuleTexture.h"

BoxerEngine::Model::Model()
= default;

BoxerEngine::Model::~Model()
{
}

void BoxerEngine::Model::Load(const char* file_name)
{
    const aiScene* scene = aiImportFile(file_name, aiProcessPreset_TargetRealtime_MaxQuality);
    if (scene)
    {
        BE_LOG("loaded model %s", file_name);
        // TODO: LoadTextures(scene->mMaterials, scene->mNumMaterials);
        // TODO: LoadMeshes(scene->mMeshes, scene->mNumMeshes);
    }
    else
    {
        BE_LOG("Error loading %s: %s", file_name, aiGetErrorString());
    }
}

void BoxerEngine::Model::LoadMaterials(const aiScene* scene)
{
    aiString file;
    materials.reserve(scene->mNumMaterials);
    for (unsigned i = 0; i < scene->mNumMaterials; ++i)
    {
        if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
        {
            materials.push_back(App->textures->Load(file.data));
        }
    }
}
