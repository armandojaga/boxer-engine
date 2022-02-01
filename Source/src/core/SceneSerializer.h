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
		const Scene* Load(std::filesystem::path& path);
		YAML::Node SaveEntity(const Entity* entity);
		YAML::Node SaveComponent(const std::shared_ptr<BoxerEngine::Component> component);
		const Entity* LoadEntity(YAML::Node& entity);
		const std::shared_ptr<BoxerEngine::Component> LoadComponent(YAML::Node& component);
	};
}
