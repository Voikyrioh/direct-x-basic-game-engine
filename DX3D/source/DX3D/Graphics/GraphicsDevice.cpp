#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>
#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/SwapChain.h>

using namespace dx3d;


GraphicsDevice::GraphicsDevice(const GraphicsDeviceDesc& desc): Base(desc.base)
{
    D3D_FEATURE_LEVEL featureLevel{};
    UINT createDeviceFlags{};

#ifdef _DEBUG
    createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(D3D11CreateDevice(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, createDeviceFlags,
            NULL, 0, D3D11_SDK_VERSION,
            &m_d3d_device_, &featureLevel, &m_d3d_context_),
        "D3D11 Fail initializing Renderer")
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_d3d_device_->QueryInterface(IID_PPV_ARGS(&m_dxgi_device_)),
        "QueryInterface failed to retrieve GPU.")

    DX_3D_GRAPHICS_ON_FAIL_THROW(m_dxgi_device_->GetParent(IID_PPV_ARGS(&m_dxgi_adapter_)),
        "GetParent failed to retrieve DXGIDevice.")

    DX_3D_GRAPHICS_ON_FAIL_THROW(m_dxgi_adapter_->GetParent(IID_PPV_ARGS(&m_dxgi_factory_)),
        "GetParent failed to retrieve DXGIFactory.")
    
}

GraphicsDevice::~GraphicsDevice()
{
}

SwapChainPtr GraphicsDevice::createSwapChain(const SwapChainDesc& desc)
{
    return std::make_shared<SwapChain>(desc, getGraphicResourceDesc());
}

DeviceContextPtr GraphicsDevice::createDeviceContext()
{
    return std::make_shared<DeviceContext>(getGraphicResourceDesc());
}

ShaderBinaryPtr GraphicsDevice::compileShader(const ShaderCompileDesc& desc)
{
    return std::make_shared<ShaderBinary>(desc, getGraphicResourceDesc());
}

GraphicsPipelineStatePtr GraphicsDevice::createGraphicsPipelineState(const GraphicsPipelineStateDesc& desc)
{
    return std::make_shared<GraphicsPipelineState>(desc, getGraphicResourceDesc());
}

void GraphicsDevice::executeCommandList(DeviceContext& context)
{
    Microsoft::WRL::ComPtr<ID3D11CommandList> list{};
    DX_3D_GRAPHICS_ON_FAIL_THROW(context.m_context_->FinishCommandList(false, &list),
        "Failed to finish command list.")
    m_d3d_context_->ExecuteCommandList(list.Get(), false);
}

graphicsResourceDesc GraphicsDevice::getGraphicResourceDesc() const noexcept
{
    return  {{m_logger_}, shared_from_this(), *m_d3d_device_.Get(), *m_dxgi_factory_.Get() };
}
