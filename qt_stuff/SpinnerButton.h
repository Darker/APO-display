#ifndef SPINNERBUTTON_H
#define SPINNERBUTTON_H

#include <QWidget>

namespace Ui {
class SpinnerButton;
}

class SpinnerButton : public QWidget
{
    Q_OBJECT

public:
    explicit SpinnerButton(QWidget *parent = 0);
    ~SpinnerButton();

signals:
    void clicked();
    void moved(qint16 offset);
public slots:
    void sliderValueChanged(int val);
protected:
    int lastValue;
private:
    Ui::SpinnerButton *ui;
};

#endif // SPINNERBUTTON_H
