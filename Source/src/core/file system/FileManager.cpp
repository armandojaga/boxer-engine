#include "FileManager.h"

using namespace BoxerEngine;

BoxerEngine::FileManager::~FileManager()
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

void FileManager::Remove()
{
}

void FileManager::Copy()
{
}

void FileManager::AppendToFile()
{
}
