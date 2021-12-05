#include "ConsolePanel.h"

#include <string>

#include "Globals.h"
#include "imgui.h"

namespace BoxerEngine
{
    ConsolePanel::ConsolePanel() : imgui_logger(new ImGuiLogger())
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

    void ConsolePanel::Display() const
    {
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
    }
}
