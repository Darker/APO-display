#include "PaintWidget.h"

PaintWidget::PaintWidget(QWidget* parent) : QWidget(parent) {
    // prepping data
    QVector<double> data;
    data.reserve(200000);
    for (int i = 0; i < 200000; ++i) data.append((double)qrand() / RAND_MAX);

    // create plotter and thread
    Plotter * p = new Plotter(size(), QRectF(0, 0, 1, 1), data);
    QThread * thread = new QThread;
    p->moveToThread(thread);

    // do connections
    connect(thread, SIGNAL(started()), p, SLOT(plot()));
    connect(p, SIGNAL(done(QImage)), this, SLOT(updatePlot(QImage)));
    connect(p, SIGNAL(cleanup()), thread, SLOT(quit()));
    connect(thread, SIGNAL(finished()), p, SLOT(deleteLater()));
    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));

    thread->start();
}
