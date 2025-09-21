#include <DX3D/Graphics/VertexBuffer.h>

dx3d::VertexBuffer::VertexBuffer(const VertexBufferDesc& desc, const GraphicsResourceDesc& gdesc):
GraphicsResource(gdesc), m_stride_(desc.vertex_size), m_vertex_list_size(desc.list_size)
{
    if (!desc.vertex_list) DX3DLogThrowInvalidArg("No vertex list provided")
    if (!desc.vertex_size) DX3DLogThrowInvalidArg("Vertex size not provided")
    if (!desc.list_size) DX3DLogThrowInvalidArg("Vertex list size not provided")
    
    D3D11_BUFFER_DESC bufferDesc{};
    bufferDesc.ByteWidth = desc.vertex_size * desc.list_size;
    bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA initData{};
    initData.pSysMem = desc.vertex_list;
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreateBuffer(&bufferDesc, &initData, &m_buffer_),
        "CreateBuffer failed")
}

dx3d::ui32 dx3d::VertexBuffer::getVertexListSize() const noexcept
{
    return m_vertex_list_size;
}
