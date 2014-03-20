#include "circle.h"

#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QFile>

#include <cmath>
#include <QDebug>  //TODO: убрать

Circle::Circle( int x, int y, int r){
    setX(x);
    setY(y);
    setR(r);
}

// устанавливаем новые значения вызываем сигнал изменения
void Circle::setX( int x ){
    qDebug()  << x; //TODO: убрать
    centreX = x;
    emit changeX( x );
}

void Circle::setY( int y ){
    qDebug() << y; //TODO: убрать
    centreY = y;
    emit changeY( y );
}

void Circle::setR( int r ){
    qDebug()   << r; //TODO: убрать
    radius = r;
    emit changeR( r );
}

// Главный метод всей лабы - отрисовка круга
void Circle::draw( QImage * backBuffer, const QColor& color ){
    if( !backBuffer ){ // надо кидать исключение
        return;
    }

    backBuffer->fill( Qt::white );

    int w = backBuffer->width();
    int h = backBuffer->height();
    uchar* bytes = backBuffer->bits();
    int bpl = backBuffer->bytesPerLine();

    double X0 = centreX + w * 1.0 / 2;
    double Y0 = centreY + h * 1.0 / 2;
    int r = radius;

    int leftY = Y0 - r > 0 ? round(Y0 - r) : 0;
    int rightY= Y0 + r < h ? round(Y0 + r) : h - 1;

    double sq_r = r * r;

    int x = 0;
    int y_bpl = leftY * bpl;

    int red = color.red();
    int green = color.green();
    int blue = color.blue();

    // ОПТИМИЗИРОВАННЫЙ КУСОК
    for( int y = leftY; y <= rightY; ++y ){
        double sq = sqrt( sq_r - (y-Y0)*(y-Y0) );
        int xa = 3*round( -1 * sq  + X0 );
        int xb = 3*round(      sq  + X0 );
        if (xa < 0) xa = 0;
        if (xb >= w*3) xb = (w-1)*3;

        for( x = xa; x <= xb; x+=3 ){
            bytes[ y_bpl + x     ] = red;
            bytes[ y_bpl + x + 1 ] = green;
            bytes[ y_bpl + x + 2 ] = blue;
        }
        y_bpl += bpl;
    }
}
