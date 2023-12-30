#pragma once

#include <map>
#include <mutex>

using namespace std;

class HandleManager
{
private:
    HandleManager();
    ~HandleManager();
public:
    static HandleManager* Instance();
    void* GetValue(int handle);
    int GenIdleHandle(void* pValue);
    void* RemoveValue(int handle);
private:
    map<int, void*>       m_mapHandle;
    static HandleManager* m_instance;
    int                   m_nIdleHandle;
    recursive_mutex       m_mutex;
};

