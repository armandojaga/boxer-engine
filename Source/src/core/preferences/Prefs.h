#pragma once

#include <yaml-cpp/yaml.h>

namespace BoxerEngine
{
	enum class PreferenceType
	{
		EDITOR,
		CAMERA,
		GAME,
		RENDER,
		TYPES_AMOUNT	// to know how much they are
	};

	class Prefs
	{
		public:
			Prefs(PreferenceType pType) { type = pType; }
			virtual ~Prefs() = default;
			virtual void LoadConfig(const YAML::Node& yNode) = 0;
			virtual void SaveConfig() = 0;
			virtual PreferenceType GetType() { return type; }

		private:
			PreferenceType type;
	};
}


