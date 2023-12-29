#pragma once


#include <mutex>
#include <thread>
#include <chrono>
#include <functional>
#include <vector>
#include "WorkEvent.h"


class CTimer
{
public:
    typedef std::function<void()> fn;
    CTimer();
    ~CTimer();
public:
    void Start(const unsigned long long llGaps, const fn& f);
    void Stop();
private:
    static void Init();
    static void UnInit();
    static void Run();
    static bool GetMinGaps(unsigned long long& llGaps);
private:
    static std::mutex m_mutexTimer;
    static std::thread* m_pThread;
    static std::mutex m_mutexRef;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_lastClock;
    static bool m_bExit;
    static std::vector<CTimer*> m_vecTimer;
    static CWorkEvent* m_event;
    static unsigned long long m_llRef;

private:
    inline void Reset()
    {
        m_lastClock = std::chrono::high_resolution_clock::now();
    }
    inline long long Elapsed_milli() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - m_lastClock).count();
    }
    unsigned long long Check();

private:
    unsigned long long m_llGaps;
    fn m_f;
};

