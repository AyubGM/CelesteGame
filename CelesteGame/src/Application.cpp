#include "Application.h"

namespace CelesteGame {

	Application::Application() {}

    Application::~Application() {}

    bool Application::Init(int width, int height, const std::string& title) {
        HINSTANCE instance = GetModuleHandle(0);

        WNDCLASSA wc = {};
        wc.hInstance = instance;
        wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.lpszClassName = title.c_str();
        wc.lpfnWndProc = Application::WindowCallbackFn;

        if (!RegisterClassA(&wc)) return false;

        m_Window = CreateWindowExA(0, title.c_str(), title.c_str(),
            WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
            width, height, NULL, NULL, instance, NULL);

        if (!m_Window) return false;

        ShowWindow(m_Window, SW_SHOW);
        m_Running = true;
        return true;
    }

    void Application::ProcessMessages() {
        MSG msg;
        while (PeekMessageA(&msg, m_Window, 0, 0, PM_REMOVE)) {
            TranslateMessage(&msg);
            DispatchMessageA(&msg);
        }
    }

    void Application::Run() {
        while (m_Running) {
            ProcessMessages();

        }
    }

    LRESULT CALLBACK Application::WindowCallbackFn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        
        Application& app = Application::Get();

        switch (msg) {
        case WM_CLOSE:
            app.m_Running = false;
            return 0;
        }
        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
}