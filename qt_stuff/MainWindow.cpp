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

    QObject::connect(ui->redButton, &SpinnerButton::moved, this, [this](qint16 offset) {
        emit buttonMoved(0, offset);
    });
    QObject::connect(ui->greenButton, &SpinnerButton::moved, this, [this](qint16 offset) {
        emit buttonMoved(1, offset);
    });
    QObject::connect(ui->blueButton, &SpinnerButton::moved, this, [this](qint16 offset) {
        emit buttonMoved(2, offset);
    });
    QObject::connect(ui->redButton, &SpinnerButton::clicked, this, [this]() {
        emit buttonClicked(0);
    });
    QObject::connect(ui->greenButton, &SpinnerButton::clicked, this, [this]() {
        emit buttonClicked(1);
    });
    QObject::connect(ui->blueButton, &SpinnerButton::clicked, this, [this]() {
        emit buttonClicked(2);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::update(const std::vector<Color>& colors)
{
    emit updateRequested(colors);
}

Plotter*MainWindow::getPlotter()
{
    return ui->widget->getPlotter();
}
