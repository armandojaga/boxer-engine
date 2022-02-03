#pragma once

#include "Importer.h"

namespace BoxerEngine
{
    // As this is a generic importer we have to deduce the resource type
    // to properly deliver it. In the future this class is going to be 
    // replaced for each importer implementation is cover here
    class GenericImporter : public Importer
    {
    public:
        GenericImporter();
        ~GenericImporter() override = default;
        void ImportAsset(const std::filesystem::path& assetPath) override;
        void SaveToFile(YAML::Node& ticket, const std::string& fileName) override;
    private:
        static ResourceType DeduceResourceType(const std::filesystem::path& path);
    };
}
