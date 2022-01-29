#include "Model.h"
#include "Globals.h"

#include <yaml-cpp/yaml.h>

Model::Model(const char* model_name)
{
    Load(model_name);
}

void Model::Load(const char* model_name)
{
    BE_LOG("Loading Model: %s", model_name);
    YAML::Node model_data = YAML::LoadFile(model_name);

    for (auto it = model_data.begin(); it != model_data.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("id"))
        {
            id = it->second.as<std::string>().c_str();
        }

        if (it->first.as<std::string>()._Equal("path"))
        {
            path = it->second.as<std::string>().c_str();
        }
    }

    for (auto it = model_data["mesh"].begin(); it != model_data["mesh"].end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("id"))
        {
            mesh_ids.push_back(it->second.as<std::string>().c_str());
        }
    }

    if (mesh_ids.size() == 0)
    {
        return;
    }
    for (auto id : mesh_ids)
    {
        meshes.push_back(new Mesh(id));
    }
}

Model::~Model()
{
    for (auto mesh : meshes)
    {
        delete mesh;
    }
}

void Model::Draw() const
{
    for (unsigned int i = 0; i < meshes.size(); i++)
    {
        meshes[i]->Draw();
    }
}

