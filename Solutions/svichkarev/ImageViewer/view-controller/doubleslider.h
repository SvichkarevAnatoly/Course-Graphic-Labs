#ifndef DOUBLESLIDER_H
#define DOUBLESLIDER_H

#include <QObject>
#include <QSlider>
#include <QDebug>


class DoubleSlider : public QSlider {
    Q_OBJECT

public:
    DoubleSlider( double min, double max,  QWidget *parent = 0) : QSlider(parent) {
        connect(this, SIGNAL(valueChanged(int)),
            this, SLOT(notifyValueChanged(int)));

        // установка границ в процентах
        setRange(min*10, max*10);
    }

signals:
    void doubleValueChanged(double value);

public slots:
    // переводящий в проценты обработчик
    void notifyValueChanged(int value) {
        double doubleValue = value*1.0 / 10;
        emit doubleValueChanged( doubleValue );
    }

    // если пришло значение double
    void setDoubleValue(double value) {
        // заблокировать на время изменения посылку сигналов
        bool t = blockSignals(true);
        setValue((int)value*10);

        // затем разблокировать
        blockSignals(t);
    }
};


#endif // DOUBLESLIDER_H
