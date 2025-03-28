#ifndef KEYBOARD_GLOBAL_H
#define KEYBOARD_GLOBAL_H

#include <map>
#include <string>

extern std::map<std::string, long long> keyCounts;      ///< 按键计数器
extern bool running;                     ///< 程序运行标志
extern const char* LOG_FILE;     ///< 日志文件


#endif