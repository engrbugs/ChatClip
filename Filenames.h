#pragma once
#include <string>

using namespace std;
string ExePath();

string FILES_TO_READ = ExePath() + "\\files.ini";

string Read_ini_string(const string iniPath, const string sectionName, const string keyName, const string defaultValue);