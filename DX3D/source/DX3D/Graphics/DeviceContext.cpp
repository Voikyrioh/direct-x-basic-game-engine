
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/VertexBuffer.h>

dx3d::DeviceContext::DeviceContext(const GraphicsResourceDesc& gdesc): GraphicsResource(gdesc)
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
    m_context_->IASetInputLayout(pipeline.m_layout_.Get());
    m_context_->VSSetShader(pipeline.m_vertex_shader_.Get(), nullptr, 0);
    m_context_->PSSetShader(pipeline.m_pixel_shader_.Get(), nullptr, 0);
}

void dx3d::DeviceContext::setVertexBuffer(const VertexBuffer& buffer)
{
    auto stride = buffer.m_stride_;
    auto buf = buffer.m_buffer_.Get();
    auto offset = 0u;
    
    m_context_->IASetVertexBuffers(0, 1, &buf, &stride, &offset);
}

void dx3d::DeviceContext::setViewportSize(const Rect& size)
{
    D3D11_VIEWPORT viewport{};
    viewport.Width = static_cast<f32>(size.width);
    viewport.Height = static_cast<f32>(size.height);
    viewport.MinDepth = 0.0f;
    viewport.MaxDepth = 1.0f;

    m_context_->RSSetViewports(1, &viewport);
}

void dx3d::DeviceContext::drawTriangleList(ui32 vertex_count, ui32 start_vertex_location)
{
    m_context_->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    m_context_->Draw(vertex_count, start_vertex_location);   
}
