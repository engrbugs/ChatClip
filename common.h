#include <Windows.h>
#include <vector>
#ifndef COMMON_H
#define COMMON_H

extern std::atomic<bool> stop_output_thread;
using namespace std;

extern string glob;
extern vector<string> clipBoards;

void Check_clipboard_update();



#endif // COMMON_H