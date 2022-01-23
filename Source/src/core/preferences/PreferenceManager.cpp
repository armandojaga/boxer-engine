#include "PreferenceManager.h"

#include "src/EditorPrefs.h"
//#include "src/RenderPrefs.h"
#include "Globals.h"

using namespace BoxerEngine;

PreferenceManager::PreferenceManager()
{
	preferences.reserve((size_t)PreferenceType::TYPES_AMOUNT);
	
	editor = new EditorPrefs();
	//render = new RenderPrefs();
	preferences.emplace_back(editor);
	//preferences.emplace_back(render);

	LoadConfigurationFile();
}

BoxerEngine::PreferenceManager::~PreferenceManager()
{
	for (auto it : preferences)
	{
		delete it;
	}
}

void BoxerEngine::PreferenceManager::LoadConfigurationFile()
{
	std::vector<YAML::Node> nodes_vec = YAML::LoadAllFromFile(CONFIG_PATH);

	for (auto node : nodes_vec)
	{
		for (auto it : preferences)
		{
			it->LoadConfig(node);
		}
	}
}

Prefs* BoxerEngine::PreferenceManager::GetPreferenceData(PreferenceType type)
{
	for (auto it : preferences)
	{
		if (it->GetType() == type)
		{
			return it;
		}
	}
}

Prefs* BoxerEngine::PreferenceManager::GetEditorPreferences() const
{
	return editor;
}
