#pragma once

#include "Importer.h"

namespace BoxerEngine
{
	class GenericImporter : public Importer
	{
	public:
		GenericImporter() = default;
		~GenericImporter() override = default;
		void ImportAsset(const std::filesystem::path& asset_path) override;
	};
}

