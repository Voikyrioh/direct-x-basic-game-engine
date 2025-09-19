
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

dx3d::DeviceContext::DeviceContext(const graphics_ressource_desc& gdesc): GraphicsRessource(gdesc)
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
