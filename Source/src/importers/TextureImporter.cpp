
#include "TextureImporter.h"
#include "Application.h"
#include "modules/ModuleTexture.h"

#include <filesystem>
#include <fstream>

#include "core/util/UUID.h"
#include "core/util/StringUtils.h"
#include "core/util/Files.h"
#include "core/events/EventManager.h"
#include "core/events/Event.h"

using namespace BoxerEngine;

void TextureImporter::ImportAsset(const std::filesystem::path& asset_path)
{
    YAML::Node asset_ticket;
    asset_ticket["id"] = UUID::GenerateUUIDv4();
    asset_ticket["file_path"] = asset_path.string();

    std::string file_name = asset_path.filename().replace_extension().string();
    SaveToFile(asset_ticket, file_name);
}

void TextureImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));

    std::string texture_path(preferences->GetLibraryPath(ResourceType::TEXTURE) + file_name);
    std::ofstream fout(texture_path);
    fout << ticket;
}

void BoxerEngine::TextureImporter::ImportMaterial(aiMaterial* material, const std::string& uuid, const std::filesystem::path& model_path)
{
    YAML::Node material_ticket;
    material_ticket["id"] = uuid;
    ImportTexturesByType(material, aiTextureType::aiTextureType_DIFFUSE, material_ticket, model_path);
    ImportTexturesByType(material, aiTextureType::aiTextureType_SPECULAR, material_ticket, model_path);
    ImportTexturesByType(material, aiTextureType::aiTextureType_NORMALS, material_ticket, model_path);
    ImportTexturesByType(material, aiTextureType::aiTextureType_AMBIENT_OCCLUSION, material_ticket, model_path);
    SaveToFile(material_ticket, uuid);
}

void BoxerEngine::TextureImporter::ImportTexturesByType(aiMaterial* material, aiTextureType type, YAML::Node& ticket, const std::filesystem::path& model_path)
{
    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        FindTextureLocation(str.C_Str(), model_path.string().c_str());
        ticket["texture"][TextureTypeToString(type)][i]["texture_name"] = str.C_Str();
    }
}

std::string BoxerEngine::TextureImporter::TextureTypeToString(aiTextureType type)
{
    switch (type)
    {
    case aiTextureType_NONE:
        return "none";
    case aiTextureType_DIFFUSE:
        return "diffuse";
    case aiTextureType_SPECULAR:
        return "specular";
    case aiTextureType_AMBIENT:
        return "ambient";
    case aiTextureType_EMISSIVE:
        return "emissive";
    case aiTextureType_HEIGHT:
         return "height";
    case aiTextureType_NORMALS:
        return "normals";
    case aiTextureType_SHININESS:
        return "shininess";
    case aiTextureType_OPACITY:
        return "opacity";
    case aiTextureType_DISPLACEMENT:
        return "displacement";
    case aiTextureType_LIGHTMAP:
        return "lightmap";
    case aiTextureType_REFLECTION:
        return "reflection";
    case aiTextureType_BASE_COLOR:
        return "base_color";
    case aiTextureType_NORMAL_CAMERA:
        return "normal_camera";
    case aiTextureType_EMISSION_COLOR:
        return "emission_color";
    case aiTextureType_METALNESS:
        return "metalness";
    case aiTextureType_DIFFUSE_ROUGHNESS:
        return "diffuse_roughness";
    case aiTextureType_AMBIENT_OCCLUSION:
        return "ambient_occlusion";
    case aiTextureType_UNKNOWN:
        return "unknown";
    case _aiTextureType_Force32Bit:
        return "force_32bit";
    }
}

std::filesystem::path BoxerEngine::TextureImporter::FindTextureLocation(const char* texture, const char* model_path)
{
    const std::filesystem::path textPath = texture;
    std::filesystem::path relativePath;
    std::string output_path;
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));

    if (model_path)
    {
        const std::filesystem::path model = model_path;
        relativePath = BoxerEngine::StringUtils::Concat(model.string(), "./", texture);
    }

    // First check if texture is already loaded in assets folder
    
    const std::filesystem::path projectTexture = 
        preferences->GetAssetsPath(BoxerEngine::ResourceType::TEXTURE) + textPath.filename().string();

    if (BoxerEngine::Files::IsValidFilePath(projectTexture))
    {
        output_path = projectTexture.string();
    }
    //use path in model. If succed notify the event
    else if (BoxerEngine::Files::IsValidFilePath(texture))
    {
        AddFileToAssetsFolder(texture);
        output_path = texture;
    }
    //use relative path to model. If succed notify the event
    else if (BoxerEngine::Files::IsValidFilePath(absolute(relativePath)))
    {
        AddFileToAssetsFolder(relativePath.string().c_str());
        output_path = absolute(relativePath).string();
    }

    return output_path;
}

void BoxerEngine::TextureImporter::AddFileToAssetsFolder(const char* path)
{
    BoxerEngine::Event fileDropped(BoxerEngine::Event::Type::FILE_ADDED);
    fileDropped.SetEventData<BoxerEngine::FileAddedEventPayload>(path);
    BoxerEngine::EventManager::GetInstance().Publish(fileDropped);
}