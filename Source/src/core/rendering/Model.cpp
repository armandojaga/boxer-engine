#include "Model.h"

#include "Application.h"
#include "Globals.h"

#include "assimp/cimport.h"
#include "assimp/postprocess.h"
#include "modules/ModuleTexture.h"
#include "Mesh.h"
#include "GL/glew.h"

BoxerEngine::Model::Model() = default;

BoxerEngine::Model::~Model()
{
    ClearModel();
};

void BoxerEngine::Model::Load(const char* path)
{
    const aiScene* scene = aiImportFile(path, aiProcess_Triangulate | aiProcess_OptimizeMeshes
                                        | aiProcess_ValidateDataStructure | aiProcess_CalcTangentSpace
                                        | aiProcess_GenSmoothNormals | aiProcess_ImproveCacheLocality
                                        | aiProcess_LimitBoneWeights | aiProcess_RemoveRedundantMaterials
                                        | aiProcess_SplitLargeMeshes | aiProcess_Triangulate
                                        | aiProcess_GenUVCoords | aiProcess_SortByPType
                                        | aiProcess_FindDegenerates | aiProcess_FindInvalidData
                                        | aiProcess_FlipUVs); // TODO, check if we can determine the orientation

    if (scene)
    {
        ClearModel();
        BE_LOG("Loaded model from %s", path);
        LoadTextures(scene, path);
        LoadMeshes(scene);
    }
    else
    {
        BE_LOG("Error loading %s: %s", path, aiGetErrorString());
    }
}

void BoxerEngine::Model::LoadTextures(const aiScene* scene, const char* path)
{
    aiString file;
    textures.reserve(scene->mNumMaterials);
    for (unsigned i = 0; i < scene->mNumMaterials; ++i)
    {
        if (scene->mMaterials[i]->GetTexture(aiTextureType_DIFFUSE, 0, &file) == AI_SUCCESS)
        {
            if (const unsigned int textureId = App->textures->Load(file.data, path);
                textureId != INVALID_ID)
            {
                textures.push_back(textureId);
            }
        }
        // auto diffuse = scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE);
        // auto specular = scene->mMaterials[i]->GetTextureCount(aiTextureType_SPECULAR);
        // auto ambient = scene->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT);
        // auto emissive = scene->mMaterials[i]->GetTextureCount(aiTextureType_EMISSIVE);
        // auto height = scene->mMaterials[i]->GetTextureCount(aiTextureType_HEIGHT);
        // auto normals = scene->mMaterials[i]->GetTextureCount(aiTextureType_NORMALS);
        // auto shininess = scene->mMaterials[i]->GetTextureCount(aiTextureType_SHININESS);
        // auto opacity = scene->mMaterials[i]->GetTextureCount(aiTextureType_OPACITY);
        // auto displacement = scene->mMaterials[i]->GetTextureCount(aiTextureType_DISPLACEMENT);
        // auto lightmap = scene->mMaterials[i]->GetTextureCount(aiTextureType_LIGHTMAP);
        // auto refection = scene->mMaterials[i]->GetTextureCount(aiTextureType_REFLECTION);
        // auto cabseColor = scene->mMaterials[i]->GetTextureCount(aiTextureType_BASE_COLOR);
        // auto normalCamera = scene->mMaterials[i]->GetTextureCount(aiTextureType_NORMAL_CAMERA);
        // auto emissionColor = scene->mMaterials[i]->GetTextureCount(aiTextureType_EMISSION_COLOR);
        // auto metalness = scene->mMaterials[i]->GetTextureCount(aiTextureType_METALNESS);
        // auto diffuseRoughness = scene->mMaterials[i]->GetTextureCount(aiTextureType_DIFFUSE_ROUGHNESS);
        // auto ambientOcclusion = scene->mMaterials[i]->GetTextureCount(aiTextureType_AMBIENT_OCCLUSION);
        // auto unknown = scene->mMaterials[i]->GetTextureCount(aiTextureType_UNKNOWN);
    }
}

void BoxerEngine::Model::ClearModel()
{
    for (auto texture : textures)
    {
        glDeleteTextures(1, &texture);
    }
    textures.clear();
    for (const auto mesh : meshes)
    {
        delete mesh;
    }
    meshes.clear();
}

void BoxerEngine::Model::LoadMeshes(const aiScene* scene)
{
    meshes.reserve(scene->mNumMeshes);
    for (unsigned i = 0; i < scene->mNumMeshes; ++i)
    {
        auto mesh = new Mesh();
        mesh->LoadMesh(scene->mMeshes[i]);
        meshes.push_back(mesh);
    }
}

void BoxerEngine::Model::Draw() const
{
    for (const auto mesh : meshes)
    {
        mesh->Draw(textures);
    }
}
