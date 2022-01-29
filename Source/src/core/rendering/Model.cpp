#include "Model.h"
#include "Globals.h"
#include "Application.h"

#include <yaml-cpp/yaml.h>
#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

Model::Model(const char* model_name)
{
    Load(model_name);
}

void Model::Load(const char* model_name)
{
    BE_LOG("Loading Model: %s", model_name);
    BoxerEngine::ResourcesPreferences* preferences = 
        static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    std::string library_path(preferences->GetLibraryPath(BoxerEngine::ResourceType::MESH));
    YAML::Node model_data = YAML::LoadFile(model_name);

    for (auto it = model_data.begin(); it != model_data.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("id"))
        {
            id = it->second.as<std::string>();
        }

        if (it->first.as<std::string>()._Equal("file_path"))
        {
            path = it->second.as<std::string>();
        }
    }

    mesh_ids.reserve(model_data["mesh"].size());
    for (int i = 0; i < model_data["mesh"].size(); ++i)
    {
        mesh_ids.push_back(model_data["mesh"][i]["id"].as<std::string>());
    }
    
    if (mesh_ids.size() == 0)
    {
        return;
    }
    for (auto id : mesh_ids)
    {
        std::string mesh_path = library_path;
        mesh_path.append(id);
        meshes.push_back(new Mesh(mesh_path.c_str()));
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

