#include <DX3D/Game/Display.h>
#include <DX3D/Graphics/GraphicsDevice.h>

dx3d::Display::Display(const DisplayDesc& desc): Window(desc.window)
{
    m_swap_chain_ = desc.graphics_device.createSwapChain({ m_handle_, m_size_ });
}

dx3d::SwapChain& dx3d::Display::getSwapChain() noexcept
{
    return *m_swap_chain_;
}
