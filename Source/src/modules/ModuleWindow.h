#ifndef __ModuleWindow_H__
#define __ModuleWindow_H__

#include "Module.h"
#include <SDL.h>
#include "core/preferences/editor/EditorPreferences.h"

class Application;

class ModuleWindow : public Module
{
public:
    ModuleWindow();

    // Destructor
    ~ModuleWindow() override;

    // Called before quitting
    bool Init() override;

    // Called before quitting
    bool CleanUp() override;

    update_status PreUpdate(float delta) override;

public:
    //The window we'll be rendering to
    SDL_Window* window = nullptr;
private:
    BoxerEngine::EditorPreferences* prefs = nullptr;
};

#endif // __ModuleWindow_H__
