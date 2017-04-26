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

void PaintWidget::updatePlot(QImage p) {
    plot = p;
    repaint();
}

Plotter* PaintWidget::getPlotter() const
{
    return plotter;
}

void PaintWidget::updateImage(const std::vector<Color>& colors)
{
    emit updateImageRequest(colors);
}

QSize PaintWidget::sizeHint() const {
    QSize s = this->parentWidget()->size();


    const quint32 maxWidth = (s.height()*3)/2;
    const quint32 maxHeight = (s.width()*2)/3;

    // Chose the smaller option of those two to prevent overflowing out
    if(maxWidth > s.width() && maxHeight<=s.height()) {
        // width is the limiting factor
        s.setHeight(maxHeight);
    }
    else if(maxHeight>=s.height() && maxWidth<=s.width()){
        // height is the limiting factor
        s.setWidth(maxWidth);
    }
    lastHeight = s.height();
    lastWidth = s.width();
    //qDebug()<<(s.width()*2)/3<<(s.height());
    return s;
}

void PaintWidget::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);

    if (lastHeight!=height() || lastWidth!=width()) {
        //const QSize hint(sizeHint());
        //setMinimumSize(hint.width()-3, hint.height()-2);
        //setMaximumSize(hint.width()+3, hint.height()+2);
        updateGeometry(); // it is possible that this call should be scheduled to next iteration of event loop
    }
    else {
        //const QSize hint(sizeHint());
        //setMinimumSize(6, 4);
        //setMaximumSize(hint.width()+30, hint.height()+20);
    }
}
