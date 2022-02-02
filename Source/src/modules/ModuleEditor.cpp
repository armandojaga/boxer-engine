#include "core/bepch.h"

#include "ModuleEditor.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"

#include "ModuleProgram.h"
#include "ModuleScene.h"

#include "ui/components/StatisticsPanel.h"
#include "core/preferences/editor/EditorPreferences.h"


ModuleEditor::ModuleEditor()
{
    scenePanel = std::make_shared<BoxerEngine::ScenePanel>();
    hierarchyPanel = std::make_shared<BoxerEngine::HierarchyPanel>();
    inspectorPanel = std::make_shared<BoxerEngine::InspectorPanel>();
    consolePanel = std::make_shared<BoxerEngine::ConsolePanel>();
    configurationPanel = std::make_shared<BoxerEngine::ConfigurationPanel>();
    statisticsPanel = std::make_shared<BoxerEngine::StatisticsPanel>();
    hardwarePanel = std::make_shared<BoxerEngine::HardwarePanel>();
    aboutPanel = std::make_shared<BoxerEngine::AboutPanel>();
    projectPanel = std::make_shared<BoxerEngine::ProjectPanel>();

    panels.push_back(aboutPanel);
    panels.push_back(hardwarePanel);
    panels.push_back(statisticsPanel);
    panels.push_back(consolePanel);
    panels.push_back(configurationPanel);
    panels.push_back(inspectorPanel);
    panels.push_back(hierarchyPanel);
    panels.push_back(scenePanel);
    panels.push_back(projectPanel);
};

ModuleEditor::~ModuleEditor()
{
    panels.erase(std::begin(panels), std::end(panels));
    panels.clear();
};

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

    // Fonts
    ImFontConfig config;
    config.MergeMode = true;
    config.GlyphMinAdvanceX = 16.0f;
    config.PixelSnapH = true;
    static constexpr ImWchar mdRange[] = {ICON_MIN_MD, ICON_MAX_MD, 0};
    io.Fonts->AddFontFromFileTTF("fonts/JetBrainsMono-Light.ttf", 16.0f);
    io.Fonts->AddFontFromFileTTF(BoxerEngine::StringUtils::Concat("fonts/", FONT_ICON_FILE_NAME_MD).c_str(), 16.0f, &config, mdRange);

    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 0.850f;
    style.DisabledAlpha = 0.60f;
    style.WindowRounding = 6.0f;
    style.ChildRounding = 6.0f;
    style.FrameRounding = 2.0f;
    style.PopupRounding = 6.0f;
    style.ScrollbarRounding = 6.0f;
    style.GrabRounding = 4.0f;

    ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->GetContext());
    ImGui_ImplOpenGL3_Init(GLSL_VERSION);

    // Get preferences from configuration
    preferences = static_cast<BoxerEngine::EditorPreferences*>(App->preferences->GetEditorPreferences());
    display_camera_settings = preferences->GetDisplayCameraSettings();

    UpdateTheme();

    return true;
}

update_status ModuleEditor::PreUpdate(float delta)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame();
    ImGui::NewFrame();
    ImGuizmo::BeginFrame();

    return update_status::UPDATE_CONTINUE;
}

update_status ModuleEditor::Update(float delta)
{
    CreateDockerspace();

    for (const auto panel : panels)
    {
        if (panel->IsVisible())
        {
            panel->Update();
        }
    }

    //make sure we render the opened windows
    if (display_camera_settings) ShowCameraSettings();
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

void ModuleEditor::UpdateTheme() const
{
    if (preferences->GetTheme() == BoxerEngine::Editor::Theme::Type::LIGHT)
    {
        // UI style
        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::StyleColorsLight();
        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg] = ImVec4(0.94f, 0.94f, 0.94f, 0.70f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.43f, 0.35f, 0.7f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 0.7f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.45f, 0.00f, 0.7f);
        preferences->SetSceneBackgroundColor(float3(0.9f));
    }
    else if (preferences->GetTheme() == BoxerEngine::Editor::Theme::Type::PINK)
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImGui::StyleColorsLight();
        ImVec4* colors = style.Colors;
        colors[ImGuiCol_WindowBg] = ImColor(160, 160, 232);
        colors[ImGuiCol_TitleBgActive] = ImColor(232, 160, 160);
        colors[ImGuiCol_TitleBg] = ImColor(160, 232, 232);
        colors[ImGuiCol_MenuBarBg] = ImColor(217, 245, 217);
        colors[ImGuiCol_PopupBg] = ImColor(153, 225, 220);
        colors[ImGuiCol_HeaderHovered] = ImColor(139, 204, 199);
        colors[ImGuiCol_Text] = ImColor(64, 64, 92);
        colors[ImGuiCol_FrameBg] = ImColor(232, 232, 160);
        preferences->SetSceneBackgroundColor(float3(217, 217, 245));
    }
    else
    {
        ImGui::StyleColorsDark();
        preferences->SetSceneBackgroundColor(float3(0.1f));
    }
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

