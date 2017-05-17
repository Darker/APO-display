#ifndef GAMEJAKUB_H
#define GAMEJAKUB_H
#include "GameInterface.h"
#include "GameButton.h"
#include "Pentagram.h"
#include "ShapePixmap.h"
#include "ShapeCar.h"
#include "threading.h"
#include <random>
class GameJakub : public GameInterface
{
public:
    GameJakub();
    // This is not htread safe!
    // must lock internal shape array before copyinf
    virtual std::vector<Shape*> getShapes();
    // one game tick
    virtual bool tick();
    GameButton button1;
    GameButton button2;
    GameButton button3;

    virtual GameButton* getButtonRED() override {return &button1;}
    virtual GameButton* getButtonBLUE() override {return &button3;}
    virtual GameButton* getButtonGREEN() override {return &button2;}
protected:
    Pentagram circle;
    ShapePixmap paintArea;
    ShapeCar car;
    std::vector<Rectangle> obstructions;

    Rectangle testRect;
    std::mutex shapeMutex;
    double drawX;
    double drawY;

    std::random_device rd;
    std::mt19937 mt;

    // variables related to the car game
    // how many shapes/s appear
    double shapesPerSec;
    // Game speed multiplier
    double speed;

    // How many shapes need to be generated
    // this increments with delta time
    // times shapes per second and
    // when reaches value over 1, the
    // ammount of shapes is generated
    double shapesToGenerate;

};

#endif // GAMEJAKUB_H
