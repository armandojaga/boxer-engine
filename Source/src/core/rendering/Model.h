#pragma once

#include <vector>

struct aiScene;

namespace BoxerEngine
{
    class Mesh;

    class Model
    {
    private:
        std::vector<unsigned int> textures;
        std::vector<Mesh*> meshes;

    public:
        Model();
        ~Model();

        void Load(const char* path);
        void Draw() const;

    private:
        void LoadTextures(const aiScene*, const char*);
        void ClearModel();
        void LoadMeshes(const aiScene*);
    };
}
