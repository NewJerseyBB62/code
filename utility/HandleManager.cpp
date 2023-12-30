#include "HandleManager.h"

HandleManager* HandleManager::m_instance = nullptr;
HandleManager::HandleManager()
    : m_nIdleHandle(0)
{
}

HandleManager::~HandleManager()
{
}

HandleManager* HandleManager::Instance()
{
    if (m_instance == nullptr)
        m_instance = new HandleManager();
    return m_instance;
}

void* HandleManager::GetValue(int handle)
{
    unique_lock<std::recursive_mutex> lock(m_mutex);
    void* pValue = nullptr;
    map<int, void*>::iterator it = m_mapHandle.find(handle);
    if (it != m_mapHandle.end())
    {
        pValue = it->second;
        return pValue;
    }
    return pValue;
}

int HandleManager::GenIdleHandle(void* pValue)
{
    unique_lock<std::recursive_mutex> lock(m_mutex);
    int nHandle = m_nIdleHandle;
    map<int, void*>::iterator it = m_mapHandle.find(m_nIdleHandle);
    while (it != m_mapHandle.end())
    {
        m_nIdleHandle = (m_nIdleHandle + 1) % 0x80000000;
        it = m_mapHandle.find(m_nIdleHandle);
    }
    m_mapHandle[m_nIdleHandle] = pValue;
    nHandle = m_nIdleHandle;
    m_nIdleHandle = (m_nIdleHandle + 1) % 0x80000000;
    return nHandle;
}

void* HandleManager::RemoveValue(int handle)
{
    unique_lock<std::recursive_mutex> lock(m_mutex);
    void* pValue = nullptr;
    map<int, void*>::iterator it = m_mapHandle.find(handle);
    if (it != m_mapHandle.end())
    {
        pValue = it->second;
        m_mapHandle.erase(it);
    }
    return pValue;
}
