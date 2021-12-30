#pragma once

#include <vector>

struct aiScene;

namespace BoxerEngine
{
    class Mesh;

    class Model
    {
    public:
        Model();
        ~Model();

        void Load(const char* path);
        void Draw() const;

    private:
        std::vector<unsigned int> textures;
        std::vector<Mesh*> meshes;

        void LoadTextures(const aiScene*, const char*);
        void ClearModel();
        void LoadMeshes(const aiScene*);
    };
}
