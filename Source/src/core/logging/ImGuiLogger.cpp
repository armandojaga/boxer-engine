#include "ImGuiLogger.h"

void BoxerEngine::ImGuiLogger::Log(const char* str, LogLevel& level)
{
    callback(str, level);
}

void BoxerEngine::ImGuiLogger::SetCallBack(const std::function<void(std::string&&, LogLevel&)>& callback)
{
    this->callback = callback;
}
