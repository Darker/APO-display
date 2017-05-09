#include "GameJakub.h"
#include <mutex>
#include "defines.h"
#include "ShapeRendering.h"
#include "Rectangle.h"
GameJakub::GameJakub()
    : circle(80, GAME_WIDTH/2.0, GAME_HEIGHT/2.0)
    , paintArea(GAME_WIDTH, GAME_HEIGHT, 0, 0)
    , drawX(GAME_WIDTH/2.0)
    , drawY(GAME_HEIGHT/2.0)
{

}

std::vector<Shape*> GameJakub::getShapes()
{
    std::vector<Shape*> result;
    shapeMutex.lock();
    result.push_back(paintArea.cloneNew());
    result.push_back(circle.cloneNew());
    //result.push_back(new Rectangle(0,0,GAME_WIDTH, 40));
    shapeMutex.unlock();
    return result;
}

void GameJakub::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    /*circle.x += button1.moveDelta();
    circle.y += button3.moveDelta();
    circle.rotation += (button2.moveDelta()*GAME_PI*2)/256.0;
    if(circle.r<5)
        circle.r = 5;*/
    circle.rotation += (button2.moveDelta()*GAME_PI*2.0)/100.0;;
    circle.rotation += (deltaT)*GAME_PI/20.0;

    double newDrawX = drawX + button1.moveDelta()/2.0;
    double newDrawY = drawY + button3.moveDelta()/2.0;
    if(newDrawX!=drawX || newDrawY!=drawY) {
        line(paintArea.drawArea, Color::YELLOW, drawX, drawY, newDrawX, newDrawY, paintArea.width);
        drawX = newDrawX;
        drawY = newDrawY;
    }
}
