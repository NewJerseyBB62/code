#include "SrodMemPool.h"
#include <algorithm>

SrodMemPool::SrodMemPool()
    : m_nSlipSize(0)
    , m_nSlipNum(0)
    , m_autoIncrement(true)
    , m_free(false)
{
}
SrodMemPool::~SrodMemPool()
{
    m_free = true;
}

void SrodMemPool::init(unsigned int p_nSlipSize, unsigned int p_nSlipNum, bool p_autoIncrement)
{
    m_nSlipSize = p_nSlipSize;
    m_nSlipNum = p_nSlipNum;
    m_autoIncrement = p_autoIncrement;

    std::lock_guard<std::mutex> objLock(m_mutex);
    add();
}

unsigned int SrodMemPool::getSlipSize()
{
    return m_nSlipSize;
}

Mem_Ptr SrodMemPool::get()
{
    std::lock_guard<std::mutex> objLock(m_mutex);
    if (m_pool.empty())
    {
        if (!m_autoIncrement)
            return nullptr;
        add();
    }
    Mem_Ptr ptr(m_pool.back());
    m_pool.pop_back();
    return ptr;
}

void SrodMemPool::add()
{
    Mem_Ptr memBuff(new char[m_nSlipSize * m_nSlipNum], std::default_delete<char[]>());
    char* buff = memBuff.get();
    for (int i = 0; i < m_nSlipNum; ++i)
    {
        Mem_Ptr ptr(buff + i * m_nSlipSize, std::bind(&SrodMemPool::poolDeletor, this, std::placeholders::_1));
        m_pool.push_back(ptr);
    }

    m_buffVec.push_back(std::move(memBuff));
}

void SrodMemPool::poolDeletor(char* t)
{
    if (m_free)
        return;

    Mem_Ptr ptr(t, std::bind(&SrodMemPool::poolDeletor, this, std::placeholders::_1));
    std::lock_guard<std::mutex> objLock(m_mutex);
    m_pool.push_back(ptr);
}

