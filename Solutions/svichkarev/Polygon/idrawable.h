#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include <QColor>
#include <QPainter> // TODO: убрать

class DrawPanel;

class iDrawable{
public:
    // TODO: вернуть
    virtual void draw( QImage * backBuffer, const QColor& color, QPainter & painter ) = 0;
};

#endif // INTERFACE_DRAWABLE_H
