#pragma once

#include <string>

class StringHelper
{
public:
	StringHelper();
	~StringHelper();
	static std::wstring StringToWString(const std::string str);
	static std::string WStringToString(const std::wstring wstr);
	static std::string UTF8ToGB(const std::string str);
	static std::string GBToUTF8(const std::string str);
	static bool IsUTF8(const std::string str);
	static bool IsGB(const std::string str);
private:
	static int PreNum(unsigned char byte);
};
