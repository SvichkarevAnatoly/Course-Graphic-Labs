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

    static const QColor DEFAULT_COLOR;
    static const uchar whiteColor = 255; //TODO: Большие буквы

private:
    QImage * backBuffer;
    Polygon & polygon;

    int oldWidth;
    int oldHeight;
public:
    DrawPanel( int w, int h, QWidget *parent = 0 );
    virtual ~DrawPanel();

private:
    void paintEvent( QPaintEvent * event );
    void mousePressEvent( QMouseEvent * event);
};

#endif // DRAWPANEL_H
