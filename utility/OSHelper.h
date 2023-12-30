#pragma once

#include <string>
#include <vector>

using namespace std;

class OSHelper
{
public:
    static string GetSysDir();
	static bool IsFileExists(string file);
	static bool IsDirExists(string dir);
	static bool CreateDir(string dir);
	static bool FindAllSubDir(string dir, vector<string>& subDirs);
	static bool RemoveFile(string file);
};

