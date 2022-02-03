#include "core/bepch.h"

#include "GenericImporter.h"

using namespace BoxerEngine;

GenericImporter::GenericImporter()
    : Importer(Type::GENERIC)
{
}

void GenericImporter::ImportAsset(const std::filesystem::path& assetPath)
{
    YAML::Node asset_ticket;
    asset_ticket[GENERIC_ID] = UUID::GenerateUUIDv4();
    asset_ticket[GENERIC_FILE_PATH] = assetPath.string();

    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    const std::string fileName = assetPath.filename().replace_extension().string();
    const std::string modelName(preferences->GetLibraryPath(DeduceResourceType(assetPath)) + fileName);

    SaveToFile(asset_ticket, modelName);
}

void GenericImporter::SaveToFile(YAML::Node& ticket, const std::string& fileName)
{
    std::ofstream fout(fileName);
    fout << ticket;
}

ResourceType GenericImporter::DeduceResourceType(const std::filesystem::path& path)
{
    return ResourceType::UNKNOWN;
}
