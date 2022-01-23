#pragma once

#include "Panel.h"
#include "core/logging/ImGuiLogger.h"

namespace BoxerEngine
{
#define DISPLAY_THRESHOLD 100 //lines to display;

    class ConsolePanel final : public Panel
    {
    public:
        ConsolePanel();
        ~ConsolePanel() override;
        void Clear();
        void Add(std::string&, LogLevel&);
        void Update() override;
    private:
        std::vector<std::pair<std::string, LogLevel>> lines;
        ImGuiLogger* imgui_logger;
    };
}
