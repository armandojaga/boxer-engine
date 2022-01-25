#pragma once
#include "../Preferences.h"
#include "modules/ModuleResources.h"

namespace BoxerEngine
{
	class ResourcesPreferences final : public Preferences
	{
	public:
		ResourcesPreferences();
		~ResourcesPreferences() override = default;
		void SetConfigurationData(const YAML::Node& node);
		void GetConfigurationData(YAML::Node& node);
		const char* GetResourcePath(ResourceType type);

	private:
		std::string meshes_path   = "./library/meshes/";
		std::string textures_path = "./library/textures/";
		std::string audio_path    = "./library/audio/";
		std::string video_path    = "./library/video/";
		std::string script_path   = "./library/scripts/";
	};
}


