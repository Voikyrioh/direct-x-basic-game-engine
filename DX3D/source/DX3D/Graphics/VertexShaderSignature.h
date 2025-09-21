#pragma once
#include <d3d11shader.h>
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
    class VertexShaderSignature final: public GraphicsResource
    {
    public:
        VertexShaderSignature(const VertexShaderSignatureDesc desc, const GraphicsResourceDesc& gdesc);
        BinaryData getShaderBinaryData()const noexcept;
        BinaryData getInputElementsData() const noexcept;
    private:
        ShaderBinaryPtr m_vertex_shader_binary_{};
        Microsoft::WRL::ComPtr<ID3D11ShaderReflection> m_vertex_shader_reflection_{};
        D3D11_INPUT_ELEMENT_DESC m_elements_[D3D11_STANDARD_VERTEX_ELEMENT_COUNT];
        ui32 m_num_elements_{};
    };   
}
