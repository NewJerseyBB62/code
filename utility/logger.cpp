#include "logger.h"
#include <stdio.h>
#include <stdarg.h>

void log(const char* p_logFile, const char* p_format, ...)
{
#ifdef _DEBUG
    char szBuff[1024] = { 0 };
    va_list arg;
    va_start(arg, p_format);
    int nLen = vsprintf(szBuff, p_format, arg);
    va_end(arg);

    if (nLen <= 0)
        return;

    if (nullptr == p_logFile)
        return;

    FILE* pf = fopen(p_logFile, "ab+");
    if (nullptr == pf)
        return;

    fwrite(szBuff, 1, nLen, pf);
    fclose(pf);
#endif // DEBUG

}

