#ifndef GAME_H
#define GAME_H
class Shape;
class Pentagram;
#include <vector>
#include <chrono>
#include <stdint.h>

#include "Pentagram.h"

class Game
{
public:
    Game();
    // Moves platform of player X
    void movePlayer(int playerID, int offset);
    // This is not htread safe!
    // must lock internal shape array before copyinf
    std::vector<Shape*> getShapes();
    // one game tick
    void tick();
protected:
    // Mutex for copying shapes
        // TODO later

    // This measures time per tick
    // Important to ensure game speed doesn't change
    // when CPU slows down or speeds up
    uint32_t sinceLastTick();
    std::chrono::steady_clock::time_point lastTick;
    bool firstTick;

    // Some testing garbage
    Pentagram pentac;
};

#endif // GAME_H
