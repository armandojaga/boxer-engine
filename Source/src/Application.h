#pragma once

#include <list>
#include <vector>

#include "Globals.h"
#include "Module.h"
#include "Timer.h"
#include "instrumentation/Statistics.h"

class ModuleCamera;
class ModuleEditor;
class ModuleRender;
class ModuleWindow;
class ModuleTextures;
class ModuleInput;
class ModuleRenderExercise;

class Application
{
public:
	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

public:
	ModuleRender* renderer = nullptr;
	ModuleWindow* window = nullptr;
	ModuleInput* input = nullptr;
	ModuleEditor* editor = nullptr;
	ModuleCamera* camera = nullptr;
	BoxerEngine::Statistics* statistics;

private:
	std::list<Module*> modules;
};

extern Application* App;
