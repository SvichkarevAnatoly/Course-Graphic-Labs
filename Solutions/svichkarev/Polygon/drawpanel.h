#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include "polygon.h"

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QList>

class Circle;

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
    QImage * backBuffer;
    Polygon & polygon;

    int oldWidth;
    int oldHeight;

    // флаг близкого замыкания
    bool flagNearClose;
public:
    DrawPanel( int w, int h, QWidget *parent = 0 );
    virtual ~DrawPanel();

private:
    virtual void paintEvent( QPaintEvent * event );
    virtual void mousePressEvent( QMouseEvent * event);
    virtual bool eventFilter(QObject *, QEvent *);

    // проверка возможности замыкания контура
    void checkNearClose( const QPoint & checkPoint );
};

#endif // DRAWPANEL_H
