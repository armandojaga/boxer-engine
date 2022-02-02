#pragma once

#include <filesystem>

namespace BoxerEngine
{
	class Scene;
	class Entity;
	class Component;

    class SceneSerializer
    {
		friend ModuleScene;

    public:
        SceneSerializer() = default;
        ~SceneSerializer() = default;
		
		bool Save(const Scene* scene, const char* name, const char* path = nullptr);
	private:
		// Load is private to ensure only ModuleScene can call it 
		// as we retrieve ownership of scene object pointer
		Scene* Load(const char* path);
		YAML::Node SaveEntity(const Entity* entity);
		YAML::Node SaveComponent(const std::shared_ptr<BoxerEngine::Component> component);
		const Entity* LoadEntity(YAML::Node entity_node, Scene* scene, Entity* parent = nullptr);
		void LoadComponent(YAML::Node component, Entity* entity);
	};
}
