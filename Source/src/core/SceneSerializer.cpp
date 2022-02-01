#include "bepch.h"
#include "SceneSerializer.h"

#include "Scene.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "components/MeshComponent.h"

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(std::filesystem::path& path)
{
    path.filename();
    return nullptr;
}

bool BoxerEngine::SceneSerializer::Save(const Scene* scene, const char* name, const char* path)
{
    const YAML::Node scene_data = SaveEntity(scene->GetRoot());
	BoxerEngine::ResourcesPreferences* preferences = static_cast<BoxerEngine::ResourcesPreferences*>
    	(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
	
	std::string scene_path = path != nullptr ? path : preferences->GetAssetsPath(BoxerEngine::ResourceType::SCENE);
	scene_path.append(name);
	std::ofstream fout(scene_path);
    fout << scene_data;
    return true;
}

YAML::Node BoxerEngine::SceneSerializer::SaveEntity(const Entity* entity)
{
	YAML::Node save_scene;
	save_scene["name"] = entity->GetName();
	save_scene["enabled"] = entity->IsEnabled();
	save_scene["id"] = entity->GetId();
	
	for (int i = 0; i < entity->GetComponents().size(); ++i)
	{
		save_scene["component"][i]["name"] = std::string(entity->GetComponents()[i]->GetName());
		save_scene["component"][i]["enabled"] = entity->GetComponents()[i]->IsEnabled();
		save_scene["component"][i]["id"] = entity->GetComponents()[i]->GetId();
		save_scene["component"][i]["type"] = static_cast<unsigned int>(entity->GetComponents()[i]->GetType());
		save_scene["component"][i]["data"] = std::move(SaveComponent(entity->GetComponents()[i]));
	}

    for (int i = 0; i < entity->GetChildren().size(); ++i)
    {
        save_scene["child"][i] = std::move(SaveEntity(entity->GetChildren()[i]));
    }

    return save_scene;
}

YAML::Node BoxerEngine::SceneSerializer::SaveComponent(const std::shared_ptr<BoxerEngine::Component> component)
{
	YAML::Node component_node;

	switch (component->GetType())
	{
		case Component::Type::TRANSFORM:
		{

			auto tc = std::static_pointer_cast<const BoxerEngine::TransformComponent>(component);

			component_node["position"]["x"] = tc->GetPosition().x;
			component_node["position"]["y"] = tc->GetPosition().y;
			component_node["position"]["z"] = tc->GetPosition().z;
			
			component_node["rotation"]["x"] = tc->GetRotation().x;
			component_node["rotation"]["y"] = tc->GetRotation().y;
			component_node["rotation"]["z"] = tc->GetRotation().z;

			component_node["scale"]["x"] = tc->GetScale().x;
			component_node["scale"]["y"] = tc->GetScale().y;
			component_node["scale"]["z"] = tc->GetScale().z;

			break;
		}
			
		case Component::Type::MESH:
		{
			auto mc = std::static_pointer_cast<const BoxerEngine::MeshComponent>(component);

			component_node["model_path"] = mc->GetModelName();
			
			for (int i = 0; i < mc->GetMeshesCount(); ++i)
			{
				component_node["mesh"][i]["enabled"] = mc->IsMeshEnabled(i);
				
				if (mc->IsMeshTextureLoaded(i))
				{
					component_node["mesh"][i]["texture_file_name"] = mc->GetMeshTextureName(i);
				}
			}
			
			break;
		}
			
		case Component::Type::LIGHT:
			break;

		case Component::Type::CAMERA:
			break;
		
		default:
			break;
	}

	return component_node;
}
