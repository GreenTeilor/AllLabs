#include <Windows.h>
#include <iostream>
#include <string>

#include "MainActivity.hpp"

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE,  LPSTR szCmdLine, int nCmdShow)
{
    MainActivity app{"Lab2/assets/text.txt"};
    return app.run();
}
