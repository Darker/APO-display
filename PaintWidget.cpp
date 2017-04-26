#include "PaintWidget.h"
#include "Plotter.h"
#include "defines.h"
#include <QThread>
#include <QPainter>
#include <QElapsedTimer>
#include <QDebug>
PaintWidget::PaintWidget(QWidget* parent)
    : QWidget(parent)
    , plotter(new Plotter(QSize(GAME_WIDTH, GAME_HEIGHT)))
    , plot(QImage(GAME_WIDTH, GAME_HEIGHT, QImage::Format_ARGB32_Premultiplied))
{

    QThread * thread = new QThread;
    plotter->moveToThread(thread);

    // do connections
    connect(thread, &QThread::started, plotter, &Plotter::plot);
    connect(plotter, &Plotter::done, this, &PaintWidget::updatePlot);
    //connect(plotter, SIGNAL(cleanup()), thread, SLOT(quit()));
    connect(thread, &QThread::finished, plotter, &QObject::deleteLater);
    connect(thread, &QThread::finished, thread, &QObject::deleteLater);

    thread->start();
}

void PaintWidget::paintEvent(QPaintEvent* e) {
    QWidget::paintEvent(e);
    QPainter p(this);
    p.drawImage(rect(), plot, plot.rect());
    p.end();
}

Plotter* PaintWidget::getPlotter() const
{
    return plotter;
}

void PaintWidget::updateImage(const std::vector<Color>& colors)
{
    emit updateImageRequest(colors);
}
