#pragma once

#include "Mesh_A.h"

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <Math/float4x4.h>

class Model_A
{
public:
    Model_A() = default;
    Model_A(const char* file);
    ~Model_A() = default;

    void Draw() const;

	bool IsValid() { return (!directory.empty() && meshes.size() != 0 && textures_loaded.size() != 0); }
    const std::vector<Mesh_A>& GetMeshes() const { return meshes; }
    const std::string& GetDirectory() const { return directory; }

	const float3& GetOrigin() const { return position; }
    void SetOrigin(const float3& pos) { position = pos; }

    void Load(const char* file);

private:
    // model data
    std::vector<Mesh_A> meshes;
    std::string directory;
    std::vector<Texture_A> textures_loaded;
    float3 position;

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh_A ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture_A> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};

