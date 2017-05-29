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
#include "GameSignalsSlots.h"
#include "GameIntersectionTest.h"
#include "GameMenu.h"
int mainQt(int argc, char *argv[]) {
    // Register meta types for events
    qRegisterMetaType<Color>("Color");
    qRegisterMetaType<std::vector<Color> >("std::vector<Color>");

    QApplication a(argc, argv);
    MainWindow* w = new MainWindow();
    GameSignalsSlots* signalForward = new GameSignalsSlots(w);
    w->show();
    GameInterface* game = nullptr;
#ifdef _JAKUBX
    GameMenu* menu = new GameMenu();
    game = menu;
    menu->addEntry("Intersections", new GameIntersectionTest());
    menu->addEntry("Pong", new Game());
    menu->addEntry("Car", new GameJakub());
    menu->addEntry("Exit", nullptr);
#else
    game = new Game();
#endif
    signalForward->game = game;
    signalForward->window = w;


    QTimer renderLoop;
    QObject::connect(&renderLoop, &QTimer::timeout, signalForward, &GameSignalsSlots::doRenderTick);
    renderLoop.start(33);
    //QTimer gameLoop;
    QObject::connect(&renderLoop, &QTimer::timeout, signalForward, &GameSignalsSlots::doGameTick);
    //gameLoop.start(33);

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
    QObject::connect(w, &MainWindow::buttonClicked, [game](const int index) {
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
