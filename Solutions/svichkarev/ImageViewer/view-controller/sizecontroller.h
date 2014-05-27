#ifndef SIZECONTROLLER_H
#define SIZECONTROLLER_H

#include "doubleslider.h"
#include <QSizePolicy>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>

// класс, упрощающий создания контроллов
class SizeController : public QWidget{
    Q_OBJECT
    QGridLayout layout;
    QLabel label;
    QDoubleSpinBox spinEditor;
    DoubleSlider slider;

    double min;
    double max;
    double value;
public:
    SizeController(QWidget*,const std::string& label, double min, double max, double val);
    double getValue() const;
protected slots:
    void setValue(double v);
signals:
    void valueChanged(double newValue);
};

#endif // SIZECONTROLLER_H
