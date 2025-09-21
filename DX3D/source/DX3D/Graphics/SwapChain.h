#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
    class SwapChain final: public GraphicsResource
    {
    public:
        SwapChain(const SwapChainDesc& desc, const GraphicsResourceDesc& gdesc);
        Rect getSize() const noexcept;
        void present(bool vsync = false);
    private:
        void reloadBuffers();
    private:
        Microsoft::WRL::ComPtr<IDXGISwapChain> m_swap_chain_{};
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_rtv_{};
        Rect m_size_{};

        friend class DeviceContext;
    };

}
