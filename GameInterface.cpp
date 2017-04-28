#include "GameInterface.h"

GameInterface::GameInterface() : firstTick(true)
{

}
uint32_t GameInterface::sinceLastTick()
{
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    uint32_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();
    lastTick = now;
    if(firstTick){
        firstTick=false;
        return 0;
    }
    return duration;
}
