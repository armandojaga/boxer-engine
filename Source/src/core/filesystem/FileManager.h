#pragma once

#include <fstream>
#include <filesystem>

namespace BoxerEngine
{
    class FileManager
    {
    public:
        FileManager() = default;
        ~FileManager();
        [[nodiscard]] std::ifstream* Load(std::filesystem::path filePath);
        void Save(std::ostream data, std::filesystem::path filePath);
        void Remove(const std::filesystem::path& source);
        void Copy(const std::filesystem::path& source, const std::filesystem::path& destination);
        bool CopyNew(const std::filesystem::path& source, const std::filesystem::path& destination);
        bool CreatePathIfNew(const std::filesystem::path& path);
        bool CreateFileIfNew(const std::filesystem::path& file_path);
        void AppendToFile();

    private:
        std::ifstream rfile;
        std::filesystem::path file_path;
    };
}
