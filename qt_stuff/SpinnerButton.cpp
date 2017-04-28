#include "SpinnerButton.h"
#include "ui_SpinnerButton.h"

SpinnerButton::SpinnerButton(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SpinnerButton)
{
    ui->setupUi(this);
    QObject::connect(ui->redButton, &QPushButton::clicked, this, &SpinnerButton::clicked, Qt::QueuedConnection);
    QObject::connect(ui->redSpinner, &QDial::valueChanged, this, &SpinnerButton::sliderValueChanged);
    lastValue = ui->redSpinner->value();
}

SpinnerButton::~SpinnerButton()
{
    delete ui;
}

void SpinnerButton::sliderValueChanged(int val)
{
    // distances less than 127 are always without overflow
    if(qAbs(val-lastValue)<127) {
        emit moved(val - lastValue);
    }
    else {
        // movement over the 255 - 0 overflow point
        if(lastValue<val) {
            emit moved(-255+val-lastValue-1);
        }
        else {
            emit moved(255-lastValue+val+1);
        }
    }
    lastValue = val;
}
