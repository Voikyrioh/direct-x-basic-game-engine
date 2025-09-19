#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
    class DeviceContext final: public GraphicsResource
    {
    public:
        explicit DeviceContext(const graphics_resource_desc& gdesc);
        void clearAndSetBackBuffer(const SwapChain& swap_chain, const Vec4& color);

    private:
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context_{};

        friend class GraphicsDevice;
    };
}
