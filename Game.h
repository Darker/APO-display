#ifndef GAME_H
#define GAME_H
class Shape;
#include <vector>
class Game
{
public:
    Game();
    // Moves platform of player X
    void movePlayer(int playerID, int offset);
    // This is not htread safe!
    // must lock internal shape array before copyinf
    std::vector<Shape*> getShapes();
};

#endif // GAME_H
