#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

#include <DX3D/Math/Vec3.h>
#include <DX3D/Math/Vec4.h>

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
        struct Vertex
        {
            Vec3 position;
            Vec4 color;
        };
    private:
        std::shared_ptr<GraphicsDevice> m_graphics_device_{};
        DeviceContextPtr m_device_context_{};
        GraphicsPipelineStatePtr m_pipeline_{};
        VertexBufferPtr m_vertex_buffer_{};
    };
}
