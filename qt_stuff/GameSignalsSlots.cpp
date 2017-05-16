#include "GameSignalsSlots.h"
#include "GameInterface.h"
#include "MainWindow.h"
void GameSignalsSlots::doGameTick()
{
    game->tick();
}

void GameSignalsSlots::doRenderTick()
{
    std::fill(pixmap.begin(), pixmap.end(), 0);
    std::vector<Shape*> shapes = game->getShapes();

    for(size_t i=0, l=shapes.size(); i<l; ++i) {
        Shape* shape = shapes[i];
        shape->renderAntialiased(pixmap, GAME_WIDTH, GAME_HEIGHT);
        delete shape;
    }
    window->update(pixmap);
}
