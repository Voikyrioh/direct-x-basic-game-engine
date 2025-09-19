#pragma once
#include <DX3D/Graphics/GraphicsResource.h>

namespace dx3d
{
    class ShaderBinary final: public GraphicsResource
    {
    public:
        ShaderBinary(const ShaderCompileDesc& desc, const graphicsResourceDesc& gdesc);
        ShaderBinaryData getData() const noexcept;
        ShaderType getType() const noexcept;

    private:
        Microsoft::WRL::ComPtr<ID3DBlob> m_binary_blob_{};
        ShaderType m_type_{};
    };
}
