#include <DX3D/Graphics/ShaderBinary.h>
#include <DX3D/Graphics/GraphicsUtils.h>
#include <d3dcompiler.h>

dx3d::ShaderBinary::ShaderBinary(const ShaderCompileDesc& desc, const GraphicsResourceDesc& gdesc): GraphicsResource(gdesc), m_type_(desc.shader_type)
{
    if (!desc.shader_source_name) DX3DLogThrowInvalidArg("No shader source name provided")
    if (!desc.shader_source_code) DX3DLogThrowInvalidArg("No shader source code provided")
    if (!desc.shader_source_code_size) DX3DLogThrowInvalidArg("No shader source size provided")
    if (!desc.shader_entry_point) DX3DLogThrowInvalidArg("No shader entry point provided")
    
    UINT compileFlags{};

#ifdef _DEBUG
    compileFlags |= D3DCOMPILE_DEBUG;
#endif

    Microsoft::WRL::ComPtr<ID3DBlob> errorBlob{};
    
    DX_3D_GRAPHICS_CHECK_SHADER_COMPILE(
    D3DCompile(
        desc.shader_source_code,
        desc.shader_source_code_size,
        desc.shader_source_name,
        nullptr,
        nullptr,
        desc.shader_entry_point,
        dx3d::GraphicsUtils::GetShaderModelTarget(desc.shader_type),
        compileFlags,
        0,
        &m_binary_blob_,
        &errorBlob
    ),
    errorBlob.Get())
}

dx3d::BinaryData dx3d::ShaderBinary::getData() const noexcept
{
    return {
        m_binary_blob_->GetBufferPointer(),
        m_binary_blob_->GetBufferSize()
    };   
}

dx3d::ShaderType dx3d::ShaderBinary::getType() const noexcept
{
    return m_type_;
}
