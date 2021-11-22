#pragma once

#include <functional>

#include "Logger.h"
#include "imgui.h"

namespace BoxerEngine
{
    class ImGuiLogger : public Logger
    {
    public:
        void Log(const char* str, LogLevel& level) override;
        void SetCallBack(const std::function<void(std::string&&, LogLevel&)>& callback);
    private:
        std::function<void(std::string&&, LogLevel&)> callback;
    };
}
