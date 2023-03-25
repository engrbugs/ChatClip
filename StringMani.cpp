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