#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
    m_graphics_device_ = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger_});

    auto& device = *m_graphics_device_;
    m_device_context_ = device.createDeviceContext();
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

dx3d::GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
    return *m_graphics_device_;
}

void dx3d::GraphicsEngine::render(SwapChain& swap_chain)
{
    auto& context = *m_device_context_;
    context.clearAndSetBackBuffer(swap_chain, { 0.4,0.3,0.8,1 });
    
    auto& device = *m_graphics_device_;
    device.executeCommandList(context);
    swap_chain.present();
}
