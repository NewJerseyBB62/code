#include "UuidGenerator.h"

#include <time.h>
#include <stdio.h>
#include <string.h>

UuidGenerator::UuidGenerator()
{
	//std::lock_guard<std::mutex> autolock(m_lockUuid);
#if (defined _WIN32 || defined _WIN64)
	m_str = nullptr;
#endif
}
UuidGenerator::~UuidGenerator()
{
#if (defined _WIN32 || defined _WIN64)
	if(m_str)
	{
		RpcStringFree(&m_str);
	}
#endif
}

string UuidGenerator::GetNewUuid()
{
#if (defined _WIN32 || defined _WIN64)
	RPC_CSTR str = nullptr;
	UUID uuid;
	string strUuid;
	UuidCreate(&uuid);
	UuidToString(&uuid, &str);
	strUuid = (char*)str;
	RpcStringFree(&str);
	return strUuid;
#else
	RPC_CSTR str = nullptr;
	UUID uuid;
	string strUuid;
	uuid_generate(uuid);
	uuid_unparse(uuid, str);
	strUuid = (char*)str;
	return strUuid;
#endif
}

//
bool UuidGenerator::IsValidUuid(const char *str)
{
    bool retval = false;
    if (strlen(str) == 36)
    {
#if (defined _WIN32 || defined _WIN64)
		UUID uuid;
        return UuidFromString((unsigned char*)str, &uuid) == RPC_S_OK;
#else
        uuid_t uuid;
        return uuid_parse((char *)str, uuid) == 0;
#endif
    }
    return retval;
}