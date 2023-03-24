#include <Windows.h>
#include <string>
#include <iostream>
#include "Common.h"

using namespace std;

string ExePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    wstring wbuffer(buffer);
    size_t pos = wbuffer.rfind(L"\\");
    string sbuffer(wbuffer.begin(), wbuffer.end());
    return sbuffer.substr(0, pos);
}

int Read_ini_string() {
    TCHAR iniPath[MAX_PATH] = TEXT("C:\\BUGS\\Github\\ChatClip\\x64\\Debug\\files.ini");
    TCHAR sectionName[] = TEXT("Files");
    TCHAR keyName[] = TEXT("a");
    TCHAR defaultValue[] = TEXT("nnn");

    TCHAR value[256];
    DWORD size = GetPrivateProfileString(sectionName, keyName, defaultValue, value, sizeof(value), iniPath);

    if (size == 0) {
        // Error: failed to read value from INI file
        std::cerr << "Failed to read value from INI file" << value << std::endl;
        //return 1;
    }
    // Convert TCHAR string to char array
    char charValue[256];
    wcstombs_s(nullptr, charValue, value, _TRUNCATE);

    // Construct std::string from char array
    std::string stringValue(charValue);

    // Use the resulting std::string
    std::cout << "Value read from INI file: " << stringValue << std::endl;

    return 0;
}
