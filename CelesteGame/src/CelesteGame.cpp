#include <iostream>
#include "Application.h"


int main()
{
    if (CelesteGame::Application::Get().Init(1200, 720, "Celeste")) {
        CelesteGame::Application::Get().Run();
    }


}

