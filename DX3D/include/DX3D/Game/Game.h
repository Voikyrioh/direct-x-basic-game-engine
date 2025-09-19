#pragma once
#include <DX3D/Core/Base.h>
#include <DX3D/Core/Core.h>

namespace dx3d
{
    class Game: public Base
    {
    public:
        explicit Game(const GameDesc& desc);
        virtual ~Game() override;

        virtual void run() final;
    private:
        void onInternalUpdate();
    private:
        std::unique_ptr<Logger> m_logger_ptr{};
        std::unique_ptr<GraphicsEngine> m_graphics_engine_{};
        std::unique_ptr<Display> m_display_{};
        bool m_is_running_{ true };
    };
}
