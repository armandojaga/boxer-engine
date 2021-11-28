#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#define DEBUG_NEW new( _NORMAL_BLOCK, __FILE__, __LINE__)
#define new DEBUG_NEW
#endif

#include <cstdlib>
#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"

#include <SDL.h>

#include "Timer.h"
#include "core/GameOptions.h"

enum main_states
{
    MAIN_CREATION,
    MAIN_START,
    MAIN_UPDATE,
    MAIN_FINISH,
    MAIN_EXIT
};
#include <typeinfo>
Application* App = nullptr;

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int main_return = EXIT_FAILURE;
    main_states state = MAIN_CREATION;

    game_clock.Start(); //TODO autostart/label

    while (state != MAIN_EXIT)
    {
        switch (state)
        {
        case MAIN_CREATION:
            BE_LOG("Application Creation --------------");
            App = new Application();
            state = MAIN_START;
            break;

        case MAIN_START:

            BE_LOG("Application Init --------------");
            if (App->Init() == false)
            {
                BE_LOG("Application Init exits with error -----");
                state = MAIN_EXIT;
            }
            else
            {
                state = MAIN_UPDATE;
                BE_LOG("Application Update --------------");
            }

            break;

        case MAIN_UPDATE:
            {
                //FPS limit
                // BoxerEngine::Timer clock;
                double start = game_clock.ReadMs();

                int update_return = App->Update();

                App->statistics->calculate();

                double elapsed = game_clock.ReadMs() - start;
                if (1000.0 / FPS_LIMIT > elapsed)
                {
                    SDL_Delay(1000.0 / FPS_LIMIT - elapsed);
                }

                if (update_return == UPDATE_ERROR)
                {
                    BE_LOG("Application Update exits with error -----");
                    state = MAIN_EXIT;
                }

                if (update_return == UPDATE_STOP)
                    state = MAIN_FINISH;
            }
            break;

        case MAIN_FINISH:

            BE_LOG("Application CleanUp --------------");
            if (App->CleanUp() == false)
            {
                BE_LOG("Application CleanUp exits with error -----");
            }
            else
                main_return = EXIT_SUCCESS;

            state = MAIN_EXIT;

            break;
        }
    }

    delete App;
    BE_LOG("Bye :)\n");
    return main_return;
}
