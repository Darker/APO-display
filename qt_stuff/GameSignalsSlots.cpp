#include "GameSignalsSlots.h"
#include "GameInterface.h"
#include "MainWindow.h"
void GameSignalsSlots::doGameTick()
{
    if(!game->tick()) {
        qDebug()<<"Game decided to end.";
        QCoreApplication::quit();
    }
}

void GameSignalsSlots::doRenderTick()
{
    std::fill(pixmap.begin(), pixmap.end(), 0);

    if(!game->render(pixmap, GAME_WIDTH, GAME_HEIGHT)) {
        std::vector<Shape*> shapes = game->getShapes();
        for(size_t i=0, l=shapes.size(); i<l; ++i) {
            shapes[i]->render(pixmap, GAME_WIDTH, GAME_HEIGHT);
            delete shapes[i];
        }
    }
    window->update(pixmap);
}
