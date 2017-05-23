#ifndef GAMEMENU_H
#define GAMEMENU_H
#include "GameInterface.h"
#include "threading.h"
#include "ShapeMenuItem.h"
#include "CooldownCalculator.h"
#include <memory>

class GameMenu : public GameInterface
{
public:
    GameMenu();
    virtual std::vector<Shape*> getShapes() override;
    virtual bool tick() override;
    virtual void addEntry(const std::string entry, GameInterface* game);

protected:
    std::mutex shapeMutex;

    std::vector<ShapeMenuItem> items;
    int activeItem;

    GameButton middleButton;
    CooldownCalculator switchCooldown;

    std::shared_ptr<GameInterface> currentGame;
public:
    virtual GameButton* getButtonRED() override;
    virtual GameButton* getButtonBLUE() override;
    virtual GameButton* getButtonGREEN() override;
    virtual GameButton* getButtonP1() override;
    virtual GameButton* getButtonP2() override;
};

#endif // GAMEMENU_H
