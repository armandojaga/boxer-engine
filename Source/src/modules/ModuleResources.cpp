#include "ModuleResources.h"

#include "Application.h"
#include "ModuleRender.h"
#include "core/events/EventManager.h"

using namespace BoxerEngine;

bool ModuleResources::Init()
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>
        (App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));
    
    // create assets & library directory tree
    for (int i = 0; i < (int)ResourceType::UNKNOWN; ++i)
    {
        file_manager.CreatePathIfNew(preferences->GetLibraryPath(static_cast<ResourceType>(i)));
        file_manager.CreatePathIfNew(preferences->GetAssetsPath(static_cast<ResourceType>(i)));
    }
    
        std::function handleAddedFile = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<FileAddedEventPayload>();
        std::filesystem::path file = e.GetPath();
        BE_LOG("Handling dropped file: %s", file.string().c_str());
        HandleResource(file);
    };
    EventManager::GetInstance().Subscribe(Event::Type::FILE_ADDED, handleAddedFile);

    return true;
}

bool ModuleResources::CleanUp()
{
    return Module::CleanUp();
}

std::filesystem::path ModuleResources::GetLastResourceLoadedPath() const
{
    return last_resource_path;
}

void ModuleResources::HandleResource(const std::filesystem::path& path)
{
    ResourceType type = GetType(path);
    if (type == ResourceType::UNKNOWN)
    {
        BE_LOG("Unknown resource type recevied, nothing to be done");
        return;
    }
    std::filesystem::path destination = preferences->GetAssetsPath(type);

    if (file_manager.CopyNew(path, destination.append(path.filename().c_str())))
    {
        last_resource_path = path; // We may need this to import more assets from this path
        HandleAssetsChanged(destination, type);
    }

    BE_LOG("File destination: %s", destination.string().c_str());
}

ResourceType ModuleResources::GetType(const std::filesystem::path& path)
{
    if (!path.has_extension())
    {
        return ResourceType::UNKNOWN;
    }
    const std::filesystem::path extension = path.extension();

    auto isValidExtension = [&](const std::pair<ResourceType, std::string>& element)
    {
        return element.second.size() == extension.string().size() &&
            std::equal(element.second.begin(), element.second.end(), extension.string().begin(),
                       [](auto a, auto b) { return std::tolower(a) == std::tolower(b); });
    };

    const auto it = std::find_if(supported_extensions.begin(), supported_extensions.end(), isValidExtension);
    if (it != supported_extensions.end())
    {
        return it->first;
    }
    return ResourceType::UNKNOWN;
}

void ModuleResources::HandleAssetsChanged(const std::filesystem::path& asset_path, const ResourceType asset_type)
{
    BoxerEngine::Event assetChanged(BoxerEngine::Event::Type::ASSETS_CHANGED);
    assetChanged.SetEventData<BoxerEngine::AssetsAddedEventPayload>(asset_path, asset_type);
    BoxerEngine::EventManager::GetInstance().Publish(assetChanged);
}