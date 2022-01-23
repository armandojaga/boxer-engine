#include "ConsolePanel.h"

#include <string>

#include "Globals.h"
#include "imgui.h"

namespace BoxerEngine
{
    ConsolePanel::ConsolePanel() : Panel("Console", true), imgui_logger(new ImGuiLogger())
    {
        logger.Register(imgui_logger);
        auto lambda = [&](std::string&& str, LogLevel& logLevel)
        {
            Add(str, logLevel);
        };
        imgui_logger->SetCallBack(lambda);
    }

    ConsolePanel::~ConsolePanel()
    {
        logger.Unregister(imgui_logger);
        delete imgui_logger;
        lines.clear();
    }

    void ConsolePanel::Clear()
    {
        lines.clear();
    }

    void ConsolePanel::Add(std::string& str, LogLevel& logLevel)
    {
        if (lines.size() >= DISPLAY_THRESHOLD)
        {
            lines.erase(lines.begin());
        }
        lines.emplace_back(str, logLevel);
    }

    void ConsolePanel::Update()
    {
        ImGui::SetNextWindowSize(ImVec2(1100, 170), ImGuiCond_FirstUseEver);
        if (!ImGui::Begin(GetTitle().c_str(), &visible))
        {
            ImGui::End();
            return;
        }
        ImGui::BeginChild("ConsoleScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);
        if (ImGui::BeginPopupContextWindow())
        {
            if (ImGui::Selectable("Clear"))
            {
                Clear();
            }
            ImGui::EndPopup();
        }
        for (const auto& [str, logLevel] : lines)
        {
            if (logLevel == LogLevel::Error)
            {
                ImVec4 co(1.0f, 0.4f, 0.4f, 1.0f);
                ImGui::PushStyleColor(ImGuiCol_Text, co);
            }
            ImGui::TextUnformatted(str.c_str());
            if (logLevel == LogLevel::Error)
                ImGui::PopStyleColor();
        }
        if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        {
            ImGui::SetScrollHereY(1.0f);
        }
        ImGui::EndChild();
        ImGui::End();
    }
}
