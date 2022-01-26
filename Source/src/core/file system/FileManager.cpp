#include "FileManager.h"

#include <functional>

#include "../../Globals.h"
#include "core/events/EventManager.h"

using namespace BoxerEngine;
namespace fs = std::filesystem;

BoxerEngine::FileManager::FileManager()
{
}

FileManager::~FileManager()
{
    if (rfile.is_open())
    {
        rfile.close();
    }
}

std::ifstream* FileManager::Load(fs::path file_path)
{
    rfile.open(file_path);
    return &rfile;
}

void FileManager::Save(std::ostream data, fs::path file_path)
{
}

void FileManager::Remove(const fs::path& source)
{
}

void FileManager::Copy(const fs::path& source, const fs::path& destination)
{
    fs::copy(source, destination);
}

bool BoxerEngine::FileManager::CopyNew(const fs::path& source, const fs::path& destination)
{
    if (fs::exists(destination))
    {
        return false;
    }

    if (!fs::exists(destination.parent_path()) && 
        !fs::create_directories(destination.parent_path()))
    {
        return false;
    }

    fs::copy(source, destination);
    return true;
}

void FileManager::AppendToFile()
{
}
