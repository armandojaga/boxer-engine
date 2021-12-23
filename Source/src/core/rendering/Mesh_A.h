#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"

struct Vertex_A
{
    float3 Position;
    float3 Normal;
    float2 TexCoords;
};

struct Texture_A
{
    unsigned int Id;
    std::string Type;
    std::string Path;
};

class Mesh_A
{
public:
    // mesh data
    std::vector<Vertex_A>       Vertices;
    std::vector<unsigned int>   Indices;
    std::vector<Texture_A>      Textures;

    Mesh_A(std::vector<Vertex_A> vertices, std::vector<unsigned int> indices, std::vector<Texture_A> textures);
    void Draw();

    size_t GetNumVertices() const  { return Vertices.size(); }
    size_t GetNumIndices()  const  { return Indices.size(); }
    size_t GetNumTextures() const  { return Textures.size(); }

private:
    //  render data
    unsigned int VAO;
    unsigned int VBO;
    unsigned int EBO;

    void SetupMesh();
};

