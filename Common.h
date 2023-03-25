#include <Windows.h>
#ifndef COMMON_H
#define COMMON_H

extern std::atomic<bool> stop_output_thread;

extern std::string glob;

void Check_clipboard_update();

#endif // COMMON_H