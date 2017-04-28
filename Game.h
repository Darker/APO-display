#ifndef GAME_H
#define GAME_H
class Shape;
class Pentagram;
#include <vector>

#include "Circle.h"
#include "Platform.h"

#include "Pentagram.h"
#include "GameInterface.h"

class Game: public GameInterface
{
public:
    Game();
    // Moves platform of player X
    void movePlayer(int playerID, int offset);
    // This is not htread safe!
    // must lock internal shape array before copyinf
    virtual std::vector<Shape*> getShapes();
    // one game tick
    virtual void tick();
    virtual ~Game(){}
protected:
    // Mutex for copying shapes
        // TODO later

    // Some testing garbage
    Circle circle;
    Platform platform1;
    Platform platform2;
};

#endif // GAME_H
