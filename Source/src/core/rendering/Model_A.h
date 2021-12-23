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
    ~Model_A();

    void Draw();

	bool IsValid() { return (!Directory.empty() && Meshes.size() != 0 && TexturesLoaded.size() != 0); }
    const std::vector<Mesh_A>& GetMeshes() const { return Meshes; }
    const std::string& GetDirectory() const { return Directory; }

	const float3& GetOrigin() const { return Position; }
    void SetOrigin(const float3& position) { Position = position; }

    void Load(const char* file);

private:
    // model data
    std::vector<Mesh_A> Meshes;
    std::string Directory;
    std::vector<Texture_A> TexturesLoaded;
    float3 Position;

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh_A ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture_A> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
    int TextureFromFile(const char* path, const std::string& directory) const;
};

