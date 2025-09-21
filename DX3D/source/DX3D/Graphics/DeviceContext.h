#pragma once
#include <DX3D/Graphics/GraphicsResource.h>
#include <DX3D/Math/Vec4.h>

#include "VertexBuffer.h"

namespace dx3d
{
    class DeviceContext final: public GraphicsResource
    {
    public:
        explicit DeviceContext(const GraphicsResourceDesc& gdesc);
        void clearAndSetBackBuffer(const SwapChain& swap_chain, const Vec4& color);
        void setGraphicsPipelineState(const GraphicsPipelineState& pipeline);
        void setVertexBuffer(const VertexBuffer& buffer);
        void setViewportSize(const Rect& size);
        void drawTriangleList(ui32 vertex_count, ui32 start_vertex_location);

    private:
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_context_{};

        friend class GraphicsDevice;
    };
}
