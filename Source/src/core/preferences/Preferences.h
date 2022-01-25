#pragma once

#include <yaml-cpp/yaml.h>

namespace BoxerEngine
{
    class Preferences
    {
    public:
        enum class Type
        {
            GLOBALS = 0,
            EDITOR,
            CAMERA,
            GAME,
            RENDER,
            COUNT // to know how many they are
        };

        Preferences(Type type) : type(type)
        {
        }

        virtual ~Preferences() = default;

        virtual void SetConfigurationData(const YAML::Node& node) = 0;
        virtual void GetConfigurationData(YAML::Node& node) = 0;
        virtual Type GetType() { return type; }
        [[nodiscard]] const std::string& GetGroupName() const { return group_name; }

    private:
        Type type;

    protected:
        std::string group_name = "";
    };
}
