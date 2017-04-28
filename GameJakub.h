#ifndef GAMEJAKUB_H
#define GAMEJAKUB_H
#include "GameInterface.h"
#include "GameButton.h"
#include "Pentagram.h"
#include "ShapePixmap.h"
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
    virtual GameButton* getButtonBLUE() override {return &button2;}
    virtual GameButton* getButtonGREEN() override {return &button3;}
protected:
    Pentagram circle;
    ShapePixmap paintArea;
    std::mutex shapeMutex;
    double drawX;
    double drawY;


};

#endif // GAMEJAKUB_H
