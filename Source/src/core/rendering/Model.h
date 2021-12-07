#pragma once

#include <vector>

#include "assimp/scene.h"

namespace BoxerEngine
{
    class Model
    {
    public:
        Model();
        ~Model();
        static void Load(const char* file_name);
        void LoadMaterials(const aiScene* scene);
        std::vector<unsigned int> materials;
    };
}
