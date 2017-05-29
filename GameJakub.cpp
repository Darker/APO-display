#include "GameJakub.h"
#include <mutex>
#include "defines.h"
#include "ShapeRendering.h"
#include "Rectangle.h"
#include <random>
#include <iostream>
GameJakub::GameJakub()
    : circle(80, GAME_WIDTH/2.0, GAME_HEIGHT/2.0)
    , paintArea(GAME_WIDTH, GAME_HEIGHT, 0, 0)
    , drawX(GAME_WIDTH/2.0)
    , drawY(GAME_HEIGHT/2.0)
    , car(ShapeCar::TRUNK_LENGTH/2.0+1, GAME_HEIGHT/2, Color(0,100,255))
    , mt(rd())
    , shapesPerSec(2.5)
    , speed(1)
    , shapesToGenerate(1)
    , gameOver("GAME OVER", Color::RED, 0, 40, "diablo.ttf")
    , scoreInfo("Travelled: ", Color::YELLOW, 50, 100)
{
    reset();
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

bool GameJakub::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight)
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(!over) {
        car.render(pixmap, pixmapWidth, pixmapHeight);
        for(size_t i=0, l=obstructions.size(); i<l; ++i) {
            obstructions[i].render(pixmap, pixmapWidth, pixmapHeight);
        }
    }
    else {

    }

}

bool GameJakub::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    shapeMutex.lock();
    if(over) {
        int travInt = (int)std::round(travelled);
        scoreInfo.setText(std::string("Travelled: ")+std::to_string(travInt));
        float x0,y0, x1,y1;
        scoreInfo.boundingRect(x0,y0, x1,y1);
        scoreInfo.x = (GAME_WIDTH-x1+x0)/2;

        return !button2.isClicked();
    }

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
    const double movement = deltaT*19*speed;
    travelled += movement;

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
            //std::cout<<"You crashed the car along with your parents, wife and kids. Nobody survived.\n";
            //return false;
            //car.setColor(Color(240, 200, 0));
            over = true;
            obstructions.clear();
            break;
        }
        obstructions[i].x -= movement;
        if((obstructions[i].x+obstructions[i].width) < 0) {
            obstructions.erase(obstructions.begin() + i);
            i--;
            l--;
        }
    }

    shapeMutex.unlock();
    return true;
}

void GameJakub::reset()
{
    car.setCy(GAME_HEIGHT/2);
    speed = 1;
    shapesPerSec = 2.5;
    shapesToGenerate = 1;
    over = false;
    travelled = 0;
    float x0,y0, x1,y1;
    gameOver.boundingRect(x0,y0, x1,y1);
    gameOver.x = (GAME_WIDTH-x1+x0)/2;
}

