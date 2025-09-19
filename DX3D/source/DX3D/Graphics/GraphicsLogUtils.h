#pragma once
#include <DX3D/Core/Logger.h>

namespace dx3d
{
    #define DX_3D_GRAPHICS_ON_FAIL_THROW(hr, errorMessage)\
        {\
            auto res = (hr);\
            if (FAILED(hr))\
                DX3DLogErrorAndThrow(errorMessage);\
        }
}
