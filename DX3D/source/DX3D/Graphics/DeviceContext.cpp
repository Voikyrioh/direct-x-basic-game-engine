
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

#include "GraphicsPipelineState.h"

dx3d::DeviceContext::DeviceContext(const graphicsResourceDesc& gdesc): GraphicsResource(gdesc)
{
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_device_.CreateDeferredContext(0, &m_context_),
        "CreateDeferredContext failed.")
}

void dx3d::DeviceContext::clearAndSetBackBuffer(const SwapChain& swap_chain, const Vec4& color)
{
    f32 fColor[] = { color.x,color.y,color.z,color.w };
    auto rtv = swap_chain.m_rtv_.Get();
    m_context_->ClearRenderTargetView(rtv, fColor);
    m_context_->OMSetRenderTargets(1, &rtv, nullptr);
}

void dx3d::DeviceContext::setGraphicsPipelineState(const GraphicsPipelineState& pipeline)
{
    m_context_->VSSetShader(pipeline.m_vertex_shader_.Get(), nullptr, 0);
    m_context_->PSSetShader(pipeline.m_pixel_shader_.Get(), nullptr, 0);
}
