#ifndef GAMEINTERSECTIONTEST_H
#define GAMEINTERSECTIONTEST_H
#include "ShapeRectangleBorder.h"
#include "GameInterface.h"
#include <mutex>
class GameIntersectionTest : public GameInterface
{
public:
    GameIntersectionTest();
protected:
    ShapeRectangleBorder a;
    ShapeRectangleBorder b;
    ShapeRectangleBorder* activeRect;
    std::mutex shapeMutex;

    // GameInterface interface
public:
    virtual std::vector<Shape*> getShapes() override;
    virtual bool tick() override;

    GameButton button1;
    GameButton button2;
    GameButton button3;

    double switchCooldown;

    virtual GameButton* getButtonRED() override {return &button1;}
    virtual GameButton* getButtonBLUE() override {return &button3;}
    virtual GameButton* getButtonGREEN() override {return &button2;}

};

#endif // GAMEINTERSECTIONTEST_H
