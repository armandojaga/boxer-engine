#pragma once

#include "Mesh.h"

#include <vector>
#include <string>
#include <yaml-cpp/yaml.h>

class Model
{
public:
    Model(const char* model_name);
    Model(Model&) = default;
    Model(Model&&) = default;
    ~Model();

    void Draw() const;

private:
    std::string id;
    std::string path;
    std::vector<std::string> mesh_ids{}; // TODO: consider using const char[36] as uuid is fixed lenght
    std::vector<Mesh*> meshes{};

    void Load(const char* file);
};
