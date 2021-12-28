#include "Model_A.h"
#include "Application.h"
#include "modules/ModuleTexture.h"

#include "Globals.h"
#include "GL/glew.h"
#include "Math/float3.h"

#include <algorithm>

Model_A::Model_A(const char* file)
	: position(0.0f, 0.0f, 0.0f)
{
	Load(file);
}

Model_A::~Model_A()
{
}

/*
 * OTHER ASSIMP POSTPROCESS USEFULL OPTIONS ARE:
 * aiProcess_GenNormals
 * aiProcess_SplitLargeMeshes
 * aiProcess_OptimizeMeshes
*/
void Model_A::Load(const char* file)
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

void Model_A::ProcessNode(aiNode* node, const aiScene* scene)
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

Mesh_A Model_A::ProcessMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<Vertex_A> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture_A> textures;

    // process vertex positions, normals and texture coordinates
    for (unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex_A vertex;
        float3 vector;

        // Position
    	vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;

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
        std::vector<Texture_A> diffuseMaps = LoadMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse");
        textures.insert(textures.end(), diffuseMaps.begin(), diffuseMaps.end());
        // Specular
        std::vector<Texture_A> specularMaps = LoadMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular");
        textures.insert(textures.end(), specularMaps.begin(), specularMaps.end());
    }

    return Mesh_A(vertices, indices, textures);
}

std::vector<Texture_A> Model_A::LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
    std::vector<Texture_A> textures;
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
        Texture_A texture;
        const int texId = App->textures->Load(str.C_Str());
        if (texId < 0)
        {
            BE_LOG("Cannot Load Texture: %s", str.C_Str());
            continue;
        }

        texture.id = (unsigned)texId;
        texture.type = typeName;
        texture.path = str.C_Str();
        textures.push_back(texture);
        textures_loaded.push_back(texture); // add to loaded textures
    }

    return textures;
}

void Model_A::Draw()
{
	for (unsigned int i = 0; i < meshes.size(); i++)
	{
        meshes[i].Draw();
	}
}