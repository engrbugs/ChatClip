#include <Windows.h>
#include <string>
#include <iostream>
#include "Common.h"
#include "Filenames.h"
#include <locale>

#include <iostream>
#include <cstring>
#include <fstream>

using namespace std;


string ExePath() {
    wchar_t buffer[MAX_PATH];
    GetModuleFileName(NULL, buffer, MAX_PATH);
    wstring wbuffer(buffer);
    size_t pos = wbuffer.rfind(L"\\");
    string sbuffer(wbuffer.begin(), wbuffer.end());
    return sbuffer.substr(0, pos);
}



string read_ini_string(const string iniPath, const string sectionName, 
    const string keyName, const string defaultValue) {

    TCHAR* _iniPath = stringToTCHAR(iniPath);
    TCHAR* _sectionName = stringToTCHAR(sectionName);
    TCHAR* _keyName = stringToTCHAR(keyName);
    TCHAR* _defaultValue = stringToTCHAR(defaultValue);

    TCHAR value[256];
    DWORD size = GetPrivateProfileString(_sectionName, _keyName, _defaultValue,
        value, sizeof(value), _iniPath);

    delete[] _iniPath;
    delete[] _sectionName;
    delete[] _keyName;
    delete[] _defaultValue;

    if (size == 0) {
        // Error: failed to read value from INI file
        //std::cerr << "Failed to read value from INI file: " << iniPath << std::endl;
        return "";
    }

    // Convert TCHAR string to std::string 
    std::string stringValue = tcharToString(value);
    stringValue = remove_Comment_Section(stringValue);
    // Use the resulting std::string
    //std::cout << "Value read from INI file: " << stringValue << std::endl;

    return stringValue;
}

string read_Text_file(string path)
{
    string output;
    string line;
    ifstream myfile(path);
    if (myfile.is_open()) {
        while (getline(myfile, line)) {
            output += line;
            if (!myfile.eof()) {
                output += "\n";
            }
            //cout << output << " " << clipBoards_index;
        }
        myfile.close();
    }
    else cout << "Unable to open file";
    return output;
}