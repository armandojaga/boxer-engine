#pragma once

#include "Importer.h"

namespace BoxerEngine
{
	class GenericImporter : public Importer
	{
	public:
		GenericImporter();
		void ImportAsset(const std::filesystem::path& asset_path) override;
	};
}

