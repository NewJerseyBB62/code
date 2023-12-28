#pragma once

#include <Windows.h>
#include <Dbghelp.h>

class dump {
public:
    explicit dump();
    ~dump();
private:
    static LONG WINAPI UnhandledExceptionFilter(struct _EXCEPTION_POINTERS* pExceptionInfo);
private:
    LPTOP_LEVEL_EXCEPTION_FILTER        m_oldExceptionFilter;
};