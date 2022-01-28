#pragma once

#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BoxerEngine
{
	class Modelmporter final : public Importer
	{
	public:
		ModelImporter();
		~ModelImporter();
		void ImportAsset(const std::filesystem::path& asset_path);
		void ProcessRoot(aiNode* node, const aiScene* scene);
	};
}

