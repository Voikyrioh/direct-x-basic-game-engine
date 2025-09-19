#pragma once
#include <DX3D/Core/Logger.h>
#include <d3dcommon.h>

namespace dx3d
{
    namespace GraphicsLogsUtils
    {
        inline void CheckShaderCompile(Logger& logger, HRESULT hr, ID3DBlob* errorblob)
        {
            auto errorMsg = errorblob ? static_cast<const char*>(errorblob->GetBufferPointer()) : nullptr;
            
            if (FAILED(hr))
            {
                if (errorMsg)
                {
                    DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, errorMsg)
                }
                DX3DLogThrow(logger, std::runtime_error, Logger::LogLevel::Error, 
                    "Shader compilation failed with unknown error!")
            }

            if (errorMsg) 
            {
                DX3DLog(logger, Logger::LogLevel::Warning, errorMsg)
            }
        }
    }
}

#define DX_3D_GRAPHICS_ON_FAIL_THROW(hr, message)\
{\
    auto res = (hr);\
    if (FAILED(res))\
    DX3DLogThrowError(message);\
}

#define DX_3D_GRAPHICS_CHECK_SHADER_COMPILE(hr, errorblob)\
{\
    auto res = (hr);\
    dx3d::GraphicsLogsUtils::CheckShaderCompile(getLogger(), res, errorblob);\
}
