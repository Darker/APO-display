#ifndef GAMEJAKUB_H
#define GAMEJAKUB_H
#include "GameInterface.h"
#include "GameButton.h"
#include "Pentagram.h"
#include "ShapePixmap.h"
#include "ShapeCar.h"
#include "threading.h"
class GameJakub : public GameInterface
{
public:
    GameJakub();
    // This is not htread safe!
    // must lock internal shape array before copyinf
    virtual std::vector<Shape*> getShapes();
    // one game tick
    virtual void tick();
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
    std::mutex shapeMutex;
    double drawX;
    double drawY;

    std::random_device rd;
    std::mt19937 mt;
};

#endif // GAMEJAKUB_H
