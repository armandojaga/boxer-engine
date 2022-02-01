#pragma once

#include <filesystem>

namespace BoxerEngine
{
	class Scene;
	class Entity;
	class Component;

    class SceneSerializer
    {
    public:
        SceneSerializer() = default;
        ~SceneSerializer() = default;

		const Scene* Load(std::filesystem::path& path);
		bool Save(const Scene* scene, const char* name, const char* path = nullptr);
	private:
		YAML::Node SaveEntity(const Entity* entity);
		YAML::Node SaveComponent(const std::shared_ptr<BoxerEngine::Component> component);
	};
}
