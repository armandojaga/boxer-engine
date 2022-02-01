#include "bepch.h"
#include "Scene.h"
#include "components/Component.h"
#include "components/TransformComponent.h"
#include "SceneSerializer.h"

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(std::filesystem::path& path)
{
    path.filename();
    return nullptr;
}

bool BoxerEngine::SceneSerializer::Save(const Scene* scene)
{
    const YAML::Node scene_data = SaveEntity(scene->GetRoot());
    //preferences = static_cast<BoxerEngine::ResourcesPreferences*>
    //	(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    const std::string scene_path("./assets/scene/MyScene.be");
    std::ofstream fout(scene_path);
    fout << scene_data;
    return true;
}

YAML::Node BoxerEngine::SceneSerializer::SaveEntity(const Entity* entity)
{
	YAML::Node save_scene;
	save_scene["id"] = entity->GetId();
	save_scene["name"] = entity->GetName();
	save_scene["enabled"] = entity->IsEnabled();
	
	for (int i = 0; i < entity->GetComponents().size(); ++i)
	{
		save_scene["component"][i]["id"] = entity->GetComponents()[i]->GetId();
		save_scene["component"][i]["name"] = std::string(entity->GetComponents()[i]->GetName());
		save_scene["component"][i]["type"] = static_cast<unsigned int>(entity->GetComponents()[i]->GetType());
		save_scene["component"][i]["enabled"] = entity->GetComponents()[i]->IsEnabled();
		save_scene["component"][i]["data"] = SaveComponent(*entity->GetComponents()[i]);
	}

    for (int i = 0; i < entity->GetChildren().size(); ++i)
    {
        save_scene["child"][i] = SaveEntity(entity->GetChildren()[i]);
    }

    return save_scene;
}

YAML::Node BoxerEngine::SceneSerializer::SaveComponent(const BoxerEngine::Component& component)
{
	YAML::Node component_node;

	switch (component.GetType())
	{
		case Component::Type::TRANSFORM:
		{
			const BoxerEngine::TransformComponent tc = 
				static_cast<const BoxerEngine::TransformComponent&>(component);

			component_node["position"]["x"] = tc.GetPosition().x;
			component_node["position"]["y"] = tc.GetPosition().y;
			component_node["position"]["z"] = tc.GetPosition().z;
			
			component_node["rotation"]["x"] = tc.GetRotation().x;
			component_node["rotation"]["y"] = tc.GetRotation().y;
			component_node["rotation"]["z"] = tc.GetRotation().z;

			component_node["scale"]["x"] = tc.GetScale().x;
			component_node["scale"]["y"] = tc.GetScale().y;
			component_node["scale"]["z"] = tc.GetScale().z;

		}
		case Component::Type::LIGHT:
		case Component::Type::CAMERA:
		case Component::Type::MESH:
		default:
			break;
	}

	return component_node;
}
