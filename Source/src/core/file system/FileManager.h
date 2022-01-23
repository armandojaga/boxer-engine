#pragma once

#include <fstream>
#include <filesystem>

namespace BoxerEngine
{
	class FileManager
	{
		public:
			~FileManager();
			[[nodiscard]] std::ifstream* Load(std::filesystem::path file_path);
			void Save();
			void Remove();
			void Copy();
			void AppendToFile();
		private:
			std::ifstream rfile;
	};
}

