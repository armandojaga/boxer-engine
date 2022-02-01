#include "core/bepch.h"

#include "GenericImporter.h"

using namespace BoxerEngine;

GenericImporter::GenericImporter()
    : Importer(Type::GENERIC)
{
}

void GenericImporter::ImportAsset(const std::filesystem::path& asset_path)
{
    YAML::Node asset_ticket;
    asset_ticket["id"] = UUID::GenerateUUIDv4();
    asset_ticket["file_path"] = asset_path.string();

    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    std::string file_name = asset_path.filename().replace_extension().string();
    std::string model_name(preferences->GetLibraryPath(DeduceResourceType(asset_path)) + file_name);

    SaveToFile(asset_ticket, model_name);
}

void GenericImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    std::ofstream fout(file_name);
    fout << ticket;
}

ResourceType GenericImporter::DeduceResourceType(const std::filesystem::path& path)
{
    auto type = ResourceType::UNKNOWN;
    std::string extension = path.filename().extension().string();
    return type;
}
