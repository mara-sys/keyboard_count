#include "log.h"

#include <algorithm>
#include <fstream>
#include <chrono>
#include <vector>
#include <iomanip>
#include <iostream>

bool LoadLog() {
    std::ifstream logFile(LOG_FILE);
    if (!logFile.is_open()) {
        return false; // 文件不存在或无权限，视为首次运行
    }
    std::cout << "reload log file\n";

    std::string line;
    while (getline(logFile, line)) {
        if (line.find("--------") != std::string::npos) {   // 找到 --------
            break;
        }

        // 忽略非统计行（如时间戳行）
        if (line.find("按键[") == std::string::npos) continue;

        // 解析格式："按键[A] : 42 次"
        size_t start = line.find('[') + 1;
        size_t end = line.find(']', start);
        if (start == std::string::npos || end == std::string::npos) continue;

        std::string key = line.substr(start, end - start);
        start = key.find_first_not_of(" \t");
        key = key.substr(start, end - start + 1);
        long long count = 0;

        // 提取次数
        size_t countStart = line.find(":", end) + 1;
        if (countStart != std::string::npos) {
            std::string countStr = line.substr(countStart);
            countStr.erase(remove_if(countStr.begin(), countStr.end(), 
                           [](char c) { return !isdigit(c); }), countStr.end());
            count = stoll(countStr);
        }

        // 合并到当前统计
        keyCounts[key] += count;
    }
    logFile.close();
    return true;
}

void SaveLog() {
    std::ofstream logFile(LOG_FILE);
    if (logFile.is_open()) {
        logFile << std::right;
        auto now = std::chrono::system_clock::now();
        time_t time = std::chrono::system_clock::to_time_t(now);

        // 使用安全的ctime_s版本
        char timeStr[26];
        if (ctime_s(timeStr, sizeof(timeStr), &time) == 0) {
            timeStr[24] = '\0'; // 去掉自动添加的换行符
            logFile << "按键统计日志 (" << timeStr << ")\n";
        }
        else {
            logFile << "按键统计日志 [时间获取失败]\n";
        }

        for (const auto& pair : keyCounts) {
            logFile << "按键[" << std::setw(10) << pair.first << "] : "
                << std::setw(10) << std::dec << pair.second << " 次\n";
        }

        SortByCount(logFile);

        logFile.close();
    }
}

void SortByCount(std::ofstream &logFile)
{
    std::vector<std::pair<std::string, int>> vec(keyCounts.begin(), keyCounts.end());

    // 按照值排序
    std::sort(vec.begin(), vec.end(),
        [](const std::pair<std::string, int>& a, const std::pair<std::string, int>& b) {
            return a.second < b.second; // 升序排序
        }
    );

    logFile << "--------------------------------------\n";
    for (const auto &pair : vec) {
        logFile << "按键[" << std::setw(10) << pair.first << "] : "
            << std::setw(10) << std::dec << pair.second << " 次\n";
    }
}