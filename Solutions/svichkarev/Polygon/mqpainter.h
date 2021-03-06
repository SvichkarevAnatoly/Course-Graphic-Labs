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
};

#endif // MQPAINTER_H
