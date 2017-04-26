#ifndef QTVIRTUALDISPLAY_H
#define QTVIRTUALDISPLAY_H
#include <QThread>
#include <QObject>
#include <QMutex>
#include <QTimer>
class MainWindow;
#include "Color.h"
class QApplication;
class QtVirtualDisplayPrivate: public QObject {
Q_OBJECT
public:
    QtVirtualDisplayPrivate();
    virtual void setNextPixel(uint16_t color);
    virtual ~QtVirtualDisplayPrivate();

signals:
    void setPixel(quint32 x, quint32 y, Color color);
    void plot();
public slots:
    void guiThread();
protected:
    QThread mainThread;
    QMutex initLock;
    MainWindow* window;
    QApplication* app;
    //QApplication app;
    quint32 pixelIndex;
};
#endif // QTVIRTUALDISPLAY_H
