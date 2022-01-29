#pragma once

#include "Mesh.h"

#include <vector>
#include <string>

class Model
{
public:
    Model(const char* model_name);
    Model(Model&) = default;
    Model(Model&&) = default;
    ~Model();

    void Draw() const;

private:
    const char* id;
    const char* path;
    std::vector<const char*> mesh_ids{};
    std::vector<Mesh*> meshes{};
    void Load(const char* file);
};
