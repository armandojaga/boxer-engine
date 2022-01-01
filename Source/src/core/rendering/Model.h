#pragma once

#include "Mesh.h"

#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

class Model
{
public:
    Model() = default;
    Model(const char* file);
    ~Model() = default;

    void Draw() const;

    [[nodiscard]] bool IsValid() const { return (!directory.empty() && meshes.size() != 0 && textures_loaded.size() != 0); }
    [[nodiscard]] const std::vector<Mesh>& GetMeshes() const { return meshes; }
    [[nodiscard]] const std::string& GetDirectory() const { return directory; }

    [[nodiscard]] const float3& GetOrigin() const { return position; }
    void SetOrigin(const float3& origin) { position = origin; }

    void Load(const char* file);

private:
    // model data
    std::vector<Mesh> meshes{};
    std::string directory;
    std::vector<Texture> textures_loaded{};
    float3 position;

    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
