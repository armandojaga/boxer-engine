#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include <SDL.h>

#include "ModuleProgram.h"
#include "core/ErrorHandler.h"
#include "core/util/StringUtils.h"

#include "core/logging/AssimpLogger.h"
#include <assimp/DefaultLogger.hpp>

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
    frame_buffer = std::make_unique<BoxerEngine::FrameBuffer>(width, height);
    model = std::make_unique<BoxerEngine::Model>();

    // Assimp Logger
    // Create a logger instance 
    Assimp::DefaultLogger::create("", Assimp::Logger::VERBOSE);

    // Select the kinds of messages you want to receive on this log stream
    const unsigned int severity =
        Assimp::Logger::Debugging |
        Assimp::Logger::Info |
        Assimp::Logger::Err |
        Assimp::Logger::Warn;

    // Attaching it to the default logger
    Assimp::DefaultLogger::get()->attachStream(new AssimpLogger(), severity);

    return true;
}

bool ModuleRender::Start()
{
    model->Load(BoxerEngine::StringUtils::Concat(ASSETS_PATH, MODELS_DIR, "BakerHouse.fbx").c_str());
    return true;
}


update_status ModuleRender::PreUpdate()
{
    glViewport(0, 0, width, height);
    glClearColor(0.9f, 0.9f, 0.9f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return update_status::UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
    App->program->UseProgram();
    const float4x4 modelMatrix = float4x4::identity;
    const float4x4& view = App->camera->GetViewMatrix();
    const float4x4& projection = App->camera->GetProjectionMatrix();

    App->program->SetUniform("model", modelMatrix);
    App->program->SetUniform("view", view);
    App->program->SetUniform("projection", projection);

    App->renderer->GetFrameBuffer().Bind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (game_options.IsDisplayDebugDraw())
    {
        App->debug_draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), width, height);
    }
    App->program->UseProgram();
    App->renderer->GetModel()->Draw();

    App->renderer->GetFrameBuffer().Unbind();
    return update_status::UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
    SDL_GL_SwapWindow(App->window->window);
    return update_status::UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
    BE_LOG("Destroying renderer");

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
        Update();
    }
}

void* ModuleRender::GetContext() const
{
    return context;
}
