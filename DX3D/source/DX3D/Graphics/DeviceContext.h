#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

namespace dx3d
{
    class DeviceContext final: public GraphicsResource
    {
    public:
        explicit DeviceContext(const graphicsResourceDesc& gdesc);
        void clearAndSetBackBuffer(const SwapChain& swap_chain, const Vec4& color);
        void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);

    private:
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context_{};

        friend class GraphicsDevice;
    };
}
