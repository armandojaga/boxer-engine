#include "core/bepch.h"

#include "TextureImporter.h"
#include "modules/ModuleResources.h"

using namespace BoxerEngine;

TextureImporter::TextureImporter()
    : Importer(Type::TEXTURE)
{
}

void TextureImporter::ImportAsset(const std::filesystem::path& asset_path)
{
    YAML::Node asset_ticket;
    std::filesystem::path texture;
    
    if (!asset_path.has_extension())
    {
        texture = FindTextureInAssets(asset_path.string().c_str());
    }
    else
    {
        texture = asset_path;
    }
    
    asset_ticket[TEXTURE_ID] = UUID::GenerateUUIDv4();
    asset_ticket[TEXTURE_FILE_PATH] = texture.string();

    std::string file_name = texture.filename().replace_extension().string();
    SaveToFile(asset_ticket, file_name);
}

void TextureImporter::SaveToFile(YAML::Node& ticket, const std::string& file_name)
{
    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));

    std::string texture_path(preferences->GetLibraryPath(ResourceType::TEXTURE) + file_name);
    std::ofstream fout(texture_path);
    fout << ticket;
}

void TextureImporter::ImportMaterial(aiMaterial* material, const std::string& uuid)
{
    YAML::Node material_ticket;
    material_ticket["id"] = uuid;
    ImportTexturesByType(material, aiTextureType_DIFFUSE, material_ticket);
    ImportTexturesByType(material, aiTextureType_SPECULAR, material_ticket);
    ImportTexturesByType(material, aiTextureType_NORMALS, material_ticket);
    ImportTexturesByType(material, aiTextureType_AMBIENT_OCCLUSION, material_ticket);
    SaveToFile(material_ticket, uuid);
}

void TextureImporter::ImportTexturesByType(aiMaterial* material, aiTextureType type, YAML::Node& ticket)
{
    preferences = static_cast<ResourcesPreferences*>
        (App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    std::string asset_path = preferences->GetAssetsPath(ResourceType::TEXTURE);

    for (unsigned int i = 0; i < material->GetTextureCount(type); i++)
    {
        aiString str;
        material->GetTexture(type, i, &str);
        FindTextureLocation(str.C_Str());
        std::filesystem::path texture_path(str.C_Str());
        ticket["texture"][TextureTypeToString(type)][i]["texture_name"] = texture_path.filename().string();
    }
}

std::string TextureImporter::TextureTypeToString(aiTextureType type)
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

std::filesystem::path TextureImporter::FindTextureLocation(const char* texture)
{
    const std::filesystem::path texture_path = texture;
    std::filesystem::path relative_path = App->resources->GetLastResourceLoadedPath().parent_path().append(texture_path.filename().string());
    std::string output_path;
    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));

    // First check if texture is already loaded in assets folder
    const std::filesystem::path project_texture_path =
        preferences->GetAssetsPath(ResourceType::TEXTURE) + texture_path.filename().string();

    if (Files::IsValidFilePath(project_texture_path))
    {
        output_path = project_texture_path.string();
    }
    //use path in model. If succed notify the event
    else if (Files::IsValidFilePath(texture))
    {
        NotifyAddedFile(texture);
        output_path = texture;
    }
    //use relative path to model. If succed notify the event
    else if (Files::IsValidFilePath(relative_path))
    {
        NotifyAddedFile(relative_path.string().c_str());
        output_path = relative_path.string();
    }

    return output_path;
}

std::filesystem::path BoxerEngine::TextureImporter::FindTextureInAssets(const char* texture)
{
    preferences = static_cast<ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    for (auto& directory_entry : std::filesystem::directory_iterator(preferences->GetAssetsPath(ResourceType::TEXTURE)))
    {
        if (directory_entry.is_directory())
        {
            continue;
        }

        if (directory_entry.path().filename().replace_extension().string()._Equal(texture))
        {
            return directory_entry.path();
        }
    }
    return std::filesystem::path();
}

void TextureImporter::NotifyAddedFile(const char* path)
{
    Event fileDropped(Event::Type::FILE_ADDED);
    fileDropped.SetEventData<FileAddedEventPayload>(path);
    EventManager::GetInstance().Publish(fileDropped);
}
