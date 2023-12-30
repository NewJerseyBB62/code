#pragma once
#include <string>
#include "SrodDeviceDefine.pb.h"

using namespace std;

class JsonFile
{
public:
    static bool Read(string strFile, string& strJson);
    static bool Write(string strFile, string& strJson);
    static bool Read(string strFile, google::protobuf::Message* msg);
    static bool Write(string strFile, google::protobuf::Message* msg);
};

