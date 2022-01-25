#include "FileManager.h"
#include "../../Globals.h"
#include "core/events/Event.h"
#include "core/events/EventManager.h"
#include <functional>

using namespace BoxerEngine;

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

std::ifstream* FileManager::Load(std::filesystem::path file_path)
{
    rfile.open(file_path);
    return &rfile;
}

void FileManager::Save(std::ostream data, std::filesystem::path file_path)
{
}

void FileManager::Remove(const std::filesystem::path& source)
{
}

void FileManager::Copy(const std::filesystem::path& source, const std::filesystem::path& destination)
{
}

void FileManager::AppendToFile()
{
}
