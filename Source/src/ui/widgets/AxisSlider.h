#pragma once
#include <string>

#include "imgui_internal.h"
#include "Math/float3.h"

namespace BoxerEngine
{
    class AxisSlider
    {
    private:
        inline static ImVec4 red = ImVec4(0.75f, 0.0f, 0.0f, 1.0f);
        inline static ImVec4 green = ImVec4(0.0f, 0.75f, 0.0f, 1.0f);
        inline static ImVec4 blue = ImVec4(0.0f, 0.0f, 0.75f, 1.0f);
        inline static ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    public:
        static void Build(std::string& label, float3& values)
        {
            ImGui::Separator();
            ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
            ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{0, 0});


            const float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
            const ImVec2 size = {lineHeight + 3.0f, lineHeight};
            auto wsize = GImGui->CurrentWindow->Size.x - (size.x * 3);
            ImGui::Text(label.c_str());

            ImGui::PushID(1);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, red);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, red);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, red);
            ImGui::Button("X", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##X", &values.x, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, green);
            ImGui::Button("Y", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##Y", &values.y, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushID(3);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, blue);
            ImGui::Button("Z", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            ImGui::DragFloat("##Z", &values.z, 0.1f, 0.0f, 0.0f, "%.2f");
            ImGui::PopItemWidth();

            ImGui::PopStyleVar();
        }
    };
}
