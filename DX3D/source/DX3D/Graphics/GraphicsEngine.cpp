#include "GraphicsEngine.h"

#include <DX3D/Graphics/DeviceContext.h>
#include <DX3D/Graphics/GraphicsDevice.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Graphics/SwapChain.h>
#include <DX3D/Graphics/VertexBuffer.h>
#include <DX3D/Math/Vec3.h>
#include <fstream>

using namespace dx3d;

dx3d::GraphicsEngine::GraphicsEngine(const GraphicsEngineDesc& desc): Base(desc.base)
{
    m_graphics_device_ = std::make_shared<GraphicsDevice>(GraphicsDeviceDesc{m_logger_});

    auto& device = *m_graphics_device_;
    m_device_context_ = device.createDeviceContext();

    constexpr char shaderFilePath[] = "DX3D/Assets/Shaders/Basic.hlsl";
    std::ifstream shaderStream(shaderFilePath);
    if (!shaderStream) DX3DLogThrowError("Failed to read shader file");
    std::string shaderFileData{
        std::istreambuf_iterator<char>(shaderStream),
        std::istreambuf_iterator<char>()
    };

    auto shaderSourceCode = shaderFileData.c_str();
    auto shaderSourceCodeSize = shaderFileData.length();
    
    auto vs = device.compileShader({shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "VSMain", ShaderType::Vertex});
    auto ps = device.compileShader({shaderFilePath, shaderSourceCode, shaderSourceCodeSize, "PSMain", ShaderType::Pixel});

    auto vertexSignature = device.createVertexShaderSignature({vs});
    
    m_pipeline_ = device.createGraphicsPipelineState({*vertexSignature, *ps});

    const Vertex vertexList[] =
    {
        {{-.5f, -.5f, 0}, {1,0,0,1}},    
        {{-.5f, .5f, 0}, {0,1,0,1}},
        {{.5f, .5f, 0}, {0,0,1,1}},
        
        {{.5f, .5f, 0}, {0,0,1,1}},
        {{.5f, -.5f, 0}, {1,0,1,1}},
        {{-.5f, -.5f, 0}, {1,0,0,1}},
    };
    
    m_vertex_buffer_ = device.createVertexBuffer({vertexList, std::size(vertexList), sizeof(Vertex)});
}

dx3d::GraphicsEngine::~GraphicsEngine()
{
}

dx3d::GraphicsDevice& dx3d::GraphicsEngine::getGraphicsDevice() noexcept
{
    return *m_graphics_device_;
}

void dx3d::GraphicsEngine::render(SwapChain& swap_chain)
{
    auto& context = *m_device_context_;
    context.clearAndSetBackBuffer(swap_chain, { 0.4f,0.3f,0.8f,1 });
    context.setGraphicsPipelineState(*m_pipeline_);

    context.setViewportSize(swap_chain.getSize());
    
    auto& vb = *m_vertex_buffer_;
    context.setVertexBuffer(vb);
    context.drawTriangleList(vb.getVertexListSize(), 0);
    
    auto& device = *m_graphics_device_;
    device.executeCommandList(context);
    swap_chain.present();
}
