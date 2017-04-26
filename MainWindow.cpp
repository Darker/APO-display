#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "PaintWidget.h"
#include "Plotter.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QObject::connect(this, &MainWindow::updateRequested, ui->widget->getPlotter(), &Plotter::update);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const std::vector<Color>& colors)
{
    emit updateRequested(colors);
}
