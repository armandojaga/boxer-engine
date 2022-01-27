#pragma once

#include "Importer.h"

namespace BoxerEngine
{
	class MeshImporter : public Importer
	{
		~MeshImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path) override;
	};
}


