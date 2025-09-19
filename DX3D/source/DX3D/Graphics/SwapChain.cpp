#include <DX3D/Graphics/SwapChain.h>

dx3d::SwapChain::SwapChain(const SwapChainDesc& desc, const graphics_ressource_desc& gdesc) :
GraphicsRessource(gdesc)
{
    DXGI_SWAP_CHAIN_DESC dxgiDesc{};

    dxgiDesc.BufferDesc.Width = std::max(1, desc.win_size.width);
    dxgiDesc.BufferDesc.Height = std::max(1, desc.win_size.height);
    dxgiDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    dxgiDesc.BufferCount = 2;
    dxgiDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    dxgiDesc.OutputWindow = static_cast<HWND>(desc.win_handle);
    dxgiDesc.SampleDesc.Count = 1;
    dxgiDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
    dxgiDesc.Windowed = TRUE;
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_factory_.CreateSwapChain(&m_device_, &dxgiDesc, &m_swap_chain_),
        "Swap chain creation failed")

    reloadBuffers();
}

void dx3d::SwapChain::present(bool vsync)
{
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_swap_chain_->Present(vsync, 0),
        "Present failed.")
}

void dx3d::SwapChain::reloadBuffers()
{
    Microsoft::WRL::ComPtr<ID3D11Texture2D> buffer{};
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_swap_chain_->GetBuffer(0, IID_PPV_ARGS(&buffer)),
        "GetBuffer failed.");
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_device_.CreateRenderTargetView(buffer.Get(), nullptr, &m_rtv_),
        "CreateRenderTargetView failed.");
}

