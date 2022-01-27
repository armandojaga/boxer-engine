#pragma once

#include <filesystem>

namespace BoxerEngine
{
	enum class ImporterType
	{
		GENERIC = 0,
		SCENE,
		MESH,
		COUNT
	};

	class Importer
	{
	public:
		Importer() = default;
		virtual ~Importer() = default;
		virtual void ImportAsset(const std::filesystem::path& asset_path) = 0;

	protected:
		BoxerEngine::ResourcesPreferences* preferences = nullptr;
	};
}
