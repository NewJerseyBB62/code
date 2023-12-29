#include "WorkEvent.h"



CWorkEvent::CWorkEvent()
    : m_bWake(false)
{
}

CWorkEvent::~CWorkEvent()
{
}

void CWorkEvent::SetEvent()
{
    std::unique_lock<std::mutex> lock(m_mutexWake);
    if (!m_bWake)
    {
        m_bWake = true;
        m_conditionWake.notify_one();
    }
}

void CWorkEvent::WaitEvent()
{
    std::unique_lock<std::mutex> lock(m_mutexWake);
    m_conditionWake.wait(lock, [&]()
    {
        return m_bWake;
    });
    m_bWake = false;
}

void CWorkEvent::WaitEvent(const unsigned long long llTime)
{
    std::unique_lock<std::mutex> lock(m_mutexWake);
    if (m_conditionWake.wait_for(lock, std::chrono::milliseconds(llTime), [&]()
{
    return m_bWake;
}))
    {
        m_bWake = false;
    }
}

void CWorkEvent::ResetEvent()
{
    m_bWake = false;
}
