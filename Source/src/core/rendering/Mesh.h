#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"
#include "core/rendering/BoundingBox.h"

struct Vertex
{
    float3 position;
    float3 normal;
    float2 tex_coords;
};

struct Texture
{
    unsigned int id{};
    std::string type;
    std::string path;
};

class Mesh
{
public:
    Mesh(const char* id);
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    Mesh(std::vector<Vertex> ver, std::vector<unsigned int> ind, std::vector<Texture> tex, float3 minPoint, float3 maxPoint);
    void Draw() const;

    [[nodiscard]] size_t GetNumVertices() const { return vertices.size(); }
    [[nodiscard]] size_t GetNumIndices() const { return indices.size(); }
    [[nodiscard]] size_t GetNumTextures() const { return textures.size(); }

private:
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    std::unique_ptr<BoxerEngine::BoundingBox> bounding_box;

    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void SetupMesh();
    void Load(const char* mesh_data);
};
