#pragma once
#include <string>

using namespace std;

string ExePath();

const string FILES_TO_READ = "\\files.ini";


string Read_ini_string(const string iniPath, const string sectionName, 
	const string keyName, const string defaultValue);
