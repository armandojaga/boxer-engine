#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleWindow.h"
#include "ModuleCamera.h"
#include "ModuleDebugDraw.h"
#include <SDL.h>

ModuleRender::ModuleRender()= default;

// Destructor
ModuleRender::~ModuleRender()
{
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
	
	GLenum err = glewInit();

	BE_LOG("Using Glew %s", glewGetString(GLEW_VERSION));

	BE_LOG("Vendor: %s", glGetString(GL_VENDOR));
	BE_LOG("Renderer: %s", glGetString(GL_RENDERER));
	BE_LOG("OpenGL version supported %s", glGetString(GL_VERSION));
	BE_LOG("GLSL: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	glEnable(GL_DEPTH_TEST); // Enable depth test
	glEnable(GL_CULL_FACE); // Enable cull backward faces
	glFrontFace(GL_CCW); // Front faces will be counter clockwise

	SDL_GetWindowSize(App->window->window, &width, &height);

	// float vtx_data[] = {-0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f};
	//
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);

	return true;
}

update_status ModuleRender::PreUpdate()
{
	glViewport(0, 0, width, height);
	glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	return UPDATE_CONTINUE;
}

// Called every draw update
update_status ModuleRender::Update()
{
	// App->debug_draw->Draw(App->camera->GetViewMatrix(), App->camera->GetProjectionMatrix(), SCREEN_WIDTH, SCREEN_HEIGHT); // delete this when editor is enabled
	//
	// unsigned vbo{};
	// constexpr float vtx_data[] = { -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f, 0.0f, 0.5f, 0.0f };
	// glGenBuffers(1, &vbo);
	// glBindBuffer(GL_ARRAY_BUFFER, vbo); // set vbo active
	// glBufferData(GL_ARRAY_BUFFER, sizeof(vtx_data), vtx_data, GL_STATIC_DRAW);
	//
	// glEnableVertexAttribArray(0);
	// glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(0));
	// glDrawArrays(GL_TRIANGLES, 0, 3);
	//
	// glDeleteBuffers(1, &vbo);

	return UPDATE_CONTINUE;
}

update_status ModuleRender::PostUpdate()
{
	SDL_GL_SwapWindow(App->window->window);
	return UPDATE_CONTINUE;
}

// Called before quitting
bool ModuleRender::CleanUp()
{
	BE_LOG("Destroying renderer");

	//Destroy window
	SDL_GL_DeleteContext(context);
	// glDeleteBuffers(1, &vbo);
	return true;
}

void ModuleRender::WindowResized(unsigned width, unsigned height)
{
	this->width = width;
	this->height = height;
}
