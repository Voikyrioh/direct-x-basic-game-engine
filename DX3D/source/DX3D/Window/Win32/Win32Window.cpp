#include <DX3D/Window/Window.h>
#include <Windows.h>
#include <stdexcept>


static LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
        case WM_CLOSE:
            {
                PostQuitMessage(0);
                break;
            }
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

dx3d::Window::Window(const WindowDesc& desc): Base(desc.base), m_size_(desc.size)
{
    auto register_window_class_function = []()
    {
        WNDCLASSEX wc{};
        wc.cbSize = sizeof(WNDCLASSEX);
        wc.lpszClassName = L"DX3DWindow";
        wc.lpfnWndProc = &WindowProcedure;
        return RegisterClassEx(&wc);
    };
    
    static const auto window_class_id = std::invoke(register_window_class_function);
    
    if (!window_class_id) DX3DLogErrorAndThrow("Window class registration failed!")
    
    
    RECT rc{0,0,m_size_.width,m_size_.height};
    AdjustWindowRect(&rc, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, false);
    
    m_handle_ = CreateWindowEx(NULL, MAKEINTATOM(window_class_id), L"DX DirectX Direct3D Window",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, CW_USEDEFAULT, CW_USEDEFAULT,
        rc.right - rc.left, rc.bottom - rc.top,
        NULL, NULL, NULL, NULL);

    if (!m_handle_) DX3DLogErrorAndThrow("Window creation failed!")

    ShowWindow(static_cast<HWND>(m_handle_), SW_SHOW);
}

dx3d::Window::~Window()
{
    DestroyWindow(static_cast<HWND>(m_handle_));
}
