#pragma once
#include <string>

#include "imgui_internal.h"
#include "Math/float3.h"

namespace BoxerEngine
{
    class AxisSlider
    {
    public:
        AxisSlider() = delete;
        ~AxisSlider() = default;

        static void Build(const std::string& label, float3& values, const char* x = nullptr, const char* y = nullptr, const char* z = nullptr)
        {
            ImGui::PushID(label.c_str());

            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(0, 5));

            const float groupWidth = ImGui::GetContentRegionAvail().x * 0.333f - ImGui::GetStyle().IndentSpacing;

            const float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            const ImVec2 size = {lineHeight + 3.0f, lineHeight};

            ImGui::Text(label.c_str());

            ImGui::PushItemWidth(groupWidth);

            ImGui::PushID(1);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, red);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, red);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, red);
            ImGui::Button(x ? x : "X", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushItemWidth(groupWidth);

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, green);
            ImGui::Button(y ? y : "Y", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushItemWidth(groupWidth);

            ImGui::PushID(3);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, blue);
            ImGui::Button(z ? z : "Z", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();

            ImGui::PopStyleVar();
            ImGui::PopID();
        }

    private:
        inline static ImVec4 red = ImVec4(0.75f, 0.0f, 0.0f, 1.0f);
        inline static ImVec4 green = ImVec4(0.0f, 0.75f, 0.0f, 1.0f);
        inline static ImVec4 blue = ImVec4(0.0f, 0.0f, 0.75f, 1.0f);
        inline static ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    };
}
