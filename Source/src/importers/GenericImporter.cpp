#include "GenericImporter.h"
#include "Application.h"

#include <filesystem>
#include <fstream>

#include "core/util/UUID.h"

using namespace BoxerEngine;

void GenericImporter::ImportAsset(const std::filesystem::path& asset_path)
{
    YAML::Node asset_ticket;
    asset_ticket["id"] = UUID::GenerateUUIDv4();
    asset_ticket["file_path"] = asset_path.string();

    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));
    std::string file_name = asset_path.filename().replace_extension().string();
    std::string model_name(preferences->GetLibraryPath(DeduceResourceType(asset_path)) + file_name);

    SaveToFile(asset_ticket, model_name);
}

void GenericImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    std::ofstream fout(file_name);
    fout << ticket;
}

ResourceType BoxerEngine::GenericImporter::DeduceResourceType(const std::filesystem::path& path)
{
    ResourceType type = ResourceType::UNKNOWN;
    std::string extension = path.filename().extension().string();
    return type;
}
