#pragma once

//TODO create loggers from config files;
//TODO create more loggers like file
//TODO log representation? (json, xml, yml, ...)

namespace BoxerEngine
{
    enum class LogLevel
    {
        Debug,
        Info,
        Error
    };

    class Logger
    {
        Logger* next{nullptr};
    public:
        Logger() = default;
        virtual ~Logger() = default;

        void Debug(const char* str)
        {
            _log(str, LogLevel::Debug);
        }

        virtual void Info(const char* str)
        {
            _log(str, LogLevel::Info);
        }

        virtual void Error(const char* str)
        {
            _log(str, LogLevel::Error);
        }

        // chain of responsibility for calling all loggers
        void Register(Logger* next)
        {
            //TODO logger registry?
            if (this->next)
            {
                this->next->Register(next);
            }
            else
            {
                this->next = next;
            }
        }

        void Unregister(Logger* logger)
        {
            if (next == logger)
            {
                if (next->next)
                {
                    next = next->next;
                }
                else
                {
                    next = nullptr;
                }
            }
            else if (next)
            {
                next->Unregister(logger);
            }
        }

        //TODO safe unregister?

    protected:
        virtual void Log(const char* str, LogLevel& level) = 0;

    private:
        void _log(const char* str, LogLevel level)
        {
            Log(str, level);
            if (next)
            {
                next->_log(str, level);
            }
        }
    };
}
