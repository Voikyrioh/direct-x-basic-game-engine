#pragma once
#include <DX3D/Core/Logger.h>

namespace dx3d
{
    #define DX_3D_GRAPHICS_ON_FAIL_THROW(hr, message)\
    {\
        auto res = (hr);\
        if (FAILED(res))\
            DX3DLogErrorAndThrow(message);\
    }
}