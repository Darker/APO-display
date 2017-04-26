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
    if(QThread::currentThread()!=this->thread()) {
        qCritical()<<"Plotter not plotting in it's own thread!!!";
    }
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

    //qDebug() << "plotted in" << t.elapsed() << "msec";
    emit done(img);
    emit cleanup();
    //delete rawImage;
}

//void Plotter::plotRange(quint32 start, quint32 end)
//{
//    QElapsedTimer t;
//    t.start();
//    QImage img(size.width(), size.height(), QImage::Format_RGB888);
//    //img.fill(Qt::black);
//    unsigned char* const rawImage = img.bits();
//    //unsigned char* const rawImage = (unsigned char*)std::malloc(size.width()*size.height()*3);
//    for (int i = qMin((int)start, data.size()-1) ,
//             l = qMin((int)end, data.size()-1)
//         ; i < l); i++) {
//        const Color& color = data[i];
//        const int pos = i*3;
//        rawImage[pos] = color.r;
//        rawImage[pos+1] = color.g;
//        rawImage[pos+2] = color.b;
//    }

//    emit done(img);
//    emit cleanup();
//}

void Plotter::update(const std::vector<Color>& newData)
{
    data = newData;
    plot();
}

void Plotter::setPixel(quint32 x, quint32 y, Color color)
{
    quint32 offset = x+size.width()*x;
    if(offset<data.size())
        data[offset] = color;
}
