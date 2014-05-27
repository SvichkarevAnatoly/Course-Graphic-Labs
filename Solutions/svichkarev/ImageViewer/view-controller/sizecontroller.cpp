#include <QGridLayout>
#include "sizecontroller.h"

SizeController::SizeController(QWidget* p, const std::string& string, double min, double max, double val)
    : QWidget(p, Qt::Window), layout(this),  min(min), max(max), slider(min, max)
{
    label.setText(QString(string.c_str()));
    label.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    spinEditor.setFixedSize(80, 30);
    spinEditor.setRange(min, max);
    spinEditor.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    spinEditor.setSingleStep(0.1);
    slider.setOrientation(Qt::Horizontal);

    slider.setFixedSize(200, 20);
    slider.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    QObject::connect(&slider, SIGNAL(doubleValueChanged(double)), &spinEditor, SLOT(setValue(double)));
    QObject::connect(&spinEditor, SIGNAL(valueChanged(double)), &slider, SLOT(setDoubleValue(double)));
    QObject::connect(&spinEditor, SIGNAL(valueChanged(double)), this, SLOT(setValue(double)));

    if (val > max) val = max;
    if (val < min) val = min;

    slider.setValue(val * 10);

    layout.addWidget(&label, 0,0, Qt::AlignLeft);
    layout.addWidget(&spinEditor, 0,1, Qt::AlignRight);
    layout.addWidget(&slider, 1,0, Qt::AlignLeft, 2);
    layout.setMargin(20);
    this->setLayout(&layout);

    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

double SizeController::getValue() const
{
    return slider.value();
}

void SizeController::setValue(double v)
{
    if (v!=value) {
        value = v;
        spinEditor.setValue(value);
        emit valueChanged(value);
    }
}

