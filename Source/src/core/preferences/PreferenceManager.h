#pragma once

#include "Prefs.h"
#include "../file system/FileManager.h"

namespace BoxerEngine
{
	class GlobalPrefs;
	class EditorPrefs;
	class RenderPrefs;
	class CameraPrefs;

	class PreferenceManager
	{
		public:
			PreferenceManager();
			~PreferenceManager();
			void LoadConfigurationFile();
			void SaveConfigurationFile();
			Prefs* GetPreferenceDataByType(PreferenceType type) const;
			Prefs* GetEditorPreferences() const;

		private:
			std::vector<Prefs*> preferences;
			std::vector<YAML::Node> nodes_vec = YAML::LoadAllFromFile(CONFIG_PATH);
			FileManager file_manager;

			GlobalPrefs* globals;
			EditorPrefs* editor;
			RenderPrefs* render;
			CameraPrefs* camera;
	};
}
