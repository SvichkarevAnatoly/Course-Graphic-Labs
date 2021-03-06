#include <QGridLayout>
#include "sizecontroller.h"

SizeController::SizeController( QWidget* p, const std::string & string, int min, int max, int val )
    : QWidget( p, Qt::Window), layout( this ), min(min), max(max)
{
    // устанавливаем надпись и делаем её фиксированной
    label.setText( QString(string.c_str()) );
    label.setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    // устанавливаем предельные значения
    spinEditor.setRange( min, max );
    spinEditor.setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );

    slider.setOrientation( Qt::Horizontal );
    slider.setRange( min, max );
    slider.setSizePolicy( QSizePolicy::Fixed,QSizePolicy::Fixed );

    // связываем перекрёстно друг с другом
    QObject::connect( &slider, SIGNAL(valueChanged(int)), &spinEditor, SLOT(setValue(int)));
    QObject::connect( &spinEditor, SIGNAL(valueChanged(int)), &slider, SLOT(setValue(int)));
    QObject::connect( &spinEditor, SIGNAL(valueChanged(int)), this, SLOT(setValue(int)));

    if (val > max) val = max;
    if (val < min) val = min;
    slider.setValue( val );

    // компоновка элементов
    layout.addWidget(&label, 0,0, Qt::AlignLeft);
    layout.addWidget(&spinEditor, 0,1, Qt::AlignRight);
    layout.addWidget(&slider, 1,0, Qt::AlignLeft, 2);
    layout.setMargin(20);

    setLayout( &layout );

    setSizePolicy( QSizePolicy::Fixed, QSizePolicy::Fixed );
}

int SizeController::getValue() const{
    return slider.value();
}

void SizeController::setValue( int v ){
    if( v != value ) {
        value = v;
        // поменять значение и вызвать событие
        slider.setValue( value );
        emit valueChanged( value );
    }
}
