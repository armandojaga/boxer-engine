#pragma once

#include "Module.h"
#include "importers/Importer.h"
#include "core/preferences/editor/ResourcesPreferences.h"

class ModuleImporter : public Module
{
public:
	ModuleImporter();
	bool Init() override;
	bool CleanUp() override;

private:
	BoxerEngine::ResourcesPreferences* preferences;
	std::vector<std::pair<BoxerEngine::ImporterType, BoxerEngine::Importer*>> importers;

	void ImportAsset(const std::filesystem::path& asset_path, const  BoxerEngine::ResourceType asset_type);
	BoxerEngine::ImporterType ToImporterType(const  BoxerEngine::ResourceType type);
};

