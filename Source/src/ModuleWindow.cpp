#include "Globals.h"
#include "Application.h"
#include "ModuleWindow.h"

ModuleWindow::ModuleWindow()
{
}

// Destructor
ModuleWindow::~ModuleWindow() = default;

// Called before render is available
bool ModuleWindow::Init()
{
    BE_LOG("Init SDL window & surface");
    bool ret = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        BE_LOG("SDL_VIDEO could not initialize! SDL_Error: %s\n", SDL_GetError());
        ret = false;
    }
    else
    {
        //Create window
        constexpr int width = SCREEN_WIDTH;
        constexpr int height = SCREEN_HEIGHT;
        Uint32 flags = SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI;

        if (game_options.IsFullScreen())
        {
            flags |= SDL_WINDOW_FULLSCREEN;
        }

        window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, flags);

        if (window == nullptr)
        {
            BE_LOG("Window could not be created! SDL_Error: %s\n", SDL_GetError());
            ret = false;
        }
    }

    return ret;
}

// Called before quitting
bool ModuleWindow::CleanUp()
{
    BE_LOG("Destroying SDL window and quitting all SDL systems");

    //Destroy window
    if (window != nullptr)
    {
        SDL_DestroyWindow(window);
    }

    //Quit SDL subsystems
    SDL_Quit();
    return true;
}

update_status ModuleWindow::PreUpdate()
{
    if (game_options.IsFullScreen())
    {
        SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    }
    else
    {
        SDL_SetWindowFullscreen(window, 0);
    }
    return UPDATE_CONTINUE;
}
