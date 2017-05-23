#ifndef GAME_H
#define GAME_H
class Shape;
class Pentagram;
#include <vector>

#include "Circle.h"
#include "Platform.h"

#include "Pentagram.h"
#include "GameInterface.h"
#include "GameButton.h"

#include <mutex>
#include <random>

class Game: public GameInterface
{
public:
    Game();
    // Moves platform of player X
    void movePlayer(int playerID, int offset);

    // must lock internal shape array before copyinf
    virtual std::vector<Shape*> getShapes();

    // one game tick
    virtual bool tick();
    virtual ~Game(){}

protected:
    // Mutex for copying shapes
    std::mutex shapeMutex;
    // Some testing garbage
    Circle circle;
    Circle circle_2;

    Platform platform1;
    Platform platform2;
    GameButton button1;
    GameButton button2;
    GameButton button3;
    int player1_score;
    int player2_score;
    std::string pl1_str;
    std::string pl2_str;

    virtual GameButton* getButtonRED() override {return &button1;}
    virtual GameButton* getButtonBLUE() override {return &button3;}
    virtual GameButton* getButtonGREEN() override {return &button2;}

    std::random_device rd;
    std::mt19937 mt;
};

#endif // GAME_H
