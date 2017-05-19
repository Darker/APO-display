#ifndef FUTURE_H
#define FUTURE_H
#include <thread>
#include "WaitMutex.h"
#include <functional>
template <typename T>
class Future
{
public:
    Future(const std::function< T() >& lambda)
        : done(false)
        , thread(lambda)
    {

    }

    // returns value if finished, otherwise blocks
    T get() {
        std::unique_lock<std::mutex> lk{doneMutex};
        if(done) {
            return result;
        }
        else {
            lk.release();
            waitForResult.wait();
            return result;
        }
    }
    // returns true if done already
    bool isDone()
    {
        std::unique_lock<std::mutex> lk{doneMutex};
        return done;
    }

protected:
    std::thread thread;
    WaitMutex waitForResult;
    std::mutex doneMutex;
    void calculateResult(const std::function< T() >& lambda) {
        result = lambda();
        std::unique_lock<std::mutex> lk{doneMutex};
        done = true;
    }

    T result;
    bool done;
};

#endif // FUTURE_H
