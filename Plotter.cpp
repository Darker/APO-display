#include "Plotter.h"
#include <QElapsedTimer>
#include <QPainter>
#include <QPen>
#include <QDebug>
Plotter::Plotter(QSize size, QRectF range, QVector<double> data, QObject *parent) : QObject(parent), _size(size), _range(range), _data(data)
{

}

void Plotter::plot() {
    QElapsedTimer t;
    t.start();
    QImage img(_size, QImage::Format_ARGB32_Premultiplied);
    img.fill(Qt::white);
    QPainter p(&img);
    QPen pen(Qt::darkBlue);
    pen.setWidth(1);
    p.setPen(pen);
    for (int i = 0; i < _data.size(); i += 2) {
        p.drawPoint(map(_data[i], _data[i + 1]));
    }
    qDebug() << "plotted in" << t.elapsed() << "msec";
    emit done(img);
    emit cleanup();
}
