#include "mqpainter.h"

#include <QPainter>

#include <math.h>

MQPainter::MQPainter( QImage * im, const QColor & c ):
    img( im ), color( c )
{
}

void MQPainter::drawImage( QWidget * w ){
    QPainter realPainter( w );
    realPainter.drawImage( 0, 0, *img );
}

void MQPainter::drawPoint( int x, int y ){
    // проверка на вхождение в пределы картинки
    if( ( y < 0 ) || ( x < 0 ) ||
        ( x > img->width() ) || ( y > img->height() ) ){
        return;
    }

    uchar * bytes = img->bits();
    int bpl = img->bytesPerLine();

    bytes[ y*bpl + x*3     ] = color.red();
    bytes[ y*bpl + x*3 + 1 ] = color.green();
    bytes[ y*bpl + x*3 + 2 ] = color.blue();
}

// Алгоритм из задания про круг
void MQPainter::drawCircle( const QPoint & center, int radius ){
    int x0 = center.x() + img->width() / 2;
    int y0 = center.y() + img->height()/ 2;

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
    int x1 = p1.x() + img->width() / 2;
    int y1 = p1.y() + img->height()/ 2;
    int x2 = p2.x() + img->width() / 2;
    int y2 = p2.y() + img->height()/ 2;
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

// Функция обёртка
void MQPainter::drawBezier( const QPoint & p1, const QPoint & p2,
                 const QPoint & p3, const QPoint & p4){

    recursive_bezier( p1.x(), p1.y(), p2.x(), p2.y(),
                      p3.x(), p3.y(), p4.x(), p4.y() );
}

// рекурсивная функция деления пополам
void MQPainter::recursive_bezier(double x1, double y1,
                      double x2, double y2,
                      double x3, double y3,
                      double x4, double y4){

    double m_distance_tolerance = 0.25;

   // Вычислить все средние точек отрезков
   //----------------------
   double x12  = (x1 + x2) / 2;
   double y12  = (y1 + y2) / 2;
   double x23  = (x2 + x3) / 2;
   double y23  = (y2 + y3) / 2;
   double x34  = (x3 + x4) / 2;
   double y34  = (y3 + y4) / 2;
   double x123  = (x12 + x23) / 2;
   double y123  = (y12 + y23) / 2;
   double x234  = (x23 + x34) / 2;
   double y234  = (y23 + y34) / 2;
   double x1234 = (x123 + x234) / 2;
   double y1234 = (y123 + y234) / 2;

   // Попытка аппроксимировать всю кривую одним отрезком
     //------------------
     double dx = x4-x1;
     double dy = y4-y1;

     double d2 = fabs(((x2 - x4) * dy - (y2 - y4) * dx));
     double d3 = fabs(((x3 - x4) * dy - (y3 - y4) * dx));

   if( (d2 + d3)*(d2 + d3) < m_distance_tolerance * (dx*dx + dy*dy) ){
      // Нарисовать отрезок и закончить
      //----------------------
      //draw_line(x1, y1, x4, y4);
       QPoint p1(x1, y1);
       QPoint p4(x4, y4);
       drawLine( p1, p4 );
   } else{
      // Продолжить деление
      //----------------------
      recursive_bezier(x1, y1, x12, y12, x123, y123, x1234, y1234);
      recursive_bezier(x1234, y1234, x234, y234, x34, y34, x4, y4);
   }
}

void MQPainter::drawLine( int y, int startX, int endX, const QColor & color ){
    int w = img->width();
    int h = img->height();

    setColor( color );

    startX += w / 2;
    endX += w / 2;
    for( int x = startX; x <= endX; x++ ){
        drawPoint( x, y + h/2 );
    }
}
