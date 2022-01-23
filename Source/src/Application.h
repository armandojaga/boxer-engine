#pragma once

#include <list>
#include <memory>

#include "Globals.h"
#include "modules/Module.h"
#include "instrumentation/Statistics.h"
#include "core/preferences/PreferenceManager.h"

class ModuleWindow;
class ModuleInput;
class ModuleResources;
class ModuleProgram;
class ModuleTexture;
class ModuleCamera;
class ModuleEditor;
class ModuleRender;
class ModuleScene;
class ModuleDebugDraw;

class Application
{
public:
    Application();
    ~Application();

    bool Init();
    update_status Update();
    bool CleanUp();

public:
    ModuleWindow* window = nullptr;
    ModuleInput* input = nullptr;
    ModuleResources* resources = nullptr;
    ModuleProgram* program = nullptr;
    ModuleTexture* textures = nullptr;
    ModuleCamera* camera = nullptr;
    ModuleScene* scene = nullptr;
    ModuleRender* renderer = nullptr;
    ModuleDebugDraw* debug_draw = nullptr;
    ModuleEditor* editor = nullptr;

    std::unique_ptr<BoxerEngine::Statistics> statistics;
    std::unique_ptr<BoxerEngine::PreferenceManager> pref_manager;

    [[nodiscard]] float GetDelta() const
    {
        return delta;
    }

private:
    std::list<Module*> modules;
    float delta{0.0f};
    float prev{0.0f};
};

extern std::unique_ptr<Application> App;
