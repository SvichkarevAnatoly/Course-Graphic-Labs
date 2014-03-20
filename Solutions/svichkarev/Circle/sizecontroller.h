#ifndef SIZECONTROLLER_H
#define SIZECONTROLLER_H

#include <QSizePolicy>
#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>
#include <QSlider>

class SizeController : public QWidget{
    Q_OBJECT
public:
    static const int DEFAULT_MAX_VALUE = 1000;
private:
    QGridLayout layout; // для расположения движков
    QLabel label; // надпись контрола
    QSpinBox spinEditor; // текстовое поле с кнопками
    QSlider slider; // движок

    int min;
    int max;
    int value;
public:
    SizeController( QWidget*, const std::string & label, int min, int max, int val );
    int getValue() const;
protected slots:
    void setValue( int v );
signals:
    void valueChanged( int newValue );

};

#endif // SIZECONTROLLER_H
