#pragma once

#include <mutex>
#include <condition_variable>


class CWorkEvent
{
public:
    CWorkEvent();
    ~CWorkEvent();
public:
    void SetEvent();
    void WaitEvent();
    void WaitEvent(const unsigned long long llTime);//ms
    void ResetEvent();
private:
    std::condition_variable m_conditionWake;
    std::mutex m_mutexWake;
    bool m_bWake;
};
