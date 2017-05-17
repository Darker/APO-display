#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H
#include <chrono>
#include <stdint.h>
#include <vector>
#include "Shape.h"
#include "GameButton.h"
class GameInterface
{
public:
    GameInterface();

    // This is not htread safe!
    // must lock internal shape array before copyinf
    virtual std::vector<Shape*> getShapes() = 0;
    // one game tick
    // returns false if game has ended
    virtual bool tick() = 0;
    virtual ~GameInterface(){}
    // Return pointer to RED/BLUE/GREEN spinner
    // button
    // Returns nullptr if no such button is assigned/used
    virtual GameButton* getButtonRED() {return nullptr;}
    virtual GameButton* getButtonBLUE() {return nullptr;}
    virtual GameButton* getButtonGREEN() {return nullptr;}
    // Returns player 1/2 button
    // returns nullptr if no button is assigned to that player
    virtual GameButton* getButtonP1() {return nullptr;}
    virtual GameButton* getButtonP2() {return nullptr;}
protected:
    // This measures time per tick
    // Important to ensure game speed doesn't change
    // when CPU slows down or speeds up
    uint32_t sinceLastTick();
    std::chrono::steady_clock::time_point lastTick;
    bool firstTick;
};

#endif // GAMEINTERFACE_H
