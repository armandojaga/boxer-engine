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
			std::string section_name;
			switch (it->GetType())
			{
				case PreferenceType::EDITOR:
					section_name = "editor";
					break;

				case PreferenceType::RENDER:
					section_name = "render";
					break;

				case PreferenceType::CAMERA:
					section_name = "camera";
					break;
			}
			if (!node[section_name].IsDefined())
			{
				continue;
			}
			it->LoadConfig(node[section_name]);
		}
	}
}

Prefs* BoxerEngine::PreferenceManager::GetPreferenceDataByType(PreferenceType type)
{
	for (auto it : preferences)
	{
		if (it->GetType() == type)
		{
			return it;
		}
	}
	return nullptr;
}

Prefs* BoxerEngine::PreferenceManager::GetEditorPreferences() const
{
	return editor;
}
