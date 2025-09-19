#pragma once
#include <DX3D/Core/Core.h>
#include <DX3D/Core/Base.h>

namespace dx3d
{
    class GraphicsEngine final: public Base
    {
    public:
        explicit GraphicsEngine(const GraphicsEngineDesc& desc);
        virtual ~GraphicsEngine() override;

        GraphicsDevice& getGraphicsDevice() noexcept;

        void render(SwapChain& swap_chain);
    private:
        std::shared_ptr<GraphicsDevice> m_graphics_device_{};
        DeviceContextPtr m_device_context_{};
    };
}