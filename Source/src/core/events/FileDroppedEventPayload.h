#pragma once

struct FileDroppedEventPayload
{
    FileDroppedEventPayload(const std::filesystem::path& path) : path(path)
    {
    }

    [[nodiscard]] std::filesystem::path GetPath() const
    {
        return path;
    }

private:
    std::filesystem::path path;
};
