#include "Application.h"

#include "modules/ModuleWindow.h"
#include "modules/ModuleInput.h"
#include "modules/ModuleProgram.h"
#include "modules/ModuleTexture.h"
#include "modules/ModuleCamera.h"
#include "modules/ModuleScene.h"
#include "modules/ModuleRender.h"
#include "modules/ModuleDebugDraw.h"
#include "modules/ModuleEditor.h"
#include "modules/ModuleResources.h"
#include "modules/ModuleImporter.h"

using namespace std;

Application::Application()
    : statistics(std::make_unique<BoxerEngine::Statistics>())
      , preferences(std::make_unique<BoxerEngine::PreferenceManager>())
{
    // Order matters: they will Init/start/update in this order
    modules.push_back(window = new ModuleWindow());
    modules.push_back(input = new ModuleInput());
    modules.push_back(textures = new ModuleTexture());
    modules.push_back(renderer = new ModuleRender());
    modules.push_back(program = new ModuleProgram());
    modules.push_back(resources = new ModuleResources());
    modules.push_back(importer = new ModuleImporter());
    modules.push_back(camera = new ModuleCamera());
    modules.push_back(scene = new ModuleScene());
    modules.push_back(debug_draw = new ModuleDebugDraw());
    modules.push_back(editor = new ModuleEditor());
}

Application::~Application()
{
    for (auto it = modules.begin(); it != modules.end(); ++it)
    {
        delete *it;
    }
}

bool Application::Init()
{
    bool ret = true;

    for (auto it = modules.begin(); it != modules.end() && ret; ++it)
    {
        ret = (*it)->Init();
    }

    for (auto it = modules.begin(); it != modules.end() && ret; ++it)
    {
        ret = (*it)->Start();
    }

    delta = 0.0f;
    prev = game_clock.ReadMs();
    return ret;
}

update_status Application::Update()
{
    const float current = game_clock.ReadMs();
    delta = (current - prev) / 1000.0f;
    prev = current;

    auto ret = update_status::UPDATE_CONTINUE;

    for (auto it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->PreUpdate(delta);
    }

    for (auto it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->Update(delta);
    }

    for (auto it = modules.begin(); it != modules.end() && ret == update_status::UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->PostUpdate(delta);
    }

    return ret;
}

bool Application::CleanUp()
{
    bool ret = true;

    for (auto it = modules.rbegin(); it != modules.rend() && ret; ++it)
    {
        ret = (*it)->CleanUp();
    }

    preferences->SaveConfigurationFile();

    return ret;
}
