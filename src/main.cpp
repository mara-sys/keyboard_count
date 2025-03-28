#include "window.h"
#include "keyboard.h"
#include "log.h"

#include <iostream>
#include <Windows.h>
#include <thread>

int main()
{
    std::cout << "keyboard count started!!!\n";

    HideConsole();

    LoadLog();

    // 安装键盘钩子
    HHOOK keyboardHook = SetWindowsHookEx(
        WH_KEYBOARD_LL,
        LowLevelKeyboardProc,
        GetModuleHandle(NULL),
        0
    );

    if (!keyboardHook) {
        return 1;
    }

    // 定时保存线程
    std::thread logThread([] {
        while (running) {
            std::this_thread::sleep_for(std::chrono::seconds(30)); // 每30秒保存一次
            SaveLog();
        }
    });

    // 消息循环
    MSG msg;
    while (running && GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // 清理
    running = false;
    logThread.join();
    UnhookWindowsHookEx(keyboardHook);
    SaveLog(); // 最后一次保存
    std::cout << "quit~~~\n";
    
    return 0;
}