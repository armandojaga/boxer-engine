#pragma once

namespace BoxerEngine
{
	enum class ImporterType
	{
		GENERIC = 0,
		MESH,
		COUNT
	};

	class Importer
	{
	public:
		virtual ~Importer() = 0;
		virtual void ImportAsset(const std::filesystem::path& asset_path) = 0;
	};
}
