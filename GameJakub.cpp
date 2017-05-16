#include "GameJakub.h"
#include <mutex>
#include "defines.h"
#include "ShapeRendering.h"
#include "Rectangle.h"
#include <iostream>
GameJakub::GameJakub()
    : circle(80, GAME_WIDTH/2.0, GAME_HEIGHT/2.0)
    , paintArea(GAME_WIDTH, GAME_HEIGHT, 0, 0)
    , drawX(GAME_WIDTH/2.0)
    , drawY(GAME_HEIGHT/2.0)
    , car(ShapeCar::TRUNK_LENGTH/2.0+1, GAME_HEIGHT/2, Color(0,100,255))
    , mt(rd())
    , testRect(GAME_WIDTH-20,GAME_HEIGHT-20,20, 20)
    , shapesPerSec(2.5)
    , speed(1)
    , shapesToGenerate(1)
{

}

std::vector<Shape*> GameJakub::getShapes()
{
    std::vector<Shape*> result;
    shapeMutex.lock();
    //result.push_back(paintArea.cloneNew());
    //result.push_back(circle.cloneNew());
    //result.push_back(new Rectangle(0,0,GAME_WIDTH, 40));
    result.push_back(car.cloneNew());
    for(size_t i=0, l=obstructions.size(); i<l; ++i) {
        //result.push_back(new Rectangle(obstructions[i].x, obstructions[i].y, obstructions[i].width, obstructions[i].height, Color(255,255,11)));
        result.push_back(obstructions[i].cloneNew());
    }
//    for(size_t i=0, l=255; i<l; ++i) {
//        result.push_back(new Rectangle(i,i,2,2,Color(i,i,i)));
//    }
    //result.push_back(testRect.cloneNew());
    shapeMutex.unlock();
    return result;
}

void GameJakub::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    shapeMutex.lock();
    //testRect.x += deltaT*5;
    //testRect.y += deltaT*5;
    /*circle.x += button1.moveDelta();
    circle.y += button3.moveDelta();
    circle.rotation += (button2.moveDelta()*GAME_PI*2)/256.0;
    if(circle.r<5)
        circle.r = 5;*/
//    circle.rotation += (button2.moveDelta()*GAME_PI*2.0)/100.0;;
//    circle.rotation += (deltaT)*GAME_PI/20.0;

//    double newDrawX = drawX + button1.moveDelta()/2.0;
//    double newDrawY = drawY + button3.moveDelta()/2.0;
//    if(newDrawX!=drawX || newDrawY!=drawY) {
//        line(paintArea.drawArea, Color::YELLOW, drawX, drawY, newDrawX, newDrawY, paintArea.width);
//        drawX = newDrawX;
//        drawY = newDrawY;
//    }
    double cary = car.getCy() + button2.moveDelta();
    static const double carBorder = ShapeCar::TRUNK_WIDTH+ShapeCar::WHEEL_WIDTH;

    if(cary < carBorder)
        cary = carBorder;
    else if(cary > GAME_HEIGHT-carBorder)
        cary = GAME_HEIGHT-carBorder;
    car.setCy(cary);

    shapesPerSec += deltaT/200.0;
    speed += deltaT/20.0;
    shapesToGenerate += shapesPerSec*deltaT;

    while(shapesToGenerate>=1) {
        std::uniform_real_distribution<double> position(0.0, GAME_HEIGHT);
        std::uniform_real_distribution<double> dimensions(5.0, 20.0);

        Rectangle r(GAME_WIDTH+1, position(mt), dimensions(mt), dimensions(mt));
        r.color = Color(255,0,0);
        obstructions.push_back(r);

        shapesToGenerate--;
    }
    car.setColor(Color(0,100,255));
    for(size_t i=0, l=obstructions.size(); i<l; ++i) {
        if(car.intersects(obstructions[i])) {
            std::cout<<"You crashed the car along with your parents, wife and kids. Nobody survived.\n";
            exit(1);
            //car.setColor(Color(240, 200, 0));
        }
        obstructions[i].x -= deltaT*19*speed;
        if((obstructions[i].x+obstructions[i].width) < 0) {
            obstructions.erase(obstructions.begin() + i);
            i--;
            l--;
        }
    }

    shapeMutex.unlock();
}
