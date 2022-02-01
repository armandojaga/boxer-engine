#include "bepch.h"
#include "SceneSerializer.h"

#include <yaml-cpp/yaml.h>

#include "Scene.h"

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(std::filesystem::path& path)
{
	path.filename();
	return nullptr;
}

bool BoxerEngine::SceneSerializer::Save(const BoxerEngine::Scene* scene)
{
	YAML::Node scene_data = SaveEntity(scene->GetRoot());
	//preferences = static_cast<BoxerEngine::ResourcesPreferences*>
	//	(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
	std::string scene_path("./assets/scene/MyScene.be");
	std::ofstream fout(scene_path);
	fout << scene_data;
	return true;
}

YAML::Node BoxerEngine::SceneSerializer::SaveEntity(const BoxerEngine::Entity* entity)
{
	YAML::Node save_scene;
	save_scene["id"] = entity->GetId();
	save_scene["name"] = entity->GetName();
	save_scene["enabled"] = entity->IsEnabled();
	
	for (int i = 0; i < entity->GetComponents().size(); ++i)
	{
		save_scene["component"][i] = (unsigned long long)entity->GetComponents()[i]->GetId();
		save_scene["component"][i] = std::move(std::string(entity->GetComponents()[i]->GetName()));
		//save_scene["component"][i] = entity->GetComponents()[i]->GetType();
		save_scene["component"][i] = entity->GetComponents()[i]->IsEnabled();
	}

	for (int i = 0; i < entity->GetChildren().size(); ++i)
	{
		save_scene["child"][i] = SaveEntity(entity->GetChildren()[i]);
	}

	return save_scene;
}
