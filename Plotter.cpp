#include "Plotter.h"
#include <QElapsedTimer>
#include <QPainter>
#include <QPen>
#include <QDebug>
#include <Color.h>
#include <QtMath>
#include <cstdlib>

Plotter::Plotter(QSize size, QObject* parent)
    : QObject(parent)
    , size(size)
{

}

void Plotter::plot() {
    QElapsedTimer t;
    t.start();
    QImage img(size.width(), size.height(), QImage::Format_RGB888);
    //img.fill(Qt::black);
    unsigned char* const rawImage = img.bits();
    //unsigned char* const rawImage = (unsigned char*)std::malloc(size.width()*size.height()*3);
    for (int i = 0; i < data.size(); i++) {
        const Color& color = data[i];
        const int pos = i*3;
        rawImage[pos] = color.r;
        rawImage[pos+1] = color.g;
        rawImage[pos+2] = color.b;
        //const int x = i%size.width();
        //const int y = i/size.width();
        //img.setPixel(x, y, color.qRGBValue());
    }

    //img.loadFromData(rawImage,size.width()*size.height()*3);
    /*QPainter p(&img);
    QPen pen(Qt::darkBlue);
    pen.setWidth(1);
    p.setPen(pen);
    for (int i = 0; i < data.size(); i ++) {
        const Color& color = data[i];
        p.setPen(QColor(color.r,color.g,color.b));
        const int x = i%size.width();
        const int y = i/(double)size.width();
        p.drawPoint(x, y);
    }*/

    qDebug() << "plotted in" << t.elapsed() << "msec";
    emit done(img);
    emit cleanup();
    //delete rawImage;
}

void Plotter::update(const std::vector<Color>& newData)
{
    data = newData;
    plot();
}
