#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class Plotter;
#include "Color.h"
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    virtual ~MainWindow();
signals:
    // This signal is emitted for the underlying Plotter
    void updateRequested(std::vector<Color> colors);
    void buttonMoved(int buttonId, qint16 offset);
    void buttonClicked(int buttonId);
public slots:
    void update(const std::vector<Color>& colors);
    Plotter* getPlotter();
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
