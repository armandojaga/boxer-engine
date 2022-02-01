#include "core/bepch.h"
#include "HardwarePanel.h"

#include "GL/glew.h"

BoxerEngine::HardwarePanel::HardwarePanel(): Panel("Hardware", false)
{
}

void BoxerEngine::HardwarePanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(325, 260), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
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
