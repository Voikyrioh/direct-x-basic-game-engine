#pragma once
#include <DX3D/Graphics/GraphicsRessource.h>

namespace dx3d
{
    class SwapChain final: public GraphicsRessource
    {
    public:
        SwapChain(const SwapChainDesc& desc, const graphics_ressource_desc& gdesc);
        
        void present(bool vsync = false);
    private:
        void reloadBuffers();
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap_chain_{};
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv_{};

        friend class DeviceContext;
    };

}
