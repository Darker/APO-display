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
#include "GameButton.h"
#include <cmath>
// for knob value struct
#include "display_magic.h"

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


int calculateDelta(int16_t last, int16_t current) {
   // distances less than 127 are always without overflow
    if(std::abs(current-last)<127) {
        return (current - last);
    }
    else {
        // movement over the 255 - 0 overflow point
        if(last<current) {
            return (-255+current-last-1);
        }
        else {
            return (255-last+current+1);
        }
    }
}
// This thread reads RGB knob values
void readInput() {
    bool firstIteration = true;
    parlcd_KnobValues lastKnobValues;
    // wait for display init
    //std::cout<<"Waiting for display init!\n";
    //renderer.waitForPalcdInit.wait();
    unsigned char* button_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    int reddeltasum = 0;
    //std::cout<<"Waiting for display done, pointer: "<<std::hex<<(uint32_t)parlcd_mem_base<<"\n";
    while(true) {
        //std::cout<<"Reading buttons: (wait) ";
        parlcd_KnobValues values = parlcd_knob_values(button_mem_base);
        //std::cout<<"button positions: "<<(int)values.red<<", "<<(int)values.green<<", "<<(int)values.blue<<"\n";
        // first iteration just records inital values
        if(firstIteration) {
            firstIteration = false;
        }
        // every other iteration calculates delta movement
        else {
            if(lastKnobValues.red!=values.red) {
                //std::cout<<"Red moved!\n";
                if(GameButton* red = game->getButtonRED()) {
                    const int delta = calculateDelta(lastKnobValues.red, values.red);
                    reddeltasum+=delta;
                    red->addMovement(delta);
                    //std::cout<<"Red updated, sum: "<<reddeltasum<<"\n";
                }
            }
            else {
                //std::cout<<"Red did not change!\n";
            }
            if(lastKnobValues.green!=values.green) {
                //std::cout<<"green moved!\n";
                if(GameButton* green = game->getButtonGREEN()) {
                    green->addMovement(calculateDelta(lastKnobValues.green, values.green));
                    //std::cout<<"green updated!\n";
                }
            }
            if(lastKnobValues.blue!=values.blue) {
                if(GameButton* blue = game->getButtonBLUE()) {
                    blue->addMovement(calculateDelta(lastKnobValues.blue, values.blue));
                }
            }
        }
        lastKnobValues = values;
        std::this_thread::sleep_for(std::chrono::milliseconds(300));
    }
}


std::thread drawThread;
std::thread gameThread;
std::thread inputThread;
void startLinuxRenderer() {
#ifdef _JAKUBX
    game = new GameJakub();
#else
    game = new Game();
#endif
    inputThread = std::thread(readInput);
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
