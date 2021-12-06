#pragma once

#include "core/logging/ImGuiLogger.h"

namespace BoxerEngine
{
#define DISPLAY_THRESHOLD 100 //lines to display;


    class ConsolePanel
    {
    private:
        std::vector<std::pair<std::string, LogLevel>> lines;
        ImGuiLogger* imgui_logger;
    public:
        ConsolePanel();
        ~ConsolePanel();
        void Clear();
        void Add(std::string&, LogLevel&);
        void Display() const;
    };
}
