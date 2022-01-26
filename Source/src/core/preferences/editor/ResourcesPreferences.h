#pragma once
#include "../Preferences.h"

namespace BoxerEngine
{
	enum class ResourceType
	{
		MODEL = 1,
		TEXTURE,
		AUDIO,
		VIDEO,
		SCRIPT,
		UNKNOWN
	};

	class ResourcesPreferences final : public Preferences
	{
	public:
		ResourcesPreferences();
		~ResourcesPreferences() override = default;
		void SetConfigurationData(const YAML::Node& node);
		void GetConfigurationData(YAML::Node& node);
		[[nodiscard]] const char* GetResourcePath(ResourceType type);

	private:
		std::string meshes_path   = "./assets/meshes/";
		std::string textures_path = "./assets/textures/";
		std::string audio_path    = "./assets/audio/";
		std::string video_path    = "./assets/video/";
		std::string script_path   = "./assets/scripts/";
	};
}


