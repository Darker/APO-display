#ifndef PLOTTER_H
#define PLOTTER_H

#include <QObject>
#include <QImage>
#include <Color.h>
class Plotter : public QObject {
    Q_OBJECT
public:
    Plotter(QSize size, QObject* parent=nullptr);

signals:
    void done(QImage);
    void cleanup();

public slots:
    void plot();
    void update(const std::vector<Color>& data);

private:
    /*inline QPointF map(double x, double y) {
        return QPointF(_size.width() * (x / (_range.width() - _range.x())),
                       _size.height() * (y / (_range.height() - _range.y())));
    }*/

    QSize size;
    std::vector<Color> data;
};

#endif // PLOTTER_H
