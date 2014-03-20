#ifndef DRAWPANEL_H
#define DRAWPANEL_H

#include "circle.h"

#include <list>

#include <QObject>
#include <QWidget>
#include <QImage>
#include <QPainter>
#include <QPaintEvent>

class Circle;

class DrawPanel : public QWidget{
public:
    // стандартные размеры окна области рисования
    static const int DEFAULT_HEIGHT = 500;
    static const int DEFAULT_WIDTH = 500;

    static const QColor DEFAULT_COLOR;
    static const uchar whiteColor = 255;

private:
    Circle * pCircle;
    QImage * backBuffer;

    int oldWidth;
    int oldHeight;
public:
    DrawPanel( int w, int h, QWidget *parent = 0 );
    virtual ~DrawPanel();

    Circle* getCircle() const;

private:
    void paintEvent( QPaintEvent * event );
};

#endif // DRAWPANEL_H
