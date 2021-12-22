#include "ModuleEditor.h"

#include <iostream>
#include <SDL.h>

#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleDebugDraw.h"
#include "ModuleCamera.h"

#include "debugdraw.h"

#include "imgui_impl_opengl3.h"
#include "imgui_impl_sdl.h"
#include "ModuleProgram.h"
#include "core/util/Files.h"
#include "ui/widgets/AxisSlider.h"


ModuleEditor::ModuleEditor() : console(new BoxerEngine::ConsolePanel())
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

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    //config
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // Font
    io.Fonts->AddFontFromFileTTF("fonts/JetBrainsMono-Light.ttf", 16);

    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 0.850f;
    style.DisabledAlpha = 0.60f;
    style.WindowRounding = 6.0f;
    style.ChildRounding = 6.0f;
    style.FrameRounding = 2.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;

    //TODO read from config file
#ifdef LIGHT_THEME
    // UI style
    ImGui::StyleColorsLight();
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.70f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 0.7f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 0.7f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 0.7f);
    game_options.SetSceneBackgroundColor(float3(0.9f));
#else
    game_options.SetSceneBackgroundColor(float3(0.1f));
#endif

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->GetContext());
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    return true;
}

update_status ModuleEditor::PreUpdate(float delta)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float delta)
{
    CreateDockerspace();

    //make sure we render the opened windows
    if (display_about) ShowAbout();
    if (display_console) ShowConsole();
    if (display_stats) ShowStats();
    if (display_config) ShowConfig();
    if (display_hardware) ShowHardware();
    if (display_camera_settings) ShowCameraSettings();

    CreateScene();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate(float delta)
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        const auto win = SDL_GL_GetCurrentWindow();
        const auto ctx = SDL_GL_GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        SDL_GL_MakeCurrent(win, ctx);
    }
    if (should_exit)
    {
        return update_status::UPDATE_STOP;
    }
    return update_status::UPDATE_CONTINUE;
}

void ModuleEditor::CreateDockerspace() const
{
    //dockerspace
    constexpr ImGuiWindowFlags dockspace_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
        ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus |
        ImGuiWindowFlags_NoBackground | ImGuiWindowFlags_MenuBar;

    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);
    ImGui::SetNextWindowViewport(viewport->ID);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

    ImGui::Begin("Dockspace", nullptr, dockspace_flags);
    ImGui::PopStyleVar(3);

    const ImGuiID dockSpaceId = ImGui::GetID("DockspaceID");

    ImGui::DockSpace(dockSpaceId, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_PassthruCentralNode);

    CreateMenu();

    ImGui::End();
}

bool ModuleEditor::CleanUp()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    return true;
}

void ModuleEditor::CreateScene() const
{
    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_FirstUseEver);
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Scene");

    const ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    float x = viewportPanelSize.x, y = viewportPanelSize.y;

    App->renderer->Resize(x, y);

    // to actually render inside the scene window
    ImGui::Image(reinterpret_cast<void*>(App->renderer->GetFrameBuffer().GetTextureId()), ImVec2{x, y}, ImVec2{0, 1}, ImVec2{1, 0});

    ImGui::End();
    ImGui::PopStyleVar();
}

