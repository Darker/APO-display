#include "Game.h"


#include "defines.h"
Game::Game()
    : circle(GAME_WIDTH/2,GAME_HEIGHT/2,10)
    , platform1(150,15)
    , platform2(150,15)
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
    returnArray.push_back(circle.cloneNew());
    returnArray.push_back(platform1.cloneNew());
    returnArray.push_back(platform2.cloneNew());
    return returnArray;
}

void Game::tick()
{
    // Delta time in seconds
    // should be something like 0.05
    double deltaT = sinceLastTick()/1000.0;
    const double rotations_per_second = 0.05;

   //pentac.rotation += rotations_per_second*deltaT*2.0*GAME_PI;


   //movement of circle
    circle.x+=deltaT*1;
    circle.y+=deltaT*1;
}
