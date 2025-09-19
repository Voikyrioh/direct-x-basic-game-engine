#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Math/Rect.h>

namespace dx3d
{
    struct BaseDesc
    {
        Logger& logger;
    };

    struct WindowDesc
    {
        BaseDesc base;
        Rect size{};
    };

    struct DisplayDesc
    {
        WindowDesc window;
        GraphicsDevice& graphics_device;
    };

    struct GraphicsEngineDesc
    {
        BaseDesc base;
    };

    struct GraphicsDeviceDesc
    {
        BaseDesc base;
    };

    struct SwapChainDesc
    {
        void* win_handle{};
        Rect win_size{};
    };

    enum class ShaderType
    {
        Vertex = 0,
        Pixel,
        Geometry,
        Hull,
        Domain,
        Compute,
    };

    struct ShaderCompileDesc
    {
        const char* shader_source_name{};
        const void* shader_source_code{};
        size_t shader_source_code_size{};
        const char* shader_entry_point{};
        ShaderType shader_type{};
    };

    struct GameDesc
    {
        Rect window_size{ 1280, 720 };
        Logger::LogLevel logLevel = Logger::LogLevel::Error;
    };
}
