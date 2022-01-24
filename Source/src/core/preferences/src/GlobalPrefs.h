#pragma once

#include "../Prefs.h"

namespace BoxerEngine
{
	class GlobalPrefs final : public Prefs
	{
    public:
        GlobalPrefs();
        ~GlobalPrefs() = default;
        void SetConfigData(const YAML::Node & yNode) override;
        void GetConfigData(YAML::Node & output_node) override;

    private:
        std::string title = "Boxer Engine";
        std::string version = "v1.0";
	};
}

