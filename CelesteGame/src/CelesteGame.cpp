#include <iostream>
#define WIN_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>

static bool running = true;

HWND window;

LRESULT WindowCallbackFn(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (msg)
	{
	case WM_CLOSE:
	{
		running = false;
		break;
	}

	default:
		result = DefWindowProcA(window, msg, wParam, lParam);
		break;
	}

	return result;
}

void PlatformUpdateWindow()
{
	MSG msg;

	while (PeekMessageA(&msg, window, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}

}

bool PlatformCreateWindow(int width, int height, const char* title)
{
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = title;
	wc.lpfnWndProc = WindowCallbackFn;

	if (!RegisterClassA(&wc))
	{
		return false;
	}

	int dwStyle = WS_OVERLAPPEDWINDOW;

	window = CreateWindowExA(0, title, title, dwStyle, 100, 100, width, height, NULL, NULL, instance, NULL);

	if (window == NULL)
	{
		return false;
	}

	ShowWindow(window, SW_SHOW);

	return true;
}

int main()
{
	PlatformCreateWindow(1200, 720, "Celeste");


	while (running)
	{
		std::cout << "Hello World!\n";
		PlatformUpdateWindow();

	}
}

