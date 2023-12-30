#include "StringHelper.h"

#if (defined _WIN32 || defined _WIN64)
    #include <Windows.h>
#endif


StringHelper::StringHelper()
{
}


StringHelper::~StringHelper()
{
}


std::string StringHelper::UTF8ToGB(const std::string str)
{
    //需要说明的是，IsGB()是通过双字节是否落在gbk的编码范围内实现的，
    //而utf-8编码格式的每个字节都是落在gbk的编码范围内
    //所以只有先调用IsUTF8()先判断不是utf-8编码，再调用IsGB()才有意义
    if (!IsUTF8(str) && IsGB(str))
        return str;

    std::string result;
#if (defined _WIN32 || defined _WIN64)
    WCHAR* strSrc;
    int len = 0;

    WORD type = 0;
    BOOL ok = GetStringTypeA(LOCALE_SYSTEM_DEFAULT, 0, (LPCSTR)str.c_str(), str.length(), &type);
    //获得临时变量的大小
    len = MultiByteToWideChar(CP_UTF8, 0, str.c_str(), -1, nullptr, 0);
    strSrc = new WCHAR[len + 1];
    MultiByteToWideChar(CP_UTF8, CP_ACP, str.c_str(), -1, strSrc, len);

    //获得临时变量的大小
    len = WideCharToMultiByte(CP_ACP, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
    len += 1;
    CHAR* out = new CHAR[len];
    WideCharToMultiByte(CP_ACP, 0, strSrc, -1, out, len, nullptr, nullptr);

    out[len - 1] = '\0';
    result.append(out);

    delete[]strSrc;
    delete[]out;

#endif
    return result;
}

std::string StringHelper::GBToUTF8(const std::string str)
{
    if (IsUTF8(str))
        return str;

    std::string result;
#if (defined _WIN32 || defined _WIN64)
    WCHAR* strSrc;
    int len;

    //获得临时变量的大小
    len = MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, nullptr, 0);
    strSrc = new WCHAR[len + 1];
    MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, strSrc, len);

    //获得临时变量的大小
    len = WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, nullptr, 0, nullptr, nullptr);
    len += 1;
    CHAR* out = new CHAR[len];
    WideCharToMultiByte(CP_UTF8, 0, strSrc, -1, out, len, nullptr, nullptr);

    out[len - 1] = '\0';
    result.append(out);

    delete[]strSrc;
    delete[]out;
#endif
    return result;
}

std::wstring StringHelper::StringToWString(const std::string str)
{
    int nLen = (int)str.length();
    std::wstring wstr;
    wstr.resize(nLen, L' ');

    int nResult = 0;
#if (defined _WIN32 || defined _WIN64)
    nResult = MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)str.c_str(), nLen, (LPWSTR)wstr.c_str(), nLen);
#endif

    if (nResult == 0)
        return wstr;

    return wstr;
}

std::string StringHelper::WStringToString(const std::wstring wstr)
{
    char* out = nullptr;
    int len = 0;
#if (defined _WIN32 || defined _WIN64)
    len = WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, nullptr, 0, nullptr, nullptr);
    len += 1;
    out = new CHAR[len];
    WideCharToMultiByte(CP_UTF8, 0, wstr.c_str(), -1, out, len, nullptr, nullptr);
#endif
    out[len - 1] = '\0';

    std::string str;
    if (len > 0)
        str.append(out);
    delete[] out;
    return str;
}


bool StringHelper::IsUTF8(const std::string str)
{
    char* data = (char*)str.c_str();
    int len = str.length();
    int num = 0;
    int i = 0;
    while (i < len)
    {
        if ((data[i] & 0x80) == 0x00)
        {
            // 0XXX_XXXX
            i++;
            continue;
        }
        else if ((num = PreNum(data[i])) > 2)
        {
            // 110X_XXXX 10XX_XXXX
            // 1110_XXXX 10XX_XXXX 10XX_XXXX
            // 1111_0XXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
            // 1111_10XX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
            // 1111_110X 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX 10XX_XXXX
            // preNUm() 返回首个字节8个bits中首个0bit前面1bit的个数，该数量也是该字符所使用的字节数
            i++;
            for (int j = 0; j < num - 1; j++)
            {
                //判断后面num - 1 个字节是不是都是10开
                if ((data[i] & 0xc0) != 0x80)
                    return false;
                i++;
            }
        }
        else
        {
            //其他情况说明不是utf-8
            return false;
        }
    }
    return true;
}

bool StringHelper::IsGB(const std::string str)
{
    char* data = (char*)str.c_str();
    int len = str.length();
    int i = 0;
    while (i < len)
    {
        if (data[i] <= 0x7f)
        {
            //编码小于等于127,只有一个字节的编码，兼容ASCII
            i++;
            continue;
        }
        else
        {
            //大于127的使用双字节编码
            if (data[i] >= 0x81 &&
                    data[i] <= 0xfe &&
                    data[i + 1] >= 0x40 &&
                    data[i + 1] <= 0xfe &&
                    data[i + 1] != 0xf7)
            {
                i += 2;
                continue;
            }
            else
                return false;
        }
    }
    return true;
}

int StringHelper::PreNum(unsigned char byte)
{
    unsigned char mask = 0x80;
    int num = 0;
    for (int i = 0; i < 8; i++)
    {
        if ((byte & mask) == mask)
        {
            mask = mask >> 1;
            num++;
        }
        else
            break;
    }
    return num;
}
