#include "Console.h"

#include <string>

#include "Globals.h"
#include "imgui.h"

namespace BoxerEngine
{
    Console::Console() : imgui_logger(new ImGuiLogger())
    {
        logger.Register(imgui_logger);
        auto lambda = [&](std::string&& str, LogLevel& logLevel)
        {
            Add(str, logLevel);
        };
        imgui_logger->SetCallBack(lambda);
    }

    Console::~Console()
    {
        logger.Unregister(imgui_logger);
        delete imgui_logger;
        lines.clear();
    }

    void Console::Clear()
    {
        lines.clear();
    }

    void Console::Add(std::string& str, LogLevel& logLevel)
    {
        if (lines.size() >= DISPLAY_THRESHOLD)
        {
            lines.erase(lines.begin());
        }
        lines.emplace_back(str, logLevel);
    }

    void Console::Display() const
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
