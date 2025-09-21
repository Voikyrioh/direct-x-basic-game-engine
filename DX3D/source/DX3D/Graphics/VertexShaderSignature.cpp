#include <DX3D/Graphics/VertexShaderSignature.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <DX3D/Graphics/ShaderBinary.h>
#include <d3dcompiler.h>
#include <ranges>

dx3d::VertexShaderSignature::VertexShaderSignature(const VertexShaderSignatureDesc desc, const GraphicsResourceDesc& gdesc):
    GraphicsResource(gdesc), m_vertex_shader_binary_(desc.binary_ptr)
{
    if (!desc.binary_ptr) DX3DLogThrowInvalidArg("No vertex shader binary provided")
    if (desc.binary_ptr->getType() != ShaderType::Vertex) DX3DLogThrowInvalidArg("Vertex shader binary is not a vertex shader")

    auto vertexShaderData = desc.binary_ptr->getData();
    
    DX_3D_GRAPHICS_ON_FAIL_THROW(
        D3DReflect(
        vertexShaderData.data,
        vertexShaderData.size,
        IID_PPV_ARGS(&m_vertex_shader_reflection_)
    ),
    "D3DReflect failed")

    D3D11_SHADER_DESC shaderDesc{};
    DX_3D_GRAPHICS_ON_FAIL_THROW(m_vertex_shader_reflection_->GetDesc(&shaderDesc),
    "GetDesc on shader reflection failed")

    m_num_elements_ = shaderDesc.InputParameters;

    D3D11_SIGNATURE_PARAMETER_DESC params[D3D11_STANDARD_VERTEX_ELEMENT_COUNT];
    for (auto i : std::views::iota(0u, m_num_elements_))
    {
        DX_3D_GRAPHICS_ON_FAIL_THROW(m_vertex_shader_reflection_->GetInputParameterDesc(i, &params[i]),
            "failed to retrieve GetInputParameterDesc on shader reflection")
    }

    for (auto i : std::views::iota(0u, m_num_elements_))
    {
        auto param = params[i];
        m_elements_[i] = {
            param.SemanticName,
            param.SemanticIndex,
            GraphicsUtils::GetDXGIFormatFromMask(param.ComponentType, param.Mask),
            0,
            D3D11_APPEND_ALIGNED_ELEMENT,
            D3D11_INPUT_PER_VERTEX_DATA,
            0
        };
    }
}

dx3d::BinaryData dx3d::VertexShaderSignature::getShaderBinaryData() const noexcept
{
    return m_vertex_shader_binary_->getData();
}

dx3d::BinaryData dx3d::VertexShaderSignature::getInputElementsData() const noexcept
{
    return
    {
        m_elements_,
        m_num_elements_
    };
}
