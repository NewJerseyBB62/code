// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "dllmain.h"
#include "dump.h"



DUMPAPI int CreateDump() 
{
	dump* dumpObj = new dump;
	return 0;
}
