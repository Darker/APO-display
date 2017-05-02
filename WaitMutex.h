#ifndef WAITMUTEX_H
#define WAITMUTEX_H
#include "threading.h"
#include <condition_variable>

class WaitMutex
{
public:
    WaitMutex();
    // block until thread is unlocked
    void wait();
    // unlocks thread if it's waiting
    void unlock();
protected:
    std::mutex m;
    std::condition_variable condition;
    bool shouldUnlock;
};

#endif // WAITMUTEX_H