void ModuleEditor::SetActiveEntity(BoxerEngine::Entity* const entity)
{
    BoxerEngine::Event selectionChanged(BoxerEngine::Event::Type::SELECTION_CHANGED);
    selectionChanged.SetEventData<BoxerEngine::SelectionChangedEventPayload>(entity);
    BoxerEngine::EventManager::GetInstance().Publish(selectionChanged);
}

void ModuleEditor::CreateMenu() const
{
    if (ImGui::BeginMainMenuBar())
    {
        if (ImGui::BeginMenu("File"))
        {
            if (ImGui::MenuItem("New scene"))
            {
                logger.Debug("Exiting");
                App->scene->CreateEmptyScene();
                SetActiveEntity(nullptr);
            }
            if (ImGui::MenuItem("Open scene"))
            {
                logger.Debug("opening");
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Save"))
            {
                logger.Debug("Saving");
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Exit"))
            {
                logger.Debug("Exiting");
                should_exit = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("View"))
        {
            if (ImGui::MenuItem(consolePanel->GetTitle().c_str()))
            {
                logger.Debug("Open console");
                consolePanel->SetVisible(true);
            }
            ImGui::Separator();
            if (ImGui::MenuItem("Stats"))
            {
                logger.Debug("Open stats");
                statisticsPanel->SetVisible(true);
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
                hardwarePanel->SetVisible(true);
            }
            if (ImGui::MenuItem(configurationPanel->GetTitle().c_str()))
            {
                logger.Debug("Open config");
                configurationPanel->SetVisible(true);
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Theme"))
        {
            bool lightTheme = preferences->GetTheme() == BoxerEngine::Editor::Theme::Type::LIGHT;
            bool darkTheme = preferences->GetTheme() == BoxerEngine::Editor::Theme::Type::DARK;
            bool pinkTheme = preferences->GetTheme() == BoxerEngine::Editor::Theme::Type::PINK;

            if (ImGui::MenuItem("Light", nullptr, &lightTheme))
            {
                logger.Debug("Selecting light mode");
                preferences->SetTheme(BoxerEngine::Editor::Theme::Type::LIGHT);
                UpdateTheme();
            }
            if (ImGui::MenuItem("Dark", nullptr, &darkTheme))
            {
                logger.Debug("Selecting dark mode");
                preferences->SetTheme(BoxerEngine::Editor::Theme::Type::DARK);
                UpdateTheme();
            }
            if (ImGui::MenuItem("Pink", nullptr, &pinkTheme))
            {
                logger.Debug("Selecting pink mode");
                preferences->SetTheme(BoxerEngine::Editor::Theme::Type::PINK);
                UpdateTheme();
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("About"))
            {
                logger.Debug("Open about");
                aboutPanel->SetVisible(true);
            }
            ImGui::EndMenu();
        }
        ImGui::EndMainMenuBar();
    }
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
    if (ImGui::SliderInt("Move Speed", &move_speed, 0, 100))
    {
        App->camera->SetMoveSpeed(move_speed);
    }

    int rotation_speed = App->camera->GetRotationSpeed();
    if (ImGui::SliderInt("Rotation Speed", &rotation_speed, 0, 100))
    {
        App->camera->SetRotationSpeed(rotation_speed);
    }

    int orbit_speed = App->camera->GetOrbitSpeed();
    if (ImGui::SliderInt("Orbit Speed", &orbit_speed, 0, 100))
    {
        App->camera->SetOrbitSpeed(orbit_speed);
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
