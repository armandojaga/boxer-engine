#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include <SDL.h>

#include "ModuleResources.h"
#include "core/util/Files.h"

constexpr int MAX_KEYS = 300;

ModuleInput::ModuleInput()
{
    keyboard = new KeyState[MAX_KEYS];
    memset(keyboard, 0, sizeof(KeyState) * MAX_KEYS);
    memset(mouse_buttons, 0, sizeof(KeyState) * NUM_MOUSE_BUTTONS);
}

// Destructor
ModuleInput::~ModuleInput()
{
    if (keyboard != nullptr)
    {
        delete[] keyboard;
        keyboard = nullptr;
    }
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

    mouse_motion = {0, 0};

    const Uint8* keys = SDL_GetKeyboardState(nullptr);

    for (int i = 0; i < MAX_KEYS; ++i)
    {
        if (keys[i] == 1)
        {
            if (keyboard[i] == KeyState::KEY_IDLE)
            {
                keyboard[i] = KeyState::KEY_DOWN;
            }
            else
            {
                keyboard[i] = KeyState::KEY_REPEAT;
            }
        }
        else
        {
            if (keyboard[i] == KeyState::KEY_REPEAT || keyboard[i] == KeyState::KEY_DOWN)
            {
                keyboard[i] = KeyState::KEY_UP;
            }
            else
            {
                keyboard[i] = KeyState::KEY_IDLE;
            }
        }
    }

    for (auto& mouse_button : mouse_buttons)
    {
        if (mouse_button == KeyState::KEY_DOWN)
            mouse_button = KeyState::KEY_REPEAT;

        if (mouse_button == KeyState::KEY_UP)
            mouse_button = KeyState::KEY_IDLE;
    }

    while (SDL_PollEvent(&sdlEvent) != 0)
    {
        switch (sdlEvent.type)
        {
        case SDL_QUIT:
            return update_status::UPDATE_STOP;

        case SDL_DROPFILE:
            {
                App->resources->HandleResource(sdlEvent.drop.file);
            }
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouse_buttons[sdlEvent.button.button - 1] = KeyState::KEY_DOWN;
            break;

        case SDL_MOUSEBUTTONUP:
            mouse_buttons[sdlEvent.button.button - 1] = KeyState::KEY_UP;
            break;

        case SDL_MOUSEMOTION:
            mouse_motion.x = sdlEvent.motion.xrel / 2.0f;
            mouse_motion.y = sdlEvent.motion.yrel / 2.0f;
            mouse_position.x = sdlEvent.motion.x / 2.0f;
            mouse_position.y = sdlEvent.motion.y / 2.0f;
            break;

        case SDL_MOUSEWHEEL:
            mouse_wheel.x = sdlEvent.wheel.x;
            mouse_wheel.y = sdlEvent.wheel.y;
            break;
        }
    }

    return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleInput::CleanUp()
{
    BE_LOG("Quitting SDL input event subsystem");
    SDL_QuitSubSystem(SDL_INIT_EVENTS);
    return true;
}
