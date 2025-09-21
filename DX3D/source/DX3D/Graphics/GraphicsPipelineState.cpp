#include <DX3D/Graphics/GraphicsPipelineState.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/VertexShaderSignature.h>

dx3d::GraphicsPipelineState::GraphicsPipelineState(const GraphicsPipelineStateDesc& desc, const GraphicsResourceDesc& gdesc): GraphicsResource(gdesc)
{
    if (desc.pixel_shader.getType() != ShaderType::Pixel)
        DX3DLogThrowInvalidArg("Pixel shader is not a valid pixel shader")
    
    auto vertexShader = desc.vertex_shader.getShaderBinaryData();
    auto pixelShader = desc.pixel_shader.getData();
    auto elements = desc.vertex_shader.getInputElementsData();
    
    

    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreateInputLayout(
            static_cast<const D3D11_INPUT_ELEMENT_DESC*>(elements.data),
            static_cast<const ui32>(elements.size),
            vertexShader.data,
            vertexShader.size,
            &m_layout_
            ),
        "CreateInputLayout failed")
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreateVertexShader(vertexShader.data, vertexShader.size, nullptr, &m_vertex_shader_),
        "CreateVertexShader failed")
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        m_device_.CreatePixelShader(pixelShader.data, pixelShader.size, nullptr, &m_pixel_shader_),
        "CreatePixelShader failed")
}
