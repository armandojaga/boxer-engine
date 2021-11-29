#include "ModuleEditor.h"

#include <iostream>
#include <SDL.h>

#include "Application.h"
#include "Files.h"
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

    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    //config
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable; // Enable Multi-Viewport / Platform Windows

    // Font
    io.Fonts->AddFontFromFileTTF("fonts/JetBrainsMono-Light.ttf", 16);

    // UI style
    ImGui::StyleColorsLight();
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 0.850f;
    style.DisabledAlpha = 0.60f;
    ImVec4* colors = style.Colors;
    colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.70f);
    colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 0.7f);
    colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 0.7f);
    colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 0.7f);

    style.WindowRounding = 6.0f;
    style.ChildRounding = 6.0f;
    style.FrameRounding = 2.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    return true;
}

update_status ModuleEditor::PreUpdate()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();

    //dockerspace
    const ImGuiWindowFlags dockspace_flags = ImGuiWindowFlags_NoDocking | ImGuiWindowFlags_NoTitleBar |
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

    return UPDATE_CONTINUE;
}

update_status ModuleEditor::Update()
{
    //make sure we render the opened windows
    if (display_about) ShowAbout(&display_about);
    if (display_console) ShowConsole(&display_console);
    if (display_stats) ShowStats(&display_stats);
    if (display_config) ShowConfig(&display_config);
    if (display_hardware) ShowHardware(&display_hardware);

    ImGui::SetNextWindowSize(ImVec2(800, 600), ImGuiCond_Once);

    ImGui::Begin("Scene");

    const ImVec2 viewportPanelSize = ImGui::GetContentRegionAvail();
    int x = viewportPanelSize.x, y = viewportPanelSize.y;
    //===============================================================================================================
    //frame buffer
    if (mFBO)
    {
        glDeleteFramebuffers(GL_FRAMEBUFFER, &mFBO);
        glDeleteTextures(1, &mTexId);
        glDeleteTextures(1, &mDepthId);
        mTexId = 0;
        mDepthId = 0;
    }


    glGenFramebuffers(1, &mFBO);
    glBindFramebuffer(GL_FRAMEBUFFER, mFBO);
    glCreateTextures(GL_TEXTURE_2D, 1, &mTexId);
    glBindTexture(GL_TEXTURE_2D, mTexId);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, mTexId, 0);

    glCreateTextures(GL_TEXTURE_2D, 1, &mDepthId);
    glBindTexture(GL_TEXTURE_2D, mDepthId);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_DEPTH24_STENCIL8, x, y);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_TEXTURE_2D, mDepthId, 0);

    GLenum buffers[4] = { GL_COLOR_ATTACHMENT0 };
    glDrawBuffers(mTexId, buffers);




    glViewport(0, 0, x, y);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //===============================================================================================================

    unsigned vbo{};
    float vtx_data[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f };
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
    glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDeleteBuffers(1, &vbo);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);


    ImGui::Image(reinterpret_cast<void*>(mTexId), ImVec2{ static_cast<float>(x), static_cast<float>(y) }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });
    
    //===============================================================================================================

    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    return UPDATE_CONTINUE;
}

update_status ModuleEditor::PostUpdate()
{
    ImGuiIO& io = ImGui::GetIO();

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        auto ctx = ImGui::GetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        ImGui::SetCurrentContext(ctx);
    }
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

void ModuleEditor::ShowConsole(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_Once);
    if (!ImGui::Begin("Console", open))
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

void ModuleEditor::ShowStats(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_Once);
    if (!ImGui::Begin("Statistics", open))
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

void ModuleEditor::ShowConfig(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_Once);
    if (!ImGui::Begin("Config", open))
    {
        ImGui::End();
        return;
    }
    float maxFps = game_options.GetMaxFPS();
    ImGui::SliderFloat("##FPSSlider", &maxFps, 24.0f, 250.0f,"FPS %.1f");
    game_options.SetMaxFPS(maxFps);

    bool vsync = game_options.GetVsync();
    ImGui::TextWrapped("Vsync");
    ImGui::SameLine();
    ImGui::Checkbox("##vsync", &vsync);
    game_options.SetVsync(vsync);

    bool fullscreen = game_options.IsFullScreen();
    ImGui::TextWrapped("Fullscreen");
    ImGui::SameLine();
    ImGui::Checkbox("##fullscreen", &fullscreen);
    game_options.SetFullSceen(fullscreen);

    ImGui::End();
}

void ModuleEditor::ShowHardware(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_Once);
    if (!ImGui::Begin("Hardware", open))
    {
        ImGui::End();
        return;
    }
    ImGui::TextWrapped("System memory: %d GB", SDL_GetSystemRAM()/1000);
    ImGui::TextWrapped("CPU cores: %d", SDL_GetCPUCount());
    ImGui::Separator();
    ImGui::TextWrapped("GPU Vendor: %s", glGetString(GL_VENDOR));
    ImGui::TextWrapped("Renderer: %s", glGetString(GL_RENDERER));
    ImGui::TextWrapped("OpenGL: %s", glGetString(GL_VERSION));
    ImGui::TextWrapped("GLSL: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
    ImGui::End();
}

void ModuleEditor::ShowAbout(bool* open) const
{
    ImGui::SetNextWindowSize(ImVec2(605, 400), ImGuiCond_Once);
    if (!ImGui::Begin("About", open))
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
    ImGui::TextWrapped("by Armando");
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
        license_content = Files::ReadFile(LICENSE_PATH);
    }

    ImGui::TextWrapped(license_content.c_str());
    ImGui::EndChild();
    ImGui::End();
}
