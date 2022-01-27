#include "MeshImporter.h"
#include <Globals.h>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <yaml-cpp/yaml.h>

#include "core/file system/FileManager.h"

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

    BE_LOG("Scene Summary");
    BE_LOG("Meshes: %d", scene->mNumMeshes);
    BE_LOG("Materials: %d", scene->mNumMaterials);
    BE_LOG("Textures: %d", scene->mNumTextures);
    BE_LOG("Cameras: %d", scene->mNumCameras);
    BE_LOG("Animations: %d", scene->mNumAnimations);
    BE_LOG("Lights: %d", scene->mNumLights);

    ProcessRoot(scene->mRootNode, scene);
}

void MeshImporter::ProcessRoot(aiNode* node, const aiScene* scene)
{
    // process all the node's meshes (if any)
    for (unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        //meshes.push_back(ProcessMesh(mesh, scene));
        MeshImporter::ImportMesh(mesh);
    }
    // then do the same for each of its children
    for (unsigned int i = 0; i < node->mNumChildren; i++)
    {
        ProcessRoot(node->mChildren[i], scene);
    }
}

void MeshImporter::ImportMesh(aiMesh* mesh)
{
    YAML::Node yaml_node;

    yaml_node["min_point"]["x"] = std::min(mesh->mVertices[0].x, yaml_node["min_point"]["x"].as<float>());
    yaml_node["min_point"]["y"] = std::min(mesh->mVertices[0].y, yaml_node["min_point"]["y"].as<float>());
    yaml_node["min_point"]["z"] = std::min(mesh->mVertices[0].z, yaml_node["min_point"]["z"].as<float>());

    yaml_node["max_point"] = yaml_node["min_point"];

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

        yaml_node["max_point"]["x"] = std::min(mesh->mVertices[i].x, yaml_node["max_point"]["x"].as<float>());
        yaml_node["max_point"]["y"] = std::min(mesh->mVertices[i].y, yaml_node["max_point"]["y"].as<float>());
        yaml_node["max_point"]["z"] = std::min(mesh->mVertices[i].z, yaml_node["max_point"]["z"].as<float>());
        
        //// Position
        //vector.x = mesh->mVertices[i].x;
        //vector.y = mesh->mVertices[i].y;
        //vector.z = mesh->mVertices[i].z;
        //vertex.position = vector;
        //
        // Bounding Boxs
       /* minPoint.x = std::min(vector.x, minPoint.x);
        minPoint.y = std::min(vector.y, minPoint.y);
        minPoint.z = std::min(vector.z, minPoint.z);
        maxPoint.x = std::max(vector.x, maxPoint.x);
        maxPoint.y = std::max(vector.y, maxPoint.y);
        maxPoint.z = std::max(vector.z, maxPoint.z);*/
        //
        //// Normals
        //vector.x = mesh->mNormals[i].x;
        //vector.y = mesh->mNormals[i].y;
        //vector.z = mesh->mNormals[i].z;
        //vertex.normal = vector;
        //
        //// Texture coords (Mesh couln'd have any)
        //if (mesh->mTextureCoords[0])
        //{
        //    float2 vec;
        //    vec.x = mesh->mTextureCoords[0][i].x;
        //    vec.y = mesh->mTextureCoords[0][i].y;
        //    vertex.tex_coords = vec;
        //}
        //else
        //{
        //    vertex.tex_coords = float2(0.0f, 0.0f);
        //}
        //vertices.push_back(vertex);
    }

    // process indices
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        for (unsigned int j = 0; j < face.mNumIndices; j++)
        {
            yaml_node["indices"][i]["face#" + j] = face.mIndices[j];
        }
    }
    
    std::ofstream fout("./library/meshes/mesh.be");
    fout << yaml_node;
}