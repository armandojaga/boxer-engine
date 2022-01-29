#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"
#include "core/rendering/BoundingBox.h"

struct Vertex
{
    Vertex(const float3& pos, const float3& norm, const float2& tex)
        : position(pos)
        , normal(norm)
        , tex_coords(tex)
    {}

    float3 position;
    float3 normal;
    float2 tex_coords;
};

struct Texture
{
    Texture(const unsigned int id, const std::string& type, const std::string& path)
        : id(id)
        , type(type)
        , path(path)
    {}

    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(const char* file_path);
    ~Mesh();
    void Draw() const;

    [[nodiscard]] size_t GetNumVertices() const { return vertices.size(); }
    [[nodiscard]] size_t GetNumIndices() const { return indices.size(); }
    [[nodiscard]] size_t GetNumTextures() const { return textures.size(); }

private:
    // mesh data
    const char* id;
    const char* material_id;
    float3 min_point;
    float3 max_point;
    std::vector<Vertex*> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*> textures;

    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void SetupMesh();
    void Load(const char* mesh_data);
    void LoadTextureData(const char* texture_path, const char* material_id);
};
