#pragma once

#include <list>
#include <memory>
#include <string>

#include "Globals.h"
#include "Module.h"
#include "core/util/Cache.h"
#include "instrumentation/Statistics.h"
#include <functional>

class ModuleWindow;
class ModuleInput;
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
    ModuleCamera* camera = nullptr;
	ModuleScene* scene = nullptr;
    ModuleRender* renderer = nullptr;
	ModuleDebugDraw* debug_draw = nullptr;
	ModuleEditor* editor = nullptr;

	BoxerEngine::Statistics* statistics;
	// BoxerEngine::Cache<std::string, int> strCache([&](const std::string& key) {return key.size(); });

private:
	std::list<Module*> modules;
};

extern std::unique_ptr<Application> App;
