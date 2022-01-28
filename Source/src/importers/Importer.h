#pragma once

#include <filesystem>

#include "core/preferences/editor/ResourcesPreferences.h"

class YAML::Node;

namespace BoxerEngine
{
	enum class ImporterType
	{
		GENERIC = 0,
		SCENE,
		MODEL,
		MESH,
		COUNT
	};

	class Importer
	{
	public:
		Importer() = default;
		virtual ~Importer() = default;
		virtual void ImportAsset(const std::filesystem::path& asset_path) = 0;
		virtual void SaveToFile(YAML::Node& ticket, const std::string& uuid) = 0;

	protected:
		BoxerEngine::ResourcesPreferences* preferences;
	};
}
