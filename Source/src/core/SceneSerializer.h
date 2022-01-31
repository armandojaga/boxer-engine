#pragma once

#include <filesystem>

namespace BoxerEngine
{
	class Scene;
	class Entity;

	class SceneSerializer
	{
	public:
		SceneSerializer() = default;
		~SceneSerializer() = default;

		const Scene* Load(std::filesystem::path& path);
		bool Save(const Scene* scene);
	private:
		YAML::Node& SaveEntity(const Entity* entity);
	};
}


