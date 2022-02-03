#include "FileManager.h"

#include "core/util/Files.h"
#include "core/events/EventManager.h"


BoxerEngine::FileManager::~FileManager()
{
    if (rfile.is_open())
    {
        rfile.close();
    }
}

std::ifstream* BoxerEngine::FileManager::Load(std::filesystem::path filePath)
{
    rfile.open(filePath);
    return &rfile;
}

void BoxerEngine::FileManager::Save(std::ostream data, std::filesystem::path filePath)
{
}

void BoxerEngine::FileManager::Remove(const std::filesystem::path& source)
{
}

void BoxerEngine::FileManager::Copy(const std::filesystem::path& source, const std::filesystem::path& destination)
{
    copy(source, destination);
}

bool BoxerEngine::FileManager::CopyNew(const std::filesystem::path& source, const std::filesystem::path& destination)
{
    if (exists(destination))
    {
        return false;
    }

    if (!exists(destination.parent_path()) &&
        !create_directories(destination.parent_path()))
    {
        return false;
    }

    copy(source, destination);
    return true;
}

bool BoxerEngine::FileManager::CreatePathIfNew(const std::filesystem::path& path)
{
    return exists(path) || create_directories(path);
}

bool BoxerEngine::FileManager::CreateFileIfNew(const std::filesystem::path& file_path)
{
    if (Files::IsValidFilePath(file_path))
    {
        return true;
    }

    if (!CreatePathIfNew(file_path.parent_path()))
    {
        return false;
    }

    std::ofstream file(file_path);
    file.close();
    return true;
}

void BoxerEngine::FileManager::AppendToFile()
{
}
