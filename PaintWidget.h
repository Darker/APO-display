#ifndef PAINTWIDGET_H
#define PAINTWIDGET_H

#include <QWidget>
class PaintWidget : public QWidget {
    Q_OBJECT
public:
    PaintWidget(QWidget * parent = 0);

protected:
    void paintEvent(QPaintEvent *) {
        QPainter p(this);
        p.drawImage(QPoint(0, 0), plot);
    }

public slots:
    void updatePlot(QImage p) {
        plot = p;
        repaint();
    }

private:
    QImage plot;
};

#endif // PAINTWIDGET_H
