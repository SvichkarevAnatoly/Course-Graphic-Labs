#ifndef INTERFACE_DRAWABLE_H
#define INTERFACE_DRAWABLE_H

#include <QColor>

class DrawPanel;

class iDrawable{
public:
    virtual void draw( QImage * backBuffer, const QColor& color ) = 0;
};

#endif // INTERFACE_DRAWABLE_H
