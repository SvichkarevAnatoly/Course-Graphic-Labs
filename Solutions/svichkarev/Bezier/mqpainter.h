#ifndef MQPAINTER_H
#define MQPAINTER_H

#include <QWidget>
#include <QImage>
#include <QPoint>

class MQPainter{
public:
    MQPainter(){}
    MQPainter( QImage * im, const QColor & c = Qt::black );

    void drawPoint( int x, int y );

    void drawLine( const QPoint & p1, const QPoint & p2 );
    void drawCircle( const QPoint & center, int radius );

    // NEW: отрисовка кубической кривой Безье
    void drawBezier( const QPoint & p1, const QPoint & p2,
                     const QPoint & p3, const QPoint & p4);

    // закрасить линию в многоугольнике
    void drawLine( int y, int startX, int endX, const QColor & color );

    inline void refreshImageBuffer( QImage * buf ){
        img = buf;
    }

    inline void setColor( const QColor & c ){
        color = c ;
    }

    void drawImage( QWidget * w );

private:
    QImage * img;
    QColor color;

    void recursive_bezier(double x1, double y1,
                          double x2, double y2,
                          double x3, double y3,
                          double x4, double y4);
};

#endif // MQPAINTER_H
