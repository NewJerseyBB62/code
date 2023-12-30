#pragma once
#include <string>
#include <mutex>
#if (defined _WIN32 || defined _WIN64)
#include <Rpc.h>
#else
#define UUID_UNPARSED_SIZE 37
typedef unsigned char uuid_t[16];
//libuuid (e2fsprogs) with extern "C" linkage
extern "C" {
	void uuid_generate(uuid_t out);
	void uuid_unparse(const uuid_t uu, char *out);
	int uuid_parse(char *in, uuid_t uu);
}
#endif

using namespace std;

class UuidGenerator
{
public:
	UuidGenerator();
	~UuidGenerator();

	static bool IsValidUuid(const char* string);
	static string GetNewUuid();

protected:
#if (defined _WIN32 || defined _WIN64)
	UUID m_uuid;
	RPC_CSTR m_str;
#else
	uuid_t m_uuid;
	char m_str[UUID_UNPARSED_SIZE];
#endif
};

