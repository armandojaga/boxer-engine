#include "core/bepch.h"

#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include "ModuleProgram.h"

#include "ModuleScene.h"

#include <SDL.h>

#include "core/ErrorHandler.h"
#include "core/logging/AssimpLogger.h"
#include <assimp/DefaultLogger.hpp>

ModuleRender::~ModuleRender()
{
    delete frame_buffer;
}

// Called before render is available
bool ModuleRender::Init()
{
    BE_LOG("Creating Renderer context");

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4); // desired version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1); // we want a double buffer
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24); // we want to have a depth buffer with 24 bits
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8); // we want to have a stencil buffer with 8 bits

    context = SDL_GL_CreateContext(App->window->window);
    SDL_GL_MakeCurrent(App->window->window, context);

    GLenum err = glewInit();

    BE_LOG("Using Glew %s", glewGetString(GLEW_VERSION));

    BE_LOG("Vendor: %s", glGetString(GL_VENDOR));
    BE_LOG("Renderer: %s", glGetString(GL_RENDERER));
    BE_LOG("OpenGL version supported %s", glGetString(GL_VERSION));
    BE_LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glEnable(GL_DEPTH_TEST); // Enable depth test
    glEnable(GL_CULL_FACE); // Enable cull backward faces
    glFrontFace(GL_CCW); // Front faces will be counter clockwise

#ifdef _DEBUG
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(&BoxerEngine::ErrorHandler::HandleOpenGlError, nullptr);
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, true);
#endif

    SDL_GetWindowSize(App->window->window, &width, &height);
    frame_buffer = new BoxerEngine::FrameBuffer(width, height);

    prefs = static_cast<BoxerEngine::EditorPreferences*>(App->preferences->GetEditorPreferences());

    // Assimp Logger
    // Create a logger instance 
    DefaultLogger::create("", Logger::VERBOSE);

    // Select the kinds of messages you want to receive on this log stream
    const unsigned int severity =
        Logger::Debugging |
        Logger::Info |
        Logger::Err |
        Logger::Warn;

    // Attaching it to the default logger
    DefaultLogger::get()->attachStream(new AssimpLogger(), severity);

    std::function setActiveEntity = [&](BoxerEngine::Event& evt)
    {
        const auto& e = evt.GetEventData<BoxerEngine::SelectionChangedEventPayload>();
        active_entity = e.GetSelected();
    };
    BoxerEngine::EventManager::GetInstance().Subscribe(BoxerEngine::Event::Type::SELECTION_CHANGED, setActiveEntity);

    return true;
}

bool ModuleRender::Start()
{
    return true;
}


update_status ModuleRender::PreUpdate(float delta)
{
    const auto& bgColor = float3(prefs->GetSceneBackgroundColor());
    glViewport(0, 0, width, height);
    glClearColor(bgColor.x, bgColor.y, bgColor.z, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update(float delta)
{
    OPTICK_EVENT();
    App->program->UseProgram();
    const float4x4 modelMatrix = float4x4::identity;
    const float4x4& view = App->camera->GetViewMatrix();
    const float4x4& projection = App->camera->GetProjectionMatrix();

    App->program->SetUniform("model", modelMatrix);
    App->program->SetUniform("view", view);
    App->program->SetUniform("projection", projection);

    App->renderer->GetFrameBuffer()->Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (prefs->IsDisplayDebugDraw())
    {
        App->debug_draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), width, height);
        if (active_entity)
        {
            active_entity->DisplayGizmos();
        }
    }

    App->program->UseProgram();

    //draw entities
    App->scene->GetScene()->GetRoot()->Draw();

    App->renderer->GetFrameBuffer()->Unbind();
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate(float delta)
{
    SDL_GL_SwapWindow(App->window->window);
    return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
    BE_LOG("Destroying renderer");
    delete model;
    //Destroy window
    SDL_GL_DeleteContext(context);
    return true;
}

void ModuleRender::Resize(const int width, const int height)
{
    if (this->width != width || this->height != height)
    {
        this->width = width;
        this->height = height;
        frame_buffer->Resize(width, height);
        App->camera->SetAspectRatio(width, height);
        Update(0);
    }
}

void* ModuleRender::GetContext() const
{
    return context;
}
