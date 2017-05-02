#include "WaitMutex.h"

WaitMutex::WaitMutex() : shouldUnlock(false)
{

}

void WaitMutex::wait()
{
    while(true) {
        std::unique_lock<std::mutex> lk{m};
        condition.wait(lk); // Will block until 'cond' is notified.
        if(shouldUnlock) {
            shouldUnlock = false;
            break;
        }
    }
}

void WaitMutex::unlock()
{
    {
        std::lock_guard<std::mutex> lk{m};
        shouldUnlock = true;
    }
    condition.notify_all();
}
