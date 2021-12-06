#include "Application.h"

#include "modules/ModuleWindow.h"
#include "modules/ModuleInput.h"
#include "modules/ModuleCamera.h"
#include "modules/ModuleScene.h"
#include "modules/ModuleRender.h"
#include "modules/ModuleDebugDraw.h"
#include "modules/ModuleEditor.h"

using namespace std;

Application::Application() : statistics(std::make_unique<BoxerEngine::Statistics>())
{
    // Order matters: they will Init/start/update in this order
    modules.push_back(window = new ModuleWindow());
    modules.push_back(input = new ModuleInput());
    modules.push_back(camera = new ModuleCamera());
    modules.push_back(scene = new ModuleScene());
    modules.push_back(renderer = new ModuleRender());
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

    return ret;
}

update_status Application::Update()
{
    update_status ret = UPDATE_CONTINUE;

    for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->PreUpdate();
    }

    for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->Update();
    }

    for (auto it = modules.begin(); it != modules.end() && ret == UPDATE_CONTINUE; ++it)
    {
        ret = (*it)->PostUpdate();
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

    return ret;
}
