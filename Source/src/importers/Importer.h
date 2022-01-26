#pragma once

namespace BoxerEngine
{
	class Importer
	{
	public:
		virtual ~Importer() = 0;
		virtual void ImportAsset() = 0;
	};
}
