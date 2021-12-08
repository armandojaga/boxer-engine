#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include <SDL.h>

#include "ModuleResources.h"
#include "core/util/Files.h"

ModuleInput::ModuleInput()
{
}

// Destructor
ModuleInput::~ModuleInput()
{
}

// Called before render is available
bool ModuleInput::Init()
{
    BE_LOG("Init SDL input event system");
    bool ret = true;
    SDL_Init(0);

    if (SDL_InitSubSystem(SDL_INIT_EVENTS) < 0)
    {
        BE_LOG("SDL_EVENTS could not initialize! SDL_Error: %s\n", SDL_GetError());
        ret = false;
    }

    return ret;
}

// Called every draw update
update_status ModuleInput::PreUpdate()
{
    SDL_Event sdlEvent;

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return update_status::UPDATE_STOP;
        case SDL_WINDOWEVENT:
            if (sdlEvent.window.event == SDL_WINDOWEVENT_RESIZED || sdlEvent.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
            {
                // App->renderer->Resize(sdlEvent.window.data1, sdlEvent.window.data2);
            }
            break;
        case SDL_DROPFILE:
            char* file = sdlEvent.drop.file;
            BE_LOG("Dropped file %s", file);
            App->resources->HandleResource(file);
            SDL_free(file);
            break;
        }
    }

    keyboard = SDL_GetKeyboardState(nullptr);

    return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    BE_LOG("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}
