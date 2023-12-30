#include "JsonFile.h"
#include <fstream>
#include "../utility/OSHelper.h"
#include "UsrPbJson.h"

using namespace std;


bool JsonFile::Read(string strFile, string& strJson)
{
    ifstream fs(strFile, ios::binary | ios::in | ios::ate);
    if (!fs.is_open())
        return false;
    std::streampos fsize = 0;
    fsize = fs.tellg();
    strJson.resize((int)fsize);
    fs.seekg(0);
    fs.read((char*)strJson.c_str(), fsize);
    fs.close();

    return true;
}

bool JsonFile::Write(string strFile, string& strJson)
{
    int pos = strFile.rfind('\\');
    string dir = strFile.substr(0, pos + 1);
    if (!dir.empty())
        OSHelper::CreateDir(dir);
    ofstream fs(strFile, ios::trunc | ios::out);
    if (!fs.is_open())
        return false;
    fs.write(strJson.c_str(), strJson.length());
    fs.close();

    return true;
}

bool JsonFile::Read(string strFile, google::protobuf::Message* msg)
{
    string strJson;
    bool ok = Read(strFile, strJson);
    if (!ok)
        return false;

    return usr::jsonToPb(strJson, *msg);
}

bool JsonFile::Write(string strFile, google::protobuf::Message* msg)
{
    string strJson;
    usr::pbToJson(*msg, strJson);
    bool ok = Write(strFile, strJson);
    return ok;
}
