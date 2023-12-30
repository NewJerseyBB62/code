#ifndef _SRODMEMPOOL_H_
#define _SRODMEMPOOL_H_

#include <vector>
#include <memory>
#include <mutex>
#include <queue>

using Mem_Ptr = std::shared_ptr<char>;
using Mem_Ptr_vec = std::vector<Mem_Ptr>;

class SrodMemPool
{
public:
    SrodMemPool();
    ~SrodMemPool();

    void init(unsigned int p_nSlipSize, unsigned int p_nSlipNum, bool p_autoIncrement = true);
    unsigned int getSlipSize();
    Mem_Ptr get();

private:
    void add();
    void poolDeletor(char* t);
private:
    unsigned int       m_nSlipSize;
    unsigned int       m_nSlipNum;
    bool               m_autoIncrement;
    std::mutex         m_mutex;
    Mem_Ptr_vec        m_buffVec;
    Mem_Ptr_vec        m_pool;
    bool               m_free;
};
typedef std::shared_ptr<SrodMemPool> PMemPool;

class SrodMemQueue
{
public:
    SrodMemQueue()
    {
    }
    void put(const Mem_Ptr& p_mem)
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue.push(p_mem);
    }
    Mem_Ptr get()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        if (m_queue.empty())
            return nullptr;
        Mem_Ptr ptr = m_queue.front();
        m_queue.pop();
        return ptr;
    }
    void clear()
    {
        std::lock_guard<std::mutex> locker(m_mutex);
        m_queue = std::queue<Mem_Ptr>();
    }
private:
    std::mutex          m_mutex;                    // 互斥量和条件变量结合起来使用
    std::queue<Mem_Ptr> m_queue;                    // 缓冲区
};

#endif //_SRODMEMPOOL_H_