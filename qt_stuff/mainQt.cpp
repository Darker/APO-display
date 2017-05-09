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
#include "GameJakub.h"
int mainQt(int argc, char *argv[]) {
    // Register meta types for events
    qRegisterMetaType<Color>("Color");
    qRegisterMetaType<std::vector<Color> >("std::vector<Color>");

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    w->show();
    GameInterface* game = nullptr;
#ifdef _JAKUBX
    game = new GameJakub();
#else
    game = new Game();
#endif
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
            shapes[i]->renderAntialiased(pixmap, GAME_WIDTH, GAME_HEIGHT);
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

    //if(GameJakub* testGame = dynamic_cast<GameJakub*>(game)) {
    QObject::connect(w, &MainWindow::buttonMoved, [game](const int index, const qint16 offset) {
        GameButton* button = nullptr;
        switch(index) {
        case 0: button = game->getButtonRED();break;
        case 1: button = game->getButtonGREEN();break;
        case 2: button = game->getButtonBLUE();break;
        }
        if(button!=nullptr) {
            button->addMovement(offset);
        }
    });
    QObject::connect(w, &MainWindow::buttonMoved, [game](const int index) {
        GameButton* button = nullptr;
        switch(index) {
        case 0: button = game->getButtonRED();break;
        case 1: button = game->getButtonGREEN();break;
        case 2: button = game->getButtonBLUE();break;
        }
        if(button!=nullptr) {
            button->clicked();
        }
    });
    //}

    int returnValue = a.exec();
    delete game;
    delete w;
    return returnValue;
}
#endif
