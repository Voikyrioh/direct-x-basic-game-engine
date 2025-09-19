#include <DX3D/Game/Game.h>
#include <DX3D/Window/Window.h>
#include <DX3D/Graphics/GraphicsEngine.h>
#include <DX3D/Core/Logger.h>
#include <DX3D/Game/Display.h>

dx3d::Game::Game(const GameDesc& desc):
    Base({*std::make_unique<Logger>(desc.logLevel).release()}),
    m_logger_ptr(&m_logger_)
{
    m_graphics_engine_ = std::make_unique<GraphicsEngine>(GraphicsEngineDesc{m_logger_});
    m_display_ = std::make_unique<Display>(DisplayDesc{ {m_logger_,desc.window_size},m_graphics_engine_->getGraphicsDevice()});

    DX3LogInfo("Game initialized.")
}

dx3d::Game::~Game()
{
    DX3LogInfo("Game is shutting down.")   
}

void dx3d::Game::onInternalUpdate()
{
    m_graphics_engine_->render(m_display_->getSwapChain());
}