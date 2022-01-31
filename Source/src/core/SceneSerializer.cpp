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

void BoxerEngine::SceneSerializer::SaveEntity(const BoxerEngine::Entity* entity)
{
	entity->GetId();
	entity->GetName();
	
	for (auto component : entity->GetComponents())
	{
	}

	for (auto child : entity->GetChildren())
	{
		SaveEntity(child);
	}

}
