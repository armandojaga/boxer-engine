#include "instrumentation/MemoryLeaks.h"
#include "Globals.h"
#include "Application.h"
#include <SDL.h>

enum class main_states
{
    MAIN_CREATION,
    MAIN_START,
    MAIN_UPDATE,
    MAIN_FINISH,
    MAIN_EXIT
};

std::unique_ptr<Application> App = nullptr;

int main(int argc, char** argv)
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

    int main_return = EXIT_FAILURE;
    auto state = main_states::MAIN_CREATION;

    game_clock.Start(); //TODO autostart/label

    while (state != main_states::MAIN_EXIT)
    {
        switch (state)
        {
        case main_states::MAIN_CREATION:
            BE_LOG("Application Creation --------------");
            App = std::make_unique<Application>();
            state = main_states::MAIN_START;
            break;

        case main_states::MAIN_START:

            BE_LOG("Application Init --------------");
            if (App->Init() == false)
            {
                BE_LOG("Application Init exits with error -----");
                state = main_states::MAIN_EXIT;
            }
            else
            {
                state = main_states::MAIN_UPDATE;
                BE_LOG("Application Update --------------");
            }

            break;

        case main_states::MAIN_UPDATE:
            {
                //FPS limit
                // BoxerEngine::Timer clock;
                float start = game_clock.ReadMs();

                update_status update_return = App->Update();

                App->statistics->calculate();

                SDL_GL_SetSwapInterval(game_options.GetVsync());

                const float elapsed = game_clock.ReadMs() - start;
                if (1000.0f / game_options.GetMaxFPS() > elapsed)
                {
                    SDL_Delay(1000.0f / game_options.GetMaxFPS() - elapsed);
                }

                if (update_return == update_status::UPDATE_ERROR)
                {
                    BE_LOG("Application Update exits with error -----");
                    state = main_states::MAIN_EXIT;
                }

                if (update_return == update_status::UPDATE_STOP)
                    state = main_states::MAIN_FINISH;
            }
            break;

        case main_states::MAIN_FINISH:

            BE_LOG("Application CleanUp --------------");
            if (App->CleanUp() == false)
            {
                BE_LOG("Application CleanUp exits with error -----");
            }
            else
                main_return = EXIT_SUCCESS;

            state = main_states::MAIN_EXIT;

            break;
        }
    }

    BE_LOG("Bye :)");
    return main_return;
}
