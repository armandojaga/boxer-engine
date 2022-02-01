#pragma once

#include "core/preferences/editor/ResourcesPreferences.h"

namespace BoxerEngine
{
    struct AssetsAddedEventPayload
    {
        AssetsAddedEventPayload(const std::filesystem::path& path, ResourceType type)
            : path(path)
              , type(type)
        {
        }

        [[nodiscard]] std::filesystem::path GetPath() const
        {
            return path;
        }

        [[nodiscard]] ResourceType GetType() const
        {
            return type;
        }

    private:
        std::filesystem::path path;
        ResourceType type;
    };
}
