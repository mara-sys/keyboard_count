#include "keyboard.h"

#include <iostream>

std::string GetKeyName(int vkCode, DWORD scanCode) {
    char keyName[256] = {0};

    // 组合扫描码和扩展键标志
    LONG lParam = (scanCode << 16);
    if (vkCode == VK_RSHIFT || vkCode == VK_RCONTROL || vkCode == VK_RMENU) {
        lParam |= (1 << 24); // 设置扩展键标志位
    }

    // 获取按键名称
    if (GetKeyNameTextA(lParam, keyName, sizeof(keyName)) != 0) {
        return keyName;
    }
    return "[Unknown]"; 
}

// 键盘钩子回调函数
LRESULT CALLBACK LowLevelKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT* p = (KBDLLHOOKSTRUCT*)lParam;

        // if (p->vkCode == 'Q' && GetAsyncKeyState(VK_CONTROL) && 
        //     GetAsyncKeyState(VK_SHIFT)) {
        //         std::cout << "quit\n";
        //         running = false;
        // }

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {

            int vkCode = p->vkCode;
            DWORD scanCode = p->scanCode;

            std::string keyName = GetKeyName(vkCode, scanCode);

            keyCounts[keyName]++;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}