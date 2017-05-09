#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H
#include "Color.h"
#include <stddef.h>
#include "WaitMutex.h"

#include <vector>

class DisplayRenderer
{
public:
    DisplayRenderer();
    // thread safe method
    // updates pixmap
    // blocks if pixmap is being currently read
    void updatePixmap(const std::vector<Color>& newPixmap);
    // Starts the rendering thread
    // thread safe, can be called multiple times
    void start();

    // pointer to mem interface
    // this is dirty way to get access to the interface from the outside
    // this exists because I didn't think it through in the beginning and am to lazy to refactor
    WaitMutex waitForPalcdInit;
    unsigned char* parlcd_mem_base;
protected:
    // rendering in another thread
    void renderLoop();
    // Not thread safe and also none of your business
    // do not call or mention
    void updatePixmapCache();

    // color data
    std::vector<Color> pixmap;
    std::vector<uint32_t> pixmapCache;
    bool pixmapChanged;

    std::mutex startLock;
    bool started;
    WaitMutex frameWait;
    std::mutex pixmapLock;
    std::thread backgroundThread;


};

#endif // DISPLAYRENDERER_H
