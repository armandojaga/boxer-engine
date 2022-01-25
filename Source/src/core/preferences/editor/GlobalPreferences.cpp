#include "GlobalPreferences.h"

using namespace BoxerEngine;

GlobalPreferences::GlobalPreferences() : Preferences(Type::GLOBALS)
{
    group_name = "globals";
}

void GlobalPreferences::SetConfigurationData(const YAML::Node& node)
{
    for (auto it = node.begin(); it != node.end(); ++it)
    {
        if (it->first.as<std::string>()._Equal("title"))
        {
            title = it->second.as<std::string>();
            continue;
        }

        if (it->first.as<std::string>()._Equal("version"))
        {
            version = it->second.as<std::string>();
        }
    }
}

void GlobalPreferences::GetConfigurationData(YAML::Node& node)
{
    node[group_name]["title"] = title;
    node[group_name]["version"] = version;
}
