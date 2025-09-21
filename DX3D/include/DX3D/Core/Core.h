#pragma once
#include <stdexcept>
#include <memory>



namespace dx3d
{
    class Base;
    class DeviceContext;
    class Display;
    class Game;
    class GraphicsDevice;
    class GraphicsEngine;
    class GraphicsPipelineState;
    class Logger;
    class ShaderBinary;
    class SwapChain;
    class Window;
    class VertexBuffer;
    class VertexShaderSignature;

    using i32 = int;
    using ui32 = unsigned int;
    using f32 = float;
    using d64 = double;

    using SwapChainPtr = std::shared_ptr<SwapChain>;
    using DeviceContextPtr = std::shared_ptr<DeviceContext>;
    using ShaderBinaryPtr = std::shared_ptr<ShaderBinary>;
    using GraphicsPipelineStatePtr = std::shared_ptr<GraphicsPipelineState>;
    using VertexBufferPtr = std::shared_ptr<VertexBuffer>;
    using VertexShaderSignaturePtr = std::shared_ptr<VertexShaderSignature>;
}
