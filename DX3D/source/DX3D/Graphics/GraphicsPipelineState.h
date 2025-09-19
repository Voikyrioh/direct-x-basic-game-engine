#pragma once
#include "GraphicsResource.h"

namespace dx3d
{
    class GraphicsPipelineState final: public GraphicsResource
    {
    public:
        GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const graphicsResourceDesc& gdesc);

    private:
        Microsoft::WRL::ComPtr<ID3D11VertexShader> m_vertex_shader_{};
        Microsoft::WRL::ComPtr<ID3D11PixelShader> m_pixel_shader_{};

        friend class DeviceContext;
    };
}
