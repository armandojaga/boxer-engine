#pragma once

#include "Mesh.h"

#include <vector>
#include <string>

namespace BoxerEngine
{
    class Model
    {
    public:
        Model(const char* modelName);
        Model(Model&) = default;
        Model(Model&&) = default;
        ~Model();

        void Draw() const;
        [[nodiscard]] const char* GetPath() const { return path.c_str(); }
        [[nodiscard]] unsigned int GetMeshesCount() const { return meshes.size(); }
        [[nodiscard]] const char* GetMeshIdByIndex(const int index) const { return meshes[index]->GetId().c_str(); }

        void SetTransform();
        void SetMeshTexture(int meshIndex, int textureId, const char* textureType);
    private:
        std::string id;
        std::string path;
        std::vector<std::string> mesh_ids{};
        std::vector<Mesh*> meshes{};

        void Load(const char* file);
    };
}
