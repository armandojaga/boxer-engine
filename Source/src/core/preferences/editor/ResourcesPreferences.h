#pragma once
#include "../Preferences.h"

namespace BoxerEngine
{
	enum class ResourceType
	{
		SCENE = 1,
		MESH,
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
		[[nodiscard]] const char* GetAssetsPath(ResourceType type);
		[[nodiscard]] const char* GetLibraryPath(ResourceType type);

	private:
		std::string scene_assets   = "./assets/scene/";
		std::string meshes_assets   = "./assets/meshes/";
		std::string textures_assets = "./assets/textures/";
		std::string audio_assets = "./assets/audio/";
		std::string video_assets = "./assets/video/";
		std::string script_assets = "./assets/scripts/";

		std::string scene_library   = "./library/scene/";
		std::string meshes_library   = "./library/meshes/";
		std::string textures_library = "./library/textures/";
		std::string audio_library = "./library/audio/";
		std::string video_library = "./library/video/";
		std::string script_library = "./library/scripts/";
	};
}


