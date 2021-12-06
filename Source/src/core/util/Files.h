#pragma once
#include <filesystem>
#include <fstream>
#include <string>

class Files
{
public:

    static std::string ReadFile(const std::filesystem::path path)
    {
        std::ifstream f(path, std::ios::in | std::ios::binary);

        // Obtain the size of the file.
        const auto sz = file_size(path);

        // Create a buffer.
        std::string result(sz, '\0');

        // Read the whole file into the buffer.
        f.read(result.data(), static_cast<long long>(sz));
        f.close();

        return result;
    }
};
