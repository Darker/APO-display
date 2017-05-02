#ifndef QTVIRTUALDISPLAY_H
#define QTVIRTUALDISPLAY_H
#include <QThread>
#include <QObject>
#include <QMutex>
#include <QTimer>
#include <QEvent>
#include "defines.h"
class MainWindow;
#include "Color.h"
class QApplication;
class QtVirtualDisplayPrivate: public QObject {
Q_OBJECT
public:
    QtVirtualDisplayPrivate();
    virtual void setNextPixel(uint16_t color);
    virtual ~QtVirtualDisplayPrivate();

    class InitEvent: public QEvent {
    public:
        InitEvent() : QEvent((QEvent::Type)(QEvent::Type::User+666)) {}
    };
    class PixelEvent: public QEvent {
    public:
        PixelEvent(std::vector<uint16_t>& pixels)
            : QEvent((QEvent::Type)(QEvent::Type::User+667))
            , data(pixels)
        {}
        std::vector<uint16_t> data;
    };
    virtual bool event(QEvent *);
signals:
    void setPixel(quint32 x, quint32 y, Color color);
    void setPixels(quint32 start, std::vector<uint16_t> pixels);
    void plot();
public slots:
    void guiThread();
protected:
    QThread* mainThread;
    MainWindow* window;
    QApplication* app;
    //QApplication app;
    quint32 pixelIndex;
    // used to wait until inicialized
    QMutex initMutex;
    bool isInicialized;

    static const quint64 COLORS_TO_BUFFER = (GAME_WIDTH*GAME_HEIGHT)/20;

    // These variables beong to the rendering thread and are used
    // to buffer received pixels
    // no less than 10 pixels will be sent as an event
    std::vector<uint16_t> pixels;
};

#endif // QTVIRTUALDISPLAY_H
