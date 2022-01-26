#pragma once

#include "Module.h"
#include "importers/Importer.h"

class ModuleImporter : public Module
{
public:
	ModuleImporter();
	bool Init() override;
	bool CleanUp() override;

private:
	BoxerEngine::ResourcesPreferences* preferences;
	BoxerEngine::Importer* importer;
};

