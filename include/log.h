#ifndef KEYBOARD_LOG
#define KEYBOARD_LOG

#include "global.h"

bool LoadLog();
void SaveLog();
void SortByCount(std::ofstream &logFile);

#endif