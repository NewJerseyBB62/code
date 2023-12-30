#ifndef _UNS_SERIALIZATION_TOOL_H_
#define _UNS_SERIALIZATION_TOOL_H_

const char* UnsStringDvsType(char dvsType);
const char* UnsStringCmd(unsigned int cmdID);
const char* UnsStringError(int usrError);
const char* UnsStringRoadbaseType(unsigned short roadbaseType);
const char* UnsStringRoadbaseAction(unsigned short roadbaseAction, unsigned short roadbaseType);
const char* UnsStringRoadbaseStatus(unsigned short status, unsigned short roadbaseType);
#endif //_UNS_SERIALIZATION_TOOL_H_
