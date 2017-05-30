#include "GameMenu.h"
#include "ShapeText.h"
#include "defines.h"
#include <algorithm>
GameMenu::GameMenu() :
    GameInterface()
  , switchCooldown(0.3)
  , activeItem(-1)
  , currentGame(nullptr)
{

}
std::vector<Shape*> GameMenu::getShapes()
{

    if(currentGame != nullptr) {
        return currentGame->getShapes();
    }
    else {
        std::vector<Shape*> result;
        std::unique_lock<std::mutex> lk{shapeMutex};
        for(const ShapeMenuItem& item: items) {
            result.push_back(item.cloneNew());
        }
        return result;
    }

}
bool GameMenu::render(std::vector<Color>& pixmap, int pixmapWidth, int pixmapHeight)
{
    if(currentGame != nullptr) {
        return currentGame->render(pixmap, pixmapWidth, pixmapHeight);
    }
    else {
        std::unique_lock<std::mutex> lk{shapeMutex};
        for(const ShapeMenuItem& item: items) {
            item.render(pixmap, pixmapWidth, pixmapHeight);
        }
    }
    return true;
}
bool GameMenu::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    switchCooldown.cool(deltaT);
    std::unique_lock<std::mutex> lk{shapeMutex};

    if(currentGame != nullptr) {
        bool result = currentGame->tick();
        if(!result) {
            currentGame = nullptr;
            // clear any movement info
            middleButton.isClicked();
            middleButton.moveDelta();
            return true;
        }
        else {
            return true;
        }
    }

    if(activeItem != -1) {
        // handle clicks first
        if(middleButton.isClicked()) {
            currentGame = items[activeItem].action;
            if(currentGame == nullptr)
                return false;
            else {
                currentGame->reset();
            }
        }
        else {
            int movement = middleButton.moveDelta();
            if(movement!=0 && switchCooldown.isCold()) {
                switchCooldown.start();
                int nextActiveItem = movement>0? activeItem+1:activeItem-1;
                if(nextActiveItem>=(int)items.size())
                    nextActiveItem = 0;
                if(nextActiveItem<0)
                    nextActiveItem = items.size()-1;
                items[activeItem].setSelected(false);
                items[nextActiveItem].setSelected(true);
                activeItem = nextActiveItem;

                for(size_t i=0, l=items.size(); i<l; ++i) {
                    int offset = (i-activeItem)*44;
                    items[i].setY(offset+GAME_HEIGHT/2-22);
                }
            }
        }
    }
    return true;
}

void GameMenu::addEntry(const std::string& entry, GameInterface* game)
{
    ShapeMenuItem item{entry, game};
    item.setX(0);
    if(items.size()>0)
        item.setY(items[items.size()-1].getY() + 44);
    if(activeItem==-1) {
        activeItem = 0;
        item.setSelected(true);
        item.setY(GAME_HEIGHT/2-22);
    }

    items.push_back(item);
}

void GameMenu::selectItem(const std::string& item)
{

    std::string itemLowerCase = item;
    std::transform(itemLowerCase.begin(), itemLowerCase.end(), itemLowerCase.begin(), ::tolower);
    //foreach (const ShapeMenuItem& item, items) {
    for(size_t i=0, l=items.size(); i<l; ++i) {
        const ShapeMenuItem& item = items[i];
        std::string curItem = item.text;
        std::transform(curItem.begin(), curItem.end(), curItem.begin(), ::tolower);
        if(curItem == itemLowerCase) {
            std::unique_lock<std::mutex> lk{shapeMutex};
            currentGame = item.action;
            return;
        }
    }
}

GameButton* GameMenu::getButtonRED()
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(currentGame!=nullptr) {
        return currentGame->getButtonRED();
    }
    return nullptr;
}

GameButton* GameMenu::getButtonBLUE()
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(currentGame!=nullptr) {
        return currentGame->getButtonBLUE();
    }
    return nullptr;
}

GameButton*GameMenu::getButtonGREEN()
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(currentGame!=nullptr) {
        return currentGame->getButtonGREEN();
    }
    else {
        return &middleButton;
    }
    return nullptr;
}

GameButton*GameMenu::getButtonP1()
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(currentGame!=nullptr) {
        return currentGame->getButtonP1();
    }
    return nullptr;
}

GameButton*GameMenu::getButtonP2()
{
    std::unique_lock<std::mutex> lk{shapeMutex};
    if(currentGame!=nullptr) {
        return currentGame->getButtonP2();
    }
    return nullptr;
}


