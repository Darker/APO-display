#ifndef GAMEMENU_H
#define GAMEMENU_H
#include "GameInterface.h"
#include "threading.h"
class GameMenu : public GameInterface
{
public:
    GameMenu();
    virtual std::vector<Shape*> getShapes() override;
    virtual bool tick() override;
protected:
    std::mutex shapeMutex;



};

#endif // GAMEMENU_H
