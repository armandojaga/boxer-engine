#include "core/bepch.h"
#include "SceneImporter.h"
#include "modules/ModuleScene.h"

using namespace BoxerEngine;

SceneImporter::SceneImporter()
    : Importer(Type::SCENE)
{
}

void SceneImporter::ImportAsset(const std::filesystem::path& asset_path)
{
    //App->scene->LoadScene(asset_path.string().c_str());
}
