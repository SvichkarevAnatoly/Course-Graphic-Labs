#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include <QColor>
#include "mqpainter.h" // TODO: убрать

class DrawPanel;

class iDrawable{
public:
    // TODO: вернуть
    virtual void draw( QImage * backBuffer, const QColor& color, MQPainter & painter ) = 0;
};

#endif // INTERFACE_DRAWABLE_H
