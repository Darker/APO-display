#ifndef GAMEJAKUB_H
#define GAMEJAKUB_H
#include "GameInterface.h"
#include "GameButton.h"
#include "Pentagram.h"
#include "ShapePixmap.h"
#include "ShapeCar.h"
#include "threading.h"
#include "ShapeText.h"
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

    virtual void reset();

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

    // variables related to the car game
    // how many shapes/s appear
    double shapesPerSec;
    // Game speed multiplier
    double speed;
    // true if game has ended
    // if true, any button press causes game to quit
    bool over;
    // distance travelled
    double travelled;
    // game over texts
    ShapeText gameOver;
    ShapeText scoreInfo;

    // How many shapes need to be generated
    // this increments with delta time
    // times shapes per second and
    // when reaches value over 1, the
    // ammount of shapes is generated
    double shapesToGenerate;


    // GameInterface interface
public:
    virtual bool render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight) override;
};

#endif // GAMEJAKUB_H
