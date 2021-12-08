#pragma once

#include <vector>

#include "assimp/mesh.h"

namespace BoxerEngine
{
    class Mesh
    {
    private:
        unsigned int num_vertices{};
        unsigned int num_indices{};
        unsigned int vbo{};
        unsigned int ebo{};
        unsigned int vao{};
        unsigned int texture;

    public:
        Mesh();
        ~Mesh();
        void LoadMesh(const aiMesh* mesh);
        void Draw(const std::vector<unsigned int>& model_textures) const;
    private:
        void LoadEBO(const aiMesh* mesh);
        void LoadVBO(const aiMesh* mesh);
        void CreateVAO();
    };
}
