#ifdef _QT_COMPILE
#include "mainFunctions.h"
#include "MainWindow.h"
#include <QApplication>
#include <QTimer>
#include "Game.h"
#include "Color.h"
#include <vector>
#include "Shape.h"
#include "ShapeRendering.h"
#include "defines.h"
int mainQt(int argc, char *argv[]) {
    // Register meta types for events
    qRegisterMetaType<Color>("Color");
    qRegisterMetaType<std::vector<Color> >("std::vector<Color>");

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();
    Game* game = new Game();
    QTimer renderLoop;
    std::vector<Color>* pixmapPtr = new std::vector<Color>();

    pixmapPtr->resize(GAME_WIDTH*GAME_HEIGHT);
    line(*pixmapPtr, Color(255,0,0), 0,0,50,50, GAME_WIDTH);
    circle(*pixmapPtr, Color(0,255,0), 30, 20, 20, GAME_WIDTH);
    QObject::connect(&renderLoop, &QTimer::timeout, [game, pixmapPtr, w]() {
        std::vector<Color>& pixmap = *pixmapPtr;
        std::fill(pixmap.begin(), pixmap.end(), 0);
        std::vector<Shape*> shapes = game->getShapes();

        for(size_t i=0, l=shapes.size(); i<l; ++i) {
            shapes[i]->render(pixmap, GAME_WIDTH, GAME_HEIGHT);
            delete shapes[i];
        }
        w->update(pixmap);
    });
    renderLoop.start(33);
    QTimer gameLoop;
    QObject::connect(&gameLoop, &QTimer::timeout, [game]() {
        game->tick();
    });
    gameLoop.start(10);

    int returnValue = a.exec();
    delete game;
    delete w;
    return returnValue;
}
#endif
