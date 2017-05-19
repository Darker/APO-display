#include "GameMenu.h"
#include "ShapeText.h"
GameMenu::GameMenu()
{

}
std::vector<Shape*> GameMenu::getShapes()
{
    std::vector<Shape*> result;
    shapeMutex.lock();
    result.push_back(new ShapeText("abcdefg", Color::RED, 10, 40, "diablo.ttf"));
    shapeMutex.unlock();
    return result;
}

bool GameMenu::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    shapeMutex.lock();

    shapeMutex.unlock();
    return true;
}
