#pragma once

#include "Importer.h"

namespace BoxerEngine
{
	class MeshImporter : public Importer
	{
		~MeshImporter() override = default;
		void ImportAsset() override;
	};
}


