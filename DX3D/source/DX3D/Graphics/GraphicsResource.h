#pragma once
#include <DX3D/Core/Common.h>
#include <DX3D/Core/Base.h>
#include <DX3D/Graphics/GraphicsLogUtils.h>

#include <d3d11.h>
#include <wrl.h>

namespace dx3d
{
    struct graphics_resource_desc
    {
        BaseDesc base;
        std::shared_ptr<const GraphicsDevice> graphics_device;
        ID3D11Device& device;
        IDXGIFactory& factory;
    };
    
    class GraphicsResource : public Base
    {
    public:
        explicit GraphicsResource(const graphics_resource_desc& desc):
            Base(desc.base),
            m_graphics_device_(desc.graphics_device),
            m_device_(desc.device),
            m_factory_(desc.factory)
        {
        }
    protected:
        std::shared_ptr<const GraphicsDevice> m_graphics_device_;
        ID3D11Device& m_device_;
        IDXGIFactory& m_factory_;
    };
}
