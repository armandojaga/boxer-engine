#pragma once
#include "Importer.h"

namespace BoxerEngine
{
	class SceneImporter final : public Importer
	{
	public:
		SceneImporter();
		~SceneImporter() = default;

		void ImportAsset(const std::filesystem::path& asset_path) override;

	};
}

