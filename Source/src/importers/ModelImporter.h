#pragma once

#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BoxerEngine
{
	class ModelImporter final : public Importer
	{
	public:
		ModelImporter();
		~ModelImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path);
		void ImportModel(const aiScene* scene, YAML::Node& ticket);
		void SaveToFile(YAML::Node& ticket, const std::string& file_name) override;
	};
}