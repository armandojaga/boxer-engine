#pragma once
#include "Importer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <yaml-cpp/yaml.h>

namespace BoxerEngine
{
	class TextureImporter : public Importer
	{
		friend class ModelImporter;
	
	public:
		TextureImporter() = default;
		~TextureImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path) override;
		void SaveToFile(YAML::Node& ticket, const std::string& file_name) override;
	
	private:
		void ImportMaterial(aiMaterial* material, const std::string& uuid);
		void ImportTexturesByType(aiMaterial* material, aiTextureType type, YAML::Node& ticket);
		std::string TextureTypeToString(aiTextureType type);
		std::filesystem::path FindTextureLocation(const char* texture);
		void NotifyAddedFile(const char* path);
	};
}

