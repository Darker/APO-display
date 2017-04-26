#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
#include <QImage>
#include "Color.h"
class Plotter;
class PaintWidget : public QWidget {
    Q_OBJECT
public:
    PaintWidget(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *);

public slots:
    void updatePlot(QImage p) {
        plot = p;
        repaint();
    }
    Plotter* getPlotter() const;
    void updateImage(const std::vector<Color>& colors);
signals:
    void updateImageRequest(const std::vector<Color>& colors);
private:
    QImage plot;
    Plotter* plotter;
};

#endif // PAINTWIDGET_H
