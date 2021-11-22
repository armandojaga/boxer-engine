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

    //make sure we render the opened windows
    if (display_about) ShowAbout(&display_about);
    if (display_console) ShowConsole(&display_console);
    if (display_stats) ShowStats(&display_stats);
    if (display_config) ShowConfig(&display_config);
    if (display_hardware) ShowHardware(&display_hardware);

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    ImGui::StyleColorsLight();
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
                console_logger.Debug("Exiting");
                should_exit = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console"))
            {
                console_logger.Debug("Open console");
                display_console = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Stats"))
            {
                console_logger.Debug("Open stats");
                display_stats = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Hardware"))
            {
                console_logger.Debug("Open hardware");
                display_hardware = true;
            }
            if(ImGui::MenuItem("Config"))
            {
                console_logger.Debug("Open config");
                display_config = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                console_logger.Debug("Open about");
                display_about = true;
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

void ModuleEditor::ShowConfig(bool*) const
{
}

void ModuleEditor::ShowHardware(bool*) const
{
}

void ModuleEditor::ShowAbout(bool*) const
{
    ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::TextWrapped("Engine version %s", BOXER_ENGINE_VERSION);
    ImGui::Separator();
    ImGui::TextWrapped("Boxer is another name for the actual flat engines in vehicles, widely used by Subaru");
    ImGui::Separator();
    ImGui::TextWrapped("Made with");
    ImGui::SameLine();
    ImGui::TextColored(red, " <3 ");
    ImGui::SameLine();
    ImGui::TextWrapped("by Armando");
    ImGui::Separator();
    ImGui::TextWrapped("Libraries");

    ImGui::Indent();
    ImGui::BulletText("Assimp 143");
    ImGui::BulletText("DevIL ");
    ImGui::BulletText("Glew");
    ImGui::BulletText("ImGui");
    ImGui::BulletText("MathGeoLib");
    ImGui::BulletText("SDL");
    ImGui::Unindent();


}
