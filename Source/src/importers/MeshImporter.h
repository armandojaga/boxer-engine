#pragma once

#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "core/util/UUID.h"

namespace BoxerEngine
{
	class MeshImporter final : public Importer
	{
		friend class ModelImporter;

		public:
			MeshImporter() = default;
			~MeshImporter() override = default;
			void ImportAsset(const std::filesystem::path& mesh_path) override;
		private:
			void ImportMesh(aiMesh* mesh, const std::string& mesh_uid);
	};
}