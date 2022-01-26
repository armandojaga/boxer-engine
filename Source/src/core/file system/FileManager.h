#pragma once

#include <fstream>
#include <filesystem>

#include "core/util/Files.h"

namespace BoxerEngine
{
    class FileManager
    {
    public:
        FileManager();
        ~FileManager();
        [[nodiscard]] std::ifstream* Load(std::filesystem::path file_path);
        void Save(std::ostream data, std::filesystem::path file_path);
        void Remove(const std::filesystem::path& source);
        void Copy(const std::filesystem::path& source, const std::filesystem::path& destination);
        bool CopyNew(const std::filesystem::path& source, const std::filesystem::path& destination);
        void AppendToFile();

    private:
        std::ifstream rfile;
        std::filesystem::path file_path;
    };
}
