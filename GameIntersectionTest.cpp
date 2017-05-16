#include "GameIntersectionTest.h"
#include "defines.h"
GameIntersectionTest::GameIntersectionTest() :
    GameInterface(),
    a(10, GAME_HEIGHT/2, 20, 20, 2, Color(0, 199, 0), Color(255, 255, 255)),
    b(GAME_WIDTH-10, GAME_HEIGHT/2, 20, 20, 2, Color(0, 199, 0), Color(150, 150, 150)),
    activeRect(nullptr)
{
    activeRect = &a;
}

std::vector<Shape*> GameIntersectionTest::getShapes()
{
    std::vector<Shape*> result;
    shapeMutex.lock();
    result.push_back(a.cloneNew());
    result.push_back(b.cloneNew());
    shapeMutex.unlock();
    return result;
}

void GameIntersectionTest::tick()
{
    const double deltaT = sinceLastTick()/1000.0;
    shapeMutex.lock();
    double offx = button1.moveDelta();
    double offy = button3.moveDelta();

    if(button2.moveDelta()!=0) {
        ShapeRectangleBorder* newActiveRect = activeRect==&a?&b:&a;
        activeRect->setBorder_color(Color::GRAY);

    }

    shapeMutex.unlock();
}
