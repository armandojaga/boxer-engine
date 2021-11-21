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


ModuleEditor::ModuleEditor()
{
}

ModuleEditor::~ModuleEditor()
{
}

bool ModuleEditor::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
	{
		printf("Error: %s\n", SDL_GetError());
		return false;
	}

	const char* glsl_version = "#version 460";
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

	SDL_GL_MakeCurrent(App->window->window, App->renderer->context);
	SDL_GL_SetSwapInterval(VSYNC); // Enable vsync

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable; // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	ImGui::StyleColorsDark();

	ImGui_ImplSDL2_InitForOpenGL(App->window->window, App->renderer->context);
	ImGui_ImplOpenGL3_Init(glsl_version);

	return true;
}

update_status ModuleEditor::Update()
{
	update_status result = UPDATE_CONTINUE;
	// Start the Dear ImGui frame
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();


	bool open = true;
	ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_MenuBar;
	ImGui::Begin("Editor", &open, window_flags);

	int action = CreateMenu();
	if(action == UPDATE_STOP)
	{
		result = UPDATE_STOP;
	}

	ImGui::End();

	ImGui::Render();

	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGui::UpdatePlatformWindows();
	ImGui::RenderPlatformWindowsDefault();

	return result;
}

bool ModuleEditor::CleanUp()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

	return true;
}

int ModuleEditor::CreateMenu()
{
	int action = 0;
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit", "Alt+F4"))
			{
				LOG("Exiting");
				action = UPDATE_STOP;
			}
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("View"))
		{
			if (ImGui::MenuItem("Console", "CTRL+O"))
			{
				LOG("Open console");
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Stats", "CTRL+Alt+S"))
			{
				LOG("View stats");
			}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}
	return action;
}
