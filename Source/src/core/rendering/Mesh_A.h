#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"

struct Vertex_A
{
    float3 position;
    float3 normal;
    float2 tex_coords;
};

struct Texture_A
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh_A
{
public:
    // mesh data
    std::vector<Vertex_A>       vertices;
    std::vector<unsigned int>   indices;
    std::vector<Texture_A>      textures;

    Mesh_A(std::vector<Vertex_A> vertices, std::vector<unsigned int> indices, std::vector<Texture_A> textures);
    void Draw() const;

    size_t GetNumVertices() const  { return vertices.size(); }
    size_t GetNumIndices()  const  { return indices.size(); }
    size_t GetNumTextures() const  { return textures.size(); }

private:
    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void SetupMesh();
};

