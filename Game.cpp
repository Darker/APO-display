#include "Game.h"

#include "defines.h"
Game::Game()
    : pentac(100, GAME_WIDTH/2, GAME_HEIGHT/2)
{

}

void Game::movePlayer(int playerID, int offset)
{

}

std::vector<Shape*> Game::getShapes()
{
    std::vector<Shape*> returnArray;
    // LOCK MUTEX!
    // copy every shape into new array and return that array
    returnArray.push_back(pentac.cloneNew());
    return returnArray;
}

void Game::tick()
{
    // Delta time in seconds
    // should be something like 0.05
    double deltaT = sinceLastTick()/1000.0;
    const double rotations_per_second = 0.05;
    pentac.rotation += rotations_per_second*deltaT*2.0*GAME_PI;
}

uint32_t Game::sinceLastTick()
{
    const std::chrono::steady_clock::time_point now = std::chrono::steady_clock::now();
    uint32_t duration = std::chrono::duration_cast<std::chrono::milliseconds>(now - lastTick).count();
    lastTick = now;
    return duration;
}
