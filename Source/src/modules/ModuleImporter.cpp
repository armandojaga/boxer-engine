#include "ModuleImporter.h"

#include <filesystem>

#include "Application.h"
#include "core/events/EventManager.h"
#include "core/preferences/editor/ResourcesPreferences.h"

using namespace BoxerEngine;

ModuleImporter::ModuleImporter()
{
}

bool ModuleImporter::Init()
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(Preferences::Type::RESOURCES));

    std::function handleAddedFile = [&](Event& evt)
    {
        const auto& e = evt.GetEventData<AssetsChangedEventPayload>();
        std::filesystem::path file = e.GetPath();
        BE_LOG("Handling asset: %s, of type: %d", file.string().c_str(), e.GetType());
    };
    EventManager::GetInstance().Subscribe(Event::Type::FILE_ADDED, handleAddedFile);
    return true;
}

bool ModuleImporter::CleanUp()
{
    return Module::CleanUp();
}
