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
			virtual void SetConfigData(const YAML::Node& input_node) = 0;
			virtual void GetConfigData(YAML::Node& output_node) = 0;
			virtual PreferenceType GetType() { return type; }

		private:
			PreferenceType type;
	};
}


