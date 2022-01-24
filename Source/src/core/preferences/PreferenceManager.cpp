#include "PreferenceManager.h"

#include "src/EditorPrefs.h"
#include "src/RenderPrefs.h"
#include "src/GlobalPrefs.h"
#include "src/CameraPrefs.h"
#include "Globals.h"

using namespace BoxerEngine;

PreferenceManager::PreferenceManager()
{
	preferences.reserve((size_t)PreferenceType::TYPES_AMOUNT);
	
	editor = new EditorPrefs();
	globals = new GlobalPrefs();
	render = new RenderPrefs();
	camera = new CameraPrefs();

	preferences.emplace_back(globals);
	preferences.emplace_back(render);
	preferences.emplace_back(editor);
	preferences.emplace_back(camera);

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
	for (auto node : nodes_vec)
	{
		for (auto it : preferences)
		{
			std::string section_name;
			switch (it->GetType())
			{
				case PreferenceType::GLOBALS:
					section_name = "globals";
					break;

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
			it->SetConfigData(node[section_name]);
		}
	}
}

void BoxerEngine::PreferenceManager::SaveConfigurationFile()
{
	YAML::Node output;
	for (auto it : preferences)
	{
		it->GetConfigData(output);
	}
	std::ofstream fout(CONFIG_PATH);
	fout << output;
}

Prefs* BoxerEngine::PreferenceManager::GetPreferenceDataByType(PreferenceType type) const
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
