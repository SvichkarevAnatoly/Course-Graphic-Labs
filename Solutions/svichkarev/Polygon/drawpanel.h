#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include "setpolygons.h"

#include <QWidget>
#include <QPaintEvent>

class DrawPanel : public QWidget{
public:
    // стандартные размеры окна области рисования
    static const int DEFAULT_HEIGHT = 500;
    static const int DEFAULT_WIDTH = 500;

    static const int CLOSE_DISTANCE = 35;

    static const QColor DEFAULT_CONTOUR_COLOR;
    static const QColor DEFAULT_INNER_COLOR;

    static const uchar WHITE_COLOR = 255; //TODO: Большие буквы

private:
    MQPainter painter;
    QImage * imgBuffer;

    SetPolygons polygons;

    // флаг примагничивания
    bool flagMagnet;
public:
    DrawPanel( QWidget *parent );
    virtual ~DrawPanel();

private:
    /*Для нормальной работы при измении размеров окна нужно
        переводить координаты в систему центра окна,
        а при отрисовке обратно в систему окна*/
    virtual void paintEvent( QPaintEvent * event );
    virtual void mousePressEvent( QMouseEvent * event);
    virtual bool eventFilter(QObject *, QEvent *);

    // проверка возможности замыкания контура
    void checkNearClose( const QPoint & checkPoint );
};

#endif // DRAWPANEL_H
