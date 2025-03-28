#include "global.h"

std::map<std::string, long long> keyCounts;     ///< 按键计数器
bool running = true;                    ///< 程序运行标志
const char* LOG_FILE = "keylog.txt";    ///< 日志文件