#include "Timer.h"
#include <algorithm>


std::vector<CTimer*> CTimer::m_vecTimer;
bool CTimer::m_bExit = false;
CWorkEvent* CTimer::m_event = nullptr;
unsigned long long CTimer::m_llRef = 0;

std::mutex CTimer::m_mutexTimer;
std::thread* CTimer::m_pThread = nullptr;
std::mutex CTimer::m_mutexRef;

CTimer::CTimer()
    : m_lastClock(std::chrono::high_resolution_clock::now())
    , m_llGaps(1)
    , m_f(nullptr)
{
    CTimer::Init();
}

void CTimer::Init()
{
    std::unique_lock<std::mutex> lock(m_mutexRef);
    m_llRef++;
    if (1 == m_llRef)
    {
        m_bExit = false;
        m_event = new CWorkEvent();
        m_pThread = new std::thread(CTimer::Run);
    }
}


CTimer::~CTimer()
{
    CTimer::UnInit();
}



void CTimer::UnInit()
{
    std::unique_lock<std::mutex> lock(m_mutexRef);
    m_llRef--;
    if (0 == m_llRef)
    {
        m_bExit = true;
        m_event->SetEvent();
        if (m_pThread)
        {
            m_pThread->join();
            delete m_pThread;
            m_pThread = nullptr;
        }
        delete m_event;
    }
}

void CTimer::Run()
{
    while (!m_bExit)
    {
        unsigned long long llMinDelay = 0;
        if (GetMinGaps(llMinDelay))
            m_event->WaitEvent(llMinDelay);
        else
            m_event->WaitEvent();
    }
}

bool CTimer::GetMinGaps(unsigned long long& llGaps)
{
    std::unique_lock<std::mutex> lock(m_mutexTimer);
    if (m_vecTimer.size() > 0)
    {
        llGaps = m_vecTimer[0]->Check();
        for (int i = 1; i < (int)m_vecTimer.size(); i++)
        {
            unsigned long long llTmp = m_vecTimer[i]->Check();
            if (llTmp < llGaps)
                llGaps = llTmp;
        }
        return true;
    }
    return false;
}

void CTimer::Start(const unsigned long long llGaps, const fn& f)
{
    m_llGaps = llGaps;
    m_f = f;
    Reset();
    {
        std::unique_lock<std::mutex> lock(m_mutexTimer);
        m_vecTimer.push_back(this);
    }
    m_event->SetEvent();
}

void CTimer::Stop()
{
    {
        //try to lock 用于在timeout中stop timer
        std::unique_lock<std::mutex> lock(m_mutexTimer);
        auto it = std::remove_if(m_vecTimer.begin(), m_vecTimer.end(), [&](CTimer * pTimer)
        {
            return pTimer == this;
        });
        m_vecTimer.erase(it, m_vecTimer.end());
    }
}

unsigned long long CTimer::Check()
{
    long long llElapsed = Elapsed_milli();
    if (llElapsed < 0)//修改电脑时间导致为负值
    {
        Reset();
        return m_llGaps;
    }

    if (llElapsed >= (long long)m_llGaps)
    {
        Reset();
        if (m_f)
            m_f();
        return m_llGaps;
    }
    else
        return (m_llGaps - llElapsed);
}

