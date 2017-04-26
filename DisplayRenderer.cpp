#include "DisplayRenderer.h"
#include "defines.h"
#include "display_magic.h"
#include <chrono>
#include <iostream>

DisplayRenderer::DisplayRenderer()
    : pixmapChanged(true)
{

}

void DisplayRenderer::updatePixmap(const std::vector<Color>& newPixmap)
{
    pixmapLock.lock();
    pixmap = newPixmap;
    pixmapChanged = true;
    pixmapLock.unlock();
}

void DisplayRenderer::start()
{
    if(startLock.try_lock()) {
        backgroundThread = std::thread(&DisplayRenderer::renderLoop, this);
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
    const int minInterval = 33;
    while(true) {
        const std::chrono::steady_clock::time_point render_start = std::chrono::steady_clock::now();
        iterator = 0;
        pixmapLock.lock();
        if(pixmapChanged)
            updatePixmapCache();
        pixmapLock.unlock();

        uint32_t maxIter = pixmapCache.size();
        for (uint16_t y = 0; y < GAME_HEIGHT ; y++) {
            if(iterator>=maxIter) {
                break;
            }
            for (uint16_t x = 0; x < GAME_WIDTH ; x++) {
                  parlcd_write_data(parlcd_mem_base, (uint16_t)pixmapCache[iterator++]);
            }
        }
        uint32_t renderDuration = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - render_start).count();
        // if we didn't waste all 33 ms rendering, we can take a break now
        if(renderDuration<minInterval) {
            const uint32_t restSleep = minInterval-renderDuration;
            std::cout<<"Rendering took "<<renderDuration<<" milliseconds. Sleeping for another "<<restSleep<<" ms\n";
            std::this_thread::sleep_for(std::chrono::milliseconds(minInterval-renderDuration));
        }
        else {
            std::cout<<"FPS WARNING: Rendering took "<<renderDuration<<" milliseconds!\n";
        }
    }
}

void DisplayRenderer::updatePixmapCache()
{
    if(pixmapChanged) {
        pixmapCache.resize(pixmap.size());
        for(size_t i=0, l=pixmap.size(); i<l; ++i) {
            pixmapCache[i] = pixmap[i];
        }
        pixmapChanged = false;
    }
}