void ModuleEditor::CreateMenu() const
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("Exit"))
            {
                logger.Debug("Exiting");
                should_exit = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem("Console"))
            {
                logger.Debug("Open console");
                display_console = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Stats"))
            {
                logger.Debug("Open stats");
                display_stats = true;
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Camera"))
            {
                logger.Debug("Open camera settings");
                display_camera_settings = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Tools"))
        {
            if (ImGui::MenuItem("Hardware"))
            {
                logger.Debug("Open hardware");
                display_hardware = true;
            }
            if (ImGui::MenuItem("Config"))
            {
                logger.Debug("Open config");
                display_config = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                logger.Debug("Open about");
                display_about = true;
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
}

void ModuleEditor::ShowConsole() const
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Console", &display_console))
    {
        ImGui::End();
        return;
    }

    ImGui::BeginChild("ConsoleScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
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

void ModuleEditor::ShowStats() const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Statistics", &display_stats))
    {
        ImGui::End();
        return;
    }
    static int counter = 0;
    static float fps = App->statistics->GetFramesPerSecond();
    static float ms = App->statistics->GetFrameSpeed();
    if (counter >= 10)
    {
        fps = App->statistics->GetFramesPerSecond();
        ms = App->statistics->GetFrameSpeed();
        counter = 0;
    }
    ++counter;
    ImGui::TextWrapped("Memory used: %d MB", App->statistics->GetUsedMemory() / 1000000);
    char fpsOverlay[32];
    sprintf(fpsOverlay, "FPS %.2f", fps);
    float fpsLimit = App->statistics->GetFramesPerSecond() + 10.0f;
    ImGui::PlotHistogram("##framerate", *App->statistics->GetFPSLog(), IM_ARRAYSIZE(*App->statistics->GetFPSLog()), 0, fpsOverlay, 0.0f, fpsLimit, ImVec2(310, 100));

    char msOverlay[32];
    sprintf(msOverlay, "%.2f ms", ms);
    ImGui::PlotHistogram("##framespeed", *App->statistics->GetMSLog(), IM_ARRAYSIZE(*App->statistics->GetMSLog()), 0, msOverlay, 0.0f, 40.0f, ImVec2(310, 100));
    ImGui::End();
}

void ModuleEditor::ShowConfig() const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Config", &display_config))
    {
        ImGui::End();
        return;
    }
    float maxFps = game_options.GetMaxFPS();
    ImGui::SliderFloat("##FPSSlider", &maxFps, 24.0f, 250.0f, "FPS %.1f");
    game_options.SetMaxFPS(maxFps);

    bool vsync = game_options.GetVsync();
    ImGui::TextWrapped("Vsync");
    ImGui::SameLine();
    ImGui::Checkbox("##vsync", &vsync);
    game_options.SetVsync(vsync);

    bool fullscreen = game_options.IsFullscreen();
    ImGui::TextWrapped("Fullscreen");
    ImGui::SameLine();
    ImGui::Checkbox("##fullscreen", &fullscreen);
    game_options.SetFullscreen(fullscreen);

    bool displayDebugDraw = game_options.IsDisplayDebugDraw();
    ImGui::TextWrapped("Display debug draw");
    ImGui::SameLine();
    ImGui::Checkbox("##debugdraw", &displayDebugDraw);
    game_options.SetDisplayDebugDraw(displayDebugDraw);

    // float3 values = float3::zero;
    // std::string label = "Camera";
    // BoxerEngine::AxisSlider::Build(label, values);

    ImGui::End();
}

void ModuleEditor::ShowHardware() const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Hardware", &display_hardware))
    {
        ImGui::End();
        return;
    }
    ImGui::TextWrapped("System memory: %.1f GB", SDL_GetSystemRAM() / 1000.0f);
    ImGui::TextWrapped("CPU cores: %d", SDL_GetCPUCount());
    ImGui::Separator();
    ImGui::TextWrapped("GPU Vendor: %s", glGetString(GL_VENDOR));
    ImGui::TextWrapped("Renderer: %s", glGetString(GL_RENDERER));
    ImGui::TextWrapped("OpenGL: %s", glGetString(GL_VERSION));
    ImGui::TextWrapped("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    ImGui::End();
}

void ModuleEditor::ShowAbout() const
{
    ImGui::SetNextWindowSize(ImVec2(605, 400), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("About", &display_about))
    {
        ImGui::End();
        return;
    }
    ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);
    ImGui::TextWrapped("Boxer Engine - version %s", BOXER_ENGINE_VERSION);

    ImGui::Separator();

    ImGui::TextWrapped("Boxer is another name for the actual flat engines in vehicles, widely used by Subaru");

    ImGui::Separator();

    ImGui::TextWrapped("Made with");
    ImGui::SameLine();
    ImGui::TextColored(red, "<3");
    ImGui::SameLine();
    ImGui::TextWrapped("by Armando and Alvaro");

    ImGui::Separator();

    ImGui::TextWrapped("Libraries");

    ImGui::Indent();
    ImGui::BulletText("Assimp v 143");
    ImGui::BulletText("DevIL v 1.8.0");
    ImGui::BulletText("Glew v 2.1.0");
    ImGui::BulletText("ImGui v 1.86 WIP");
    ImGui::BulletText("MathGeoLib v 1.5");
    ImGui::BulletText("SDL v 2.0.16");
    ImGui::Unindent();

    ImGui::Separator();

    ImGui::TextWrapped("License");

    ImGui::BeginChild("LicenseScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
    if (license_content.empty())
    {
        license_content = BoxerEngine::Files::ReadFile(LICENSE_PATH);
    }

    ImGui::TextWrapped(license_content.c_str());
    ImGui::EndChild();
    ImGui::End();
}

void ModuleEditor::ShowCameraSettings() const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin("Camera Settings", &display_camera_settings))
    {
        ImGui::End();
        return;
    }

    int move_speed = App->camera->GetMoveSpeed();
    if (ImGui::SliderInt("Move Speed", &move_speed, 0, 10))
    {
        App->camera->SetMoveSpeed(move_speed);
    }

    int rotation_speed = App->camera->GetRotationSpeed();
    if (ImGui::SliderInt("Rotation Speed", &rotation_speed, 0, 10))
    {
        App->camera->SetRotationSpeed(rotation_speed);
    }

    int zoom_speed = App->camera->GetZoomPosSpeed();
    if (ImGui::SliderInt("Zoom Speed", &zoom_speed, 1, 100))
    {
        App->camera->SetZoomPosSpeed(zoom_speed);
    }

    float fov = App->camera->GetHorizontalFovDegrees();
    ImGui::InputFloat("FOV", &fov, 0.0f, 120.0f);

    ImGui::End();
}
