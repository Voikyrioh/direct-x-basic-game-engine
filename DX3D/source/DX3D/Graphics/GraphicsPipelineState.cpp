#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const graphicsResourceDesc& gdesc): GraphicsResource(gdesc)
{
    if (desc.vertex_shader.getType() != ShaderType::Vertex)
        DX3DLogThrowInvalidArg("Vertex shader is not a valid vertex shader")

    if (desc.pixel_shader.getType() != ShaderType::Pixel)
        DX3DLogThrowInvalidArg("Pixel shader is not a valid pixel shader")
    
    auto vertexShader = desc.vertex_shader.getData();
    auto pixelShader = desc.pixel_shader.getData();
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreateVertexShader(vertexShader.data, vertexShader.size, nullptr, &m_vertex_shader_),
        "CreateVertexShader failed")
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreatePixelShader(pixelShader.data, pixelShader.size, nullptr, &m_pixel_shader_),
        "CreatePixelShader failed")
}
