#pragma once

#include <string>
#include <vector>
#include "Math/float3.h"
#include "Math/float2.h"
#include "core/rendering/BoundingBox.h"

namespace BoxerEngine
{
    struct Vertex
    {
        Vertex(const float3& pos, const float3& norm, const float2& tex)
            : position(pos)
            , normal(norm)
            , tex_coords(tex)
        {}

        Vertex(Vertex&& vertex) noexcept
        {
            this->position = std::move(vertex.position);
            this->normal = std::move(vertex.normal);
            this->tex_coords = std::move(vertex.tex_coords);
        }

        float3 position;
        float3 normal;
        float2 tex_coords;
    };

    struct Texture
    {
        Texture(const unsigned int id, std::string type)
            : id(id)
            , type(std::move(type))
        {}

        Texture(Texture&& texture) = default;

        Texture& operator= (Texture&& tex) noexcept
        {
            this->id = std::move(tex.id);
            this->type = std::move(tex.type);
            return *this;
        }
        
        unsigned int id;
        std::string type;
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
        [[nodiscard]] const std::string& GetId() const { return id; };

        void SetTexture(unsigned int id, const char* type);
    private:
        // mesh data
        std::string id;
        float3 min_point;
        float3 max_point;

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<Texture> textures;

        //  render data
        unsigned int VAO;
        unsigned int VBO;
        unsigned int EBO;

        void SetupMesh();
        void Load(const char* mesh_data);
    };
}