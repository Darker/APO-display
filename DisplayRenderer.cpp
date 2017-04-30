#include "DisplayRenderer.h"
#include "defines.h"
#include "display_magic.h"
#include <chrono>
#include <iostream>

DisplayRenderer::DisplayRenderer()
    : pixmapChanged(true)
    , started(false)
{

}

void DisplayRenderer::updatePixmap(const std::vector<Color>& newPixmap)
{
    std::unique_lock<std::mutex> lk{pixmapLock};
    pixmap = newPixmap;
    pixmapChanged = true;
    //frameWait.unlock();
}

void DisplayRenderer::start()
{
    std::unique_lock<std::mutex> lck(startLock);
    if(!started) {
        backgroundThread = std::thread(&DisplayRenderer::renderLoop, this);
        started = true;
    }
}

void DisplayRenderer::renderLoop()
{
    unsigned char* parlcd_mem_base;
    parlcd_mem_base = (unsigned char*) map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    // In QT mode, the pointer is not used so it doesn't matter if it's null
#ifndef _QT_COMPILE
    if (parlcd_mem_base == NULL)
        exit(1);
#endif
    parlcd_hx8357_init(parlcd_mem_base);

    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    uint32_t iterator = 0;


    // 1000/30 - approx 30 fps as max fps
    const int minInterval = 45;
    while(true) {
        const std::chrono::steady_clock::time_point render_start = std::chrono::steady_clock::now();
        iterator = 0;
        {
            std::unique_lock<std::mutex> lck(startLock);
            if(pixmapChanged) {
                updatePixmapCache();
            }
        }

        const uint32_t maxIter = pixmapCache.size();
        const uint32_t colors = GAME_HEIGHT*GAME_WIDTH;
        for (; iterator+1<maxIter; iterator+=2) {
            //parlcd_write_data(parlcd_mem_base, (uint16_t)pixmapCache[iterator++]);
            parlcd_write_data2x(parlcd_mem_base, pixmapCache[iterator]);
        }
        for (; iterator+1<colors; iterator+=1) {
            parlcd_write_data(parlcd_mem_base, (uint16_t)0);
        }
        uint32_t renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - render_start).count();
        // if we didn't waste all 33 ms rendering, we can take a break now
        if(renderDuration<minInterval) {
            const uint32_t restSleep = minInterval-renderDuration;
            //std::cout<<"Rendering took "<<renderDuration<<" milliseconds. Sleeping for another "<<restSleep<<" ms\n";
            //std::this_thread::sleep_for(std::chrono::milliseconds(minInterval-renderDuration));
        }
        else {
            std::cout<<"FPS WARNING: Rendering took "<<renderDuration<<" milliseconds!\n";
        }
        // If should wait for next frame
        //std::cout<<"Waiting for next frame.\n";
        //frameWait.wait();
        //std::cout<<"Next frame done.\n";
    }
}

void DisplayRenderer::updatePixmapCache()
{
    if(pixmapChanged) {
        pixmapCache.resize(pixmap.size());
        for(size_t i=0, l=pixmap.size(); i+1<l; i+=2) {
            uint32_t colors = pixmap[i];
            colors = colors<<16;
            colors = colors | pixmap[i+1];

            pixmapCache[i] = colors;
        }
        pixmapChanged = false;
    }
}
