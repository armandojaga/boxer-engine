#include "ModuleEditor.h"

#include <iostream>
#include <SDL.h>
#include <SDL_error.h>
#include <GL/glew.h>

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"


ModuleEditor::ModuleEditor() : console(new BoxerEngine::Console())
{
}

ModuleEditor::~ModuleEditor()
{
    delete console;
}

bool ModuleEditor::Init()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    CreateMenu();

    //make sure we render the console if opened
    if (display_console)
    {
        ShowConsole(&display_console);
    }

    //make sure we render the stats if opened
    if (display_stats)
    {
        ShowStats(&display_stats);
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    if (should_exit)
    {
        return UPDATE_STOP;
    }
    return UPDATE_CONTINUE;
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::CreateMenu()
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                LOG("Exiting");
                should_exit = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console", "CTRL+O"))
            {
                LOG("Open console");
                display_console = true;
                ShowConsole(&display_console);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Stats", "CTRL+Alt+S"))
            {
                console_logger.Error(" ERROR View stats");
                display_stats = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ModuleEditor::ShowConsole(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(520, 600), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Console", open))
    {
        ImGui::End();
        return;
    }
    ImGui::TextWrapped("Engine version %s", BOXER_ENGINE_VERSION);
    const float footerHeight = ImGui::GetStyle().ItemSpacing.y + ImGui::GetFrameHeightWithSpacing();
    ImGui::BeginChild("ConsoleScrollingRegion", ImVec2(0, -footerHeight), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (ImGui::BeginPopupContextWindow())
    {
        if (ImGui::Selectable("Clear"))
        {
            console->Clear();
        }
        ImGui::EndPopup();
    }
    console->Display();
    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
    {
        ImGui::SetScrollHereY(1.0f);
    }
    ImGui::EndChild();
    ImGui::End();
}

void ModuleEditor::ShowStats(bool*) const
{
}
