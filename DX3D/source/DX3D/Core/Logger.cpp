#include "DX3D/Core/Logger.h"

#include <iostream>

dx3d::Logger::Logger(LogLevel logLevel): m_log_level_(logLevel)
{
    std::clog << "My first game engine | C++ edition \n";
    std::clog << "_____________________________________\n";
}

dx3d::Logger::~Logger()
=default;

void dx3d::Logger::log(LogLevel level, const char* message)
{
    auto logLevelToString = [](LogLevel level)
    {
        switch (level)
        {
            case LogLevel::Info: return "Info";
            case LogLevel::Warning: return "Warning";
            case LogLevel::Error: return "Error";
            default: return "Unknown";
        }
    };
    
    if (level > m_log_level_) return;
    std::clog << "[DX3D " << logLevelToString(level) << "] " << message << '\n';
}
