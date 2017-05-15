#include "Game.h"


#include "defines.h"
Game::Game()
    : circle(GAME_WIDTH/2,GAME_HEIGHT/2,15,5,10)
    , platform1(150,15,GAME_WIDTH-10,80)
    , platform2(150,15,0,40)
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



    //just trying to make it bounce, dj hit the decks
    //if I change if into while whole thing crashes

    circle.move(deltaT);

    if(platform1.intersects_ball(circle)){
        circle.bounce_platform();
    }

    if(platform2.intersects_ball(circle)){
        circle.bounce_platform();
    }



}
