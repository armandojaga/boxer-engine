#include "ModuleResources.h"

#include "Application.h"
#include "ModuleRender.h"
#include "core/util/Files.h"
#include "core/events/Event.h"
#include "core/events/EventManager.h"
#include "core/file system/FileManager.h"

// #include <algorithm>
using namespace BoxerEngine;

bool ModuleResources::Init()
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetEditorPreferences());

    std::function handleAddedFile = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<FileDroppedEventPayload>();
        BE_LOG("File dropped: %s", e.GetPath().c_str());
        HandleResource(e.GetPath());
    };
    EventManager::GetInstance().Subscribe(Event::Type::FILE_DROPPED, handleAddedFile);

    return true;
}

bool ModuleResources::CleanUp()
{
    return Module::CleanUp();
}

void ModuleResources::HandleResource(const std::filesystem::path& path)
{
    ResourceType type = GetType(path);
    switch (type)
    {
    case ResourceType::MODEL:
        break;
    case ResourceType::TEXTURE:
        break;
    case ResourceType::AUDIO:
        break;
    case ResourceType::VIDEO:
        break;
    case ResourceType::SCRIPT:
        break;
    }

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
