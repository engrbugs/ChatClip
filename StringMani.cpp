#include <Windows.h>
#include <string>
#include <iostream>
#include <locale>

#include "Common.h"
#include "Filenames.h"


using namespace std;

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


string tcharToString(const TCHAR* tch)
{
    char charValue[256];
    wcstombs_s(nullptr, charValue, tch, _TRUNCATE);
    return std::string(charValue);
}



string trim_Both_Ends(const string str)
{
    std::string output = str;
    size_t first = output.find_first_not_of(' ');
    size_t last = output.find_last_not_of(' ');
    if (first != std::string::npos && last != std::string::npos) {
        output = output.substr(first, last - first + 1);
    }
    else {
        output.clear();
    }
    return output;
}


string remove_Comment_Section(const string str)
{
    size_t pos = str.find("//");
    if (pos != string::npos) {
        return trim_Both_Ends(str.substr(0, pos));
    }
    else {
        return trim_Both_Ends(str);
    }
}