#pragma once

#include <vector>

#include "assimp/mesh.h"

namespace BoxerEngine
{
    class Mesh
    {
    private:
        unsigned int num_indices{};
        unsigned int vbo{};
        unsigned int ebo{};
        unsigned int vao{};
        unsigned int num_vertices{};
    public:
        Mesh();
        ~Mesh();
        void LoadEBO(const aiMesh* mesh);
        void LoadVBO(const aiMesh* mesh);
        void CreateVAO();
        void Draw(const std::vector<unsigned>& model_textures);
    };
}
