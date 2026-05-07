#pragma once
#define WIN_LEAN_AND_MEAN
#define NOMINMAX
#include <Windows.h>
#include <string>

namespace CelesteGame {
	class Application
	{
	public:
		~Application();
		Application(const Application&) = delete;
		void operator=(const Application&) = delete;

		static Application& Get() {
			static Application instance;
			return instance;
		}

		bool Init(int width, int height, const std::string& title);
		void Run();
		void Shutdown();
		static LRESULT CALLBACK WindowCallbackFn(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	private:
		Application();
		void ProcessMessages();

	private:
		HWND m_Window = nullptr;
		bool m_Running = false;
	};



}