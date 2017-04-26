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
    void updatePlot(QImage p);
    Plotter* getPlotter() const;
    void updateImage(const std::vector<Color>& colors);
    QSize sizeHint() const override;

    void resizeEvent(QResizeEvent * event) override;
signals:
    void updateImageRequest(const std::vector<Color>& colors);
protected:
    QImage plot;
    Plotter* plotter;
    mutable quint32 lastHeight;
    mutable quint32 lastWidth;
};

#endif // PAINTWIDGET_H
