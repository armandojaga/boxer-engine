#pragma once
#include "Logger.h"

namespace BoxerEngine
{
    class ConsoleLogger : public Logger
    {
    public:
        ~ConsoleLogger() override = default;
        void Log(const char* str, LogLevel& level) override;
        void Log(const char file[], int line, const char* format, ...);
    };
}
