#include "mainFunctions.h"
#include "defines.h"
#include "Game.h"
#include "DisplayRenderer.h"
#include <stddef.h>
#include <thread>
#include <mutex>
#include <iostream>
#include "WaitMutex.h"
#ifdef _QT_COMPILE
    #include <QApplication>
#endif
#include "GameJakub.h"
GameInterface* game;

DisplayRenderer renderer;
WaitMutex waitForFrame;
// this thread calls game ticks
void runGame() {
    const uint32_t minInterval = 20;
    while(true) {
        const std::chrono::steady_clock::time_point tick_start = std::chrono::steady_clock::now();
        game->tick();
        uint32_t tickDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - tick_start).count();
        // notify that next frame can be rendered
        waitForFrame.unlock();

        // if we didn't waste all time we can take a break
        if(tickDuration < minInterval) {
            std::this_thread::sleep_for(std::chrono::milliseconds(minInterval-tickDuration));
        }
    }
}
// this thread reads and renders game objects
void paintGame() {
    std::vector<Color> pixmap;
    pixmap.resize(GAME_WIDTH*GAME_HEIGHT);
    while(true) {
        std::fill(pixmap.begin(), pixmap.end(), 0);

        std::vector<Shape*> shapes = game->getShapes();
        for(size_t i=0, l=shapes.size(); i<l; ++i) {
            shapes[i]->render(pixmap, GAME_WIDTH, GAME_HEIGHT);
            delete shapes[i];
        }
        renderer.updatePixmap(pixmap);
        // wait for next frame
        waitForFrame.wait();
        //std::this_thread::sleep_for(std::chrono::milliseconds(25));
    }
}
std::thread drawThread;
std::thread gameThread;
void startLinuxRenderer() {
#ifdef _JAKUBX
    game = new GameJakub();
#else
    game = new Game();
#endif
    drawThread = std::thread(paintGame);
    gameThread = std::thread(runGame);
    renderer.start();
}

void exitLinuxRenderer() {
    drawThread.join();
    gameThread.join();
    delete game;
}

int mainLinux(int argc, char *argv[])
{
    startLinuxRenderer();
    exitLinuxRenderer();
    return 0;
}
