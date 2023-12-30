#include "Hardware.h"

#if (defined _WIN32 || defined _WIN64)
#include <windows.h>
#else
#endif

string Hardware::GetCpuId()
{
	std::string strCPUId;
#if (defined _WIN32 || defined _WIN64)
	INT32 dwBuf[4];
	char buf[32] = { 0 };
	__cpuidex(dwBuf, 1, 1);
	memset(buf, 0, 32);
	sprintf_s(buf, 32, "%08X", dwBuf[3]);
	strCPUId += buf;
	memset(buf, 0, 32);
	sprintf_s(buf, 32, "%08X", dwBuf[0]);
	strCPUId += buf;
#else

#endif // _WIN32 || _WIN64
	return strCPUId;

}
