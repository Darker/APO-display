#include "Game.h"
#include <random>

#include "defines.h"
Game::Game()
    : circle()
    , platform1(5,GAME_HEIGHT/2,GAME_WIDTH/25,GAME_HEIGHT/4)
    , platform2(GAME_WIDTH-5,GAME_HEIGHT/2,GAME_WIDTH/25,GAME_HEIGHT/4)
    , mt(rd())
{
    std::uniform_real_distribution<double> position(0.0, GAME_HEIGHT);
    std::uniform_real_distribution<double> speed(0.0, 40);

    platform1 = Platform(5, (double) position(mt), GAME_WIDTH/25,GAME_HEIGHT/4);
    platform2 = Platform(GAME_WIDTH-6, (double) position(mt),GAME_WIDTH/25,GAME_HEIGHT/4);

    circle = Circle((double)(GAME_WIDTH/2), (double)(GAME_HEIGHT/2), (double)(speed(mt)), (double)(speed(mt)), (int)10);
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

    double deltaT = sinceLastTick()/1000.0;
    const double rotations_per_second = 0.05;



    circle.move(deltaT);

    if(platform1.intersects(circle)){
        circle.bounce_platform();
        circle.vx++;
        circle.vy++;

    }

    if(platform2.intersects(circle)){
        circle.bounce_platform();
        circle.vx++;
        circle.vy++;
    }



}
