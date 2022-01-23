#pragma once

#include "Prefs.h"
#include "../file system/FileManager.h"

namespace BoxerEngine
{
	class EditorPrefs;
	//class RenderPrefs;

	class PreferenceManager
	{
		public:
			PreferenceManager();
			~PreferenceManager();
			void LoadConfigurationFile();
			Prefs* GetPreferenceDataByType(PreferenceType type);
			Prefs* GetEditorPreferences() const;

		private:
			std::vector<Prefs*> preferences;
			FileManager file_manager;
			std::vector<std::pair<std::string, std::string>> pref_data;

			EditorPrefs* editor;
			//RenderPrefs* render;
	};
}
