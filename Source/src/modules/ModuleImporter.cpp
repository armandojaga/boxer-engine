#include "ModuleImporter.h"

#include <filesystem>
#include <algorithm>

#include "Application.h"
#include "core/events/EventManager.h"

#include "importers/GenericImporter.h"
#include "importers/MeshImporter.h"
#include "importers/SceneImporter.h"

ModuleImporter::ModuleImporter()
{
    BoxerEngine::GenericImporter* gen = new BoxerEngine::GenericImporter();
    BoxerEngine::MeshImporter* mesh = new BoxerEngine::MeshImporter();
    BoxerEngine::SceneImporter* scene = new BoxerEngine::SceneImporter();
    importers.push_back(std::make_pair<BoxerEngine::ImporterType, BoxerEngine::Importer*>(BoxerEngine::ImporterType::GENERIC, static_cast<BoxerEngine::Importer*>(gen)));
    importers.push_back(std::make_pair<BoxerEngine::ImporterType, BoxerEngine::Importer*>(BoxerEngine::ImporterType::MESH, static_cast<BoxerEngine::Importer*>(mesh)));
    importers.push_back(std::make_pair<BoxerEngine::ImporterType, BoxerEngine::Importer*>(BoxerEngine::ImporterType::MESH, static_cast<BoxerEngine::Importer*>(mesh)));
}

bool ModuleImporter::Init()
{
    preferences = static_cast<BoxerEngine::ResourcesPreferences*>(App->preferences->GetPreferenceDataByType(BoxerEngine::Preferences::Type::RESOURCES));

    std::function handleNewAsset = [&](BoxerEngine::Event& evt)
    {
        const auto& e = evt.GetEventData<BoxerEngine::AssetsChangedEventPayload>();
        std::filesystem::path file = e.GetPath();
        BE_LOG("Handling asset: %s, of type: %d", file.string().c_str(), e.GetType());
        ImportAsset(file, e.GetType());
    };
    BoxerEngine::EventManager::GetInstance().Subscribe(BoxerEngine::Event::Type::ASSETS_CHANGED, handleNewAsset);
    return true;
}

bool ModuleImporter::CleanUp()
{
    for (auto it : importers)
    {
        delete it.second;
    }

    return true;
}

void ModuleImporter::ImportAsset(const std::filesystem::path& asset_path, const BoxerEngine::ResourceType asset_type)
{
    auto it = std::find_if(importers.begin(), importers.end(),
        [&](const std::pair<BoxerEngine::ImporterType, BoxerEngine::Importer*>& element)
        { 
            return element.first == ToImporterType(asset_type);
        });
    
    it->second->ImportAsset(asset_path);
}

BoxerEngine::ImporterType ModuleImporter::ToImporterType(const BoxerEngine::ResourceType type)
{
    BoxerEngine::ImporterType iType;
    switch (type)
    {
    case BoxerEngine::ResourceType::MODEL:
        iType = BoxerEngine::ImporterType::SCENE;
        break;
    case BoxerEngine::ResourceType::TEXTURE:
    case BoxerEngine::ResourceType::AUDIO:
    case BoxerEngine::ResourceType::VIDEO:
    case BoxerEngine::ResourceType::SCRIPT:
    case BoxerEngine::ResourceType::UNKNOWN:
        iType = BoxerEngine::ImporterType::GENERIC;
    }
    return iType;
}
