#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QImage>

class Plotter : public QObject {
    Q_OBJECT
public:
    Plotter(QSize size, QRectF range, QVector<double> data, QObject* parent=nullptr);

signals:
    void done(QImage);
    void cleanup();

public slots:
    void plot();

private:
    inline QPointF map(double x, double y) {
        return QPointF(_size.width() * (x / (_range.width() - _range.x())),
                       _size.height() * (y / (_range.height() - _range.y())));
    }

    QSize _size;
    QRectF _range;
    QVector<double> _data;
};

#endif // PLOTTER_H
