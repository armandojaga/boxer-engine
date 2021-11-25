#pragma once
#include <vector>
#include "ImGuiLogger.h"

namespace BoxerEngine
{
#define DISPLAY_THRESHOLD 100 //lines to display;


    class Console
    {
    private:
        std::vector<std::pair<std::string, LogLevel>> lines;
        ImGuiLogger* imgui_logger;
    public:
        Console();
        ~Console();
        void Clear();
        void Add(std::string&, LogLevel&);
        void Display() const;
    };
}
