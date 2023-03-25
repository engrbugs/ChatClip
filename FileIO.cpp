#include <Windows.h>
#include <string>
#include <iostream>
#include "Common.h"
#include <locale>

#include <iostream>
#include <cstring>


using namespace std;


string ExePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    wstring wbuffer(buffer);
    size_t pos = wbuffer.rfind(L"\\");
    string sbuffer(wbuffer.begin(), wbuffer.end());
    return sbuffer.substr(0, pos);
}



string Read_ini_string(const string iniPath, const string sectionName, const string keyName, const string defaultValue) {
    char* myCharPtr = new char[iniPath.length() + 1];
    strcpy_s(myCharPtr, iniPath.length() + 1, iniPath.c_str());

    std::cout << myCharPtr << std::endl;

    

    size_t newsize = strlen(myCharPtr) + 1;
    //delete[] myCharPtr;

    wchar_t* wcstring = new wchar_t[newsize];

    // Convert char* string to a wchar_t* string.
    size_t convertedChars = 0;
    mbstowcs_s(&convertedChars, wcstring, newsize, myCharPtr, _TRUNCATE);
    // Display the result and indicate the type of string that it is.
    wcout << wcstring << L" (wchar_t *)" << endl;
    //delete[]wcstring;

    //TCHAR _iniPath[MAX_PATH] = wcstring;
    TCHAR _sectionName[] = TEXT("Files");
    TCHAR _keyName[] = TEXT("a");
    TCHAR _defaultValue[] = TEXT("nnn");

    TCHAR value[256];
    DWORD size = GetPrivateProfileString(_sectionName, _keyName, _defaultValue, value, sizeof(value), wcstring);

    if (size == 0) {
        // Error: failed to read value from INI file
        std::cerr << "Failed to INI file:" << "_iniPath" << std::endl;
        //return 1;
    }
    // Convert TCHAR string to char array
    char charValue[256];
    wcstombs_s(nullptr, charValue, value, _TRUNCATE);

    // Construct std::string from char array
    std::string stringValue(charValue);

    // Use the resulting std::string
    std::cout << "Value read from INI file: " << stringValue << std::endl;

    return "";
}
