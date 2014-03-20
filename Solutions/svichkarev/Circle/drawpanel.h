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

private:
    Circle* pCircle;
    QImage backBuffer;

public:
    DrawPanel( int w, int h, QWidget *parent = 0 );

    virtual void drawPixel( int x, int y, const QColor& color );
    Circle* getCircle() const;

protected: // TODO: почему protected?
    void paintEvent(QPaintEvent *event);
    void resizeEvent (QResizeEvent* event );
};

#endif // DRAWPANEL_H
