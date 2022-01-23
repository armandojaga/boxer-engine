#include "Model.h"
#include "Application.h"
#include "modules/ModuleTexture.h"

#include "Globals.h"
#include "Math/float3.h"

Model::Model(const char* file)
    : position(0.0f, 0.0f, 0.0f)
{
    Load(file);
}

/*
 * OTHER ASSIMP POSTPROCESS USEFULL OPTIONS ARE:
 * aiProcess_GenNormals
 * aiProcess_SplitLargeMeshes
 * aiProcess_OptimizeMeshes
*/
void Model::Load(const char* file)
{
    BE_LOG("Loading Module: %s", file);
    Assimp::Importer import;
    const aiScene* scene = import.ReadFile(file, aiProcess_Triangulate | aiProcess_FlipUVs);

    if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        BE_LOG("ERROR::ASSIMP::%c", import.GetErrorString());
        return;
    }
    const std::string path = file;
    directory = path.substr(0, path.find_last_of('\\'));

    BE_LOG("Scene Summary");
    BE_LOG("Meshes: %d", scene->mNumMeshes);
    BE_LOG("Materials: %d", scene->mNumMaterials);
    BE_LOG("Textures: %d", scene->mNumTextures);
    BE_LOG("Cameras: %d", scene->mNumCameras);
    BE_LOG("Animations: %d", scene->mNumAnimations);
    BE_LOG("Lights: %d", scene->mNumLights);

    ProcessNode(scene->mRootNode, scene);
}

void Model::ProcessNode(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.push_back(ProcessMesh(mesh, scene));
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessNode(node->mChildren[i], scene);
    }
}

Mesh Model::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    vec minPoint;
    vec maxPoint;
    minPoint.x = mesh->mVertices[0].x;
    minPoint.y = mesh->mVertices[0].y;
    minPoint.z = mesh->mVertices[0].z;
    maxPoint = minPoint;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        float3 vector;

        // Position
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

        // Bounding Box
        minPoint.x = std::min(vector.x, minPoint.x);
        minPoint.y = std::min(vector.y, minPoint.y);
        minPoint.z = std::min(vector.z, minPoint.z);
        maxPoint.x = std::max(vector.x, maxPoint.x);
        maxPoint.y = std::max(vector.y, maxPoint.y);
        maxPoint.z = std::max(vector.z, maxPoint.z);

        // Normals
        vector.x = mesh->mNormals[i].x;
        vector.y = mesh->mNormals[i].y;
        vector.z = mesh->mNormals[i].z;
        vertex.normal = vector;

        // Texture coords (Mesh couln'd have any)
        if (mesh->mTextureCoords[0])
        {
            float2 vec;
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.tex_coords = vec;
        }
        else
        {
            vertex.tex_coords = float2(0.0f, 0.0f);
        }
        vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    // process material
    if (mesh->mMaterialIndex >= 0)
    {
        aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
        // Diffuse
        std::vector<Texture> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // Specular
        std::vector<Texture> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh(vertices, indices, textures, minPoint, maxPoint);
}

std::vector<Texture> Model::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture> textures;
    for (unsigned int i = 0; i < mat->GetTextureCount(type); i++)
    {
        aiString str;
        mat->GetTexture(type, i, &str);
        bool skip = false;

        //Check if the texture has already loaded
        for (unsigned int j = 0; j < textures_loaded.size(); j++)
        {
            if (std::strcmp(textures_loaded[j].path.data(), str.C_Str()) == 0)
            {
                textures.push_back(textures_loaded[j]);
                skip = true;
                break;
            }
        }

        if (skip)
        {
            continue;
        }

        // if texture hasn't been loaded already, load it
        Texture texture;
        const int texId = App->textures->Load(str.C_Str());
        if (texId < 0)
        {
            BE_LOG("Cannot Load Texture: %s", str.C_Str());
            continue;
        }

        texture.id = static_cast<unsigned>(texId);
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture); // add to loaded textures
    }

    return textures;
}

void Model::Draw() const
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i].Draw();
    }
}
