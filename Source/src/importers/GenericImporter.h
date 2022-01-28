#pragma once

#include "Importer.h"

namespace BoxerEngine
{
	// As this is a generic importer we have to deduce the resource type
	// to properly deliver it. In the future this class is going to be 
	// replaced for each importer implementation is cover here
	class GenericImporter : public Importer
	{
	public:
		GenericImporter() = default;
		~GenericImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path) override;
		void SaveToFile(YAML::Node& ticket, const std::string& file_name) override;
	private:
		ResourceType DeduceResourceType(const std::filesystem::path& path);
	};
}

