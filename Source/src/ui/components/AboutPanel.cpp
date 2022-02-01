#include "core/bepch.h"
#include "AboutPanel.h"

BoxerEngine::AboutPanel::AboutPanel(): Panel("About", false)
{
}

void BoxerEngine::AboutPanel::Update()
{
    ImGui::SetNextWindowSize(ImVec2(605, 400), ImGuiCond_FirstUseEver);
    if (!ImGui::Begin(GetTitle().c_str(), &visible))
    {
        ImGui::End();
        return;
    }
    const ImVec4 red(1.0f, 0.0f, 0.0f, 1.0f);
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
    ImGui::BulletText("Yaml-cpp v 0.7.0");
    ImGui::BulletText("IconFontCppHeaders");
    ImGui::BulletText("ImGuizmo v1.83");
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
