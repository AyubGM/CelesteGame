#include <iostream>
#include "Application.h"
#include "Input.h"


int main()
{

    g_InputState.ScreenSizeX = 1200;
    g_InputState.ScreenSizeY = 720;
    if (CelesteGame::Application::Get().Init(g_InputState.ScreenSizeX, g_InputState.ScreenSizeY, "Celeste")) {
        CelesteGame::Application::Get().Run();
    }


}

