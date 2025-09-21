#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
    class VertexBuffer final: public GraphicsResource
    {
    public:
        VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gdesc);
        ui32 getVertexListSize() const noexcept;

    private:
        Microsoft::WRL::ComPtr<ID3D11Buffer> m_buffer_{};
        ui32 m_stride_{};
        ui32 m_vertex_list_size{};
        
        friend class DeviceContext;
    };
}
