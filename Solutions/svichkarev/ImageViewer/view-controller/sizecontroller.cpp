#include <QGridLayout>
#include "sizecontroller.h"

SizeController::SizeController(QWidget* p, const std::string& string, double min, double max, double val)
    : QWidget(p, Qt::Window), layout(this),  min(min), max(max), slider(min, max)
{
    // установка названия контролла
    label.setText(QString(string.c_str()));
    label.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    // настройка выбирателя: диапазон и шаг
    // физические размеры
    spinEditor.setFixedSize(80, 30);
    spinEditor.setRange(min, max);
    spinEditor.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    spinEditor.setSingleStep(0.1);

    // настройки движка
    slider.setOrientation(Qt::Horizontal);
    slider.setFixedSize(200, 20);
    slider.setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);

    //? как связь организована?
    // регистрация событий
    QObject::connect(&slider, SIGNAL(doubleValueChanged(double)), &spinEditor, SLOT(setValue(double)));
    QObject::connect(&spinEditor, SIGNAL(valueChanged(double)), &slider, SLOT(setDoubleValue(double)));
    QObject::connect(&spinEditor, SIGNAL(valueChanged(double)), this, SLOT(setValue(double)));

    // нормировка значения по-умолчанию под диапазон
    if (val > max) val = max;
    if (val < min) val = min;

    // перевод в проценты
    slider.setValue(val * 10);

    // сборка в заготовку
    layout.addWidget(&label, 0,0, Qt::AlignLeft);
    layout.addWidget(&spinEditor, 0,1, Qt::AlignRight);
    layout.addWidget(&slider, 1,0, Qt::AlignLeft, 2);
    layout.setMargin(20);
    // добавление к форме
    this->setLayout(&layout);

    // не изменяемый контролл
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
}

//?
double SizeController::getValue() const{
    return slider.value();
}

// обработчик события изменения контролла
void SizeController::setValue(double v){
    if (v!=value) { // если новое значение установлено
        value = v;
        // устанавливаем на выбирателе
        spinEditor.setValue(value);
        // вызываем событие на других элементах связанных
        emit valueChanged(value);
    }
}

