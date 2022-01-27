#pragma once

#include "Importer.h"

class aiMesh;
class aiNode; //Debug
class aiScene; //Debug

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