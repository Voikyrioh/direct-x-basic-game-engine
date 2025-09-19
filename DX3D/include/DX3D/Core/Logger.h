#pragma once

namespace dx3d
{
    class Logger final
    {
    public:
        enum class LogLevel
        {
            Error = 0,
            Warning,
            Info
        };

        explicit Logger(LogLevel logLevel = LogLevel::Error);
        ~Logger();
        void log(LogLevel level, const char* message);
    private:
        LogLevel m_log_level_ = LogLevel::Error;

    protected:
        Logger(const Logger&) = delete;
        Logger(Logger&&) = delete;
        Logger& operator= (const Logger&) = delete;
        Logger& operator= (Logger&&) = delete;
    };
    
}
#define DX3DLog(logger, type, message)\
logger.log((type), message);

#define DX3DLogThrow(logger, exception, type, message)\
{\
DX3DLog(logger, type, message);\
throw exception(message);\
}
