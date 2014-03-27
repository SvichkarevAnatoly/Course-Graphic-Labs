#include "polygon.h"

#include <QPen>

Polygon::Polygon(){
}

Polygon::~Polygon(){
}

void Polygon::draw( QImage * backBuffer, const QColor & color, QPainter & painter ){
    if( !backBuffer ){ // надо кидать исключение
        return;
    }

    /*int w = backBuffer->width();
    int h = backBuffer->height();
    uchar* bytes = backBuffer->bits();
    int bpl = backBuffer->bytesPerLine();

    double X0 = centreX + w * 1.0 / 2;
    double Y0 = centreY + h * 1.0 / 2;

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
    }*/

    backBuffer->fill( Qt::white );

    if( pointsList.size() >= 2 ){
        QPen pen(Qt::green, 5, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin);
        painter.setPen( pen );

        QList<QPoint>::const_iterator it = pointsList.begin();
        QPoint start = *it;
        it++;
        while(it != pointsList.end()) {
            QPoint end = *it;

            // TODO подправить
            QPoint end1( end );
            QPoint start1( start );
            start1.setX( start.x() + backBuffer->width()/2 );
            start1.setY( start.y() + backBuffer->height()/2 );
            end1.setX( end.x() + backBuffer->width()/2 );
            end1.setY( end.y() + backBuffer->height()/2 );


            painter.drawLine( start1, end1 );
            start = end;
            it++;
        }
    }
}

void Polygon::append( const QPoint &newPoint ){
    pointsList.append( newPoint );
}

void Polygon::removeLast(){
    if( pointsList.size() > 0 ){
        pointsList.removeLast();
    }
}
