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
	SaveEntity(scene->GetRoot());
	return false;
}

YAML::Node& BoxerEngine::SceneSerializer::SaveEntity(const BoxerEngine::Entity* entity)
{
	YAML::Node save_scene;
	save_scene["id"] = entity->GetId();
	save_scene["name"] = entity->GetName();
	save_scene["enabled"] = entity->IsEnabled();
	
	for (int i = 0; i < entity->GetComponents().size(); ++i)
	{
		save_scene["component"][i] = entity->GetComponents()[i]->GetId();
		save_scene["component"][i] = entity->GetComponents()[i]->GetName();
		save_scene["component"][i] = entity->GetComponents()[i]->GetType();
		save_scene["component"][i] = entity->GetComponents()[i]->IsEnabled();
	}

	for (auto child : entity->GetChildren())
	{
		SaveEntity(child);
	}

}
