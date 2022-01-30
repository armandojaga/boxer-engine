#include "Model.h"
#include "Globals.h"
#include "Application.h"

#include "core/preferences/PreferenceManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"
#include "core/util/Files.h"
#include "core/util/StringUtils.h"

using namespace BoxerEngine;

Model::Model(const char* model_name)
{
    Load(model_name);
}

void Model::Load(const char* model_name)
{
    BE_LOG("Loading Model: %s", model_name);

    BoxerEngine::ResourcesPreferences* preferences = 
        static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    std::string meshes_library_path(preferences->GetLibraryPath(BoxerEngine::ResourceType::MESH));
    std::string models_library_path(preferences->GetLibraryPath(BoxerEngine::ResourceType::MODEL));
    
    models_library_path.append(model_name);
    if (!Files::IsValidFilePath(models_library_path))
    {
        return;
    }

    YAML::Node model_data = YAML::LoadFile(models_library_path);

    for (auto it = model_data.begin(); it != model_data.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("id"))
        {
            id = std::move(it->second.as<std::string>());
        }

        if (it->first.as<std::string>()._Equal("file_path"))
        {
            path = std::move(it->second.as<std::string>());
        }
    }

    mesh_ids.reserve(model_data["mesh"].size());
    for (int i = 0; i < model_data["mesh"].size(); ++i)
    {
        mesh_ids.emplace_back(model_data["mesh"][i]["id"].as<std::string>());
    }
    
    if (mesh_ids.size() == 0)
    {
        return;
    }
    for (auto id : mesh_ids)
    {
        std::string mesh_path = BoxerEngine::StringUtils::Concat(preferences->GetLibraryPath(BoxerEngine::ResourceType::MESH), id);
        meshes.emplace_back(new Mesh(mesh_path.c_str()));
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

void BoxerEngine::Model::SetTransform()
{
}

void BoxerEngine::Model::SetMeshTexture(const char* mesh_id, const int texture_id, const char* texture_type)
{
    for (auto mesh : meshes)
    {
        mesh->SetTexture(texture_id, texture_type);
        //if (mesh_id == mesh->GetId())
        //{
        //    mesh->SetTexture(texture_id, texture_type);
        //    return;
        //}
    }
}