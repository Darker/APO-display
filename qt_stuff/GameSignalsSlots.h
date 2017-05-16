#ifndef GAMESIGNALSSLOTS_H
#define GAMESIGNALSSLOTS_H
#include <QObject>
#include "Color.h"
#include "defines.h"
/**
 * Forwards timer timeouts to game code. This is necessary because GameInterface is not a QObject
 * and therefore cannot receive signals.
 */
class GameInterface;
class MainWindow;
class GameSignalsSlots: public QObject
{
Q_OBJECT
public:
    GameSignalsSlots(QObject* parent=nullptr) : QObject(parent), pixmap(GAME_WIDTH*GAME_HEIGHT) {}
    GameInterface* game;
    MainWindow* window;

public slots:
    void doGameTick();
    void doRenderTick();
protected:
    std::vector<Color> pixmap;
};

#endif // GAMESIGNALSSLOTS_H
