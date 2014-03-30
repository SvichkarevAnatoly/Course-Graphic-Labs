#include "mqpainter.h"

#include <QPainter>

MQPainter::MQPainter( QImage * im, const QColor & c ):
    img( im ), color( c )
{
}

void MQPainter::drawImage( QWidget * w ){
    QPainter realPainter( w );
    realPainter.drawImage( 0, 0, *img );
}

void MQPainter::drawPoint( int x, int y ){
    // без проверок, на доверие
    uchar * bytes = img->bits();
    int bpl = img->bytesPerLine();

    bytes[ y*bpl + x*3     ] = color.red();
    bytes[ y*bpl + x*3 + 1 ] = color.green();
    bytes[ y*bpl + x*3 + 2 ] = color.blue();
}

// Алгоритм из задания про круг
void MQPainter::drawCircle( const QPoint & center, int radius ){
    int x0 = center.x();
    int y0 = center.y();

    int x = 0;
    int y = radius;
    int delta = 1 - 2 * radius;
    int error = 0;
    while(y >= 0) {
        drawPoint(x0 + x, y0 + y);
        drawPoint(x0 + x, y0 - y);
        drawPoint(x0 - x, y0 + y);
        drawPoint(x0 - x, y0 - y);
        error = 2 * (delta + y) - 1;
        if(delta < 0 && error <= 0) {
            ++x;
            delta += 2 * x + 1;
            continue;
        }
        error = 2 * (delta - x) - 1;
        if(delta > 0 && error > 0) {
            --y;
            delta += 1 - 2 * y;
            continue;
        }
        ++x;
        delta += 2 * (x - y);
        --y;
    }
}

// Алгоритм Брезенхэма с Вики
void MQPainter::drawLine( const QPoint & p1, const QPoint & p2 ){
    int x1 = p1.x();
    int y1 = p1.y();
    int x2 = p2.x();
    int y2 = p2.y();
    const int deltaX = abs(x2 - x1);
    const int deltaY = abs(y2 - y1);
    const int signX = x1 < x2 ? 1 : -1;
    const int signY = y1 < y2 ? 1 : -1;

    int error = deltaX - deltaY;

    drawPoint( x2, y2 );
    while(x1 != x2 || y1 != y2) {
        drawPoint( x1, y1 );
        const int error2 = error * 2;

        if(error2 > -deltaY) {
            error -= deltaY;
            x1 += signX;
        }
        if(error2 < deltaX) {
            error += deltaX;
            y1 += signY;
        }
    }
}
