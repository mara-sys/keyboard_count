#include "window.h"

#include <iostream>
#include <Windows.h>

void HideConsole()
{
    HWND hwnd = GetConsoleWindow();
    if (hwnd)
        ShowWindow(hwnd, SW_HIDE);
}
