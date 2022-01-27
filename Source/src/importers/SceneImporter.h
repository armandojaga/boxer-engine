#pragma once

#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BoxerEngine
{
	class SceneImporter final : public Importer
	{
	public:
		SceneImporter() = default;
		~SceneImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path);
		void ProcessRoot(aiNode* node, const aiScene* scene);

	private:
		BoxerEngine::ResourcesPreferences* preferences = nullptr;
	};
}

