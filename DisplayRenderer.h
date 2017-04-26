#ifndef DISPLAYRENDERER_H
#define DISPLAYRENDERER_H
#include "Color.h"
#include <stddef.h>
#include <thread>
#include <mutex>
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
protected:
    // rendering in another thread
    void renderLoop();
    // Not thread safe and also none of your business
    // do not call or mention
    void updatePixmapCache();

    // color data
    std::vector<Color> pixmap;
    std::vector<uint16_t> pixmapCache;
    bool pixmapChanged;

    std::mutex startLock;
    std::mutex pixmapLock;
    std::thread backgroundThread;
};

#endif // DISPLAYRENDERER_H
