#include "Application.h"
#include "Logger.h"
#include "Renderer.h"
#include "Utils.h"
#include "Input.h"
#include <filesystem>
#include "../vendor/glcorearb.h"
#include "../vendor/wglext.h"

namespace CelesteGame {

	Application::Application() : m_TransientStorage(MB(50))
    {
    
        std::error_code ec;
        auto cwd = std::filesystem::current_path(ec);
        if (!ec) {
            SD_TRACE("Current working directory: {}", cwd.string());
        }
        else {
            SD_ERROR("Failed to get current_path: {}", ec.message());
        }
    }

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

        // WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX
        int dwStyle = WS_OVERLAPPEDWINDOW;

        PFNWGLCHOOSEPIXELFORMATARBPROC wglChoosePixelFormatARB = nullptr;
        PFNWGLCREATECONTEXTATTRIBSARBPROC wglCreateContextAttribsARB = nullptr;
        {
        m_Window = CreateWindowExA(0, title.c_str(), title.c_str(),
            dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
            width, height, NULL, NULL, instance, NULL);

        if (!m_Window) return false;

        

            HDC fakeDC = GetDC(m_Window);
            if (!fakeDC)
            {
                SD_ASSERT(false, "Faild to get HDC");
                return false;
            }

            PIXELFORMATDESCRIPTOR pfd = { 0 };
            pfd.nSize = sizeof(pfd);
            pfd.nVersion = 1;
            pfd.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
            pfd.cColorBits = 32;
            pfd.cAlphaBits = 8;
            pfd.cDepthBits = 24;

            int pixelFormat = ChoosePixelFormat(fakeDC, &pfd);
            if (!pixelFormat)
            {
                SD_ASSERT(false, "Faild to choose picxel Format");
                return false;
            }

            if (!SetPixelFormat(fakeDC, pixelFormat, &pfd))
            {
                SD_ASSERT(false, "Faild to set pixel format");
                return false;
            }

            HGLRC fakeRC = wglCreateContext(fakeDC);
            if (!fakeRC)
            {
                SD_ASSERT(false, "Faild tp create Render context");
                return false;
            }

            if (!wglMakeCurrent(fakeDC, fakeRC))
            {
                SD_ASSERT(false, "Faild to make current");
                return false;
            }

            wglChoosePixelFormatARB =
                (PFNWGLCHOOSEPIXELFORMATARBPROC)PlatformLoadGLFunction("wglChoosePixelFormatARB");

            wglCreateContextAttribsARB =
                (PFNWGLCREATECONTEXTATTRIBSARBPROC)PlatformLoadGLFunction("wglCreateContextAttribsARB");

            if (!wglChoosePixelFormatARB || !wglCreateContextAttribsARB)
            {
                SD_ASSERT(false, "Faild to load OpenGL functions");
                return false;
            }

            //Clean up
            wglMakeCurrent(fakeDC, 0);
            wglDeleteContext(fakeRC);
            ReleaseDC(m_Window, fakeDC);

            DestroyWindow(m_Window);
        }

        // Actual OpengGl init
        {
            // Add in the border size of the window
            {
                RECT borderRect = {};
                AdjustWindowRectEx(&borderRect, dwStyle, 0, 0);

                width += borderRect.right - borderRect.left;
                height += borderRect.bottom - borderRect.top;
            }

            m_Window = CreateWindowExA(0, title.c_str(), title.c_str(),
                dwStyle, CW_USEDEFAULT, CW_USEDEFAULT,
                width, height, NULL, NULL, instance, NULL);

            if (!m_Window) return false;

            m_Dc = GetDC(m_Window);
            if (!m_Dc)
            {
                SD_ASSERT(false, "Faild to get HDC");
                return false;
            }

            const int pixelAttribs[] =
            {
              WGL_DRAW_TO_WINDOW_ARB, GL_TRUE,
              WGL_SUPPORT_OPENGL_ARB, GL_TRUE,
              WGL_DOUBLE_BUFFER_ARB,  GL_TRUE,
              WGL_SWAP_METHOD_ARB,    WGL_SWAP_COPY_ARB,
              WGL_PIXEL_TYPE_ARB,     WGL_TYPE_RGBA_ARB,
              WGL_ACCELERATION_ARB,   WGL_FULL_ACCELERATION_ARB,
              WGL_COLOR_BITS_ARB,     32,
              WGL_ALPHA_BITS_ARB,     8,
              WGL_DEPTH_BITS_ARB,     24,
              0 // Terminate with 0, otherwise OpenGL will throw an Error!
            };

            UINT numPixelFormats;
            int pixelFormat = 0;
            if (!wglChoosePixelFormatARB(m_Dc, pixelAttribs,
                0, // Float List
                1, // Max Formats
                &pixelFormat,
                &numPixelFormats))
            {
                SD_ASSERT(0, "Failed to wglChoosePixelFormatARB");
                return false;
            }

            PIXELFORMATDESCRIPTOR pfd = { 0 };
            DescribePixelFormat(m_Dc, pixelFormat, sizeof(PIXELFORMATDESCRIPTOR), &pfd);

            if (!SetPixelFormat(m_Dc, pixelFormat, &pfd))
            {
                SD_ASSERT(0, "Failed to SetPixelFormat");
                return true;
            }

            const int contextAttribs[] =
            {
              WGL_CONTEXT_MAJOR_VERSION_ARB, 4,
              WGL_CONTEXT_MINOR_VERSION_ARB, 3,
              WGL_CONTEXT_PROFILE_MASK_ARB, WGL_CONTEXT_CORE_PROFILE_BIT_ARB,
              WGL_CONTEXT_FLAGS_ARB, WGL_CONTEXT_DEBUG_BIT_ARB,
              0 // Terminate the Array
            };

            HGLRC rc = wglCreateContextAttribsARB(m_Dc, 0, contextAttribs);
            if (!rc)
            {
                SD_ASSERT(0, "Failed to crate Render Context for OpenGL");
                return false;
            }

            if (!wglMakeCurrent(m_Dc, rc))
            {
                SD_ASSERT(0, "Faield to wglMakeCurrent");
                return false;
            }

        }

        ShowWindow(m_Window, SW_SHOW);
        m_Running = true;

        GLInit(m_TransientStorage);
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

            GLRender();
            SwapBuffers(m_Dc);
        }
    }

    LRESULT CALLBACK Application::WindowCallbackFn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
        
        Application& app = Application::Get();

        switch (msg) {
        case WM_CLOSE:
        {
            app.m_Running = false;
            return 0;
        }
        case WM_SIZE:
        {
            /*RECT rect = {};
            GetClientRect(app.m_Window, &rect);
            g_InputState.ScreenSizeX = rect.right - rect.left;
            g_InputState.ScreenSizeY = rect.bottom - rect.top;*/
            g_InputState.ScreenSizeX = LOWORD(lParam);
            g_InputState.ScreenSizeY = HIWORD(lParam);
            return 0;
        }
        }


        return DefWindowProcA(hwnd, msg, wParam, lParam);
    }
}