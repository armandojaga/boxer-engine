#pragma once

#include <vector>

#include "assimp/scene.h"

namespace BoxerEngine
{
    class Mesh;

    class Model
    {
    private:
        std::vector<unsigned int> materials;
        std::vector<Mesh&> meshes;

    public:
        Model();
        ~Model();
        
        void Load(const char* path);

    private:
        void LoadMaterials(const aiScene*, const char*);
        void LoadMeshes(const aiScene*);
    };
}
