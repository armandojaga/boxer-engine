#include "bepch.h"
#include "SceneSerializer.h"
#include "Scene.h"
#include "Entity.h"

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load()
{
	return nullptr;
}

const BoxerEngine::Scene* BoxerEngine::SceneSerializer::Load(std::filesystem::path& path)
{
	return nullptr;
}

bool BoxerEngine::SceneSerializer::Save(const BoxerEngine::Scene* scene)
{
	SaveEntity(scene->GetRoot());
	return false;
}

void BoxerEngine::SceneSerializer::SaveEntity(const Entity* entity)
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
