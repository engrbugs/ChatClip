#pragma once
#include <string>

using namespace std;

string ExePath();

const string FILES_TO_READ = "\\files.ini";

TCHAR* stringToTCHAR(const string str);

string tcharToString(const TCHAR* tch);

string remove_Comment_Section(const string str);

string Read_ini_string(const string iniPath, const string sectionName, 
	const string keyName, const string defaultValue);