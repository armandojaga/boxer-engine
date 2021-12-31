#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"

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
    // mesh data
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;

    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
    void Draw() const;

    [[nodiscard]] size_t GetNumVertices() const { return vertices.size(); }
    [[nodiscard]] size_t GetNumIndices() const { return indices.size(); }
    [[nodiscard]] size_t GetNumTextures() const { return textures.size(); }

private:
    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void SetupMesh();
};
