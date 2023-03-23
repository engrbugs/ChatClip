#include <Windows.h>
#include <string>
#include <iostream>


using namespace std;

string ExePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    wstring wbuffer(buffer);
    size_t pos = wbuffer.rfind(L"\\");
    string sbuffer(wbuffer.begin(), wbuffer.end());
    return sbuffer.substr(0, pos);
}
