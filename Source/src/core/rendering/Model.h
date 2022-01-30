#pragma once

#include "Mesh.h"

#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

namespace BoxerEngine
{
    class Model
    {
    public:
        Model(const char* model_name);
        Model(Model&) = default;
        Model(Model&&) = default;
        ~Model();

        void Draw() const;
        [[nodiscard]] const char* GetPath() const { return path.c_str(); }
        [[nodiscard]] unsigned int GetMeshesCount() const { return meshes.size(); }

        void SetTransform();
        void SetMeshTexture(const char* mesh_id, const int texture_id, const char* texture_type);
    private:
        std::string id;
        std::string path;
        std::vector<std::string> mesh_ids{};
        std::vector<Mesh*> meshes{};

        void Load(const char* file);
    };
}