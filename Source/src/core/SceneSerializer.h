#pragma once

class Scene;
class Entity;

namespace BoxerEngine
{
	class SceneSerializer
	{
	public:
		SceneSerializer() = default;
		~SceneSerializer() = default;

		const Scene* Load();
		const Scene* Load(std::filesystem::path& path);
		bool Save(const Scene* scene);
	private:
		void SaveEntity(const Entity* entity);
	};
}


