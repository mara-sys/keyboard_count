#ifndef KEYBOARD_KEYBOARD_H
#define KEYBOARD_KEYBOARD_H

#include "global.h"

#include <Windows.h>
#include <fstream>
#include <sstream>
#include <string>

LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam);



#endif