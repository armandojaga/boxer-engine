#pragma once

#include "core/preferences/editor/ResourcesPreferences.h"

namespace BoxerEngine
{
    struct AssetsAddedEventPayload
    {
        AssetsAddedEventPayload(const std::filesystem::path& path, BoxerEngine::ResourceType type)
            : path(path)
            , type(type)
        {
        }

        [[nodiscard]] std::filesystem::path GetPath() const
        {
            return path;
        }

        [[nodiscard]] BoxerEngine::ResourceType GetType() const
        {
            return type;
        }

    private:
        std::filesystem::path path;
        BoxerEngine::ResourceType type;
    };
}
