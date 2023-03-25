#include <Windows.h>
#include <string>
#include <iostream>
#include "Common.h"
#include "Filenames.h"
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


// Function that converts a string to a TCHAR*
TCHAR* stringToTCHAR(const string str) {

    // Calculate the required size of the buffer
    size_t size = str.size() + 1;

    // Allocate memory for the TCHAR* buffer
    TCHAR* buffer = new TCHAR[size];

    // Convert the input string to a TCHAR* string
    // Using the mbstowcs_s function to handle multibyte strings
    // nullptr is passed as the first argument to mbstowcs_s to indicate that we don't need to know how many characters were actually converted
    // The buffer is passed as the second argument to store the converted string
    // The size is passed as both the third and fourth arguments to indicate the size of both the input string and the output buffer
    // str.c_str() is passed as the final argument to provide the input string
    mbstowcs_s(nullptr, buffer, size, str.c_str(), size);

    // Return the converted TCHAR* string
    return buffer;
}



string Read_ini_string(const string iniPath, const string sectionName, 
    const string keyName, const string defaultValue) {

    TCHAR* _iniPath = stringToTCHAR(iniPath);
    TCHAR* _sectionName = stringToTCHAR(sectionName);
    TCHAR* _keyName = stringToTCHAR(keyName);
    TCHAR* _defaultValue = stringToTCHAR(defaultValue);

    TCHAR value[256];
    DWORD size = GetPrivateProfileString(_sectionName, _keyName, _defaultValue, 
        value, sizeof(value), _iniPath);
    /*delete[] _iniPath;
    delete[] _sectionName;
    delete[] _keyName;
    delete[] _defaultValue;*/

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
