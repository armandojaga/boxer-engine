#pragma once
#include <string>

#include "imgui_internal.h"
#include "Math/float3.h"

namespace BoxerEngine
{
    class AxisSlider
    {
    public:
        struct Config
        {
            const char* label_x = nullptr;
            const char* label_y = nullptr;
            const char* label_z = nullptr;
            float3 speed = float3(0.1f);
            float3 min = float3(std::numeric_limits<float>::lowest());
            float3 max = float3(std::numeric_limits<float>::max());
        };

        AxisSlider() = delete;
        ~AxisSlider() = default;

        static bool Build(const std::string& label, float3& values, const Config& config)
        {
            bool changed = false;
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
            ImGui::Button(config.label_x ? config.label_x : "X", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            if (ImGui::DragFloat("##X", &values.x, config.speed.x, config.min.x, config.max.x, "%.2f"))
            {
                changed = true;
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushItemWidth(groupWidth);

            ImGui::PushID(2);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, green);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, green);
            ImGui::Button(config.label_y ? config.label_y : "Y", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            if (ImGui::DragFloat("##Y", &values.y, config.speed.y, config.min.y, config.max.y, "%.2f"))
            {
                changed = true;
            }
            ImGui::PopItemWidth();
            ImGui::SameLine();

            ImGui::PushItemWidth(groupWidth);

            ImGui::PushID(3);
            ImGui::PushStyleColor(ImGuiCol_Text, white);
            ImGui::PushStyleColor(ImGuiCol_Button, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonHovered, blue);
            ImGui::PushStyleColor(ImGuiCol_ButtonActive, blue);
            ImGui::Button(config.label_z ? config.label_z : "Z", size);
            ImGui::PopStyleColor(4);
            ImGui::PopID();

            ImGui::SameLine();
            if (ImGui::DragFloat("##Z", &values.z, config.speed.z, config.min.z, config.max.z, "%.2f"))
            {
                changed = true;
            }
            ImGui::PopItemWidth();

            ImGui::PopStyleVar();
            ImGui::PopID();
            return changed;
        }

    private:
        inline static ImVec4 red = ImVec4(0.75f, 0.0f, 0.0f, 1.0f);
        inline static ImVec4 green = ImVec4(0.0f, 0.75f, 0.0f, 1.0f);
        inline static ImVec4 blue = ImVec4(0.0f, 0.0f, 0.75f, 1.0f);
        inline static ImVec4 white = ImVec4(1.0f, 1.0f, 1.0f, 1.0f);
    };
}
