#pragma once

#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace BoxerEngine
{
	class MeshImporter final : public Importer
	{
	public:
		MeshImporter() = default;
		~MeshImporter() override = default;
		void ImportAsset(const std::filesystem::path& mesh_path) override;
		void ImportMesh(aiMesh* mesh);
	private:
		void ProcessRoot(aiNode* node, const aiScene* scene); // Function for debug
	};
}