#pragma once

#include <filesystem>

#include "core/preferences/editor/ResourcesPreferences.h"

class YAML::Node;

namespace BoxerEngine
{
    class Importer
    {
    public:
        enum class Type
        {
            GENERIC = 0,
            SCENE,
            MODEL,
            MESH,
            TEXTURE,
            COUNT
        };

        Importer(const Type type) : type(type)
        {
        }

        virtual ~Importer() = default;

        [[nodiscard]] Type GetType() const { return type; }

        virtual void ImportAsset(const std::filesystem::path& asset_path) = 0;
        virtual void SaveToFile(YAML::Node& ticket, const std::string& file_name) {};

    protected:
        ResourcesPreferences* preferences = nullptr;
        Type type;
    };
}
